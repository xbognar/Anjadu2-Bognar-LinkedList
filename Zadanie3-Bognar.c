#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct TWN {
    int data;
    struct TWN* prev;
    struct TWN* next;
}TWN;

typedef struct {
    TWN* start;
    int size;
}CTWL;

// Funkcia na automaticke naplnenie NODE-ov 

TWN* ADD(TWN* predosli, int num, CTWL* list)
{

    TWN* new_item = (TWN*)malloc(sizeof(TWN));
    new_item->data = num;
    new_item->next = list->start;
    new_item->prev = predosli;
    predosli->next = new_item;
    return new_item;
}

// Suctova modulacia dvoch zoznamov 

CTWL* ctwl_sum_modulation(CTWL a, CTWL b) {

    int dlzka3 = (a.size * b.size);
    CTWL* c = (CTWL*)malloc(dlzka3 * sizeof(CTWL));
    c->start = (TWN*)malloc(sizeof(TWN));
    c->size = dlzka3;
    TWN* act3 = (TWN*)malloc(sizeof(TWN));
    CTWL* tmp1;
    CTWL* tmp2;
    int id_data;
    int first_data;
    int x, y;

    tmp1 = &a;
    tmp2 = &b;

    TWN* pom1;
    TWN* pom2;
    TWN* predosli = NULL;
    TWN* actual = c->start;
    for (int i = 1; i <= dlzka3; i++) {
        x = i / tmp1->size;
        y = i % tmp1->size;

        pom1 = tmp1->start;
        for (int j = 0; j < x; j++) {
            pom1 = pom1->next;
        }

        pom2 = tmp2->start;
        for (int j = 0; j < y; j++) {
            pom2 = pom2->next;
        }

        id_data =pom1->data + pom2->data;

        if (i == 1) {
            actual->data = id_data;
            actual->next = (TWN*)malloc(sizeof(TWN));
            actual->prev = NULL;
            predosli = actual;
            actual = actual->next;
        }
        else if (i == dlzka3) {
            actual->data = id_data;
            actual->next = c->start;
            actual->prev = predosli;
            c->start->prev = actual;
        }
        else {
            actual->data = id_data;
            actual->next = (TWN*)malloc(sizeof(TWN));
            actual->prev = predosli;
            predosli = actual;
            actual = actual->next;
        }
        

    }

    return c;
}

// Vypis

void print_list(CTWL* list) {
    TWN* tmp = list->start;
    for (int i = 0; i < list->size; i++) {
        printf(" %d ", tmp->data);
        tmp = tmp->next;

    }
    printf("\n");
}

int main() {

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
        act1 = ADD(act1, cislo, a);
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
        act2 = ADD(act2, cislo, b);
        b->start->prev = act2;
    }

    CTWL* c = ctwl_sum_modulation(*a, *b);

    printf("Zlozky listu A:\n");
    print_list(a);
    printf("Zlozky listu B:\n");
    print_list(b);
    printf("Zlozky listu C:\n");
    print_list(c);

}