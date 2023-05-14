#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX_THREADS 1024

typedef struct {
    int terms;
    int thread_count;
    double* sum;
    int id;
} ThreadArgs;

void* calculatePi(void* arg) {
    ThreadArgs* thread_args = (ThreadArgs*)arg;

    int terms = thread_args->terms;
    int thread_count = thread_args->thread_count;
    double* sum = thread_args->sum;
    int id = thread_args->id;

    int i;
    double pi = 0.0;

    for (i = id; i < terms; i += thread_count) {
        int sign = (i % 2 == 0) ? 1 : -1;
        double term = sign * (4.0 / (2 * i + 1));
        pi += term;
    }

    sum[id] = pi;

    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: ./pi_calc <number_of_terms> <number_of_threads>\n");
        return 1;
    }

    int terms = atoi(argv[1]);
    int thread_count = atoi(argv[2]);
    if (thread_count > MAX_THREADS)
        thread_count = MAX_THREADS;

    clock_t start_time, end_time;
    double total_time = 0.0;
    int iterations = 10;
    double average_time;
    double sum[MAX_THREADS] = {0.0};

    for (int i = 0; i < iterations; i++) {
        start_time = clock();

        pthread_t threads[MAX_THREADS];
        ThreadArgs thread_args[MAX_THREADS];

        for (int j = 0; j < thread_count; j++) {
            thread_args[j].terms = terms;
            thread_args[j].thread_count = thread_count;
            thread_args[j].sum = sum;
            thread_args[j].id = j;
            pthread_create(&threads[j], NULL, calculatePi, (void*)&thread_args[j]);
        }

        for (int j = 0; j < thread_count; j++) {
            pthread_join(threads[j], NULL);
        }

        double pi = 0.0;
        for (int j = 0; j < thread_count; j++) {
            pi += sum[j];
        }

        end_time = clock();
        
        double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        total_time += elapsed_time;

        printf("Iteration %d: Pi = %.15f, Time = %.6f\n", i + 1, pi, elapsed_time);
    }

    average_time = total_time / iterations;

    printf("%d threads: Average time elapsed for %d iterations: %.6f seconds\n", thread_count, iterations, average_time);

    return 0;
}
