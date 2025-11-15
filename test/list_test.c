//
// Created by Kayky de Brito on 15/11/25.
//

#include <assert.h>
#include "../src/lib/list.h"

int main() {
    List* list = list_new(42);
    assert(list_val(list) == 42);
    return 0;
}

