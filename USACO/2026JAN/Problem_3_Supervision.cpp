#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,d;
    cin >> n >> d;
    vector<int> a(n),b(n);
    for(int i=0;i<n;i++){
        cin >> a[i] >> b[i];
    }
    deque<pair<int,mint>> dq;
    mint tot=1,sum=0,mult=1;
    for(int i=0,p=0;i<n;i++){
        if(b[i]){
            dq.emplace_back(a[i],tot/mult);
            sum+=tot;
            tot*=2;
        }else{
            while(!dq.empty()&&a[i]-dq.front().first>d){
                sum-=dq.front().second*mult;
                dq.pop_front();
            }
            tot+=sum;
            sum*=2;
            mult*=2;
        }
    }
    cout << tot-1 << "\n";
}