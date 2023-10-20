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


public:
    CTable();
    CTable(std::string sName,int iTable_Len);
    CTable(CTable &pcOther);
    ~CTable();
    void v_set_name(std::string sName);
    bool b_set_new_size(int iTable_Len);
    CTable* pcClone();
    int* get_pi_Table();
    int get_iTable_Length();
};
#endif //LISTA1_CTABLE_H
