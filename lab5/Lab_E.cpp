#include "Lab_E.h"

#include <stdlib.h>
#include <math.h>

#define max(x,y) (((x) >= (y)) ? (x) : (y))


// Function to create a new tree node
Node* createNode(int value, Node* left, Node* right) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    
    if (!newNode) return 0;

    newNode->left = left;
    newNode->right = right;
    newNode->value = value;

    return newNode;
}

// Function to free the memory occupied by the tree
void freeNode(Node* node) {
    if (!node) return;

    freeNode(node->left);
    freeNode(node->right);
    free(node);
}

// Helper recursive function to read a tree from an array of data
static Node* recursiveReadTree(int* data, int index, int length) {
    if (index >= length)
        return 0;

    return createNode(data[index], recursiveReadTree(data, 2 * index + 1, length), recursiveReadTree(data, 2 * index + 2, length));
}

// Function to read a tree from a file
Node* readTree(FILE* file) {
    int length = 0;
    int size = 2;
    int* data = (int*)malloc(sizeof(int) * size);

    int temp = 0;
    while (fscanf(file, "%i", &temp) != EOF) {
        if (length >= size) {
            size *= 2;
            data = (int*)realloc(data, sizeof(int) * size);
        }

        data[length] = temp;
        length++;
    }
    data = (int*)realloc(data, length * sizeof(int));

    return recursiveReadTree(data, 0, length);
}    

// Helper function to get the depth of the tree
static int getDepth(Node* node) {
    if (!node)
        return 0;
    return 1 + max(getDepth(node->left), getDepth(node->right));
}

// Helper function that prints n spaces to file
static void fprint_tab(FILE* out, int n) {
    for (int i = 0;i < n;i++)
        fprintf(out, " ");
}

// Function to display the tree in usual way (to file)
void displayTree1(FILE* out, Node* node) {
    const int symbolWidth = 4;         // Width of symbols for display

    int depth = getDepth(node); // Get the depth of the tree
    int currentLength = 1;       // Current level length
    int nextSize = 2;            // Size for the next level
    int nextLength = 0;          // Length for the next level

    Node** currentLine = (Node**)malloc(sizeof(Node*)); // Current line of nodes
    Node** nextLine = (Node**)malloc(sizeof(Node*) * nextSize); // Next line of nodes

    currentLine[0] = node; // Start with the root of the tree

    int totalWidth = (pow(2, depth)) * (symbolWidth + 1) + 1; // Total width for display

    for (int i = 0; i < depth; i++) {

        int items = currentLength; // Number of items at the current level
        int tab = (totalWidth - symbolWidth * items) / (pow(2, i + 1)); // Calculate spacing

        // Display values of nodes at the current level
        for (int j = 0; j < currentLength; j++) {
            fprint_tab(out, tab);
            if (j > 0)
                fprint_tab(out, tab);

            fprintf(out, "%4i", currentLine[j]->value);
        }
        fprint_tab(out, tab);
        fprintf(out, "\n");

        // Prepare the next level
        for (int j = 0; j < currentLength; j++) {
            if (nextLength + 2 >= nextSize) {
                nextSize *= 2;
                nextLine = (Node**)realloc(nextLine, sizeof(Node*) * nextSize);
            }
            nextLine[nextLength] = currentLine[j]->left;
            nextLine[nextLength + 1] = currentLine[j]->right;
            nextLength += 2;
        }

        currentLine = (Node**)realloc(currentLine, sizeof(Node*) * nextSize);

        for (int i = 0; i < nextLength; i++)
            currentLine[i] = nextLine[i];

        currentLength = nextLength;
        nextLength = 0;
    }

    free(nextLine);
    free(currentLine);
}

// Function to display tree (int file) in the form of: node [left subtree] [right subtree]
void displayTree2(FILE* out, Node* node) {
    if (!node) return;

    fprintf(out, "%i ", node->value);

    displayTree2(out, node->left);
    displayTree2(out, node->right);
}

// Function that displays data from file
void displayFile(FILE* file) {
    char line[256];

    // Check if the file was opened successfully.
    if (file != NULL) {
        // Read each line from the file and store it in the 'line' buffer.
        while (fgets(line, sizeof(line), file))
            // Print each line to the standard output.
            printf("%s", line);

        // Close the file stream once all lines have been read.
        fclose(file);
    }
}