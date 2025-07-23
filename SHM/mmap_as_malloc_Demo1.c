#include<stdio.h>
#include<sys/mman.h>
#include<errno.h>

#if 0
void *mmap(void *addr,size_t len,int prot,int flags,int fd,off_t offset);

int munmap(void *addr,size_t len);

#endif

int main(int argc,char **argv){
    int n=5;

    int *ptr=mmap(NULL,
    n*sizeof(int),
    PROT_READ|
    PROT_WRITE,
    MAP_PRIVATE|
    MAP_ANONYMOUS,0,0
);

if(ptr==MAP_FAILED){
    printf("Mapping Failed, errno: %d",errno);
    return 1;
}

for(int i=0;i<n;i++)
ptr[i]=i*10;

for(int i=0;i<n;i++){
    printf("[%d]",ptr[i]);
}

printf("\n");
int err=munmap(ptr,10*sizeof(int));
if(err!=0){
    printf("Unmapping Failed\n");
    return 1;
}
return 0;
     
}