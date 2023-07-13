#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k,x;
    cin >> n >> k >> x;
    if(x>1){
        cout << "YES\n";
        cout << n << "\n";
        for(int i=1;i<=n;i++)cout << 1 << " \n"[i==n];
    }else if(k==1){
        cout << "NO\n";
    }else if(k==2){
        if(n&1)cout << "NO\n";
        else{
            cout << "YES\n";
            cout << n/2 << "\n";
            for(int i=1;i<=n/2;i++)cout << 2 << " \n"[i==n/2];
        }
    }else{
        cout << "YES\n";
        if(n&1){
            cout << (n-3)/2+1 << "\n";
            for(int i=1;i<=(n-3)/2;i++)cout << "2 ";
            cout << "3\n";
        }else{
            cout << n/2 << "\n";
            for(int i=1;i<=n/2;i++)cout << 2 << " \n"[i==n/2];
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}