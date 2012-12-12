#include <vector>
#include "dsets.h"

void DisjointSets::addelements(int num)
{
    int prevSize = v.size();

    v.resize( v.size() + num );

    for (int i = prevSize; i < v.size(); i++)
    {
        v[i]=-1;
    }
}

int DisjointSets::find(int elem)
{
    if (v[elem] < 0) return elem;
    else 
    {
        v[elem] = find( v[ elem ] );
        return find( v[ elem ] );
    }
}

void DisjointSets::setunion(int a, int b)
{
    a = find(a);
    b = find(b);
    int newSize = v[a]+v[b];
    if ( v[a] <= v[b])
    {
        v[b] = a;
        v[a] = newSize;
    }
    else {
        v[a] = b;
        v[b] = newSize;
    }
}

bool DisjointSets::isBigger(int c, int d)
{
    return v[c]<v[d];
}
