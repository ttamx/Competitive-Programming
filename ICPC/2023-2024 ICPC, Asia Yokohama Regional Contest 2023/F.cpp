#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    int ca=n,cb=n;
    vector<int> a(n),b(n);
    for(int i=0;i<n;i++){
        a[i]=b[i]=i%2;
    }
    while(q--){
        string op;
        int x;
        cin >> op >> x;
        x--;
        if(op=="ROW"){
            if(x>0&&a[x]!=a[x-1])ca--;
            if(x+1<n&&a[x]!=a[x+1])ca--;
            a[x]^=1;
            if(x>0&&a[x]!=a[x-1])ca++;
            if(x+1<n&&a[x]!=a[x+1])ca++;
        }else{
            if(x>0&&b[x]!=b[x-1])cb--;
            if(x+1<n&&b[x]!=b[x+1])cb--;
            b[x]^=1;
            if(x>0&&b[x]!=b[x-1])cb++;
            if(x+1<n&&b[x]!=b[x+1])cb++;
        }
        cout << 1LL*ca*cb << "\n";
    }
}