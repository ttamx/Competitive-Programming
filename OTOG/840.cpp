#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int M=5e5+5;

vector<int> factor[M];

void runcase(){
    int n,m;
    cin >> n >> m;
    long long ans=0;
    for(int y=2;y<=n;y++){
        int num=m-m%y;
        if(num==0)ans+=y-1;
        else ans+=lower_bound(factor[num].begin(),factor[num].end(),y)-factor[num].begin();
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=1;i<M;i++)for(int j=i;j<M;j+=i)factor[j].emplace_back(i);
    int t;
    cin >> t;
    while(t--)runcase();   
}