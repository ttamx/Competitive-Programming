#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        cout << 1 << ' ';
        if(i>0){
            for(int j=1;j<i;j++)cout << 0 << ' ';
            cout << 1 << ' ';
        }
        cout << '\n';
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}