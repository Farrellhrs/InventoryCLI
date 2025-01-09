#include <iostream>
#include "inventory.h"
using namespace std;

void createList_transaction(list_transaction &L){
    first(L) = nil;
}
void createList_item(list_item &L){
    first(L) = nil;
}
adr_item input_item(infotype_item &item){
    cout << "input nama item: ";
    cin >> item.item_name;
    cout << "Input kategori item: ";
    cin >> item.item_category;
    cout << "input quantity item: ";
    cin >> item.item_quantity;
    adr_item p;
    p = new elm_item;
    next(p) = nil;
    info(p) = item;
    return p;
};

adr_item naro_item(infotype_item &item){
    adr_item p;
    p = new elm_item;
    next(p) = nil;
    info(p) = item;
    return p;
}

//perubahan konsep nanti dibubah
adr_transaction input_transaction(infotype_transaction &transaction, list_item &L){
    cout << "tipe transaksi (masuk/keluar): ";
    cin >> transaction.transaction_type;
    cout << "input Tanggal: ";
    cin >> transaction.date;
    cout << "input invoice: ";
    cin >> transaction.invoice;
    adr_transaction p;
    p = new elm_transaction;
    next(p) = nil;
    prev(p) = nil;
    item(p) = nil;
    info(p) = transaction;
    cout << "Ada berapa barang yang ingin diinput? (maksimal 5): ";
    int a;
    cin >> a;
    int i = 1;
    for (i=1;i<=(a);i++){
        adr_relation1 k = new elm_relation1;
        next(k) = nil;
        next_item(k) = nil;
        connect_update_transactiontoitem(L, k, p, i);
        if (item(p)==nil){
            item(p) = k;
        }else {
            adr_relation1 q;
            q = item(p);
            while (next(q)!=nil){
                q = next(q);
            }
            next(q) = k;
        }
    }
    return p;
}

void insertfirst_transaction(list_transaction &L, adr_transaction P){
    if (first(L)==nil){
        first(L) = P;
        prev(P) = P;
    } else {
        next(P) = first(L);
        prev(first(L)) = P;
        first(L) = P;
    }
};
void insertfirst_item(list_item &L, adr_item P){
    if (first(L)==nil){
        first(L) = P;
    } else {
        next(P) = first(L);
        first(L) = P;
    }
};

void advancedinsert_item(list_item &L){
    infotype_item item;
    adr_item p = input_item(item);
    insertfirst_item(L,p);
};

void advanced_delete_item(list_item &L){
    cout << "---------------------------------------"<< endl;
    cout << "Masukan Nama Item yang ingin didelete: ";
    string nama;
    cin >> nama;
    adr_item p = find_item(L,nama);
    if (p==nil){
        cout << "Item tidak ditemukan";
    } else {
        delete_item(L,p);
        cout << "item berhasil di delete";
    }
};


void advancedinsert_transaction(list_transaction &L, list_item &L1){
    infotype_transaction transaction;
    adr_transaction p = input_transaction(transaction,L1);
    insertfirst_transaction(L, p);
};

void advanced_delete_transaction(list_transaction &L, list_item &L1){
    int invoice;
    cout << "---------------------------------------" << endl;
    cout << "Masukan nomor invoice yang ingin dihapus: ";
    cin >> invoice;
    adr_transaction h = find_transaction(L, invoice);
    adr_transaction temp = prev(h);
    if (h==nil){
        cout << "Transaksi tidak ditemukan!";
    } else {
        while (item(h)!=nil){
            deletefirst_relation(L1,h);
        }
        next(temp) = next(h);
        prev(next(h)) = temp;
        next(h) = nil;
        prev(h) = nil;
        cout << "Transaksi sudah didelete!";
    }
};

void deleteafter_item(list_item &L, adr_item prec, adr_item P){
    P = next(prec);
    next(prec) = next(P);
    next(P) = nil;
};

void delete_item(list_item &L, adr_item target){
    adr_item p = first(L);
    while (next(p)!= target){
        p = next(p);
    }
    adr_item buangan;
    deleteafter_item(L,p,buangan);
};

void deletefirst_relation(list_item &L, adr_transaction &q){
    adr_relation1 p = item(q);
    if (next(p)==nil){
        adr_item h;
        h = next_item(p);
        next_item(p) = nil;
        info(h).item_quantity = info(h).item_quantity - quantity(p);
        next(h) = nil;
        item(q) = nil;
    }else{
        adr_relation1 k = next(p);
        item(q) = k;
        adr_item h = next_item(p);
        next(p) = nil;
        next_item(p) = nil;
        info(h).item_quantity = info(h).item_quantity - quantity(p);
        next(h) = nil;
    }
};

