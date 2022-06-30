#include "testlib.h"
#define MAXT 20000
#define MAXN 100000
#define MAXSUM 2000000
using namespace std;

int tcase,n,m;

int main(int argc, char* argv[])
{
    string s;

    registerValidation(argc, argv);
    
    tcase = inf.readInt(1, MAXT, "T");
    inf.readEoln();
    int sum = 0;
    while(tcase--)
    {
        n = inf.readInt(1, MAXN, "n");
        inf.readSpace();
        m = inf.readInt(1, MAXN, "m");
        inf.readEoln();
        s = inf.readString("[01]{1,200000}", "s");
        ensuref((int) s.size() == n + m, "Length of s does not equal to n + m");
        sum += n + m;
        ensuref(sum <= MAXSUM, format("sum of n + m <= %d", MAXSUM).c_str());
    }

    inf.readEof();
    return 0;
}
