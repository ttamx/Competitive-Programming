#include "template.hpp"
#include "convolution/xor-convolution.hpp"

void runcase(){
    int n,m;
    cin >> n >> m;
    int k=1<<m;
    vector<ll> a(k),b(k);
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        int val=0;
        for(auto x:s){
            val=(val<<1)|(x=='1');
        }
        a[val]++;
    }
    for(int i=0;i<k;i++){
        int c=__builtin_popcount(i);
        b[i]=min(c,m-c);
    }
    auto c=xor_convolution(a,b);
    cout << *min_element(c.begin(),c.end()) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}