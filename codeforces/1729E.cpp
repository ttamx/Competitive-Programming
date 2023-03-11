#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    long long a,b;
    for(int i=0;i<25;++i){
        cout << "? 1 " << 3+i << endl;
        cin >> a;
        cout << "? " << 3+i << " 1" << endl;
        cin >> b;
        if(b!=a)break;
    }
    cout << "! " << a+b;
}

