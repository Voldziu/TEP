#include <iostream>
#include "functionalities.h"
#include "CNumber.h"
int main() {
    // to do: ogarnac kolejnosc odejmowania, porownac moduly, aby zawsze odejmowac a-b, abs(a) >= abs(b)
    CNumber dupcia1;
    CNumber dupcia2;
    dupcia1=10;
    dupcia2.vSet(69126846);
    CNumber dupcia3 = dupcia1 + dupcia2;
    cout<<dupcia3.s_to_str()<<endl;
    cout<<dupcia1.s_to_str()<<endl;



    return 0;
}
