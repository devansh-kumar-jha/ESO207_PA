/// Algorithm
/// While(not null) node->left and height++
/// h1 = height of tree 1
/// h2 = height of tree 2
/// Can save the height of trees in the ADT.
/// if(h1>=h2) insert(tree 2 into tree 1 at height h2)
/// else insert(tree 1 into tree 2 at height h1)

/// Iterations = h(T1)+h(T2)+max(h(T1),h(T2))
/// The above iterations are only when the `h` in two three tree is not functional.
/// If h functions than Iterations = max(h(T1),h(T2))

// #include<bits/stdc++.h>
// using namespace std;
// #define int long long int

#include "twth.hpp"

int32_t main()
{
    
}