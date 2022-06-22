#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct TWN
{
    int data;
    struct TWN* prev;
    struct TWN* next;
} TWN;

typedef struct
{
    TWN* start;
    int size;
} CTWL;

void ctwl_print(CTWL* list)
{
    TWN* tmp = list->start;
    int i;
    for ( i= 0; i < list->size; i++)
    {
        printf(" %d ", tmp->data);
        tmp = tmp->next;
    }
    printf("\n");
}

void ctwl_cur_step_right(CTWL* list)
{

    list->start = list->start->next;
}

TWN* ctwl_insert_right(CTWL* list, int val, TWN* predosli)
{
    TWN* new_item = (TWN*)malloc(sizeof(TWN));
    new_item->data = val;
    new_item->next = list->start;
    new_item->prev = predosli;
    predosli->next = new_item;
    return new_item;
}

CTWL* ctwl_sum_modulation(CTWL* a, CTWL* b)
{

    int dlzka3 = (a->size * b->size);
    CTWL* c = (CTWL*)malloc(dlzka3 * sizeof(CTWL));
    c->start = (TWN*)malloc(sizeof(TWN));
    c->size = dlzka3;
    TWN* act3 = (TWN*)malloc(sizeof(TWN));
    CTWL tmp1;
    CTWL tmp2;
    int id_data;
    int first_data;
    int x, y;

    tmp1 = *a;
    tmp2 = *b;

    TWN* pom1 = a->start;
    TWN* pom2 = b->start;
    TWN* predosli = NULL;
    TWN* actual = c->start;
    int i;
    for ( i = 1; i <= dlzka3; i++)
    {
    	int j; 
        x = i / tmp1.size;
        y = i % tmp1.size;

        pom1 = tmp1.start;
        for ( j = 0; j < x; j++)
        {
            ctwl_cur_step_right(a);
        }

        pom2 = tmp2.start;
        for ( j = 0; j < y; j++)
        {
            ctwl_cur_step_right(b);
        }

        id_data = a->start->data + b->start->data;

        if (i == 1)
        {
            actual->data = id_data;
            actual->next = (TWN*)malloc(sizeof(TWN));
            actual->prev = NULL;
            predosli = actual;
            actual = actual->next;
        }
        else if (i == dlzka3)
        {
            actual->data = id_data;
            actual->next = c->start;
            actual->prev = predosli;
            c->start->prev = actual;
        }
        else
        {
            actual->data = id_data;
            actual->next = (TWN*)malloc(sizeof(TWN));
            actual->prev = predosli;
            predosli = actual;
            actual = actual->next;
        }
    }
    a->start = pom1;
    b->start = pom2;

    return c;
}

int main()
{

    int dlzka1 = 0, dlzka2 = 0, cislo = 0;
    int i;

    CTWL* a = (CTWL*)malloc(sizeof(CTWL));
    CTWL* b = (CTWL*)malloc(sizeof(CTWL));

    TWN* act1 = (TWN*)malloc(sizeof(TWN)), * first1;
    TWN* act2 = (TWN*)malloc(sizeof(TWN)), * first2;

    printf("Zadaj dlzku prveho dinamickeho pola: ");
    scanf("%d", &dlzka1);

    printf("Zadaj dlzku druheho dinamickeho pola: ");
    scanf("%d", &dlzka2);

    a->size = dlzka1;
    b->size = dlzka2;

    // Naplnim prvy zoznam

    printf("Zadaj prvky prveho pola:");
    scanf("%d", &cislo);
    act1->data = cislo;
    act1->next = NULL;
    act1->prev = NULL;
    first1 = act1;
    a->start = first1;
    for (i = 1; i < dlzka1; i++)
    {
        scanf("%d", &cislo);
        act1 = ctwl_insert_right(a, cislo, act1);
        a->start->prev = act1;
    }

    // Naplnim druhy zoznam

    printf("Zadaj prvky druheho pola:");
    scanf("%d", &cislo);
    act2->data = cislo;
    act2->next = NULL;
    act2->prev = NULL;
    first2 = act2;
    b->start = first2;
    for (i = 1; i < dlzka2; i++)
    {
        scanf("%d", &cislo);
        act2 = ctwl_insert_right(b, cislo, act2);
        b->start->prev = act2;
    }

    CTWL* c = ctwl_sum_modulation(a, b);

    printf("Zlozky listu A:\n");
    ctwl_print(a);
    printf("Zlozky listu B:\n");
    ctwl_print(b);
    printf("Zlozky listu C:\n");
    ctwl_print(c);
}
