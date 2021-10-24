/// Makes a tree for singleton set.
/// O(1) time.
twth MakeSingleton(int x)
{
    twth th;
    th.set(leaf(x));
    return th;
}