void delete_relation(list_item &L, adr_relation1 &target, adr_transaction &q){
    adr_relation1 h = item(q);
    adr_relation1 p = target;
    if (next(h)==nil){
        deletefirst_relation(L,q);
    }else {
        while (next(h)!=p){
            h = next(h);
        }
        target = h;
        next(h) = next(p);
        adr_item y = next_item(p);
        info(y).item_quantity = info(y).item_quantity - quantity(p);
        next_item(p) = nil;
        next(p) = nil;
        delete p;
    }
};

void connect_update_transactiontoitem(list_item &L, adr_relation1 &k, adr_transaction &h, int u){
    string nama;
    string category;
    cout << "---------------------------------------" << endl;
    cout << "input nama barang ke "<< u<< " yang baru: ";
    cin >> nama;
    cout << "Jumlah barang: ";
    cin >> quantity(k);
    cout << "Category Barang: ";
    cin >> category;
    adr_item p = find_item(L,nama);
    if (p==nil){
        infotype_item itembaru;
        itembaru.item_category = category;
        itembaru.item_name = nama;
        itembaru.item_quantity = quantity(k);
        adr_item j = naro_item(itembaru);
        insertfirst_item(L,j);
        next_item(k) = j;
    } else {
        if (info(h).transaction_type == "masuk"){
            info(p).item_quantity = info(p).item_quantity + quantity(k);
            next_item(k) = p;
        }else {
            info(p).item_quantity = info(p).item_quantity - quantity(k);
            next_item(k) = p;
        }
    }
};

adr_item find_item(list_item L, string name){
    adr_item p = first(L);
    while(p != nil){
        if(info(p).item_name == name){
            return p;
        }
        p = next(p);
    }
    return nil;
}
void show_item_category(list_item L, string category){
    adr_item p = first(L);
    int i = 1;
    cout << "Berikut item dengan kategori " << category << endl;
    cout << "------------------------------" << endl;
    while(p != nil){
      if(info(p).item_category == category){
        cout << "Item: " << i <<endl;
        cout << "Nama: " << info(p).item_name << endl;
        cout << "Quantity: " << info(p).item_quantity << endl;
        cout << "Category: "<<info(p).item_category << endl;
        cout << endl;
      }
      p = next(p);
    }
}

void show_item_quantity1(list_item L, int quantity){
    adr_item p = first(L);
    int i = 1;
    cout << "Berikut item dengan quantity kurang dari" << quantity << endl;
    cout << "------------------------------" << endl;
    while(p != nil){
      if(info(p).item_quantity < quantity){
        cout << "Item: " << i <<endl;
        cout << "Nama: "<< info(p).item_name << endl;
        cout << "Quantity: "<< info(p).item_quantity << endl;
        cout << "Category: "<< info(p).item_category << endl;
        cout << endl;
      }
      p = next(p);
    }
}
void show_item_quatity2(list_item L, int quantity){
adr_item p = first(L);
    int i = 1;
    cout << "Berikut item dengan quantity lebih dari" << quantity << endl;
    cout << "------------------------------" << endl;
    while(p != nil){
      if(info(p).item_quantity > quantity){
        cout << "Item: " << i <<endl;
        cout << "Nama: "<< info(p).item_name << endl;
        cout << "Quantity: "<< info(p).item_quantity << endl;
        cout << "Category: "<< info(p).item_category << endl;
        cout << endl;
      }
      p = next(p);
    }
}

adr_transaction find_transaction(list_transaction L, int invoice){
    adr_transaction p = first(L);
    while(p != nil){
        if(info(p).invoice == invoice){
            return p;
        }
    }
    return nil;
}

void show_transaction1(list_transaction L, string typetransaction){
    adr_transaction p = first(L);
    int i = 1;
    while(p != nil){
        if(info(p).transaction_type == typetransaction){
            cout << "Berikut transaksi dengan tipe" << typetransaction << endl;
            cout << "Transaction " << i <<endl;
            cout << "Invoice: "<< info(p).invoice << endl;
            cout << "Date: "<<info(p).date << endl;
            cout << "Transaction type: "<<info(p).transaction_type << endl;
            cout <<"-----------------------------------" << endl;
            adr_relation1 q = item(p);
            while(q != nil){
                cout << "Quantitiy :" << quantity(q) << endl;
                cout << "Item Name :" << info(next_item(q)).item_name << endl;
                cout << "Item Category :" <<info(next_item(q)).item_category<< endl;
                q = next(q);
            };
        }
        p = next(p);
    }
}

