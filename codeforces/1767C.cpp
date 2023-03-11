#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=105;
const ll mod=998244353;

int n;
int a[N][N];
int p1[N],p2[N];
ll diff[N],same[N];

int fp1(int u){
    if(u==p1[u])return u;
    return p1[u]=fp1(p1[u]);
}

int fp2(int u){
    if(u==p2[u])return u;
    return p2[u]=fp2(p2[u]);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    iota(p1,p1+n+1,0);
    iota(p2,p2+n+1,0);
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            cin >> a[i][j];
            if(i==j){
                if(a[i][j]==2){
                    cout << 0;
                    return 0;
                }
            }else if(a[i][j]==1){
                for(int k=i+1;k<=j;k++)p1[fp1(k)]=fp1(i);
            }else if(a[i][j]==2){
                for(int k=i+1;k<=j;k++)p2[fp2(k)]=fp2(i);
            }
        }
    }
    vector<int> v1,v2;
    v1.push_back(0);
    v2.push_back(0);
    for(int i=1;i<=n;i++){
        if(fp1(i)!=fp1(i+1))v1.push_back(i);
        if(fp2(i)!=fp2(i+1))v2.push_back(i);
    }
    int idx=1;
    for(auto i:v1)cout << i << ' ';
    cout << '\n';
    for(auto i:v2)cout << i << ' ';
    cout << '\n';
    for(int i=1;i<v1.size();i++){
        while(idx<v2.size()&&v2[idx]<=v1[i]){
            if(v2[idx-1]+1!=v2[idx]&&v2[idx-1]>=v1[i-1]){
                cout << 0;
                return 0;
            }
            idx++;
        }
    }
        for(int i=1;i<=n;i++)for(int j=1;j<=i;j++){
        if(i==j){
            if(a[j][i]<2){
                same[j][i]=2;
            }else{
                cout << 0;
                return 0;
            }
        }else if(a[j][i]==0){
            diff[j][i]=(diff[j][i-1]*2+same[j][i-1])%mod;
            same[j][i]=same[j][i-1];
        }else if(a[j][i]==1){
            if(same[j][i-1]==0){
                cout << 0;
                return 0;
            }
            same[j][i]=same[j][i-1];
        }else if(a[j][i]==2){
            diff[j][i]=(diff[j][i-1]*2+same[j][i-1])%mod;
        }
    }
    cout << "done";
}