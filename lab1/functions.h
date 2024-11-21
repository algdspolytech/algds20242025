#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct {
    int index;       // Original index (1-based)
    int l;           // Time to deliver
    int d;           // Deadline
    int w;           // Penalty per unit time
} Telegram;

void read_input(const char* filename, int* n, unsigned int* K, Telegram** telegrams);
void write_output(const char* filename, int n, int* order);
int schedule_telegrams(int n, unsigned int K, Telegram* telegrams, int* order);

#endif // FUNCTIONS_H