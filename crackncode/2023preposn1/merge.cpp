#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,c,d;
    cin >> n >> c >> d;
    c--,d--;
    int ans=0;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        ans^=x&1;
    }
    if(ans==0)return void(cout << "No\n");
    n--;
    for(int i=0;i*c<=n;i++)if((n-i*c)%d==0)return void(cout << "Yes\n");
    cout << "No\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}