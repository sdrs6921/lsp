#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define BUFFER_SIZE 1024
#define SECOND_TO_MICRO 1000000

void ssu_runtime (struct timeval *begin_t, struct timeval *end_t) {
	//calculate and print runtime
	end_t -> tv_sec -= begin_t -> tv_sec;

	if (end_t -> tv_usec < begin_t -> tv_usec) {
		end_t -> tv_sec--;
		end_t -> tv_usec += SECOND_TO_MICRO;
	}

	end_t -> tv_usec -= begin_t -> tv_usec;

	printf("runtime : %ld:%06ld(sec:usec)\n",
			end_t -> tv_sec, end_t -> tv_usec);
}

int main(void)
{
	struct timeval begin_t, end_t;
	char buf[BUFFER_SIZE];
	int a, b;
	int i;

	gettimeofday(&begin_t, NULL);
	
	setbuf(stdin, buf);//Line buffering to Fully buffering
	scanf("%d %d", &a, &b);

	for (i = 0; buf[i] != '\n'; i++)//put character in buf until \n
		putchar(buf[i]);

	putchar('\n');
	gettimeofday(&end_t, NULL);
	
	ssu_runtime(&begin_t, &end_t);
	exit(0);
}
