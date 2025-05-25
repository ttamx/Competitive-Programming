#include<bits/stdc++.h>

using namespace std;

const int N=11;
const int S=60000;
const int K=8;

int dp[N][K][S];
bool vis[N][K][S];

int mex(const vector<int> &vals){
    vector<bool> seen(vals.size()+1);
    for(auto x:vals){
        if(x<seen.size()){
            seen[x]=true;
        }
    }
    int res=0;
    while(seen[res]){
        res++;
    }
    return res;
}

int to_num(char c){
    if(c=='R')return 0;
    if(c=='G')return 1;
    return 2;
}

int encode(const vector<int> &a){
    int res=0;
    for(auto x:a){
        res=res*3+x;
    }
    return res;
}

int grundy(int n,int k,int state){
    if(vis[n][k][state])return dp[n][k][state];
    vis[n][k][state]=true;
    int _state=state;
    vector<int> a(n);
    for(int i=0;i<n;i++){
        a[i]=_state%3;
        _state/=3;
    }
    vector<int> pos;
    for(int i=0;i<n;i++){
        if(a[i]==2){
            pos.emplace_back(i);
        }
    }
    if(pos.empty())return 0;
    int m=pos.size();
    vector<int> vals;
    for(int val=0;val<2;val++){
        for(int mask=1;mask<(1<<m);mask++){
            bool ok=true;
            int l=n-1,r=0;
            int cnt=0;
            for(int j=0;j<m;j++){
                if(mask>>j&1){
                    int idx=pos[j];
                    if(idx>0&&a[idx-1]==(val^1))ok=false;
                    if(idx+1<n&&a[idx+1]==(val^1))ok=false;
                    l=min(l,idx);
                    r=max(r,idx);
                    cnt++;
                }
            }
            if(ok&&cnt%2==1&&r-l<=k){
                auto b=a;
                for(int j=0;j<m;j++){
                    if(mask>>j&1){
                        b[pos[j]]=val;
                    }
                }
                vals.emplace_back(grundy(n,k,encode(b)));
            }
        }
    }
    return dp[n][k][state]=mex(vals);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        int n,k;
        cin >> n >> k;
        string s;
        cin >> s;
        int state=0;
        for(auto x:s){
            state=state*3+to_num(x);
        }
        cout << (grundy(n,k,state)?"Amy":"Aimee") << "\n";
    }
}