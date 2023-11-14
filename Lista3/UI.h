//
// Created by Mikołaj Machalski on 07/11/2023.
//

#ifndef LISTA3_UI_H
#define LISTA3_UI_H
#include "CTree.h"
#include "constants.h"
#include "string"

class UI {
public:
    UI();
    ~UI();
    private:
    CTree *pc_Tree;
    public:
    void v_gameloop();
    void v_procces_and_choose_action(vector<string> vTokens,bool**pb_Flag);
    void v_enter(vector<string> vParamTokens);
    void v_vars();
    void v_print();
    void v_comp(vector<string> vParamTokens);
    void v_join(vector<string> vParamTokens);
};


#endif //LISTA3_UI_H
