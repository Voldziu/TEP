//
// Created by Mikołaj Machalski on 16/10/2023.
//
#include <string>
#include "CTable.h"
#include <iostream>



CTable::CTable() {
    s_name=sConst_Name;
    std::cout <<"bezp: '"<<s_name<<"'\n";
    pi_Table = new int[iConst_Table_Len];
    iTable_Length=iConst_Table_Len;
}

CTable::CTable(std::string sName,int iTable_Len) {
    s_name=sName;
    std::cout <<"parametr: '"<<s_name<<"'\n";
    pi_Table = new int[iTable_Len];
    iTable_Length=iTable_Len;
}

CTable::CTable(CTable &pcOther) {
    s_name=pcOther.s_name +"_copy";
    std::cout <<"kopiuj: '"<<s_name<<"'\n";
    iTable_Length= pcOther.iTable_Length;
    pi_Table = pi_rewrite_table(pcOther.pi_Table,iTable_Length);
}

CTable::~CTable(){

    delete pi_Table;;
    std::cout <<"usuwam: '"<<s_name<<"'\n";
}

void CTable::v_set_name(std::string sName) {
    s_name=sName;
}

bool CTable::b_set_new_size(int iTable_Len_New) {
    if(iTable_Len_New<=0){
        return false;
    }
    int *pi_Swap;
    pi_Swap = pi_rewrite_table(pi_Table,iTable_Len_New);
    delete pi_Table;
    pi_Table=pi_Swap;
    return true;

}
CTable* CTable::pcClone() {

    return new CTable(*this);
}
void CTable::v_mod_tab(CTable *pc_Tab, int iNew_Size) {
    int *pi_Swap;
    pi_Swap= pi_rewrite_table((*pc_Tab).pi_Table,iNew_Size);
    delete (*pc_Tab).pi_Table;
    (*pc_Tab).pi_Table = pi_Swap;
    (*pc_Tab).iTable_Length=iNew_Size;

}

void CTable::v_mod_tab(CTable cTab, int iNew_Size) {
    int *pi_Swap;
    pi_Swap= pi_rewrite_table(cTab.pi_Table,iNew_Size);
    delete cTab.pi_Table;
    cTab.pi_Table = pi_Swap;
    cTab.iTable_Length=iNew_Size;
}

int* CTable::pi_rewrite_table(int *pi_Table,int iTab_Size){
    int *pi_Table_New = new int[iTab_Size];
    for (int ii = 0; ii <std::min(iTab_Size,iTable_Length) ; ++ii) {
        pi_Table_New[ii]=pi_Table[ii];

    }
    return pi_Table_New;

}
int CTable::get_iTable_Length() {
    return iTable_Length;
}
int* CTable::get_pi_Table() {
    return pi_Table;
}







