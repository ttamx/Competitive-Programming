#include<bits/stdc++.h>

using namespace std;

const int N=32000;

bool b[N];
vector<int> p;

void runcase(){
    int n,m;
    cin >> n;
    map<int,int> mp;
    while(n--){
        int x;
        cin >> x;
        for(int i=0;i<p.size();i++){
            if(x%p[i])continue;
            mp[i]++;
            while(x%p[i]==0)x/=p[i];
        }
        if(x>1)mp[x]++;
    }
    bool ans=false;
    for(auto [a,b]:mp){
        if(b>=2){
            ans=true;
            break;
        }
    }
    if(ans)cout << "YES\n";
    else cout << "NO\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<N;i++){
        if(b[i])continue;
        p.push_back(i);
        for(int j=i;j<N;j+=i)b[j]=true;
    }
    int t;
    cin >> t;
    while(t--)runcase();
}