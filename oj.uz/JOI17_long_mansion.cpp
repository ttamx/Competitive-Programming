#include<bits/stdc++.h>

using namespace std;

const int N=5e5+5;

int n,q;
int a[N];
vector<int> keys[N];
int l[N],r[N];
int cnt[N];

void update(int x,int v){
    for(auto i:keys[x]){
        cnt[i]+=v;
    }
}

void solve(int cl,int cr){
    if(cl==cr){
        l[cl]=r[cl]=cl;
        return;
    }
    int m=(cl+cr)/2;
    solve(cl,m);
    solve(m+1,cr);
    int st=m+1,ed=m;
    for(int i=m;i>=cl;i--){
        if(r[i]<m){
            continue;
        }
        while(st>i){
            st--;
            update(st,+1);
        }
        while(true){
            if(st>cl&&cnt[a[st-1]]>0){
                st--;
                update(st,+1);
            }else if(ed<cr&&cnt[a[ed]]>0){
                ed++;
                update(ed,+1);
            }else{
                break;
            }
        }
        l[i]=st;
        r[i]=ed;
    }
    while(st<=ed){
        update(st,-1);
        st++;
    }
    st=m+1;
    ed=m;
    for(int i=m+1;i<=cr;i++){
        if(l[i]>m+1){
            continue;
        }
        while(ed<i){
            ed++;
            update(ed,+1);
        }
        while(true){
            if(st>cl&&cnt[a[st-1]]>0){
                st--;
                update(st,+1);
            }else if(ed<cr&&cnt[a[ed]]>0){
                ed++;
                update(ed,+1);
            }else{
                break;
            }
        }
        l[i]=st;
        r[i]=ed;
    }
    while(st<=ed){
        update(st,-1);
        st++;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n-1;i++){
        cin >> a[i];
    }
    for(int i=1;i<=n;i++){
        int s;
        cin >> s;
        keys[i].resize(s);
        for(auto &x:keys[i]){
            cin >> x;
        }
    }
    solve(1,n);
    cin >> q;
    while(q--){
        int x,y;
        cin >> x >> y;
        cout << ((l[x]<=y&&y<=r[x])?"YES":"NO") << "\n";
    }
}