#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<int> p(n),q(n);
    set<int> sp,sq;
    for(int i=1;i<=n;i++){
        sp.insert(i);
        sq.insert(i);
    }
    for(int i=0;i<n;i++){
        if(sp.find(a[i])!=sp.end()){
            p[i]=a[i];
            sp.erase(a[i]);
        }else if(sq.find(a[i])!=sq.end()){
            q[i]=a[i];
            sq.erase(a[i]);
        }else{
            cout << "NO\n";
            return;
        }
    }
    for(int i=0;i<n;i++){
        if(!p[i]){
            auto it=sp.upper_bound(q[i]);
            if(it==sp.begin()){
                cout << "NO\n";
                return;
            }
            it=prev(it);
            p[i]=*it;
            sp.erase(it);
        }else if(!q[i]){
            auto it=sq.upper_bound(p[i]);
            if(it==sq.begin()){
                cout << "NO\n";
                return;
            }
            it=prev(it);
            q[i]=*it;
            sq.erase(it);
        }
    }
    cout << "YES\n";
    for(auto x:p)cout << x << ' ';
    cout << '\n';
    for(auto x:q)cout << x << ' ';
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}