void show_transaction2(list_transaction L, string date){
    adr_transaction p = first(L);
    int i = 1;
    while(p != nil){
        if(info(p).date == date){
            cout << "Berikut transaksi dengan tanggal" << date << endl;
            cout << "Transaction " << i <<endl;
            cout << "Invoice: "<< info(p).invoice << endl;
            cout << "Date: "<<info(p).date << endl;
            cout << "Transaction type: "<<info(p).transaction_type << endl;
            cout <<"-----------------------------------" << endl;
            adr_relation1 q = item(p);
            while(q != nil){
                cout << "Quantitiy :" << quantity(q) << endl;
                cout << "Item Name :" << info(next_item(q)).item_name << endl;
                cout << "Item Category :" <<info(next_item(q)).item_category<< endl;
                q = next(q);
            };
            i++;
        }
        p = next(p);
    }
}

void print_item(list_item L){
    adr_item p = first(L);
    int i = 1;
    cout <<"-----------------------------------" << endl;
    cout << "List Item" << endl;
    while(p != nil){
        cout << "Item " << i <<endl;
        cout << "Nama: "<< info(p).item_name << endl;
        cout << "Quantity: "<< info(p).item_quantity << endl;
        cout << "Category: "<< info(p).item_category << endl;

        p = next(p);
    }
}

void print_transaction(list_transaction L){
    adr_transaction p = first(L);
    int i = 1;
    while(p != nil){
        cout << "List Transaksi" << endl;
        cout << "Transaction " << i <<endl;
        cout << "Invoice: "<< info(p).invoice << endl;
        cout << "Date: "<<info(p).date << endl;
        cout << "Transaction type: "<<info(p).transaction_type << endl;
        cout <<"-----------------------------------" << endl;
            adr_relation1 q = item(p);
            while(q != nil){
                cout << "Quantitiy :" << quantity(q) << endl;
                cout << "Item Name :" << info(next_item(q)).item_name << endl;
                cout << "Item Category :" <<info(next_item(q)).item_category<< endl;
                q = next(q);
            };
        p = next(p);
    }
}

void sortingstock_item_ascending(list_item &L){
    adr_item p,q,idx;
    infotype_item temp;
    p = first(L);
    while (p!=nil){
        idx = p;
        q = next(p);
        while (q!=nil){
            if (info(q).item_quantity <info(idx).item_quantity){
                idx = q;
            }
            q = next(q);
        }
        temp = info(p);
        info(p) = info(idx);
        info(idx) = temp;
        p = next(p);
    }
}
void sortingstock_item_descending(list_item &L){
        adr_item p,q,idx;
    infotype_item temp;
    p = first(L);
    while (p!=nil){
        idx = p;
        q = next(p);
        while (q!=nil){
            if (info(q).item_quantity >info(idx).item_quantity){
                idx = q;
            }
            q = next(q);
        }
        temp = info(p);
        info(p) = info(idx);
        info(idx) = temp;
        p = next(p);
    }
}

void edit_item(list_item &L){
    cout << "Nama Item yang ingin diedit? ";
    string nama;
    cin >> nama;
    adr_item h = find_item(L,nama);
    if (h==nil){
        cout << "nama item tidak ditemukan";
    } else {
        cout << "input nama item yang baru";
        cin >> info(h).item_name;
        cout << "input quantity yang baru";
        cin >> info(h).item_quantity;
        cout << "input category yang baru";
        cin >> info(h).item_category;
    }
}
void edit_transaction(list_transaction &L, list_item &L1){
    string jwb;
    cout << "invoice yang ingin diedit?";
    int invoice;
    cin >> invoice;
    adr_transaction h = find_transaction(L, invoice);
    if (h==nil){
        cout << "invoice tidak ditemukan";
    } else{
        cout << "apakah ingin mengubah date dan type transaction? (yes or no)";
        cin >> jwb;
        if (jwb=="yes"){
            cout << "input date item yang baru";
            cin >> info(h).date;
            cout << "input transaction type yang baru";
            cin >> info(h).transaction_type;
        }
        cout << "apakah ingin mengubah nama barang? (yes or no)";
        cin >> jwb;
        if (jwb == "yes"){
            adr_relation1 k;
            k = item(h);
            int u = 1;
            while (k!=nil){
                connect_update_transactiontoitem(L1,k, h, u);
                k = next(k);
                u = u+1;
            }
        }
    }
}

void advancedsearch_transaction(list_transaction L){
    int invoice;
    cout << "Invoice transaction yang ingin dicari? ";
    cin >> invoice;
    adr_transaction f = find_transaction(L, invoice);
    if (f == nil){
        cout << "Transaction invoice tidak ditemukan";
    } else {
        cout << "----------------------------" << endl;
        cout << "          Invoice           " << endl;
        cout << "----------------------------" << endl;

        cout << "Invoice    : " << info(f).invoice<<endl;
        cout << "Date       : " <<info(f).date<<endl;
        cout << "Type       : " << info(f).transaction_type<<endl;
        int iterasi = 1;
        adr_relation1 x = item(f);
        while (x!=nil){
            cout << "list item ke "<< iterasi<< ": " << info(next_item(x)).item_name<<endl;
            x = next(x);
        }
    }
}

