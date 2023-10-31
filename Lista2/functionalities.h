//
// Created by Mikołaj Machalski on 24/10/2023.
//

#ifndef LISTA2_FUNCTIONALITIES_H
#define LISTA2_FUNCTIONALITIES_H
#include "CNumber.h"

int* pi_rewrite_table(int *pi_Table,int iTab_Size_New,int iTable_Length);
int* pi_rewrite_table_from_back(int *pi_Table,int iTab_Size_New,int iTable_Length);
void v_print_table(int *pi_Table,int iTable_Size);
void v_compare_2_equal_len_tables(int *pi_Table1,int *pi_Table2,int iMutualLen, int** pb_ReturnValue);

void v_compareTo_by_abs(CNumber &pcFirst,CNumber &pcSecond, int** pb_ReturnValue);

int i_how_many_leading_x(int *pi_Table,int x, int iTable_Length);

#endif //LISTA2_FUNCTIONALITIES_H
