#include "plik.h"
#include "lista.h"
#include "errors.h"
#include "towar.h"
#include <stdlib.h>
#include <stdio.h>

element *odczytaj_plik(element *first, char *nazwa_pliku)
{
    int err;
    char c;
    if (nazwa_pliku == NULL)
    {
        nazwa_pliku = (char *)malloc(sizeof(char) * MAX_FILE_NAME + 1);
        printf("Podaj nazwę pliku (maksymalnie %d znaków):\n", MAX_FILE_NAME);
        //konieczne żeby odczytywać całą linię
        //---------
        while(getchar() != '\n');
        fgets(nazwa_pliku, MAX_FILE_NAME + 1, stdin);
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

    element *temp = NULL;

    while ((err = sprawdz_czy_komentarz(plik)) == COMMENT_OK)
    {
        while ((c = fgetc(plik)) != '\n') {} // żeby przeskoczyć znak '{'
        temp = (element *)malloc(sizeof(element));
        temp->next = NULL;
        temp->twr = (towar *)malloc(sizeof(towar));
        temp->twr->nazwa_pliku = nazwa_pliku;
        temp->twr->nazwa = (char *)malloc(sizeof(char) * MAX_TOWAR_LENGHT + 1);
        fgets(temp->twr->nazwa, MAX_TOWAR_LENGHT + 1, plik); //+1 bo /n
        strtok(temp->twr->nazwa, "\n");
        fscanf(plik, "%d", &temp->twr->ilosc);
        fscanf(plik, "%lf", &temp->twr->cena);
        while ((c = fgetc(plik)) != '}') {} // żeby przeskoczyć znak '{'
        while ((c = fgetc(plik)) != '\n') {}

        if (_DEBUG)
            printf("Odczytano:\n"
                   "Nazwa pliku: %s\n"
                   "Nazwa towaru: %s\n"
                   "Ilość: %d\n"
                   "Cena: %.2f\n",
                   temp->twr->nazwa_pliku,
                   temp->twr->nazwa,
                   temp->twr->ilosc,
                   temp->twr->cena);

        first = push(first, temp);
    }

    if (_DEBUG) printf("Kod err: %d\n", err);

    fclose(plik);
    return first;
}

int sprawdz_czy_komentarz(FILE *plik)
{
    char c = fgetc(plik);
    while (c == '#' && c != EOF)
    {
        if (_DEBUG) printf("Znaleziono komentarz\n");
        do
        {
            c = fgetc(plik);
        } while (c != '\n' && c != EOF);
        c = fgetc(plik);
    }
    if (c == EOF)
        return COMMENT_EOF;
    else if (!fseek(plik, ftell(plik) - 1, SEEK_SET))
    {
        //if (_DEBUG) printf("Nie znaleziono komentarza\n");
        return COMMENT_OK;
    }
    else
    {
        printf("Błąd odczytu z pliku\n");
        return COMMENT_ERR;
    }
}
