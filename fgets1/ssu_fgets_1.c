#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define SECOND_TO_MICRO 1000000
#define BUFFER_SIZE 1024

void ssu_runtime (struct timeval *begin_t, struct timeval *end_t);

int main(void)
{
	struct timeval begin_t, end_t;
	char buf[BUFFER_SIZE];

	gettimeofday(&begin_t, NULL);
	
	while (fgets(buf, BUFFER_SIZE, stdin) != NULL) {
		//fgtes in standard input
		if (fputs(buf, stdout) == EOF) {
			//fputs int standard output -> if error print error message to standard error
			//exit
			fprintf(stderr, "standard output error\n");
			exit(1);
		}
	}

	gettimeofday(&end_t, NULL);

	ssu_runtime(&begin_t, &end_t);

	exit(0);
}
void ssu_runtime (struct timeval *begin_t, struct timeval *end_t) {
	//for calculate and print runtime
	end_t -> tv_sec -= begin_t -> tv_sec;

	if (end_t -> tv_usec < begin_t -> tv_usec) {
		end_t -> tv_sec--;
		end_t -> tv_usec += SECOND_TO_MICRO;
	}

	end_t -> tv_usec -= begin_t -> tv_usec;

	printf("runtime : %ld:%06ld(sec:usec)\n",
			end_t -> tv_sec, end_t -> tv_usec);
}
