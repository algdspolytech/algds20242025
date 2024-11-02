#pragma once
// ��������� ��� �������� ����� � ��������� �����
#include <cstddef>
#ifndef HEADER_H
#define HEADER_H

#ifdef __cplusplus
extern "C" {
#endif
    typedef struct {
        char word[50];
        int key;
    } Data;

    // ������� ��� ��������� ������ ��� ����������
    int compareKeys(const void* a, const void* b) {
        return ((Data*)a)->key - ((Data*)b)->key;
    }

    // ������� ��� ������ ����� �� �����
    const char* findWordByKey(Data* data, int size, int key) {
        for (int i = 0; i < size; i++) {
            if (data[i].key == key) {
                return data[i].word;
            }
        }
        return NULL;
    }
#ifdef __cplusplus
}
#endif
#endif