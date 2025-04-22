#pragma once

//���-�������
typedef struct {
	char** data; //������ �����
	int size; //������ �������
} HashTable_t;

//���-�������
int HashFunc(char* element, int table_size);

//�������� ���-�������
HashTable_t CreateTable(int size);

//����� ��������
int Find(char* element, HashTable_t table);

//���������� ��������
void Insert(char* element, HashTable_t table);

//�������� ��������
void Delete(char* element, HashTable_t table);
