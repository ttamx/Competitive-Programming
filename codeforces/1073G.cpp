#include "template.hpp"
#include "string/suffix-array.hpp"

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    string s;
    cin >> s;
    SuffixArray sa(s);
    while(q--){
        vector<pair<int,int>> event;
        set<int> ss;
        ll ans=0;
        int m[2];
        cin >> m[0] >> m[1];
        for(int t=0;t<2;t++){
            while(m[t]--){
                int x;
                cin >> x;
                x--;
                if(!ss.emplace(x).second)ans+=n-x;
                event.emplace_back(sa.isa[x],t);
            }
        }
        for(int t=0;t<2;t++){
            sort(event.rbegin(),event.rend());
            ll sum=0;
            int last=n-1;
            vector<pair<ll,ll>> st;
            auto push=[&](ll val,ll sz){
                while(!st.empty()&&st.back().first>val){
                    auto [h,w]=st.back();
                    st.pop_back();
                    sz+=w;
                    sum-=h*w;
                }
                st.emplace_back(val,sz);
                sum+=val*sz;
            };
            for(auto &[i,tt]:event){
                if(i<last){
                    push(sa.st.query(i+1,last),0);
                    last=i;
                }
                if(tt){
                    ans+=sum;
                }else{
                    push(sa.lcp[i],1);
                }
                tt^=1;
            }
        }
        cout << ans << "\n";
    }
}