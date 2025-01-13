#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;

int n;
int a[N];
vector<ll> dp[2*N][2][2];
int idx;

void update(vector<ll> &a,const vector<ll> &b){
    for(int i=0;i<b.size();i++){
        if(a.size()==i){
            a.emplace_back(b[i]);
        }else{
            a[i]=max(a[i],b[i]);
        }
    }
}

vector<ll> merge(const vector<ll> &a,const vector<ll> &b){
    if(a.empty()||b.empty())return {};
    vector<ll> c{a[0]+b[0]};
    for(int i=1,j=1;i<a.size()||j<b.size();){
        if(j==b.size()||(i<a.size()&&a[i]-a[i-1]>b[j]-b[j-1])){
            c.emplace_back(a[i]-a[i-1]);
            i++;
        }else{
            c.emplace_back(b[j]-b[j-1]);
            j++;
        }
    }
    for(int i=1;i<c.size();i++){
        c[i]+=c[i-1];
    }
    return c;
}

int dnc(int l,int r){
    int cur=++idx;
    if(l==r){
        dp[cur][0][0]={0LL,a[l]};
        dp[cur][1][1]={0LL};
    }else{
        int m=(l+r)/2;
        int li=dnc(l,m),ri=dnc(m+1,r);
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){   
                for(int k=0;k<2;k++){
                    update(dp[cur][i][k],merge(dp[li][i][j],dp[ri][1-j][k]));
                }
            }
        }
    }
    for(int i=1;i>=0;i--){
        for(int j=1;j>=0;j--){
            if(i==0)update(dp[cur][i][j],dp[cur][i+1][j]);
            if(j==0)update(dp[cur][i][j],dp[cur][i][j+1]);
        }
    }
    return cur;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    dnc(1,n);
    for(int i=1;i<=(n+1)/2;i++){
        cout << dp[1][0][0][i] << "\n";
    }
}