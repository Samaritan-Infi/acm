#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;
const double PI = acos(-1.0);
//复数结构体
struct Complex
{
    double x,y;//实部和虚部 x+yi
    Complex(double _x = 0.0,double _y = 0.0)
    {
        x = _x;
        y = _y;
    }
    Complex operator -(const Complex &b)const
    {
        return Complex(x-b.x,y-b.y);
    }
    Complex operator +(const Complex &b)const
    {
        return Complex(x+b.x,y+b.y);
    }
    Complex operator *(const Complex &b)const
    {
        return Complex(x*b.x-y*b.y,x*b.y+y*b.x);
    }
};
/*
* 进行FFT和IFFT前的反转变换。
* 位置i和 （i二进制反转后位置）互换
* len必须去2的幂
*/
void change(Complex y[],int len)
{
    int i,j,k;
    for(i = 1, j = len/2; i <len-1; i++)
    {
        if(i < j)swap(y[i],y[j]);
//交换互为小标反转的元素， i<j保证交换一次
//i做正常的+1， j左反转类型的+1,始终保持i和j是反转的
        k = len/2;
        while(j >= k)
        {
            j -= k;
            k /= 2;
        }
        if(j < k)j += k;
    }
}
/*
* 做FFT
* len必须为2^k形式，
* on==1时是DFT， on==-1时是IDFT
*/
void fft(Complex y[],int len,int on)
{
    change(y,len);
    for(int h = 2; h <= len; h <<= 1)
    {
        Complex wn(cos(-on*2*PI/h),sin(-on*2*PI/h));
        for(int j = 0; j < len; j+=h)
        {
            Complex w(1,0);
            for(int k = j; k < j+h/2; k++)
            {
                Complex u = y[k];
                Complex t = w*y[k+h/2];
                y[k] = u+t;
                y[k+h/2] = u-t;
                w = w*wn;
            }
        }
    }
    if(on == -1)
        for(int i = 0; i < len; i++)
            y[i].x /= len;
}
const int MAXN = 1000005;
Complex x1[MAXN],x2[MAXN];
char str1[MAXN/2],str2[MAXN/2];
int sum[MAXN];
int main()
{
    while(~scanf("%s%s",str1,str2))
    {
        memset(sum,0,sizeof(sum));
        int len1=strlen(str1),len2=strlen(str2);
        int len=1;
        while(len<len1*2||len<len2*2) len<<=1;
        int res=0;
        //R vs L S
        for(int i = 0; i < len1; i++)
            x1[i] = Complex(str1[i]=='L'||str1[i]=='S',0);
        for(int i = len1; i < len; i++)
            x1[i] = Complex(0,0);
        for(int i = 0; i < len2; i++)
            x2[i] = Complex(str2[len2-1-i]=='R',0);
        for(int i = len2; i < len; i++)
            x2[i] = Complex(0,0);
        fft(x1,len,1);
        fft(x2,len,1);
        for(int i = 0; i < len; i++)
            x1[i] = x1[i]*x2[i];
        fft(x1,len,-1);
        for(int i = len2-1; i < len1+len2; i++)
            sum[i]+=(int)(x1[i].x+0.5);
        //P vs R K
        for(int i = 0; i < len1; i++)
            x1[i] = Complex(str1[i]=='P'||str1[i]=='L',0);
        for(int i = len1; i < len; i++)
            x1[i] = Complex(0,0);
        for(int i = 0; i < len2; i++)
            x2[i] = Complex(str2[len2-1-i]=='S',0);
        for(int i = len2; i < len; i++)
            x2[i] = Complex(0,0);
        fft(x1,len,1);
        fft(x2,len,1);
        for(int i = 0; i < len; i++)
            x1[i] = x1[i]*x2[i];
        fft(x1,len,-1);
        for(int i = len2-1; i < len1+len2; i++)
            sum[i]+=(int)(x1[i].x+0.5);
        //S vs P L
        for(int i = 0; i < len1; i++)
            x1[i] = Complex(str1[i]=='R'||str1[i]=='K',0);
        for(int i = len1; i < len; i++)
            x1[i] = Complex(0,0);
        for(int i = 0; i < len2; i++)
            x2[i] = Complex(str2[len2-1-i]=='P',0);
        for(int i = len2; i < len; i++)
            x2[i] = Complex(0,0);
        fft(x1,len,1);
        fft(x2,len,1);
        for(int i = 0; i < len; i++)
            x1[i] = x1[i]*x2[i];
        fft(x1,len,-1);
        for(int i = len2-1; i < len1+len2; i++)
            sum[i]+=(int)(x1[i].x+0.5);
        //L vs P K
        for(int i = 0; i < len1; i++)
            x1[i] = Complex(str1[i]=='P'||str1[i]=='K',0);
        for(int i = len1; i < len; i++)
            x1[i] = Complex(0,0);
        for(int i = 0; i < len2; i++)
            x2[i] = Complex(str2[len2-1-i]=='L',0);
        for(int i = len2; i < len; i++)
            x2[i] = Complex(0,0);
        fft(x1,len,1);
        fft(x2,len,1);
        for(int i = 0; i < len; i++)
            x1[i] = x1[i]*x2[i];
        fft(x1,len,-1);
        for(int i = len2-1; i < len1+len2; i++)
            sum[i]+=(int)(x1[i].x+0.5);
        //K vs R S
        for(int i = 0; i < len1; i++)
            x1[i] = Complex(str1[i]=='R'||str1[i]=='S',0);
        for(int i = len1; i < len; i++)
            x1[i] = Complex(0,0);
        for(int i = 0; i < len2; i++)
            x2[i] = Complex(str2[len2-1-i]=='K',0);
        for(int i = len2; i < len; i++)
            x2[i] = Complex(0,0);
        fft(x1,len,1);
        fft(x2,len,1);
        for(int i = 0; i < len; i++)
            x1[i] = x1[i]*x2[i];
        fft(x1,len,-1);
        for(int i = len2-1; i < len1+len2; i++)
            sum[i]+=(int)(x1[i].x+0.5);
        for(int i = len2-1; i < len1+len2; i++)
            res=max(res,sum[i]);
        printf("%d\n",res);
    }
    return 0;
}
