#include <stdio.h>
#include <stdlib.h>
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


int main( int argc, char **argv ) {
    int N = atoi(argv[1]);
    int i = 0;

    void (*matMulFunctions[])(int,float *,float *,float *) = {&matMulIJK, &matMulIKJ, &matMulJIK, &matMulJKI, &matMulKIJ, &matMulKJI};
    char *orders[] = {"ijk","ikj","jik","jki","kij","kji"};

    float *A = (float *)malloc( N*N * sizeof(float));
    float *B = (float *)malloc( N*N * sizeof(float));
    float *C = (float *)malloc( N*N * sizeof(float));

    struct timeval start, end;

    // Seed the random number generator with the current time
    srand(time(NULL));

    // Initilize matrices with random floating numbers
    for( i = 0; i < N*N; i++ ) A[i] = ((float)rand() / (float)RAND_MAX)*2-1;
    for( i = 0; i < N*N; i++ ) B[i] = ((float)rand() / (float)RAND_MAX)*2-1;
    for( i = 0; i < N*N; i++ ) C[i] = ((float)rand() / (float)RAND_MAX)*2-1;

    for( i = 0; i < 6; i++) {
        // Do matirx multiplication with the relevant order
        gettimeofday( &start, NULL );
        (*matMulFunctions[i])( N, A, B, C );
        gettimeofday( &end, NULL );

        double seconds = (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
        printf("%s:\tn = %d, time = %f s\n", orders[i], N, seconds);
    }

    free( A );
    free( B );
    free( C );

    printf("\n");

    return 0;
}
