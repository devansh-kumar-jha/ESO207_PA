/// Algorithm
/// if(twonode) -> if(val>=x) -> go left
///             -> else       -> go middle
/// if(threenode) -> if(val1>=x)      -> go left
///               -> else if(val2>=x) -> go middle
///               -> else             -> go right
/// if(leaf) -> split , repair and return
/// if(null) -> return
/// Iterations = h(T)+h(T)+h(T)

#include<bits/stdc++.h>
using namespace std;
#define int long long int
