#include <fs/vfs.h>
 
#include <drivers/serial_port.h>
#include <arch/x86/isr.h>

#include <core/print.h>
#include <core/string.h>

#include <mem/kheap.h>

VFS* vfs;
int log = 0;
int fid = 0;

Directory_t* home;
Directory_t* bin;
Directory_t* lib;
Directory_t* tmp;
Directory_t* cfg;

void init_vfs() {
    vfs->root = kmalloc(sizeof(Directory_t));
    strcpy(vfs->root->name, "/");
    vfs->root->num_files = 0;
    vfs->root->num_directories = 0;

    home = create_dir("home", vfs->root);
    bin = create_dir("bin", vfs->root);
    lib = create_dir("lib", vfs->root);
    tmp = create_dir("tmp", vfs->root);
    cfg = create_dir("cfg", vfs->root);

    create_file("ls",    bin);
    create_file("mkdir", bin);
    create_file("touch", bin);
    create_file("rm",    bin);

    create_file("config.os", cfg);
}

void set_log(int _log) { log = _log; }

Directory_t* get_root_dir() { return vfs->root; }
Directory_t* get_home_dir() { return home; }
Directory_t* get_bin_dir() { return bin; }
Directory_t* get_lib_dir() { return lib; }
Directory_t* get_tmp_dir() { return tmp; }
Directory_t* get_cfg_dir() { return cfg; }

File_t* get_file_in_dir(Directory_t* dir, char* fname) {
    for (int i = 0; i < dir->num_files; i++) 
        if (strcmp(dir->files[i]->name, fname) == 0)
            return dir->files[i];

    return NULL;
}

File_t* get_file_by_fid(Directory_t* parent, int fid) {
    for (int i = 0; i < parent->num_files; i++)
        if (parent->files[i]->fid == fid) {
            printf("LOL %s", parent->files[i]->name);
            return parent->files[i];
        }

    return NULL;
}

Directory_t* get_dir_in_dir(Directory_t* dir, char* dname) {
    for (int i = 0; i < dir->num_directories; i++) 
        if (strcmp(dir->directories[i]->name, dname) == 0)
            return dir->directories[i];

    return NULL;
}

int fputc(int c, File_t* file) {
    int len = strlen(file->data);
    file->data = krealloc(file->data, len + 2);
    if (file->data == NULL) 
        return -1;
    file->data[len] = c;
    file->data[len+1] = '\0';
    return 0;
}

int fread(void* ptr, int size, int count, File_t* file) {
    int total = size * count;
    int n = 0;
    
    while (n < total) {
        int c = file->data[n];
        if (c == '\0') break;
        *((char*)ptr + n) = c;
        n++;
    }

    return n / size;
}


int fwrite(const void* ptr, int size, int count, File_t* file) {
    file->data = (char*)krealloc(file->data, (size * count) + 1);
    file->data = (char*)ptr;
}

Directory_t* find_directory(Directory_t* dir, char* path) {
    if (strcmp(path, ".") == 0)
        return dir;
    
    if (strcmp(path, "..") == 0) 
        return dir->parent;

    if (strcmp(path, "/") == 0) 
        return vfs->root;
    
    for (int i = 0; i < dir->num_directories; i++) {
        if (strcmp(dir->directories[i]->name, path) == 0) 
            return dir->directories[i];
    }
    
    for (int i = 0; i < dir->num_files; i++) {
        if (strcmp(dir->files[i]->name, path) == 0) {
            if (log == 1)
                printf("Path is a file, not a directory\n");
            serial_printf("[\x1b[1;33mVFS\x1b[0;0m] Path is a file, not a directory\n", path);
            return NULL;
        }
    }
    
    char *next_dir = strtok(path, "/");
    char *rest_of_path = strtok(NULL, "");
    
    if (next_dir == NULL) {
        if (log == 1)
            printf("Invalid path \"%s\"\n", path);
        serial_printf("[\x1b[1;33mVFS\x1b[0;0m] Invalid path \"%s\"\n", path);
        return NULL;
    }
    
    Directory_t* next = find_directory(dir, next_dir);
    if (next == NULL) 
        return NULL;
    
    return find_directory(next, rest_of_path);
}

