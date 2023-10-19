#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    string s;
    cin >> s;
    int n=s.size();
    ll pos;
    cin >> pos;
    int id=0;
    while(pos>n-id)pos-=n-id++;
    deque<char> dq;
    for(auto x:s){
        while(id>0&&!dq.empty()&&dq.back()>x)dq.pop_back(),id--;
        dq.emplace_back(x);
    }
    while(id--)dq.pop_back();
    cout << dq[pos-1];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}