#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define SECOND_TO_MICRO 1000000
#define BUFFER_SIZE 1024

void ssu_runtime (struct timeval *begin_t, struct timeval *end_t);

int main(int argc, char *argv[]) 
{
	struct timeval begin_t, end_t;
	char buf[BUFFER_SIZE];
	FILE *fp;

	gettimeofday(&begin_t, NULL);

	if (argc != 2) {
		//argument count needed 2 if not print error message to standard error
		fprintf(stderr, "usage :%s <file>\n", argv[0]);
		exit(1);
	}

	if ((fp = fopen(argv[1], "w+")) == NULL) {
		//if fopen w+ mode failed
		fprintf(stderr, "fopen error for %s\n", argv[1]);
		exit(1);
	}

	fputs("Input String >> ", stdout);//fputs to standard output
	gets(buf);//input String to buf
	fputs(buf, fp);//input buf to fp
	rewind(fp);//rewind fp
	fgets(buf, sizeof(buf), fp);//input fp to buf
	puts(buf);//put buf to stdout
	fclose(fp);//cloes fp

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
