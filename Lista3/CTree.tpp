//
// Created by Mikołaj Machalski on 27/11/2023.
//

#ifndef LISTA3_CTREE_TPP
#define LISTA3_CTREE_TPP
#include "CTree.h"
#include <sstream>
#include <string>
using namespace std;
template <typename T>

CTree<T>::CNode::CNode(std::string slabel) {
    if(CONSTboolDebugFlag){
        cout<<"Tworzę wezel o adresie: "<<this <<endl;
    }
    sLabel=slabel;
    bIsEvaluated=false;
    pi_vecChildren=new vector<CNode*>(2,nullptr);
    CParent= nullptr;

}

template< typename T >
CTree<T>::CNode::CNode(const CNode &COther){ //it copies without "connections"
    if(CONSTboolDebugFlag){
        cout<<"Kopiuję węzeł na adres: "<<this <<"z adresu: "<<this<<endl;
    }

    sLabel = COther.sLabel;
    TRealValue=COther.TRealValue;
    bIsEvaluated=COther.bIsEvaluated;
    CParent=0;
    pi_vecChildren = new vector<CTree::CNode*>(2,nullptr);
}
template< typename T >

CTree<T>::CTree(){
    if(CONSTboolDebugFlag){
        cout<<"Tworzę drzewo o adresie: "<<this <<endl;
    }
    pc_Root=0;
}

template< typename T >
CTree<T>::CTree(string sInput){
    if(CONSTboolDebugFlag){
        cout<<"Tworzę drzewo o adresie: "<<this <<endl;
    }
    int*pi_Errors=new int(0);
    vector<string> vInputTokens;
    vInputTokens = vec_tokenize(sInput,' ');

    pc_Root=0;
    v_enter(vInputTokens,&pi_Errors);
    delete pi_Errors;
}
template< typename T >
CTree<T>::~CTree(){
    if(CONSTboolDebugFlag){
        cout<<"Usuwam drzewo z adresu: "<<this <<endl;
    }
    delete pc_Root;

}
template< typename T >

CTree<T>::CNode::CNode() {
    if(CONSTboolDebugFlag){
        cout<<"Tworzę węzeł o adresie: "<<this <<endl;
    }
    sLabel=CONSTstringNodeValue;


}
template< typename T >

CTree<T>::CNode::~CNode() {

    for (int i = 0; i <(*pi_vecChildren).capacity() ; ++i) {
        delete (*pi_vecChildren)[i];

    }
    delete pi_vecChildren;
    if(CONSTboolDebugFlag){
        cout<<"Usuwam węzeł z adresu: "<<this <<" o wartości: "<<this->sLabel<<endl;
    }
}
template< typename T >

 CTree<T>::CNode  *CTree<T>::C_procces_RPN_recur(vector<string> *pvec_Tokens,CNode* pc_Parent,int**pi_Errors){ // figure out how to deal with bad input

    int* pi_ArgsNumber;
    if ((*pvec_Tokens).empty()) {
        *pi_Errors = new int(-1);
        CNode *pC_node = new CNode("1");
        (*pC_node).set_pc_Parent(&pc_Parent);
        return pC_node;
    }
    string sToken = (*pvec_Tokens).front();
    (*pvec_Tokens).erase((*pvec_Tokens).begin());

    CNode *pC_node = new CNode(sToken);
    (*pC_node).set_pc_Parent(&pc_Parent);
    if(b_is_operator(sToken,&pi_ArgsNumber)) {
        if(*pi_ArgsNumber==CONSTintOperatorList4Args) {
            (*(*pC_node).get_pi_vecChildren()).resize(CONSTintOperatorList4Args);
        }
        for (int i = 0; i < *pi_ArgsNumber ; ++i) {
            (*(*pC_node).get_pi_vecChildren())[i] = C_procces_RPN_recur(pvec_Tokens, pC_node, pi_Errors);
        }


    } else if(b_is_digit(sToken)){
        (*(*pC_node).get_pi_vecChildren())[0]=0;
        (*(*pC_node).get_pi_vecChildren())[1]= 0;


    } else if(b_is_variable(sToken)){
        (*(*pC_node).get_pi_vecChildren())[0]=0;
        (*(*pC_node).get_pi_vecChildren())[1]= 0;

    } else{ // jakis blad parsowania
        *pi_Errors = new int(2);
        pC_node = new CNode("1");
        (*(*pC_node).get_pi_vecChildren())[0]=0;
        (*(*pC_node).get_pi_vecChildren())[1]= 0;
    }
    delete pi_ArgsNumber;
    return pC_node;

}

