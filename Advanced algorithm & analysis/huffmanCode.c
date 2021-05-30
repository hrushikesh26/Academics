#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct Node
{
    int freq;
    char letter;
    struct Node *left;
    struct Node *right;
} Node;

Node *createNode(char l, int f)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->letter = l;
    node->freq = f;
    node->left = node->right = NULL;
    return node;
}
void freeNode(Node *node)
{
    free(node);
}
void printNode(Node *node)
{
    printf("%c: %d\n", node->letter, node->freq);
}
void swapNodes(Node **a, Node **b)
{
    Node *temp = *a;
    *a = *b;
    *b = temp;
}
Node *popSmallest(Node **nodeArray, int *arrSize)
{
    int smallest = 999999;
    int smallestIndex = 0;
    Node *smallestNode;
    for (int i = 0; i < *arrSize; i++)
    {
        if (nodeArray[i]->freq < smallest)
        {
            smallest = nodeArray[i]->freq;
            smallestIndex = i;
        }
    }
    smallestNode = nodeArray[smallestIndex];
    swapNodes(&nodeArray[smallestIndex], &nodeArray[*arrSize - 1]);
    if (*arrSize > 1)
        nodeArray = (Node **)realloc(nodeArray, --*arrSize * sizeof(Node *));
    else
        --*arrSize;
    return smallestNode;
}
void addNodeToArray(Node **nodeArray, Node *temp, int *arrSize)
{
    if (*arrSize > 0)
    {
        int newSize = ++*arrSize;
        nodeArray = (Node **)realloc(nodeArray, newSize * sizeof(Node *));
    }
    else
        ++*arrSize;
    nodeArray[*arrSize - 1] = temp;
}
int calculateTreeHeight(Node *temp)
{
    if (temp == NULL)
        return 0;
    else
    {
        int left_side;
        int right_side;
        left_side = calculateTreeHeight(temp->left);
        right_side = calculateTreeHeight(temp->right);
        if (left_side > right_side)
        {
            return left_side + 1;
        }
        else
            return right_side + 1;
    }
}
void printArr(int codeArr[], int treeDepth)
{
    for (int i = 0; i < treeDepth; i++)
    {
        printf("%d", codeArr[i]);
    }
    printf("\n");
}
void printTree(Node *temp, int codeArr[], int treeDepth)
{
    if (temp->left)
    {
        codeArr[treeDepth] = 0;
        printTree(temp->left, codeArr, treeDepth + 1);
    }
    if (temp->right)
    {
        codeArr[treeDepth] = 1;
        printTree(temp->right, codeArr, treeDepth + 1);
    }
    if (temp->left == NULL && temp->right == NULL)
    {
        printf("%c : %d : ", temp->letter, temp->freq);
        printArr(codeArr, treeDepth);
    }
}

int main()
{
    char charArray[] = {'a', 'b', 's', 'd', 'f', 'e'};
    int freqArray[] = {1, 2, 3, 4, 5, 6};
    // char charArray[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    // int freqArray[] = {5, 9, 12, 13, 16, 45};
    int arrSize = sizeof(freqArray) / sizeof(int);
    Node **nodeArray = (Node **)malloc(arrSize * sizeof(Node *));

    for (int i = 0; i < arrSize; i++)
    {

        Node *temp = createNode(charArray[i], freqArray[i]);
        nodeArray[i] = temp;
    }
    Node *root = NULL;
    Node *temp = NULL;
    // building tree
    while (arrSize > 1)
    {
        Node *smallest1 = popSmallest(nodeArray, &arrSize);
        Node *smallest2 = popSmallest(nodeArray, &arrSize);
        temp = createNode('$', smallest1->freq + smallest2->freq);
        temp->left = smallest1;
        temp->right = smallest2;
        root = temp;
        addNodeToArray(nodeArray, temp, &arrSize);
    }
    int treeHeight = calculateTreeHeight(root);
    int codeArr[treeHeight];
    printf("\nPrinting Tree!! \n");
    printTree(root, codeArr, 0);
    for (int i = 0; i < arrSize; i++)
        freeNode(nodeArray[i]);

    printf("\n ");
    return 0;
}