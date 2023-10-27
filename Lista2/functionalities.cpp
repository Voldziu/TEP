//
// Created by Mikołaj Machalski on 24/10/2023.
//

#include <algorithm>
#include "functionalities.h"
#include <iostream>
using namespace std;
int* pi_rewrite_table(int *pi_Table,int iTab_Size_New,int iTable_Length) {
    int *pi_Table_New = new int[iTab_Size_New];
    for (int ii = 0; ii < std::min(iTab_Size_New, iTable_Length); ++ii) {
        pi_Table_New[ii] = pi_Table[ii];

    }
    return pi_Table_New;
}

int* pi_rewrite_table_from_back(int *pi_Table,int iTab_Size_New,int iTable_Length){
    int *pi_Table_New= new int[iTab_Size_New];
    for (int ii = 0;  ii <std::min(iTab_Size_New,iTable_Length) ; ++ii) {
        pi_Table_New[iTab_Size_New-1-ii] = pi_Table[iTable_Length-1-ii];
        cout<<pi_Table[iTable_Length-1-ii]<<endl;

    }
    return pi_Table_New;

}
void v_print_table(int *pi_Table,int iTable_Size){
    for (int ii = 0; ii <iTable_Size ; ++ii) {
        std::cout <<pi_Table[ii];
    }
    std::cout<<"\n";
} // void v_print_table(int *pi_Table,int iTable_Size)
bool b_compare_2_equal_len_tables(int *pi_Table1,int *pi_Table2,int iMutualLen){ // true => 1st greater or equal than 2nd
    int i=0;
    bool bFlag=true;
    bool bReturn;
    while(bFlag && i!=iMutualLen){
        if(pi_Table1[i]!=pi_Table2[i]){
            bFlag=false;
            if(pi_Table1[i]>pi_Table2[i]){
                bReturn=true;
            }
            else{
                bReturn=false;
            }
        }else{
            i++;

        }
    }
    if(bFlag){
        return true;
    } else{
        return bReturn;
    }
}
