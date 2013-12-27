#include "plik.h"
#include "lista.h"
#include "errors.h"
#include "towar.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

element *odczytaj_plik(element *first, char *nazwa_pliku)
{
    int err = FILENAME_WRONG;
    int i = 0;
    char c;

    wyswietl_pliki();

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

    //sprawdzanie czy jest to plik typu .mtw
    //---------------------------------------

    char *nazwa_copy = (char *)malloc(sizeof(char)*strlen(nazwa_pliku) + 1);
    char *c_temp = nazwa_copy;
    strcpy(nazwa_copy, nazwa_pliku);
    nazwa_copy = strtok(nazwa_copy, ".");

    nazwa_copy = strtok(NULL, ".");

    if(strcmp("mtw", nazwa_copy) == 0 && (nazwa_copy = strtok(nazwa_copy, ".")) != NULL)
    {
        if (_DEBUG) printf("Plik OK!\n");
    }
    else
    {
        printf("Program obsługuje tylko pliki formatu *.mtw");
        free(c_temp);
        free(nazwa_pliku);
        return first;
    }


    //---------------------------------------

    FILE *plik;
    printf("Otwieranie pliku... %s ", nazwa_pliku);
    //otwarcie podanego pliku w trybie do odczytu
    if((plik = fopen(nazwa_pliku, "r")) == NULL)
    {
        perror("Nie udało się otworzyć podanego pliku\n");
        free(nazwa_pliku);
        return first;
    }
    else
        printf("OK\n");

    element *temp = NULL;

    while ((err = sprawdz_czy_komentarz(plik)) == COMMENT_OK)
    {
        while ((c = fgetc(plik)) != '\n' && c != EOF) {} // żeby przeskoczyć znak '{'
        if (c == EOF) break;
        temp = (element *)malloc(sizeof(element));
        temp->next = NULL;
        temp->twr = (towar *)malloc(sizeof(towar));
        temp->twr->nazwa_pliku = nazwa_pliku;
        temp->twr->nazwa = (char *)malloc(sizeof(char) * MAX_TOWAR_LENGHT + 1);
        fgets(temp->twr->nazwa, MAX_TOWAR_LENGHT + 1, plik); //+1 bo /n
        strtok(temp->twr->nazwa, "\n");
        fscanf(plik, "%d", &temp->twr->ilosc);
        fscanf(plik, "%lf", &temp->twr->cena);
        while ((c = fgetc(plik)) != '}' && c != EOF) {} // żeby przeskoczyć znak '}'
        while ((c = fgetc(plik)) != '\n' && c != EOF) {}

        /*if (_DEBUG)
            printf("Odczytano:\n"
                   "Nazwa pliku: %s\n"
                   "Nazwa towaru: %s\n"
                   "Ilość: %d\n"
                   "Cena: %.2f\n",
                   temp->twr->nazwa_pliku,
                   temp->twr->nazwa,
                   temp->twr->ilosc,
                   temp->twr->cena);*/

        first = push(first, temp);
        i++;
    }

    printf("Wczytano %d towarów", i);

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
    if (c == '\n')
    {
        while ((c = fgetc(plik)) == '\n') {}
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

int wyswietl_pliki()
{
#ifdef WIN32
    FILE *ls = _popen("dir /b *.mtw", "r");
#else
    FILE *ls = popen("ls *.mtw", "r");
#endif
    if (ls == NULL)
    {
        perror ("Nie odnaleziono polecenia ls, wpisz nazwę pliku z pamięci\n");
        return LS_NOT_FOUND;
    }
    char * temp = (char *)malloc(sizeof(char) * MAX_FILE_NAME + 1);
    temp[0] = '\0';
    printf("Pliki mtw w tym folderze:\n------------\n");
    do
    {
        printf("%s", temp);
        fgets(temp, MAX_FILE_NAME, ls);
    } while(!feof(ls));
    printf("------------\n");
    free(temp);
#ifdef WIN32
    _pclose(ls);
#else
    pclose(ls);
#endif
    return SHOW_OK;
}
