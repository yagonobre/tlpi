#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "lib/tlpi_hdr.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

void usage(char *argv[]) {
    errExit("Usage: ./$s <src> <dst>", argv[0]);
}

int main(int argc, char *argv[]) {
    int srcFd, dstFd, filePerms;
    char *fileSrc, *fileDst;
    char buf[BUF_SIZE];
    ssize_t numRead;

    if (argc != 3)
        usage(argv);

    fileSrc = argv[1];
    fileDst = argv[2];
    filePerms = (S_IRUSR | S_IWUSR | S_IRGRP |
		         S_IROTH | S_IWOTH);

    srcFd = open(fileSrc, O_RDONLY);
    dstFd = open(fileDst, O_CREAT | O_WRONLY, filePerms);
    if (srcFd == -1 || dstFd == -1)
        errExit("opening files");

    while((numRead = read(srcFd, buf, BUF_SIZE)) > 0) {
        if(write(dstFd, buf, numRead) != numRead)
            errExit("writing to file");
    }

    if(close(srcFd) == -1)
        errExit("closing src file");

    if(close(dstFd) == -1)
        errExit("closing dst file");

    return(0);
}
