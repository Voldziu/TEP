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
