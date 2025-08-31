// I've read the editorial last month :/
#pragma GCC optimize("O3, unroll-loops")
#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;

ll n,d,x;
int a[N],b[N],pos[N];
vector<int> good;

ll getNextX() {
    x = (x * 37 + 10007) % 1000000007;
    return x;
}
void initAB() {
    for(int i = 0; i < n; i = i + 1){
        a[i] = i + 1;
    }
    for(int i = 0; i < n; i = i + 1){
        swap(a[i], a[getNextX() % (i + 1)]);
    }
    for(int i = 0; i < n; i = i + 1){
        if (i < d)
            b[i] = 1;
        else
            b[i] = 0;
    }
    for(int i = 0; i < n; i = i + 1){
        swap(b[i], b[getNextX() % (i + 1)]);
    }
}

int solve(int i){
    int t=max(n-1000,1LL);
    for(int j=n;j>=t;j--){
        if(pos[j]<=i&&b[i-pos[j]]){
            return j;
        }
    }
    int res=0;
    for(auto j:good){
        if(j>i)break;
        res=max(res,a[i-j]*b[j]);
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> d >> x;
    initAB();
    for(int i=1;i<=n;i++)pos[a[i]]=i;
    for(int i=0;i<n;i++)if(b[i])good.emplace_back(i);
    for(int i=0;i<n;i++){
        cout << solve(i) << "\n";
    }
}