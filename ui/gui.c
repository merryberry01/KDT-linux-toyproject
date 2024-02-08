#include <stdio.h>

#include <system_server.h>
#include <gui.h>
#include <input.h>
#include <web_server.h>

int create_gui()
{
	pid_t systemPid;

	printf("create_gui: creating gui process...\n");
	switch(systemPid = fork()){
		case 0:
			if(execl("/usr/bin/google-chrome-stable", "google-chrome-stable", "http://localhost:8282", NULL) < 0)
				perror("execl() from create_gui()");
			break;
		case -1:
			perror("fork() in create_gui()");
			break;
		default:
			break;
	}

	sleep(3);
	return systemPid;
}
