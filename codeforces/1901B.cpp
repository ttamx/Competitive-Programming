#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    long long ans=0;
    int cur=0;
    for(int i=n-1;i>=0;i--){
        if(a[i]<cur)ans+=cur-a[i];
        cur=a[i];
    }
    ans+=cur;
    cout << ans-1 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}