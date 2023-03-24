#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    int sum=0;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        if(x&1)sum-=x;
        else sum+=x;
    }
    cout << (sum>0?"YES":"NO") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}