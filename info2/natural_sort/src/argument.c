#include "argument.h"

action_type read_arguments(int argc, char *argv[]) {
    action_type action;
	struct option long_opt[] = {{"alpha", no_argument, 0, 'a'},
								{"natural", no_argument, 0, 'n'},
								{"help", no_argument, 0, 'h'},
								{"count", no_argument, 0, 'c'},
								{0, 0, 0, 0}};

	switch (getopt_long(argc, argv, "anhc", long_opt, NULL)) {    
		case 'a':
			action = ALPHA;
			break;
		case 'n':
			action = NATURAL;
			break;
		case 'h':
			action = HELP;
			break;
		case 'c':
			action = COUNT;
			break;
		case -1:
			break;
		default:
			exit(EXIT_FAILURE);
	}

    return action;
}

int usage(char* app_name) {
	log_info("Usage: %s [option] [strings]...\n", app_name);
	log_info("%-7s %-14s\t%s","Option","Long option","Effect");
	log_info("%-7s %-14s\t%s","-h","--help","Displays this.");
	log_info("%-7s %-14s\t%s","-a","--alpha","Sorts according to ASCII table.");
	log_info("%-7s %-14s\t%s","-n","--natural","Sorts according to numbers in strings");
	log_info("%-7s %-14s\t%s","-c","--count","Displays number of strings.");

	return 0;
}