//
// Created by Mikołaj Machalski on 24/10/2023.
//

#include <algorithm>
#include <iostream>
#include "CNumber.h"
#include "constants.h"
#include "functionalities.h"
#include <sstream>

using namespace std;

CNumber::CNumber() {
    iLength=CONST_NUMBER_DEFAULT_LENGHTH;
    pi_Number = new int[iLength];
    positive=true;
    cout<<"Tworzę domyślny Cnumber o dlugosci: "<<iLength<<", Wartości: "<<s_to_str()<<"\t oraz adresie: "<<this<<endl;


}
CNumber::CNumber(const CNumber &COther) {
    iLength=COther.iLength;
    pi_Number= pi_rewrite_table(COther.pi_Number,iLength,iLength);
    positive=COther.positive;
    cout<<"Kopiuję Cnumber o dlugosci: "<<iLength<<", Wartości: "<<s_to_str()<<"\t z adresu: "<<&COther<<"\t na  adres: "<<this<<endl;

}
CNumber::~CNumber(){


    cout<<"Usuwam Cnumber o dlugosci: "<<iLength<<", Wartości: "<<s_to_str()<<"\t oraz adresie: "<<this<<endl;

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
    if(iNewVal==0){
        iLength=1;
    }else{
        iLength = floor(log(iAbsVal)/ log(CONST_BASE)) + 1;
    }


    pi_Number = new int[iLength];
    for (int ii = 0; ii <iLength ; ++ii) {
        pi_Number[iLength-1-ii]= iAbsVal % CONST_BASE;
        iAbsVal = iAbsVal / CONST_BASE;
    }

}
void CNumber::operator=(const CNumber &pcOther) {
    cout<<"------- =  begins-----"<<endl;
    this->vSet_all_params(pcOther.pi_Number,pcOther.iLength,pcOther.positive);
}
void CNumber::operator=(const int iValue)  {
    this->vSet(iValue);
}
bool CNumber::operator==( CNumber &pcOther){
    int *pi_ComparedValue;

    v_compareTo_by_abs(*this,pcOther,&pi_ComparedValue);

    if(positive==pcOther.positive && *pi_ComparedValue==0){
        return true;

    } else{
        return false;
    }
    delete pi_ComparedValue;
}
bool CNumber::operator==( int iValue ){
    CNumber CSecond;
    CSecond.vSet(iValue);
    return (*this) == CSecond;

}
CNumber CNumber::operator*(int iNewVal) {
    cout<<"-------Int Multiplication begins-----"<<endl;
    CNumber CSecond;
    CSecond.vSet(iNewVal);
    return (*this) * CSecond;

}
CNumber CNumber::operator-(int iNewVal) {
    cout<<"-------Int Substraction begins-----"<<endl;
    CNumber CSecond;
    CSecond.vSet(iNewVal);
    return (*this) - CSecond;

}
CNumber CNumber::operator+(int iNewVal) {
    cout<<"-------Int Addition begins-----"<<endl;
    CNumber CSecond;
    CSecond.vSet(iNewVal);
    return (*this) + CSecond;

}
CNumber CNumber::operator/(int iNewVal) {
    cout<<"-------Int Division begins-----"<<endl;
    CNumber CSecond;
    CSecond.vSet(iNewVal);
    return (*this) / CSecond;

}

