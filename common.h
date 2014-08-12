#ifndef		__COMMON_H
#define		__COMMON_H

struct my_command {

	int argc;
	char **argv;
	char *name;
	int (*cmd) (int ,char **);
};

#endif
