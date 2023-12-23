#include<bits/stdc++.h>

using namespace std;

vector<int> prime;
bool b[1005];

void runcase(){
    int n;
    cin >> n;
    map<int,int> mp;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        for(auto p:prime){
            while(x%p==0)mp[p]++,x/=p;
        }
        if(x>0)mp[x]++;
    }
    for(auto [x,y]:mp)if(y%n)return void(cout << "NO\n");
    cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<=1000;i++){
        if(b[i])continue;
        prime.emplace_back(i);
        for(int j=i+i;j<=1000;j+=i)b[j]=true;
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}