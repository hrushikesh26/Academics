#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
void printSolution(int colourArray[], int verticesLen)
{
    printf("Solution : \n");
    printf("Vertex\t|   Colour\n");
    for (int i = 0; i < verticesLen; i++)
        printf("%d\t|\t%d\n", i + 1, colourArray[i]);
    printf("\n");
}

bool isSafe(int currVertex, bool **adjacencyMatrix, int colourArray[], int colour, int verticesLen)
{
    for (int i = 0; i < verticesLen; i++)
        if (adjacencyMatrix[currVertex][i] && colour == colourArray[i])
            return false;
    return true;
}

bool backTrack(bool **adjacencyMatrix, int maxColours, int colourArray[], int currVertex, int verticesLen)
{
    if (currVertex == verticesLen)
        return true;

    for (int colour = 1; colour <= maxColours; colour++)
    {
        if (isSafe(currVertex, adjacencyMatrix, colourArray, colour, verticesLen))
        {
            colourArray[currVertex] = colour;
            if (
                backTrack(adjacencyMatrix, maxColours, colourArray, currVertex + 1, verticesLen) == true)
                return true;
            colourArray[currVertex] = 0;
        }
    }
    return false;
}

bool graphColoring(bool **adjacencyMatrix, int maxColours, int verticesLen)
{
    int colourArray[verticesLen];
    for (int i = 0; i < verticesLen; i++)
        colourArray[i] = 0;

    if (backTrack(adjacencyMatrix, maxColours, colourArray, 0, verticesLen) == false)
    {
        printf("Solution does not exist");
        return false;
    }
    printSolution(colourArray, verticesLen);
    return true;
}

int main()
{
    int verticesLen = 4;
    bool **adjacencyMatrix = (bool **)malloc(verticesLen * sizeof(bool));
    for (int i = 0; i < verticesLen; i++)
    {
        adjacencyMatrix[i] = (bool *)malloc(sizeof(bool) * verticesLen);
    }

    bool graphArray[16] = {0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0};
    for (int i = 0; i < verticesLen; i++)
    {
        for (int j = 0; j < verticesLen; j++)
        {
            // scanf("%d", &adjacencyMatrix[i][j]);
            adjacencyMatrix[i][j] = graphArray[i * verticesLen + j];
        }
    }
    // for (int i = 0; i < verticesLen; i++)
    // {
    //     for (int j = 0; j < verticesLen; j++)
    //     {
    //         printf("%d ", adjacencyMatrix[i][j]);
    //     }
    //     printf("\n");
    // }

    int maxColours = 4;
    graphColoring(adjacencyMatrix, maxColours, verticesLen);
    return 0;
}
