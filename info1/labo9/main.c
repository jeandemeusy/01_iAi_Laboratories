#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NO_ERROR 0
#define BAD_CHAR 1
#define NOT_ENOUGH_ARGUMENTS 2
#define UNKNOWN_COMMAND 3
#define INVALID_ARGUMENT 4
#define EMPTY_STRING 5

#define VERSION "1.0.0"
#define OWNER "jean.demeusy@heig-vd.ch"

bool is_lower(char c) { return (c >= 'a' && c <= 'z'); }
bool is_upper(char c) { return (c >= 'A' && c <= 'Z'); }
bool is_number(char c) { return (c >= '0' && c <= '9'); }
bool is_letter(char c) { return (is_lower(c) + is_upper(c)); }
bool is_alphanum(char c) { return (is_letter(c) + is_number(c)); }
bool is_good(char c) { return is_alphanum(c) + ispunct(c) + isspace(c); }

void print_alphanum(char* txt)
{
    char* p_txt = txt;
    while (*p_txt != '\0') {
        if (is_alphanum(*p_txt)) printf("%c", *p_txt);
        p_txt++;
    }
}

void swap_char(char* c1, char* c2)
{
    *c1 ^= *c2;
    *c2 ^= *c1;
    *c1 ^= *c2;
}

void to_lower(char* txt)
{
    char* p_txt = txt;
    while (*p_txt != '\0') {
        if (is_upper(*p_txt)) *p_txt -= 'A' - 'a';
        p_txt++;
    }
}

void version(char app[]) { printf("%s version %s <%s>", app, VERSION, OWNER); }

int len(char* txt)
{
    char* p_txt = txt;

    while (*(p_txt++) != '\0')
        ;
    return p_txt - txt - 1;
}
int count(char* txt)
{
    int n_word = 0;
    char* p_txt = txt;
    bool prev_is_letter = false;

    while (*p_txt != '\0') {
        bool now_is_letter = is_alphanum(*p_txt);
        n_word += (!prev_is_letter && now_is_letter);
        prev_is_letter = now_is_letter;

        p_txt++;
    }

    return n_word;
}

int find(char c, char* txt)
{
    char* p_txt = txt;

    while (*p_txt != c && *p_txt != '\0') {
        p_txt++;
    }

    return (*p_txt != '\0') ? p_txt - txt : -1;
}

int bubble_string(char* txt)
{
    bool has_changed = false;
    char* p_txt = txt;

    while (*p_txt != '\0') {
        if (!is_good(*p_txt)) return BAD_CHAR;
        p_txt++;
    }

    do {
        has_changed = false;
        p_txt = txt;

        while (*(++p_txt) != '\0') {
            if (*(p_txt - 1) > *p_txt) {
                swap_char(p_txt - 1, p_txt);
                has_changed = true;
            }
        }

    } while (has_changed);

    return NO_ERROR;
}

int main(int argc, char* argv[])
{
    if (argc < 2) return NOT_ENOUGH_ARGUMENTS;

    if (!strcmp(argv[1], "--version")) {
        version(argv[0]);
    } else if (!strcmp(argv[1], "lower")) {
        if (argc < 3) return NOT_ENOUGH_ARGUMENTS;

        to_lower(argv[2]);
        printf("%s\n", argv[2]);
    } else if (!strcmp(argv[1], "count")) {
        if (argc < 3) return NOT_ENOUGH_ARGUMENTS;

        int n_words = count(argv[2]);
        printf("%d\n", n_words);
    } else if (!strcmp(argv[1], "find")) {
        if (argc < 4) return NOT_ENOUGH_ARGUMENTS;
        if (len(argv[2]) > 1) return INVALID_ARGUMENT;

        printf("%d\n", find(argv[2][0], argv[3]));
    } else if (!strcmp(argv[1], "bubble")) {
        if (argc < 3) return NOT_ENOUGH_ARGUMENTS;

        bubble_string(argv[2]);
        print_alphanum(argv[2]);
    } else {
        return UNKNOWN_COMMAND;
    }

    return NO_ERROR;
}