template<>

CTree<int>::CNode  *CTree<int>::C_procces_RPN_recur(vector<string> *pvec_Tokens,CNode* pc_Parent,int**pi_Errors){ // figure out how to deal with bad input

    int* pi_ArgsNumber;
    if ((*pvec_Tokens).empty()) {
        *pi_Errors = new int(-1);
        CNode *pC_node = new CNode("1");
        (*pC_node).set_pc_Parent(&pc_Parent);
        (*pC_node).set_TRealValue(1);
        return pC_node;
    }
    string sToken = (*pvec_Tokens).front();
    (*pvec_Tokens).erase((*pvec_Tokens).begin());

    CNode *pC_node = new CNode(sToken);
    (*pC_node).set_pc_Parent(&pc_Parent);
    if(b_is_operator(sToken,&pi_ArgsNumber)) {
        if(*pi_ArgsNumber==CONSTintOperatorList4Args) {
            (*(*pC_node).get_pi_vecChildren()).resize(CONSTintOperatorList4Args);
        }
        for (int i = 0; i < *pi_ArgsNumber ; ++i) {
            (*(*pC_node).get_pi_vecChildren())[i] = C_procces_RPN_recur(pvec_Tokens, pC_node, pi_Errors);
        }


    } else if(b_is_digit(sToken)){
        pC_node->set_TRealValue(stoi(sToken));
        (*(*pC_node).get_pi_vecChildren())[0]=0;
        (*(*pC_node).get_pi_vecChildren())[1]= 0;


    } else if(b_is_variable(sToken)){
        (*(*pC_node).get_pi_vecChildren())[0]=0;
        (*(*pC_node).get_pi_vecChildren())[1]= 0;

    } else{ // jakis blad parsowania
        *pi_Errors = new int(2);
       //pC_node = new CNode("1");
        //(*(*pC_node).get_pi_vecChildren())[0]=0;
        //(*(*pC_node).get_pi_vecChildren())[1]= 0;
    }
    delete pi_ArgsNumber;
    return pC_node;

}

template<>

CTree<double>::CNode  *CTree<double>::C_procces_RPN_recur(vector<string> *pvec_Tokens,CNode* pc_Parent,int**pi_Errors){ // figure out how to deal with bad input

    int* pi_ArgsNumber;
    if ((*pvec_Tokens).empty()) {
        *pi_Errors = new int(-1);
        CNode *pC_node = new CNode("1.0");
        (*pC_node).set_pc_Parent(&pc_Parent);
        (*pC_node).set_TRealValue(1.0);
        return pC_node;
    }
    string sToken = (*pvec_Tokens).front();
    (*pvec_Tokens).erase((*pvec_Tokens).begin());

    CNode *pC_node = new CNode(sToken);
    (*pC_node).set_pc_Parent(&pc_Parent);
    if(b_is_operator(sToken,&pi_ArgsNumber)) {
        if(*pi_ArgsNumber==CONSTintOperatorList4Args) {
            (*(*pC_node).get_pi_vecChildren()).resize(CONSTintOperatorList4Args);
        }
        for (int i = 0; i < *pi_ArgsNumber ; ++i) {
            (*(*pC_node).get_pi_vecChildren())[i] = C_procces_RPN_recur(pvec_Tokens, pC_node, pi_Errors);
        }


    } else if(b_is_double(sToken)){
        pC_node->set_TRealValue(stod(sToken));
        (*(*pC_node).get_pi_vecChildren())[0]=0;
        (*(*pC_node).get_pi_vecChildren())[1]= 0;


    } else if(b_is_variable(sToken)){
        (*(*pC_node).get_pi_vecChildren())[0]=0;
        (*(*pC_node).get_pi_vecChildren())[1]= 0;

    } else{ // jakis blad parsowania
        *pi_Errors = new int(2);
        //pC_node = new CNode("1");
        //(*(*pC_node).get_pi_vecChildren())[0]=0;
        //(*(*pC_node).get_pi_vecChildren())[1]= 0;
    }
    delete pi_ArgsNumber;
    return pC_node;

}

template<>

