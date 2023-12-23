#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    int sum=0,sum2=0;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        sum^=x;
    }
    for(int i=0;i<m;i++){
        int x;
        cin >> x;
        sum2|=x;
    }
    if(n&1){
        cout << sum << " " << (sum|sum2) << "\n";
    }else{
        cout << (sum&(~sum2)) << " " << sum << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}