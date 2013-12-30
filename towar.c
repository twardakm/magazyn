#include "towar.h"
#include "lista.h"
#include "menu.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

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
    int c;
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

    printf("Wybierz rozmiar: (0 aby wyjść)\n");
    wyswietl_rozmiary();
    getchar();
    c = getchar();

    do
    {
        switch (c)
        {
        case '1':
            temp->twr->rozmiar = 1; break;
        case '2':
            temp->twr->rozmiar = 2; break;
        case '3':
            temp->twr->rozmiar = 3; break;
        case '4':
            temp->twr->rozmiar = 4; break;
        case '5':
            temp->twr->rozmiar = 5; break;
        case '6':
            temp->twr->rozmiar = 6; break;
        case '7':
            temp->twr->rozmiar = 7; break;
        case '8':
            temp->twr->rozmiar = 8; break;
        case '0':
            free (temp->twr->nazwa);
            free (temp->twr);
            free (temp);

            return first;
        default:
            printf("Wybierz poprawny rozmiar!\n");
            getchar();
            c = getchar();
            break;
        }
    } while (c < '0' && c > '8');
    getchar();

    temp->twr->kolor = (char *)malloc(sizeof(char) * MAX_COLOR_LENGHT+1);
    printf("Podaj kolor towaru: (maks, dł: %d, puste aby wyjść) ", MAX_COLOR_LENGHT);
    fgets(temp->twr->kolor, MAX_COLOR_LENGHT + 1, stdin);
    if (temp->twr->kolor[0] == '\n')
    {
        free (temp->twr->nazwa);
        free (temp->twr->kolor);
        free (temp->twr);
        free (temp);
        return first;
    }
    strtok(temp->twr->kolor, "\n");
    //pierwsza litera musi być duża
    if (islower(temp->twr->kolor[0]))
        temp->twr->kolor[0] = toupper(temp->twr->kolor[0]);
    //---------

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

