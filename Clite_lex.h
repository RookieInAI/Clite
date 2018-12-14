//
// Created by loop on 18-12-6.
//

#ifndef COMPILER_OF_CLIT_CLITE_LEX_H
#define COMPILER_OF_CLIT_CLITE_LEX_H

#include <string>
#include <vector>
#include <set>
#include <iostream>
using namespace std;

struct token{
    string name;
    string type;
    int line_num;
    int char_num;
    token(string& a,string& b,int c,int d){
        name=a;
        type=b;
        line_num=c;
        char_num=d;
    }
};


class Clite_lex {
    const set<string> keywords={"int","char","float","void","bool",
                                    "Struct","struct",
                                "if","else","return","while","for","use"
    };
    vector<token> tokenlist;
    string str_code;

    unsigned long position_now;
    char ch;

    int line_num_tmp=0;
    int char_num_tmp=0;

    void error(int i);
    void run();
    const token generate_token();

    void getch(){
        ch=str_code[position_now];
        position_now++;
        char_num_tmp+=1;
    }
    bool isKeywords(const string& str_token){
        return 0 != keywords.count (str_token);
    }
    void retract(){position_now--;}
    bool isSignaQuo(){ return ch=='\'';}
    bool isDoubleQuo(){ return '\"' == ch;}
    bool isSpace(){ return ch==' '||ch=='\n'||ch=='\t'; }
    bool isLetter(){ return (ch<='z'&&ch>='a')||(ch<='Z'&&ch>='A'); }
    bool isDigit(){ return (ch<='9'&&ch>='0'); }
    bool isEqu(){ return '=' == ch;}
    bool isPlus(){ return '+' == ch;}
    bool isMinus(){ return '-' == ch;}
    bool isDivi(){ return '/' == ch;}
    //bool isColon(){ return ':' == ch;}
    bool isComma(){ return ',' == ch;}
    bool isSemi(){ return ';' == ch;}
    bool isStar(){ return '*' == ch;}
    bool isLp(){ return '(' == ch;}
    bool isRp(){ return ')' == ch;}
    bool isLb(){ return '[' == ch;}
    bool isRb(){ return ']' == ch;}
    bool isLc(){ return '{' == ch;}
    bool isRc(){ return '}' == ch;}
    bool isAnd(){ return '&' == ch;}
    bool isOr(){ return '|' == ch;}
    bool isGreater_than(){ return '>'==ch;}
    bool isLess_than(){ return '<'==ch;}
    bool isBlkSlash(){ return '\\' == ch;}
    bool isfull_stop(){ return '.'==ch;}
    bool isNot(){return '!'==ch;}
public:
    explicit Clite_lex(string& src);
    const vector<token> gettokenlist(){
        return tokenlist;
    }
    void show(){
        for(auto i:tokenlist)
            cout<<i.name<<" "<<i.type<<" "
            <<i.line_num<<" "<<i.char_num<<endl;
    }
};


#endif //COMPILER_OF_CLIT_CLITE_LEX_H
