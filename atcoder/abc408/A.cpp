#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,s;
    cin >> n >> s;
    int last=0;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        if(x-last>s){
            cout << "No\n";
            exit(0);
        }
        last=x;
    }
    cout << "Yes\n";
}