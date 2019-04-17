#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define SECOND_TO_MICRO 1000000

void ssu_runtime (struct timeval *begin_t, struct timeval *end_t);

int main(void)
{
	struct timeval begin_t, end_t;
	int character;

	gettimeofday(&begin_t, NULL);
	
	while ((character = getc(stdin)) != EOF) 
		if(putc(character, stdout) == EOF) {
			fprintf(stderr, "standard output error\n");
			exit(1);
		}
	
	if(ferror(stdin)) {
		fprintf(stderr, "standard input error\n");
		exit(1);
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
