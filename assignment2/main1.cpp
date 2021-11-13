#include "tree.hpp"
#include "merge.hpp"
#include "extract.hpp"
#include "make_singleton.hpp"

/// Testing function.
void test()
{
    twth T;
    for(int i=1;i<=500;i++) T=Merge(T,MakeSingleton(i));

    twth U=MakeSingleton(1000000);
    for(int i=777;i<=1000;i++) U=Merge(MakeSingleton(i),U);

    twth V=Merge(T,U);
    Extract(V);
    return;
}

int32_t main()
{
    test();
    cerr<<"Time:"<<1000*((double)clock())/(double)CLOCKS_PER_SEC<<"ms/n";
    return 0;
}
