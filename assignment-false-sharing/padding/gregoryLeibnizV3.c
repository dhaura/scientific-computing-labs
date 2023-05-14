/*

Pi calulation based Gregory Leibniz Series using Pthreads without False Sharing.

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define CACHE_LINE_SIZE 64

typedef struct {
    int start;
    int end;
    double sum;
    char padding[CACHE_LINE_SIZE - sizeof(int) - sizeof(int) - sizeof(double)];
} ThreadData;

void* calculatePartialSum(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    double sum = 0.0;
    int denominator;
    int sign;

    for (int i = data->start; i < data->end; i++) {
        denominator = 1 + 2 * i;
        sign = (i % 2 == 0) ? 1 : -1;
        sum += (double)sign / denominator;
    }

    data->sum = sum;
    return NULL;
}

double calculatePi(int numTerms, int numThreads) {
    pthread_t* threads = (pthread_t*)malloc(numThreads * sizeof(pthread_t));
    ThreadData* threadData = (ThreadData*)malloc(numThreads * sizeof(ThreadData));
    double pi = 0.0;
    int iterationsPerThread = numTerms / numThreads;

    for (int i = 0; i < numThreads; i++) {
        threadData[i].start = i * iterationsPerThread;
        threadData[i].end = (i + 1) * iterationsPerThread;
        pthread_create(&threads[i], NULL, calculatePartialSum, &threadData[i]);
    }

    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
        pi += threadData[i].sum;
    }

    free(threads);
    free(threadData);

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

int main(int argc, char* argv[]) {
    int m = 20;  // Number of iterations
    double *time_records = (double *)malloc(m * sizeof(double));  // Array to store time values for multiple iterations
    double pi; // Store calculated Pi value

    if (argc != 3) {
        printf("Usage: ./gregoryLeibnizV3 <num_terms> <num_threads>\n");
        return 1;
    }

    int numTerms = atoi(argv[1]);
    int numThreads = atoi(argv[2]);

    if (numTerms <= 0 || numThreads <= 0) {
        printf("Iterations and number of threads must be positive integers.\n");
        return 1;
    }

        for(int j = 0; j < m; j++) {
        double startTime = getCurrentTime();
        pi = calculatePi(numTerms, numThreads);
        double endTime = getCurrentTime();

        double elapsedTime = endTime - startTime;
        time_records[j] = elapsedTime;
        printf("Iteration: %d:\t time = %f s\n", (j+1), elapsedTime);
    }

    double avg_time = cal_avg(time_records, m);  // Calculate average time taken

    printf("\nApproximation of pi using %d number of terms and %d number of threads: %.15f\n", numTerms, numThreads, pi);
    printf("Average Time taken: %.6f seconds\n", avg_time);
    printf("---------------------------------------------------------\n\n");

    return 0;
}
