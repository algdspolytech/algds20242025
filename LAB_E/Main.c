#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include <stdlib.h>
#include <string.h>

typedef struct Node {
	int data;
	int width;
	struct Node* r;
	struct Node* l;
} Node;


Node* createknot(int n) {
	Node* knot = (Node*)malloc(sizeof(Node));
	knot->data = n;
	knot->l = NULL;
	knot->r = NULL;
	knot->width = 0;
	return knot;
}

int calcwidth(Node* root) {
	int width;
	char str[50];
	if (root != NULL) {
		if (root->l == NULL) {
			if (root->r == NULL) {
				sprintf(str, "%d", root->data);
				return width = strlen(str);			}
			else {
				sprintf(str, "%d", root->data);
				return width = strlen(str) + calcwidth(root->r);
			}
		}
		else {
			if (root->r == NULL) {
				sprintf(str, "%d", root->data);
				return width = strlen(str) + calcwidth(root->l);
			}
			else {
				sprintf(str, "%d", root->data);
				return width = strlen(str) + calcwidth(root->r) + calcwidth(root->l);
			}

		}

	}
	else {
		return 0;
	}
}

void freeTree(Node* root) {
	if (root == NULL) {
		return;
	}
	freeTree(root->l);
	freeTree(root->r);
	free(root);
}

writewidthtoknot(Node* root) {
	if (root != NULL) {
		root->width = calcwidth(root);
	}
	else {
		return;
	}
	writewidthtoknot(root->r);
	writewidthtoknot(root->l);

}
void testFillSubtreeWidths_no1() {
    Node* root = NULL;
    writewidthtoknot(root);
    printf("Test 1: ");
    if (root == NULL) {
        printf("Successfully\n");
    }
    else {
        printf("Failed\n");
    }
}

void testFillSubtreeWidths_no2() {
    Node* root = createknot(10);
    root->l = createknot(20);
    root->r = createknot(30);
    root->l->l = createknot(40);
    writewidthtoknot(root);
    printf("Test 2: ");
    if (root->width == 8 && root->l->width == 4 && root->r->width == 2) {
        printf("Successfully\n");
    }
    else {
        printf("Failed\n");
    }
    freeTree(root);
}

void testFillSubtreeWidths_no3() {
    Node* root = createknot(400);
    writewidthtoknot(root);
    printf("Test 3: ");
    if (root->width == 3) {
        printf("Successfully\n");
    }
    else {
        printf("Failed\n");
    }
    freeTree(root);
}


void testFillSubtreeWidths_no4() {
    Node* root = createknot(1);
    root->l = createknot(2);
    root->r = createknot(3);
    writewidthtoknot(root);
    printf("Test 4: ");
    if (root->width == 3 && root->l->width == 1 && root->r->width == 1) {
        printf("Successfully\n");
    }
    else {
        printf("Failed\n");
    }
    freeTree(root);
}

void testFillSubtreeWidths_no5() {
    Node* root = createknot(1);
    root->r = createknot(2);
    root->l = NULL;
    writewidthtoknot(root);
    printf("Test 5: ");
    if (root->width == 2 && root->r->width == 1) {
        printf("Successfully\n");
    }
    else {
        printf("Failed\n");
    }
    freeTree(root);
}

// ���� 6: �������� ������ � ����������� �������� � ������, ������� ����
void testFillSubtreeWidths_no6() {
    Node* root = createknot(123);
    root->l = createknot(377);
    root->r = createknot(952);
    root->l->l = createknot(0);
    root->l->l->r = createknot(52);
    writewidthtoknot(root);
    printf("Test 6: ");
    if (root->width == 12 && root->l->width == 6 && root->r->width == 3) {
        printf("Successfully\n");
    }
    else {
        printf("Failed\n");
    }
    freeTree(root);
}

void testFillSubtreeWidths_no7() {
    Node* root = createknot(999);
    root->l = createknot(888);
    root->r = createknot(777);
    root->l->l = createknot(666);
    root->l->r= createknot(555);
    root->r->l = createknot(444);
    root->r->r = createknot(333);
    writewidthtoknot(root);
    printf("Test 7: ");
    if (root->width == 21 && root->l->width == 9 && root->r->width == 9 &&
        root->l->l->width == 3 && root->l->r->width == 3 &&
        root->r->l->width == 3 && root->r->r->width == 3) {
        printf("Successfully\n");
    }
    else {
        printf("Failed\n");
    }
    freeTree(root);
}

void testFillSubtreeWidths_no8() {
    Node* root = createknot(1);
    root->l = createknot(2);
    root->r = createknot(3);
    root->l->l = createknot(4);
    root->l->r = createknot(-5);
    root->r->l = createknot(6);
    root->r->r = NULL;
    writewidthtoknot(root);
    printf("Test 8: ");
    if (root->width == 7 && root->l->width == 4 && root->r->width == 2) {
        printf("Successfully\n");
    }
    else {
        printf("Failed\n");
    }
    freeTree(root);
}

void testFillSubtreeWidths_no9() {
    Node* root = createknot(0);
    root->l = createknot(-1);
    root->r = createknot(-2);
    writewidthtoknot(root);
    printf("Test 9: ");
    if (root->width == 5 && root->l->width == 2 && root->r->width == 2) {
        printf("Successfully\n");
    }
    else {
        printf("Failed\n");
    }
    freeTree(root);
}

void testFillSubtreeWidths_no10() {
    Node* root = createknot(12345);
    root->l = createknot(67890);
    root->r = createknot(-11111);
    root->l->l = createknot(22222);
    root->l->r = createknot(-33333);
    root->r->l = createknot(44444);
    root->r->r = createknot(55555);
    writewidthtoknot(root);
    printf("Test 10: ");
    if (root->width == 37 && root->l->width == 16 && root->r->width == 16 &&
        root->l->l->width == 5 && root->l->r->width == 6 &&
        root->r->l->width == 5 && root->r->r->width == 5) {
        printf("Successfully\n");
    }
    else {
        printf("Failed\n");
    }
    freeTree(root);
}


int main() {
    testFillSubtreeWidths_no1();
    testFillSubtreeWidths_no2();
    testFillSubtreeWidths_no3();
    testFillSubtreeWidths_no4();
    testFillSubtreeWidths_no5();
    testFillSubtreeWidths_no6();
    testFillSubtreeWidths_no7();
    testFillSubtreeWidths_no8();
    testFillSubtreeWidths_no9();
    testFillSubtreeWidths_no10();

    return 0;

}