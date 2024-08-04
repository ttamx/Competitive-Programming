#include<bits/stdc++.h>

using namespace std;

using T = tuple<int,int,int>;

const int N=2e5+5;

int n;
int x[N],y[N];
char d[N];
map<int,set<pair<int,int>>> diag[4],str[2];
string pat[4]={"ES","SW","NW","EN"};
string pat2[2]={"EW","SN"};
priority_queue<T,vector<T>,greater<T>> pq;
bool del[N];

int dist(int i,int j){
    return abs(x[i]-x[j])+abs(y[i]-y[j]);
}

vector<int> getdiag(char c){
    if(c=='S')return {0,1};
    if(c=='W')return {2,1};
    if(c=='N')return {2,3};
    if(c=='E')return {0,3};
    return {};
}

void update(int i){
    if(del[i])return;
    del[i]=true;
    int mul=1;
    for(int j:getdiag(d[i])){
        auto &s=diag[j][x[i]+mul*y[i]];
        auto r=s.erase(s.find({x[i],i}));
        if(r!=s.begin()&&r!=s.end()){
            auto l=prev(r);
            auto [p1,i1]=*l;
            auto [p2,i2]=*r;
            if(d[i1]==pat[j][0]&&d[i2]==pat[j][1]){
                pq.emplace(dist(i1,i2),i1,i2);
            }
        }
        mul=-1;
    }
    bool hor=(d[i]=='E'||d[i]=='W');
    auto &s=hor?str[0][y[i]]:str[1][x[i]];
    auto it=s.erase(s.find({hor?x[i]:y[i],i}));
    if(it!=s.begin()&&it!=s.end()){
        auto [p1,i1]=*prev(it);
        auto [p2,i2]=*it;
        if(d[i1]==pat2[!hor][0]&&d[i2]==pat2[!hor][1]){
            pq.emplace(dist(i1,i2),i1,i2);
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> x[i] >> y[i] >> d[i];
        auto v=getdiag(d[i]);
        diag[v[0]][x[i]+y[i]].emplace(x[i],i);
        diag[v[1]][x[i]-y[i]].emplace(x[i],i);
        if(d[i]=='E'||d[i]=='W'){
            str[0][y[i]].emplace(x[i],i);
        }else{
            str[1][x[i]].emplace(y[i],i);
        }
    }
    for(int i=0;i<4;i++){
        for(auto &[_,s]:diag[i]){
            if(s.size()<2)continue;
            for(auto it=next(s.begin());it!=s.end();it++){
                auto [p1,i1]=*prev(it);
                auto [p2,i2]=*it;
                if(d[i1]==pat[i][0]&&d[i2]==pat[i][1]){
                    pq.emplace(dist(i1,i2),i1,i2);
                }
            }
        }
    }
    for(int i=0;i<2;i++){
        for(auto &[_,s]:str[i]){
            if(s.size()<2)continue;
            for(auto it=next(s.begin());it!=s.end();it++){
                auto [p1,i1]=*prev(it);
                auto [p2,i2]=*it;
                if(d[i1]==pat2[i][0]&&d[i2]==pat2[i][1]){
                    pq.emplace(dist(i1,i2),i1,i2);
                }
            }
        }
    }
    while(!pq.empty()){
        auto [d,i,j]=pq.top();
        pq.pop();
        if(del[i]||del[j])continue;
        vector<pair<int,int>> col{{i,j}};
        while(!pq.empty()){
            auto [dd,ii,jj]=pq.top();
            if(dd>d)break;
            pq.pop();
            if(del[ii]||del[jj])continue;
            col.emplace_back(ii,jj);
        }
        for(auto [i,j]:col){
            update(i);
            update(j);
        }
    }
    for(int i=1;i<=n;i++)if(!del[i])cout << i << "\n";
}