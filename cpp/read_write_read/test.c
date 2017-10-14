#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <errno.h>

void create_file(const char* filename)
{
    assert(filename != NULL);
    
    int fd = open(filename, O_WRONLY | O_CREAT, 0777);
    if (fd == -1) {
        printf("create_file() failed: %s\n", strerror(errno));
        return;
    }
    
    char *buf = "1234567890";
    write(fd, buf, strlen(buf));
    close(fd);
}

void read_write_read(const char *filename)  
{  
    assert(filename != NULL);  
      
    char *buf="34";  
    char read_buf[2];  
    int fd = open(filename, O_RDWR);  
    if (fd == -1) {  
        printf(" -----%s open failed: %s", filename, strerror(errno));  
        return;
    }  

    read(fd, read_buf, 2);  
    printf(" -----before write: %s = (%c,%c)\n", filename, read_buf[0], read_buf[1]);  
    
    lseek(fd, 0, SEEK_SET);
    write(fd, buf, strlen(buf));
    
    lseek(fd, 0, SEEK_SET);  
    read(fd, read_buf, 2);  
    printf(" -----after write: %s = (%c,%c)\n",filename,read_buf[0],read_buf[1]);  
    
    ftruncate(fd, 2);
    
    close(fd);
} 

int main()
{
    const char* filename = "./test.bin";
    create_file(filename);
    read_write_read(filename);
    
    return 0;
}
