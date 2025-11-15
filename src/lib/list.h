#ifndef UFABC_AEDI_PROJ_LIST_H
#define UFABC_AEDI_PROJ_LIST_H

typedef struct list List;

List* list_new(int val);
int list_val(List* node);

#endif //UFABC_AEDI_PROJ_LIST_H