#include<bits/stdc++.h>

using namespace std;

void runcase(){
    string n;
    cin >> n;
    int a=0,b=0,d=0;
    for(auto x:n){
        x-='0';
        a*=10,b*=10;
        a+=x/2,b+=x/2;
        if(x&1){
            if(d>0){
                b++;
                d--;
            }else{
                a++;
                d++;
            }
        }
    }
    cout << a << ' ' << b << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}