void menu1(list_transaction &L, list_item &L1){
    int pilih;
    cout << "----------------------------" << endl;
    cout << "   Selamat Datang Admin   " << endl;
    cout << "       Menu Transaksi         " << endl;
    cout << "----------------------------" << endl;
    do {
        cout << "Daftar menu :" << endl;
        cout << "1. Search invoice" << endl;
        cout << "2. Edit transaction" << endl;
        cout << "0. untuk keluar menu transaksi" << endl;
        cout << "Silakan pilih menu :";
        cin >> pilih;
        if(pilih == 1){
            advancedsearch_transaction(L);
        }else if(pilih == 2){
            cout << "----------------------------" << endl;
            cout << "Daftar menu :" << endl;
            cout << "1. Add transaction" << endl;
            cout << "2. Edit transaction" << endl;
            cout << "2. Delete transaction" << endl;
            cout << "0. untuk keluar menu transaksi" << endl;
            cout << "Silakan pilih menu :";
            cin >> pilih;
            if(pilih == 1){
                advancedinsert_transaction(L, L1);
            }else if(pilih == 2){
                edit_transaction(L,L1);
            }else if(pilih == 3){
                advanced_delete_transaction(L,L1);
            }else if(pilih == 0){
                menu1(L,L1);
            }
        }
    }while(pilih != 0);
}

void menu2(list_transaction &L, list_item &L1){
    int pilih;
    cout << "----------------------------" << endl;
    cout << "   Selamat Datang Admin   " << endl;
    cout << "       Menu Item         " << endl;
    cout << "----------------------------" << endl;
     do {
        cout << "Daftar menu :" << endl;
        cout << "1. Show Item by category" << endl;
        cout << "2. Search Item by name" << endl;
        cout << "3. Show Item sorted Ascending" << endl;
        cout << "4. Show Item sorted Descending" << endl;
        cout << "5. Show item less than a Quantity" << endl;
        cout << "6. Show item more than a Quantity" << endl;
        cout << "7. Edit Item" << endl;
        cout << "0. untuk keluar" << endl;
        cout << "Silakan pilih menu :";
        cin >> pilih;
        if(pilih == 1){
            string category;
            cout << "Kategori yang ingin dicari? ";
            cin >> category;
            show_item_category(L1,category);
        }else if(pilih == 2){
            adr_item p;
            string nama;
            cout << "Nama item yang ingin dicari? ";
            cin >> nama;
            p = find_item(L1,nama);
            if (p==nil){
                cout << "item tidak ditemukan";
            } else {
                cout << "Item name:" <<info(p).item_name<<endl;
                cout << "Item Category: " <<info(p).item_category<<endl;
                cout<< "Item Quantity" <<info(p).item_quantity<<endl;
            }
        }else if(pilih == 3){
            sortingstock_item_ascending(L1);
        }else if(pilih == 4){
            sortingstock_item_descending(L1);
        }else if(pilih == 5){
            int quantityitem;
            cout << "input the quantity for show item less than a quantity: ";
            cin >> quantityitem;
            show_item_quantity1(L1,quantityitem);
        }else if(pilih == 6){
            int quantityitem;
            cout << "input the quantity for show item more than a quantity: ";
            cin >> quantityitem;
            show_item_quatity2(L1,quantityitem);
        }else if(pilih == 7){
             cout << "----------------------------" << endl;
            cout << "Daftar menu :" << endl;
            cout << "1. Add item" << endl;
            cout << "2. Edit item" << endl;
            cout << "2. Delete tem" << endl;
            cout << "0. untuk keluar menu item" << endl;
            cout << "Silakan pilih menu :";
            cin >> pilih;
            if(pilih == 1){
                advancedinsert_item(L1);
            }else if(pilih == 2){
                edit_item(L1);
            }else if(pilih == 3){
                advanced_delete_item(L1);
            }else if(pilih == 0){
                menu2(L,L1);
            }
        }
    }while(pilih !=0);
}

void mainmenu(list_transaction &L, list_item &L1){
    int pilih;
    cout << "----------------------------" << endl;
    cout << "   Selamat Datang Admin   " << endl;
    cout << "         Main Menu          " << endl;
    cout << "----------------------------" << endl;


    do {
        cout << "Daftar menu :" << endl;
        cout << "1. Tranaksi" << endl;
        cout << "2. Barang" << endl;
        cout << "0. untuk keluar" << endl;
        cout << "Silakan pilih menu :";
        cin >> pilih;
        if(pilih == 1){
            menu1(L,L1);
        }else if(pilih == 2){
            menu2(L,L1);
        }
    }while(pilih !=0);

}
