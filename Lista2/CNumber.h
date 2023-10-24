//
// Created by Mikołaj Machalski on 24/10/2023.
//

#ifndef LISTA2_CNUMBER_H
#define LISTA2_CNUMBER_H


class CNumber {
public:
    CNumber();
    CNumber(const CNumber &COther);
    ~CNumber();
    void vSet(int iNewVal);
    void vSet_table_and_len(int* pi_Table_New,int iNewLen);

    void vSet(CNumber &pcNewVal);
    //void operator=(const CNumber &pcNewVal);
    CNumber operator+(CNumber &pcNewVal);
    CNumber operator*(CNumber &pcNewVal);
    CNumber operator-(CNumber &pcNewVal);
    CNumber operator/(CNumber &pcNewVal);
    CNumber operator+(int iNewVal);
    CNumber operator*(int iNewVal);
    CNumber operator-(int iNewVal);
    CNumber operator/(int iNewVal);
    int* get_pi_Number();
    int get_iLength();

private:
    int *pi_Number;
    int iLength;
    bool positive;

};


#endif //LISTA2_CNUMBER_H
