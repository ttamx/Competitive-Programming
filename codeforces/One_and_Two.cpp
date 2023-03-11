#include<bits/stdc++.h>

using namespace std;

void runcase(){
    long long res=1;
    int n;
    cin >> n;
    vector<long long> a(n);
    for(auto &x:a)cin >> x,res*=x;
    long long res2=1;
    int ans=-1;
    for(int i=0;i<n-1;i++){
        res/=a[i];
        res2*=a[i];
        if(res==res2){
            ans=i+1;
            break;
        }
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}