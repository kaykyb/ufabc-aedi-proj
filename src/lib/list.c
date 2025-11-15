//
// Created by Kayky de Brito on 15/11/25.
//

#include "list.h"

#include <stdlib.h>

typedef struct list {
    struct list* next;
    int val;
} List;

List * list_new(int val) {
    List* list = malloc(sizeof(List));
    list->val = val;

    return list;
}

int list_val(List *node) {
    return node->val;
}
