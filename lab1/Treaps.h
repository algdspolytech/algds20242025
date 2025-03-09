#pragma once

//декартово дерево
typedef struct Treap {
	int key; //ключ
	int priority; //приоритет
	struct Treap* left; //левый сын
	struct Treap* right; //правый сын
} Treap_t;

//создание элемента со случайным приоритетом
Treap_t* CreateNode(int key);

//объединение
Treap_t* Merge(Treap_t* l, Treap_t* r);

//разделение
void Split(Treap_t* t, int key, Treap_t** l, Treap_t** r);

//добавление элемента с ключом key
Treap_t* Add(Treap_t* t, int key);

//поиск элемента по ключу
Treap_t* Find(Treap_t* t, int key);

//удаление элемента по ключу
Treap_t* Delete(Treap_t* t, int key);