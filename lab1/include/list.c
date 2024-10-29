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
    printf("\"%s\"\n", node->chars);
}

void printLongerWords(const List* list, const size_t len){
    if(!len)
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
