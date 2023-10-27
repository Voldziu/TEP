//
// Created by Mikołaj Machalski on 24/10/2023.
//

#ifndef LISTA2_CNUMBER_H
#define LISTA2_CNUMBER_H
using namespace std;

class CNumber {
public:
    CNumber();
    CNumber(const CNumber &COther);
    ~CNumber();
    void vSet(int iNewVal);
    void vSet_all_params(int* pi_Table_New,int iNewLen, bool bSign);

    void vSet(CNumber &pcNewVal);
    void operator=(const CNumber &pcNewVal);
    void operator=(const int iValue );
    CNumber operator+(CNumber &pcNewVal);
    CNumber operator*(CNumber &pcNewVal);
    CNumber operator-(CNumber &pcNewVal);
    CNumber operator/(CNumber &pcNewVal);
    CNumber operator+(int iNewVal);
    CNumber operator*(int iNewVal);
    CNumber operator-(int iNewVal);
    CNumber operator/(int iNewVal);
    void v_add(CNumber &pcNewVal, int**p2i_Number_Return, int**pi_iLength);
    void v_subtract(CNumber &pcNewVal, int**p2i_Number_Return, int**pi_iLength);
    bool b_compareTo_by_abs(CNumber &pcNewVal);
    int* get_pi_Number();
    int get_iLength();
    string s_to_str();

private:
    int *pi_Number;
    int iLength;
    bool positive;

};


#endif //LISTA2_CNUMBER_H
