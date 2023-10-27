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
void CNumber::operator=(const CNumber &pcNewVal) {
    delete pi_Number;
    pi_Number= pi_rewrite_table(pcNewVal.pi_Number,pcNewVal.iLength,pcNewVal.iLength);
    iLength=pcNewVal.iLength;
}
void CNumber::operator=(const int iValue)  {
    this->vSet(iValue);
}

CNumber CNumber::operator+(CNumber &pcNewVal) {
    int *pi_Number, *pi_iLength;
    bool bNewSign;
    if( (positive==pcNewVal.positive)){//++
        v_add(pcNewVal,&pi_Number,&pi_iLength);
        if(positive){
            bNewSign=true;
        }else{ //--
            bNewSign=false;
        }
    } else{ // take bigger number based on its abs value - lesser
        if(this->b_compareTo_by_abs(pcNewVal)){ // first abs is larger
            this->v_subtract(pcNewVal,&pi_Number,&pi_iLength);
            if(positive){// +-
                bNewSign=true;
            } else{//-+
                bNewSign=false;
            }
        } else{ // second is larger (by abs)
            pcNewVal.v_subtract(*this,&pi_Number,&pi_iLength);
            if(positive){// +-
                bNewSign= false;
            } else{//-+
                bNewSign=true;
            }
        }
    }
    CNumber CReturn;
    CReturn.vSet_all_params(pi_Number,*pi_iLength,bNewSign);
    delete pi_iLength; //WAZNE
    return CReturn;
}

void CNumber::v_add( CNumber &pcNewVal, int **p2i_Number_Return, int **pi_iLength) {
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
        iCarry = iSum/CONST_BASE_10;
        pi_Result[iMaxLen-1-ii]=iSum %CONST_BASE_10;
    }
    if(iCarry>0){
        iMaxLen++;
        int* pi_Swap = pi_rewrite_table_from_back(pi_Result,iMaxLen,iMaxLen-1);
        delete pi_Result;
        pi_Swap[0]=iCarry;
        pi_Result=pi_Swap;
    }
    *p2i_Number_Return = pi_Result;
    *pi_iLength=new int(iMaxLen) ;
}
void CNumber::v_subtract(CNumber &pcNewVal, int **p2i_Number_Return, int **pi_iLength) { // we assume that pcNewVal's abs value is always less/equal
    int iBorrow=0;
    int iMaxLen = iLength;
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
        int iDiff = iDigit1-iDigit2-iBorrow; //iBorrow is "1" that was lend prior.
        iBorrow=0;
        if(iDiff<0){
            iDiff+=10;
            iBorrow=1; // Take 1 from next iteration.
        }
        pi_Result[iMaxLen-1-ii]=iDiff %CONST_BASE_10;

    }
    int iLeadingZeros=0;
    while(iLeadingZeros < iMaxLen && pi_Result[iLeadingZeros] == 0){
        iLeadingZeros++;
    }
    int* pi_Swap = pi_rewrite_table_from_back(pi_Result, iMaxLen - iLeadingZeros, iMaxLen);
    delete pi_Result;
    pi_Result=pi_Swap;
    *p2i_Number_Return=pi_Result;
    *pi_iLength= new int (iMaxLen - iLeadingZeros);
}

int CNumber::get_iLength() {
    return iLength;
}
string CNumber::s_to_str() {
    string sign,number;
    if(positive){
        sign = "";
    }else{
        sign="-";
    }

    for (int ii = 0; ii <iLength ; ++ii) {
        number = number + to_string( pi_Number[ii]);

    }
    return sign+number;
}


void CNumber::vSet_all_params(int *pi_Table_New, int iNewLen,bool bSign) {
    delete pi_Number;
    pi_Number= pi_rewrite_table(pi_Table_New,iNewLen,iNewLen);
    iLength=iNewLen;
    positive=bSign;
}

bool CNumber::b_compareTo_by_abs(CNumber &pcNewVal) {
    bool bComparedLenGrt=iLength > pcNewVal.iLength;
    bool bComparedLenEq=iLength== pcNewVal.iLength;
    if(bComparedLenGrt){
        return true;
    } else if (bComparedLenEq){
        return b_compare_2_equal_len_tables(pi_Number,pcNewVal.pi_Number,iLength);
    } else{
        return false;
    }




}


