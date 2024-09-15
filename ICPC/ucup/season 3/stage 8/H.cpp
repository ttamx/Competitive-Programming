#include<bits/stdc++.h>

using namespace std;

const bool AUTO = false;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n+1);
    iota(a.begin(),a.end(),0);
    shuffle(a.begin()+1,a.end(),rng);
    int query_count=0;
    int total_size=0;
    int target=max_element(a.begin()+1,a.end())-a.begin();
    map<pair<int,int>,int> memo;
    auto ask=[&](int l,int r){
        if(memo.count({l,r})){
            return memo[{l,r}];
        }
        assert(l<r);
        total_size+=r-l+1;
        query_count++;
        if(AUTO){
            array<pair<int,int>,2> mx;
            mx[0]=mx[1]={0,0};
            for(int i=l;i<=r;i++){
                mx[1]=max(mx[1],{a[i],i});
                if(mx[1]>mx[0]){
                    swap(mx[0],mx[1]);
                }
            }
            return mx[1].second;
        }
        cout << "? " << l << " " << r << endl;
        int res;
        cin >> res;
        return memo[{l,r}]=res;
    };
    function<int(int,int,int)> dnc=[&](int l,int r,int idx){
        if(l==r){
            return l;
        }
        if(idx==0){
            idx=ask(l,r);
        }
        int mid=(l+r)/2;
        if(idx<=mid){
            if(l==mid||ask(l,mid)!=idx){
                if(mid+1==r){
                    return r;
                }
                int mid2=(mid+1+r)/2;
                if(ask(idx,mid2)==idx){
                    return dnc(mid+1,mid2,0);
                }else{
                    return dnc(mid2+1,r,0);
                }
            }else{
                int mid2=(l+mid)/2;
                if(idx<=mid2){
                    if(l==mid2||ask(l,mid2)!=idx){
                        return dnc(mid2+1,mid,0);
                    }else{
                        return dnc(l,mid2,idx);
                    }
                }else{
                    if(mid2+1==mid||ask(mid2+1,mid)!=idx){
                        return dnc(l,mid2,0);
                    }else{
                        return dnc(mid2+1,mid,idx);
                    }
                }
            }
        }else{
            if(mid+1==r||ask(mid+1,r)!=idx){
                if(l==mid){
                    return l;
                }
                int mid2=(l+mid)/2;
                if(ask(mid2+1,idx)==idx){
                    return dnc(mid2+1,mid,0);
                }else{
                    return dnc(l,mid2,0);
                }
            }else{
                int mid2=(mid+1+r)/2;
                if(idx<=mid2){
                    if(mid+1==mid2||ask(mid+1,mid2)!=idx){
                        return dnc(mid2+1,r,0);
                    }else{
                        return dnc(mid+1,mid2,idx);
                    }
                }else{
                    if(mid2+1==r||ask(mid2+1,r)!=idx){
                        return dnc(mid+1,mid2,0);
                    }else{
                        return dnc(mid2+1,r,idx);
                    }
                }
            }
        }
    };
    int ans=dnc(1,n,0);
    cout << "! " << ans << endl;
    assert(total_size<=3*n);
    if(AUTO){
        cerr << "QUERY COUNT : " << query_count << "\n";
        cerr << "TOTAL SIZE : " << total_size << "\n";
        assert(query_count<=ceil(1.5*log2(n)));
        assert(ans==target);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        runcase();
    }
}