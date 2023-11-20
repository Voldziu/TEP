//
// Created by Mikołaj Machalski on 06/11/2023.
//

#include "CTree.h"
#include "vector"
#include "iostream"
#include "constants.h"
#include <iostream>
#include <sstream>
using namespace std;


using namespace std;
CTree::CNode::CNode(string svalue){
    if(CONSTboolDebugFlag){
        cout<<"Tworzę węzeł na adres: "<<this <<endl;
    }
    sValue = svalue;
    pi_vecChildren = new vector<CTree::CNode*>(2,nullptr);
    iRealValue=0;
    bIsEvaluated=false;

}

CTree::CNode::CNode(const CNode &COther){ //it copies without "connections"
    if(CONSTboolDebugFlag){
        cout<<"Kopiuję węzeł na adres: "<<this <<"z adresu: "<<this<<endl;
    }

    sValue = COther.sValue;
    iRealValue=COther.iRealValue;
    bIsEvaluated=COther.bIsEvaluated;
    CParent=0;
    pi_vecChildren = new vector<CTree::CNode*>(2,nullptr);
}


CTree::CTree(){
    if(CONSTboolDebugFlag){
        cout<<"Tworzę drzewo o adresie: "<<this <<endl;
    }
    pc_Root=0;
}
CTree::CTree(string sInput){
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
CTree::~CTree(){
    if(CONSTboolDebugFlag){
        cout<<"Usuwam drzewo z adresu: "<<this <<endl;
    }
    delete pc_Root;

}
CTree::CNode::CNode() {
    if(CONSTboolDebugFlag){
        cout<<"Tworzę węzeł o adresie: "<<this <<endl;
    }
    sValue=CONSTstringNodeValue;


}
CTree::CNode::~CNode() {

    for (int i = 0; i <(*pi_vecChildren).capacity() ; ++i) {
        delete (*pi_vecChildren)[i];

    }
    delete pi_vecChildren;
    if(CONSTboolDebugFlag){
        cout<<"Usuwam węzeł z adresu: "<<this <<" o wartości: "<<this->sValue<<endl;
    }
}

 CTree::CNode  *CTree::C_procces_RPN_recur(vector<string> *pvec_Tokens,CNode* pc_Parent,int**pi_Errors){ // figure out how to deal with bad input

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
    if(b_is_operator(sToken,&pi_ArgsNumber)){
        if(*pi_ArgsNumber==1){
            CNode* pvec_swap;
            pvec_swap=(*(*pC_node).get_pi_vecChildren())[0];
            (*(*pC_node).get_pi_vecChildren())[0]= C_procces_RPN_recur(pvec_Tokens,pC_node,pi_Errors);
        } else if( *pi_ArgsNumber==2){
            (*(*pC_node).get_pi_vecChildren())[0]= C_procces_RPN_recur(pvec_Tokens,pC_node,pi_Errors);
            (*(*pC_node).get_pi_vecChildren())[1]= C_procces_RPN_recur(pvec_Tokens,pC_node,pi_Errors);
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

double CTree::v_comp(vector<std::string> vecVariablesTokens, int **pi_Errors) {
    v_evaluate_variables_recur(&vecVariablesTokens,pc_Root,pi_Errors);
    return v_comp_all_tree(pc_Root,pi_Errors);
}
void CTree::v_evaluate_variables_recur(vector<string> *pvec_Tokens, CNode *pc_CurrentNode, int** pi_Errors){
    int* pi_ArgsNumber;

    if(b_is_operator(pc_CurrentNode->get_sValue(), &pi_ArgsNumber)){
        if(*pi_ArgsNumber==1){
            v_evaluate_variables_recur(pvec_Tokens, (*(*pc_CurrentNode).get_pi_vecChildren())[0], pi_Errors);
        } else if( *pi_ArgsNumber==2){
            v_evaluate_variables_recur(pvec_Tokens, (*(*pc_CurrentNode).get_pi_vecChildren())[0], pi_Errors);
            v_evaluate_variables_recur(pvec_Tokens, (*(*pc_CurrentNode).get_pi_vecChildren())[1], pi_Errors);

        }
    } else if(b_is_variable(pc_CurrentNode->get_sValue())){
        if(!pc_CurrentNode->get_bIsEvaluated()){
            string sToken;
            if ((*pvec_Tokens).empty()) {
                 sToken ="1";
            } else{
                 sToken = (*pvec_Tokens).front();
                (*pvec_Tokens).erase((*pvec_Tokens).begin());
            }
            if(b_is_digit(sToken)){
                pc_CurrentNode->set_iRealValue(stoi(sToken));
                pc_CurrentNode->set_bIsEvaluated(true);
                v_find_and_evaluate_all_instances_of_variable_recur(pc_CurrentNode, this->pc_Root);

            } else{
                *pi_Errors = new int(2);
            }

        }

    }

    delete pi_ArgsNumber;
}

double CTree::v_comp_all_tree(CNode* pc_CurrentNode,int** pi_Errors){
    pc_CurrentNode->set_bIsEvaluated(false);
    if(pc_CurrentNode==0){
        return 0;
    } else{
        int*pi_HowManyArgs;
        if(b_is_digit(pc_CurrentNode->get_sValue())){
            return stoi(pc_CurrentNode->get_sValue());
        }  else if(b_is_operator(pc_CurrentNode->get_sValue(),&pi_HowManyArgs)){
            if(*pi_HowManyArgs==1){ //only one possibility
                double dDegrees = v_comp_all_tree((*(pc_CurrentNode->get_pi_vecChildren()))[0],pi_Errors);
                delete pi_HowManyArgs;

                return d_round(sin(dDegrees / 180.0* M_PI),10);

            } else if(*pi_HowManyArgs==2){
                delete pi_HowManyArgs;
                double dLeft = v_comp_all_tree((*(pc_CurrentNode->get_pi_vecChildren()))[0],pi_Errors);
                double dRight = v_comp_all_tree((*(pc_CurrentNode->get_pi_vecChildren()))[1],pi_Errors);
                if(pc_CurrentNode->get_sValue()=="+"){
                    return dLeft+dRight;
                } else if(pc_CurrentNode->get_sValue()=="-"){
                    return dLeft-dRight;
                }else if(pc_CurrentNode->get_sValue()=="*"){
                    return dLeft*dRight;
                }else if(pc_CurrentNode->get_sValue()=="/"){
                    if(dRight==0.0){
                        throw runtime_error("Nie dziel przez zero cholero");
                    }else{
                        return dLeft/dRight;
                    }
                }
            }
        }else if(b_is_variable(pc_CurrentNode->get_sValue())){
            return pc_CurrentNode->get_iRealValue();
        }


    }
}

void CTree::v_find_and_evaluate_all_instances_of_variable_recur(CNode* pc_LookedFor,CNode* pc_CurrentNode){
    if(pc_CurrentNode==0){
        return;
    }
    if(pc_LookedFor->get_sValue() == pc_CurrentNode->get_sValue()){
        pc_CurrentNode->set_iRealValue(pc_LookedFor->get_iRealValue());
        pc_CurrentNode->set_bIsEvaluated(true);
    }
    v_find_and_evaluate_all_instances_of_variable_recur(pc_LookedFor,(*(pc_CurrentNode->get_pi_vecChildren()))[0]);
    v_find_and_evaluate_all_instances_of_variable_recur(pc_LookedFor,(*(pc_CurrentNode->get_pi_vecChildren()))[1]);
}


vector<CTree::CNode*>* CTree::CNode::get_pi_vecChildren() {

    return (this->pi_vecChildren);
}
CTree::CNode* CTree::get_pc_Root(){
    return this->pc_Root;
}
void CTree::set_pc_Root(CTree::CNode**pc_Root_Other){
    this->pc_Root=*pc_Root_Other;
}
void CTree::v_enter(vector<string> vParamTokens,int** pi_Errors){

    pc_Root= C_procces_RPN_recur(&vParamTokens,pc_Root,pi_Errors);
    if(vParamTokens.size()>0){ // to many arguments
        *pi_Errors=new int(1);
    }
}
CTree::CNode* CTree::CNode::get_CParent(){
    return this->CParent;
}
void CTree::CNode::set_pc_Parent(CTree::CNode**pc_Parent_Other){
    this->CParent = *pc_Parent_Other;
}
string CTree::CNode::get_sValue() {
    return this->sValue;
}
void CTree::CNode::set_iRealValue(int iRealValue) {
    this->iRealValue =  iRealValue;
}
void CTree::CNode::set_bIsEvaluated(bool bFlag){
    this->bIsEvaluated=bFlag;
}
bool CTree::CNode::get_bIsEvaluated() {
    return this->bIsEvaluated;
}
int CTree::CNode::get_iRealValue(){
    return this->iRealValue;

}

string CTree::to_string_recur(CTree::CNode* pc_Root) {
    if(pc_Root==0){
        return"";
    }
    std::stringstream ss;
    ss << pc_Root->get_sValue() << " ";
    ss << to_string_recur((*(pc_Root->get_pi_vecChildren()))[0]);
    ss << to_string_recur((*(pc_Root->get_pi_vecChildren()))[1]);

    return ss.str();

}
string CTree::to_string(){
    return to_string_recur(pc_Root);
}
void CTree::v_print() {
    cout<<to_string();
    cout<<endl;
}
void CTree::v_vars_recur(CNode* pc_CurrentNode,vector<string> *pvec_SetOfVariables){
    if(pc_CurrentNode!=0){
        int* pi_HowManyArgs;
        if(b_is_variable(pc_CurrentNode->get_sValue()) && !b_is_operator(pc_CurrentNode->get_sValue(),&pi_HowManyArgs)){
            if(i_find((*pvec_SetOfVariables).data(), pvec_SetOfVariables->size(), pc_CurrentNode->get_sValue()) ==-1){
                pvec_SetOfVariables->push_back(pc_CurrentNode->get_sValue());
            }
        }
        v_vars_recur((*(pc_CurrentNode->get_pi_vecChildren()))[0],pvec_SetOfVariables);
        v_vars_recur((*(pc_CurrentNode->get_pi_vecChildren()))[1],pvec_SetOfVariables);
    } else{
        return;
    }
}
void CTree::v_vars(){
    vector<string>* pvec_SetOfVariables= vec_getSetOfVariables();
    for (int i = 0; i <pvec_SetOfVariables->size() ; ++i) {
        cout<<(*pvec_SetOfVariables)[i]+" ";

    }
    cout<<endl;
    delete pvec_SetOfVariables;
}

vector<string>* CTree::vec_getSetOfVariables(){
    vector<string>* pvec_SetOfVariables = new vector<string>;
    v_vars_recur(pc_Root,pvec_SetOfVariables);
    return pvec_SetOfVariables;
}

CTree::CNode* CTree::C_get_most_right(int**pi_Index){
    return C_get_most_right_recur(pc_Root,pi_Index);
}
CTree::CNode* CTree::C_get_most_right_recur(CNode*pc_CurrentNode,int**pi_Index){

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
void CTree::v_join(vector<string> vParamTokens,int** pi_Errors){
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
void CTree::operator=(const CTree &COther){
    CTree* nonConstCOther = const_cast<CTree*>(&COther);
    pc_Root= nonConstCOther->C_get_ctree_copy()->pc_Root;

}
CTree CTree::operator+(CTree &COther){
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

CTree * CTree::C_get_ctree_copy()  {

    int*pi_Errors;
    CTree* pc_ReturnTree = new CTree();
    CNode* pc_RootCopied=0;
    vector<string>* pvec_Tokens= new vector<string>(vec_tokenize(to_string(),' '));
    pc_RootCopied = C_procces_RPN_recur(pvec_Tokens,pc_RootCopied,&pi_Errors);
    pc_ReturnTree->set_pc_Root(&pc_RootCopied);
    return pc_ReturnTree;
}



