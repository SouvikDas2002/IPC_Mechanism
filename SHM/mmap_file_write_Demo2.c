#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <memory.h>

static void breakpoint() {}

typedef struct student_
{
    int roll_no;
    int marks;
    char name[128];
    char city[128];
} student_t;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("File path not mentioned\n");
        exit(0);
    }

    const char *filepath = argv[1];

    int fd = open(filepath, O_RDWR);

    if (fd < 0)
    {
        printf("\n\"%s\"could not open", filepath);
        exit(1);
    }

    struct stat statbuf;
    int err = fstat(fd, &statbuf);

    // After a successful call, statbuf will contain:

    // statbuf.st_size: File size in bytes
    // statbuf.st_mode: File type and permissions
    // statbuf.st_uid: User ID of owner
    // statbuf.st_gid: Group ID of owner
    // statbuf.st_mtime: Last modification time
    // statbuf.st_ino: Inode number
    // statbuf.st_nlink: Number of hard links

    
    // printf("File size: %ld bytes\n", statbuf.st_size);
    // printf("Number of links: %ld\n", statbuf.st_nlink);
    // printf("File inode: %ld\n", statbuf.st_ino);
    // printf("File permissions: %o\n", statbuf.st_mode & 0777);
    // printf("Owner UID: %d\n", statbuf.st_uid);
    // printf("Group GID: %d\n", statbuf.st_gid);
    // printf("Last access time: %s", ctime(&statbuf.st_atime));
    // printf("Last modification time: %s", ctime(&statbuf.st_mtime));
    // printf("Last status change time: %s", ctime(&statbuf.st_ctime));


    if (err < 0)
    {
        printf("\n\"%s\"could not open", filepath);
        exit(2);
    }

    char *ptr=mmap(NULL,
        statbuf.st_size,
        PROT_READ|PROT_WRITE,
        MAP_SHARED,fd,0);

    if(ptr==MAP_FAILED){
        printf("Mapping failed errono %d",errno);
        return 1;
    }

    close(fd);

    student_t stu1={123,90,"Souvik","Gurgaon"};

    memcpy(ptr,&stu1,sizeof(stu1));
    msync(ptr,sizeof(stu1),MS_SYNC);

    err=munmap(ptr,statbuf.st_size);

    if(err!=0){
        printf("Unmapping Failed\n");
        return 1;
    }
    return 0;
}