#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>


char* trim_space(char *str) {
    char *end;

    while (isspace(*str)) {
        str = str + 1;
    }
    end = str + strlen(str) - 1;
    while (end > str && isspace(*end)) {
        end = end - 1;
    }
    *(end+1) = '\0';
    return str;
}

int main(void) {
    char *line = NULL;
    size_t len = 0;

    int last_key = 0;
    int max_val = INT_MIN;

    while(getline(&line, &len, stdin) != -1) {
        line = trim_space(line);

        int key = atoi(strtok(line, "\t"));
        int val = atoi(strtok(NULL, "\t"));

        if(last_key && last_key != key) {
            printf("%d\t%d\n",last_key,max_val);
            max_val = val;
        }
        else {
            max_val = (max_val > val) ? max_val:val;
        }
        
        last_key = key;
    }


    if (last_key) {
        printf("%d\t%d\n",last_key,max_val);
    }

}