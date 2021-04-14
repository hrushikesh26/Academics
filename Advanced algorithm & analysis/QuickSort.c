#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int randInt(int low, int high)
{
    return (int)(rand() % (high - low + 1)) + low;
}

void swap(int *a, int *b)
{
    // printf("Swapping: %d, %d",*a, *b);
    int temp = *a;
    *a = *b;
    *b = temp;
}
int partition(int array[], int start, int end)
{
    int randomPivotIndex = randInt(start, end);
    // printf("Random Pivot Index: %d", randomPivotIndex);
    int pivot = array[randomPivotIndex];
    swap(&array[randomPivotIndex], &array[end]);
    int i = (start - 1);

    for (int j = start; j <= end - 1; j++)
    {
        if (array[j] < pivot)
        {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[end]);
    return (i + 1);
}

void quickSort(int array[], int start, int end)
{
    if (start < end)
    {
        int pivoteIndex = partition(array, start, end);
        quickSort(array, start, pivoteIndex - 1);
        quickSort(array, pivoteIndex + 1, end);
    }
}
void printArray(int array[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
}

int main()
{
    srand(time(0));
    int arraySize;
    printf("Enter size of array: ");
    scanf("%d", &arraySize);
    int array[arraySize];
    for (int i = 0; i < arraySize; i++)
        array[i] = randInt(0, 50);
    printf("Initial array: ");
    printArray(array, arraySize);

    quickSort(array, 0, arraySize - 1);
    printf("Sorted array: ");
    printArray(array, arraySize);
    return 0;
}
