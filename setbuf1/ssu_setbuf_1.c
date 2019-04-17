#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define BUFFER_SIZE 1024
#define SECOND_TO_MICRO 1000000

void ssu_runtime(struct timeval *begin_t, struct timeval *end_t) {
	//calculate and print runtime
	end_t -> tv_sec -= begin_t -> tv_sec;

	if (end_t -> tv_usec < begin_t -> tv_usec) {
		end_t -> tv_sec--;
		end_t -> tv_usec += SECOND_TO_MICRO;
	}

	end_t -> tv_usec -= begin_t -> tv_usec;

	printf("runtime : %ld:%06ld(sec:usec)\n",
			end_t -> tv_sec, begin_t -> tv_usec);
}

int main(void)
{
	struct timeval begin_t, end_t;
	char buf[BUFFER_SIZE];

	gettimeofday(&begin_t, NULL);

	setbuf(stdout, buf);//set buffer fully buffering
	printf("Hello, ");
	sleep(1);
	printf("OSLAB!!");
	sleep(1);
	printf("\n");
	sleep(1);

	setbuf(stdout, NULL);//set buffer no buffering
	printf("How");
	sleep(1);
	printf(" are");
	sleep(1);
	printf(" you?");
	sleep(1);
	printf("\n");
	gettimeofday(&end_t, NULL);
	
	ssu_runtime(&begin_t, &end_t);
	exit(0);
}
