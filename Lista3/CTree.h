//
// Created by Mikołaj Machalski on 06/11/2023.
//

#ifndef LISTA3_CTREE_H
#define LISTA3_CTREE_H
#include <iostream>
#include <vector>
#include <string>
#include "constants.h"
#include "functionalities.h"
using namespace std;


template<typename T> class CTree {
private:


    class CNode{
    public:
        CNode();
        CNode(string slabel);

        CNode(const CNode &COther);

        ~CNode();
        vector<CNode*>* get_pi_vecChildren();
        CNode* get_CParent();
        void set_pc_Parent(CNode** COther);
        void set_bIsEvaluated(bool bFlag);
        bool get_bIsEvaluated();
        string get_sLabelValue();
        void set_TRealValue(T iRealValue);
        T get_TRealValue();

    private:
        vector<CNode*>* pi_vecChildren;
        string sLabel;
        CNode* CParent;
        T TRealValue;
        bool bIsEvaluated;

    };
    CNode* pc_Root;
public:

    CTree();
    CTree(string sInput);
    ~CTree();

    void v_enter(vector<string> vParamTokens,int** pi_Errors);

    CNode* C_procces_RPN_recur(vector<string> *pvec_Tokens,CNode* pc_Parent,int** pi_Errors); // errors: 0- no error, -1 - too few, 1 - too many, 2 - other parse error?
    T v_comp(vector<string> vecVariablesTokens,int** pi_Errors); // // errors: 0- no error, -1 - too few, 1 - too many 2- not a number
    void v_evaluate_variables_recur(vector<string> *pvec_Tokens, CNode* pc_CurrentNode, int** pi_Errors);
    T v_comp_all_tree(CNode* pc_CurrentNode,int** pi_Errors);
    void v_find_and_evaluate_all_instances_of_variable_recur(CNode* pc_VarNode,CNode* pc_CurrentNode);

    CNode* get_pc_Root();
    void set_pc_Root(CNode** COther);
    void v_print();
    string to_string();

    string to_string_recur(CNode* pc_Root);
    void v_vars();

    void v_vars_recur(CNode* pc_CurrentNode,vector<string> *pvec_SetOfVariables);
    vector<string>* vec_getSetOfVariables();

    CNode* C_get_most_right(int**pi_Index); // returns also the index where returned Cnode is allocated in Parent's vector of children
    CNode* C_get_most_right_recur(CNode*pc_CurrentNode,int**pi_Index);
    CTree<T> * C_get_ctree_copy();


    void v_join(vector<string> vParamTokens,int** pi_Errors);
    void operator=(const CTree<T> &COther);
    CTree<T> operator+(CTree<T> &COther);


};
#include "CTree.tpp"

#endif //LISTA3_CTREE_H


