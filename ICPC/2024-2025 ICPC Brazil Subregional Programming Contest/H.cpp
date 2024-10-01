#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s,t;
    cin >> s >> t;
    int k=0;
    for(auto x:s)if(x=='*')k++;
    for(auto x:t)if(x=='*')k++;
    int m=s.size(),n=t.size();
    for(int mask=0;mask<1<<k;mask++){
        string s2=s,t2=t;
        int k2=0;
        for(auto &x:s2){
            if(x=='*'){
                x=(mask>>k2&1)+'0';
                k2++;
            }
        }
        for(auto &x:t2){
            if(x=='*'){
                x=(mask>>k2&1)+'0';
                k2++;
            }
        }
        int den=0;
        for(auto x:t2){
            den<<=1;
            if(x=='1')den++;
        }
        int rem=0;
        for(auto x:s2){
            rem*=2;
            if(x=='1')rem++;
            rem%=den;
        }
        if(rem==0){
            cout << s2;
            exit(0);
        }
    }
    assert(false);
}