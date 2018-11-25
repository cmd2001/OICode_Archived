#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdlib>
using namespace std;

const int inf=0x3f3f;
int n,maxn,maxm;
int lim,cur;
int dp[2][1<<13];
int map[110][7];
char inp[7];
bool finda;

void trans(int &k,int lar,int sm)//��һ��״̬��Ϊlar������ת��Ϊsm��lar��֤��sm�� 
{
	for(int i=0;i<6;i++)
	{
		if(((k>>(i<<1))&3)==lar)
		{
			k=k^(lar<<(i<<1))^(sm<<(i<<1));
		}
	}
}

void prom(int &k)//���1�м��֣������3û��2�����3����Ϊ2����ȷ����һ�����ӽ������µ�1���Ϸ�Ϊ0ʱֱ�Ӹ�ֵΪ3����ȷ�ġ� 
{
	bool f2=false,f3=false;
	for(int i=0;i<5;i++)
	{
		if(((k>>(i<<1))&3)==2)f2=true;
		if(((k>>(i<<1))&3)==3)f3=true;
	}
	if(!f2 && f3 && finda)trans(k,3,2);
	else if(!f2 && f3 && !finda)
	{
		trans(k,3,1);
		finda=true;
	}
}

bool checka(int k)
{
	for(int i=0;i<5;i++)
	{
		if(((k>>(i<<1))&3)>1)return false;//����д���1������˵����״̬��1û�к�����������һ�𣬲��Ϸ��� 
	}
	return true;
}

void getans()//��ȡ�𰸡� 
{
	int ans=inf;
	for(int k=0;k<lim-1;k++)if(checka(k))//checkȷ����״̬�ǺϷ��� 
	{
		ans=min(ans,dp[cur][k]);
	}
	printf("%d\n",ans);
}

void update(int a,int b,int type,int row)
{
	if(type>=1 && row>0)
	{
		int cur1=(a&3),cur2=(b&3);
		if(cur1!=cur2 && cur1>0)trans(b,max(cur1,cur2),min(cur1,cur2));
	}
	
	bool flag=true;
	int cnt=0;
	int check=(b>>10);
	if(a>0)
	{
		flag=false;
		if(check>1)cnt=1;
		for(int i=0;i<5;i++)
		{
			if(((b>>(i<<1))&3)==1)flag=true;
			if(check>1 && ((b>>(i<<1))&3)==check)cnt++;
		}
	}
	prom(b);
	
	if(flag==true && cnt!=1)
	{
		dp[cur][b^((b>>10)<<10)]=min(dp[cur][b^((b>>10)<<10)],dp[1-cur][a]+(type==2 ? 1 : 0));
	}
	else dp[cur][b^((b>>10)<<10)]=min(dp[cur][b^((b>>10)<<10)],inf);
}

int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
	{
		scanf("%s",inp);
		for(int j=0;j<5;j++)
		{
			map[i][j]=inp[j]-'0';
			if(map[i][j])maxn=i,maxm=j;
		}
	}
	memset(dp,inf,sizeof(dp));//�����鸳��ʼֵΪ���޴󣨳���500���ɣ��� 
		cur=0;//��ǰ״̬�� 
		lim=1<<(5<<1);//ÿ���׶δ�����Ϻ󱣴�����״̬��������ʹ���Ľ���������10λ������5λ�� 
		dp[0][0]=0;//�ڵ�0��ǰ�������һ�ţ������ֶ�Ϊ0������00000���״̬�����״̬��С��Ϊ���޴󣬸�״̬Ϊ0�� 
		finda=false;//���ڵ�һ���ҵ�1ʱ��ֵΪ1����2�� 
	
	for(int i=0;i<n;i++) 
	{
		for(int j=0;j<5;j++)//ö�ٽ׶Ρ� 
		{
			if(!finda && !map[i][j])continue;
			if(i>maxn || (i>=maxn && j>maxm))break;//������������һ��1�Ľ���ֱ���˳��� 
			cur^=1;//״̬ת���� 
			memset(dp[cur],inf,sizeof(dp[cur]));//��ʼ����״ֵ̬��Ϊ��� 
			for(int k=0;k<lim;k++)//ö����һ�׶�����״̬�� 
			{
				if(map[i][j])update(k,(k<<2)^((k>>8)>0 ? (k>>8) : (((k&3)>0 && j) ? (k&3) : 3)),1,j);//����õ���1��ֱ�Ӽ���״̬���������Ľ��ƣ�Ҫȷ���¼ӽڵ��Ϸ���Ϊ0����1Ҫ����8λ�� 
				else//Ϊ0�� 
				{
					update(k,(k<<2)^((k>>8)>0 ? (k>>8) : (((k&3)>0 && j) ? (k&3) : 3)),2,j);//�ĳ�1�� 
					update(k,k<<2,0,j);//���ģ�ֱ�Ӽ��롣 
				}
			}
		}
	}
	getans();
	
	return 0;
}
