#include "Header.h"

node* initNode(int vertex){
    node* newNode = malloc(sizeof(node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

graph* initGraph(int vertex){
    graph* newG = (graph*)malloc(sizeof(graph));
    newG->numVertex = vertex;

    newG->adjList = (node**)malloc(vertex*sizeof(node*));
    newG->visited = (bool*)malloc(vertex*sizeof(bool));

    for(int i = 0; i < vertex; i++){
        newG->adjList[i] = 0;
        newG->visited[i] = false;
    }
    return newG;
}

void addEdge(graph* gr, int cur, int end){
  node* newN = initNode(end);
  newN->vertex = end;
  newN->next = gr->adjList[cur];
  gr->adjList[cur] = newN;

  newN = initNode(cur);
  newN->next=gr->adjList[end];
  gr->adjList[end] = newN;
}


void DFS(graph* gr, int start, int end, int* found){
    gr->visited[start] = 1;
    if(start == end){*found = 1; return;}

    node* List = gr->adjList[start];
 

    while(List != NULL){
        int tmp = List->vertex;
        if(!gr->visited[tmp]){
           DFS(gr, tmp, end, found);
        }
        List = List->next;
    }
    
}

int pathExist(graph* gr, int start, int end){
    int found = 0;
    DFS(gr, start, end, &found);
    return found;
}

graph* ReadFromFile(const char* filename){
    FILE* file = fopen(filename, "r");
    if(file == NULL){
        printf("file opening error, exit");
        exit(1);
    }

    int vertices;
    fscanf(file, "%d", &vertices);

    graph* gr = initGraph(vertices);
    int start = 1, end = 2;

    while(fscanf(file, "%d %d", &start, &end) != EOF){
        addEdge(gr, start, end);
    }
    fclose(file);

    return gr;
}

graph* Free_graph(graph* gr){
    node** cur = gr->adjList;

    while(*cur!= NULL){
    node* temp = *cur;
    temp = temp->next;
    free(*cur);
    }

    free(gr);
    free(cur);
    return 0;
}