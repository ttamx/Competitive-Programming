#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,q;
    cin >> n >> q;
    for(int i=1;i<n;i++)cout << i << " " << i+1 << "\n";
    int v=2;
    while(q--){
        int d;
        cin >> d;
        if(v==d+1){
            cout << "-1 -1 -1\n";
        }else{
            cout << 1 << " " << v << " " << d+1 << "\n";
            v=d+1;
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}