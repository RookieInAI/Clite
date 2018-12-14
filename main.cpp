#include <iostream>
#include "Clite_lex.h"
#include "Clite_parse.h"
#include <fstream>
int main() {
    string ss="/home/loop/CLionProjects/Compiler_of_Clit/code.txt";
    ifstream file(ss);
    string str((istreambuf_iterator<char>(file)),istreambuf_iterator<char>());
    Clite_lex CL(str);
    CL.show ();
    Clite_parse c;
    c.gettoken(CL.gettokenlist());
    c.token2list();
    c.run();
    return 0;
}