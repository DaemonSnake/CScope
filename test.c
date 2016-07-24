#include "scope.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

void file_stuff(void(*writer)(int fd))
{
    int fd = open("file", O_CREAT|O_RDWR|O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    if (fd < 0)
        return ;
    scope(exit)
    {
        printf("closing file\n");
        close(fd);
    }
    writer(fd);
    write(fd, "END of FILE\n", 12);
    printf("End of file_stuff\n");
}

void writer(int fd)
{
    write(fd, "Hello how u r ?\n", 16);
}

int main()
{
    scope(exit)
    {
        scope(exit)
        {
            printf("Second\n");
        }
        printf("First\n");
    }
    printf("before file_stuff\n");
    file_stuff(writer);
    printf("End of main\n");
}
