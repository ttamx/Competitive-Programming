#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<int> pos(n);
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        pos[x]=i;
    }
    vector<int> l(m+n),r(m+n);
    priority_queue<pair<int,int>> sl;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> sr;
    vector<bool> del(m+n);
    for(int i=0;i<m;i++){
        cin >> l[i] >> r[i];
        l[i]--,r[i]--;
        sl.emplace(l[i],i);
        sr.emplace(r[i],i);
    }
    int buf=m;
    long long ans=0;
    int tot=0;
    for(int i=0;i<n;i++){
        int p=pos[i];
        int cnt=0;
        int cl=-1,cr=n;
        while(!sl.empty()&&sl.top().first>p){
            int j=sl.top().second;
            sl.pop();
            if(del[j])continue;
            del[j]=true;
            // cerr << j+1 << " : " << i << "\n";
            cnt++;
            cl=max(cl,l[j]);
            cr=min(cr,r[j]);
        }
        while(!sr.empty()&&sr.top().first<p){
            int j=sr.top().second;
            sr.pop();
            if(del[j])continue;
            del[j]=true;
            // cerr << j+1 << " : " << i << "\n";
            cnt++;
            cl=max(cl,l[j]);
            cr=min(cr,r[j]);
        }
        if(cnt>0){
            ans+=1LL*(cnt-1)*i;
            tot+=cnt-1;
            l[buf]=cl;
            r[buf]=cr;
            // cerr << "PUSH " << buf+1 << " " << cl << " " << cr << "\n";
            sl.emplace(l[buf],buf);
            sr.emplace(r[buf],buf);
            buf++;
        }
    }
    // cerr << tot << "\n";
    ans+=1LL*(m-1-tot)*n;
    cout << ans << "\n";
}