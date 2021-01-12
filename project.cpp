#include<iostream>
#include<cstdlib>
#include<cmath>
using namespace std;
/*array includes income,expenditure,govt job or pvt job and if the person has any previous debt*/
float z[6][4]={{70000,50000,1,0},{100000,70000,0,0},{100000,40000,1,1},{100000,80000,1,1},{100000,80000,0,0},{100000,70000,1,1}};
float labels[6]={1,1,1,0,1,0};
float w1,w2,w3,w4,bias,lr=0.1,OL[6],OR[6],error[6],sigde[6],z_det[6];
float max1,min1,max2,min2;
int normalise(float z[6][4])
{
	int i,j;
	min1=z[0][0];
	max1=0;
	min2=z[0][1];
	max2=0;
	for(i=0;i<6;i++)
	{
		if(z[i][0]>max1)
		{
			max1=z[i][0];
		}
		if(z[i][0]<min1)
		{
			min1=z[i][0];
		}
	}
	for(i=0;i<6;i++)
	{
		if(z[i][1]>max2)
		{
			max2=z[i][1];
		}
		if(z[i][1]<min2)
		{
			min2=z[i][1];
		}
	}
	for(i=0;i<6;i++)
	{
		z[i][0]=((z[i][0]-min1)/(max1-min1));
	}
	for(i=0;i<6;i++)
	{
		z[i][1]=((z[i][1]-min2)/(max2-min2));
	}
}
int weights()
{
	w1=(float)rand()/RAND_MAX;
	w2=(float)rand()/RAND_MAX;
	w3=(float)rand()/RAND_MAX;
	w4=(float)rand()/RAND_MAX;
	bias=(float)rand()/RAND_MAX;
}
int summation()
{
	int i;
	for(i=0;i<6;i++)
	{
		OL[i]=(z[i][0]*w1)+(z[i][1]*w2)+(z[i][2]*w3)+(z[i][3]*w4)+bias;
	}
}
float sigmoid(int x)
{
	return (1/(1+(exp(-x))));
}
float sigmoid_derivative(int x)
{
	return sigmoid(x)*(1-sigmoid(x));
}
int amount(int x1,int x2)
{
	int f,a;
	f=(x1*12)-(x2*12);
	a=(0.2)*f;
	cout<<"\n Upto rupees "<<f-a<<" can be sanctioned as a loan.";
}

int prediction()
{
	int x1,x2,x3,x4;
	float sum,z1,z2;
	cout<<" Enter monthly income:";
	cin>>x1;
	cout<<"\n Enter monthly expenditure:";
	cin>>x2;
	cout<<"\n Govt(1) or Prvt(0): ";
	cin>>x3;
	cout<<"\n Any dept(1,0): ";
	cin>>x4;
	z1=(x1-min1)/(max1-min1);
	z2=(x2-min2)/(max2-min2);
	sum=(z1*w1)+(z2*w2)+(x3*w3)+(x4*w4)+bias;
	if(sigmoid(sum)>0.5)
	{
		cout<<"\n Loan can be sanctioned!!!";
		amount(x1,x2);
	}
	else
	{
		cout<<"\n Load cannot be sanctioned!!!";
	}
}
int main()
{
	float f;
	int epoch,i;
	normalise(z);
	weights();
	for(epoch=0;epoch<50;epoch++)
	{
		for(i=0;i<6;i++)
		{
			summation();
			OR[i]=sigmoid(OL[i]);
			error[i]=OR[i]-labels[i];
			sigde[i]=sigmoid_derivative(OL[i]);
			z_det[i]=error[i]*sigde[i];
			w1=w1-(lr*error[i]*sigde[i]*z[i][0]);
			w2=w2-(lr*error[i]*sigde[i]*z[i][1]);
			w3=w2-(lr*error[i]*sigde[i]*z[i][2]);
			w4=w4-(lr*error[i]*sigde[i]*z[i][3]);
		}
		for(i=0;i<6;i++)
		{
			bias=bias-(lr*z_det[i]);
		}
		
	}
	
	prediction();
}
