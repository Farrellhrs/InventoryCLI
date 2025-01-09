#include <iostream>
#include "inventory.h"
using namespace std;

int main()
{
    list_item L1;
    list_transaction L;
    createList_item(L1);
    createList_transaction(L);
    mainmenu(L,L1);
    return 0;
}