CTree<string>::CNode  *CTree<string>::C_procces_RPN_recur(vector<string> *pvec_Tokens,CNode* pc_Parent,int**pi_Errors){ // figure out how to deal with bad input

    int* pi_ArgsNumber;
    if ((*pvec_Tokens).empty()) {
        *pi_Errors = new int(-1);
        CNode *pC_node = new CNode("\"KOCHAMTEP\"");
        (*pC_node).set_pc_Parent(&pc_Parent);
        (*pC_node).set_TRealValue("KOCHAMTEP");
        return pC_node;
    }
    string sToken = (*pvec_Tokens).front();
    (*pvec_Tokens).erase((*pvec_Tokens).begin());

    CNode *pC_node = new CNode(sToken);
    (*pC_node).set_pc_Parent(&pc_Parent);
    if(b_is_operator(sToken,&pi_ArgsNumber)) {
        if(*pi_ArgsNumber==CONSTintOperatorList4Args) {
            (*(*pC_node).get_pi_vecChildren()).resize(CONSTintOperatorList4Args);
        }
        for (int i = 0; i < *pi_ArgsNumber ; ++i) {
            (*(*pC_node).get_pi_vecChildren())[i] = C_procces_RPN_recur(pvec_Tokens, pC_node, pi_Errors);
        }


    } else if(b_is_quoted_string(sToken)){
        pC_node->set_TRealValue(sToken.substr(1,sToken.length()-2));
        (*(*pC_node).get_pi_vecChildren())[0]=0;
        (*(*pC_node).get_pi_vecChildren())[1]= 0;


    } else if(b_is_variable(sToken)){
        (*(*pC_node).get_pi_vecChildren())[0]=0;
        (*(*pC_node).get_pi_vecChildren())[1]= 0;

    } else{ // jakis blad parsowania
        *pi_Errors = new int(2);
        //pC_node = new CNode("1");
        //(*(*pC_node).get_pi_vecChildren())[0]=0;
        //(*(*pC_node).get_pi_vecChildren())[1]= 0;
    }
    delete pi_ArgsNumber;
    return pC_node;

}


template< typename T >
T CTree<T>::v_comp(vector<std::string> vecVariablesTokens, int **pi_Errors) {
    v_evaluate_variables_recur(&vecVariablesTokens,pc_Root,pi_Errors);
    return v_comp_all_tree(pc_Root,pi_Errors);
}
template< typename T >
void CTree<T>::v_evaluate_variables_recur(vector<string> *pvec_Tokens, CNode *pc_CurrentNode, int** pi_Errors){
    int* pi_ArgsNumber;

    if(b_is_operator(pc_CurrentNode->get_sLabelValue(), &pi_ArgsNumber)){
        for (int i = 0; i <*pi_ArgsNumber ; ++i) {
            v_evaluate_variables_recur(pvec_Tokens, (*(*pc_CurrentNode).get_pi_vecChildren())[i], pi_Errors);
        }
    } else if(b_is_variable(pc_CurrentNode->get_sLabelValue())){
        if(!pc_CurrentNode->get_bIsEvaluated()){
            string sToken;
            if ((*pvec_Tokens).empty()) {
                sToken ="1";
            } else{
                sToken = (*pvec_Tokens).front();
                (*pvec_Tokens).erase((*pvec_Tokens).begin());
            }
            if(b_is_quoted_string(sToken)){
                pc_CurrentNode->set_TRealValue(stoi(sToken));
                pc_CurrentNode->set_bIsEvaluated(true);
                v_find_and_evaluate_all_instances_of_variable_recur(pc_CurrentNode, this->pc_Root);

            } else{
                *pi_Errors = new int(2);
            }

        }

    }

    delete pi_ArgsNumber;
}

template< >
void CTree<int>::v_evaluate_variables_recur(vector<string> *pvec_Tokens, CNode *pc_CurrentNode, int** pi_Errors){
    int* pi_ArgsNumber;

    if(b_is_operator(pc_CurrentNode->get_sLabelValue(), &pi_ArgsNumber)){
        for (int i = 0; i <*pi_ArgsNumber ; ++i) {
            v_evaluate_variables_recur(pvec_Tokens, (*(*pc_CurrentNode).get_pi_vecChildren())[i], pi_Errors);
        }
    } else if(b_is_variable(pc_CurrentNode->get_sLabelValue())){
        if(!pc_CurrentNode->get_bIsEvaluated()){
            string sToken;
            if ((*pvec_Tokens).empty()) {
                sToken ="1";
            } else{
                sToken = (*pvec_Tokens).front();
                (*pvec_Tokens).erase((*pvec_Tokens).begin());
            }
            if(b_is_digit(sToken)){
                pc_CurrentNode->set_TRealValue(stoi(sToken));
                pc_CurrentNode->set_bIsEvaluated(true);
                v_find_and_evaluate_all_instances_of_variable_recur(pc_CurrentNode, this->pc_Root);

            } else{
                *pi_Errors = new int(2);
            }

        }

    }

    delete pi_ArgsNumber;
}

