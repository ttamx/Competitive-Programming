#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    int l=0,r=n/2;
    while(r-l>1){
        int mid=(l+r)/2;
        int a,b;
        cout << "1 " << mid*2 << endl;
        cin >> a;
        cout << "2 " << mid*2+1 << endl;
        cin >> b;
        if(a==b)r=mid;
        else l=mid;
    }
    cout << "3 " << l*2+1 << " " << r*2+1 << endl;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}