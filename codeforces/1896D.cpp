#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,q;
    cin >> n >> q;
    int sum=0;
    vector<int> a(n+2);
    set<int> s;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        if(a[i]==1)s.emplace(i);
        sum+=a[i];
    }
    while(q--){
        int t;
        cin >> t;
        if(t==1){
            int x;
            cin >> x;
            if(x>sum){
                cout << "NO\n";
            }else if(s.empty()){
                cout << (x%2==sum%2?"YES":"NO") << "\n";
            }else{
                int l=*s.begin(),r=*s.rbegin();
                int val=sum-(l+n-r-1-max(l-1,n-r))*2;
                if(x<=val)cout << "YES\n";
                else cout << (x%2==val%2?"YES":"NO") << "\n";
            }
        }else{
            int x,y;
            cin >> x >> y;
            if(a[x]==1)s.erase(x);
            sum+=y-a[x];
            a[x]=y;
            if(a[x]==1)s.emplace(x);
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}