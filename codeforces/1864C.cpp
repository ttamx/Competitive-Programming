#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

bool d[N];
vector<int> prime;

void runcase(){
    int x;
    cin >> x;
    vector<int> ans;
    map<int,int> cnt;
    cnt[1]=1;
    while(x!=(x&-x)){
        ans.emplace_back(x);
        x-=x&-x;
    }
    while(x>0){
        ans.emplace_back(x);
        x>>=1;
    }
    cout << ans.size() << "\n";
    for(auto x:ans)cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<N;i++){
        if(d[i])continue;
        prime.emplace_back(i);
        for(int j=i+i;j<N;j+=i)d[j]=true;
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}