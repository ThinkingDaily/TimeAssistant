#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

/**
 * List all the files and directories under the specified directory, recursively.
 *
 */
void list_files(const char* directory, char*** filenames, int* file_count, int* array_size)
{
    DIR* dir;
    struct dirent* de;
    char file_name[FILENAME_MAX];
    struct stat st;
    
    dir = opendir(directory);
    if (NULL == dir) {
        printf("ERROR: open failed: %s(%s)\n", directory, strerror(errno));
        return;
    }
    
    bool end_with_slash = ('/' == directory[strlen(directory) - 1]);
    bool is_dir;
    while ((de = readdir(dir)) != 0) {
        strcpy(file_name, directory);
        if (!end_with_slash) strcat(file_name, "/");
        strcat(file_name, de->d_name);
        
        printf("de->d_name: %s\n", de->d_name);
        if ('.' == de->d_name[0]) {
            if (0 == de->d_name[1]) continue; // .
            if (('.' == de->d_name[1]) && (0 == de->d_name[2])) continue; // ..
        }
        
        if (stat(file_name, &st) != 0) {
            printf("stat failed: %s, %s\n", file_name, strerror(errno));
            continue;
        }
        
        if ((is_dir = S_ISDIR(st.st_mode)) || S_ISREG(st.st_mode)) {
            if (*file_count > *array_size) {
                *array_size = (*array_size) * 2;
                *filenames = (char**)realloc(*filenames, (*array_size) * sizeof(char*));
            }
            
            (*filenames)[(*file_count)++] = strdup(file_name);
            
            if (is_dir) {
                list_files(file_name, filenames, file_count, array_size);
            }
        } else {
            printf("Other files: %s\n", file_name);
        }
    }
    
    closedir(dir);
}

static void test(const char* directory)
{
    char** filenames;
    int file_count = 0;
    int array_size = 16;
    
    filenames = (char**)malloc(array_size * sizeof(char*));
    if (NULL == filenames) {
        printf("No memory.\n");
        return;
    }
    
    list_files(directory, &filenames, &file_count, &array_size);
    
    printf("All files:\n");
    for (int i = 0; i < file_count; i++) {
        printf("%s\n", filenames[i]);
        free(filenames[i]);
        filenames[i] = NULL;
    }
    
    free(filenames);
}

int main(int argc, const char* argv[])
{
    if (argc != 2) {
        printf("Usage: %s dir_name\n", argv[0]);
        return 1;
    }

    test(argv[1]);
    
    return 0;
}


