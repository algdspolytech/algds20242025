#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
        int id;       
        int l;        
        int d;        
        int w;        
        int delivered; 
    } Telegram;

    void readInput(const char* filename, int* n, unsigned int* K, Telegram** telegrams);
    void writeOutput(const char* filename, int n, Telegram* schedule);
    unsigned int computeTotalPenalty(int n, Telegram* schedule);
    void scheduleGreedy(int n, Telegram* telegrams, Telegram* schedule);

#ifdef __cplusplus
}
#endif

#endif 

