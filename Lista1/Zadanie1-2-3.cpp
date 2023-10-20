#include <iostream>
#include "Zadanie1-2-3.h"
#include "Constants.h"

void v_alloc_table_fill_34(int iSize){
    if(iSize<=0 ){
        std::cout <<"Come on, give me a positive integer!" << std::endl;
        return;
    } else {
        int *pi_table;
        pi_table = new int[iSize];
        v_fill_table(pi_table,iSize);
        v_print_table(pi_table,iSize);
        delete pi_table;
    }
} // void v_alloc_table_fill_34(int iSize)

void v_print_table(int *pi_Table,int iTable_Size){
    for (int ii = 0; ii <iTable_Size ; ++ii) {
        std::cout <<pi_Table[ii]<<"\t";
    }
    std::cout<<"\n";
} // void v_print_table(int *pi_Table,int iTable_Size)

void v_fill_table(int *pi_Table,int iTable_Size){
    for (int ij = 0; ij <iTable_Size ; ++ij) {
        pi_Table[ij]=iConst_34;
    }
} // void v_fill_table(int *pi_Table,int iTable_Size)

bool b_alloc_table_2_dim(int ***pi_Table, int iSize_X, int iSize_Y){
    if(iSize_X <=0 || iSize_Y<=0) { // check if any of dimension is less or equal 0
        return false;
    } else {
        *pi_Table = new int*[iSize_X];
        for (int ii = 0; ii <iSize_X ; ++ii) { // alocate every row
            (*pi_Table)[ii]= new int[iSize_Y];
            }
    }
    return true; // if false was not returned, return true
} // bool b_alloc_table_2_dim(int ***pi_Table, int iSize_X, int iSize_Y)

bool b_dealloc_table_2_dim(int **pi_Table, int iSize_X, int iSize_Y){ // no iSize_Y needed? no *** needed, only **
    if(iSize_X<=0){
        return false;
    } else{
        for (int ix = 0; ix <iSize_X ; ++ix) {
            delete pi_Table[ix];
        }
        delete pi_Table;
    }
    return true;
} //bool b_dealloc_table_2_dim(int ***pi_Table, int iSize_X, int iSize_Y)








