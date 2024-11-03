#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <memory.h>

#include "HashMap.h"


uint16_t _hash(char* str, uint16_t mod) {
	uint16_t h = 0;
	int i = 0;
	while (str[i] != '\0')
		h += str[i++];

	return h % mod;
}

HashMap* CreateHashMap(uint16_t mod) {
	HashMap* hm = (HashMap*)malloc(sizeof(HashMap));
	hm->items = (item**)malloc(sizeof(item*) * mod);

	for (int i = 0;i < mod;i++) {
		hm->items[i] = (item*)malloc(sizeof(item));
		hm->items[i][0] = {0, -1};
	}

	hm->keys_size = 0;
	hm->keys = (char**)malloc(sizeof(char*) * (hm->keys_size));

	hm->size = 0;

	return hm;
}

void AddItem(HashMap* hm, char* key, int value) {
	hm->size++;

	uint16_t hash = _hash(key, hm->mod);

	int length = 0;

	while (hm->items[hash][length].value != -1) length++;
	hm->items[hash] = (item*)realloc(hm->items[hash], sizeof(item) * (length + 1));
	hm->items[hash][length].value = value;
	hm->items[hash][length].key = key;

	hm->keys = (char**)realloc(hm->keys, sizeof(char*)*(hm->keys_size+1));
	hm->keys[hm->keys_size] = key;
	hm->keys_size++;
	hm->size++;
}

int cmp_str(char* s1, char* s2) {
	int i = 0;
	while (s1[i] != '\0' || s2[i] != '\0') {
		if (s1[i] != s2[i]) return 0;
		i++;
	}
	return 1;
}

int GetValue(HashMap* hm, char* key) {
	uint16_t hash = _hash(key, hm->mod);
	int i = 0;
	while (hm->items[hash][i].value != -1) {
		if (cmp_str(hm->items[hash][i].key, key))
			return hm->items[hash][i].value;
		i++;
	}

}

char** GetKeys(HashMap* hm) {
	hm->keys = (char**)realloc(hm->keys, sizeof(char*)*(hm->keys_size+1));
	hm->keys[hm->keys_size] = NULL;

	return hm->keys;
};

char* GetKeyByValue(HashMap* hm, int value) {
	for (int i = 0;i < hm->keys_size;i++) {
		if (GetValue(hm, hm->keys[i]) == value) {
			return hm->keys[i];
		}
	}
}

