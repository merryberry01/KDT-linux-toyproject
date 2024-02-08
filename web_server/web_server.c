#include <stdio.h>

#include <system_server.h>
#include <gui.h>
#include <input.h>
#include <web_server.h>

int create_web_server()
{
	pid_t systemPid;

	printf("create_web_server: creating web server...\n");

	switch(systemPid = fork()){
		case 0:
			if(execl("/usr/local/bin/filebrowser", "filebrowser", "-p", "8282", (char *)NULL) < 0)
				perror("execl() from create_web_server()");
			break;
		case -1:
			perror("fork() from create_web_server()");
			break;
		default:
			break;
	}
	return systemPid;
}
