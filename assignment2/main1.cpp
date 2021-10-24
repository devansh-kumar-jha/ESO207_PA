#include "tree.hpp"
#include "merge.hpp"
#include "extract.hpp"
#include "make_singleton.hpp"

/// Testing function.
void test()
{
    twth T=MakeSingleton(1);
    for(int i=2;i<=500;i++) T=Merge(T,MakeSingleton(i));

    twth U=MakeSingleton(777);
    for(int i=778;i<=1000;i++) U=Merge(U,MakeSingleton(i));

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
