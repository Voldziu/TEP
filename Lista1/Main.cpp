//
// Created by Mikołaj Machalski on 16/10/2023.
//
#include "CTable.h"
#include <iostream>
#include "Zadanie1-2-3.h"

int main(){
//    int ***pppi_Table;
//    std::cout<< b_alloc_table_2_dim(pppi_Table,10,500);
//    std:: cout<<b_dealloc_table_2_dim(pppi_Table,100,500);
    CTable *ctable_param = new CTable("Luka",15);

    std::cout <<(*ctable_param).get_iTable_Length();
    for (int i = 0; i <(*ctable_param).get_iTable_Length() ; ++i) {
        std::cout <<(*ctable_param).get_pi_Table()[i];


    }
    (*ctable_param).v_mod_tab(ctable_param,10);
    std::cout <<(*ctable_param).get_iTable_Length();
    for (int i = 0; i <(*ctable_param).get_iTable_Length() ; ++i) {
        std::cout <<(*ctable_param).get_pi_Table()[i];

    }







    return 0;
}