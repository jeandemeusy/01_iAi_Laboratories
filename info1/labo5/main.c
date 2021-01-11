#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_STR_LENGTH (20)
#define EXPECTED_INPUTS (6)
#define ITEMS_ON_QUOTE (6)

typedef enum
{
    E_NO_ERROR,
    E_TOO_FEW_ARGUMENTS,
    E_TOO_MANY_ARGUMENTS,
    E_INCORRECT_ARGUMENT = 4
} error_code;

typedef enum
{
    PCB_CAT_1 = 12,
    PCB_CAT_2 = 10,
    LAYERS_PER_CM2_LAYER = 5,
    GLAZE_PER_CM2 = 1,
    DIODE_CAT_1 = 75,
    DIODE_CAT_2 = 70,
    DIODE_CAT_3 = 60,
    CAPACITOR_CAT_1 = 100,
    CAPACITOR_CAT_2 = 80,
    RESISTOR_PER_PACK = 100
} prices;

typedef enum
{
    PCB_THRES_1 = 200,
    DIODE_THRES_1 = 10,
    DIODE_THRES_2 = 20,
    CAPACITOR_THRES_1 = 10,
    RESISTOR_PACK_SIZE = 10
} ranges;

typedef struct
{
    char name[MAX_STR_LENGTH];
    double quantity;
    double unit_price;
    double total_price;
} list_item;

void usage(char *name)
{
    printf("Usage for %s :\n", name);
    printf("\t %s [<length[mm]> <width[mm]> <n_layers> <n_diode> <n_capa> <n_resis>]\n", name);
}

void display_order(double params[])
{
    printf("%-20s : %.0lf\n", "Largeur du CI (cm)", params[0]);
    printf("%-20s : %.0lf\n", "Longueur du CI (cm)", params[1]);
    printf("%-20s : %.0lf\n", "Couche (s)", params[2]);
    printf("%-20s : %.0lf\n", "Nbre de diodes", params[3]);
    printf("%-20s : %.0lf\n", "Nbre condensateurs", params[4]);
    printf("%-20s : %.0lf\n", "Nbre de resistances", params[5]);
}

void display_quote(list_item items[], double total_price, double tax_rate)
{
    char *format = "| %-16s | %8.0lf | %.2lf | %6.2lf |\n";

    printf("+---------------------------------------------+\n");
    printf("|      ITEM        | QUANTITE |  PU  |   PT   |\n");
    printf("+------------------+----------+------+--------+\n");
    for (int i = 0; i < ITEMS_ON_QUOTE; i++)
    {
        list_item u = items[i];
        printf(format, u.name, u.quantity, u.unit_price, u.total_price);
    }
    printf("+------------------------------------+--------+\n");
    printf("| %34s | %6.2lf |\n", "TOTAL HT", total_price);
    printf("| %34s | %6.2lf |\n", "TVA", total_price * tax_rate);
    printf("| %34s | %6.2lf |\n", "TOTAL TTC", total_price * (1 + tax_rate));
    printf("+---------------------------------------------+\n");
}

void get_prices(double param[], list_item items[], double *total)
{
    // SURFACE
    sprintf(items[0].name, "CI (cm2)");
    items[0].quantity = param[0] * param[1];
    if (items[0].quantity < PCB_THRES_1)
        items[0].unit_price = PCB_CAT_1;
    else
        items[0].unit_price = PCB_CAT_2;

    // LAYER
    sprintf(items[1].name, "COUCHE (S)");
    items[1].quantity = param[2];
    items[1].unit_price = LAYERS_PER_CM2_LAYER * items[0].quantity;

    // GLAZE
    sprintf(items[2].name, "VERNIS");
    items[2].quantity = 2 * items[0].quantity;
    items[2].unit_price = GLAZE_PER_CM2;

    // DIODES
    sprintf(items[3].name, "DIODE");
    items[3].quantity = param[3];
    if (items[3].quantity < DIODE_THRES_1)
        items[3].unit_price = DIODE_CAT_1;
    else if (items[3].quantity < DIODE_THRES_2)
        items[3].unit_price = DIODE_CAT_2;
    else
        items[3].unit_price = DIODE_CAT_3;

    // CAPACITOR
    sprintf(items[4].name, "CONDENSATEUR");
    items[4].quantity = param[4];
    if (items[4].quantity < CAPACITOR_THRES_1)
        items[4].unit_price = CAPACITOR_CAT_1;
    else
        items[4].unit_price = CAPACITOR_CAT_2;

    // RESISTOR
    sprintf(items[5].name, "RESISTANCE (x%d)", RESISTOR_PACK_SIZE);
    items[5].quantity = (int)(param[5] + RESISTOR_PACK_SIZE - 1) / RESISTOR_PACK_SIZE;
    items[5].unit_price = RESISTOR_PER_PACK;

    // PT AND TOTAL HT
    *total = 0.;
    for (int i = 0; i < ITEMS_ON_QUOTE; *total += items[i++].total_price)
    {
        items[i].unit_price /= 100.;
        items[i].total_price = items[i].quantity * items[i].unit_price;
    }
}

int check_input(char *argv[])
{
    return (atof(argv[1]) > 0 && atof(argv[2]) > 0 && atof(argv[3]) > 0 &&
            atof(argv[4]) >= 0 && atof(argv[5]) >= 0 && atof(argv[6]) >= 0);
}

int main(int argc, char *argv[])
{
    // HELP DISPLAY
    if (argc == 1)
        usage(argv[0]);

    // NUMBER OF INPUT ARGUMENTS CHECK
    if (argc > EXPECTED_INPUTS + 1)
        return E_TOO_MANY_ARGUMENTS;

    if (argc < EXPECTED_INPUTS + 1)
        return E_TOO_FEW_ARGUMENTS;

    if (check_input(argv) == 0)
        return E_INCORRECT_ARGUMENT;

    // PARAMETER CONVERSION (str -> double)
    double params[EXPECTED_INPUTS] = {0};
    for (int i = 0; i < EXPECTED_INPUTS; i++)
        params[i] = atof(argv[i + 1]);
    params[0] /= 10.;
    params[1] /= 10.;

    // PRICE COMPUTATION AND DISPLAY
    list_item items[ITEMS_ON_QUOTE];
    double tax_rate = .08;
    double total_price = 0.;

    get_prices(params, items, &total_price);
    display_order(params);
    display_quote(items, total_price, tax_rate);

    return E_NO_ERROR;
}
