#include "towar.h"
#include "lista.h"
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
                return;
        }
        else if (first->twr->czy_zmieniany || strcmp(first->twr->nazwa_pliku, first->next->twr->nazwa_pliku)!=0)
            return 1;
        first = first->next;
    }
    return 0;
}

element * dodaj_towar(element *first)
{
    element *temp = (element *)malloc(sizeof(element));
    temp->next = NULL;
    temp->twr = (towar *)malloc(sizeof(towar));
    temp->twr->nazwa = (char *)malloc(sizeof(char)*MAX_TOWAR_LENGHT + 1); //+1 na znak /0
    temp->twr->nazwa_pliku = NULL;

    printf("Podaj nazwę towaru: (maks. dł: %d)\n", MAX_TOWAR_LENGHT);
    //konieczne żeby odczytywać całą linię
    //---------
    while(getchar() != '\n');
    fgets(temp->twr->nazwa, MAX_TOWAR_LENGHT + 1, stdin);
    strtok(temp->twr->nazwa, "\n");
    //pierwsza litera musi być duża
    if (islower(temp->twr->nazwa[0]))
        temp->twr->nazwa[0] = toupper(temp->twr->nazwa[0]);
    //---------

    printf("Podaj ilość towaru: ");
    scanf("%d", &temp->twr->ilosc);

    printf("Podaj cenę towaru: ");
    scanf("%lf", &temp->twr->cena);

    temp->twr->czy_zmieniany = 1;

    first = push(first, temp);

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

    wyswietl_towary(first);

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

    wyswietl_towary(first);

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

    wyswietl_towary(first);

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

    wyswietl_towary(first);

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

    wyswietl_towary(first);

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

    wyswietl_towary(first);

    return first;
}

element * sprzedanie_towaru(element *first)
{
    sortowanie_nazwa_rosnaco(first);
    if (first == NULL)
    {
        printf("Nie dodano żadnego towaru\n");
        return first;
    }
    int d, ile;
    wyswietl_towary(first);
    do
    {
        printf("Który towar sprzedano - podaj Lp: ");
        scanf("%d", &d);
    } while (d > size(first) || d <= 0);
    do
    {
        printf("Ile sztuk sprzedano: ");
        scanf ("%d", &ile);
    } while(ile > position(first, d-1)->twr->ilosc || d <= 0);

    if (_DEBUG) printf("Wybrano towar: %d, sztuk: %d\n", d, ile);

    return first;
}

void wyswietl_towary(element *first)
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
    while (first != NULL)
    {
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
        first = first->next;
        i++;
    }
    printf("--------------------------------------\n");
    return;
}
