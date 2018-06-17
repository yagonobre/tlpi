#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include "lib/tlpi_hdr.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int
main(int argc, char *argv[])
{
    int opt, openFlags, outputFd, append = 0;
    char *file;
    char buf[BUF_SIZE];
    ssize_t numRead;

    while ((opt = getopt(argc, argv, "a")) != -1) {
        switch (opt) {
            case 'a':
                append = 1;
                break;
        }
    }
    if (optind < argc)
        file = argv[optind];

    openFlags = O_CREAT | O_WRONLY;
    if (append)
        openFlags |= O_APPEND;

    outputFd = open(file, openFlags);
    if (outputFd == -1)
        errExit("opening file");

    while ((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0) {
        if (write(STDOUT_FILENO, buf, numRead) != numRead)
            errExit("writing to stdout");
        if (write(outputFd, buf, numRead) != numRead)
            errExit("writing to file");
    }

    if(close(outputFd) == -1)
        errExit("closing file");

    return(0);
}
