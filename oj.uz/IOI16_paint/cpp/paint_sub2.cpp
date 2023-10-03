#include "paint.h"
#include <bits/stdc++.h>

using namespace std;

string solve_puzzle(string s, vector<int> c) {
    int n=s.size();
    vector<int> v(n);
    for(int i=0;i<1<<n;i++){
        int cnt=0,cur=0;
        bool ok=true;
        for(int j=0;j<n;j++){
            if(i>>j&1){
                cnt++;
            }else if(cnt>0){
                if(cur>=c.size()||c[cur]!=cnt){
                    ok=false;
                    break;
                }
                cnt=0;
                cur++;
            }
        }
        if(cnt>0){
            if(cur>=c.size()||c[cur]!=cnt){
                ok=false;
            }else{
                cur++;
            }
        }
        if(cur!=c.size())ok=false;
        if(ok){
            for(int j=0;j<n;j++){
                if(i>>j&1){
                    v[j]|=1;
                }else{
                    v[j]|=2;
                }
            }
        }
    }
    string ans="";
    for(auto x:v){
        if(x==1)ans+='X';
        if(x==2)ans+='_';
        if(x==3)ans+='?';
    }
    return ans;
}