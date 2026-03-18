#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using db = long double;
using P = complex<ll>;
using PD = complex<db>;

inline ll cross(P a,P b){
    return imag(conj(a)*b);
}

inline int side(P a){
    return imag(a)>0||(imag(a)==0&&real(a)>0);
}

PD convert(P a){
    return PD(a.real(),a.imag());
}

vector<P> rect;

inline db area(P s,P e){
	vector<PD> res;
	for(int i=0;i<4;i++){
		P cur = rect[i], prev = i ? rect[i-1] : rect.back();
		db a = cross(e-s, cur-s), b = cross(e-s, prev-s);
		if (a*b<0)
			res.push_back(convert(cur) + convert(prev - cur) * (a / (a - b)));
		if (a<=0)
			res.push_back(convert(cur));
	}
    res.emplace_back(res[0]);
    db ret=0;
    for(int i=0;i+1<res.size();i++){
        ret+=imag(conj(res[i])*res[i+1]);
    }
    return db(ret)/2.0;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<P> a(m);
    for(auto &p:a){
        ll x,y;
        cin >> x >> y;
        p=P(x,y);
    }
    rect.emplace_back(P(0,0));
    rect.emplace_back(P(n,0));
    rect.emplace_back(P(n,n));
    rect.emplace_back(P(0,n));
    db ans=-1e18;
    for(int i=0;i<m;i++){
        vector<P> b;
        for(int j=0;j<m;j++)if(j!=i)b.emplace_back(a[j]);
        for(auto &p:b)p-=a[i];
        sort(b.begin(),b.end(),[&](P x,P y){
            int u=side(x),v=side(y);
            if(u!=v)return u>v;
            return cross(x,y)>0;
        });
        int sz=b.size();
        b.insert(b.end(),b.begin(),b.end());
        for(int l=0,r=0;l<sz;l++){
            if(l>0&&cross(b[l-1],b[l])==0)continue;
            while(r<l+sz&&cross(b[l],b[r])>=0)r++;
            ans=max(ans,db(r-l+1)/db(m)-area(a[i]+b[l],a[i])/n/n);
        }
        P p;
        ll x=real(a[i]),y=imag(a[i]);
        if(x*2<=n){
            if(y*2<=n)p=P(x*2,0);
            else p=P(0,2*y-n);
        }else{
            if(y*2<=n)p=P(n,2*y);
            else p=P(2*x-n,n);
        }
        int cnt=1;
        for(int j=0;j<m;j++)if(i!=j&&cross(a[j]-a[i],p-a[i])>=0)cnt++;
        ans=max(ans,db(cnt)/db(m)-area(a[i],p)/n/n);
    }
    cout << fixed << setprecision(12) << ans << "\n";
}