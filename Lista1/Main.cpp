//
// Created by Mikołaj Machalski on 16/10/2023.
//
#include "CTable.h"
#include <iostream>
#include "Zadanie1-2-3.h"
#include "Functionalities.h"
using namespace std;


int main(){
    int **ppi_Table;
    std::cout<< b_alloc_table_2_dim(&ppi_Table,10,500) <<endl;
    std:: cout<<b_dealloc_table_2_dim(ppi_Table,10,500)<<endl;
    CTable *ctable_param = new CTable("Luka",15);
    CTable *ctable_default = new CTable();
    std::cout <<(*ctable_param).get_iTable_Length()<<endl;

    v_mod_tab(ctable_param,10);
    std::cout <<(*ctable_param).get_iTable_Length()<<endl;
    for (int i = 0; i <(*ctable_param).get_iTable_Length() ; ++i) {
        std::cout <<(*ctable_param).get_pi_Table()[i];

    }







    return 0;
}