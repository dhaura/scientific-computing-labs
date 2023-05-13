/*

Pi calulation based Gregory Leibniz Series in a Sequential manner.

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

double calculatePi(int numTerms) {
    double pi = 0.0;
    int denominator = 1;
    int sign = 1;

    for (int i = 0; i < numTerms; i++) {
        double term = (double)sign / denominator;
        pi += term;
        denominator += 2;
        sign *= -1;
    }

    pi *= 4;
    return pi;
}

double getCurrentTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
}

double cal_avg(double arr[], int n) {
    double sum = 0.0;
    int i;

    for (i = 0; i < n; i++) {
        sum += arr[i];
    }

    return sum / n;
}

int main(int argc, char *argv[]) {
    int m = 20;  // Number of iterations
    double *time_records = (double *)malloc(m * sizeof(double));  // Array to store time values for multiple iterations
    double pi; // Store calculated Pi value

    if (argc != 2) {
        printf("Usage: ./gregoryLeibnizV1 <num_terms>\n");
        return 1;
    }

    int numTerms = atoi(argv[1]);
    if (numTerms <= 0) {
        printf("Number of iterations must be a positive integer.\n");
        return 1;
    }

    for(int j = 0; j < m; j++) {
        double startTime = getCurrentTime();
        pi = calculatePi(numTerms);
        double endTime = getCurrentTime();

        double elapsedTime = endTime - startTime;
        time_records[j] = elapsedTime;
        printf("Iteration: %d:\t time = %f s\n", (j+1), elapsedTime);
    }

    double avg_time = cal_avg(time_records, m);  // Calculate average time taken

    printf("\nApproximation of pi using %d number of terms: %.15f\n", numTerms, pi);
    printf("Average Time taken: %.6f seconds\n", avg_time);
    printf("---------------------------------------------------------\n\n");

    return 0;
}
