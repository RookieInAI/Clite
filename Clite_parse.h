//
// Created by loop on 18-12-10.
//

#ifndef COMPILER_OF_CLIT_CLITE_PARSE_H
#define COMPILER_OF_CLIT_CLITE_PARSE_H

#include <map>
#include <set>
#include <string>
#include <stack>
#include <vector>
#include <fstream>
#include <iostream>
#include "Clite_lex.h"
#include <iomanip>
using namespace std;


//set<string> acction_ch;
//map<string,set<vector<string>>> grammar;
//map<vector<string>,vector<string>> grammar_trans;
//map<string,map<string,vector<string>>> table;


class Clite_parse {

    map<string,vector<vector<string>>> grammar;
    const string null_ch="BLANK",start_ch="<PROGRAM>";
    vector<token> v;
    vector<string> list;
    set<string> ter_ch,nonter_ch;
    map<string,set<string>> first,follow;
    map<string,map<string,vector<string>>> table;
    void get_table();
    void get_Followch();
    void get_Firstch();
    void getfirstch(string c);
    const set<string> getfirst(vector<string> s);
    void getGrammar();
    void showGrammar();
public:
    Clite_parse(){
        set<string> ter_ch_0={"int","float","char","bool","void",
                              "struct",
                              "if","else","while","for","return",
                              "main",
                               "NINT","REAL","CHAR","STR","BOOL",
                              "SEMI","COMMA",
                              "AND","OR","Struct",
                              "PLUS","MINUS","STAR","DIV",
                              "ASSIGN_OP","STOP",
                              "NOT_EQU","NOT",
                              "EQU","GREATER","GREATER_EQU","LESS","LESS_EQU",
                              "LP","LB","LC","RP","RB","RC",
                              "BLANK","<IDS>"
        };
        set<string> nter_ch_0={
                "<PROGRAM>","<DE_LIST>","<STR_FUNC_DE>","<STR_DE>","<FUNC_DE>",
                "<LOC_VAR_DE_LIST>","<TYPE>","<STR_TYPE>","<PAR_LIST>","<PAR_VAR>",
                "<PAR_VAR_PLUS>",
                "<STA_BLOCK>","<STA_LIST>","<STA>","<EXP>","<S_EXP>","<SS_EXP>",
                "<SSS_EXP>","<SSSS_EXP>","<SSSSS_EXP>",
                "<S_EXP_PLUS>","<SS_EXP_PLUS>","<SSS_EXP_PLUS>",
                "<SSSS_EXP_PLUS>","<SSSSS_EXP_PLUS>",
                "<STA_VAR_DE>","<VAR_LIST>","<VAR_LIST_PLUS>","<VAR>","<VAR_ARR_PLUS>",
                "<IDS_PLUS>",
                "<PARS>","<PARS_PLUS>"
        };
        getGrammar();
        showGrammar ();
        ter_ch=ter_ch_0;
        nonter_ch=nter_ch_0;
        get_Firstch ();
        get_Followch ();
        get_table ();
        showtable ();
    }
    void gettoken(vector<token> lex_re);
    void token2list();
    void run();
    void showtable();
};


#endif //COMPILER_OF_CLIT_CLITE_PARSE_H
