#include <iostream>
#include <cstdlib>
#include <omp.h>

using namespace std;

void generate(int **matrix, int n, int m)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            matrix[i][j] = rand() % 11;
}

void print(int **matrix, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << endl;
    }
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    int rows1 = 10;
    int columns1 = 4;
    int rows2 = 4;
    int columns2 = 6;

    int **matrix1;
    int **matrix2;

    matrix1 = (int **)malloc(sizeof(int *) * rows1);
    for (int i = 0; i < rows1; i++)
    {
        matrix1[i] = (int *)malloc(sizeof(int) * columns1);
    }
    matrix2 = (int **)malloc(sizeof(int *) * rows2);
    for (int i = 0; i < rows2; i++)
    {
        matrix2[i] = (int *)malloc(sizeof(int) * columns2);
    }

    generate(matrix1, rows1, columns1);
    generate(matrix2, rows2, columns2);

    int **result = (int **)malloc(sizeof(int *) * rows1);

    for (int i = 0; i < rows1; i++)
    {
        result[i] = (int *)malloc(sizeof(int) * columns2);
    }

    int threadsNum = omp_get_max_threads();
    omp_set_num_threads(threadsNum);

    int i, j, k;
#pragma omp parallel for shared(matrix1, matrix2, result) private(i, j, k)
    for (i = 0; i < rows1; i++)
    {
        for (j = 0; j < columns2; j++)
        {
            result[i][j] = 0;
            for (k = 0; k < columns1; k++)
            {

                result[i][j] += (matrix1[i][k] * matrix2[k][j]);
            }
        }
    }

    print(result, rows1, columns2);

    return 0;
}