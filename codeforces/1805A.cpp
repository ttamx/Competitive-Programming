#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    int x=0;
    for(int i=0;i<n;i++){
        int y;
        cin >> y;
        x^=y;
    }
    if(n%2==0&&x!=0){
        cout << -1 << '\n';
    }else{
        cout << x << '\n';
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}