template< >
void CTree<string>::v_evaluate_variables_recur(vector<string> *pvec_Tokens, CNode *pc_CurrentNode, int** pi_Errors){
    int* pi_ArgsNumber;

    if(b_is_operator(pc_CurrentNode->get_sLabelValue(), &pi_ArgsNumber)){
        for (int i = 0; i <*pi_ArgsNumber ; ++i) {
            v_evaluate_variables_recur(pvec_Tokens, (*(*pc_CurrentNode).get_pi_vecChildren())[i], pi_Errors);
        }
    } else if(b_is_variable(pc_CurrentNode->get_sLabelValue())){
        if(!pc_CurrentNode->get_bIsEvaluated()){
            string sToken;
            if ((*pvec_Tokens).empty()) {
                sToken ="\"KOCHAMTEP\"";
            } else{
                sToken = (*pvec_Tokens).front();
                (*pvec_Tokens).erase((*pvec_Tokens).begin());
            }
            if(b_is_quoted_string(sToken)){
                pc_CurrentNode->set_TRealValue(sToken.substr(1,sToken.length()-2));
                pc_CurrentNode->set_bIsEvaluated(true);
                v_find_and_evaluate_all_instances_of_variable_recur(pc_CurrentNode, this->pc_Root);

            } else{
                *pi_Errors = new int(2);
            }

        }

    }

    delete pi_ArgsNumber;
}

template< typename T >
T CTree<T>::v_comp_all_tree(CNode* pc_CurrentNode,int** pi_Errors){
    pc_CurrentNode->set_bIsEvaluated(false);
    if(pc_CurrentNode==0){
        return 0;
    } else{
        int*pi_HowManyArgs;
        if(b_is_digit(pc_CurrentNode->get_sLabelValue())){
            return pc_CurrentNode->get_TRealValue();
        }  else if(b_is_operator(pc_CurrentNode->get_sLabelValue(),&pi_HowManyArgs)){
            if(*pi_HowManyArgs==CONSTintOperatorList1Args){ //only one possibility
                T dDegrees = v_comp_all_tree((*(pc_CurrentNode->get_pi_vecChildren()))[0],pi_Errors);
                delete pi_HowManyArgs;

                return d_round(sin(dDegrees / CONST180ForSin* M_PI),CONSTintRoundPlaces);

            } else if(*pi_HowManyArgs==CONSTintOperatorList2Args){
                delete pi_HowManyArgs;
                T dLeft = v_comp_all_tree((*(pc_CurrentNode->get_pi_vecChildren()))[0],pi_Errors);
                T dRight = v_comp_all_tree((*(pc_CurrentNode->get_pi_vecChildren()))[1],pi_Errors);
                if(pc_CurrentNode->get_sLabelValue()==CONSTplus){
                    return dLeft+dRight;
                } else if(pc_CurrentNode->get_sLabelValue()==CONSTminus){
                    return dLeft-dRight;
                }else if(pc_CurrentNode->get_sLabelValue()==CONSTstar){
                    return dLeft*dRight;
                }else if(pc_CurrentNode->get_sLabelValue()==CONSTslash){
                    if(dRight==0.0){
                        throw runtime_error("Nie dziel przez zero cholero");
                    }else{
                        return dLeft/dRight;
                    }
                }
            } else if(*pi_HowManyArgs==CONSTintOperatorList4Args){
                delete pi_HowManyArgs;
                T dFirst = v_comp_all_tree((*(pc_CurrentNode->get_pi_vecChildren()))[0],pi_Errors);
                T dSecond = v_comp_all_tree((*(pc_CurrentNode->get_pi_vecChildren()))[1],pi_Errors);
                T dThird = v_comp_all_tree((*(pc_CurrentNode->get_pi_vecChildren()))[2],pi_Errors);
                T dFourth = v_comp_all_tree((*(pc_CurrentNode->get_pi_vecChildren()))[3],pi_Errors);
                return dFirst+dFourth+dSecond+dThird;


            }

        }else if(b_is_variable(pc_CurrentNode->get_sLabelValue())){
            return pc_CurrentNode->get_TRealValue();
        }


    }
}

