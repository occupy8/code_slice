#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(void)
{
        int fd,res;
        struct flock region;

        fd = open("test_file", O_RDWR | O_CREAT);
        if(fd == -1)
        {
                printf("Open error.\n");
                exit(1);
        }

        region.l_type=F_RDLCK;
        region.l_whence=SEEK_SET;
        region.l_start=0;
        region.l_len=50;
        region.l_pid=1;
        if((res=fcntl(fd,F_GETLK,&region))==0)
        {
                if(region.l_type==F_UNLCK)
                {
                        printf("Read lock will be setted.\n");
                        printf("l.type has not been changed.\n");
                        printf("l_start=%d\n",(int)region.l_start);
                        printf("l_len=%d\n",(int)region.l_len);
                        printf("l_pid=%d\n",(int)region.l_pid);
                }
        }
        else
        {
                printf("Set lock error.\n");
                exit(1);
        }

        region.l_type = F_RDLCK;
        region.l_whence = SEEK_SET;
        region.l_start = 0;
        region.l_len = 40;
        region.l_pid = 2;
        if((res = fcntl(fd, F_SETLK, &region))==0)
        {
                if(region.l_type==F_RDLCK)
                {
                        printf("l.type has been changed.\n");
                        printf("l_start=%d\n",(int)region.l_start);
                        printf("l_len=%d\n",(int)region.l_len);
                        printf("l_pid=%d\n",(int)region.l_pid);
                }
        }
        else
        {
                printf("Set lock error.\n");
                exit(1);
        }

        region.l_type=F_WRLCK;
        if((res=fcntl(fd,F_GETLK,&region))==0)
        {
                if(region.l_type==F_UNLCK)
                {
                        printf("Write lock will be setted.\n");
                        printf("l.type has not been changed.\n");
                        printf("l_start=%d\n",(int)region.l_start);
                        printf("l_len=%d\n",(int)region.l_len);
                        printf("l_pid=%d\n",(int)region.l_pid);
                }
        }
        else
        {
                printf("Set lock error.\n");
                exit(1);
        }

        region.l_type = F_WRLCK;
        region.l_whence = SEEK_SET;
        region.l_start = 0;
        region.l_len = 40;
        region.l_pid = 2;
        if((res = fcntl(fd, F_SETLK, &region))==0)
        {
                if(region.l_type == F_WRLCK)
                {
                        printf("l.type has been changed.\n");
                        printf("l_start=%d\n",(int)region.l_start);
                        printf("l_len=%d\n",(int)region.l_len);
                        printf("l_pid=%d\n",(int)region.l_pid);
                }
        }
        else
        {
                printf("Set lock error.\n");
                exit(1);
        }

        close(fd);
}
