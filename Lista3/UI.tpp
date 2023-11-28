//
// Created by Mikołaj Machalski on 07/11/2023.
//

#include "UI.h"

#include "functionalities.h"
#include "CTree.h"
#include "iostream"

using namespace std;


UI::UI(){

}

UI::~UI(){

}
template<typename T>
UI::UITyped<T>::UITyped(){
    pc_Tree = 0;

}
template<typename T>
UI::UITyped<T>::~UITyped(){
    delete pc_Tree;

}

void UI::v_outer_gameloop() {
    bool* pb_flag = new bool(true);
    string sUserInput;
    vector<string> vInputTokens;
    while(*pb_flag){

        cout<<"Please specify your type: "<<endl;
        getline(cin,sUserInput);
        v_procces_typed_gameloop(sUserInput,&pb_flag);

    }
    delete pb_flag;

}
void UI::v_procces_typed_gameloop(std::string sType,bool**pb_Flag) {
    if(sType==CONSTIntType){
        UITyped<int> uityped;
        uityped.v_gameloop();

    } else if(sType==CONSTDoubleType){
        UITyped<double> uityped;
        uityped.v_gameloop();

    } else if(sType==CONSTStringType){
        UITyped<string> uityped;
        uityped.v_gameloop();
    } else if(sType==CONSTend){
        *pb_Flag=false;
    }



}
template<typename T>
void UI::UITyped<T>::v_gameloop() {
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
template<typename T>
void UI::UITyped<T>::v_procces_and_choose_action(vector<string> vTokens,bool** pb_Flag) {
    string sToken = vTokens[0];
    if (!vTokens.empty()) {
        vTokens.erase(vTokens.begin());
    }
    if(sToken==CONSTenter){

        v_enter(vTokens);

    } else if( sToken ==CONSTvars){
        v_vars();

    }else if( sToken ==CONSTprint){
        v_print();

    }else if( sToken ==CONSTcomp){
        try{
            v_comp(vTokens);
        } catch (const exception& e ){
            std::cerr << "Caught an exception: " << e.what() << std::endl;
        }


    }else if( sToken ==CONSTjoin){
       v_join(vTokens);

    }
    else if( sToken ==CONSTend){
        *pb_Flag= new bool(false);

    }else{
        cout<<"Couldnt process that command";
    }
}
template<typename T>

void UI::UITyped<T>::v_enter(vector<string> vParamTokens){
    int*piErrors=new int(0);
    if(pc_Tree!=0){
        delete pc_Tree;
    }


    pc_Tree = new CTree<T>();

    pc_Tree->v_enter(vParamTokens,&piErrors);
    if(*piErrors==0){
        cout<<"Succesfully read tree: ";

    } else if(*piErrors==1){
     //  std::cout << "\033[1;31mThis text is red.\033[0m" << std::endl;
        cout<<"\033[1;31mToo many arguments.\033[0m"<<endl<<"Loaded tree: ";


    } else if(*piErrors==-1){
        cout<<"\033[1;31mToo few arguments.(Missing were replaced by ""defualt values"")\033[0m"<<endl<<"Loaded tree: ";

    } else if(*piErrors==2){
        cout<<"\033[1;31mParse Error (Variable name not acceptable, replaced by ""default values"")\033[0m"<<endl<<"Loaded tree: ";
    }

    v_print();
    cout<<endl;
    delete piErrors;

}
template<typename T>
void UI::UITyped<T>::v_comp(vector<string> vParamTokens){
    int*piErrors=new int(0);
    T result;
    if(pc_Tree==0){
        cout<<"There's no tree!"<<endl;
        return;
    } else{
        result = pc_Tree->v_comp(vParamTokens,&piErrors);
        if(*piErrors==2){
            cout<<"\033[1;31mFailed. One of the variables is not a represent of type given.\033[0m"<<endl<<"Loaded variables: ";
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
                cout<<"\033[1;31mToo few arguments.(Missing were replaced by \"\"default value\"\")\033[0m"<<endl<<"Loaded variables: ";

            }
            v_vars();
            cout<<"Result of the tree ";
            pc_Tree->v_print();
            cout<<"with provided values is:  "<<result<<endl;

        }

        }



}
template<typename T>
void UI::UITyped<T>::v_print() {
    if(pc_Tree!=0){
        pc_Tree->v_print();
    } else{
        cout<<"There's no tree!"<<endl;
    }
}
template<typename T>
void UI::UITyped<T>::v_vars(){
    if(pc_Tree!=0){
        pc_Tree->v_vars();
    } else{
        cout<<"There's no tree!"<<endl;
    }
}
template<typename T>

void UI::UITyped<T>::v_join(vector<string> vParamTokens){
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