template<  >
double CTree<double>::v_comp_all_tree(CNode* pc_CurrentNode,int** pi_Errors){
    pc_CurrentNode->set_bIsEvaluated(false);
    if(pc_CurrentNode==0){
        return 0.0;
    } else{
        int*pi_HowManyArgs;
        if(b_is_double(pc_CurrentNode->get_sLabelValue())){
            return pc_CurrentNode->get_TRealValue();
        }  else if(b_is_operator(pc_CurrentNode->get_sLabelValue(),&pi_HowManyArgs)){
            if(*pi_HowManyArgs==CONSTintOperatorList1Args){ //only one possibility
                double dDegrees = v_comp_all_tree((*(pc_CurrentNode->get_pi_vecChildren()))[0],pi_Errors);
                delete pi_HowManyArgs;

                return d_round(sin(dDegrees / CONST180ForSin* M_PI),CONSTintRoundPlaces);

            } else if(*pi_HowManyArgs==CONSTintOperatorList2Args){
                delete pi_HowManyArgs;
                double dLeft = v_comp_all_tree((*(pc_CurrentNode->get_pi_vecChildren()))[0],pi_Errors);
                double dRight = v_comp_all_tree((*(pc_CurrentNode->get_pi_vecChildren()))[1],pi_Errors);
                if(pc_CurrentNode->get_sLabelValue()==CONSTplus){
                    return dLeft+dRight;
                } else if(pc_CurrentNode->get_sLabelValue()==CONSTminus){
                    return dLeft-dRight;
                }else if(pc_CurrentNode->get_sLabelValue()==CONSTstar){
                    return dLeft*dRight;
                }else if(pc_CurrentNode->get_sLabelValue()==CONSTslash){
                    if(dRight==0.0){
                        throw runtime_error("Nie dziel przez zero cholero");
                    }else{
                        return dLeft/dRight;
                    }
                }
            } else if(*pi_HowManyArgs==CONSTintOperatorList4Args){
                delete pi_HowManyArgs;
                double dFirst = v_comp_all_tree((*(pc_CurrentNode->get_pi_vecChildren()))[0],pi_Errors);
                double dSecond = v_comp_all_tree((*(pc_CurrentNode->get_pi_vecChildren()))[1],pi_Errors);
                double dThird = v_comp_all_tree((*(pc_CurrentNode->get_pi_vecChildren()))[2],pi_Errors);
                double dFourth = v_comp_all_tree((*(pc_CurrentNode->get_pi_vecChildren()))[3],pi_Errors);
                return dFirst+dFourth+dSecond+dThird;


            }

        }else if(b_is_variable(pc_CurrentNode->get_sLabelValue())){
            return pc_CurrentNode->get_TRealValue();
        }


    }
}

template< >
int CTree<int>::v_comp_all_tree(CNode* pc_CurrentNode,int** pi_Errors){
    pc_CurrentNode->set_bIsEvaluated(false);
    if(pc_CurrentNode==0){
        return 0;
    } else{
        int*pi_HowManyArgs;
        if(b_is_digit(pc_CurrentNode->get_sLabelValue())){
            return pc_CurrentNode->get_TRealValue();
        }  else if(b_is_operator(pc_CurrentNode->get_sLabelValue(),&pi_HowManyArgs)){
            if(*pi_HowManyArgs==CONSTintOperatorList1Args){ //only one possibility
                int dDegrees = v_comp_all_tree((*(pc_CurrentNode->get_pi_vecChildren()))[0],pi_Errors);
                delete pi_HowManyArgs;

                return (int)sin(dDegrees / CONST180ForSin* M_PI);

            } else if(*pi_HowManyArgs==CONSTintOperatorList2Args){
                delete pi_HowManyArgs;
                int dLeft = v_comp_all_tree((*(pc_CurrentNode->get_pi_vecChildren()))[0],pi_Errors);
                int dRight = v_comp_all_tree((*(pc_CurrentNode->get_pi_vecChildren()))[1],pi_Errors);
                if(pc_CurrentNode->get_sLabelValue()==CONSTplus){
                    return dLeft+dRight;
                } else if(pc_CurrentNode->get_sLabelValue()==CONSTminus){
                    return dLeft-dRight;
                }else if(pc_CurrentNode->get_sLabelValue()==CONSTstar){
                    return dLeft*dRight;
                }else if(pc_CurrentNode->get_sLabelValue()==CONSTslash){
                    if(dRight==0){
                        throw runtime_error("Nie dziel przez zero cholero");
                    }else{
                        return dLeft/dRight;
                    }
                }
            } else if(*pi_HowManyArgs==CONSTintOperatorList4Args){
                delete pi_HowManyArgs;
                int dFirst = v_comp_all_tree((*(pc_CurrentNode->get_pi_vecChildren()))[0],pi_Errors);
                int dSecond = v_comp_all_tree((*(pc_CurrentNode->get_pi_vecChildren()))[1],pi_Errors);
                int dThird = v_comp_all_tree((*(pc_CurrentNode->get_pi_vecChildren()))[2],pi_Errors);
                int dFourth = v_comp_all_tree((*(pc_CurrentNode->get_pi_vecChildren()))[3],pi_Errors);
                return dFirst+dFourth+dSecond+dThird;


            }

        }else if(b_is_variable(pc_CurrentNode->get_sLabelValue())){
            return pc_CurrentNode->get_TRealValue();
        }


    }
}

