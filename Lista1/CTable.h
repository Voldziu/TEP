//
// Created by Mikołaj Machalski on 16/10/2023.
//
#include <string>
#ifndef LISTA1_CTABLE_H
#define LISTA1_CTABLE_H
const std::string sConst_Name="Basic_Table_Name";
const int iConst_Table_Len=15;
class CTable{
private:


    std::string s_name;
    int *pi_Table;
    int iTable_Length;
    int* pi_rewrite_table(int *pi_Table,int iTab_Size);

public:
    CTable();
    CTable(std::string sName,int iTable_Len);
    CTable(CTable &pcOther);
    ~CTable();
    void v_set_name(std::string sName);
    bool b_set_new_size(int iTable_Len);
    CTable* pcClone();
    void v_mod_tab(CTable *pc_Tab,int iNew_Size);
    void v_mod_tab(CTable cTab,int iNew_Size);
};
#endif //LISTA1_CTABLE_H
