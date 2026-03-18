#include<bits/stdc++.h>

using namespace std;

using ll = long long;

ll solve(vector<int> a){
    if(*min_element(a.begin(),a.end())<0){
        return -1LL;
    }
    if(a.size()==1){
        return (1LL<<a[0])-1;
    }
    for(int t=0;t<2;t++){
        vector<int> b;
        if(t){
            b.emplace_back(a[0]-1);
        }
        bool ok=true;
        for(int i=t;i<a.size();i+=2){
            if(i+1<a.size()&&a[i]+1!=a[i+1]){
                ok=false;
                break;
            }
            b.emplace_back(a[i]);
        }
        if(!ok)continue;
        ll res=solve(b);
        if(res!=-1)return res*2+t;
    }
    return -1LL;
}

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    cout << solve(a) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}