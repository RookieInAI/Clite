//
// Created by loop on 18-12-10.
//

#include "Clite_parse.h"

void Clite_parse::getGrammar() {
    ifstream file("/home/loop/CLionProjects/Compiler_of_Clit/Grammar_en");
    string tmp;
    int state=0;
    string tmp1,tmp2,tmp3;
    int i=0;
    while(!file.eof ()){
        if(state==0){
            file>>tmp1;
            state=1;
            file>>tmp2;
        }
        else {
            file>>tmp2;
            vector<string> t;
            i=0;
            while(tmp2!="|"&&tmp2!=";"){
                t.push_back (tmp2);
                file>>tmp2;
                i++;
                if(i>=1000)
                    break;
            }
            grammar[tmp1].push_back (t);
            if(tmp2=="|")
                state=1;
            else state=0;
        }
    }
}

void Clite_parse::showGrammar() {
    cout<<"LEFT"<<"\t"<<"RIGHT"<<endl;
    for(auto &i:grammar){
        cout<<"LEFT:"<<setw(20)<<i.first <<"RIGHT:";
        for (auto j:i.second){
            for(auto &k:j){
                cout<<k;
            }
            cout<<"\n"<<setw(27)<<'|';
        }
        cout<<endl;
    }
}

void Clite_parse::getfirstch(string c) {
    for(auto i:grammar){
        if(i.first==c)
            for(const auto&k:i.second){
                //k: vector<string> //i.second:set
                for(const string &j:k){
                    if(ter_ch.count(j)){
                        first[c].insert (j);
                        break;
                    }
                    else if(j==null_ch){
                        first[c].insert (j);
                    }
                    else {
                        if(first.count(j)==0){
                            getfirstch(j);
                        }
                        set<string> tmp(first[j].begin(),first[j].end());
                        tmp.erase (null_ch);
                        first[c].insert (tmp.begin (),tmp.end ());
                        if(first[j].count(null_ch)==0){
                            break;
                        }
                    }
                }
            }
    }
}

void Clite_parse::get_Firstch() {
    first[null_ch].insert (null_ch);
    for (const auto& i:ter_ch){
        first[i].insert (i);
    }
    for (const auto& i:nonter_ch){
        getfirstch (i);
    }
}

const set<string> Clite_parse::getfirst(vector<string> s) {
    set<string> tmp;
    bool flag= true;
    bool subflag;
    for(auto i:s){
        subflag = false;
        for (auto j:first[i]){
            if(j!= null_ch)
                tmp.insert (j);
            else subflag=true;
        }
        flag = flag &&subflag;
        if(!flag)
            break;
    }
    if(flag)
        tmp.insert (null_ch);
    return set<string> (tmp);
}

void Clite_parse::get_Followch() {
    follow[start_ch].insert ("#TOP#");

    long a=follow.size ();
    vector<long> b;
    for(auto i:follow){
        b.push_back (i.second.size ());
    }
    int i=0;
    while(true){
        //showtable ();
        //cout<<i++<<endl;
        for(auto i:grammar){
            for(auto j:i.second){
                auto tmp=j;
                for (auto k:j){
                    tmp.erase (tmp.begin ());
                    if(nonter_ch.count (k)){
                        set<string> t=getfirst(tmp);
                        bool flag=false;
                        for (string n:t){
                            if(n!=null_ch)
                                follow[k].insert(n);
                            else flag= true;
                        }
                        if(flag){
                            //cout<<"have: "<<k<<" "<<i.first<<endl;
                            follow[k].insert (follow[i.first].begin(),follow[i.first].end ());
                        }
                    }
                }
            }
        }
        long na;
        na=follow.size ();
        vector<long> nb;
        for(auto m:follow){
            nb.push_back (m.second.size());
        }
        //cout<<na<<endl<<a<<endl;
        if(na==a){
            //cout<<"xxx\n";
            bool flag=true;
            for(int i=0;i<nb.size ();i++){
                flag=flag && (b[i]==nb[i]);
            }
            if(!flag){
                a=na;
                b=nb;
            } else break;
        }else {
            a=na;
            b=nb;
        }
    }
}

