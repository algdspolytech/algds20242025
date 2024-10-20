#include "funcs.h"



char* fullname(char* surname, char* name) {

	char* fullname = (char*) malloc(sizeof(char)*40);
	sprintf_s(fullname, 40, "%s %s", surname, name);

	return fullname;
}


void add_sort_list(Node** head, Node* new) {

	if ((*head) == NULL) {
		(*head) = new;
		(*head)->next = NULL;
	}

	else if (new->hours < (*head)->hours) {
		new->next = (*head);
		(*head) = new;
	}

	else {

		Node* p = (*head);

		while ((p->next) && (p->next->hours < new->hours)) {
			p = p->next;
		}

		new->next = p->next;
		p->next = new;

	}

}

Node* find_by_hours(Node* head, int value) {

	Node *p = head;

	while (p) {
		if (p->hours == value)
			return p;
		p = p->next;
	}
	
}

void add_sort_entries(Entry** head, Entry* new) {

	if ((*head) == NULL) {
		(*head) = new;
		(*head)->next = NULL;
	}

	else if (strcmp(fullname(new->surname, new->name), fullname((*head)->surname, (*head)->name)) < 0) {
		new->next = (*head);
		(*head) = new;
	}

	else {

		Entry* p = (*head);

		while ((p->next) && (strcmp(fullname(p->surname, p->name), fullname(new->surname, new->name)) < 0)) {
			p = p->next;
		}

		new->next = p->next;
		p->next = new;

	}
}

Node* read_file(char* filename) {

	FILE* file;
	Node* Head = NULL;
	char line[100];

	fopen_s(&file, filename, "r");
	while (fgets(line, sizeof(line), file)) {

		int hours;
		Entry* Person = (Entry*) malloc(sizeof(Entry));
		sscanf_s(line, "%d.%d.%d %s %s %d\n", &Person->date.day, &Person->date.month, &Person->date.year, &Person->surname, 20, &Person->name, 20, &hours);
		Person->total_hours = 0;

		Node* Found = find_by_hours(Head, hours);
		if (Found)
			add_sort_entries(&Found->head, Person);
		else {

			Node* New = (Node*) malloc(sizeof(Node));
			New->head = Person;
			New->hours = hours;
			New->head->next = NULL;
			add_sort_list(&Head, New);

		}
	}

	fclose(file);
	return Head;
}

void print_list(Node** head) {

	Node* p = (*head);
	while (p) {

		Entry* m = p->head;

		while (m) {
			printf("%d.%d.%d %s %s %d\n", m->date.day, m->date.month, m->date.year, m->surname, m->name, p->hours);
			m = m->next;
		}

		p = p->next;

	};
}