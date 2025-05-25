#include<bits/stdc++.h>

using namespace std;

void solve(){
    int n;
    cin >> n;
    vector<int> a(n),b(n),c(n),d(n);
    for(int i=0;i<n;i++){
        int p,s;
        cin >> p >> s;
        (s?a:b).emplace_back(p);
    }
    for(int i=0;i<n;i++){
        int p,s;
        cin >> p >> s;
        (s?c:d).emplace_back(p);
    }
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    sort(c.begin(),c.end());
    sort(d.begin(),d.end());
    for(int t=0;t<2;t++){
        int m=b.size();
        int pos=0;
        vector<int> e(b.size());
        for(int i=0;i<b.size();i++){
            while(pos<d.size()&&d[pos]<=2*b[i]){
                pos++;
            }
            e[i]=pos-(i+1);
        }
        deque<pair<int,int>> dq;
        int same=0,diff=0,base=0,cur=0,cur2=0;
        for(auto x:a){
            base++;
            while(!dq.empty()&&b[dq.front().second]*2<x){
                dq.pop_front();
            }
            while(cur<b.size()&&b[cur]*2<=x){
                cur++;
            }
            while(cur2<b.size()&&b[cur2]<=x){
                if(b[cur2]*2>=x){
                    while(!dq.empty()&&dq.back().first>=e[cur2]){
                        dq.pop_back();
                    }
                    dq.emplace_back(e[cur2],cur2);
                }
                cur2++;
            }
            while(same<c.size()&&c[same]<=2*x){
                same++;
            }
            while(diff<d.size()&&d[diff]<=x){
                diff++;
            }
            if(same+diff<base+cur){
                cout << "NO\n";
                return;
            }
            if(!dq.empty()&&same+dq.front().first<base){
                cout << "NO\n";
                return;
            }
        }
        swap(a,b);
        swap(c,d);
    }
    cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)solve();
}