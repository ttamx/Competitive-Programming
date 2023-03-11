#include<bits/stdc++.h>

using namespace std;

int n;
int a1,a2,a3;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    int pre=0;
    for(int i=0;i<n;++i){
        int x;
        cin >> x;
        if(x==10)++a2;
        if(x==13)++a3;
        if(x==10&&pre==13)++a1;
        pre=x;
    }
    cout << ++a1 << ' ' << ++a2 << ' ' << ++a3;
}
