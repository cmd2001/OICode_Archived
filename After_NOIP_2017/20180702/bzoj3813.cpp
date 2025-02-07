#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long int lli;
typedef unsigned long long int ulli;
using namespace std;
const int maxn=1e5+1e2,lim=1e5;
const int mod=19961993;

int prime[maxn],inv[maxn],cnt;

struct SegmentTree {
    struct Node {
        int pi; ulli app;
        friend Node operator + (const Node &a,const Node &b) {
            return (Node){(lli)a.pi*b.pi%mod,a.app|b.app};
        }
    }dat[maxn<<2],ini;
    inline Node cut(int x) {
        Node ret = (Node){x,0};
        for(int i=0;i<cnt;i++) if( ! ( x % prime[i] ) ) ret.app |= 1ull << i;
        return ret;
    }
    #define lson(pos) (pos<<1)
    #define rson(pos) (pos<<1|1)
    inline void build(int pos,int l,int r) {
        if( l == r ) return void( dat[pos] = ini );
        const int mid = ( l + r ) >> 1;
        build(lson(pos),l,mid) , build(rson(pos),mid+1,r);
        dat[pos] = dat[lson(pos)] + dat[rson(pos)];
    }
    inline void update(int pos,int l,int r,const int &tar,const int &x) {
        if( l == r ) return void( dat[pos] = cut(x) );
        const int mid = ( l + r ) >> 1;
        tar <= mid ? update(lson(pos),l,mid,tar,x) : update(rson(pos),mid+1,r,tar,x);
        dat[pos] = dat[lson(pos)] + dat[rson(pos)];
    }
    inline Node query(int pos,int l,int r,const int &ll,const int &rr) {
        if( ll <= l && r <= rr ) return dat[pos];
        const int mid = ( l + r ) >> 1;
        if( rr <= mid ) return query(lson(pos),l,mid,ll,rr);
        if( ll > mid ) return query(rson(pos),mid+1,r,ll,rr);
        return query(lson(pos),l,mid,ll,rr) + query(rson(pos),mid+1,r,ll,rr);
    }
    inline void init() {
        ini = cut(3);
    }
}sgt;
typedef SegmentTree::Node Node;

inline int query(int l,int r) {
    Node nd = sgt.query(1,1,lim,l,r);
    int ret = nd.pi;
    for(int i=0;i<60;i++) if( nd.app & ( 1ull << i ) ) {
        ret = (lli) ret * inv[i] % mod , ret = (lli) ret * ( prime[i] - 1 ) % mod;
    }
    return ret;
}

inline int fastpow(int base,int tim) {
    int ret = 1;
    while(tim) {
        if( tim & 1 ) ret = (lli) ret * base % mod;
        if( tim >>= 1 ) base = (lli) base * base % mod;
    }
    return ret;
}
inline void sieve() {
    static bool vis[maxn];
    for(int i=2;i<=lim;i++) {
        if( !vis[i] ) {
            prime[cnt] = i , inv[cnt++] = fastpow(i,mod-2);
            if( cnt == 60 ) break;
        }
        for(int j=0;j<cnt&&(lli)i*prime[j]<=lim;j++) {
            vis[i*prime[j]] = 1;
            if( ! ( i % prime[j] ) ) break;
        }
    }
}

int n;

int main() {
    sieve() , sgt.init() , sgt.build(1,1,lim) , scanf("%d",&n);
    for(int i=1,o,a,b;i<=n;i++) {
        scanf("%d%d%d",&o,&a,&b);
        if( !o ) printf("%d\n",query(a,b));
        else if( o == 1 ) sgt.update(1,1,lim,a,b);
    }
    return 0;
}

