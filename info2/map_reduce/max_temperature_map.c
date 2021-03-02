#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
    ssize_t lineSize = 0;

    char year[5];
    char temp[6];
    int q = 0;
    year[4] = '\0';
    temp[5] = '\0';

    while(getline(&line, &len, stdin) != -1) {
        line = trim_space(line);

        memcpy(year, &line[15], 4);
        memcpy(temp, &line[87], 5);
        int q = line[92]-'0';

        if(strcmp(temp,"+9999") && (q==0 || q==1 || q==4 || q==5 || q==9)) {
            printf("%s\t%s\n", year, temp);
        }
    }

    return 0;
}