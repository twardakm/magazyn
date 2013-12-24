#include "plik.h"
#include "lista.h"
#include <stdlib.h>
#include <stdio.h>

element *odczytaj_plik(element *first, char *nazwa_pliku)
{
    if (nazwa_pliku == NULL)
    {
        nazwa_pliku = (char *)malloc(sizeof(char) * MAX_FILE_NAME + 1);
        printf("Podaj nazwę pliku (maksymalnie %d znaków):\n", MAX_FILE_NAME);
        //konieczne żeby odczytywać całą linię
        //---------
        while(getchar() != '\n');
        fgets(nazwa_pliku, MAX_FILE_NAME, stdin);
        strtok(nazwa_pliku, "\n");
        //---------
    }
    if (_DEBUG) printf ("Nazwa pliku: %s\n", nazwa_pliku);

    return first;
}
