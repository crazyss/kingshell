#include <stdio.h>
#include "common.h"
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>

#define MAXSIZE_CMD		20
int help();
int quit();
int do_ls();

char cmd[MAXSIZE_CMD];

struct my_command cmd_set[] = {

	{NULL, NULL, "help", help}, /* help display info about this shell*/
	{NULL, NULL, "quit", quit}, /* help display info about this shell*/
	{NULL, NULL, "ls", do_ls},
	{NULL, NULL, NULL, NULL}
};


int do_ls() {
	int fd;	
	DIR *dir;
	struct dirent *stru_dir;
	if ((fd = open("/", O_RDONLY)) < 0) {
		perror("opening a dir ");
	}

	if ( (dir = fdopendir(fd)) ==  NULL) {
		perror("open a dir by fd");
	}


	while((stru_dir = readdir(dir)) != NULL ) {
		int i = 0 ;
		if (strcmp(stru_dir->d_name, ".") != 0 
		   && strcmp(stru_dir->d_name, "..") != 0)
		{	
			printf("%s\t", stru_dir->d_name);
		}	
	}
	printf("\n");
}



int quit() {

	exit(-1);

}
int help() {

	printf("This is a program be used for teach \n\
You can type some command example: \n\
cd , ls , quit and so on \n");
	return 0;

}

int main(int argc,char **argv) {

	while(1) {
		main_loop();
	}
	/*
	 * option 
	 */	
	//	getopt();
	
}

void main_loop() {

	int count = 0;
	char c;

	printf("kingshell$ ");
	fflush(stdout);
	while ((c=getchar())!='\n' && count < MAXSIZE_CMD) {
		cmd[count++] = c;
	}
	if ( count > MAXSIZE_CMD) {
		perror("command is too long");
		exit(-1);
	}
	cmd[count] = '\0'; //end of string(cmd)
	run(cmd);
}
