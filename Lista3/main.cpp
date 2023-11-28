#include <iostream>
#include "functionalities.h"

#include "UI.h"



using namespace std;
int main() {
    vector<int> vec=searchKMP("rarabrarabra","rarabratata");
    for (int i = 0; i <vec.size() ; ++i) {
        cout<<vec[i]<<endl;

    }

    UI Ui;
    Ui.v_outer_gameloop();
//    CTree ctree1("+ a b");
//    CTree ctree2("+ g h");
//    CTree csum;
//    csum = ctree1+ctree2;
//    cout<<"End of main"<<endl;
// wyliczac zmienne w trakcie funkcji, nie trzymac listy zmiennych.




    return 0;
}
