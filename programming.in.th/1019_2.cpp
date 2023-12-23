#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=205;
const ll MOD=1e9+7;
const ll MUL=29;

int n,m;
string a,b;
ll qsa[N],qsb[N],pw[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> a >> b;
    n=a.size(),m=b.size();
    a=" "+a,b=" "+b;
    pw[0]=1;
    for(int i=1;i<N;i++)pw[i]=pw[i-1]*MUL%MOD;
    for(int i=1;i<=n;i++)qsa[i]=(qsa[i-1]+(a[i]-'A'+1)*pw[i])%MOD;
    for(int i=1;i<=m;i++)qsb[i]=(qsb[i-1]+(b[i]-'A'+1)*pw[i])%MOD;
    for(int sz=min(n,m);sz>=1;sz--){
        for(int i=sz;i<=n;i++){
            ll vala=(qsa[i]-qsa[i-sz]+MOD)%MOD;
            for(int j=sz;j<=m;j++){
                ll valb=(qsb[j]-qsb[j-sz]+MOD)%MOD;
                int d=j-i;
                if(d>0){
                    if(vala*pw[d]%MOD==valb){
                        cout << a.substr(i-sz+1,sz);
                        exit(0);
                    }
                }else{
                    if(vala==valb*pw[-d]%MOD){
                        cout << a.substr(i-sz+1,sz);
                        exit(0);
                    }
                }
            }
        }
    }
}