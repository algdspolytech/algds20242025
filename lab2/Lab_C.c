#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

//Ôóíêöèÿ ñ÷èòûâàíèÿ ñòðîêè â ôàéëå
char* Read_line(FILE* file) {
    char* line = malloc(sizeof(char));
    if (line == NULL) {
        free(line);
        printf("Îøèáêà âûäåëåíèÿ ïàìÿòè");
        return NULL;
    }
    char c;
    int i = 1;
    while (fscanf(file, "%c", &c) != EOF) {
        if (c == '\n' || c == '\0') {
            break;
        }
        line[i - 1] = c;
        i++;
        line = realloc(line, i * sizeof(char));
        if (line == NULL) {
            free(line);
            printf("Îøèáêà âûäåëåíèÿ ïàìÿòè");
            return NULL;
        }
    }
    line[i-1] = '\0';
    return line;
}

// Ôóíêöèÿ äëÿ îñâîáîæäåíèÿ ïàìÿòè, âûäåëåííîé ïîä ìàòðèöó
void Free_Matrix_adj(int** Matrix, int vertices) {
    for (int i = 0; i < vertices; i++) {
        free(Matrix[i]);
        Matrix[i] = NULL;
    }
    free(Matrix);
    Matrix = NULL;
}

// Ôóíêöèÿ äëÿ îïðåäåëåíèÿ êîëè÷åñòâà âåðøèí (ïî êîëè÷åñòâó ñòðîê â ôàéëå)
int Count_Vertices(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Îøèáêà îòêðûòèÿ ôàéëà\n");
        return -1;
    }

    int vertices = 0;
    int u;

    // Ñ÷èòàåì êîëè÷åñòâî ñòðîê ñ ïîìîùüþ fscanf
    while (1) {
        char* line = Read_line(file);
        if (line[0] == '\0') {
            free(line);
            break;
        }
        vertices++;
        free(line);
    }

    fclose(file);
    return vertices;
}

// Ôóíêöèÿ äëÿ ñîçäàíèÿ ìàòðèöû ñìåæíîñòè è èíèöèàëèçàöèè å¸ íóëÿìè
int** Create_Matrix_adj(int vertices) {
    int** Matrix_adj = (int**)malloc(vertices * sizeof(int*));
    if (Matrix_adj == NULL) {
        free(Matrix_adj);
        return NULL;
    }
    int flag = 0;
    for (int i = 0; i < vertices; i++) {
        Matrix_adj[i] = (int*)malloc(vertices * sizeof(int));
        if (Matrix_adj[i] == NULL) {
            flag = 1;
        }
        if (flag == 0) {
            for (int j = 0; j < vertices; j++) {
                Matrix_adj[i][j] = 0; // Èíèöèàëèçèðóåì íóëÿìè
            }
        }  
    }
    if (flag == 1) {
        Free_Matrix_adj(Matrix_adj, vertices);
        return NULL;
    }
    return Matrix_adj;
}

// Ôóíêöèÿ äëÿ çàïîëíåíèÿ ìàòðèöû ñìåæíîñòè íà îñíîâå ôàéëà
void Parsing_Matrix_adj(const char* filename, int** Matrix_adj, int vertices) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Îøèáêà îòêðûòèÿ ôàéëà\n");
        return;
    }

    int i, j;
    
    while (1) {
        char* line = Read_line(file);
        if (line[0] == '\0') {
            free(line);
            break;
        }
        char* line_cp = line;
        char* token;

        // Ïåðâûì ñ÷èòûâàåì âåðøèíó (íîìåð ïåðåä äâîåòî÷èåì)
        sscanf(line, "%d:", &j);

        // Ïîëó÷àåì ñïèñîê ñìåæíûõ âåðøèí (ðàçäåë¸ííûõ ïðîáåëàìè)
        token = strtok(
            line, " "); // Ïåðâûì òîêåíîì áóäåò íîìåð âåðøèíû j, åãî ïðîïóñêàåì
        token = strtok(NULL, " "); // Ñëåäóþùèå òîêåíû — ýòî ñìåæíûå âåðøèíû

        while (token != NULL) {
            i = atoi(token); // Ïðåîáðàçóåì ñòðîêó â ÷èñëî
            Matrix_adj[j][i] = 1;
            Matrix_adj[i][j] = 1;
            token = strtok(NULL, " "); // Ïåðåõîäèì ê ñëåäóþùåìó òîêåíó
        }
        free(line_cp);
    }

    fclose(file);
}

// Ôóíêöèÿ äëÿ âûâîäà êâàäðàòíîé ìàòðèöû 
void Print_Matrix(int** Matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", Matrix[i][j]);
        }
        printf("\n");
    }
}
