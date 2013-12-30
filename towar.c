#include "towar.h"
#include "lista.h"
#include "menu.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int czy_zmieniono(element *first)
{
    while (first != NULL)
    {
        if(first->next == NULL)
        {
            if (first->twr->czy_zmieniany)
                return 1;
        }
        else if (first->twr->nazwa_pliku == NULL && first->next->twr->nazwa_pliku == NULL)
        {
            if (first->twr->czy_zmieniany)
                return 1;
        }
        else if (first->twr->nazwa_pliku == NULL || first->next->twr->nazwa_pliku == NULL)
            return 1;
        else if (first->twr->czy_zmieniany || strcmp(first->twr->nazwa_pliku, first->next->twr->nazwa_pliku)!=0)
            return 1;
        first = first->next;
    }
    return 0;
}

element * dodaj_sztuk_towaru(element *first)
{
    if (first == NULL)
    {
        printf("Nie dodano żadnego towaru\n");
        return first;
    }
    first = sortowanie_nazwa_rosnaco(first);
    int d, ile;
    element *temp;
    do
    {
        printf("Który towar dodano - podaj Lp (0 aby wyjść): ");
        scanf("%d", &d);
    } while (d > size(first) || d < 0);
    if (d == 0) return first;
    temp = position(first, d-1);
    do
    {
        printf("Ile sztuk dodano (0 aby wyjść): ");
        scanf ("%d", &ile);
    } while(ile < 0);
    if (ile == 0) return first;

    if (_DEBUG) printf("Wybrano towar: %d, sztuk: %d\n", d, ile);

    temp->twr->czy_zmieniany = 1;
    temp->twr->ilosc += ile;

    return first;
}

element * dodaj_towar(element *first)
{
    element *temp = (element *)malloc(sizeof(element));
    temp->next = NULL;
    temp->twr = (towar *)malloc(sizeof(towar));
    temp->twr->nazwa = (char *)malloc(sizeof(char)*MAX_TOWAR_LENGHT + 1); //+1 na znak /0
    temp->twr->nazwa_pliku = NULL;

    while(getchar() != '\n');
    printf("Podaj nazwę towaru: (maks. dł: %d, puste aby wyjść) ", MAX_TOWAR_LENGHT);
    //konieczne żeby odczytywać całą linię
    //---------
    fgets(temp->twr->nazwa, MAX_TOWAR_LENGHT + 1, stdin);
    if (temp->twr->nazwa[0] == '\n')
    {
        free (temp->twr->nazwa);
        free (temp->twr);
        free (temp);
        return first;
    }
    strtok(temp->twr->nazwa, "\n");
    //pierwsza litera musi być duża
    if (islower(temp->twr->nazwa[0]))
        temp->twr->nazwa[0] = toupper(temp->twr->nazwa[0]);
    //---------

    printf("Podaj ilość towaru: (0 aby wyjść) ");
    scanf("%d", &temp->twr->ilosc);
    if (temp->twr->ilosc == 0)
    {
        free (temp->twr->nazwa);
        free (temp->twr);
        free (temp);

        return first;
    }

    printf("Podaj cenę towaru: (0 aby wyjść) ");
    scanf("%lf", &temp->twr->cena);

    if (temp->twr->cena == 0)
    {
        free (temp->twr->nazwa);
        free (temp->twr);
        free (temp);
        return first;
    }

    temp->twr->czy_zmieniany = 1;

    first = push(first, temp);

    return first;
}

element * przyjeto_towar(element *first)
{
    if (first == NULL)
    {
        first = dodaj_towar(first);
        return first;
    }
    tekst_przyjeto_towar();
    char c = getchar();

    while(c = getchar())
    {
        switch(c)
        {
        case '1':
            if(_DEBUG) printf("Wybrano %c\n", c);
            first = dodaj_towar(first);
            return first;
        case '2':
            if(_DEBUG) printf("Wybrano %c\n", c);
            first = dodaj_sztuk_towaru(first);
            return first;
        default:
            tekst_przyjeto_towar();
            break;
        }
    }
    return first;
}

