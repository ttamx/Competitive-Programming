#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=20'005;
const int B=145;
const int X=10'000'005;

int lp[X];
vector<int> primes;

int n,q;
int a[N];
vector<tuple<int,int,int>> qr[N];
bool ans[N];

int cnt[X];
int nimber;

void update(int i,int v){
    int x=a[i];
    while(x>1){
        int p=lp[x];
        nimber^=cnt[p];
        while(x%p==0){
            cnt[p]+=v;
            x/=p;
        }
        nimber^=cnt[p];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<X;i++){
        if(!lp[i]){
            lp[i]=i;
            primes.emplace_back(i);
        }
        for(int j=0;j<primes.size()&&1LL*i*primes[j]<X&&primes[j]<=lp[i];j++){
            lp[i*primes[j]]=primes[j];
        }
    }
    cin >> n >> q;
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    for(int i=0;i<q;i++){
        int l,r;
        cin >> l >> r;
        l--,r--;
        qr[r/B].emplace_back(l,r,i);
    }
    int st=0,ed=0;
    update(0,+1);
    for(int b=0;b<B;b++){
        auto &v=qr[b];
        sort(v.begin(),v.end());
        for(auto [l,r,i]:v){
            while(ed<r){
                ed++;
                update(ed,+1);
            }
            while(st>l){
                st--;
                update(st,+1);
            }
            while(ed>r){
                update(ed,-1);
                ed--;
            }
            while(st<l){
                update(st,-1);
                st++;
            }
            ans[i]=(nimber>0);
        }
    }
    for(int i=0;i<q;i++){
        cout << (ans[i]?"IGNACIO":"COUSIN") << "\n";
    }
}