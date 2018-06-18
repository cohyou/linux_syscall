#include <unistd.h> // for dup

#include <sys/stat.h> // for open
#include <fcntl.h> // for open
#include <stdio.h> // for perror()

int main() {
    int fd;
    char *argv[3];
    extern char **environ;

    if ((fd = open("file.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666)) < 0) {
        perror("open");
        return 1;
    }
    close(1);
    if (dup(fd) < 0) {
        perror("dup");
        return 1;
    }
    close(fd);

    argv[0] = "echo";
    argv[1] = "Hello";
    argv[2] = NULL;
    execve("/bin/echo", argv, environ);

    perror("execve");
    return 1;
}
