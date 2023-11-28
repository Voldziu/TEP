//
// Created by Mikołaj Machalski on 07/11/2023.
//

#include "functionalities.h"
#include "constants.h"
using namespace std;
#include "string"



bool b_is_operator(std::string sToken, int **pi_HowManyArgs) { // also returns number of arguments needed by the operator
    int iFound2arg = i_find(const_cast<string *>(CONSTstringOperatorList2Args), CONSTintOperatorList2ArgsLen, sToken);
    int iFound1arg = i_find(const_cast<string *>(CONSTstringOperatorList1Args), CONSTintOperatorList1ArgsLen, sToken);
    int iFound4arg = i_find(const_cast<string *>(CONSTstringOperatorList4Args), CONSTintOperatorList4ArgsLen, sToken);

    if(iFound4arg==iFound2arg && iFound2arg == iFound1arg && iFound2arg==-1){
        *pi_HowManyArgs= new int(0);
        return false;

    } else if( iFound1arg>-1){
        *pi_HowManyArgs= new int(1);
        return true;

    } else if(iFound2arg>-1){
        *pi_HowManyArgs=new int(2);
        return true;
    } else if(iFound4arg>-1){
        *pi_HowManyArgs=new int(4);
        return true;
    }else{
        return false;
    }
}

bool b_is_digit(string sToken) {
    for (int ii = 0; ii < sToken.length() ; ++ii) {
        if(!isdigit(sToken[ii])){
            return false;
        }
    }
    return true;

}
bool b_is_double(string sToken){
    bool bHasPoint=false;
    for (int i = 0; i < sToken.length(); ++i) {
        if(sToken[i]=='.'){
            if(bHasPoint){
                return false;
            }
            bHasPoint=true;
        }
        if(!isdigit(sToken[i])){
            return false;
        }

    }
    return true;
}
bool b_is_quoted_string(string sToken){
    if(sToken[0]!='"'){
        return false;
    }
    for (int ii = 1; ii < sToken.length()-1 ; ++ii) {
        if(!isalpha(sToken[ii])){
            return false;
        }
    }
    if(sToken[sToken.length()-1]!='"'){
        return false;
    }
    return true;
}
bool b_is_variable(std::string sToken) {
    if(!isalpha(sToken[0])){ // first letter should be alpha
        return false;
    }
    for (int ii = 1; ii < sToken.length() ; ++ii) {
        if(!isalnum(sToken[ii])){
            return false;
        }
    }
    return true;

}
vector<string> vec_tokenize(string sInput,char chDelimeter){
    vector<string> tokens;
    string temp = "";
    for(int i = 0; i < sInput.length(); i++){
        if(sInput[i] == chDelimeter){
            if(temp!=""){
                tokens.push_back(temp);
                temp = "";
            }

        }
        else
            temp += sInput[i];
    }
    if(temp!=""){
        tokens.push_back(temp);
    }

    return tokens;
}
int i_find(string* sTokenList,int iTokenListLen,string sWanted){
    int ii=0;
    while(ii<iTokenListLen){
        if(sTokenList[ii]==sWanted){
            return ii;
        }
        ii++;
    }
    return -1;
}
double d_round(double dNumber,int iDecimalPlaces){
    double multiplier = std::pow(10.0, iDecimalPlaces);
    return std::round(dNumber * multiplier) / multiplier;
}
std::vector<int> computePrefixFunction(string pattern) {
    int m = pattern.length();
    std::vector<int> prefix(m, 0);
    int k = 0;

    for (int q = 1; q < m; ++q) {
        while (k > 0 && pattern[k] != pattern[q]) {
            k = prefix[k - 1];
        }

        if (pattern[k] == pattern[q]) {
            k++;
        }

        prefix[q] = k;
    }

    return prefix;
}

std::vector<int> searchKMP(string text, string pattern) {
    int n = text.size();
    int m = pattern.size();
    std::vector<int> prefix = computePrefixFunction(pattern);
    std::vector<int> indices;

    int q = 0;

    for (int i = 0; i < n; ++i) {
        while (q > 0 && pattern[q] != text[i]) {
            q = prefix[q - 1];
        }

        if (pattern[q] == text[i]) {
            q++;
        }

        if (q == m) {
            indices.push_back(i - m + 1);
            q = prefix[q - 1];
        }
    }

    return indices;
}

