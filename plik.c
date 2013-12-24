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

    FILE *plik;
    printf("Otwieranie pliku... %s ", nazwa_pliku);
    //otwarcie podanego pliku w trybie do odczytu
    if((plik = fopen(nazwa_pliku, "r")) == NULL)
    {
        perror("Nie udało się otworzyć podanego pliku\n");
        printf("\nKod błędu: %d\n");
        return first;
    }
    else
        printf("OK\n");

    fclose(plik);
    return first;
}
