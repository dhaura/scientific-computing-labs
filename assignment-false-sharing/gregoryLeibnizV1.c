#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double calculatePi(int terms) {
    double pi = 0.0;
    int i;

    for (i = 0; i < terms; i++) {
        int sign = (i % 2 == 0) ? 1 : -1;
        pi += sign * (4.0 / (2 * i + 1));
    }

    return pi;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./gregoryLeibnizV1 <number_of_terms>\n");
        return 1;
    }

    int terms = atoi(argv[1]);

    clock_t start_time, end_time;
    double total_time = 0.0;
    int iterations = 20;
    double average_time;

    for (int i = 0; i < iterations; i++) {
        start_time = clock();

        double pi = calculatePi(terms);

        end_time = clock();

        double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        total_time += elapsed_time;

        printf("Iteration %d: Pi = %.15f, Time = %.6f\n", i + 1, pi, elapsed_time);
    }

    average_time = total_time / iterations;

    printf("Average time elapsed for %d iterations: %.6f seconds\n", iterations, average_time);

    return 0;
}
