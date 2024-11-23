#include "code.h"



void append(BigInt* list, int item)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->value = item;

	if (list->head == NULL) {
		list->head = newNode;
		list->head->next = list->tail;
	}
	else if (list->tail == NULL) {
		list->tail = newNode;
		list->tail->next = NULL;
		list->head->next = list->tail;
	}
	else {
		list->tail->next = newNode;
		list->tail = newNode;
		list->tail->next = NULL;
	}
}


void rappend(BigInt* list, int item)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->value = item;

	if (list->head == NULL) {
		list->head = newNode;
		list->head->next = list->tail;
	}
	else if (list->tail == NULL) {
		list->tail = list->head;
		list->head = newNode;
		list->head->next = list->tail;
	}
	else {
		newNode->next = list->head;
		list->head = newNode;
	}
}


BigInt* init(int count, ...)
{
	BigInt* tmp = (BigInt*)malloc(sizeof(BigInt));
	tmp->head = tmp->tail = NULL;
	va_list number;
	va_start(number, count);
	for (int i = 0; i < count; i++)
	{
		rappend(tmp, va_arg(number, int));
	}
	va_end(number);
	return tmp;
}


BigInt* copy(BigInt* list) {
	BigInt* newlist = (BigInt*)malloc(sizeof(BigInt));
	if (list->head == NULL) {
		newlist->head = newlist->tail = NULL;
		return newlist;
	}
	Node* currentNode = list->head;
	Node* newNode = (Node*)malloc(sizeof(Node));
	newlist->head = newNode;
	if (list->tail == NULL) {
		newlist->head->next = newlist->tail = NULL;
		newlist->head->value = list->head->value;
		return newlist;
	}

	while (currentNode->next)
	{
		newNode->value = currentNode->value;
		newNode->next = (Node*)malloc(sizeof(Node));
		newNode = newNode->next;
		currentNode = currentNode->next;
	}
	newlist->tail = newNode;
	newlist->tail->value = list->tail->value;
	newlist->tail->next = NULL;
	return newlist;
}


void delete(BigInt* list) {
	Node* currentNode = list->head;
	Node* prevNode;
	while (currentNode) {
		prevNode = currentNode;
		currentNode = currentNode->next;
		free(prevNode);
	}

	free(list);
}


void reverse(BigInt* list) {
	if (list->tail == NULL) return;
	Node* currentNode = list->head;
	Node* nextNode = NULL;
	Node* prevNode = NULL;
	while (currentNode) {
		nextNode = currentNode->next;
		currentNode->next = prevNode;
		prevNode = currentNode;
		currentNode = nextNode;
	}
	list->head = prevNode;
}


void print(BigInt* list) {
	reverse(list);
	Node* currentNode = list->head;
	while (currentNode) {
		printf("%d", currentNode->value);
		currentNode = currentNode->next;
	}
	printf("\n");
	reverse(list);
}


void fix(BigInt* list) {
	Node* nzeroNode = list->head;
	Node* currentNode = list->head;
	int sign;
	if (list->tail == NULL) {
		sign = list->head->value >= 0 ? 1 : -1;
	}
	else {
		sign = list->tail->value >= 0 ? 1 : -1;
	}

	while (currentNode) {
		if (currentNode->value * sign < 0) {
			currentNode->value = 10 + currentNode->value * sign;
			currentNode->next->value -= sign;
		}
		else
		{
			if (currentNode->next) currentNode->next->value += currentNode->value / 10;
			currentNode->value = currentNode->value * sign % 10;
		}
		if (currentNode->value != 0) {
			nzeroNode = currentNode;
		}
		currentNode = currentNode->next;
	}
	nzeroNode->value = abs(nzeroNode->value) * sign;
	if (nzeroNode == list->head) {
		list->head->next = NULL;
	}
	else {
		list->tail = nzeroNode;
		list->tail->next = NULL;
	}
}


