#include "menu.h"
#include "lista.h"
#include "towar.h"
#include "plik.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void menu_sortowanie(element *lista)
{
    if (lista == NULL)
    {
        printf("Nie dodano żadnych towarów\n");
        return;
    }
    tekst_sortowanie();
    char c = getchar();

    while(c = getchar())
    {
        switch(c)
        {
        case '1':
            if (_DEBUG) printf("Wybrano %c", c);
            c = getchar();
            switch(c)
            {
            case '1':
                if (_DEBUG) printf("%c\n", c);
                break;
            case '2':
                if (_DEBUG) printf("%c\n", c);
                break;
            default:
                if (_DEBUG) printf("%c\n", c);
                printf("Niepoprawny wybór\n");
                break;
            }
            break;
        case '2':
            if (_DEBUG) printf("Wybrano %c", c);
            c = getchar();
            switch(c)
            {
            case '1':
                if (_DEBUG) printf("%c\n", c);
                break;
            case '2':
                if (_DEBUG) printf("%c\n", c);
                break;
            default:
                if (_DEBUG) printf("%c\n", c);
                printf("Niepoprawny wybór\n");
                break;
            }
            break;
        case '3':
            if (_DEBUG) printf("Wybrano %c", c);
            c = getchar();
            switch(c)
            {
            case '1':
                if (_DEBUG) printf("%c\n", c);
                break;
            case '2':
                if (_DEBUG) printf("%c\n", c);
                break;
            default:
                if (_DEBUG) printf("%c\n", c);
                printf("Niepoprawny wybór\n");
                break;
            }
            break;
        case '0':
            return;
        default:
            tekst_sortowanie();
            break;
        }
    }
}

void tekst_powitalny(int ile)
{
    printf("\nMAGAZYN\n--------------------------------\n");
    wyswietl_date();
    printf("Towarów w magazynie: %d\n", ile);
    printf("1 - Dodaj towar\n"
           "2 - Wczytaj plik\n"
           "3 - Wyświetl dodane towary\n"
           "0 - Wyjdź\n");
}

void tekst_sortowanie()
{
    printf("W jaki sposób posortować?\n"
           "11 - po nazwie\trosnąco\n"
           "12 - po nazwie\tmalejąco\n"
           "21 - po ilości\trosnąco\n"
           "22 - po ilości\tmalejąco\n"
           "31 - po cenie\trosnąco\n"
           "32 - po cenie\tmalejąco\n"
           "0 - powrót\n");
}

void ustaw_kodowanie()
{
#ifdef WIN32
    system("chcp 65001");
#endif
}

element * wiadomosc_powitalna(element *lista)
{
    tekst_powitalny(size(lista));
    int c;

    while(c = getchar())
    {
        switch(c)
        {
        case '1':
            if(_DEBUG) printf("Wybrano %c\n",c);
            lista = dodaj_towar(lista);
            break;
        case '2':
            if(_DEBUG) printf("Wybrano %c\n",c);
            lista = odczytaj_plik(lista, NULL);
            break;
        case '3':
            if(_DEBUG) printf("Wybrano %c\n",c);
            menu_sortowanie(lista);
            break;
        case '0':
            if(_DEBUG) printf("Wybrano %c\n",c);
            printf("Dziękuję za skorzystanie z programu\nMarcin Twardak\n");
            return lista;
        default:
            tekst_powitalny(size(lista));
            break;
        }
    }
}

void wyswietl_date()
{
    time_t *tp = malloc(sizeof(time_t));
    time(tp); //wygenerowanie czasu

    printf("%s\n", ctime(tp));

    free(tp);
}
