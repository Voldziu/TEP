//
// Created by Mikołaj Machalski on 07/11/2023.
//

#ifndef LISTA3_FUNCTIONALITIES_H
#define LISTA3_FUNCTIONALITIES_H
using namespace std;
#include "string"

bool b_is_operator(string sToken,int** pi_HowManyArgs);
bool b_is_digit(string sToken);
bool b_is_variable(string sToken);
vector<string> vec_tokenize(string sInput,char sDelimeter);
int i_find(string* sTokenList,int iTokenListLen,string sWanted);
double d_round(double dNumber,int iDecimalPlaces);
bool b_is_double(string sToken);
bool b_is_quoted_string(string sToken);
std::vector<int> computePrefixFunction(string pattern);
std::vector<int> searchKMP(string text, string pattern);

#endif //LISTA3_FUNCTIONALITIES_H
