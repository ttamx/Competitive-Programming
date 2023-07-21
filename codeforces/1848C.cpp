#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    auto sol=[&](int x,int y){
        int cnt=0;
        while(y!=0){
            if(x>=2*y){
                x%=2*y;
            }else if(x>=y){
                cnt++;
                cnt%=3;
                tie(x,y)=make_pair(y,x-y);
            }else{
                cnt++;
                cnt%=3;
                tie(x,y)=make_pair(y,y-x);
            }
        }
        if(x==0&&y==0)return -1;
        return cnt;
    };
    set<int> s;
    for(int i=0;i<n;i++)s.emplace(sol(a[i],b[i]));
    if(s.count(-1))s.erase(-1);
    cout << (s.size()<=1?"YES":"NO") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}