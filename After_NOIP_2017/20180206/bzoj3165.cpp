#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cassert>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=4e4+1e2,maxm=1e5+1e2;
const double eps=1e-8;

int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3],dat[maxn<<3],cnt;
double k[maxm],b[maxm];

inline int dcmp(double x) {
    return fabs(x) <= eps ? 0 : x < 0 ? -1 : 1;
}
inline void build(int pos,int ll,int rr) {
    l[pos] = ll , r[pos] = rr;
    if( ll == rr ) return;
    const int mid = ( ll + rr ) >> 1;
    build(lson[pos]=++cnt,ll,mid);
    build(rson[pos]=++cnt,mid+1,rr);
}
inline double f(int x,int p) {
    return k[x] * p + b[x];
}
inline bool judge(int x,int y,int p) {
    double fx = f(x,p) , fy = f(y,p);
    return dcmp(fx-fy) ? fx < fy : x > y;
}
inline void update(int pos,int ll,int rr,int nw) {
    if( r[pos] < ll || rr < l[pos] ) return;
    if( ll <= l[pos] && r[pos] <= rr ) {
        if( judge(nw,dat[pos],l[pos]) && judge(nw,dat[pos],r[pos]) ) return; // completely useless
        if( judge(dat[pos],nw,l[pos]) && judge(dat[pos],nw,r[pos]) ) { // completely better
            dat[pos] = nw;
            return;
        }
        const int mid = ( l[pos] + r[pos] ) >> 1;
        if( judge(dat[pos],nw,mid) ) swap(dat[pos],nw); // keep dat[pos] the better choice for mid point
        if( judge(dat[pos],nw,l[pos]) ) update(lson[pos],l[pos],r[pos],nw); // nw maybe usefull in lson
        else update(rson[pos],l[pos],r[pos],nw);
        return; // you will get TLE without this return
    }
    update(lson[pos],ll,rr,nw) , update(rson[pos],ll,rr,nw);
}
inline int query(int pos,int x) {
    if( x < l[pos] || r[pos] < x ) return 0;
    if( l[pos] == r[pos] && l[pos] == x ) return dat[pos];
    const int mid = ( l[pos] + r[pos] ) >> 1;
    int ret = x <= mid ? query(lson[pos],x) : query(rson[pos],x);
    if( judge(ret,dat[pos],x) ) ret = dat[pos];
    return ret;
}

int main() {
    static int n,lastans=-1,x0,y0,x1,y1,p,cc;
    build(cnt=1,1,40000);
    scanf("%d",&n);
    for(int i=1,ope;i<=n;i++) {
        scanf("%d",&ope);
        if( ope ) {
            scanf("%d%d%d%d",&x0,&y0,&x1,&y1) , ++cc;
            x0 = ( x0 + lastans + 39989 ) % 39989 + 1 , y0 = ( (lli) y0 + lastans + 1000000000 ) % 1000000000 + 1 ,
            x1 = ( x1 + lastans + 39989 ) % 39989 + 1 , y1 = ( (lli) y1 + lastans + 1000000000 ) % 1000000000 + 1 ;
            if( x1 < x0 ) swap( x1 , x0 ) , swap( y1 , y0 );
            if( x0 == x1 ) k[cc] = 0 , b[cc] = max( y0 , y1 );
            else k[cc] = (double)(y1-y0)/(x1-x0) , b[cc] = y1 - k[cc] * x1;
            update(1,x0,x1,cc);
        } else {
            scanf("%d",&p);
            p = ( p + lastans + 39989 ) % 39989 + 1;
            lastans = query(1,p);
            printf("%d\n",lastans);
            --lastans;
        }
    }
    return 0;
}

