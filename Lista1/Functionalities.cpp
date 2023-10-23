//
// Created by Mikołaj Machalski on 20/10/2023.
#include "CTable.h";
#include "Functionalities.h";

void v_mod_tab(CTable *pc_Tab, int iNew_Size) {
    (*pc_Tab).b_set_new_size(iNew_Size);
} // void v_mod_tab(CTable *pc_Tab, int iNew_Size)

void v_mod_tab(CTable cTab, int iNew_Size) {
    cTab.b_set_new_size(iNew_Size);
} // void v_mod_tab(CTable cTab, int iNew_Size)

int* pi_rewrite_table(int *pi_Table,int iTab_Size_New,int iTable_Length){
    int *pi_Table_New = new int[iTab_Size_New];
    for (int ii = 0; ii <std::min(iTab_Size_New,iTable_Length) ; ++ii) {
        pi_Table_New[ii]=pi_Table[ii];

    }
    return pi_Table_New;

} // int* pi_rewrite_table(int **pi_Table,int iTab_Size_New,int iTable_Length)

