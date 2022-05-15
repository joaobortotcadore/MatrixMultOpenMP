#include <cstdio>
#include <time.h>
#include <omp.h>
#include <iostream>
#include <stdlib.h>

#define TAM 4
#define MAX_RAND 10

void Mult_mat(int* m, int* n, int* p, int size)
{
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

    time_t t;
    srand((unsigned) time(&t)); /* Intializes random number generator */

    size_t bytes = TAM * TAM * sizeof(int); //qnt de bytes que precisam ser alocados para a matriz
    int* M = (int*)malloc(bytes);
    int* N = (int*)malloc(bytes);
    int* P = (int*)malloc(bytes);

    //inicializar matrizes m,n,p
    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++) 
        {
            M[i*TAM + j] = rand() % MAX_RAND; //valores aleatorios entre 0-1023
            N[i*TAM + j] = rand() % MAX_RAND; //valores aleatorios entre 0-1023
            P[i*TAM + j] = 0;
        }
    }

    Mult_mat(M,N,P,TAM);
    print_Mat(M,TAM);
    print_Mat(N,TAM);
    print_Mat(P,TAM);

}