#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m,h;
    cin >> n >> m >> h;
    vector<tuple<int,long long,int>> vec;
    for(int i=0;i<n;i++){
        vector<int> p(m);
        for(auto &x:p)cin >> x;
        sort(p.begin(),p.end());
        long long sum=0;
        int cnt=0;
        int pre=0;
        for(auto x:p){
            pre+=x;
            if(pre>h)break;
            sum+=pre;
            cnt++;
        }
        vec.emplace_back(cnt,-sum,-i);
    }
    sort(vec.rbegin(),vec.rend());
    for(int i=0;i<n;i++)if(get<2>(vec[i])==0)return void(cout << i+1 << "\n");
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}