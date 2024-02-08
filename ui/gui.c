#include <stdio.h>

#include <system_server.h>
#include <gui.h>
#include <input.h>
#include <web_server.h>

int create_gui()
{
    pid_t systemPid;

    printf("create_gui: creating gui process\n");

    sleep(3);

    switch (systemPid = fork()) {
    case -1:
        printf("fork failed\n");
    case 0:
        if (execl("/usr/bin/google-chrome-stable", "google-chrome-stable", "http://localhost:8282", NULL)) {
            printf("execfailed\n");
        }
        break;
    default:
        break;
    }

    return 0;
}