element * losuj(element *first)
{
    int ile, i;
    element *temp;
    char **kolory;
    char **nazwy;
    do
    {
        printf("Ile elementów chcesz wylosować? (Od 1 do %d, 0 wychodzi) ", MAX_RANDOM);
        scanf("%d", &ile);
    } while(ile < 0 || ile > MAX_RANDOM);
    if (ile == 0)
        return first;

    kolory = (char **)malloc(sizeof(char *) * 16);
    for (i = 0; i < 16; i++)
        kolory[i] = (char *)malloc(sizeof(char) * MAX_COLOR_LENGHT + 1);

    nazwy = (char **)malloc(sizeof(char *) * 10);
    for (i = 0; i < 10; i++)
        nazwy[i] = (char *)malloc(sizeof(char) * MAX_TOWAR_LENGHT + 1);

    //wgranie kolorów
    //-----
    strcpy(kolory[0], "Czarny");
    strcpy(kolory[1], "Srebrny");
    strcpy(kolory[2], "Szary");
    strcpy(kolory[3], "Biały");
    strcpy(kolory[4], "Bordowy");
    strcpy(kolory[5], "Czerwony");
    strcpy(kolory[6], "Fioletowy");
    strcpy(kolory[7], "Pomarańczowy");
    strcpy(kolory[8], "Ciemnozielony");
    strcpy(kolory[9], "Jasnozielony");
    strcpy(kolory[10], "Zielony");
    strcpy(kolory[11], "Złoty");
    strcpy(kolory[12], "Granatowy");
    strcpy(kolory[13], "Niebieski");
    strcpy(kolory[14], "Błękitny");
    strcpy(kolory[15], "Wodny");
    //-----
    //wgranie nazw towarów
    //-----
    strcpy(nazwy[0], "T-Shirt");
    strcpy(nazwy[1], "Spodenki sport.");
    strcpy(nazwy[2], "Kurtka zimowa");
    strcpy(nazwy[3], "Kurtka letnia");
    strcpy(nazwy[4], "Skarpety");
    strcpy(nazwy[5], "Czapka");
    strcpy(nazwy[6], "Bluza");
    strcpy(nazwy[7], "Koszula z krótk.");
    strcpy(nazwy[8], "Koszula");
    strcpy(nazwy[9], "Podkoszulek");
    //-----

    for (i = 0; i < ile; i++)
    {
        temp = (element *)malloc(sizeof(element));
        temp->twr = (towar *)malloc(sizeof(towar));
        temp->twr->nazwa_pliku = NULL;
        temp->twr->nazwa = (char *)malloc(sizeof(char) * MAX_TOWAR_LENGHT + 1);
        temp->twr->kolor = (char *)malloc(sizeof(char) * MAX_COLOR_LENGHT + 1);
        temp->twr->czy_zmieniany = 1;

        strcpy(temp->twr->nazwa, nazwy[(int)(rand()%10)]);
        temp->twr->ilosc = (int)(rand()%100) + 1;
        temp->twr->rozmiar = (int)(rand()%8) + 1;
        strcpy(temp->twr->kolor, kolory[(int)(rand()%16)]);
        temp->twr->cena = (double)((rand()%10000)/100.);

        first = push(first, temp);
    }

    for (i = 0; i < 16; i++)
        free(kolory[i]);
    free (kolory);

    for (i = 0; i < 10; i++)
        free(nazwy[i]);
    free (nazwy);
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
        return first;
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
        return first;
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
        return first;
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
        return first;
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

element * sortowanie_kolor_malejaco(element *first)
{
    if (first == NULL)
    {
        printf("Nie dodano żadnych towarów\n");
        return first;
    }
    int czy = 0; //oznaczenie czy zmieniono coś w jednym przebiegu
    towar *temp;
    do
    {
        czy = 0;
        while (first->prev != NULL) {first = first->prev; } //powrót do początku
        while (first != NULL && first->next != NULL)
        {

            if (strcoll(first->next->twr->kolor, first->twr->kolor) > 0)
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

element * sortowanie_kolor_rosnaco(element *first)
{
    if (first == NULL)
    {
        printf("Nie dodano żadnych towarów\n");
        return first;
    }
    int czy = 0; //oznaczenie czy zmieniono coś w jednym przebiegu
    towar *temp;
    do
    {
        czy = 0;
        while (first->prev != NULL) {first = first->prev; } //powrót do początku
        while (first != NULL && first->next != NULL)
        {

            if (strcoll(first->next->twr->kolor, first->twr->kolor) < 0)
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
        return first;
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
        return first;
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

element * sortowanie_rozmiar_malejaco(element *first)
{
    if (first == NULL)
    {
        printf("Nie dodano żadnych towarów\n");
        return first;
    }
    int czy = 0; //oznaczenie czy zmieniono coś w jednym przebiegu
    towar *temp;
    do
    {
        czy = 0;
        while (first->prev != NULL) {first = first->prev; } //powrót do początku
        while (first != NULL && first->next != NULL)
        {
            if (first->next->twr->rozmiar > first->twr->rozmiar)
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

element * sortowanie_rozmiar_rosnaco(element *first)
{
    if (first == NULL)
    {
        printf("Nie dodano żadnych towarów\n");
        return first;
    }
    int czy = 0; //oznaczenie czy zmieniono coś w jednym przebiegu
    towar *temp;
    do
    {
        czy = 0;
        while (first->prev != NULL) {first = first->prev; } //powrót do początku
        while (first != NULL && first->next != NULL)
        {
            if (first->next->twr->rozmiar < first->twr->rozmiar)
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

        return (usun_towar(first, temp));
    }

    return first;
}

element * usun_towar(element *first, element *temp)
{
    element *t = first;
    char *c = temp->twr->nazwa_pliku;
    int d = 0;
    while (t != NULL)
    {
        if (c == temp->twr->nazwa_pliku)
            d++;
        t->twr->czy_zmieniany = 1; //skoro 1 usunięty zaznaczam na wszystkich
        t = t->next;
    }
    if (d == 1)
        free (temp->twr->nazwa_pliku);

    free (temp->twr->kolor);
    free (temp->twr->nazwa);
    free (temp->twr);

    if (temp->next == NULL && temp->prev != NULL)
        temp->prev->next = NULL;
    else if (temp->next != NULL && temp->prev == NULL)
    {
        first = temp->next;
        first->prev = NULL;
    }
    else if (temp->next == NULL && temp->prev == NULL)
    {
        free (temp);
        return NULL;
    }
    else
    {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
    }

    free (temp);
    return first;
}

element * usuwanie_towaru(element *first)
{
    first = menu_sortowanie(first);
    int d;
    do
    {
        printf("Który towar chcesz usunąć? (0 wychodzi)\n");
        scanf("%d", &d);
    } while (d < 0 || d > size(first));
    if (d == 0)
        return first;

    first = usun_towar(first, position(first,d-1));

    return first;
}

void tekst_przyjeto_towar()
{
    printf("Chcesz dodać\n"
           "1 - Nowy towar\n"
           "2 - Ilość sztuk już dodanego towaru\n");
}

void wyswietl_rozmiary()
{
    printf("1 - XS\n"
           "2 - S\n"
           "3 - M\n"
           "4 - L\n"
           "5 - XL\n"
           "6 - 2XL\n"
           "7 - 3XL\n"
           "8 - 4XL\n");
    return;
}

void wyswietl_towary(element *first, int * ktory, int ile)
{
    if (size(first) == 0)
    {
        printf("Nie dodano żadnych towarów!\n");
        return;
    }
    int i = 0;
    printf("DODANE TOWARY\n----------------------------------------------------------------------\n\n");
    printf("Lp\tNazwa towaru\t\tIlość\tRozmiar\tKolor\t\tCena\n"
           "----------------------------------------------------------------------\n");
    element *lista = first;
    do
    {
        if (ktory != NULL)
            first = position(lista, ktory[i]);
        printf("%d\t", i+1);
        if (strlen(first->twr->nazwa) < 8)
            printf("%s\t\t\t", first->twr->nazwa);
        else if (strlen(first->twr->nazwa) < 16)
            printf("%s\t\t", first->twr->nazwa);
        else
            printf("%s\t", first->twr->nazwa);

        printf("%d\t", first->twr->ilosc);

        switch(first->twr->rozmiar)
        {
        case 1: printf("XS\t"); break;
        case 2: printf("S\t"); break;
        case 3: printf("M\t"); break;
        case 4: printf("L\t"); break;
        case 5: printf("XL\t"); break;
        case 6: printf("2XL\t"); break;
        case 7: printf("3XL\t"); break;
        case 8: printf("4XL\t"); break;
        }

        if (strlen(first->twr->kolor) < 8)
            printf("%s\t\t", first->twr->kolor);
        else
            printf("%s\t", first->twr->kolor);

        printf("%.2f\n", first->twr->cena);
        if (ktory == NULL)
            first = first->next;
        i++;
    } while (first != NULL && (ktory == NULL || i < ile));

    printf("----------------------------------------------------------------------\n");
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
    int j = 0;
    int ile = 0;
    char *nazwa = (char *)malloc(sizeof(char) * MAX_TOWAR_LENGHT + 1);
    int *ktore = (int *)malloc(sizeof(int) * size(first));
    int *ktore_kopia = ktore;
    element *lista = first;

    while(getchar() != '\n');
    printf("Podaj nazwę bądź jej początek do wyszukania - wielkość liter nie ma znaczenia (pusty wiersz wychodzi): ");
    fgets(nazwa, MAX_TOWAR_LENGHT + 1, stdin);
    if(nazwa[0] == '\n')
    {
        free(nazwa);
        return;
    }
    strtok(nazwa, "\n");
    printf("\nWyszukiwanie... %s\n", nazwa);

    while (first != NULL)
    {
        for (i = 0; i < strlen(first->twr->nazwa); i++)
        {
            if(tolower(first->twr->nazwa[i]) == tolower(nazwa[i]))
            {
                if (nazwa[i+1] == '\0')
                {
                    //to znaczy że pasują do siebie
                    ktore[ile] = j;
                    ile++;
                    i = strlen(first->twr->nazwa); //sprawdzić czy break zadziała
                }
            }
            else
                i = strlen(first->twr->nazwa);
        }

        first = first->next;
        j++;
    }
    if (_DEBUG)
    {
        ktore = ktore_kopia;
        printf("Towary do wyświetlenia:\n");
        for (i = 0; i < ile; i++)
            printf("%d\t%s\n", ktore[i], position(lista,ktore[i])->twr->nazwa);
    }

    wyswietl_towary(lista, ktore_kopia, ile);

    free (ktore_kopia);
    free (nazwa);
    return;
}
