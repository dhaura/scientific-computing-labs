#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define MAX_THREADS 128

int n;
int num_threads;
int **A, **B, **C;

void *matrix_mult(void *arg) {
    int thread_id = *(int *) arg;
    int start_row = thread_id * (n / num_threads);
    int end_row = start_row + (n / num_threads);

    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./matrix_mult <matrix_dimension>\n");
        exit(1);
    }

    n = atoi(argv[1]);
    if (n < 1) {
        printf("Error: Matrix dimension must be positive.\n");
        exit(1);
    }

    num_threads = MAX_THREADS;
    if (n < num_threads) {
        num_threads = n;
    }

    // Allocate memory for matrices A, B, and C
    A = (int **) malloc(n * sizeof(int *));
    B = (int **) malloc(n * sizeof(int *));
    C = (int **) malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        A[i] = (int *) malloc(n * sizeof(int));
        B[i] = (int *) malloc(n * sizeof(int));
        C[i] = (int *) malloc(n * sizeof(int));
    }

    // Initialize matrices A and B with random values
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }

    // Create threads and perform matrix multiplication
    pthread_t threads[num_threads];
    int thread_ids[num_threads];
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    for (int i = 0; i < num_threads; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, matrix_mult, &thread_ids[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    gettimeofday(&end_time, NULL);
    double elapsed_time = (double) (end_time.tv_sec - start_time.tv_sec)
        + (double) (end_time.tv_usec - start_time.tv_usec) / 1000000.0;

    // Print the result matrix C
    /*
    printf("Matrix C:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    */

    printf("Matrix multiplication with %d threads took %.6f seconds.\n", num_threads, elapsed_time);

    // Free memory
    for (int i = 0; i < n; i++) {
        free(A[i])
        free(B[i])
        free(C[i])
    }
}
