//
// Created by Mikołaj Machalski on 06/11/2023.
//

#ifndef LISTA3_CONSTANTS_H
#define LISTA3_CONSTANTS_H
#include "string"
#include "vector"
using namespace std;


const bool CONSTboolDebugFlag = true;
const string CONSTstringNodeValue="0";
const string CONSTenter = "enter";
const string CONSTjoin = "join";
const string CONSTvars = "vars";
const string CONSTprint = "print";
const string CONSTend = "end";
const string CONSTcomp = "comp";

const string CONSTIntType = "int";
const string CONSTDoubleType = "double";
const string CONSTStringType = "string";


const string CONSTplus = "+";
const string CONSTminus = "-";
const string CONSTslash = "/";
const string CONSTstar = "*";
const string CONSTsin = "sin";


const string CONSTstringOperatorList2Args[]={"+","-","/","*"};
const string CONSTstringOperatorList4Args[]={"supersum"};

const string CONSTstringOperatorList1Args[] = {"sin"};
const double CONST180ForSin = 180.0;
const int CONSTintRoundPlaces=10;
const int CONSTintOperatorList2ArgsLen = 4;
const int CONSTintOperatorList1ArgsLen = 1;
const int CONSTintOperatorList4ArgsLen = 1;

const int CONSTintOperatorList2Args = 2;
const int CONSTintOperatorList1Args = 1;
const int CONSTintOperatorList4Args = 4;
#endif //LISTA3_CONSTANTS_H
