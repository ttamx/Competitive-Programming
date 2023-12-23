#include<bits/stdc++.h>

using namespace std;

const int N=1e4;

int notprime[N];
vector<int> prime;

void runcase(){
    int l,r;
    cin >> l >> r;
    if(r<=3)return void(cout << "-1\n");
    if(r-l>0)return void(cout << r/2 << " " << r/2 << "\n");
    int num=r,ans=-1;
    for(auto p:prime)while(num%p==0)num/=p,ans=p;
    if(num==r||ans==-1||ans==r)cout << "-1\n";
    else cout << ans << " " << r-ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<N;i++){
        if(notprime[i])continue;
        prime.push_back(i);
        for(int j=i+i;j<N;j+=i)notprime[j]=true;
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}