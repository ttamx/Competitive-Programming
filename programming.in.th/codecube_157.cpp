#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int n;
bool zero;
ll add,sub,mul=1;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n;i++){
        char c;
        int x;
        cin >> c >> x;
        if(c=='+')add+=x;
        else if(c=='-')sub+=x;
        else if(x)mul*=x;
        else zero=true;
    }
    cout << add*mul-(zero?0:sub);
}