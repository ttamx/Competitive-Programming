    #include<bits/stdc++.h>

    using namespace std;

    const int N=5005;

    int n,q;
    int a[N];

    int main(){
        cin.tie(nullptr)->sync_with_stdio(false);
        cin >> n >> q;
        for(int i=1;i<=n;i++){
            cin >> a[i];
        }
        while(q--){
            int op,l,r;
            cin >> op >> l >> r;
            if(op==1){
                swap(a[l],a[r]);
            }else{
                vector<int> b;
                for(int i=l;i<=r;i++){
                    b.emplace_back(a[i]);
                }
                sort(b.begin(),b.end());
                auto c=b;
                for(int i=1;i<b.size();i++){
                    b[i]|=b[i-1];
                }
                for(int i=c.size()-2;i>=0;i--){
                    c[i]&=c[i+1];
                }
                int ans=0;
                for(int i=0;i<b.size();i++){
                    if(b[i]==c[i]){
                        ans++;
                    }
                }
                assert(ans<=20);
                cout << ans << "\n";
            }
        }
    }