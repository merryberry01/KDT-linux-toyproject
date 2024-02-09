#include <stdio.h>
#include <sys/prctl.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>

#include <system_server.h>
#include <gui.h>
#include <input.h>
#include <web_server.h>

static int toy_timer = 0;

void sigrtmax_handler(int signo){
	clock_t clk = clock();
	printf("clock %ld\n", clk);
}

int posix_sleep_ms(unsigned int timeout_ms)
{
    struct timespec sleep_time;

    sleep_time.tv_sec = timeout_ms / MILLISEC_PER_SECOND;
    sleep_time.tv_nsec = (timeout_ms % MILLISEC_PER_SECOND) * (NANOSEC_PER_USEC * USEC_PER_MILLISEC);

    return nanosleep(&sleep_time, NULL);
}

int system_server()
{
    struct itimerspec ts;
    struct sigaction  sa;
    struct sigevent   sev;
    timer_t *tidlist;

    printf("나 system_server 프로세스!\n");

    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = sigrtmax_handler;
    sigemptyset(&sa.sa_mask);
    if(sigaction(SIGRTMAX, &sa, NULL) == -1)
	    perror("sigaction() from system_server()");

    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMAX;
    
    tidlist = malloc(sizeof(timer_t));
    sev.sigev_value.sival_ptr = tidlist;

    if(timer_create(CLOCK_REALTIME, &sev, tidlist) == -1)
	    perror("timer_create() from system_server()");
   
    ts.it_interval.tv_sec = 5;
    ts.it_interval.tv_nsec = 0;
    ts.it_value.tv_sec = 5;
    ts.it_value.tv_nsec = 0;

    if(timer_settime(*tidlist, 0, &ts, NULL) == -1)
	    perror("timer_settime() from system_server()");


    while (1) {
        posix_sleep_ms(5000);
    }

    return 0;
}

int create_system_server()
{
    pid_t systemPid;
    const char *name = "system_server";

    printf("여기서 시스템 프로세스를 생성합니다.\n");

    /* fork 를 이용하세요 */
    switch (systemPid = fork()) {
    case -1:
        printf("fork failed\n");
    case 0:
        /* 프로세스 이름 변경 */
        if (prctl(PR_SET_NAME, (unsigned long) name) < 0)
            perror("prctl()");
        system_server();
        break;
    default:
        break;
    }

    return 0;
}