BigInt* add(BigInt* a, BigInt* b) {
	BigInt* c = (BigInt*)malloc(sizeof(BigInt));
	Node* currentNodeA = a->head;
	Node* currentNodeB = b->head;
	Node* currentNodeC = (Node*)malloc(sizeof(Node));
	int signA, signB;
	if (a->tail == NULL) {
		signA = a->head->value >= 0 ? 1 : -1;
	}
	else {
		signA = a->tail->value >= 0 ? 1 : -1;
	}
	if (b->tail == NULL) {
		signB = b->head->value >= 0 ? 1 : -1;
	}
	else {
		signB = b->tail->value >= 0 ? 1 : -1;
	}
	c->head = currentNodeC;
	c->head->value = (abs(a->head->value) * signA + abs(b->head->value) * signB) % 10;
	int d = (abs(a->head->value) * signA + abs(b->head->value) * signB) / 10;
	while (currentNodeA->next && currentNodeB->next) {
		currentNodeA = currentNodeA->next;
		currentNodeB = currentNodeB->next;
		currentNodeC->next = (Node*)malloc(sizeof(Node));
		currentNodeC = currentNodeC->next;
		currentNodeC->value = (abs(currentNodeA->value) * signA + abs(currentNodeB->value) * signB + d) % 10;
		d = (abs(currentNodeA->value) * signA + abs(currentNodeB->value) * signB + d) / 10;
	}
	while (currentNodeA->next) {
		currentNodeA = currentNodeA->next;
		currentNodeC->next = (Node*)malloc(sizeof(Node));
		currentNodeC = currentNodeC->next;
		currentNodeC->value = (abs(currentNodeA->value) * signA + d) % 10;
		d = (abs(currentNodeA->value) * signA + d) / 10;
	}
	while (currentNodeB->next) {
		currentNodeB = currentNodeB->next;
		currentNodeC->next = (Node*)malloc(sizeof(Node));
		currentNodeC = currentNodeC->next;
		currentNodeC->value = (abs(currentNodeB->value) * signB + d) % 10;
		d = (abs(currentNodeB->value) * signB + d) / 10;
	}
	if (d != 0) {
		currentNodeC->next = (Node*)malloc(sizeof(Node));
		currentNodeC = currentNodeC->next;
		currentNodeC->value = d;
	}
	currentNodeC->next = NULL;
	c->tail = currentNodeC;
	fix(c);
	return c;
}


BigInt* mul(BigInt* a, BigInt* b) {
	BigInt* c = (BigInt*)malloc(sizeof(BigInt));
	Node* currentNodeA = a->head;
	Node* currentNodeB = b->head;
	Node* currentNodeC = (Node*)malloc(sizeof(Node));
	int signA, signB;
	if (a->tail == NULL) {
		signA = a->head->value >= 0 ? 1 : -1;
	}
	else {
		signA = a->tail->value >= 0 ? 1 : -1;
	}
	if (b->tail == NULL) {
		signB = b->head->value >= 0 ? 1 : -1;
	}
	else {
		signB = b->tail->value >= 0 ? 1 : -1;
	}
	c->head = currentNodeC;
	c->head->value = 0;
	c->tail = NULL;
	if (a->tail == NULL)(append(a, 0));
	if (b->tail == NULL)(append(b, 0));
	c->head->next = c->tail;
	Node* bNode = currentNodeB;
	Node* cNode = c->head;
	int d = 0;
	int value = 0;
	while (currentNodeA) {
		currentNodeB = bNode;
		while (currentNodeB) {
			value = (abs(currentNodeA->value) * signA * abs(currentNodeB->value) * signB + d) % 10;
			d = (abs(currentNodeA->value) * signA * abs(currentNodeB->value) * signB + d) / 10;
			if (currentNodeC == NULL) {
				append(c, value);
				currentNodeC = c->tail;

			}
			else {
				currentNodeC->value += value;
				currentNodeC = currentNodeC->next;
			}
			currentNodeB = currentNodeB->next;
			//print(c);
		}
		currentNodeA = currentNodeA->next;
		if (currentNodeC == NULL) {
			if (d != 0)append(c, d);


		}
		else {
			if (currentNodeC->next == NULL) {
				if (d != 0)append(c, d);
			}
		}

		d = 0;
		if (cNode->next) {
			cNode = cNode->next;
		}
		else  if (currentNodeA) {

			cNode = c->tail;
		}

		currentNodeC = cNode;
	}
	if (c->tail->value == 0) {
		currentNodeC = c->head;
		while (currentNodeC->next != c->tail)
		{
			currentNodeC = currentNodeC->next;
		}
		c->tail = currentNodeC;
		c->tail->next = NULL;
	}
	if (c->tail->value == 0) {
		currentNodeC = c->head;
		while (currentNodeC->next != c->tail)
		{
			currentNodeC = currentNodeC->next;
		}
		c->tail = currentNodeC;
		c->tail->next = NULL;
	}
	fix(c);
	return c;
}


BigInt* sub(BigInt* a, BigInt* b) {
	BigInt* c = init(1, -1);
	return add(a, mul(b, c));
}


int equal(BigInt* a, BigInt* b) {
	Node* currentNodeA = a->head;
	Node* currentNodeB = b->head;
	while (currentNodeA || currentNodeB) {
		if (currentNodeA && currentNodeB && (currentNodeA->value == currentNodeB->value)) {
			currentNodeA = currentNodeA->next;
			currentNodeB = currentNodeB->next;
		}
		else {
			return 0;
		}
	}
	return 1;
}


BigInt* bigpow(BigInt* a, BigInt* b) {
	BigInt* z0 = init(1, 0);
	BigInt* z1 = init(1, -1);
	BigInt* c = init(1, 1);
	BigInt* i = copy(b);
	while (equal(i, z0) != 1) {
		i = add(i, z1);
		c = mul(c, a);
	}
	return c;
}
