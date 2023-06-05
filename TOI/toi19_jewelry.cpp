#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e6+5;

int n;
ll ans;
string s;
stack<pair<int,int>> st;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> s;
    int val=0;
    ll sum=0;
    for(int i=0;i<n;i++){
        if(s[i]=='T')val++;
        else{
            while(val>=0){
                int sz=1;
                while(!st.empty()&&st.top().first<=val){
                    auto [_val,_sz]=st.top();
                    st.pop();
                    sz+=_sz;
                    sum-=1ll*_val*_sz;
                }
                st.emplace(val,sz);
                sum+=1ll*val*sz;
                val--;
            }
            val=0;
        }
        int sz=0;
        while(!st.empty()&&st.top().first<=val){
            auto [_val,_sz]=st.top();
            st.pop();
            sz+=_sz;
            sum-=1ll*_val*_sz;
        }
        st.emplace(val,sz);
        sum+=1ll*val*sz;
        ans+=1ll*val*(val+1)/2;
        ans+=sum;
    }
    cout << ans;
}