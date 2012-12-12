#ifndef DSETS_H
#define DSETS_H
#include <vector>

using namespace std;

class DisjointSets
{
    public:
    void addelements(int num);
    int find (int elem);
    void setunion(int a, int b);
    bool isBigger(int c, int d);

    private:
    vector<int> v;
};

#endif
