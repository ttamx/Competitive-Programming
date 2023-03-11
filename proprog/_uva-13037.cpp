#include<bits/stdc++.h>

using namespace std;

void runcase(){
    vector<int> c[3];
    for(int i=0;i<3;i++){
        int x;
        cin >> x;
        c[i].resize(x);
    }
    map<int,int> mp;
    for(int i=0;i<3;i++){
        for(int &x:c[i]){
            cin >> x;
            mp[x]|=(1<<i);
        }
    }
    vector<int> a(3),b(3);
    for(auto [x,y]:mp){
        int cnt=__builtin_popcount(y);
        if(cnt==1)for(int i=0;i<3;i++)if(y&(1<<i))a[i]++;
        if(cnt==2)for(int i=0;i<3;i++)if((y&(1<<i))==0)b[i]++;
    }
    for(int i=0;i<3;i++)cout << a[i] << ' ' << b[i] << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    for(int i=1;i<=t;i++){
        cout << "Case #" << i << ":\n";
        runcase();
    }
}