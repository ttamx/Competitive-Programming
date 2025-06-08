#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e6+5;

struct Node;
using Ptr = Node*;
struct Node{
    int val;
    Ptr l,r;
    Node(int val):val(val),l(),r(){}
};

Ptr addr[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    {
        vector<Ptr> a(n);
        for(auto &x:a){
            int v;
            cin >> v;
            x=new Node(v);
        }
        for(int i=0;i<n;i++){
            a[i]->l=a[(i+n-1)%n];
            a[i]->r=a[(i+1)%n];
            addr[a[i]->val]=a[i];
        }
    }
    int q;
    cin >> q;
    while(q--){
        char op;
        cin >> op;
        if(op=='-'){
            int x;
            cin >> x;
            Ptr it=addr[x];
            it->l->r=it->r;
            it->r->l=it->l;
            addr[x]=nullptr;
        }else if(op=='+'){
            int x,y;
            cin >> x >> y;
            Ptr it=addr[y];
            Ptr cur=new Node(x);
            cur->l=it->l;
            cur->r=it;
            cur->l->r=cur;
            cur->r->l=cur;
            addr[x]=cur;
        }else{
            int k;
            cin >> k;
            vector<int> a(k);
            for(auto &x:a)cin >> x;
            int ans=0;
            a.insert(a.end(),a.begin(),a.end());
            for(int i=0;i<2*k;i++){
                Ptr it=addr[a[i]];
                if(!it)continue;
                int j=i;
                while(j+1<2*k&&it->r->val==a[j+1]){
                    it=it->r;
                    j++;
                }
                ans=max(ans,j-i+1);
                i=j;
            }
            if(ans>k){
                cout << "*\n";
            }else{
                cout << ans << "\n";
            }
        }
    }
}