void Clite_parse::get_table() {
    for(auto i:grammar){
       // cout<<'a'<<endl;
        for(const auto &j:i.second){
         //   cout<<'b'<<endl;
            set<string> tmp;
            tmp = getfirst (j);
            for(auto k:tmp) {
               // cout << 'c' << endl;
                if (k != null_ch) {
                    if (table[ i.first ][ k ].empty ())
                        table[ i.first ][ k ] = j;
                    else {
                        cout << "notLL(1)\n";
                        cout << "1\n";
                        cout << "K:" << k << endl;
                        cout << "LEFT:" << i.first << endl;
                        cout << "RIGHT1:";
                        for (auto ddd:table[ i.first ][ k ])
                            cout << ddd;
                        cout << endl;
                        cout << "RIGHT2:";
                        for (auto ddd:j)
                            cout << ddd;
                        cout << endl;
                    }
                }
            }
                if(tmp.count (null_ch)){
                    for(auto n:follow[i.first]){
                    //    cout<<'d'<<endl;
                        vector<string> stmp{null_ch};
                        if(table[i.first][n].empty ()){
                            table[i.first][n]=stmp;
                        }
                        else {
                            cout<<"notLL(1)\n";
                            cout<<"2\n";
                            cout<<"N:"<<n<<endl;

                            cout<<"LEFT<FOLLOW>:";
                            for(auto f:follow[i.first]){
                                cout<<f<<" ";
                            }
                            cout<<endl;
                            cout<<"LEFT:"<<i.first<<endl;
                            cout<<"RIGHT1:";
                            for(auto ddd:table[i.first][n])
                                cout<<ddd;
                            cout<<endl;
                            cout<<"RIGHT2:";
                            for(auto ddd:stmp)
                                cout<<ddd;
                            cout<<endl;
                            cout<<"SIZE:"<<follow[i.first].size ()<<endl;
                        }
                    }
                }
        }
    }
}

void Clite_parse::gettoken(vector<token> lex_re) {
    v=lex_re;
}

void Clite_parse::token2list() {
    for(auto i:v){
        if(i.type=="Keywords")
            list.push_back (i.name);
        else
            list.push_back (i.type);
    }
    list.emplace_back ("#TOP#");
}

void Clite_parse::showtable() {
    cout<<"FIRST:\n";
    for(auto i:first){
        cout<<setw(20)<<i.first;
        for(auto j:i.second){
            cout<<setw(15)<<j;
        }
        cout<<endl;
    }
    cout<<"FOLLOW:\n";
    for(auto i:follow){
        cout<<setw(30)<<i.first;
        for(auto j:i.second){
            cout<<setw(15)<<j;
        }
        cout<<endl;
    }
    for(auto i:table){
        cout<<setw(15)<<i.first<<endl;
        for(auto j:i.second){
            cout<<setw(5)<<"|"<<setw(25)<<j.first<<"   |    ";
            for(auto k:j.second){
                cout<<k;
            }
            cout<<endl;
        }
    }
}

void Clite_parse::run() {
    vector<string> l=list;
    stack<string> s;
    s.push ("#TOP#");
    s.push (start_ch);
    while(true){
        //getchar ();
        cout<<"当前栈内容: \n";
        stack<string> stmp=s;
        stack<string> ttmp;
        while(!stmp.empty ()){
            ttmp.push (stmp.top());
            stmp.pop ();
        }
        while(!ttmp.empty ()){
            cout<<ttmp.top ();
            ttmp.pop ();
        }
        cout<<endl;
        cout<<"当前串内容: \n";
        for(auto i:l){
            cout<<i;
        }
        cout<<endl;
        cout<<"-----------------------------------------"<<endl;
        if(s.top ()=="#TOP#"&&l[0]=="#TOP#") {
            s.pop ();
            l.erase (l.begin ());
            cout<<"done\n";
            break;
        }
        else if(ter_ch.count (s.top ())){
            if(s.top()==*l.begin ())
            {
                s.pop();
                l.erase (l.begin ());
            }
            else {
                cout<<"wrong code\n";
                break;
            }
        }
        else if(nonter_ch.count (s.top())){
            stack<string> tmp;
            if(table.count(s.top ())&&table[s.top()].count (l[0])) {
                for (const auto &i:table[ s.top () ][ *l.begin () ]) {
                    tmp.push (i);
                }
                s.pop ();
                while (!tmp.empty ()) {
                    if(tmp.top ()!="BLANK")
                        s.push (tmp.top ());
                    tmp.pop ();
                }
            }
            else{
                cout<<"wrong code2\n";
                cout<<"S:"<<s.top()<<endl;
                cout<<"L:"<<l[0]<<endl;
                break;
            }
        }
    }
    if(!s.empty ()||!l.empty ()) {
        cout << "error code3\n";
        cout<<"当前栈内容: \n";
        stack<string> stmp=s;
        stack<string> ttmp;
        while(!stmp.empty ()){
            ttmp.push (stmp.top());
            stmp.pop ();
        }
        while(!ttmp.empty ()){
            cout<<ttmp.top ();
            ttmp.pop ();
        }
        cout<<endl;
        cout<<"当前串内容: \n";
        for(auto i:l){
            cout<<i;
        }
        cout<<endl;
    }
    else cout<<"OK!";
}

