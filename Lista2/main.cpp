#include <iostream>
#include "functionalities.h"
#include "CNumber.h"
#include "constants.h"
int main() {
    cout<<"Pracujemy w systemie "<<CONST_BASE<<"-kowym"<<endl<<endl;
    CNumber liczba1;
    CNumber liczba2;
    liczba1=894;
    liczba2=89;
    try{
        liczba2 = liczba1 / liczba2;
    } catch (const exception& e ){
        std::cerr << "Caught an exception: " << e.what() << std::endl;
    }

    cout<<liczba2.s_to_str()<<endl;
    cout<<liczba1.s_to_str()<<endl;



    return 0;
}
