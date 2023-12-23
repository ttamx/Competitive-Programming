#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<ll> vl;

const int N=(1<<20)+5;

int n,m;
ll p;
ll q[N];
vl a;

void dft(vl &a,int k){
    int n=a.size();
    if(n==1)return;
    vl p[2];
    for(int i=0;i<n;i++)p[i&1].emplace_back(a[i]);
    dft(p[0],k*2),dft(p[1],k*2);
    int mid=n/2;
    for(int i=0;i<n;i++)a[i]=(p[0][i%mid]+q[k*i]*p[1][i%mid])%m;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> p;
    a.resize(n);
    for(auto &x:a)cin >> x;
    q[0]=1;
    for(int i=1;i<n;i++)q[i]=q[i-1]*p%m;
    dft(a,1);
    ll sum=0;
    for(auto x:a)sum=(sum+x)%m;
    cout << sum << "\n";
    for(int i=1;i<n;i++)cout << a[i] << " ";
    cout << a[0];
}