template<>
string CTree<string>::v_comp_all_tree(CNode* pc_CurrentNode,int** pi_Errors){
    pc_CurrentNode->set_bIsEvaluated(false);
    if(pc_CurrentNode==0){
        return "";
    } else{
        int*pi_HowManyArgs;
        if(b_is_quoted_string(pc_CurrentNode->get_sLabelValue())){
            return pc_CurrentNode->get_TRealValue();
        }  else if(b_is_operator(pc_CurrentNode->get_sLabelValue(),&pi_HowManyArgs)){
            if(*pi_HowManyArgs==CONSTintOperatorList1Args){ //only one possibility

                return "sin{"+v_comp_all_tree((*(pc_CurrentNode->get_pi_vecChildren()))[0],pi_Errors)+"}";;

            } else if(*pi_HowManyArgs==CONSTintOperatorList2Args){
                delete pi_HowManyArgs;
                string dLeft = v_comp_all_tree((*(pc_CurrentNode->get_pi_vecChildren()))[0],pi_Errors);
                string dRight = v_comp_all_tree((*(pc_CurrentNode->get_pi_vecChildren()))[1],pi_Errors);
                if(pc_CurrentNode->get_sLabelValue()==CONSTplus){
                    return dLeft+dRight;
                } else if(pc_CurrentNode->get_sLabelValue()==CONSTminus){
                    if(dRight.size()==0){
                        return dLeft;
                    }
                    vector<int> vecIndices =searchKMP(dLeft,dRight);
                    int iVecSize=vecIndices.size();

                    if(iVecSize>0){
                        return dLeft.substr(0,dLeft.size()-dRight.size());
                    }else{
                        return dLeft;
                    }

                }else if(pc_CurrentNode->get_sLabelValue()==CONSTstar){
                    if(dLeft.size()==0){
                        return "";
                    }
                    if(dRight.size()==0){
                        return dLeft;
                    }
                    string s(1,dRight[0]);
                    vector<int> vecIndices =searchKMP(dLeft,s);
                    int iCurrentVecIndex=0;
                    int iVecSize=vecIndices.size();
                    string sReturn="";
                    if(iVecSize>0){
                        for (int i = 0; i <dLeft.size()  ; ++i) {
                            if(i==vecIndices[iCurrentVecIndex]){
                                sReturn+=dRight;
                                if(iCurrentVecIndex!=vecIndices.size()){
                                    iCurrentVecIndex++;
                                }

                            } else{
                                sReturn+=dLeft[i];
                            }
                        }
                    } else{
                        return dLeft;
                    }

                    return sReturn;
                }else if(pc_CurrentNode->get_sLabelValue()==CONSTslash){
                    if(dLeft.size()==0){
                        return "";
                    }
                    if(dRight.size()==0){
                        return dLeft;
                    }

                    vector<int> vecIndices =searchKMP(dLeft,dRight);
                    int iCurrentVecIndex=0;
                    int iVecSize=vecIndices.size();
                    string sReturn="";
                    if(iVecSize>0){
                        for (int i = 0; i <dLeft.size() ; ++i) {
                            cout<<i;
                            sReturn+=dLeft[i];
                            if(i==vecIndices[iCurrentVecIndex]){
                                i+=dRight.size()-1;

                                if(iCurrentVecIndex!=iVecSize){
                                    iCurrentVecIndex++;
                                }
                            }
                        }
                    } else {
                        return dLeft;
                    }
                    return sReturn;
                }

            } else if(*pi_HowManyArgs==CONSTintOperatorList4Args){
                delete pi_HowManyArgs;

                return "d";


            }

        }else if(b_is_variable(pc_CurrentNode->get_sLabelValue())){
            return pc_CurrentNode->get_TRealValue();
        }


    }
}

