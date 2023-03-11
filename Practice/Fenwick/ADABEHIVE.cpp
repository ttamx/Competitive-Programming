#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2e3+5;

int n,m,q;
ll f[N][N];

void add(int x,int y,int v){
    for(int i=x;i<N;i+=i&-i)for(int j=y;j<N;j+=j&-j)f[i][j]+=v;
}

ll read(int x,int y){
    ll ret=0;
    for(int i=x;i>0;i-=i&-i)for(int j=y;j>0;j-=j&-j)ret+=f[i][j];
    return ret;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=1;i<=n;++i)for(int j=1;j<=m;++j){
        ll x;
        cin >> x;
        add(i,j,x);
    }
    while(q--){
        ll x,a,b,c,d;
        cin >> x;
        if(x==1){
            cin >> a >> b >> c;
            add(a,b,c);
        }else{
            cin >> a >> b >> c >> d;
            --a,--b;
            cout << read(c,d)-read(a,d)-read(c,b)+read(a,b) << '\n';
        }
    }
}
