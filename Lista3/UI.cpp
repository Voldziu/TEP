//
// Created by Mikołaj Machalski on 07/11/2023.
//

#include "UI.h"
#include "string"
#include "functionalities.h"
#include "CTree.h"
#include "iostream"

using namespace std;

UI::UI(){
    pc_Tree= 0;
};
UI::~UI(){
    delete pc_Tree;
}

void UI::v_gameloop() {
    bool* pb_flag = new bool(true);

    string sUserInput;
    vector<string> vInputTokens;
    while(*pb_flag){
        cout<<"Please write a command:"<<endl;
        getline(cin,sUserInput);
        vInputTokens = vec_tokenize(sUserInput,' ');
        v_procces_and_choose_action(vInputTokens,&pb_flag);
    }
    delete pb_flag;
}

void UI::v_procces_and_choose_action(vector<string> vTokens,bool** pb_Flag) {
    string sToken = vTokens[0];
    if (!vTokens.empty()) {
        vTokens.erase(vTokens.begin());
    }
    if(sToken=="enter"){

        v_enter(vTokens);

    } else if( sToken =="vars"){
        v_vars();

    }else if( sToken =="print"){
        v_print();

    }else if( sToken =="comp"){
        try{
            v_comp(vTokens);
        } catch (const exception& e ){
            std::cerr << "Caught an exception: " << e.what() << std::endl;
        }


    }else if( sToken =="join"){
       v_join(vTokens);

    }
    else if( sToken =="end"){
        *pb_Flag= new bool(false);

    }else{
        cout<<"Couldnt process that command";
    }
}
void UI::v_enter(vector<string> vParamTokens){
    int*piErrors=new int(0);
    if(pc_Tree!=0){
        delete pc_Tree;
    }

    pc_Tree = new CTree();
    pc_Tree->v_enter(vParamTokens,&piErrors);
    if(*piErrors==0){
        cout<<"Succesfully read tree: ";

    } else if(*piErrors==1){
     //  std::cout << "\033[1;31mThis text is red.\033[0m" << std::endl;
        cout<<"\033[1;31mToo many arguments.\033[0m"<<endl<<"Loaded tree: ";


    } else if(*piErrors==-1){
        cout<<"\033[1;31mToo few arguments.(Missing were replaced by ""1s"")\033[0m"<<endl<<"Loaded tree: ";

    } else if(*piErrors==2){
        cout<<"\033[1;31mParse Error (Variable name not acceptable, replaced by ""1s"")\033[0m"<<endl<<"Loaded tree: ";
    }

    v_print();
    cout<<endl;
    delete piErrors;

}
void UI::v_comp(vector<string> vParamTokens){
    int*piErrors=new int(0);
    double result;
    if(pc_Tree==0){
        cout<<"There's no tree!"<<endl;
        return;
    } else{
        result = pc_Tree->v_comp(vParamTokens,&piErrors);
        if(*piErrors==2){
            cout<<"\033[1;31mFailed. One of the variables is not a positive integer.\033[0m"<<endl<<"Loaded variables: ";
            v_vars();
        } else{
            int iNumberOfArguments= pc_Tree->vec_getSetOfVariables()->size();
            int iDifference = vParamTokens.size()-iNumberOfArguments;

            if(iDifference==0){
                cout<<"Succesfully read variable values "<<endl<<"Loaded variables: ";

            } else if(iDifference>0){
                //  std::cout << "\033[1;31mThis text is red.\033[0m" << std::endl;
                cout<<"\033[1;31mToo many arguments.\033[0m"<<endl<<"Loaded variables: ";

            } else if(iDifference<0){
                cout<<"\033[1;31mToo few arguments.(Missing were replaced by \"\"1s\"\")\033[0m"<<endl<<"Loaded variables: ";

            }
            v_vars();
            cout<<"Result of the tree ";
            pc_Tree->v_print();
            cout<<"with provided values is:  "<<result<<endl;

        }

        }



}
void UI::v_print() {
    if(pc_Tree!=0){
        pc_Tree->v_print();
    } else{
        cout<<"There's no tree!"<<endl;
    }
}
void UI::v_vars(){
    if(pc_Tree!=0){
        pc_Tree->v_vars();
    } else{
        cout<<"There's no tree!"<<endl;
    }
}
void UI::v_join(vector<string> vParamTokens){
    int*pi_Errors= new int(0);
    if(pc_Tree!=0){
        pc_Tree->v_join(vParamTokens,&pi_Errors);
        if(*pi_Errors==0){
            cout<<"Succesfully read tree: ";

        } else if(*pi_Errors==1){
            //  std::cout << "\033[1;31mThis text is red.\033[0m" << std::endl;
            cout<<"\033[1;31mToo many arguments.\033[0m"<<endl<<"Loaded tree: ";


        } else if(*pi_Errors==-1){
            cout<<"\033[1;31mToo few arguments.(Missing were replaced by ""1s"")\033[0m"<<endl<<"Loaded tree: ";

        } else if(*pi_Errors==2){
            cout<<"\033[1;31mParse Error (Variable name not acceptable, replaced by ""1s"")\033[0m"<<endl<<"Loaded tree: ";
        }

        v_print();
        cout<<endl;
        delete pi_Errors;


    } else{
        cout<<"There's no tree!"<<endl;
    }

}