// Create a new file in the VFS 
File_t* create_file(char* filename, Directory_t* dir) {
    serial_printf("[\x1b[1;33mVFS\x1b[0;0m] Creating file \"%s\" in \"%s\"\n", filename, dir->name);

    for (int i = 0; i < dir->num_files; i++) {
        if (strcmp(dir->files[i]->name, filename) == 0) {
            if (log == 1) 
                printf("File already exists\n");
            serial_printf("[\x1b[1;33mVFS\x1b[0;0m] File already exists\n");
            return NULL;
        }
    }

    for (int i = 0; i < dir->num_files; i++) {
        if (strcmp(dir->files[i]->name, filename) == 0) {
            if (log == 1) 
                printf("Directory with this name already exists\n");
            serial_printf("[\x1b[1;33mVFS\x1b[0;0m] Directory with this name already exists\n");
            return NULL;
        }
    }

    if (dir->num_files == MAX_FILES) {
        if (log == 1)
            printf("Directory is full\n");
        serial_printf("[\x1b[1;33mVFS\x1b[0;0m] Directory is full\n");
        return NULL;
    }

    // strcpy(dir->files[dir->num_files]->name, filename);
    // dir->files[dir->num_files]->name = (char*)kmalloc(sizeof(char) * strlen(filename));
    // dir->files[dir->num_files]->name = filename;

    // dir->files[dir->num_files].data = (char*)kmalloc(1);
    // dir->files[dir->num_files].data = "\0";

    // dir->files[dir->num_files].parent = dir;
    // fid++; dir->files[dir->num_files].fid = fid;
    File_t* new_file = (File_t*)kmalloc(sizeof(File_t));
    strcpy(new_file->name, filename);
    
    new_file->data = (char*)kmalloc(1);
    new_file->data = "\0";

    new_file->parent = dir;
    fid++;
    new_file->fid = fid;

    dir->files[dir->num_files] = new_file;
    dir->num_files++;

    if (log == 1)
        printf("Succesfully created file \"%s\" in \"%s\"\n", filename, dir->name);
    serial_printf("[\x1b[1;33mVFS\x1b[0;0m] Succesfully created file \"%s\" in \"%s\"\n", filename, dir->name);

    return new_file;
}

// Create a new directory in the VFS 
Directory_t* create_dir(char* dirname, Directory_t* dir) {
    serial_printf("[\x1b[1;33mVFS\x1b[0;0m] Creating directories \"%s\" in \"%s\"\n", dirname, dir->name);

    for (int i = 0; i < dir->num_directories; i++) {
        if (strcmp(dir->directories[i]->name, dirname) == 0) {
            if (log == 1) 
                printf("File with this name already exists\n");
            serial_printf("[\x1b[1;33mVFS\x1b[0;0m] File with this name already exists\n");
            return NULL;
        }
    }

    for (int i = 0; i < dir->num_directories; i++) {
        if (strcmp(dir->directories[i]->name, dirname) == 0) {
            if (log == 1) 
                printf("Directory with this name already exists\n");
            serial_printf("[\x1b[1;33mVFS\x1b[0;0m] Directory with this name already exists\n");
            return NULL;
        }
    }

    if (dir->num_directories == MAX_DIRECTORIES) {
        if (log == 1)
            printf("Directory is full\n");
        serial_printf("[\x1b[1;33mVFS\x1b[0;0m] Directory is full\n");
        return NULL;
    }

    Directory_t* new_dir = (Directory_t*)kmalloc(sizeof(Directory_t));
    strcpy(new_dir->name, dirname);
    new_dir->num_files = 0;
    new_dir->num_directories = 0;
    new_dir->parent = dir;
    
    dir->directories[dir->num_directories] = new_dir;
    dir->num_directories++;
    
    if (log == 1)
        printf("Succesfully created directories \"%s\" in \"%s\"\n", dirname, dir->name);
    serial_printf("[\x1b[1;33mVFS\x1b[0;0m] Succesfully created directories \"%s\" in \"%s\"\n", dirname, dir->name);
    return new_dir;
}

void print_file(File_t* file) {
    set_print_fg(color(255, 255, 255));
    printf("- ");
    set_print_fg(color(138, 178, 242));
    printf("%s\n", file->name);
}

void print_dir(Directory_t* dir) {
    set_print_fg(color(255, 255, 255));
    printf("- ");
    set_print_fg(color(230, 242, 138));
    printf("%s\n", dir->name);
}

void print_tabs_file(int tabs) {
    for (int i = 0; i < tabs; i++)
        printf("\t");
}

void print_out_tree(Directory_t* dir, int tabs, int print_main_dir_) {
    if (dir == NULL)
        dir = vfs->root;

    if (print_main_dir_ == 1) {
        print_dir(dir);
        tabs++;
    }

    for (int i = 0; i < dir->num_files; i++) {
        print_tabs_file(tabs);
        print_file(dir->files[i]);
    }

    for (int i = 0; i < dir->num_directories; i++) {
        print_tabs_file(tabs);
        print_dir(dir->directories[i]);

        tabs += 1;
        print_out_tree(dir->directories[i], tabs, 0);
        tabs -= 1;
    }
}