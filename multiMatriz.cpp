#include <cstdio>
#include <time.h>
#include <omp.h>
#include <iostream>
#include <stdlib.h>

#define TAM 2048
#define MAX_RAND 10

void matrix_mult_SERIAL(int* m, int* n, int* p, int size)
{
	double start=omp_get_wtime();
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            for (int k = 0; k < size; k++)
            {
                p[i * size + j] += m[i * size + k] * n[k * size + j];
            }
        }
    }
    double end=omp_get_wtime();
	printf("Serial: %lf\n",end-start);
}

void matrix_mult_PARALLEL_STATIC(int* m, int* n, int* p, int size)
{
	double start=omp_get_wtime();
	#pragma omp parallel for schedule(static,50) collapse(2) shared(m,n,p)
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            for (int k = 0; k < size; k++)
            {
                p[i * size + j] += m[i * size + k] * n[k * size + j];
            }
        }
    }
    double end=omp_get_wtime();
	printf("Parallel(Static Scheduler) %lf\n",end-start);
}

void matrix_mult_PARALLEL_DYNAMIC(int* m, int* n, int* p, int size)
{
	double start=omp_get_wtime();
	#pragma omp parallel for schedule(dynamic,50) collapse(2) shared(m,n,p)
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            for (int k = 0; k < size; k++)
            {
                p[i * size + j] += m[i * size + k] * n[k * size + j];
            }
        }
    }
    double end=omp_get_wtime();
	printf("Parallel(Dynamic Scheduler) %lf\n",end-start);
}

void print_Mat(int* m, int size) //imprime matriz quadrada
{
    printf("[");
    for (int i = 0; i < size; i++)
    {
        printf("[");
        for (int j = 0; j < size; j++) 
        {
            if(j == size-1)
            {
                printf("%d",m[i*size + j]);
            }else{
                printf("%d ",m[i*size + j]);
            }
        }
        if(i == size-1)
        {
            printf("]");
        }else{
            printf("]\n");
        }

    }
    printf("]\n");
}

void print_Mat_file(int* m, int size) //imprime matriz quadrada
{
    FILE *f = fopen("matrix.txt", "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(f,"[");
    for (int i = 0; i < size; i++)
    {
        fprintf(f,"[");
        for (int j = 0; j < size; j++) 
        {
            if(j == size-1)
            {
                fprintf(f,"%d",m[i*size + j]);
            }else{
                fprintf(f,"%d ",m[i*size + j]);
            }
        }
        if(i == size-1)
        {
            fprintf(f,"]");
        }else{
            fprintf(f,"]\n");
        }
    }
    fprintf(f,"]");
    fclose(f);
}

int main(void)
{
    size_t bytes = TAM * TAM * sizeof(int); //qnt de bytes que precisam ser alocados para a matriz
    int* M = (int*)malloc(bytes);
    int* N = (int*)malloc(bytes);
    int* P = (int*)malloc(bytes);

    time_t t;
    srand((unsigned) time(&t)); /* Inicializa o gerador de números aleatórios */
    //inicializar matrizes m,n,p
    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++) 
        {
            M[i*TAM + j] = rand() % MAX_RAND;
            N[i*TAM + j] = rand() % MAX_RAND; 
            P[i*TAM + j] = 0;
        }
    }

    matrix_mult_SERIAL(M,N,P,TAM);
    matrix_mult_PARALLEL_STATIC(M,N,P,TAM);
    matrix_mult_PARALLEL_DYNAMIC(M,N,P,TAM);
    // print_Mat(M,TAM);
    // print_Mat(N,TAM);
    // print_Mat(P,TAM);

}