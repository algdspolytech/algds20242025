#pragma once
#define N 4

//����������� ������� ������

typedef struct List {
	int count; //���������� ����������� ����� �������
	int data[N]; //������ � �������
	struct List* next; //��������� �� ��������� ����
} ULList_t;

//��������� ��� �������� ���������� �� �������� ��� �������� ������� � ����

typedef struct {
	ULList_t* list; //��������� �� ����, � ������� ���������� �������
	int index; //������ �������� ������ ������� ������ �����
} Element_t;

//�������� ��������� ���� ULList_t �� ��������� �����
ULList_t Create(int count, int* data, ULList_t* next); 

//���������� ��������
void Add(ULList_t* list, int element);

//����� ������ �������� �� �����
int Index(ULList_t* list, int key);

/*��������������� ������� - ����� �����, ����������� ������� � ������ �������,
� ��� ������� ������ �����*/
ULList_t* Find(ULList_t* list, int index, int* ptr);

//����� �������� � �������� �������
Element_t Element(ULList_t* list, int index);

//�������� �������� � �������� ������� 
void Delete(ULList_t* list, int index);

//������� ���������� ���������
int ElementCount(ULList_t* list);

//������������
Element_t Next(Element_t elem);
