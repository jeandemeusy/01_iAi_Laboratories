/**
 * Decode tire code information.
 *
 * Convension : variables containing distances/lengths/size are by default in
 * millimeters. If the unit is different than millimeters, its specified in
 * the name of the variable.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// clang-format off
#define REPEAT(A, N)    { for (int i = 0; i < (N); i++) printf(A); }
#define INCH_TO_MM      (25.4)
#define MM_TO_M         (1.e-3)
#define MM_TO_CM        (1.e-1)
#define KM_TO_MM        (1.e+6)
// clang-format on

typedef enum {
    E_NO_ERROR = 0,
    E_BAD_TIRE_TEXT,
    E_NOT_ENOUGH_ARGUMENTS,
    E_TOO_MANY_ARGUMENTS,
    E_BAD_DISTANCE
} error_code;

void usage(char* name) { printf("Usage for %s\n", name); }
void version(char* name) { printf("Version %s\n", "0.1"); }

int count_max_digit(double* values, const int n_values)
{
    int max_digit = 0;

    for (int i = 0, count = 0; i < n_values; i++, count = 0) {
        while ((int)values[i] != 0) {
            values[i] /= 10;
            count++;
        }

        max_digit = (count > max_digit) ? count : max_digit;
    }

    return max_digit;
}

int read_code(int argc, char* argv[], int* diameter, int* width, int* ratio,
              double* distance)
{
    int ret = sscanf(argv[1], "P%d/%dR%d", width, ratio, diameter);

    ret -= (*width == 0) + (*ratio <= 0 || *ratio >= 100) + (*diameter == 0);

    return ret;
}

void display(const double wheel_diameter, const double wheel_perimeter,
             const double revolutions_per_km, const double revolutions)
{
    double wheel_diameter_cm = wheel_diameter * MM_TO_CM;
    double wheel_perimeter_m = wheel_perimeter * MM_TO_M;

    double values[] = {wheel_diameter_cm, wheel_perimeter_m, revolutions_per_km,
                       revolutions};

    const int max_length = count_max_digit(values, 4) + 8;

    printf("┌─────────────┬");
    REPEAT("─", max_length);
    printf("┐\n");

    printf("│ Diameter    │ %*.2lf%s│\n", max_length - 1 - (int)strlen(" cm "),
           wheel_diameter_cm, " cm ");
    printf("│ Perimeter   │ %*.2lf%s│\n", max_length - 1 - (int)strlen(" m  "),
           wheel_perimeter_m, " m  ");
    printf("│ Revs/km     │ %*.1lf%s│\n", max_length - 1 - (int)strlen("     "),
           revolutions_per_km, "     ");

    if (revolutions >= 0) {
        printf("├─────────────┼");
        REPEAT("─", max_length);
        printf("┤\n");
        printf("│ Revolutions │ %*.2lf%s│\n",
               max_length - 1 - (int)strlen("    "), revolutions, "    ");
    }

    printf("└─────────────┴");
    REPEAT("─", max_length);
    printf("┘\n");
}

void conversion(const int rim_diameter_inch, const int tire_width,
                const int ratio, const double distance_km,
                double* wheel_diameter, double* wheel_perimeter,
                double* revolutions_per_km, double* revolutions)
{
    double rim_diameter = rim_diameter_inch * INCH_TO_MM;
    double tire_sidewall = tire_width * (ratio / 100.);

    *wheel_diameter = rim_diameter + 2 * tire_sidewall;
    *wheel_perimeter = *wheel_diameter * M_PI;

    *revolutions_per_km = 1. * KM_TO_MM / *wheel_perimeter;
    *revolutions = *revolutions_per_km * distance_km;
}

int main(int argc, char* argv[])
{
    // ARGUMENTS CHECK
    if (argc < 2) {
        return E_NOT_ENOUGH_ARGUMENTS;
    }
    if (argc > 3) {
        return E_TOO_MANY_ARGUMENTS;
    }

    if (!strcmp(argv[1], "--help")) {
        usage(argv[0]);
        return E_NO_ERROR;
    }
    if (!strcmp(argv[1], "--version")) {
        version(argv[0]);
        return E_NO_ERROR;
    }

    // TIRE CODE READING
    int rim_diameter_inch = 0;
    int tire_width = 0;
    int ratio = 0;
    double distance_km = -1.;

    int ret = read_code(argc, argv, &rim_diameter_inch, &tire_width, &ratio,
                        &distance_km);
    if (ret != 3) {
        return E_BAD_TIRE_TEXT;
    }

    if (argc == 3) {
        distance_km = atof(argv[2]);
        if (distance_km <= 0) {
            return E_BAD_DISTANCE;
        }
    }

    // VALUES CONVERSIONS
    double wheel_diameter = 0.;
    double wheel_perimeter = 0.;
    double revolutions_per_km = 0.;
    double revolutions = 0.;

    conversion(rim_diameter_inch, tire_width, ratio, distance_km,
               &wheel_diameter, &wheel_perimeter, &revolutions_per_km,
               &revolutions);

    // DISPLAY TABLE
    display(wheel_diameter, wheel_perimeter, revolutions_per_km, revolutions);

    return E_NO_ERROR;
}