//
// Created by Mikołaj Machalski on 24/10/2023.
//

#include <algorithm>
#include <iostream>
#include "CNumber.h"
#include "constants.h"
#include "functionalities.h"

using namespace std;

CNumber::CNumber() {
    iLength=CONST_NUMBER_DEFAULT_LENGHTH;
    pi_Number = new int[iLength];
    positive=true;
    cout<<"Tworzę domyślny Cnumber o dlugosci: "<<iLength<<", Wartości: ";
    v_print_table(pi_Number,iLength);
    cout<<endl;

}
CNumber::CNumber(const CNumber &COther) {
    iLength=COther.iLength;
    pi_Number= pi_rewrite_table(COther.pi_Number,iLength,iLength);
    cout<<"Kopiuję Cnumber o dlugosci: "<<iLength<<", Wartości: ";
    v_print_table(pi_Number,iLength);
    cout<<endl;
}
CNumber::~CNumber(){


    cout<<"Usuwam Cnumber o dlugosci: "<<iLength<<", Wartości: ";
    v_print_table(pi_Number,iLength);
    cout<<endl;
    delete pi_Number;
}
void CNumber::vSet(int iNewVal) {
    delete pi_Number;
    if(iNewVal<0){
        positive=false;
    }
    else{
        positive=true;
    }
    int iAbsVal = abs(iNewVal);
    iLength = floor(log10(iAbsVal))+1;
    pi_Number = new int[iLength];
    for (int ii = 0; ii <iLength ; ++ii) {
        pi_Number[iLength-1-ii]=iAbsVal % CONST_BASE_10;
        iAbsVal =iAbsVal / CONST_BASE_10;
    }

}

CNumber CNumber::operator+(CNumber &pcNewVal) {

    int iCarry=0;
    int iMaxLen = std::max(iLength,pcNewVal.iLength);
    int *pi_Result = new int[iMaxLen];

    for (int ii = 0; ii <iMaxLen ; ++ii) {
        int iDigit1, iDigit2;
        if(ii<iLength){
            iDigit1 = pi_Number[iLength-1-ii];
        } else{
            iDigit1=0;
        }
        if(ii<pcNewVal.iLength){
            iDigit2 = pcNewVal.pi_Number[pcNewVal.iLength-1-ii];
        } else{
            iDigit2=0;
        }
        int iSum = iDigit1+iDigit2 +iCarry;
        iCarry = iSum/10;
        pi_Result[iMaxLen-1-ii]=iSum %CONST_BASE_10;
    }
    if(iCarry>0){
        iMaxLen++;
        int* pi_Swap = pi_rewrite_table_from_back(pi_Result,iMaxLen,iMaxLen-1);
        delete pi_Result;
        pi_Swap[0]=iCarry;
        pi_Result=pi_Swap;

    }
    CNumber CReturn;
    CReturn.vSet_table_and_len(pi_Result,iMaxLen);
    return CReturn;
}


int *CNumber::get_pi_Number() {
    return pi_Number;
}
int CNumber::get_iLength() {
    return iLength;
}


void CNumber::vSet_table_and_len(int *pi_Table_New,int iNewLen) {
    delete pi_Number;
    pi_Number= pi_rewrite_table(pi_Table_New,iNewLen,iNewLen);
    iLength=iNewLen;
}

