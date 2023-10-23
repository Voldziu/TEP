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
    CTable *ctable_default_array = new CTable[10];
    delete [] ctable_default_array;
    CTable static_array[10];
    std::cout <<(*ctable_param).get_iTable_Length()<<endl;

    v_mod_tab(ctable_param,10);
    std::cout <<(*ctable_param).get_iTable_Length()<<endl;
    for (int i = 0; i <(*ctable_param).get_iTable_Length() ; ++i) {
        std::cout <<(*ctable_param).get_pi_Table()[i];

    }
    cout<<"\n";
    CTable ctable_static_default;
    int* ctab;
    ctab = new int[4];
    ctab[0]=1;
    ctab[1]=2;
    ctab[2]=3;
    ctab[3]=4;

    ctable_static_default.b_set_new_table(ctab,4);
    v_print_table(ctable_static_default.get_pi_Table(),ctable_static_default.get_iTable_Length());
    CTable *pc_doub;
    ctable_static_default.v_double_size(&pc_doub);
    v_print_table((*pc_doub).get_pi_Table(), (*pc_doub).get_iTable_Length());
    delete pc_doub;







    return 0;
}