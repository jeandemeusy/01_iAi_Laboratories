#include "natural_sort.h"

int main(int argc, char* argv[]) {
    action_type action = read_arguments(argc, argv);
	int return_code = 0;

	char **input_str = (char**)malloc((argc-2) * sizeof(char*));
	for (int k = 2; k < argc; k++) {
		input_str[k-2] = (char*)malloc(NAME_MAX_SIZE * sizeof(char));
		strcpy(input_str[k-2], argv[k]);
	}
		
	switch(action) {
		case HELP:
			return_code = usage(argv[0]);
			break;
		case ALPHA:
		case NATURAL:
			return_code = sort_names(argc-2, input_str, action);
			print_names(argc-2, input_str);
			break;
		case COUNT:
			printf("count: %d\n", argc-2);
			return_code = argc-2;
			break;
		default:
			usage(argv[0]);
			return_code = 254;
			break;
	}

	for (int k = 0; k < argc-2; k++)
		free(input_str[k]);
	free(input_str);

	return return_code;
}


int comp_alpha(const void* str1, const void* str2) {
    return strcmp(*(const char**)str1, *(const char**)str2); 
}

int comp_num(const void* str1, const void* str2) {
	char* char1 = *(char**)str1;
	char* char2 = *(char**)str2;
	int num1, num2;

	while((*char1 != '\0') && (*char2 != '\0')) {
		while(*char1 == *char2 && 
			 ('0' < *char1 || *char1 > '9') &&
			 (*char1 != '\0') && (*char2 != '\0')) {
			char1++;
			char2++;
		}

		num1 = 0;
		while('0' <= *char1 && *char1 <= '9')
			num1 = num1 * 10 + *(char1++) - '0';

		num2 = 0;
		while('0' <= *char2 && *char2 <= '9')
			num2 = num2 * 10 + *(char2++) - '0';

		if (num1 ^ num2)
			return num1 - num2;

		if (!(num1 | num2))
			return strcmp(*(char**)str1, *(char**)str2); 
	}

	return 0;
}

int sort_names(const uint32_t num_names, char* names[], action_type action) {
	if (action == ALPHA)
    	qsort(names, num_names, sizeof(const char*), comp_alpha);
	else if (action == NATURAL)
		qsort(names, num_names, sizeof(const char*), comp_num);
	return num_names ? 0:253;
}

void print_names(const uint32_t num_names, char* names[]) {
	for (int k = 0; k < num_names; k++)
		printf("%s%s", names[k], (k+1 < num_names)?", ":".\n");
}