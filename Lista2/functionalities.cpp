//
// Created by Mikołaj Machalski on 24/10/2023.
//

#include <algorithm>
#include "functionalities.h"
#include <iostream>
#include "CNumber.h"
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


    }
    return pi_Table_New;

}
void v_print_table(int *pi_Table,int iTable_Size){
    for (int ii = 0; ii <iTable_Size ; ++ii) {
        std::cout <<pi_Table[ii];
    }
    std::cout<<"\n";
} // void v_print_table(int *pi_Table,int iTable_Size)
void v_compare_2_equal_len_tables(int *pi_Table1,int *pi_Table2,int iMutualLen,int**pb_ReturnValue){
    int i=0;
    bool bFlag=true;
    int iReturn;
    while(bFlag && i!=iMutualLen){
        if(pi_Table1[i]!=pi_Table2[i]){
            bFlag=false;
            if(pi_Table1[i]>pi_Table2[i]){
                iReturn=1;
            }
            else{
                iReturn=-1;
            }
        }else{
            i++;

        }
    }
    if(bFlag){
        iReturn =0;
    }
    *pb_ReturnValue= new int(iReturn);
}


void  v_compareTo_by_abs(CNumber &pcFirst,CNumber &pcSecond, int** pb_ReturnValue) {
    bool bComparedLenGrt=pcFirst.get_iLength() > pcSecond.get_iLength();
    bool bComparedLenEq=pcFirst.get_iLength() == pcSecond.get_iLength();
    if(bComparedLenGrt){
        *pb_ReturnValue=new int(1);
    } else if (bComparedLenEq){
         v_compare_2_equal_len_tables(pcFirst.get_pi_Number(),pcSecond.get_pi_Number(),pcFirst.get_iLength(),pb_ReturnValue);
    } else{
        *pb_ReturnValue=new int(-1);
    }
}
int i_how_many_leading_x(int *pi_Table,int x, int iTable_Length){
    int iLeadingXs=0; // zrobic funckje na to....
    while(iLeadingXs < iTable_Length-1 && pi_Table[iLeadingXs] == x){
        iLeadingXs++;
    }
    return iLeadingXs;
}
