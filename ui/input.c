#include <stdio.h>
#include <sys/prctl.h>

#include <system_server.h>
#include <gui.h>
#include <input.h>
#include <web_server.h>

int input()
{
	printf("input: input process is created\n");

	while (1) {
		sleep(1);
	}

	return 0;
}

int create_input()
{
	pid_t systemPid;
	const char *name = "input";

	printf("create_input: creating input process\n");
	
	switch(systemPid = fork()){
		case 0:
			if(prctl(PR_SET_NAME, (unsigned long) name) < 0)
				perror("prctl() from create_input()");
			break;
		case -1:
			perror("fork()  from create_input()");
			break;
		default:
			break;
	}

	return systemPid;
}
