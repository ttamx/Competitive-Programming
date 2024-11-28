#include<bits/stdc++.h>

using namespace std;

const int B=1<<30;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    int ans=0;
    for(int b=1;b<B;b<<=1){
        vector<int> l,r;
        for(auto x:a){
            ((x&b)?r:l).emplace_back(x);
        }
        int c=0;
        for(int t=0;t<2;t++){
            for(int i=l.size()-1,p=0;i>=0;i--){
                while(p<l.size()&&!((l[i]+l[p])&b)){
                    p++;
                }
                if(p<=i){
                    c^=(i-p+1)&1;
                }
            }
            swap(l,r);
        }
        for(int i=r.size()-1,p=0;i>=0;i--){
            while(p<l.size()&&((r[i]+l[p])&b)){
                p++;
            }
            c^=p&1;
        }
        ans|=c*b;
        l.insert(l.end(),r.begin(),r.end());
        a=move(l);
    }
    cout << ans;
}