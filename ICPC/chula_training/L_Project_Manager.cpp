#include<bits/stdc++.h>

using namespace std;

template<class T>
using heap = priority_queue<T,vector<T>,greater<T>>;

const int N=2e5+5;

string days[7]={"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};

int a[N],h[N],pt[N],ver[N];
vector<int> pr[N];
heap<pair<int,int>> event;
heap<int> todo[N];
int idx[N],ans[N];
pair<int,int> mp[128*N];
int mpl[128],mpr[128];
int buf=0;

inline void push(int t,int i){if(t>ver[i])event.emplace(ver[i]=t,i);}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,q;
    cin >> n >> m >> q;
    for(int i=0;i<n;i++){
        int d;
        cin >> d;
        while(d--){
            string s;
            cin >> s;
            int id=0;
            while(id<7&&s!=days[id])id++;
            assert(id<7);
            a[i]|=1<<id;
        }
    }
    for(int i=0;i<m;i++){
        cin >> h[i];
        h[i]--;
    }
    for(int i=0;i<q;i++){
        int k;
        cin >> k;
        pr[i].resize(k);
        for(auto &x:pr[i])cin >> x,x--;
    }
    auto nxt=[&](int mask,int d){
        int res=1;
        while(!(mask>>((d+res)%7)&1))res++;
        return res;
    };
    for(int mask=1;mask<128;mask++){
        mpl[mask]=buf;
        auto check=[&](int d){return (mask>>(d%7)&1);};
        for(int i=0;i<m;i++){
            int cur=h[i];
            if(!check(cur))continue;
            vector<int> tmp{cur};
            do{
                cur+=nxt(mask,cur%7);
                tmp.emplace_back(cur);
                while(i<m&&h[i]<cur)i++;
            }while(i<m&&cur==h[i]&&check(h[i]));
            tmp.pop_back();
            for(auto st:tmp){
                assert(buf<128*N);
                mp[buf++]={st,cur};
            }
            if(i<m&&h[i]>cur)i--;
        }
        mpr[mask]=buf;
    }
    for(int i=0;i<n;i++)pt[i]=ver[i]=-1;
    auto when=[&](int i,int d){
        int mask=a[i];
        d=max(pt[i],d);
        d+=nxt(mask,(d+7)%7);
        auto it=lower_bound(mp+mpl[mask],mp+mpr[mask],make_pair(d,-1));
        if(it!=mp+mpr[mask]&&it->first==d)d=it->second;
        return d;
    };
    for(int i=0;i<q;i++){
        int j=pr[i][0];
        push(when(j,-1),j);
        todo[j].emplace(i);
    }
    vector<tuple<int,int,int>> tmp;
    while(!event.empty()){
        auto [t,i]=event.top();
        event.pop();
        assert(!todo[i].empty());
        int j=todo[i].top();
        todo[i].pop();
        pt[i]=t;
        ans[j]=t;
        if(++idx[j]<pr[j].size()){
            int k=pr[j][idx[j]];
            tmp.emplace_back(j,k,t);
        }
        if(!todo[i].empty())push(when(i,t),i);
        if(event.empty()||event.top().first>t){
            for(auto [j,k,t]:tmp){
                push(when(k,t),k);
                todo[k].emplace(j);
            }
            tmp.clear();
        }
    }
    for(int i=0;i<q;i++)cout << ans[i]+1 << " ";
}