#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int solver(int a, int b, int c, double *sol1, double *sol2)
{
    // Calcul du déterminant
    int det = b * b - 4 * a * c;

    if (det >= 0)
    {
        *sol1 = (-b - sqrt(det)) / (2. * a);
        *sol2 = (-b + sqrt(det)) / (2. * a);
    }

    return (det >= 0) + (det > 0);
}

int show_solutions(double sol1, double sol2, int n)
{
    if (n == 0)
    {
        printf("Pas de solution\n");
    }
    else if (n == 1)
    {
        printf("Solution = %.1lf\n", sol1);
    }
    else if (n == 2)
    {
        printf("Solution 1 = %.1lf\n", sol1);
        printf("Solution 2 = %.1lf\n", sol2);
    }

    return (n == 0);
}

int main(int argc, char **argv)
{
    // Declaration des variables
    int a = 0, b = 0, c = 0;
    double sol1 = 0., sol2 = 0.;
    int n_sol = 0, retval = 0;

    // Saisies utilisateur
    printf("Entrer A : ");
    scanf("%d", &a);
    printf("Entrer B : ");
    scanf("%d", &b);
    printf("Entrer C : ");
    scanf("%d", &c);

    // Rappel des valeurs saisies
    printf("\n");
    printf("La valeur de A = %d\n", a);
    printf("La valeur de B = %d\n", b);
    printf("La valeur de C = %d\n", c);

    // Resolution de ax^2 + bx + c = 0
    n_sol = solver(a, b, c, &sol1, &sol2);
    retval = show_solutions(sol1, sol2, n_sol);

    return retval;
}