element * sortowanie_cena_malejaco(element *first)
{
    if (first == NULL)
    {
        printf("Nie dodano żadnych towarów\n");
        return;
    }
    int czy = 0; //oznaczenie czy zmieniono coś w jednym przebiegu
    towar *temp;
    do
    {
        czy = 0;
        while (first->prev != NULL) {first = first->prev; } //powrót do początku
        while (first != NULL && first->next != NULL)
        {
            if (first->next->twr->cena > first->twr->cena)
            {
                //zamiana kolejności
                temp = first->twr;
                first->twr = first->next->twr;
                first->next->twr = temp;
                czy = 1;
            }
            first = first->next;
        }
    } while(czy);

    while (first->prev != NULL) {first = first->prev; } //powrót do początku

    wyswietl_towary(first, NULL, 0);

    return first;
}

element * sortowanie_cena_rosnaco(element *first)
{
    if (first == NULL)
    {
        printf("Nie dodano żadnych towarów\n");
        return;
    }
    int czy = 0; //oznaczenie czy zmieniono coś w jednym przebiegu
    towar *temp;
    do
    {
        czy = 0;
        while (first->prev != NULL) {first = first->prev; } //powrót do początku
        while (first != NULL && first->next != NULL)
        {
            if (first->next->twr->cena < first->twr->cena)
            {
                //zamiana kolejności
                temp = first->twr;
                first->twr = first->next->twr;
                first->next->twr = temp;
                czy = 1;
            }
            first = first->next;
        }
    } while(czy);

    while (first->prev != NULL) {first = first->prev; } //powrót do początku

    wyswietl_towary(first,NULL,0);

    return first;
}

element * sortowanie_ilosc_malejaco(element *first)
{
    if (first == NULL)
    {
        printf("Nie dodano żadnych towarów\n");
        return;
    }
    int czy = 0; //oznaczenie czy zmieniono coś w jednym przebiegu
    towar *temp;
    do
    {
        czy = 0;
        while (first->prev != NULL) {first = first->prev; } //powrót do początku
        while (first != NULL && first->next != NULL)
        {
            if (first->next->twr->ilosc > first->twr->ilosc)
            {
                //zamiana kolejności
                temp = first->twr;
                first->twr = first->next->twr;
                first->next->twr = temp;
                czy = 1;
            }
            first = first->next;
        }
    } while(czy);

    while (first->prev != NULL) {first = first->prev; } //powrót do początku

    wyswietl_towary(first,NULL,0);

    return first;
}

element * sortowanie_ilosc_rosnaco(element *first)
{
    if (first == NULL)
    {
        printf("Nie dodano żadnych towarów\n");
        return;
    }
    int czy = 0; //oznaczenie czy zmieniono coś w jednym przebiegu
    towar *temp;
    do
    {
        czy = 0;
        while (first->prev != NULL) {first = first->prev; } //powrót do początku
        while (first != NULL && first->next != NULL)
        {
            if (first->next->twr->ilosc < first->twr->ilosc)
            {
                //zamiana kolejności
                temp = first->twr;
                first->twr = first->next->twr;
                first->next->twr = temp;
                czy = 1;
            }
            first = first->next;
        }
    } while(czy);

    while (first->prev != NULL) {first = first->prev; } //powrót do początku

    wyswietl_towary(first,NULL,0);

    return first;
}

element * sortowanie_nazwa_malejaco(element *first)
{
    if (first == NULL)
    {
        printf("Nie dodano żadnych towarów\n");
        return;
    }
    int czy = 0; //oznaczenie czy zmieniono coś w jednym przebiegu
    towar *temp;
    do
    {
        czy = 0;
        while (first->prev != NULL) {first = first->prev; } //powrót do początku
        while (first != NULL && first->next != NULL)
        {

            if (strcoll(first->next->twr->nazwa, first->twr->nazwa) > 0)
            {
                //zamiana kolejności
                temp = first->twr;
                first->twr = first->next->twr;
                first->next->twr = temp;
                czy = 1;
            }
            first = first->next;
        }
    } while(czy);

    while (first->prev != NULL) {first = first->prev; } //powrót do początku

    wyswietl_towary(first,NULL,0);

    return first;
}

