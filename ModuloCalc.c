#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX 100

typedef struct wielomian
{
    int stopien;
    int wspolczynniki[MAX];

}Wielomian;

void menu();
void inicjalizacjaWspolczynnikow(Wielomian*);
int podstawaModularna();
void wpisywanie(Wielomian*, int);
void ustalStopien(Wielomian*);
void printowanie(Wielomian*);
void przepiszTablice(int*, int*);
void zerowanie(Wielomian*);
void dodawanie(Wielomian*, Wielomian*, int);
void odejmowanie(Wielomian*, Wielomian*, int);
void mnozenie(Wielomian*, Wielomian*, int);
void dzielenie(Wielomian*, Wielomian*, int);
void reszta(Wielomian*, Wielomian*, int);
int odwrotna(int, int, int);
int mod(int, int);
void kopiujRejestr(Wielomian*, Wielomian*);

int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}

void kopiujRejestr(Wielomian* src, Wielomian* dst) {
    int i;
    dst->stopien = src->stopien;
    for (i = 0; i < MAX; i++)
    {
        dst->wspolczynniki[i] = src->wspolczynniki[i];
    }
}

int odwrotna(int a, int b, int p) {
    int wynik = 0;
    while (wynik < p) {
        if (a == 0) {
            return 0;
        }
        if ((a * wynik) % p != b) {
            wynik++;
        }
        else {
            return wynik;
        }
    }
    return -1;
}

void menu()
{
    // menu przepisane z zalozen zadania
    puts("Wybierz opcje ktora cie interesuje:");
    puts("0.Zeruj rejestr.");
    puts("1.Dodaj do rejestru.");
    puts("2.Odejmij od rejestru.");
    puts("3.Pomnoz rejestr.");
    puts("4.Podziel rejestr (jesli mozliwe).");
    puts("5.Reszta z dzielenia przez rejestr (jesli mozliwe).");
    puts("6.Zapisz rejestr w pamieci.");
    puts("7.Odtworz rejestr z pamieci.");
    puts("8.Wyjscie");
}

void inicjalizacjaWspolczynnikow(Wielomian* w) {
    int i;
    for (i = 0; i < MAX; i++) {
        w->wspolczynniki[i] = 0;
    }
}

int podstawaModularna() {

    int p;
    printf("Podaj podstawe modularna:\n");
    scanf("%d", &p);
    return p;
}

void wpisywanie(Wielomian* w, int p)
{
    int i;
    printf("Podaj stopien wielomianu\n");
    scanf("%d", &w->stopien);
    if (p == 0) {
        for (i = 0; i <= w->stopien; i++)
        {
            printf("Podaj wspolczynnik wielomianu x^%d\n", i);
            scanf("%d", &w->wspolczynniki[i]);
        }
    }
    else {
        for (i = 0; i <= w->stopien; i++)
        {
            printf("Podaj wspolczynnik wielomianu x^%d\n", i);
            scanf("%d", &w->wspolczynniki[i]);
            w->wspolczynniki[i] = mod(w->wspolczynniki[i], p); /* uzywam swojej funkcji,
                                                               poniewaz kompilator C traktuje % jako operacje reszty,
                                                               a nie modulo */
        }
    }

}

void ustalStopien(Wielomian* w) {
    int i;
    w->stopien = 0;
    for (i = 0; i < MAX; i++) {
        if (w->wspolczynniki[i] != 0)
            w->stopien = i;
    }
}

void printowanie(Wielomian * w) {

    int i;
    printf("Wielomian: ");
    for (i = w->stopien; i > -1; i--)
    {
        if (i > 0)
            printf("%dx^%d + ", w->wspolczynniki[i], i);
        else
            printf("%dx^%d", w->wspolczynniki[i], i);
    }
    printf("\n");

}

void przepiszTablice(int* dest, int* src) {
    int i;
    for (i = 0; i < MAX; i++) {
        dest[i] = src[i];
    }
}

void zerowanie(Wielomian * w) {

    int i;
    for (i = w->stopien; i >= 0; i--)
    {
        w->wspolczynniki[i] = 0;
    }
    w->stopien = 0;

}

void dodawanie(Wielomian * w, Wielomian * u, int p) {

    int i = 0, j = 0;

    wpisywanie(u, p);
    if (p == 0)
    {
        for (i = 0; i < u->stopien + 1; i++)
            w->wspolczynniki[i] += u->wspolczynniki[i];
    }
    else
    {
        for (i = 0; i < u->stopien + 1; i++)
            w->wspolczynniki[i] = (w->wspolczynniki[i] + u->wspolczynniki[i]) % p;
    }
    ustalStopien(w);
    printowanie(w);
}

void odejmowanie(Wielomian * w, Wielomian * u, int p) {

    int i = 0, j = 0;

    wpisywanie(u, p);

    if (p == 0)
    {
        for (i = 0; i < u->stopien + 1; i++)
            w->wspolczynniki[i] -= u->wspolczynniki[i];
    }
    else
    {
        for (i = 0; i < u->stopien + 1; i++)
            w->wspolczynniki[i] = mod((w->wspolczynniki[i] - u->wspolczynniki[i]), p);
    }

    ustalStopien(&w);
    printowanie(w);
}

