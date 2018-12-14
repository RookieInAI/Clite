//
// Created by loop on 18-12-8.
//

#ifndef COMPILER_OF_CLIT_SYMTABLE_H
#define COMPILER_OF_CLIT_SYMTABLE_H

#include <string>
#include <stack>
#include <set>
#include <map>

using namespace std;



struct mess{
    enum CAT{fuc,cons,typ,var,varn,varf};
    CAT bcat;
};

struct typetab{};

struct atab{
     unsigned int high;
     unsigned int csize;
     unsigned int size;
     typetab* ctype;
};

struct strtab{
    string struname;
    int offset;
    typetab* ctype;
};



struct funtab{};

class node{
    set<string> nametab;
    map<string,mess> tabcon;
    node* papr;
    set<node*> chpr;
};

class TAB{
    node root;
    stack<pair<string,mess>> symstack;
};

#endif //COMPILER_OF_CLIT_SYMTABLE_H
