#include<bits/stdc++.h>
using namespace std;
#define double long double
#define int long long
const double eps=1e-9;
const int maxn=1e5+10;
int dcmp(double x)
{
    return (fabs(x)<=eps)?0:(x<0?-1:1);
}
struct Point
{
    double x,y;
    Point(double X=0,double Y=0){x=X;y=Y;}
    Point operator - (Point b)
    {
        return Point(x-b.x,y-b.y);
    }
}a[maxn],b[maxn];
inline bool cmp(Point a,Point b)
{
    if(a.x==b.x) return a.y<b.y;
    else return a.x<b.x;
}
inline double Cross(Point a,Point b)
{
    return (a.x*b.y-a.y*b.x);
}
vector<Point> tu(Point *p,int n)
{
    int v=0;
    vector<Point> ans;
    for(int i=1;i<=n;i++)
    {
        while(v>1&&Cross(b[v-1]-b[v-2],p[i]-b[v-1])<=0) v--;
        b[v++]=p[i];
    }
    int j=v;
    for(int i=n-1;i>=1;i--)
    {
        while(v>j&&Cross(b[v-1]-b[v-2],p[i]-b[v-1])<=0) v--;
        b[v++]=p[i];
    }
    if(n>1) v--;
    for(int i=0;i<v;i++)
    {
        ans.push_back(b[i]);
    }
    return ans;
}
struct Line
{
    Point a;Point b;
    Line(Point x,Point y){a=x;b=y-x;}
};
inline double len(Point a)
{
    return a.x*a.x+a.y*a.y;
}
inline double DistanceToLine(Point a,Line b)
{
    return fabs(Cross(b.a-a,b.b))/len(b.b);
}
inline double cal(vector<Point> p)
{
    int j=0;
    double ans=0;
    int n=p.size();
    if(n==2) return len(p[1]-p[0]);
    for(int i=0;i<n-1;i++)
    {
        Line line(p[i],p[i+1]);
        while(DistanceToLine(p[j],line)<=DistanceToLine(p[(j+1)%n],line))
        {
            j=(j+1)%n;
        }
        ans=max(ans,max(len(p[j]-p[i]),len(p[j]-p[i+1])));
    }
    return ans;
}
signed main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i].x>>a[i].y;
    sort(a+1,a+1+n,cmp);
    cout<<(int)cal(tu(a,n))<<endl;
}
