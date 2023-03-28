#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>


void matMulIJK( int n, float *A, float *B, float *C ) {
    int i,j,k;
    /* This is ijk loop order. */
    for( i = 0; i < n; i++ )
        for( j = 0; j < n; j++ )
            for( k = 0; k < n; k++ )
                C[i+j*n] += A[i+k*n]*B[k+j*n];
}

void matMulIKJ( int n, float *A, float *B, float *C ) {
    int i,j,k;
    /* This is ikj loop order. */
    for( i = 0; i < n; i++ )
        for( k = 0; k < n; k++ )
            for( j = 0; j < n; j++ )
                C[i+j*n] += A[i+k*n]*B[k+j*n];
}

void matMulJIK( int n, float *A, float *B, float *C ) {
    int i,j,k;
    /* This is jik loop order. */
    for( j = 0; j < n; j++ )
        for( i = 0; i < n; i++ )
            for( k = 0; k < n; k++ )
                C[i+j*n] += A[i+k*n]*B[k+j*n];
}

void matMulJKI( int n, float *A, float *B, float *C ) {
    int i,j,k;
    /* This is jki loop order. */
    for( j = 0; j < n; j++ )
        for( k = 0; k < n; k++ )
            for( i = 0; i < n; i++ )
                C[i+j*n] += A[i+k*n]*B[k+j*n];
}

void matMulKIJ( int n, float *A, float *B, float *C ) {
    int i,j,k;
    /* This is kij loop order. */
    for( k = 0; k < n; k++ )
        for( i = 0; i < n; i++ )
            for( j = 0; j < n; j++ )
                C[i+j*n] += A[i+k*n]*B[k+j*n];
}

void matMulKJI( int n, float *A, float *B, float *C ) {
    int i,j,k;
    /* This is kji loop order. */
    for( k = 0; k < n; k++ )
        for( j = 0; j < n; j++ )
            for( i = 0; i < n; i++ )
                C[i+j*n] += A[i+k*n]*B[k+j*n];
}

double cal_mean(double arr[], int n) {
    double sum = 0.0;
    int i;

    for (i = 0; i < n; i++) {
        sum += arr[i];
    }

    return sum / n;
}

double cal_variance(double arr[], int n) {
    double mean = cal_mean(arr, n);
    double variance = 0.0;
    int i;

    for (i = 0; i < n; i++) {
        variance += pow(arr[i] - mean, 2);
    }

    return variance / n;
}


int main( int argc, char **argv ) {
    int N = atoi(argv[1]);  // Size of the matrix will be N x N
    int i = 0;
    int m = atoi(argv[2]);  // Number of iterations need to be run for each order

    void (*matMulFunctions[])(int,float *,float *,float *) = {&matMulIJK, &matMulIKJ, &matMulJIK, &matMulJKI, &matMulKIJ, &matMulKJI};
    char *orders[] = {"ijk","ikj","jik","jki","kij","kji"};

    float *A = (float *)malloc(N*N * sizeof(float));
    float *B = (float *)malloc(N*N * sizeof(float));
    float *C = (float *)malloc(N*N * sizeof(float));

    struct timeval start, end;
    double *time_records = (double *)malloc(m * sizeof(double));  // Array to store time values for multiple iterations

    // Seed the random number generator with the current time
    srand(time(NULL));

    // Initilize matrices with random floating numbers
    for( i = 0; i < N*N; i++ ) A[i] = ((float)rand() / (float)RAND_MAX)*2-1;
    for( i = 0; i < N*N; i++ ) B[i] = ((float)rand() / (float)RAND_MAX)*2-1;
    for( i = 0; i < N*N; i++ ) C[i] = ((float)rand() / (float)RAND_MAX)*2-1;

    // Loop through each of the matrix multiplication orderings
    for( i = 0; i < 6; i++) {
        int j = 0;
        printf("Order: %s, n = %d\n\n", orders[i], N);

        for( j = 0; j < m; j++) {
            gettimeofday( &start, NULL );  // Record start time
            (*matMulFunctions[i])( N, A, B, C );  // Do matirx multiplication with the relevant order
            gettimeofday( &end, NULL );  // Record end time

            double seconds = (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);  // Calculate the time difference
            time_records[j] = seconds;
            printf("Iteration: %d:\t time = %f s\n", (j+1), seconds);
        }

        double avg_time = cal_mean(time_records, m);  // Calculate average time taken
        double variance_time = cal_variance(time_records, m);  // Calculate the variance

        printf("\n%s:\tn = %d, avg time = %f s, variance = %f s\n\n", orders[i], N, avg_time, variance_time);
        printf("---------------------------------------------------------\n\n");
    }

    free( time_records );
    free( A );
    free( B );
    free( C );

    printf("\n");

    return 0;
}
