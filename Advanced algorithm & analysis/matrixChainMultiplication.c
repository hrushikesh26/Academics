#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
// #include <conio.h>
#define INT_MAX 2147483647
struct matrix
{
    int row, col;
    double **data;
};

double randDouble(int low, int high)
{
    return (double)(rand() % (high - low + 1)) + low;
}

    int randInt(int low, int high)
    {
        return (int)(rand() % (high - low + 1)) + low;
    }

double **initdoubleMatrix(int row, int col)
{

    double **matrix = (double **)malloc(row * sizeof(double *));
    for (int i = 0; i < row; i++)
        matrix[i] = (double *)malloc(col * sizeof(double));

    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            matrix[i][j] = randDouble(1, 10);
    return matrix;
}

int **initIntMatrix(int row, int col)
{

    int **matrix = (int **)malloc(row * sizeof(int *));
    for (int i = 0; i < row; i++)
        matrix[i] = (int *)malloc(col * sizeof(int));

    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            matrix[i][j] = 0;
    return matrix;
}

long long **initLongMatrix(int row, int col)
{

    long long **matrix = (long long **)malloc(row * sizeof(long long *));
    for (int i = 0; i < row; i++)
        matrix[i] = (long long *)malloc(col * sizeof(long long));

    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            matrix[i][j] = 0;
    return matrix;
}

void printMatrix(double **matrix, int row, int col)
{
    printf("\nMatrix:\n");
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
            printf("%0.1f\t", matrix[i][j]);
        printf("\n");
    }
}

void printMatrixArray(double **matrixArr[], int numOfMatrices, int *dimensionArray)
{
    for (int i = 0; i < numOfMatrices; i++)
        printMatrix(matrixArr[i], dimensionArray[i], dimensionArray[i + 1]);
}

void freeMatrix(struct matrix matrix)
{
    for (int i = 0; i < matrix.row; i++)
    {
        free(matrix.data[i]);
    }

    free(matrix.data);
}

struct matrix multiplyMatrices(struct matrix matA, struct matrix matB, bool freeMatA)
{
    if (matA.col == matB.row)
    {
        struct matrix matResult;
        matResult.row = matA.row;
        matResult.col = matB.col;
        matResult.data = initdoubleMatrix(matA.row, matB.col);
        for (int i = 0; i < matA.row; i++)
        {
            for (int j = 0; j < matB.col; j++)
            {
                matResult.data[i][j] = 0;
                for (int k = 0; k < matB.row; k++)
                {
                    matResult.data[i][j] += matA.data[i][k] * matB.data[k][j];
                }
            }
        }

        if (freeMatA)
            freeMatrix(matA);
        return matResult;
    }

    printf("Matrix dimentions did not match!!");
    struct matrix null;
    return null;
}

int **getOptimalSolution(int *dimensionArray, int numOfMatrices, long long **costMatrix)
{
    int **splitMatrix = initIntMatrix(numOfMatrices + 1, numOfMatrices + 1);
    // for (int i = 0; i < numOfMatrices + 1; i++)
    // {
    //     for (int j = 0; j < numOfMatrices + 1; j++)
    //     {
    //         costTable[i][j] = 0;
    //         splitMatrix[i][j] = 0;
    //     }
    // }
    for (int l = 2; l <= numOfMatrices; l++)
    {
        for (int i = 1; i <= numOfMatrices - l + 1; i++)
        {
            int j = i + l - 1;
            costMatrix[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; k++)
            {
                int temp = costMatrix[i][k] + costMatrix[k + 1][j] + dimensionArray[i - 1] * dimensionArray[k] * dimensionArray[j];
                if (temp < costMatrix[i][j])
                {
                    costMatrix[i][j] = temp;
                    splitMatrix[i][j] = k;
                }
            }
        }
    }
    return splitMatrix;
}

struct matrix matrixChainOptimal(struct matrix matrixArray[], int start, int end, int **splitMatrix)
{
    if (start == end)
    {
        return matrixArray[start];
    }
    if (start + 1 == end)
        return multiplyMatrices(matrixArray[start], matrixArray[end], start > 0 ? true : false);
    int splitIndex = splitMatrix[start][end];
    struct matrix result1 = matrixChainOptimal(matrixArray, start, splitIndex, splitMatrix);
    struct matrix result2 = matrixChainOptimal(matrixArray, splitIndex + 1, end, splitMatrix);
    return multiplyMatrices(result1, result2, true);
}

