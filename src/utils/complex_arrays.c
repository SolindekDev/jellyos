#include <utils/complex_arrays.h>

#include <arch/x86/isr.h>

#include <mem/kheap.h>

// TODO: make compolex arrays work

int resize_array(ComplexArray* v, int capacity) {
    if (v) {
        void **items = krealloc(v->vector_list.items, sizeof(void *) * capacity);
        if (items) {
            v->vector_list.items = items;
            v->vector_list.capacity = capacity;
            return 1;
        }
    }
    
    return 0;
}

int push_item_array(ComplexArray* v, void* item) {
    int status = 0;
    if (v) {
        if (v->vector_list.capacity == v->vector_list.size) {
            status = resize_array(v, v->vector_list.capacity * 2);
            if (status != 0) {
                v->vector_list.items[v->vector_list.size++] = item;
            }
        } else {
            v->vector_list.items[v->vector_list.size++] = item;
            status = 1;
        }
    }

    return status;
}

int set_item_array(ComplexArray* v, int index, void* item) {
    if (v) {
        if ((index >= 0) && (index < v->vector_list.size)) {
            v->vector_list.items[index] = item;
            return 1;
        }
    }
    
    return 0;
}

void* get_item_array(ComplexArray* v, int index) {
    void* readData = NULL;
    if (v)
        if ((index >= 0) && (index < v->vector_list.size)) 
            readData = v->vector_list.items[index];

    return readData;
}

int delete_item_array(ComplexArray *v, int index) {
    int status = 0;
    if (v) {
        if ((index < 0) || (index >= v->vector_list.size))
            return status;
        v->vector_list.items[index] = NULL;
        for (int i = index; (i < v->vector_list.size - 1); ++i)
        {
            v->vector_list.items[i] = v->vector_list.items[i + 1];
            v->vector_list.items[i + 1] = NULL;
        }
        v->vector_list.size--;
        if ((v->vector_list.size > 0) && ((v->vector_list.size) == (v->vector_list.capacity / 4))) 
            resize_array(v, v->vector_list.capacity / 2);
        
        return status;
    }

    return status;
}

int free_array(ComplexArray* v) {
    if (v) {
        kfree(v->vector_list.items);
        v->vector_list.items = NULL;
        return 1;
    }

    return 0;
}

ComplexArray* complex_array_init() {
    ComplexArray* complex_array = (ComplexArray*)kmalloc(sizeof(complex_array));

    complex_array->free_array        = free_array;
    complex_array->resize_array      = resize_array;
    complex_array->push_item_array   = push_item_array;
    complex_array->set_item_array    = set_item_array;
    complex_array->get_item_array    = get_item_array;
    complex_array->delete_item_array = delete_item_array;

    complex_array->vector_list.capacity = 8;
    complex_array->vector_list.size     = 0;
    complex_array->vector_list.items    = (void**)kmalloc(sizeof(void*) * complex_array->vector_list.capacity);

    return complex_array;
}
