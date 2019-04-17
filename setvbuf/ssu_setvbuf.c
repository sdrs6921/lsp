#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define BUFFER_SIZE 1024
#define SECOND_TO_MICRO 1000000

void ssu_runtime (struct timeval *begin_t, struct timeval *end_t);
void ssu_setbuf (FILE *fp, char *buf);

int main(void)
{
	struct timeval begin_t, end_t;
	char buf[BUFFER_SIZE];
	char *fname = "/dev/pts/2";
	FILE *fp;

	gettimeofday(&begin_t, NULL);
	if ((fp = fopen(fname, "w")) == NULL) {
		fprintf(stderr, "open error for %s\n", fname);
		exit(1);
	}

	ssu_setbuf(fp, buf);
	fprintf(fp, "Hello, ");
	sleep(1);
	fprintf(fp, "UNIX!!");
	sleep(1);
	fprintf(fp, "\n");
	sleep(1);
	ssu_setbuf(fp, buf);
	fprintf(fp, "HOW");
	sleep(1);
	fprintf(fp, " ARE");
	sleep(1);
	fprintf(fp, " YOU?");
	sleep(1);
	fprintf(fp, "\n");
	sleep(1);
	gettimeofday(&end_t, NULL);

	ssu_runtime(&begin_t, &end_t);
	exit(0);
}

void ssu_runtime (struct timeval *begin_t, struct timeval *end_t) {
	//calculate and print runtime
	end_t -> tv_sec -= begin_t -> tv_sec;

	if (end_t -> tv_usec -= begin_t -> tv_usec) {
		end_t -> tv_sec--;
		end_t -> tv_usec += SECOND_TO_MICRO;
	}

	end_t -> tv_usec -= begin_t -> tv_usec;

	printf("runtime : %ld:%06ld(sec:usec)\n",
			end_t -> tv_sec, end_t -> tv_usec);
}

void ssu_setbuf(FILE *fp, char *buf) {
	size_t size;
	int fd;
	int mode;

	fd = fileno(fp);//fp -> fd

	if (isatty(fd))//is terminal?
		mode = _IOLBF;//set mode Line buffering
	else
		mode = _IOFBF;//set mode Fully buffering

	if (buf == NULL) {
		mode = _IONBF;//set mode none buffering
		size - 0;
	}
	else
		size = BUFFER_SIZE;

	setvbuf(fp, buf, mode, size);
}
