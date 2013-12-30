#include "menu.h"
#include "lista.h"
#include "towar.h"
#include "plik.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

element *menu_sklep(element *lista)
{
    if (lista == NULL)
    {
        printf("Nie dodano żadnych towarów\n");
        return lista;
    }
    getchar();
    tekst_sklep(size(lista));
    int c = getchar();

    while(1)
    {
        switch(c)
        {
        case '1':
            if(_DEBUG) printf("Wybrano %c\n",c);
            lista = sprzedanie_towaru(lista);
            break;
        case '2':
            if (_DEBUG) printf("Wybrano %c\n",c);
            lista = przyjeto_towar(lista);
            c = 0;
            break;
        case '3':
            if (_DEBUG) printf("Wybrano %c\n", c);
            lista = menu_sortowanie(lista);
            break;
        case '4':
            if (_DEBUG) printf("Wybrano %c\n", c);
            wyszukiwanie_towaru(lista);
            break;
        case '0':
            if(_DEBUG) printf("Wybrano %c\n",c);
            printf("Czy aby na pewno chcesz wyjść? (T, N) ");
            if(czy_zapisac())
                return lista;
            break;
        default:
            tekst_sklep(size(lista));
            break;
        }
        if (c == 0)
        {
            tekst_sklep(size(lista));
            while((c = getchar())=='\n');
        }
        else
            c = getchar();
    }

    return lista;
}

element *menu_sortowanie(element *lista)
{
    if (lista == NULL)
    {
        printf("Nie dodano żadnych towarów\n");
        return;
    }
    tekst_sortowanie();
    getchar();
    char c;
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
                lista = sortowanie_nazwa_rosnaco(lista);
                return lista;
            case '2':
                if (_DEBUG) printf("%c\n", c);
                lista = sortowanie_nazwa_malejaco(lista);
                return lista;
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
                lista = sortowanie_ilosc_rosnaco(lista);
                return lista;
            case '2':
                if (_DEBUG) printf("%c\n", c);
                lista = sortowanie_ilosc_malejaco(lista);
                return lista;
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
                lista = sortowanie_rozmiar_rosnaco(lista);
                return lista;
            case '2':
                if (_DEBUG) printf("%c\n", c);
                lista = sortowanie_rozmiar_malejaco(lista);
                return lista;
            default:
                if (_DEBUG) printf("%c\n", c);
                printf("Niepoprawny wybór\n");
                break;
            }
            break;
        case '4':
            if (_DEBUG) printf("Wybrano %c", c);
            c = getchar();
            switch(c)
            {
            case '1':
                if (_DEBUG) printf("%c\n", c);
                lista = sortowanie_kolor_rosnaco(lista);
                return lista;
            case '2':
                if (_DEBUG) printf("%c\n", c);
                lista = sortowanie_kolor_malejaco(lista);
                return lista;
            default:
                if (_DEBUG) printf("%c\n", c);
                printf("Niepoprawny wybór\n");
                break;
            }
            break;
        case '5':
            if (_DEBUG) printf("Wybrano %c", c);
            c = getchar();
            switch(c)
            {
            case '1':
                if (_DEBUG) printf("%c\n", c);
                lista = sortowanie_cena_rosnaco(lista);
                return lista;
            case '2':
                if (_DEBUG) printf("%c\n", c);
                lista = sortowanie_cena_malejaco(lista);
                return lista;
            default:
                if (_DEBUG) printf("%c\n", c);
                printf("Niepoprawny wybór\n");
                break;
            }
            break;
        case '0':
            return lista;
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
           "2 - Usuń towar\n"
           "3 - Wczytaj plik\n"
           "4 - Wczytaj pojedyncze towary z pliku\n"
           "5 - Wyświetl dodane towary\n"
           "6 - Przejdź do menu sklepu\n"
           "8 - Wylosuj elementy\n"
           "9 - Zapisz\n"
           "0 - Wyjdź\n");
}

void tekst_sklep(int ile)
{
    printf("\nSKLEP\n--------\n");
    wyswietl_date();
    printf("Towarów w sklepie: %d\n", ile);
    printf("1 - sprzedano towar\n"
           "2 - przyjęto towar\n"
           "3 - wyświetl dostępny towar\n"
           "4 - wyszukiwanie towaru\n"
           "0 - Wróć do magazynu\n");
}

void tekst_sortowanie()
{
    printf("W jaki sposób posortować?\n"
           "11 - po nazwie\trosnąco\n"
           "12 - po nazwie\tmalejąco\n"
           "21 - po ilości\trosnąco\n"
           "22 - po ilości\tmalejąco\n"
           "31 - po rozmiarze\trosnąco\n"
           "32 - po rozmiarze\tmalejąco\n"
           "41 - po kolorze\trosnąco\n"
           "42 - po kolorze\tmalejąco\n"
           "51 - po cenie\trosnąco\n"
           "52 - po cenie\tmalejąco\n"
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
    int c = getchar();

    while(1)
    {
        switch(c)
        {
        case '1':
            if(_DEBUG) printf("Wybrano %c\n",c);
            lista = przyjeto_towar(lista);
            c = 0;
            break;
        case '2':
            if(_DEBUG) printf("Wybrano %c\n",c);
            lista = usuwanie_towaru(lista);
            break;
        case '3':
            if(_DEBUG) printf("Wybrano %c\n",c);
            lista = odczytaj_plik(lista, NULL, 1);
            break;
        case '4':
            if(_DEBUG) printf("Wybrano %c\n",c);
            lista = odczytaj_plik(lista, NULL, 0);
            break;
        case '5':
            if(_DEBUG) printf("Wybrano %c\n",c);
            lista = menu_sortowanie(lista);
            break;
        case '6':
            if(_DEBUG) printf("Wybrano %c\n",c);
            lista = menu_sklep(lista);
            break;
        case '8':
            if(_DEBUG) printf("Wybrano %c\n",c);
            lista = losuj(lista);
            break;
        case '9':
            if(_DEBUG) printf("Wybrano %c\n",c);
            break;
        case '0':
            if(_DEBUG) printf("Wybrano %c\n",c);
            if (czy_zmieniono(lista))
            {
                printf("Dokonano zmiany w magazynie, czy chcesz zapisać? (T, N) ");
                if(czy_zapisac())
                    zapisz_plik(lista, NULL);
            }
            printf("Dziękuję za skorzystanie z programu\nMarcin Twardak\n");
            return lista;
        default:
            tekst_powitalny(size(lista));
            break;
        }
        if (c == 0)
        {
            tekst_powitalny(size(lista));
            while((c = getchar())=='\n');
        }
        else
            c = getchar();
    }
}

void wyswietl_date()
{
    time_t *tp = malloc(sizeof(time_t));
    time(tp); //wygenerowanie czasu

    printf("%s\n", ctime(tp));

    free(tp);
}
