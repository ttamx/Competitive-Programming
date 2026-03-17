#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1<<20;
const int MOD=1e9+7;

ll f[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    for(int i=0;i<N;i++){
        f[i]=1;
    }
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        f[x]=(f[x]*2)%MOD;
    }
    for(int i=1;i<N;i<<=1){
        for(int j=0;j<N;j++){
            if(j&i){
                f[j^i]=(f[j^i]*f[j])%MOD;
            }
        }
    }
    for(int i=N;i>>=1;){
        for(int j=0;j<N;j++){
            if(j&i){
                f[j^i]=(f[j^i]-f[j]+MOD)%MOD;
            }
        }
    }
    cout << f[0] << "\n";
}