void mnozenie(Wielomian * w, Wielomian * u, int p) {

    int i = 0, j = 0;

    wpisywanie(u, p);

    if (p == 0)
    {
        for (i = 0; i < w->stopien + 1; i++)
            for (j = 0; j < w->stopien + 1; j++)
                w->wspolczynniki[i + j] = w->wspolczynniki[i] * u->wspolczynniki[j];
    }
    else
    {
        for (i = 0; i < w->stopien + 1; i++)
            for (j = 0; j < w->stopien + 1; j++)
                w->wspolczynniki[i + j] = (w->wspolczynniki[i] * u->wspolczynniki[j]) % p;
    }
    ustalStopien(w);
    printowanie(w);
}

void dzielenie(Wielomian * w, Wielomian * u, int p)
{
    int noweWartosci[MAX] = { 0 }; //inicjuje zerami
    int i, j, k = 0;
    wpisywanie(u, p);


    if (w->stopien >= u->stopien) {
        if (p == 0) {
            for (i = w->stopien; i > u->stopien - 1; i--) {
                noweWartosci[i - u->stopien] = w->wspolczynniki[i] / u->wspolczynniki[u->stopien];
                for (j = 0; j < u->stopien + 1; j++) {
                    w->wspolczynniki[i - j] = w->wspolczynniki[i - j] - (noweWartosci[i - u->stopien] * u->wspolczynniki[u->stopien - j]);
                }
            }
        }
        else {
            for (i = w->stopien; i > u->stopien - 1; i--) {
                k = odwrotna(w->wspolczynniki[i], u->wspolczynniki[u->stopien], p);
                if (k == -1) {
                    printf("Nie mozna podzielic wielomianow. Wspolczynniki sa niepodzielne w pierscieniu z%d", p);
                    return;
                }
                noweWartosci[i - u->stopien] = k;
                for (j = 0; j < u->stopien + 1; j++) {
                    w->wspolczynniki[i - j] = mod((w->wspolczynniki[i - j] - noweWartosci[i - u->stopien] * u->wspolczynniki[u->stopien - j]), p);
                }
            }
        }
        przepiszTablice(w->wspolczynniki, noweWartosci);
        ustalStopien(w);
    }
    else
    {
        zerowanie(&w);
        w->stopien = 0;
    }
    printowanie(w);
}

void reszta(Wielomian * w, Wielomian * u, int p) {
    int noweWartosci[MAX] = { 0 }; //inicjuje zerami
    int i, j, k = 0;
    wpisywanie(u, p);


    if (w->stopien >= u->stopien) {
        if (p == 0) {
            for (i = w->stopien; i > u->stopien - 1; i--) {
                noweWartosci[i - u->stopien] = w->wspolczynniki[i] / u->wspolczynniki[u->stopien];
                for (j = 0; j < u->stopien + 1; j++) {
                    w->wspolczynniki[i - j] = w->wspolczynniki[i - j] - (noweWartosci[i - u->stopien] * u->wspolczynniki[u->stopien - j]);
                }
            }
        }
        else {
            for (i = w->stopien; i > u->stopien - 1; i--) {
                k = odwrotna(w->wspolczynniki[i], u->wspolczynniki[u->stopien], p);
                if (k == -1) {
                    printf("Nie mozna podzielic wielomianow. Wspolczynniki sa niepodzielne w pierscieniu z%d", p);
                    return;
                }
                noweWartosci[i - u->stopien] = k;
                for (j = 0; j < u->stopien + 1; j++) {
                    w->wspolczynniki[i - j] = mod((w->wspolczynniki[i - j] - noweWartosci[i - u->stopien] * u->wspolczynniki[u->stopien - j]), p);
                }
            }
        }
        ustalStopien(w);
    }
    else
    {
        zerowanie(&w);
        w->stopien = 0;
    }
    printowanie(w);
}

int main()
{
    int wybor = 0;
    Wielomian w, u, r;
    int p = podstawaModularna();
    inicjalizacjaWspolczynnikow(&w);
    inicjalizacjaWspolczynnikow(&u);
    inicjalizacjaWspolczynnikow(&r);

    wpisywanie(&w, p);
    while (1) {
        menu();
        scanf(" %d", &wybor);
        switch (wybor) {
        case 0:
            zerowanie(&w);
            break;
        case 1:
            dodawanie(&w, &u, p);
            break;
        case 2:
            mnozenie(&w, &u, p);
            break;
        case 3:
            mnozenie(&w, &u, p);
            break;
        case 4:
            dzielenie(&w, &u, p);
            break;
        case 5:
            reszta(&w, &u, p);
            break;
        case 6:
            kopiujRejestr(&w, &r);
            break;
        case 7:
            kopiujRejestr(&r, &w);
            break;
        default:
            return 0;
        }
        system("pause");
    }
    return 0;

}