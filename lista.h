#ifndef LISTA_H
#define LISTA_H

typedef struct element
{
    struct element *next;
    struct element *prev;
    struct towar *twr;
}element;

element * clear(element *first);
element * position(element *first, int n);
element * push(element * first, element * newone);
int size(element *first);

#endif // LISTA_H
