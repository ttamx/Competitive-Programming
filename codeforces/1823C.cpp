#include<bits/stdc++.h>

using namespace std;

const int N=3200;

bool notprime[N];
vector<int> prime;

void runcase(){
    int n;
    cin >> n;
    map<int,int> mp;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        for(auto p:prime)while(x%p==0)mp[p]++,x/=p;
        if(x>1)mp[x]++;
    }
    int ans=0,cnt=0;
    for(auto [x,y]:mp){
        ans+=y/2;
        cnt+=y%2;
    }
    ans+=cnt/3;
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    notprime[0]=notprime[1]=true;
    for(int i=2;i<N;i++){
        if(notprime[i])continue;
        prime.emplace_back(i);
        for(int j=i+i;j<N;j+=i)notprime[j]=true;
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}