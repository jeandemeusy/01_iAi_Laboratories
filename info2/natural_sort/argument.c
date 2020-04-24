#include "argument.h"

option_type read_arguments(int argc, char *argv[]) {
    option_type options = {0};
	struct option long_opt[] = {{"alpha", no_argument, 0, 'a'},
								{"natural", no_argument, 0, 'n'},
								{"help", no_argument, 0, 'h'},
								{"count", no_argument, 0, 'c'},
								{0, 0, 0, 0}};

	switch (getopt_long(argc, argv, "anhc", long_opt, NULL)) {    
		case 'a':
			options.action = ALPHA;
			break;
		case 'n':
			options.action = NATURAL;
			break;
		case 'h':
			options.action = HELP;
			break;
		case 'c':
			options.action = COUNT;
			break;
		case -1:
			break;
		default:
			exit(EXIT_FAILURE);
	}

    return options;
}

int usage(char* app_name) {
	log_info("Usage: %s [option] [strings]...", app_name);
	log_info("\n%-7s %-20s\t%s","Option","Long option","Effect");
	log_info("%-7s %-20s\t%s","-h","--help","Displays this.");
	log_info("%-7s %-20s\t%s","-a","--alpha","Sorts according to ASCII table.");
	log_info("%-7s %-20s\t%s","-n","--natural","Sorts according to numbers in strings");
	log_info("%-7s %-20s\t%s","-c","--count","Displays number of strings.");

	return 0;
}