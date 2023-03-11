#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int a,b,c;
    cin >> a >> b >> c;
    int t=0;
    int A=a,B=b,C=c;
    int cp=0;
    string s;
    bool done=false;
    while(!done){
        string str,s;
        getline(cin >> ws,str);
        vector<string> v;
        auto ss=stringstream(str);
        while(getline(ss,s,' ')){
            v.push_back(s);
        }
        if(v[0]!="n"){
            cout << "error";
            return 0;
        }
        for(int i=1;i<v.size();i+=2){
            if(v[i]=="0"){
                done=true;
                break;
            }
            int x=stoi(v[i+1]);
        if(v[i]=="1"){
            cp+=min(a,x)*5/30;
            a=max(0,a-x);
        }else if(v[i]=="2"){
            cp+=min(b,x)*10/30;
            b=max(0,b-x);
        }else if(v[i]=="3"){
            cp+=min(c,x)*20/30;
            c=max(0,c-x);
        }else{
            cout << "error";
            return 0;
        }
        }
    }
    cout << 1 << ' ' << A-a << ' ' << a << '\n';
    cout << 2 << ' ' << B-b << ' ' << b << '\n';
    cout << 3 << ' ' << C-c << ' ' << c << '\n';
    cout << (A-a)*5+(B-b)*10+(C-c)*20 << ' ' << cp << '\n';
}