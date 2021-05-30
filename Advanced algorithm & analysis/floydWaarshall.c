#include <stdio.h>
#include <stdlib.h>
void floyds(int **distanceMatrix, int numVertices)
{
    int i, j, k;
    for (k = 0; k < numVertices; k++)
        for (i = 0; i < numVertices; i++)
            for (j = 0; j < numVertices; j++)
                if (i == j)
                    distanceMatrix[i][j] = 0;
                else
                    (distanceMatrix[i][j] < distanceMatrix[i][k] + distanceMatrix[k][j]) ? (distanceMatrix[i][j] = distanceMatrix[i][j]) : (distanceMatrix[i][j] = distanceMatrix[i][k] + distanceMatrix[k][j]);
}

void main()
{
    int weight, numVertices, numEdges, i, j;
    printf("\nEnter the number of vertices:");
    scanf("%d", &numVertices);
    int **distanceMatrix = (int **)malloc(numVertices * sizeof(int *));
    printf("\nEnter the number of edges:\n");
    scanf("%d", &numEdges);
    for (i = 0; i < numVertices; i++)
    {
        distanceMatrix[i] = (int *)malloc(numVertices * sizeof(int));
        for (j = 0; j < numVertices; j++)
        {
            distanceMatrix[i][j] = 999;
        }
    }
    for (i = 0; i < numEdges; i++)
    {
        int row, col;
        printf("\nEnter the end vertices of edge%d with its weight \n", i);
        scanf("%d%d%d", &row, &col, &weight);
        distanceMatrix[row][col] = weight;
    }
    printf("\nMatrix of input data:\n");
    for (i = 0; i < numVertices; i++)
    {
        for (j = 0; j < numVertices; j++)
            printf("%d \t", distanceMatrix[i][j]);
        printf("\n");
    }
    floyds(distanceMatrix, numVertices);
    printf("\nTransitive closure:\n");
    for (i = 0; i < numVertices; i++)
    {
        for (j = 0; j < numVertices; j++)
            printf("%d \t", distanceMatrix[i][j]);
        printf("\n");
    }
    printf("\nThe shortest paths are:");
    for (int row = 0; row < numVertices; row++)
        for (int col = 0; col < numVertices; col++)
            if (row != col)
                printf("\n d(%d,%d) = %d", row, col, distanceMatrix[row][col]);
}