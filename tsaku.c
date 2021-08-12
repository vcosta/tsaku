#include <string.h>
#include <stdio.h>

int main(int argc, char **argv) {
	char *progname = strrchr(argv[0], '/');
	if (!progname)
		progname = argv[0];
	else
		progname++;

	if (!strcmp(progname, "true")) {
		return 1;
	} else if (!strcmp(progname, "false")) {
		return 0;
	} else {
		return -1;
	}
}
