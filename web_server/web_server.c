#define _GNU_SOURCE

#include <stdio.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <sys/mman.h>
#include <signal.h>

#include <system_server.h>
#include <gui.h>
#include <input.h>
#include <web_server.h>

#define STACK_SIZE (1024 * 1024)

int child_func(void *arg){
    if (execl("/usr/local/bin/filebrowser", "filebrowser", "-p", "8282", (char *) NULL)) {
        perror("execl() from child_func()");
    }
    return 0;
}

int create_web_server()
{
    pid_t systemPid;
    char *stack;

    if((stack = mmap(NULL, STACK_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_STACK, -1, 0)) == -1)
        perror("mmap() from create_web_server()");

    printf("여기서 Web Server 프로세스를 생성합니다.\n");

    // fork를 clone + 새로운 namespace로 생성하세요.
    if((systemPid = clone(child_func, stack + STACK_SIZE, CLONE_NEWUTS | CLONE_NEWIPC | CLONE_NEWPID | CLONE_NEWNS | SIGCHLD, NULL)) == -1)
        perror("clone() from create_web_server()");

    return systemPid;
}