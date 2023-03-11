#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    int c1=0,c2=0;
    for(auto &x:a)cin >> x,c1+=x-1;
    long long res2=1;
    int ans=-1;
    for(int i=0;i<n-1;i++){
        c1-=a[i]-1;
        c2+=a[i]-1;
        if(c1==c2){
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