#include<bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// mt19937 rng(chrono::steady_clock::now().time_since_epoch(),count());

int rnd(int l,int r)
{
    return uniform_int_distribution<int>(l,r)(rng);
}

#ifdef _WIN32
#define A "1.exe < in.txt > a.txt"
#define B "std.exe < in.txt > b.txt"
#define CMP "fc a.txt b.txt > nul"
#else
#define A "./1 < in.txt > a.txt"
#define B "./std < in.txt > b.txt"
#define CMP "diff -q a.txt b.txt > /dev/null"
#endif

int main()
{
    for(int T=1;;T++)
    {
        ofstream out("in.txt");

        int n=rnd(1,10);
        out<<n<<'\n';

        for(int i=1;i<=n;i++)
            out<<rnd(1,20)<<" \n"[i==n];

        out.close();

        system(A);
        system(B);

        if(system(CMP))
        {
            cerr<<"WA "<<T<<'\n';
            ifstream in("in.txt");
            cerr<<in.rdbuf();
            break;
        }

        cerr<<"AC "<<T<<'\n';
    }
}
