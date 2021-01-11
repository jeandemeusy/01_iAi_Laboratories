#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define DIGITS(A) (int)(1 + log10(A))
#define REPEAT(A, N) { for (int i = 0; i < (N); i++) printf("%s",A); }
#define VERSION "0.1.0"

void empty_buffer(void) { 
    int c;  
    do {
        c = getchar();
     } while(c != EOF && c != '\n'); 
}

int is_number(char* str) {
    if (*str >= '0' && *str <= '9')
        return true;

    if (*str == '-' || *str == '+') {
        return is_number((str + sizeof(*str)));
    }

    return false;
}

int is_enter(char* str) {
    return (*str == -1 || *str == 0|| *str == '\177');
}

int read_int(char* text, int min_val, int max_val, int default_val) {
    int choice = min_val-1;
    char choice_str[3] = { 0 };
    bool correct = false;
    
    do {
        printf("%s ",text);

        if (scanf("%99[^\n]%*c", choice_str)) {
            if (is_number(choice_str))
                choice = atoi(choice_str);
            else {
                printf("Wrong input : must be an number\n");
                choice = min_val-1;
            }
        } else if (is_enter(choice_str)) {
            if (default_val != -1) {
                choice = default_val;
            } else {
                choice = min_val-1;
                printf("Wrong input : need to provide a number\n");
            }
            empty_buffer();
        }
        sprintf(choice_str,"\177\177");
        correct = (choice >= min_val && choice <= max_val);
    } while (!correct);

    printf("\n");
    
    return choice;
}

char read_char(char* text) {
    char choice;
    bool correct = false;

    do {
        printf("%s ",text);
        scanf("%c",&choice);
        empty_buffer();

        correct = (choice == 'y' || choice == 'n');        
    } while (!correct);

    return choice;
}

void table_line(char* line_char, int max_value, int size) {
   for (int i = 0; i < max_value; i++) {
        REPEAT(line_char,size+2);
        printf("+");
    }
    REPEAT("-",size+2);
    printf("\n");
}

void table_numbers(char* text,int line, int max_value, int size) {
    printf(" %*s ",size,text);
    for (int i = 1; i <= max_value; i++) {
        printf("| %*d ", size, i*line);
    }
    printf("\n");
}

void table() {
    do {
        int max_value = read_int("Livret le plus élevé ? (1..15) [12]:",1,15,12);
        int max_length = DIGITS(max_value*max_value);
        char line_name[3];

        table_numbers("X",1,max_value,max_length);

        for (int i = 1; i <= max_value; i++) {
            sprintf(line_name,"%d",i);
            table_line("-",max_value,max_length);
            table_numbers(line_name,i,max_value,max_length);
        }
        printf("\n");

    } while(read_char("Voulez-vous recommencer [y/n] ? :") == 'y');

    return ;
}

void version() {
    printf("Version %s Copyright(c) "
           "HEIG-VD J.Demeusy <jean.demeusy@heig-vd.ch>\n",VERSION);
}

void help() {
    printf("Ce programme affiche les tables de multiplication "
           "pour mieux vous aider à les apprendre.\n");
}

int menu()
{
    puts("\nVeuillez choisir une option :\n");
    puts("\t1. Table de multiplication");
    puts("\t2. Version");
    puts("\t3. Aide");
    puts("\t0. Quitter");
    
    return read_int(">",0,3,-1);

}
int main(int argc, char* argv[]) {

    int menu_choice = 0;

    do {
        menu_choice = menu();
    
        switch(menu_choice) {
            case 1:
                table();
                break;
            case 2: 
                version();
                break;
            case 3:
                help();
                break;
            case 0: 
            default: break;
        }
    } while(menu_choice != 0);

    return 0;
}