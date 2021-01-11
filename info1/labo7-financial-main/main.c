#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// clang-format off
#define REPEAT(A, N) { for (int i = 0; i < (N); i++) printf(A); }
#define DIGITS(A) (int)(1 + log10(A))
#define MAX(A,S) ((A > strlen(S))? A : strlen(S))
// clang-format on

void empty_buffer(void) { while (getchar() != '\n'); }

double read_double(char* str) {
    bool correct_input = false;
    double value = 0.;

    do {
        printf("%s",str);
        int ret = scanf("%lf", &value);
        empty_buffer();

        correct_input =(value >= 0 && ret == 1);
    } while(!correct_input);

    return value;
}


void calcul_interet_annuels() {
    double capital = read_double("Capital: ");
    double rate = read_double("Interests: ");
    double interests = capital * rate/100;

    int interests_len = MAX(DIGITS(interests) + 3, "Interet");
    int rate_len = MAX(DIGITS(rate) + 3, "Taux");
    int capital_len = MAX(DIGITS(capital) + 3, "Capital");

    printf("┌─");
    REPEAT("─",capital_len);
    printf("─┬─");
    REPEAT("─",rate_len);
    printf("─┬─");
    REPEAT("─",interests_len);
    printf("─┐\n");

    printf("│ %-*s │ %-*s │ %-*s │\n",capital_len,"Capital",
                                      rate_len,"Taux",
                                      interests_len,"Interet");
    printf("├─");
    REPEAT("─",capital_len);
    printf("─┼─");
    REPEAT("─",rate_len);
    printf("─┼─");
    REPEAT("─",interests_len);
    printf("─┤\n");

    printf("│ %*.2lf │ %*.2lf │ %*.2lf │\n",capital_len,capital,
                                            rate_len, rate,
                                            interests_len, interests);
    printf("└─");
    REPEAT("─",capital_len);
    printf("─┴─");
    REPEAT("─",rate_len);
    printf("─┴─");
    REPEAT("─",interests_len);
    printf("─┘\n");
}

void conversion_euro_chf() {
    const double EUR_TO_CHF = 1.2;

    double amount_euro = read_double("Valeur en euro: ");
    double amount_chf = amount_euro * EUR_TO_CHF;

    printf("%.2lf [EUR] => %.2lf [CHF]",amount_euro, amount_chf);
}

void conversion_chf_euro() {
    const double CHF_TO_EUR = 1.0/1.2;

    double amount_chf = read_double("Valeur en chf: ");
    double amount_euro = amount_chf * CHF_TO_EUR;

    printf("%.2lf [CHF] => %.2lf [EUR]", amount_chf, amount_euro);
}

int menu()
{
    int selection = 0;
    bool correct_input = false;

    puts("====== Menu ======");
    puts("1 - Interets annuels");
    puts("2 - Conversion EUR -> CHF");
    puts("3 - Conversion CHF -> EUR");
    puts("0 - Quitter");

    do {
        printf("User input: ");
        int ret = scanf("%d",&selection);
        empty_buffer();

        correct_input = (selection >= 0 && selection <= 3 && ret == 1);
    } while (!correct_input);

    return selection;
}

int main(int argc, char* argv[])
{
    switch(menu()) {
        case 1: calcul_interet_annuels(); break;
        case 2: conversion_euro_chf(); break;
        case 3: conversion_chf_euro(); break;
        default: break;
    }

    return 0;
}

// \\eistore1\profs\TMZ\info\info1\labos\labo7
// https://github.com/tony-maulaz/labo7-financial