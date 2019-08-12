// 矩阵连乘.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "iostream"
#include "string"
using namespace std;
string h[100]={""};
void MatrixChain(int *p,int n,int **m,int **s)
{
	for(int i=1;i<=n;i++)m[i][i]=0;
	for(int r=2;r<=n;r++)
		for(int i=1;i<=n-r+1;i++)
		{
			int j=i+r-1;
			m[i][j]=m[i+1][j]+p[i-1]*p[i]*p[j];
			s[i][j]=i;
			for(int k=i+1;k<j;k++)
			{
				int t=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
				if(t<m[i][j]){m[i][j]=t;s[i][j]=k;}
			}
		}
}
void Traceback(int i,int j,int **s)
{
	if(i==j)return;
	Traceback(i,s[i][j],s);
	Traceback(s[i][j]+1,j,s);
	if(h[i] == "" && h[s[i][j]+1]=="")
	{
		string h6=" ";
		string h1="(A";
		string h2="A";
		string h3=")";
		h[i]=h1+to_string(long long(i))+h6+h2+to_string(long long(s[i][j]+1))+h3;
	}else if(h[i] != "" && h[s[i][j]+1]=="")
	{
		string h6=" ";
		string h1="(";
		string h2="A";
		string h3=")";
		h[i]=h1+h[i]+h6+h2+to_string(long long(s[i][j]+1))+h3;
	}else if(h[i] == "" && h[s[i][j]+1]!="")
	{
		string h6=" ";
		string h1="(A";
		string h3=")";
		h[i]=h1+to_string(long long(i))+h6+h[s[i][j]+1]+h3;
	}else
	{
		string h6=" ";
		string h1="(";
		string h3=")";
		h[i]=h1+h[i]+h6+h[s[i][j]+1]+h3;
	}
}
template <typename T>
T** malloc_Array2D(int row, int col)
{
	int size = sizeof(T);
	int point_size = sizeof(T*);
	T **arr = (T **) malloc(point_size * row + size * row * col);
	if (arr != NULL)
	{	
		memset(arr, 0, point_size * row + size * row * col);
		T *head = (T*)((int)arr + point_size * row);
		while (row--)
			arr[row] = (T*)((int)head + row * col * size);
	}
	return (T**)arr;
}

void free_Aarray2D(void **arr)
{
	if (arr != NULL)
		free(arr);
}
int _tmain(int argc, _TCHAR* argv[])
{
	cout<<"请输入参数的个数：";
	int n;
	cin>>n;
	int *a1=new int[n];
	int w=0;
	cout<<"请输入参数的值：";
	while(w<n)
	{
		cin>>a1[w];
		w++;
	}
	int nRow=n, nCol=n;
	int **p = malloc_Array2D<int>(nRow+1, nCol+1);
	int nRow1=n, nCol1=n;
	int **q = malloc_Array2D<int>(nRow1+1, nCol1+1);
	MatrixChain(a1,n,q,p);
	Traceback(1,n-1,p);
	cout<<"最优加括号方式为：";
	for(int i=0;i<100;i++)
	{
		if(h[i]!="")
		{
			cout<<h[i];
			break;
		}
	}
	int z;
	cin>>z;
	return 0;
}

