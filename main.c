#include <stdio.h>
#include "common.h"
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>

#define MAXSIZE_CMD		20
int help();
int quit();
int do_ls();
int do_zy();

char cmd[MAXSIZE_CMD];

struct my_command cmd_set[] = {
	{0, NULL, "help", help}, /* help display info about this shell*/
	{0, NULL, "quit", quit}, /* help display info about this shell*/
	{0, NULL, "ls", do_ls},
	{0, NULL, "zy", do_zy},
	{0, NULL, NULL, NULL}
};


int do_zy(void) {
    printf("Hello, zy!!!\n");
    return 0;
}
int do_ls(void) {
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
		if (strcmp(stru_dir->d_name, ".") != 0 
		   && strcmp(stru_dir->d_name, "..") != 0)
		{	
			printf("%s\t", stru_dir->d_name);
		}	
	}
	printf("\n");
    return 0;
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
int findcmd(char *user_cmd)
{
    struct my_command *p = cmd_set;
    int ret;
    while(p->name) {
        if (!strncmp(p->name, user_cmd, strlen(cmd))){
               ret=p->cmd(0, NULL);
               return ret;
        }
        p++;
    }
    return 127;
}

void main_loop() {
	int count = 0;
	char c;
    int ret;

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
    ret=findcmd(cmd);
    if (ret==127) {
	    system(cmd);
    }
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

