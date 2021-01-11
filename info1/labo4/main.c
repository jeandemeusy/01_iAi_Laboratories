#include <stdio.h>
#include <stdlib.h>

#define N_ZONE 3
#define EUCLID_2(X, Y) ((X) * (X) + (Y) * (Y))

void usage(char *app)
{
    printf("Usage for %s [param] <val1> <val2>:\n", app);
    printf("\t - [param]\t1: show help\n");
    printf("\t\t\t2: get score\n");
    printf("\t - <val1>\tx coordinate (ignored if [param] is 1).\n");
    printf("\t - <val2>\ty coordinate (ignored if [param] is 1).\n");
}

int get_score(double x, double y)
{
    double diameter[N_ZONE] = {1, 5, 10};
    int points[N_ZONE + 1] = {100, 25, 5, 0};
    int zone = 0;

    while (zone < N_ZONE)
    {
        if (EUCLID_2(x, y) * 4 <= diameter[zone] * diameter[zone])
            break;
        zone++;
    }

    return points[zone];
}

int main(int argc, char **argv)
{
    char *param = (argc > 1) ? argv[1] : "";

    switch (*param)
    {
    default:
        printf("Error: missing param. See usage.\n");
    case '1':
        usage(argv[0]);
        break;
    case '2':
        if (argc < 4)
        {
            printf("Error: missing coordinates. See usage.\n");
            usage(argv[0]);
        }
        else
        {
            printf("\nNombre de points:%4d\n", get_score(atof(argv[2]), atof(argv[3])));
        }
        break;
    }

    return 0;
}