template< typename T >
void CTree<T>::v_find_and_evaluate_all_instances_of_variable_recur(CNode* pc_LookedFor,CNode* pc_CurrentNode){
    if(pc_CurrentNode==0){
        return;
    }
    if(pc_LookedFor->get_sLabelValue() == pc_CurrentNode->get_sLabelValue()){
        pc_CurrentNode->set_TRealValue(pc_LookedFor->get_TRealValue());
        pc_CurrentNode->set_bIsEvaluated(true);
    }
    for (int i = 0; i <pc_CurrentNode->get_pi_vecChildren()->size() ; ++i) {
        v_find_and_evaluate_all_instances_of_variable_recur(pc_LookedFor,(*(pc_CurrentNode->get_pi_vecChildren()))[i]);
    }



}

template<typename T>

vector<typename CTree<T>:: CNode*>* CTree<T>::CNode::get_pi_vecChildren() {
    return pi_vecChildren;
}
template< typename T >

 CTree<T>:: CNode* CTree<T>::get_pc_Root(){
    return this->pc_Root;
}
template< typename T >
void CTree<T>::set_pc_Root(CTree<T>::CNode**pc_Root_Other){
    this->pc_Root=*pc_Root_Other;
}
template< typename T >
void CTree<T>::v_enter(vector<string> vParamTokens,int** pi_Errors){

    pc_Root= C_procces_RPN_recur(&vParamTokens,pc_Root,pi_Errors);
    if(vParamTokens.size()>0){ // to many arguments
        *pi_Errors=new int(1);
    }
}



template<typename T>

 CTree<T>:: CNode* CTree<T>::CNode::get_CParent() {
    return this->CParent;
}
template< typename T >

void CTree<T>::CNode::set_pc_Parent(CTree<T>::CNode**pc_Parent_Other){
    this->CParent = *pc_Parent_Other;
}
template< typename T >

string CTree<T>::CNode::get_sLabelValue() {
    return this->sLabel;
}
template< typename T >

void CTree<T>::CNode::set_TRealValue(T TRealValue) {
    this->TRealValue =  TRealValue;
}
template< typename T >

void CTree<T>::CNode::set_bIsEvaluated(bool bFlag){
    this->bIsEvaluated=bFlag;
}
template< typename T >

bool CTree<T>::CNode::get_bIsEvaluated() {
    return this->bIsEvaluated;
}
template< typename T >

T CTree<T>::CNode::get_TRealValue(){
    return this->TRealValue;

}
template< typename T >

string CTree<T>::to_string_recur(CTree<T>::CNode* pc_Root) {
    if(pc_Root==0){
        return"";
    }
    std::stringstream ss;
    ss << pc_Root->get_sLabelValue() << " ";
    for (int i = 0; i<pc_Root->get_pi_vecChildren()->size() ; ++i) {
        ss << to_string_recur((*(pc_Root->get_pi_vecChildren()))[i]);

    }
    return ss.str();

}
template< typename T >
string CTree<T>::to_string(){
    return to_string_recur(pc_Root);
}
template< typename T >
void CTree<T>::v_print() {
    cout<<to_string();
    cout<<endl;
}
template< typename T >