int main()
{
    srand(time(0));
    int numOfMatrices;
    int row, col;
    int **splitMatrix;
    long long **costMatrix;
    struct matrix result;
    struct matrix result2;
    double cpu_time_used1;
    double cpu_time_used2;
    printf("Enter Number of Matrices: ");
    scanf("%d", &numOfMatrices);
    int dimensionArray[numOfMatrices + 1];
    struct matrix matrixArray[numOfMatrices];
    /**
    *   $ Get Matrix Dimentions Manually 
    */
    // for (int i = 0; i < numOfMatrices; i++)
    // {
    //     if (i == 0)
    //     {
    //         printf("\nRow count for matrix %d: ", i);
    //         scanf("%d", &row);
    //         dimensionArray[i] = row;
    //         matrixArray[i].row = row;
    //     }
    //     else
    //     {
    //         printf("\nRow count for matrix %d: %d\n", i, col);
    //         row = col;
    //         matrixArray[i].row = col;
    //     }
    //     printf("Column count for matrix %d: ", i);
    //     scanf("%d", &col);
    //     dimensionArray[i + 1] = col;
    //     matrixArray[i].col = col;
    //     matrixArray[i].data = initdoubleMatrix(row, col);
    // }

    /**
     * $ Generate Random Dimensions For Matrices 
     */

    int low = 10, high = 100; //* Range of dimensions of matrices
    for (int i = 0; i < numOfMatrices; i++)
    {
        if (i == 0)
        {
            row = randInt(low, high);
            dimensionArray[i] = row;
        }
        else
        {
            row = col;
        }
        col = randInt(low, high);
        dimensionArray[i + 1] = col;
        matrixArray[i].row = row;
        matrixArray[i].col = col;
        matrixArray[i].data = initdoubleMatrix(row, col); //* Initialize matrix with random double number
    }

    /** 
     * $ Print dimension Array
     */
    printf("Dimension Array: ");
    for (int i = 0; i < numOfMatrices + 1; i++)
        printf("%d ", dimensionArray[i]);
    /** 
     * $ Print Matrices
     */
    // for (int i = 0; i < numOfMatrices; i++)
    //     printMatrix(matrixArray[i].data, matrixArray[i].row, matrixArray[i].col);

    /**
 * $ Normal(Sequentially) Matrix Chain Multiplication
 */
    result = matrixArray[0]; //* Set first matrix as result to pass it to function

    for (int i = 0; i < numOfMatrices - 1; i++)
        result = multiplyMatrices(result, matrixArray[i + 1], i > 0 ? true : false);
    long long normalCost = 1;
    for (int i = 0; i < numOfMatrices + 1; i++)
    {
        normalCost = normalCost * dimensionArray[i];
    }
    printf("\nCost with normal solution:\t%ld", normalCost);

    /**
     * $ Constructing Optimal solution and calculating matrix multiplication.
     */
    costMatrix = initLongMatrix(numOfMatrices + 1, numOfMatrices + 1);
    splitMatrix = getOptimalSolution(dimensionArray, numOfMatrices, costMatrix);
    result2 = matrixChainOptimal(matrixArray, 0, numOfMatrices - 1, splitMatrix);
    printf("\nCost with optimal solution:\t%ld", costMatrix[1][numOfMatrices]);

    /**
     * $ Print Split Matrix For Optimal Solution
     */

    // printf("\nCost Matrix:\n");
    // for (int i = 1; i < numOfMatrices + 1; i++)
    // {
    //     for (int j = 1; j < numOfMatrices + 1; j++)
    //     {
    //         printf("%d\t", costMatrix[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("\nSplit Matrix\n");
    // for (int i = 1; i < numOfMatrices + 1; i++)
    // {
    //     for (int j = 1; j < numOfMatrices + 1; j++)
    //         printf("%d\t", splitMatrix[i][j]);
    //     printf("\n");
    // }

    /**
     * $ Verify Result By Comparing With Normal Matrix Chain Multiplication
     */
    // printf("\n\nNORMAL Matrix Chain Multiplication Result");
    // printMatrix(result.data, result.row, result.col);
    // printf("\nOPTIMAL Matrix Chain Multiplication Result");
    // printMatrix(result2.data, result.row, result.col);
    /**
     * $ De-allocating Memory.
    */
    for (int i = 0; i < numOfMatrices; i++)
        freeMatrix(matrixArray[i]);

    printf("\nMemoery De-allocated !!");
    // printf("\nPress any key to exit.");
    // getch();
    return 0;
}
