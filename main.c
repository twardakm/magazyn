#include <stdio.h>
#include <time.h>
#include "lista.h"
#include "menu.h"

int main(void)
{
    srand(time(NULL));
    element *lista = NULL;

    ustaw_kodowanie();
    lista = wiadomosc_powitalna(lista);

    lista = clear(lista);
    return 0;
}
