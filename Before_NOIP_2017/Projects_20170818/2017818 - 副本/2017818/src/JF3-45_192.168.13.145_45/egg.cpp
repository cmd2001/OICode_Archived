#include<cstdio>
#include<cmath>
using namespace std;
inline int geta(int x,int y){	//x��y���� ��� 
	if(y==1) return x;
	if(x<=y) return (int)pow(2,x)-1;
	return geta(x-1,y-1)+geta(x-1,y)+1; //��ĳ�� ��һ��Ϊ ���ˣ���>ʵ�ʣ��ڶ����෴ 
}
int main(){
	freopen("egg.in","r",stdin);
	freopen("egg.out","w",stdout);
	int n,m;
	scanf("%d%d",&n,&m);
	int f=1;
	while(geta(f,m)<n) f++;
	printf("%d",f);
	return 0;
}