element * sortowanie_nazwa_rosnaco(element *first)
{
    if (first == NULL)
    {
        printf("Nie dodano żadnych towarów\n");
        return;
    }
    int czy = 0; //oznaczenie czy zmieniono coś w jednym przebiegu
    towar *temp;
    do
    {
        czy = 0;
        while (first->prev != NULL) {first = first->prev; } //powrót do początku
        while (first != NULL && first->next != NULL)
        {

            if (strcoll(first->next->twr->nazwa, first->twr->nazwa) < 0)
            {
                //zamiana kolejności
                temp = first->twr;
                first->twr = first->next->twr;
                first->next->twr = temp;
                czy = 1;
            }
            first = first->next;
        }
    } while(czy);

    while (first->prev != NULL) {first = first->prev; } //powrót do początku

    wyswietl_towary(first,NULL,0);

    return first;
}

element * sprzedanie_towaru(element *first)
{
    first = sortowanie_nazwa_rosnaco(first);
    if (first == NULL)
    {
        printf("Nie dodano żadnego towaru\n");
        return first;
    }
    int d, ile;
    element *temp;
    do
    {
        printf("Który towar sprzedano - podaj Lp (0 aby wyjść): ");
        scanf("%d", &d);
    } while (d > size(first) || d < 0);
    if (d == 0) return first;
    temp = position(first, d-1);
    do
    {
        printf("Ile sztuk sprzedano (0 aby wyjść): ");
        scanf ("%d", &ile);
    } while(ile > temp->twr->ilosc || ile < 0);
    if (ile == 0) return first;
    if (_DEBUG) printf("Wybrano towar: %d, sztuk: %d\n", d, ile);

    temp->twr->czy_zmieniany = 1;
    temp->twr->ilosc -= ile;
    if (temp->twr->ilosc == 0)
    {
        //usunięcie danego elementu
        printf("Towaru %s już brak na magazynie. Usuwam.\n",temp->twr->nazwa);

        free (temp->twr->nazwa_pliku);
        free (temp->twr->nazwa);
        free (temp->twr);

        if (temp->next == NULL)
            temp->prev->next = NULL;
        else
            temp->prev->next = temp->next;
        if (temp->prev == NULL)
            first = temp->next;
        else
            temp->next->prev = temp->prev;

        free (temp);
        return first;
    }

    return first;
}

void tekst_przyjeto_towar()
{
    printf("Chcesz dodać\n"
           "1 - Nowy towar\n"
           "2 - Ilość sztuk już dodanego towaru\n");
}

void wyswietl_towary(element *first, int * ktory, int ile)
{
    if (size(first) == 0)
    {
        printf("Nie dodano żadnych towarów!\n");
        return;
    }
    int i = 1;
    printf("DODANE TOWARY\n--------------------------------------\n\n");
    printf("Lp\tNazwa towaru\t\tIlość\tCena\n"
           "--------------------------------------\n");
    do
    {
        if (ktory != NULL)
            first = position(first, *(ktory+i));
        printf("%d\t", i);
        if (strlen(first->twr->nazwa) < 8)
            printf("%s\t\t\t", first->twr->nazwa);
        else if (strlen(first->twr->nazwa) < 16)
            printf("%s\t\t", first->twr->nazwa);
        else
            printf("%s\t", first->twr->nazwa);

        printf("%d\t%.2f\n",
               first->twr->ilosc,
               first->twr->cena);
        if (ktory == NULL)
            first = first->next;
        i++;
    } while (first != NULL && (ktory == NULL || i < ile));

    printf("--------------------------------------\n");
    return;
}

void wyszukiwanie_towaru(element *first)
{
    if (first == NULL)
    {
        printf("Nie dodano dotąd żadnego towaru\n");
        return;
    }

    int i;
    char *nazwa = (char *)malloc(sizeof(char) * MAX_TOWAR_LENGHT + 1);

    while(getchar() != '\n');
    printf("Podaj nazwę bądź jej początek do wyszukania - wielkość liter nie ma znaczenia (pusty wiersz wychodzi): ");
    fgets(nazwa, MAX_TOWAR_LENGHT + 1, stdin);
    if(nazwa[0] == '\n')
    {
        free(nazwa);
        return;
    }
    strtok(nazwa, "\n");
    printf("Wyszukiwanie... %s\n", nazwa);

    while (first != NULL)
    {
        for (i = 0; i < strlen(first->twr->nazwa); i++)
        {
            if(tolower(first->twr->nazwa[i]) == nazwa[i])
            {
                if (nazwa[i+1] == '\0')
                {
                    //wyświetlenie towaru
                }
            }
        }

        first = first->next;
    }

    free (nazwa);
    return;
}
