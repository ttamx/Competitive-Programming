#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    cin >> s;
    int n=s.size();
    ll buf=1e18;
    auto eval=[&](const string &t)->ll {
        ll val=0;
        int sgn=1;
        for(int i=0;i<t.size();i++){
            ll cur=0;
            int cnt=0;
            char st=t[i];
            while(i<t.size()&&isdigit(t[i])){
                cur=cur*10+t[i]-'0';
                i++;
                cnt++;
            }
            if(cnt>10)return buf++;
            if(st=='0'&&cnt>1)return buf++;
            val+=cur*sgn;
            if(i<t.size()){
                if(t[i]=='+'){
                    sgn=1;
                }else{
                    sgn=-1;
                }
            }
        }
        return val;
    };
    auto check=[&](const string &t){
        if(!isdigit(t[0])||!isdigit(t[n-1]))return false;
        for(int i=0;i+1<n;i++){
            if(!isdigit(t[i])&&!isdigit(t[i+1]))return false;
        }
        string l,r;
        for(int i=0;i<n;i++){
            if(t[i]=='='){
                l=t.substr(0,i);
                r=t.substr(i+1,n-i-1);
                break;
            }
        }
        return eval(l)==eval(r);
    };
    if(check(s)){
        cout << "Correct";
        exit(0);
    }
    for(int i=0;i<n;i++){
        if(!isdigit(s[i]))continue;
        string t=s.substr(0,i)+s.substr(i+1,n-i+1);
        for(int j=0;j<n;j++){
            t.insert(t.begin()+j,s[i]);
            if(check(t)){
                cout << t;
                exit(0);
            }
            t.erase(t.begin()+j);
        }
    }
    cout << "Impossible";
}