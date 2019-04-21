#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/time.h>

#define SECOND_TO_MICRO 1000000

void ssu_runtime(struct timeval *begin_t, struct timeval *end_t);

int main(void)
{
	struct timeval begin_t, end_t;
	char operator;
	FILE *fp;
	int character;
	int number = 0;

	gettimeofday(&begin_t, NULL);
	if ((fp = fopen("ssu_expr.txt", "r")) == NULL) {
		//if fopen error
		fprintf(stderr, "open error for ssu_ex[r.txt\n");
		exit(1);
	}

	while (!feof(fp)) {
		while ((character = fgetc(fp)) != EOF && isdigit(character))//if character is not EOF or DIGIT!!
			number = 10 * number + character - 48;//multly 10 and calculate ASCII CODE while find operator

		fprintf(stdout, " %d\n", number);
		number = 0;//number initialize 0

		if(character != EOF) {
			//if character is not end of file
			ungetc(character, fp);//return file stream
			operator = fgetc(fp);
			printf("operator => %c\n", operator);
		}
	}

	fclose(fp);

	gettimeofday(&end_t, NULL);

	ssu_runtime(&begin_t, &end_t);

	exit(0);

}
void ssu_runtime(struct timeval *begin_t, struct timeval *end_t) {
	//calculate and print runtime
	end_t -> tv_sec -= begin_t -> tv_sec;

	if (end_t -> tv_usec < begin_t -> tv_usec) {
		end_t -> tv_sec --;
		end_t -> tv_usec += SECOND_TO_MICRO;
	}

	end_t -> tv_usec -= begin_t -> tv_usec;

	printf("ssu_runtime : %ld:%06ld(sec:usec)\n",
			end_t -> tv_sec, end_t -> tv_usec);
}
