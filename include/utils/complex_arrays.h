#pragma once

typedef struct ComplexArray_list {
    void** items;
    int capacity;
    int size;
} ComplexArray_list;

typedef struct ComplexArray {
    ComplexArray_list vector_list;

    int   (*free_array       )  (struct ComplexArray*);
    int   (*resize_array     )  (struct ComplexArray*, int);
    int   (*push_item_array  )  (struct ComplexArray*, void *);
    int   (*set_item_array   )  (struct ComplexArray*, int, void *);
    void* (*get_item_array   )  (struct ComplexArray*, int);
    int   (*delete_item_array)  (struct ComplexArray*, int);
} ComplexArray;

ComplexArray* complex_array_init();