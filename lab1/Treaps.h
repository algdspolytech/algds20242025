#pragma once

//��������� ������
typedef struct Treap {
	int key; //����
	int priority; //���������
	struct Treap* left; //����� ���
	struct Treap* right; //������ ���
} Treap_t;

//�������� �������� �� ��������� �����������
Treap_t* CreateNode(int key);

//�����������
Treap_t* Merge(Treap_t* l, Treap_t* r);

//����������
void Split(Treap_t* t, int key, Treap_t** l, Treap_t** r);

//���������� �������� � ������ key
Treap_t* Add(Treap_t* t, int key);

//����� �������� �� �����
Treap_t* Find(Treap_t* t, int key);

//�������� �������� �� �����
Treap_t* Delete(Treap_t* t, int key);