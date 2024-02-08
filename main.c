#include <stdio.h>
#include <sys/wait.h>

#include <system_server.h>
#include <gui.h>
#include <input.h>
#include <web_server.h>

static void
sigchldHandler(int sig)
{
	printf("handler: Caught SIGCHLD : %d\n", sig);
	printf("handler: returning\n");
}

int main()
{
    pid_t spid, gpid, ipid, wpid;
    int status, savedErrno;
    int sigCnt;
    sigset_t blockMask, emptyMask;
    struct sigaction sa;

    signal(SIGCHLD, sigchldHandler);

    printf("main: main process started\n");
    printf("main: create system server\n");
    spid = create_system_server();
    printf("main: create web server\n");
    wpid = create_web_server();
    printf("main: create input process\n");
    ipid = create_input();
    printf("main: create gui process\n");
    gpid = create_gui();

    waitpid(spid, &status, 0);
    waitpid(gpid, &status, 0);
    waitpid(ipid, &status, 0);
    waitpid(wpid, &status, 0);

    return 0;
}
