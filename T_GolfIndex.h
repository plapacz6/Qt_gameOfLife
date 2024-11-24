#ifndef T_GOLFINDEX_H
#define T_GOLFINDEX_H
#include <cstdlib>

class T_GolfIndex
{
public:
    size_t row;
    size_t col;
    explicit T_GolfIndex();
    explicit T_GolfIndex(size_t c, size_t r);
};

#endif // T_GOLFINDEX_H