void CTree<T>::v_vars_recur(CNode* pc_CurrentNode,vector<string> *pvec_SetOfVariables){
    if(pc_CurrentNode!=0){
        int* pi_HowManyArgs;
        if(b_is_variable(pc_CurrentNode->get_sLabelValue()) && !b_is_operator(pc_CurrentNode->get_sLabelValue(),&pi_HowManyArgs)){
            if(i_find((*pvec_SetOfVariables).data(), pvec_SetOfVariables->size(), pc_CurrentNode->get_sLabelValue()) ==-1){
                pvec_SetOfVariables->push_back(pc_CurrentNode->get_sLabelValue());
            }
        }
        for (int i = 0; i <pc_CurrentNode->get_pi_vecChildren()->size() ; ++i) {
            v_vars_recur((*(pc_CurrentNode->get_pi_vecChildren()))[i],pvec_SetOfVariables);
        }
    } else{
        return;
    }
}
template< typename T >
void CTree<T>::v_vars(){
    vector<string>* pvec_SetOfVariables= vec_getSetOfVariables();
    for (int i = 0; i <pvec_SetOfVariables->size() ; ++i) {
        cout<<(*pvec_SetOfVariables)[i]+" ";

    }
    cout<<endl;
    delete pvec_SetOfVariables;
}
template< typename T >
vector<string>* CTree<T>::vec_getSetOfVariables(){
    vector<string>* pvec_SetOfVariables = new vector<string>;
    v_vars_recur(pc_Root,pvec_SetOfVariables);
    return pvec_SetOfVariables;
}
template< typename T >

CTree<T>::CNode* CTree<T>::C_get_most_right(int**pi_Index){
    return C_get_most_right_recur(pc_Root,pi_Index);
}
template< typename T >

 CTree<T>::CNode* CTree<T>::C_get_most_right_recur(CNode*pc_CurrentNode,int**pi_Index){

    int index = pc_CurrentNode->get_pi_vecChildren()->size()-1;
    bool bFound=false;
    while(index>=0 && !bFound){
        if((*(pc_CurrentNode->get_pi_vecChildren()))[index]==0){
            index--;
        } else{
            bFound=true;
        }
    }
    if(!bFound){
        return pc_CurrentNode;

    } else{
        *pi_Index=new int(index);
        return C_get_most_right_recur((*(pc_CurrentNode->get_pi_vecChildren()))[index],pi_Index);
    }

}
template< typename T >

void CTree<T>::v_join(vector<string> vParamTokens,int** pi_Errors){
    CNode* pc_NewRoot=0;
    int* pi_Index=new int(0);
    pc_NewRoot=C_procces_RPN_recur(&vParamTokens,pc_NewRoot,pi_Errors);
    if(vParamTokens.size()>0){ // to many arguments
        *pi_Errors=new int(1);
    }
    CNode * pc_MostRight=0;
    pc_MostRight =C_get_most_right(&pi_Index);
    CNode * pc_MostRightsParent = pc_MostRight->get_CParent();
    pc_NewRoot->set_pc_Parent(&pc_MostRightsParent);
    (*(pc_MostRight->get_CParent()->get_pi_vecChildren()))[*pi_Index]=pc_NewRoot;

    delete pi_Index;
    delete pc_MostRight;

}
template< typename T >
void CTree<T>::operator=(const CTree &COther){
    CTree* nonConstCOther = const_cast<CTree*>(&COther);
    pc_Root= nonConstCOther->C_get_ctree_copy()->pc_Root;

}
template< typename T >
CTree<T> CTree<T>::operator+(CTree &COther){
    CTree * CCopyOfThis = C_get_ctree_copy();
    int* pi_Index=new int(0);
    CNode* pc_NewRoot=0;
    pc_NewRoot=COther.C_get_ctree_copy()->pc_Root;
    CNode * pc_MostRight=0;
    pc_MostRight = CCopyOfThis->C_get_most_right(&pi_Index);
    CNode * pc_MostRightsParent = pc_MostRight->get_CParent();
    pc_NewRoot->set_pc_Parent(&pc_MostRightsParent);
    (*(pc_MostRightsParent->get_pi_vecChildren()))[*pi_Index]=pc_NewRoot;
    delete pi_Index;
    delete pc_MostRight;
    return *CCopyOfThis;

}
template< typename T >
CTree<T> * CTree<T>::C_get_ctree_copy()  {

    int*pi_Errors;
    CTree* pc_ReturnTree = new CTree();
    CNode* pc_RootCopied=0;
    vector<string>* pvec_Tokens= new vector<string>(vec_tokenize(to_string(),' '));
    pc_RootCopied = C_procces_RPN_recur(pvec_Tokens,pc_RootCopied,&pi_Errors);
    pc_ReturnTree->set_pc_Root(&pc_RootCopied);
    return pc_ReturnTree;
}






#endif //LISTA3_CTREE_TPP
