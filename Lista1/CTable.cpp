//
// Created by Mikołaj Machalski on 16/10/2023.
//
#include <string>
#include "CTable.h"
#include <iostream>
#include "Constants.h"
#include "Functionalities.h"



CTable::CTable() {
    s_name=sConst_Name;
    std::cout <<sBezparamtr_Prompt+"'"<<s_name<<"'\n";
    pi_Table = new int[iConst_Table_Len];
    iTable_Length=iConst_Table_Len;
}

CTable::CTable(std::string sName,int iTable_Len) {
    s_name=sName;
    std::cout <<sParam_Prompt+"'"<<s_name<<"'\n";

    if(iTable_Len<=0){
        iTable_Length=iConst_Table_Len;
    } else{
        iTable_Length=iTable_Len;
    }
    pi_Table = new int[iTable_Len];

}

CTable::CTable(const CTable &pcOther) {
    s_name=pcOther.s_name +"_copy";
    std::cout <<sKopiuj_Prompt+"'"<<s_name<<"'\n";
    iTable_Length= pcOther.iTable_Length;
    pi_Table = pi_rewrite_table(pcOther.pi_Table, iTable_Length, iTable_Length);
}

CTable::~CTable(){

    delete pi_Table;;
    std::cout <<sUsuwam_Prompt+"'"<<s_name<<"'\n";
}

void CTable::v_set_name(std::string sName) {
    s_name=sName;
}

bool CTable::b_set_new_size(int iTable_Len_New) {
    if(iTable_Len_New<=0){
        return false;
    }
    int *pi_Swap;
    pi_Swap = pi_rewrite_table(pi_Table,iTable_Len_New,iTable_Length);
    delete pi_Table;
    pi_Table=pi_Swap;
    iTable_Length=iTable_Len_New;
    return true;

}
bool CTable::b_set_new_table(int *pi_Table_New,int iTable_Len_New) {
    if(iTable_Len_New<=0){
        return false;
    }

    int *pi_Swap = pi_rewrite_table(pi_Table_New,iTable_Len_New,iTable_Len_New);
    delete pi_Table;
    pi_Table=pi_Swap;
    iTable_Length=iTable_Len_New;
    return true;

}
void CTable::v_double_size(CTable** pCTable_Other) {


    *pCTable_Other = new CTable(s_name+"_double",iTable_Length*2);
    for (int ii = 0; ii <2 ; ++ii) {
        for (int ij = 0; ij <iTable_Length ; ++ij) {
            (**pCTable_Other).pi_Table[iTable_Length*ii+ij]=pi_Table[ij];
        }
    }
}
CTable* CTable::pcClone() {

    return new CTable(*this);
}



int CTable::get_iTable_Length() {
    return iTable_Length;
}
int* CTable::get_pi_Table() {
    return pi_Table;
}