CNumber CNumber::operator+(CNumber &pcNewVal) {
    cout<<"-------Cnumber Adding begins-----"<<endl;
    int *pi_Number, *pi_iLength, *pi_CompareValue;
    bool bNewSign;
    v_compareTo_by_abs(*this,pcNewVal,&pi_CompareValue);
    if( (positive==pcNewVal.positive)){//++
        v_add(pcNewVal,&pi_Number,&pi_iLength);
        if(positive){
            bNewSign=true;
        }else{ //--
            bNewSign=false;
        }
    } else{ // take bigger number based on its abs value - lesser
        if(*pi_CompareValue==1){ // first abs is larger
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
    delete pi_Number;
    delete pi_CompareValue;
    return CReturn;
}
CNumber CNumber::operator-(CNumber &pcOther){
    cout<<"-------Cnumber Substraction begins-----"<<endl;
    int *pi_Number, *pi_iLength, *pi_CompareValue;
    bool bNewSign;
    v_compareTo_by_abs(*this,pcOther,&pi_CompareValue);
    if( (positive == pcOther.positive)){// +-+ or --- // take bigger number based on its abs value - lesser
        if(*pi_CompareValue==1){ // first abs is larger
            this->v_subtract(pcOther, &pi_Number, &pi_iLength);
            if(positive){// +-
                bNewSign=true;
            } else{//-+
                bNewSign=false;
            }
        } else{ // second is larger (by abs)
            pcOther.v_subtract(*this, &pi_Number, &pi_iLength);
            if(positive){// +-
                bNewSign= false;
            } else{//-+
                bNewSign=true;
            }
        }

    } else{ //simple add, and watch the sign
        v_add(pcOther, &pi_Number, &pi_iLength);
        if(positive){//+-+
            bNewSign=true;
        }else{ //---
            bNewSign=false;
        }

    }
    CNumber CReturn;
    CReturn.vSet_all_params(pi_Number,*pi_iLength,bNewSign);
    delete pi_iLength; //WAZNE
    delete pi_Number;
    delete pi_CompareValue;
    return CReturn;

}
CNumber CNumber::operator*(CNumber &pcOther){
    cout<<"-------Cnumber Multiplication begins-----"<<endl;
    int *pi_Number, *pi_iLength;
    bool bNewSign;
    v_multiply(pcOther,&pi_Number,&pi_iLength);
    if( (positive == pcOther.positive)){// ++ or --
        bNewSign=true;
    } else{ //-+ or -+
        bNewSign= false;
    }
    CNumber CReturn;
    CReturn.vSet_all_params(pi_Number,*pi_iLength,bNewSign);
    delete pi_iLength; //WAZNE
    delete pi_Number;
    return CReturn;


}
CNumber CNumber::operator/(CNumber &pcOther){
    cout<<"-------Cnumber Division begins-----"<<endl;
    int *pi_Number, *pi_iLength;
    bool bNewSign;
    if( pcOther ==0){
        throw std::runtime_error("Division by 0");


    } else{
        v_divide(pcOther,&pi_Number,&pi_iLength);
    }

    if( (positive == pcOther.positive)){// ++ or --
        bNewSign=true;
    } else{ //-+ or -+
        bNewSign= false;
    }
    CNumber CReturn;
    CReturn.vSet_all_params(pi_Number,*pi_iLength,bNewSign);
    delete pi_iLength; //WAZNE
    delete pi_Number;
    return CReturn;


}

void CNumber::v_add(CNumber &pcOther, int **p2i_Number_Return, int **pi_iLength) {

    int iCarry=0;
    int iMaxLen = std::max(iLength, pcOther.iLength);
    int *pi_Result = new int[iMaxLen];

    for (int ii = 0; ii <iMaxLen ; ++ii) {
        int iDigit1, iDigit2;
        if(ii<iLength){
            iDigit1 = pi_Number[iLength-1-ii];
        } else{
            iDigit1=0;
        }
        if(ii < pcOther.iLength){
            iDigit2 = pcOther.pi_Number[pcOther.iLength - 1 - ii];
        } else{
            iDigit2=0;
        }
        int iSum = iDigit1+iDigit2 +iCarry;
        iCarry = iSum / CONST_BASE;
        pi_Result[iMaxLen-1-ii]= iSum % CONST_BASE;
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
void CNumber::v_subtract(CNumber &pcOther, int **p2i_Number_Return, int **pi_iLength) { // we assume that pcOther's abs value is always less/equal
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
        if(ii < pcOther.iLength){
            iDigit2 = pcOther.pi_Number[pcOther.iLength - 1 - ii];
        } else{
            iDigit2=0;
        }
        int iDiff = iDigit1-iDigit2-iBorrow; //iBorrow is "1" that was lend prior.
        iBorrow=0;
        if(iDiff<0){
            iDiff+=CONST_BASE;
            iBorrow=1; // Take 1 from next iteration.
        }
        pi_Result[iMaxLen-1-ii]= iDiff % CONST_BASE;

    }
    int iLeadingZeros=0;
    while(iLeadingZeros < iMaxLen-1 && pi_Result[iLeadingZeros] == 0){
        iLeadingZeros++;
    }
    int* pi_Swap = pi_rewrite_table_from_back(pi_Result, iMaxLen - iLeadingZeros, iMaxLen);
    delete pi_Result;
    pi_Result=pi_Swap;
    *p2i_Number_Return=pi_Result;
    *pi_iLength= new int (iMaxLen - iLeadingZeros);

}
void CNumber::v_multiply(CNumber &pcOther, int**p2i_Number_Return, int**pi_iLength){
    int iMaxLen = iLength + pcOther.iLength;
    int* pi_Result = new int[iMaxLen];
    for (int ii = 0; ii <iMaxLen ; ++ii) { // for safety
        pi_Result[ii]=0;
    }
    for (int ii = 0; ii <iLength ; ++ii) {
        for (int ik = 0; ik < pcOther.iLength ; ++ik) {
            int iSingleMul = pi_Number[iLength-1-ii] * pcOther.pi_Number[pcOther.iLength-1-ik];
            int iUnitPos = iLength+pcOther.iLength-1-ii-ik;
            int iDecPos = iUnitPos-1;
            int iSum = iSingleMul+pi_Result[iUnitPos];
            pi_Result[iUnitPos]= iSum % CONST_BASE;
            pi_Result[iDecPos] += iSum / CONST_BASE;

        }

    }

    int iLeadingZeros=0;
    while(iLeadingZeros < iMaxLen-1 && pi_Result[iLeadingZeros] == 0){
        iLeadingZeros++;
    }
    int* pi_Swap = pi_rewrite_table_from_back(pi_Result, iMaxLen - iLeadingZeros, iMaxLen);
    delete pi_Result;
    pi_Result=pi_Swap;
    *p2i_Number_Return=pi_Result;
    *pi_iLength= new int (iMaxLen - iLeadingZeros);


}
void CNumber::v_divide(CNumber &pcOther, int **p2i_Number_Return, int **pi_iLength) { // UWAZAC NA MEMORY LEAKI MEGA MEGA MEGA !!!!
    int *pi_SubNumber;
    int *pi_Remainder_Table;
    int *pi_Result;
    int *pi_ComparedValue;

    CNumber CTempNominatorOrg;
    CNumber CTempNominator;
    CNumber CTempMultResult;
    CNumber CTempRemainder;

    int iPartDivRes;
    int iMaxLen = iLength - pcOther.iLength+1;
    CNumber pcOtherAbs;
    pcOtherAbs= pcOther;
    pcOtherAbs.vSet_all_params(pcOther.pi_Number,pcOther.iLength,true); // create a positive copy

    v_compareTo_by_abs(*this,pcOther,&pi_ComparedValue);
    if(*pi_ComparedValue==-1){ // if denominator is smaller than nominator
        *p2i_Number_Return=new int[1];
        *p2i_Number_Return[0]=0;
        *pi_iLength = new int(1);
        delete pi_ComparedValue;
    }else{
        pi_Result=new int[iMaxLen];

        pi_SubNumber= pi_rewrite_table(pi_Number, pcOtherAbs.iLength, iLength);
        CTempNominatorOrg.vSet_all_params(pi_SubNumber, pcOtherAbs.iLength, true);
        delete pi_SubNumber;

        for (int ii = 0; ii <iMaxLen ; ++ii) { // outer loop
            CTempNominator = CTempNominatorOrg;

            iPartDivRes=0;
            bool bWhileFlag=true;
            while(bWhileFlag){
                v_compareTo_by_abs(CTempNominator,pcOtherAbs,&pi_ComparedValue);
                if(*pi_ComparedValue>-1){
                    CTempNominator = CTempNominator-pcOtherAbs;

                    iPartDivRes++;
                } else{
                    bWhileFlag=false;
                }
                delete pi_ComparedValue;

            }
            CTempMultResult=pcOtherAbs*iPartDivRes;
            CTempRemainder = CTempNominatorOrg-CTempMultResult;
            pi_Remainder_Table = pi_rewrite_table(CTempRemainder.pi_Number,CTempRemainder.iLength+1,CTempRemainder.iLength);
            pi_Remainder_Table[CTempRemainder.iLength]=pi_Number[ii+pcOther.iLength];
            CTempNominatorOrg.vSet_all_params(pi_Remainder_Table,CTempRemainder.iLength+1,true);
            delete pi_Remainder_Table;
            pi_Result[ii]=iPartDivRes;
        }


        int iLeadingZeros = i_how_many_leading_x(pi_Result,0,iMaxLen);
        int* pi_Swap = pi_rewrite_table_from_back(pi_Result, iMaxLen - iLeadingZeros, iMaxLen);
        delete pi_Result;
        pi_Result=pi_Swap;
        *p2i_Number_Return=pi_Result;
        *pi_iLength= new int (iMaxLen - iLeadingZeros);

    }
}
CNumber CNumber:: cDiv(CNumber &pcOther, CNumber **pc_Rest){
    CNumber CRes, CRest,CMult;
    CRes = *this / pcOther;
    CMult =  pcOther * CRes;
    CRest = *this - CMult;
    *pc_Rest= new CNumber();
    **pc_Rest = CRest;
    return CRes;


}



int CNumber::get_iLength() {
    return iLength;
}
int * CNumber::get_pi_Number() {
    return pi_Number;
}
string CNumber::s_to_str() {
    bool bTabFlag;
    if(CONST_BASE>10){
        bTabFlag= true;
    } else{
        bTabFlag=false;
    }
    string sign,number;
    if(positive){
        sign = "";
    }else{
        sign="-";
    }
    if(bTabFlag){
        for (int ii = 0; ii <iLength ; ++ii) {
            std::stringstream ss;
            ss << pi_Number[ii];
            number += ss.str();

        }
    } else{
        for (int ii = 0; ii <iLength ; ++ii) {
            std::stringstream ss;
            ss << pi_Number[ii];
            number += ss.str();


        }
    }

    return sign+number;
}


void CNumber::vSet_all_params(int *pi_Table_New, int iNewLen,bool bSign) {
    delete pi_Number;
    pi_Number= pi_rewrite_table(pi_Table_New,iNewLen,iNewLen);
    iLength=iNewLen;
    positive=bSign;
}




