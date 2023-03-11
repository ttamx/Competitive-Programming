#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

bool notprime[100];
vector<int> prime;

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(n),b;
    for(auto &x:a)cin >> x;
    vector<set<int>> r(100);
    for(int i=0;i<n;i++)for(int j=i+1;j<n;j++){
        ll dif=llabs(a[i]-a[j]);
        if(dif==0){
            cout << "NO\n";
            return;
        }
        for(auto x:prime)if(dif%x==0)r[x].insert(a[i]%x);
    }
    for(auto i:prime){
        if(r[i].size()==i){
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<100;i++){
        if(notprime[i])continue;
        prime.push_back(i);
        for(int j=i;j<100;j+=i)notprime[j]=true;
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}