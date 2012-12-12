#include <vector>
#include "dsets.h"

void DisjointSets::addelements(int num)
{
    for (int i = 0; i < num; i++)
    {
        v.push_back(-1);
    }
}

int DisjointSets::find(int elem)
{
    if (v[elem] < 0) return elem;
    else return v[elem] = find(v[elem]);
}

void DisjointSets::setunion(int a, int b)
{
    int c = find(a);
    int d = find(b);
    int newSize = v[c]+v[d];
    if (isBigger(c,d))
    {
        v[d] = c;
        v[c] = newSize;
    }
    else {
        v[c] = d;
        v[d] = newSize;
    }
}

bool DisjointSets::isBigger(int c, int d)
{
    return c<d;
}
