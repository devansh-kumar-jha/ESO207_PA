//! This is just a auxiliary file to ckeck the correctness
//! in working of two-three tree ADT.

#include "twth.hpp"

/// Test Case
/// 5
/// 2 3 4 5 1

int32_t main()
{
    twth th;
    int n;  cin>>n;
    int x;
    for(int i=0;i<n;i++) { cin>>x;  th.insert(x); }
    th.display();
    return 0;
}
