#include "towar.h"
#include "lista.h"
#include <stdlib.h>
#include <stdio.h>

element *dodaj_towar(element *first)
{
    element *temp = (element *)malloc(sizeof(element));
    temp->twr = (towar *)malloc(sizeof(towar));
    temp->twr->nazwa = (char *)malloc(sizeof(char)*MAX_TOWAR_LENGHT + 1); //+1 na znak /0

    printf("Podaj nazwę towaru: (maks. dł: %d)\n", MAX_TOWAR_LENGHT);
    //konieczne żeby odczytywać całą linię
    //---------
    while(getchar() != '\n');
    fgets(temp->twr->nazwa, MAX_TOWAR_LENGHT, stdin);
    strtok(temp->twr->nazwa, "\n");
    //---------

    printf("Podaj ilość towaru: ");
    scanf("%d", &temp->twr->ilosc);

    printf("Podaj cenę towaru: ");
    scanf("%lf", &temp->twr->cena);

    first = push(first, temp);

    return first;
}
