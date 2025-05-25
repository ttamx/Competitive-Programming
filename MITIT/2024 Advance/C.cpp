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

int grundy_brute(int n,int k,int state){
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
                vals.emplace_back(grundy_brute(n,k,encode(b)));
            }
        }
    }
    return dp[n][k][state]=mex(vals);
}

int grundy(int len,int l,int r){
    if(len==0)return 0;
    if(l==2&&r==2)return len&1;
    if(l==2||r==2)return len;
    return (len^l^r)&1;
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
        bool sub2=true;
        for(int i=1;i<n;i++){
            if(s[i-1]=='W'&&s[i]=='W'){
                sub2=false;
            }
        }
        if(k==0||sub2){
            int l=0,r=n-1;
            while(l<n&&s[l]=='W')l++;
            while(r>=0&&s[r]=='W')r--;
            if(l==n){
                cout << (grundy(n,2,2)?"Amy":"Aimee") << "\n";
                continue;
            }
            int ans=0;
            for(int i=l;i+1<=r;){
                int j=i+1;
                while(s[j]=='W')j++;
                ans^=grundy(j-i-1,to_num(s[i]),to_num(s[j]));
                i=j;
            }
            ans^=grundy(l,2,to_num(s[l]));
            ans^=grundy(n-r-1,to_num(s[r]),2);
            cout << (ans?"Amy":"Aimee") << "\n";
        }else{
            int state=0;
            for(auto x:s){
                state=state*3+to_num(x);
            }
            cout << (grundy_brute(n,k,state)?"Amy":"Aimee") << "\n";
        }
    }
}