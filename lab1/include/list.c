#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node{
    size_t countChars;
    char* chars;
    struct Node* next;
} Node;

typedef struct List{
    Node* head;
} List;

Node* initNode(const char* chars,Node* next){
    /**
     * Initializes a new Node with the given character data.
     *
     * @param chars A pointer to string.
     *              Must not be NULL and array of chars must have a not null length.
     * @param next A pointer to the next Node in the linked list.
     *
     * @return A pointer to the newly created Node, or NULL if memory allocation
     *         fails or if the input parameters are invalid.
     */

    if(!chars)//chars=nullptr
        return NULL;

    size_t strLen=strlen(chars);
    if ( !strLen )
        return NULL;

    Node* node = (Node*)malloc(sizeof(Node));
    if(!node)//mem check
        return NULL;

    node->countChars = strLen;
    node->next = next;
    node->chars = (char*)malloc(strLen*sizeof(char));
    if(!node->chars){//mem check
        free(node);
        return NULL;
    }
    strcpy(node->chars, chars);

    return node;
}

void addSorted(List* list,const char* word){
    /**
     * Adds a word to the linked list in sorted order.
     * Words are sorted by length and, in case of equal length, by alphabetical order.
     *
     * @param list A pointer to the linked list where the word will be added.
     *             Must not be NULL.
     * @param word A pointer to a string representing the word.
     *             Must not be NULL and must have a non-zero length.
     *
     * @note If the list or the word is invalid, the function does nothing.
     */
    if(!list || !word || !strlen(word))
        return;

    Node* newNode=initNode(word, NULL);

    if(!list->head){
        list->head=newNode;
        return;
    }

    Node* tmp = list->head;
    Node* prevTmp=NULL;
    while(tmp && (tmp->countChars < newNode->countChars || (tmp->countChars==newNode->countChars && strcmp(tmp->chars,newNode->chars)))){
        prevTmp=tmp;
        tmp=tmp->next;
    }

    newNode->next=tmp;
    if(prevTmp)prevTmp->next=newNode;
    else list->head=newNode;
}

void printNode(const Node* node){
    /**
     * Prints the character data of a node.
     *
     * This function outputs the string stored in the given node to the standard output,
     * enclosed in double quotes.
     *
     * @param node A pointer to the Node whose character data will be printed.
     *             Must not be NULL.
     */
    if(!node)
        return;
    printf("\"%s\"\n", node->chars);
}

void printWordsLongerThan(const List* list, const size_t len){
    /**
     * Prints all words in the list that are longer than a specified length..
     *
     * @param list A pointer to the linked list.
     *             Must not be NULL.
     * @param len The length to compare against. Only words longer than this length
     *            will be printed.
     */
    if(!list)
        return;
    Node* tmp=list->head;
    while(tmp && tmp->countChars<=len){
        tmp=tmp->next;
    }
    while(tmp){
        printNode(tmp);
        tmp=tmp->next;
    }
}

Node* getWordOfLength(const List* list,const size_t len){
    /**
     * Retrieves the first node in the list that contains a word of a specified length.
     *
     * @param list A pointer to the linked list to be searched.
     *             Must not be NULL.
     * @param len The length of the word to search for.
     *             Must be greater than zero.
     * @return A pointer to the first Node containing a word of the specified length,
     *         or NULL if no such word exists.
     */
    if(!list || !len)
        return NULL;
    Node* tmp = list->head;
    while(tmp){
        if(tmp->countChars==len) return tmp;
        tmp=tmp->next;
    }
    return NULL;
}

bool hasWordOfLength(const List* list,const size_t len){
    /**
     *Checks if there is a word of a specified length in the list.
     *
     * @param list A pointer to the linked list.
     *             Must not be NULL.
     * @param len The length of the word to search for.
     *             Must be greater than zero.
     *
     * @return true if a word of the specified length exists in the list,
     *         false otherwise.
     */
    if (!getWordOfLength(list,len))
        return false;
    return true;
}

void printWordsOfLength(const List* list,const size_t len){
    /**
     * Prints all words in the list that are of a specified length.
     *
     * @param list A pointer to the linked list.
     *             Must not be NULL.
     * @param len The length to compare against.
     */
    Node* tmp=getWordOfLength(list, len);
    while(tmp && tmp->countChars==len){
        printNode(tmp);
        tmp=tmp->next;
    }
}

void readWordsFromFile(List* list, const char* filename) {
    /**
     * Reads words from a specified file and adds them to the linked list in sorted order.

     *
     * @param list A pointer to the linked list.
     *             Must not be NULL.
     * @param filename A pointer to a string representing the name of the file to read from.
     *                 Must not be NULL.
     */
    if(!list)
        return;
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("file not found");
        return;
    }

    char buffer[256];
    while (fscanf(file, "%255s", buffer) == 1) {
        addSorted(list, buffer);
    }
    fclose(file);
}

void freeList(List* list) {
    /**
     * Frees the memory allocated for the linked list and its nodes.
     *
     * @param list A pointer to the linked list to be freed.
     *             Must not be NULL.
     */
    if(!list)
        return;
    Node* tmp = list->head;
    while (tmp) {
        Node* next = tmp->next;
        free(tmp->chars);
        free(tmp);
        tmp = next;
    }
}
