#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,c;
    cin >> n >> c;
    vector<int> a(n);
    for(int i=0;i<n;i++){
        cin >> a[i];
        a[i]+=i+1;
    }
    sort(a.begin(),a.end());
    int ans=0;
    for(auto x:a){
        if(x>c)break;
        c-=x;
        ans++;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}