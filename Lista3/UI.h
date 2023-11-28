//
// Created by Mikołaj Machalski on 07/11/2023.
//

#ifndef LISTA3_UI_H
#define LISTA3_UI_H
#include "CTree.h"

#include "constants.h"
using namespace std;

class UI {
private:
    template<typename T> class UITyped{
    private:
        CTree<T> *pc_Tree;
    public:
        UITyped();
        ~UITyped();

        void v_gameloop();
        void v_procces_and_choose_action(vector<string> vTokens,bool**pb_Flag);
        void v_enter(vector<string> vParamTokens);
        void v_vars();
        void v_print();
        void v_comp(vector<string> vParamTokens);
        void v_join(vector<string> vParamTokens);


    };
public:
    UI();
    ~UI();


    public:
    void v_outer_gameloop();
    void v_procces_typed_gameloop(string sType,bool **pb_Flag);


};
#include "UI.tpp"

#endif //LISTA3_UI_H
