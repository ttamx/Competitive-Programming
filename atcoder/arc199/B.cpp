#include<bits/stdc++.h>

using namespace std;

using ull = uint64_t;

struct DS{
    ull basis[60],mask[60];
    int id[60];
    DS(){
        for(int i=0;i<60;i++){
            basis[i]=0;
            mask[i]=0;
            id[i]=-1;
        }
    }
    void insert(ull v,int idx){
        for(int i=59;i>=0;i--){
            ull cur=0;
            if(v>>i&1){
                if(!basis[i]){
                    basis[i]=v;
                    mask[i]=cur^(1LL<<i);
                    id[i]=idx;
                    return;
                }else{
                    v^=basis[i];
                    cur^=mask[i];
                }
            }
        }
    }
    pair<bool,ull> query(ull v){
        ull res=0;
        for(int i=59;i>=0;i--){
            if(v>>i&1){
                if(!basis[i]){
                    return {false,0ULL};
                }else{
                    v^=basis[i];
                    res^=mask[i];
                }
            }
        }
        return {true,res};
    }
};

void runcase(){
    int n;
    ull k;
    cin >> n >> k;
    vector<ull> a(n);
    for(auto &x:a)cin >> x;
    if(a[0]==k){
        cout << "Yes\n";
        cout << 0 << "\n\n";
        return;
    }
    {
        ull sum=0;
        for(int i=0;i<n;i++){
            sum^=a[i];
        }
        if(sum==k){
            cout << "Yes\n";
            cout << n-1 << "\n";
            for(int i=n-2;i>=0;i--){
                cout << i << " ";
            }
            cout << "\n";
            return;
        }
    }
    vector<int> ans;
    auto work=[&](int i){
        assert(i>=0&&i+1<n);
        ull x=a[i]^a[i+1];
        a[i]=a[i+1]=x;
        ans.emplace_back(i);
        // cerr << "CALL " << i << " : ";
        // for(auto x:a)cerr << x << " ";
        // cerr << "\n";
    };
    for(int i=0;i+1<n;i++){
        DS ds;
        for(int j=0;j<i;j++){
            ds.insert(a[j],j);
        }
        for(int j=i+2;j<n;j++){
            ds.insert(a[j],j);
        }
        {
            auto [ok,mask]=ds.query(k);
            if(ok){
                // cerr << "MASK : " << mask << "\n";
                vector<int> l,r;
                // cerr << "POS : ";
                for(int j=0;j<60;j++){
                    if(mask>>j&1){
                        int id=ds.id[j];
                        // cerr << id << " ";
                        (id<i?l:r).emplace_back(id);
                    }
                }
                // cerr << "\n";
                sort(l.rbegin(),l.rend());
                sort(r.begin(),r.end());
                // clear
                work(i);
                work(i);
                assert(a[i]==0);
                if(!r.empty()){
                    // cerr << "RIGHT\n";
                    for(auto j:r){
                        // cerr << "AT " << j << "\n";
                        for(int k=i+1;k+1<j;k++){
                            work(k);
                            work(k);
                        }
                        // move to i
                        for(int k=j-1;k>=i;k--){
                            work(k);
                        }
                    }
                    // clear right
                    work(i+1);
                    work(i+1);
                    // copy
                    work(i);
                    work(i+1);
                    // clear i
                    work(i);
                    work(i);
                    work(i+1);
                    // cerr << a[i] << " " << a[i+1] << "\n";
                }
                assert(a[i]==0);
                if(!l.empty()){
                    // cerr << "LEFT\n";
                    for(auto j:l){
                        for(int k=j+1;k<i;k++){
                            work(k);
                            work(k);
                        }
                        for(int k=j;k<=i;k++){
                            work(k);
                        }
                    }
                    // clear left
                    work(i-1);
                    work(i-1);
                    // cerr << a[i] << " " << a[i+1] << "\n";
                }
                assert(a[i]==0);
                // cerr << k << " " << a[i+1] << "\n";
                for(int j=0;j<i;j++){
                    work(j);
                    work(j);
                }
                for(int j=i;j>=0;j--){
                    work(j);
                }
                assert(a[0]==k);
                cout << "Yes\n";
                cout << ans.size() << "\n";
                for(auto x:ans)cout << x+1 << " ";
                cout << "\n";
                return;
            }
        }
        if(false){
            auto [ok,mask]=ds.query(k^a[i]^a[i+1]);
            if(ok){
                work(i);
                // cerr << "MASK : " << mask << "\n";
                vector<int> l,r;
                // cerr << "POS : ";
                for(int j=0;j<60;j++){
                    if(mask>>j&1){
                        int id=ds.id[j];
                        // cerr << id << " ";
                        (id<i?l:r).emplace_back(id);
                    }
                }
                // cerr << "\n";
                sort(l.rbegin(),l.rend());
                sort(r.begin(),r.end());
                if(!r.empty()){
                    int j=r[0];
                    if(j>i+2){
                        for(int k=i+1;k+1<j;k++){
                            work(k);
                            work(k);
                        }
                        for(int k=j-1;k>=i;k--){
                            work(k);
                        }
                    }else{
                        work(i+1);
                        work(i);
                        work(i);
                        work(i+1);
                        work(i);
                        work(i+1);
                        work(i+1);
                    }
                    // cerr << "RIGHT\n";
                    for(int ii=1;ii<r.size();ii++){
                        int j=r[ii];
                        // cerr << "AT " << j << "\n";
                        for(int k=i+1;k+1<j;k++){
                            work(k);
                            work(k);
                        }
                        // move to i
                        for(int k=j-1;k>=i;k--){
                            work(k);
                        }
                    }
                    // clear right
                    work(i+1);
                    work(i+1);
                    // copy
                    work(i);
                    // cerr << a[i] << " " << a[i+1] << "\n";
                }
                if(!l.empty()){
                    int j=l[0];
                    if(j<i-1){
                        for(int k=j+1;k<i;k++){
                            work(k);
                            work(k);
                        }
                        for(int k=j;k<=i;k++){
                            work(k);
                        }
                    }else{
                        work(i-1);
                        work(i);
                        work(i);
                        work(i-1);
                        work(i);
                        work(i-1);
                        work(i-1);
                    }
                    // cerr << "LEFT\n";
                    for(int ii=1;ii<l.size();ii++){
                        int j=l[ii];
                        for(int k=j+1;k<i;k++){
                            work(k);
                            work(k);
                        }
                        for(int k=j;k<=i;k++){
                            work(k);
                        }
                    }
                    // clear left
                    work(i-1);
                    work(i-1);
                    work(i);
                    // cerr << a[i] << " " << a[i+1] << "\n";
                }
                // cerr << k << " " << a[i+1] << "\n";
                for(int j=0;j<i;j++){
                    work(j);
                    work(j);
                }
                for(int j=i;j>=0;j--){
                    work(j);
                }
                assert(a[0]==k);
                cout << "Yes\n";
                cout << ans.size() << "\n";
                for(auto x:ans)cout << x+1 << " ";
                cout << "\n";
                return;
            }
        }
    }
    cout << "No\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}