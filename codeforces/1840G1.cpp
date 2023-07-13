#include<bits/stdc++.h>

using namespace std;

void runcase(){
    auto ask=[&](int x){
        cout << "+ " << x << endl;
        int res;
        cin >> res;
        return res;
    };
    int x;
    cin >> x;
    vector<int> a(1e6+1);
    vector<bool> vis(1e6+1);
    a[x]=0;
    vis[x]=true;
    for(int i=1;i<1000;i++){
        x=ask(1);
        if(vis[x]){
            cout << "! " << i << endl;
            return;
        }
        a[x]=i;
        vis[x]=true;
    }
    for(int i=1;i<=1000;i++){
        x=ask(i==1?1:1000);
        if(vis[x]){
            cout << "! " << i*1000-a[x] << endl;
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}