#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e6+5;

int n,k;
string a,b;
vector<pair<vector<int>,vector<int>>> comp;
ll ans=0;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k >> a >> b;
    vector<int> va,vb;
    for(int i=0;i<n;i++){
        if(a[i]==b[i])continue;
        if(a[i]=='1')va.emplace_back(i);
        else vb.emplace_back(i);
        if(va.size()==vb.size()){
            comp.emplace_back(va,vb);
            va.clear();
            vb.clear();
        }
    }
    for(auto &[x,y]:comp){
        if(x[0]>y[0])swap(x,y);
        reverse(x.begin(),x.end());
        set<pair<int,int>> s;
        for(auto i:y){
            while(!x.empty()&&x.back()<i){
                int j=x.back();
                x.pop_back();
                s.emplace(j%k,j);
                s.emplace(j%k+k,j);
            }
            auto [m,j]=*s.lower_bound(make_pair(i%k,0));
            m%=k;
            s.erase(make_pair(m,j));
            s.erase(make_pair(m+k,j));
            ans+=(i-j-1)/k+1;
        }
    }
    cout << ans;
}