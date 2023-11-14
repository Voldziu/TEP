#include <iostream>
#include "functionalities.h"
#include "CNumber.h"
#include "constants.h"
int main() {
    cout<<"Pracujemy w systemie "<<CONST_BASE<<"-kowym"<<endl<<endl;
    CNumber liczba1;
    CNumber liczba2;
    CNumber liczba3;
    CNumber liczba4;
    CNumber *pc_Rest;
    liczba1=60;
    liczba2=0;
    liczba3=104;


    try{
        liczba3 = liczba1 / liczba2;
    } catch (const exception& e ){
        std::cerr << "Caught an exception: " << e.what() << std::endl;
    }


    liczba4 = liczba3.cDiv(liczba1, &pc_Rest);

    cout<<liczba2.s_to_str()<<endl;
    cout<<liczba1.s_to_str()<<endl;
    cout<<liczba4.s_to_str()<<endl;
    cout<<pc_Rest->s_to_str()<<endl;



    return 0;
}
