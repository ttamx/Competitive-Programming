#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<tuple<int,int,int>> a(n);
    for(auto &[x,y,r]:a){
        cin >> x >> y >> r;
    }
    map<pair<int,int>,int> cnt;
    vector<pair<int,int>> qr(q);
    for(auto &[x,y]:qr){
        cin >> x >> y;
        cnt[{x,y}];
    }
    for(auto &[x,y,r]:a){
        for(int dx=-r;dx<=r;dx++){
            for(int dy=-r;dy<=r;dy++){
                if(dx*dx+dy*dy>r*r)continue;
                auto it=cnt.find({x+dx,y+dy});
                if(it!=cnt.end()){
                    it->second++;
                }
            }
        }
    }
    for(auto &[x,y]:qr){
        cout << cnt[{x,y}] << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}