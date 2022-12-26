#pragma once

#define MAX_FILES 100
#define MAX_DIRECTORIES 100

#define MAX_NAME_LENGTH 128

#define ROOT_FID 0

#define CREATE_FILE_ERROR_PATH_NOT_FOUND  -1
#define CREATE_FILE_ERROR_ALREADY_EXIST   -2
#define CREATE_FILE_ERROR_DIRECTORY_FULL  -3

typedef struct Directory_t Directory_t;

typedef struct File_t {
    char name[MAX_NAME_LENGTH];
    char* data;

    Directory_t* parent;

    int fid;
} File_t;
 
typedef struct Directory_t {
    char name[MAX_NAME_LENGTH];
    File_t* files[MAX_FILES];
    
    struct Directory_t* directories[MAX_DIRECTORIES];
    struct Directory_t* parent;

    int num_directories;
    int num_files;
} Directory_t;
 
typedef struct {
    Directory_t *root;
} VFS;

void init_vfs();

Directory_t* get_root_dir();
Directory_t* get_home_dir();
Directory_t* get_bin_dir();
Directory_t* get_lib_dir();
Directory_t* get_tmp_dir();
Directory_t* get_cfg_dir();

File_t* get_file_in_dir(Directory_t* dir, char* fname);

File_t* get_file_by_fid(Directory_t* parent, int fid);

Directory_t* get_dir_in_dir(Directory_t* dir, char* dname);

void set_log(int _log);

Directory_t* find_directory(Directory_t* dir, char* path);

File_t* create_file(char* filename, Directory_t* dir);

Directory_t* create_dir(char* dirname, Directory_t* dir);

int fputc(int c, File_t* file);

int fread(void* ptr, int size, int count, File_t* file);

int fwrite(const void* ptr, int size, int count, File_t* file);

void print_file(File_t* file);

void print_dir(Directory_t* dir);

void print_tabs_file(int tabs);

void print_out_tree(Directory_t* dir, int tabs, int print_main_dir_);