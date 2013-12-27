#include "towar.h"
#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

element *dodaj_towar(element *first)
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
    //---------

    printf("Podaj ilość towaru: ");
    scanf("%d", &temp->twr->ilosc);

    printf("Podaj cenę towaru: ");
    scanf("%lf", &temp->twr->cena);

    first = push(first, temp);

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

void wyswietl_towary(element *first)
{
    printf("DODANE TOWARY\n-------------------------\n\n");
    printf("Nazwa towaru\t\tIlość\tCena\n"
           "--------------------------------------\n");
    while (first != NULL)
    {
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
    }
    printf("--------------------------------------\n");
    return;
}
