#include<bits/stdc++.h>

using namespace std;

typedef long double ld;

ld pw(ld a,ld b){
    ld res=1;
    for(int i=0;i<b;i++)res=res*a;
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    getline(cin >> ws,s);
    ld a,b,ans=0;
    cin >> a >> b;
    ld res=0,mul=1;
    for(int i=0;i<s.size();i++){
        if(s[i]==' ')continue;
        if(s[i]=='+')continue;
        if(s[i]=='-'){
            mul=-1;
            continue;
        }
        if(isdigit(s[i])){
            res*=10;
            res+=s[i]-'0';
            continue;
        }
        if(isalpha(s[i])){
            ld d=1;
            if(s[i+1]=='^'){
                i+=2;
                d=s[i]-'0';
            }
            if(res==0)res=1;
            ans+=res*mul*pw(b,d+1)/(d+1);
            ans-=res*mul*pw(a,d+1)/(d+1);
            res=0,mul=1;
        }
    }
    if(res!=0){
        ans+=res*mul*b;
        ans-=res*mul*a;
    }
    cout << fixed << setprecision(2) << ans;
}