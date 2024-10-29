///////////////////////////////////////////// Òåñòû äëÿ ðåàëèçàöèè î÷åðåäè ///////////////////////////////////////////////////////////////////
#include <stdio.h>
#include "lab1.h"
#include <locale.h>
void testLinkedQueue();
void testArrayQueue();

int main() {
    setlocale(LC_CTYPE, "Russian");
    testLinkedQueue();
    testArrayQueue();
    return 0;
}

void testLinkedQueue() {
    LinkedQueue* q = createLinkedQueue();
    printf("Òåñòû äëÿ ñâÿçíîãî ñïèñêà\n\n");
    // Test_no1
    printf("Òåñò 1: Äîáàâëåíèå â ïóñòóþ î÷åðåäü\n");
    enqueueLinked(q, 10);
    printf("Dequeued: %d\n", dequeueLinked(q));

    // Test_no2
    printf("Òåñò 2: Äîáàâëåíèå äâóõ ýëåìåíòîâ\n");
    enqueueLinked(q, 20);
    enqueueLinked(q, 30);
    printf("Dequeued: %d\n", dequeueLinked(q));
    printf("Dequeued: %d\n", dequeueLinked(q));

    // Test_no3
    printf("Òåñò 3: Äåêüþ èç ïóñòîé î÷åðåäè\n");
    printf("Dequeued: %d\n", dequeueLinked(q)); // Îæèäàåì -1

    // Test_no4
    printf("Òåñò 4: Äîáàâëåíèå ýëåìåíòîâ ïîñëå óäàëåíèÿ\n");
    enqueueLinked(q, 40);
    printf("Dequeued: %d\n", dequeueLinked(q)); // Îæèäàåì 40

    // Test_no5
    printf("Òåñò 5: Ìíîæåñòâåííîå äîáàâëåíèå ýëåìåíòîâ\n");
    for (int i = 50; i <= 70; i += 10) {
        enqueueLinked(q, i);
    }
    printf("Äåêüþ âñå ýëåìåíòû:\n");
    for (int i = 0; i < 3; i++) {
        printf("Dequeued: %d\n", dequeueLinked(q));
    }

    destroyLinkedQueue(q);
}

void testArrayQueue() {
    printf("\nÒåñòû äëÿ ìàññèâà\n\n");
    ArrayQueue* q = createArrayQueue(4);
    // Test_no6
    printf("Òåñò 6: Äîáàâëåíèå â ïóñòóþ ìàññèâíóþ î÷åðåäü\n");
    enqueueArray(q, 10);
    printf("Dequeued: %d\n", dequeueArray(q));

    // Test_no7
    printf("Òåñò 7: Äîáàâëåíèå äâóõ ýëåìåíòîâ\n");
    enqueueArray(q, 20);
    enqueueArray(q, 30);
    printf("Dequeued: %d\n", dequeueArray(q));
    printf("Dequeued: %d\n", dequeueArray(q));

    // Test_no8
    printf("Òåñò 8: Ïåðåïîëíåíèå ìàññèâíîé î÷åðåäè\n");
    for (int i = 40; i <= 70; i += 10) {
        enqueueArray(q, i);
    }
    printf("Ïîïûòêà ïîñòàâèòü â î÷åðåäü åùå îäèí ýëåìåíò(80):\n");
    enqueueArray(q, 80); // Îæèäàåì ñîîáùåíèå îá îøèáêå

    // Test_no9
    printf("Òåñò 9: Äåêüþ èç ïóñòîé ìàññèâíîé î÷åðåäè\n");
    while (!isEmpty(q)) {
        printf("Dequeued: %d\n", dequeueArray(q)); // Äåêüþèì ýëåìåíòû äî ïóñòîé î÷åðåäè
    }
    printf("Dequeued: %d\n", dequeueArray(q)); // Îæèäàåì -1

    // Test_no10
    printf("Òåñò 10: Äîáàâëåíèå ýëåìåíòîâ ïîñëå îïóñòîøåíèÿ î÷åðåäè\n");
    enqueueArray(q, 90);
    printf("Dequeued: %d\n", dequeueArray(q)); // Îæèäàåì 90

    destroyArrayQueue(q);
}
