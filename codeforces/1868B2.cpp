#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using db = long double;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<db>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pdd = pair<db,db>;
const int INF=0x3fffffff;
// const int MOD=1000000007;
const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

template<class T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<class T>
using ordered_multiset = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    ll sum=0;
    for(auto &x:a){
        cin >> x;
        sum+=x;
    }
    if(sum%n>0){
        cout << "No\n";
        return;
    }
    int target=sum/n;
    vector<int> cnt(30),cnt2(30),cnt3(30);
    for(int i=0;i<n;i++){
        int diff=abs(a[i]-target);
        if(a[i]>target){
            if(diff==(diff&-diff)){
                cnt2[31-__builtin_clz(diff)]++;
            }else{
                int diff2=diff+(diff&-diff);
                if(diff2!=(diff2&-diff2)){
                    cout << "No\n";
                    return;
                }
                cnt[31-__builtin_clz(diff2)]++;
                cnt[31-__builtin_clz(diff&-diff)]--;
            }
        }else if(a[i]<target){
            if(diff==(diff&-diff)){
                cnt3[31-__builtin_clz(diff)]++;
            }else{
                int diff2=diff+(diff&-diff);
                if(diff2!=(diff2&-diff2)){
                    cout << "No\n";
                    return;
                }
                cnt[31-__builtin_clz(diff2)]--;
                cnt[31-__builtin_clz(diff&-diff)]++;
            }
        }
    }
    for(int i=0;i<30;i++){
        int cur=cnt[i]+cnt2[i]-cnt3[i];
        while(i<29&&cur>0&&cnt2[i]>0){
            cur-=2;
            cnt[i+1]++;
            cnt2[i]--;
        }
        while(i<29&&cur<0&&cnt3[i]>0){
            cur+=2;
            cnt[i+1]--;
            cnt3[i]--;
        }
        if(cur!=0){
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";

}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}