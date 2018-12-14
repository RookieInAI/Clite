//
// Created by loop on 18-12-6.
//

#include "Clite_lex.h"

Clite_lex::Clite_lex(string& src) {
    cout<<str_code[0]<<endl;
    str_code =src;
    position_now=0;
    run ();
}

void Clite_lex::run() {
    while(position_now<str_code.size ()){
        tokenlist.push_back (generate_token ());
    }
}

const token Clite_lex::generate_token() {
    string str_token;
    string str_type;
    getch ();
    while(isSpace ()) {
        if(ch=='\n'){
            char_num_tmp=0;
            line_num_tmp+=1;
        }
        getch ();
    }
    if(isLetter ()){
        while(isLetter ()||isDigit ()) {
            str_token += ch;
            getch ();
        }
        if(isKeywords (str_token))
            str_type="Keywords";
        else
            str_type="<IDS>";
        retract ();
    }
    else if(isDigit ()){
        while(isDigit ()){
            str_token += ch;
            getch ();
        }
        if(isfull_stop ()){
            str_token += ch;
            getch ();
            if(isDigit ()){
                while(isDigit ()){
                    str_token+=ch;
                    getch ();
                }
                if(ch=='E') {
                    str_token+=ch;
                    getch ();
                    if(isMinus ()){
                        str_token+=ch;
                        getch ();
                        if (isDigit ()) {
                            while (isDigit ()) {
                                str_token += ch;
                                getch ();
                            }
                            str_type="REAL";
                            retract ();
                        }
                        else error (0);//指数形式实数指数部分 负指数负号后非数字
                    }
                    else if (isDigit ()){
                        while(isDigit ()){
                            str_token+=ch;
                            getch ();
                        }
                        str_type="REAL";
                        retract ();
                    }
                    else error (1);//E后非数字
                }
                else{
                    str_type="REAL";
                    retract ();
                }
                //else 普通无符号实数
            }
            else error(2);//小数点后非数字
        }
        else{
            str_type="NINT";
            retract ();
        }
        //else 普通无符号整数
    }
    else if(isDoubleQuo ()){
        str_token+=ch;
        getch ();
        while(!isDoubleQuo ()){
            //出错：读到文档尾

            if(position_now==str_code.size ())
                error (3);

            //读到反斜杠立即读下一个
            if(isBlkSlash ()){
                str_token+=ch;
                getch ();
            }
            str_token+=ch;
            getch ();
        }
        str_type="STR";
        retract ();
    }
    else if(isSignaQuo ()){
        str_token+=ch;
        getch ();
        if(isBlkSlash ()){
            str_token+=ch;
            getch ();
        }
        str_token+=ch;
        getch ();
        if(isSignaQuo ()){
            str_token+=ch;
            getch ();
        }
        else error (4);//char常量结尾缺少'
        str_type="CHAR";
        retract ();
    }
    else if(isAnd ()){
        str_token+=ch;
        getch ();
        if(isAnd ()){
            str_token+=ch;
            getch ();
            str_type="AND";
            retract ();
        } else error (5);
    }
    else if(isOr ()){
        str_token+=ch;
        getch ();
        if(isOr ()){
            str_token+=ch;
            getch ();
            str_type="OR";
            retract ();
        }else error (6);
    }
    else if(isStar ()){
        str_token+=ch;
        getch ();
        str_type="STAR";
        retract ();
    }
    else if(isMinus ()){
        str_token+=ch;
        getch ();
      /*  if(isMinus ()){
            str_token+=ch;
            getch ();
            str_type="DEC_SELF";
            retract ();
       */// }
       // else{
            str_type="MINUS";
            retract ();
        //}
    }
    else if(isDivi ()){
        str_token+=ch;
        getch ();
        str_type="DIV";
        retract ();
    }
    else if(isNot ()){
        str_token+=ch;
        getch ();
        if(isEqu ()){
            str_token+=ch;
            str_type="NOT_EQU";
        }
        else{
            str_type="NOT";
            retract ();
        }
    }
    else if(isEqu ()){
        str_token+=ch;
        getch ();
        if(isEqu ()){
            str_token+=ch;
            getch ();
            str_type="EQU";
            retract ();
        }
        else{
            str_type="ASSIGN_OP";
            retract ();
        }
    }
    else if(isPlus ()){
        str_token+=ch;
        getch ();
      /*  if(isPlus ()){
            str_token+=ch;
            str_type="ADD_SELF";
        }
        else{*/
            str_type="PLUS";
            retract ();
       // }
    }
    else if(isSemi ()){
        str_token+=ch;
        str_type="SEMI";
    }
    else if(isComma ()){
        str_token+=ch;
        str_type="COMMA";
    }
    else if(isLp ()){
        str_token+=ch;
        str_type="LP";
    }
    else if(isRp ()){
        str_token+=ch;
        str_type="RP";
    }
    else if(isLb ()){
        str_token+=ch;
        str_type="LB";
    }
    else if(isRb ()){
        str_token+=ch;
        str_type="RB";
    }
    else if(isLc ()){
        str_token+=ch;
        str_type="LC";
    }
    else if(isRc ()){
        str_token+=ch;
        str_type="RC";
    }
    else if(isGreater_than ()){
        str_token+=ch;
        getch ();
        if(isEqu ()){
            str_token+=ch;
            str_type="GREATER_EQU";
        }
        else {
            str_type = "GREATER";
            retract ();
        }
    }
    else if(isLess_than ()) {
        str_token += ch;
        getch ();
        if (isEqu ()) {
            str_token += ch;
            str_type="LESS_EQU";
        }
        else {
            str_type = "LESS";
            retract ();
        }
    }
    else if(isBlkSlash ()){
        getch ();
        if(isBlkSlash ())
        {
            getch ();
            while(ch!='\n')
                getch ();
        }
        if(isStar ()){
            while(true){
                getch ();
                if(isStar ()){
                    getch ();
                    if(isBlkSlash ())
                        break;
                }
            }
        }
    }
    else error (7);//未定义符号出现
    return token (str_token,str_type,line_num_tmp,char_num_tmp);
}

void Clite_lex::error(int i) {
    cout<<"error"<<i<<endl;
    getch ();
}
