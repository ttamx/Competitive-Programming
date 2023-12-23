#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

struct fenwick{
    int t[N];
    void add(int i,int v){
        while(i<N)t[i]+=v,i+=i&-i;
    }
    int read(int i){
        int res=0;
        while(i>0)res+=t[i],i-=i&-i;
        return res;
    }
}f;

int n;
int a[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        f.add(i,1);
    }
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        int l=1,r=n;
        while(l<r){
            int m=(l+r)/2;
            if(f.read(m)>=x)r=m;
            else l=m+1;
        }
        f.add(l,-1);
        cout << a[l] << '\n';
    }
}