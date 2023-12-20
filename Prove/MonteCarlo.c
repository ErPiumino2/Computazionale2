#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <muparser/muParser.h>

double evaluate_function(double x, double y, mu::Parser &parser) {
    parser.DefineVar("x", &x);
    parser.DefineVar("y", &y);

    return parser.Eval();
}

double monte_carlo_integration(int num_samples, double x_lower, double x_upper, double y_lower, double y_upper, mu::Parser &parser) {
    srand(time(NULL));

    double integral = 0.0;

    for (int i = 0; i < num_samples; ++i) {
        double x = ((double)rand() / RAND_MAX) * (x_upper - x_lower) + x_lower;
        double y = ((double)rand() / RAND_MAX) * (y_upper - y_lower) + y_lower;

        integral += evaluate_function(x, y, parser);
    }

    double area = (x_upper - x_lower) * (y_upper - y_lower);
    double result = (integral / num_samples) * area;

    return result;
}

int main() {
    mu::Parser parser;
    char function_str[100];

    // Chiedi all'utente di inserire la funzione
    printf("Inserisci la funzione (utilizza 'x' e 'y' come variabili): ");
    fgets(function_str, sizeof(function_str), stdin);

    // Rimuovi il newline dalla stringa letta
    function_str[strcspn(function_str, "\n")] = 0;

    // Imposta la funzione nel parser
    parser.SetExpr(function_str);

    double x_lower = 0.0, x_upper = 1.0;
    double y_lower = 0.0, y_upper = 2.0;
    int num_samples = 100000;

    double result = monte_carlo_integration(num_samples, x_lower, x_upper, y_lower, y_upper, parser);

    printf("Risultato dell'integrale con Montecarlo: %f\n", result);

    return 0;
}