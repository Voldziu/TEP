#include <iostream>
#include "functionalities.h"
#include "CNumber.h"
int main() {

    CNumber dupcia1;
    CNumber dupcia2;
    dupcia1.vSet(42412412);
    dupcia2.vSet(69126846);
    CNumber dupcia3 = dupcia1 + dupcia2;
    v_print_table(dupcia3.get_pi_Number(),dupcia3.get_iLength()) ;

    return 0;
}
