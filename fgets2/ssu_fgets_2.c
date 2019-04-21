#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define SECOND_TO_MICRO 1000000
#define BUFFER_MAX 256

void ssu_runtime (struct timeval *begin_t, struct timeval *end_t);

int main(void)
{
	struct timeval begin_t, end_t;
	char command[BUFFER_MAX];
	char *prompt = "Prompt>>";

	gettimeofday(&begin_t, NULL);

	while (1) {
		fputs(prompt, stdout);//print prompt to stdout

		if (fgets(command, sizeof(command), stdin) == NULL)//if stdin is null
			break;

		system(command);//input command
	}

	fprintf(stdout, "Good bye..\n");//if break while loop
	fflush(stdout);//flush input stdout buffer

	gettimeofday(&end_t, NULL);

	ssu_runtime(&begin_t, &end_t);
	exit(0);
}
void ssu_runtime (struct timeval *begin_t, struct timeval *end_t) {
	//calculate and print runtime
	end_t -> tv_sec -= begin_t -> tv_sec;

	if (end_t -> tv_usec < begin_t -> tv_usec) {
		end_t -> tv_sec--;
		end_t -> tv_usec += SECOND_TO_MICRO;
	}

	end_t -> tv_usec -= begin_t -> tv_usec;

	printf("runtime %ld:%06ld(sec:usec)\n",
			end_t -> tv_sec, end_t -> tv_usec);
}
