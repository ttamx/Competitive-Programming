#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    iota(a.begin(),a.end(),1);
    int fac=1;
    for(int i=1;i<=n;i++)fac*=i;
    if(k<fac/2){
        while(--k)next_permutation(a.begin(),a.end());
    }else{
        k=fac-k;
        while(--k)prev_permutation(a.begin(),a.end());
    }
    for(auto x:a)cout << x << ' ';
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}