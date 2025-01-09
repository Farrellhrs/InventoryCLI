#ifndef INVENTORY_H_INCLUDED
#define INVENTORY_H_INCLUDED

#define first(L) L.first
#define last(L) L.last
#define info(p) p -> info
#define next(p) p -> next
#define prev(P) P -> prev
#define item(p) p->item
#define next_item(p) p -> next_item
#define nil NULL
#define quantity(q) q->quantity

#include<iostream>

using namespace std;

const int nmax = 4;

typedef struct infotype_transaction{
    string date;
    string transaction_type;
    int invoice;
};
typedef struct infotype_item{
    string item_name;
    string item_category;
    int item_quantity;
};



typedef struct elm_item *adr_item;
typedef struct elm_relation1 *adr_relation1;
typedef struct elm_transaction *adr_transaction;


struct elm_transaction{
    infotype_transaction info;
    adr_transaction next;
    adr_relation1 item;
    adr_transaction prev;
};

struct elm_item{
    infotype_item info;
    adr_item next;
};
struct elm_relation1{
    adr_item next_item;
    adr_relation1 next;
    int quantity;
};


struct list_item{
    adr_item first;
};


struct list_transaction{
    adr_transaction first;
};

void createList_transaction(list_transaction &L);
void createList_item(list_item &L);
adr_item input_item(infotype_item &item);
adr_item naro_item(infotype_item &item);
adr_transaction input_transaction(infotype_transaction &transaction, list_item &L);
void insertfirst_transaction(list_transaction &L, adr_transaction P);
void insertfirst_item(list_item &L, adr_item P);
void advancedinsert_item(list_item &L);
void advanced_delete_item(list_item &L);
void advancedinsert_transaction(list_transaction &L, list_item &L1);
void advanced_delete_transaction(list_transaction &L, list_item &L1);
void deleteafter_item(list_item &L, adr_item prec, adr_item P);
void delete_item(list_item &L, adr_item target);

void deletefirst_relation(list_item &L, adr_transaction &q);
void delete_relation(list_item &L, adr_relation1 &target, adr_transaction &q);

void connect_update_transactiontoitem(list_item &L, adr_relation1 &k,adr_transaction &h, int u);
void print_item(list_item L);
void print_transaction(list_transaction L);
adr_item find_item(list_item L, string name); //berdasarkan nama
void show_item_category(list_item L, string category); //berdasarkan category
void show_item_quantity1(list_item L, int quantity); //yang kurang dari quantity
void show_item_quatity2(list_item L, int quantity); //yang lebih dari quantity
adr_transaction find_transaction(list_transaction, int invoice);
void show_transaction1(list_transaction, string typetransaction); //buat show transaction tipe masuk atau keluar
void show_transaction2(list_transaction, string date); //buat show transaction berdasarkan tanggal
void sortingstock_item_ascending(list_item &L);
void sortingstock_item_descending(list_item &L);
void mainmenu(list_transaction &L, list_item &L1);
void menu1(list_transaction &L, list_item &L1);
void menu2(list_transaction &L, list_item &L1);
void edit_item(list_item &L);
void edit_transaction(list_transaction &L, list_item &L1);
void advancedsearch_transaction(list_transaction L);



#endif // INVENTORY_H_INCLUDED

