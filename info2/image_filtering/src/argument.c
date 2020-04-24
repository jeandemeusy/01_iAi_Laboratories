#include "argument.h"

option_type read_arguments(int argc, char *argv[]) {
    option_type options = {0};
	static struct option long_options[] = {{"adjust", no_argument, 0, 0},
										   {"help", no_argument, 0, 1},
										   {"edge", no_argument, 0, 'e'},
										   {"v_edge", no_argument, 0, 'v'},
										   {"h_edge", no_argument, 0, 'h'},
										   {"sharpen", no_argument, 0, 's'},
										   {"blur", no_argument, 0, 'b'},
										   {"resize",required_argument,0,'r'},
										   {0, 0, 0, 0}};

    while(true) {
		int c = getopt_long(argc, argv, "evhsbkhr:", long_options, NULL);
		if (c == -1) break;

        switch (c) {        
			case 'e':
				options.type = EDGE;
				break;
			case 'v':
				options.type = V_EDGE;
				break;
			case 'h':
				options.type = H_EDGE;
				break;
			case 's':
				options.type = SHARPEN;
				break;
			case 'b':
				options.type = BLUR;
				break;
			case 'r':
				options.resize = optarg;
				break;
            case '?':
				break;
			case 0:
				options.adjust = true;  
				break;
			case 1:
				usage(argv[0]);
				exit(EXIT_SUCCESS);
            default:
                log_err("Unkown error!");
                exit(EXIT_FAILURE);
        }
    }
	options.filter_size = 3;

    if (optind < argc)
	    options.input_filename = argv[optind++];
	else {
        log_err("Error: no input filename provided!");
        exit(EXIT_FAILURE);
    }

	if (optind < argc)
		options.output_filename = argv[optind];
	else {
		log_err("Error: no output filename provided!");
		exit(EXIT_FAILURE);
	}

    return options;
}

void usage(char* app_name) {
	log_info("Usage: %s <input_file> <output_file>  [options [value]] [flag]...", app_name);
	
	log_info("\n%-7s %-20s\tEffect",					"Option","Long option");
	log_info("%-7s %-20s\tCanny edge filter",			"-e","--edge");
	log_info("%-7s %-20s\tVertical Canny edge filter",	"-v","--v_edge");
	log_info("%-7s %-20s\tHorizontal Canny edge filter","-h","--h_edge");
	log_info("%-7s %-20s\tSharpening",					"-s","--sharpen");
	log_info("%-7s %-20s\t3x3 gaussian blur",			"-b","--blur");
	log_info("%-7s %-20s\tResize with specified dimensions (aaxbb) or ratio (a)" ,"-r","--resize <value>");

	log_info("\n%-27s\tEffect","Flag");
	log_info("%-27s\tSet intensity range to [0, 255]","--adjust");

}