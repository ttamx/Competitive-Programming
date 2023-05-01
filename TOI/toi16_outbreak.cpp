#include<bits/stdc++.h>

using namespace std;

typedef tuple<int,int,int> t3;
typedef tuple<int,int,int,int> t4;

const int N=1e5+5;

int dx[4]={-1,0,1,0};
int dy[4]={0,-1,0,1};

int n,T,f,s,q,all,qua;
map<pair<int,int>,t3> mp;
priority_queue<t4,vector<t4>,greater<t4>> pq;

void upd(int x,int y,int t){
    auto it=mp.find({x,y});
    if(it==mp.end())return;
    auto &[hp,st,ti]=it->second;
    if(st!=3)return;
    int sum=0,cnt=0;
    for(int i=0;i<4;i++){
        int xx=x+dx[i];
        int yy=y+dy[i];
        auto it=mp.find({xx,yy});
        if(it==mp.end())continue;
        auto &[hp,st,ti]=it->second;
        if(st==1){
            cnt++;
            sum+=f-hp-ti;
        }
    }
    if(cnt){
        ti=max(t,(int)ceil(1.0*(hp-sum)/cnt));
        pq.emplace(ti,2,x,y);
    }else{
        ti=-1;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> T >> f >> s >> q;
    for(int i=1;i<=n;i++){
        int x,y,h,v;
        cin >> x >> y >> h >> v;
        auto &[hp,st,ti]=mp[{x,y}];
        hp=h;
        st=3;
        ti=-1;
        if(v){
            if(h>q){
                ti=0;
                pq.emplace(0,2,x,y);
            }else{
                st=0;
                qua++;
                all++;
            }
        }
    }
    while(!pq.empty()){
        auto [t,d,x,y]=pq.top();
        pq.pop();
        if(t>T)break;
        auto &[hp,st,ti]=mp[{x,y}];
        if(st<=d||(d==2&&t!=ti))continue;
        st=d;
        if(d==2){
            all++;
            pq.emplace(t+max(1,hp-s),1,x,y);
            pq.emplace(t+max(1,hp-q),0,x,y);
        }else{
            qua+=(d==0);
            for(int i=0;i<4;i++)upd(x+dx[i],y+dy[i],t);
        }
    }
    cout << all-qua << '\n' << qua;
}