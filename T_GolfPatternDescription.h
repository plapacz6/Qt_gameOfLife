#ifndef T_GOLFPATTERNDESCRIPTION_H
#define T_GOLFPATTERNDESCRIPTION_H
#include "T_GolfIndex.h"
#include <vector>
#include <string>

class T_GolfPatternDescription
{
    std::vector<T_GolfIndex> points;
    size_t width;
    size_t hight;
    std::string name;
public:
    explicit T_GolfPatternDescription(std::string name_);
    /**
     * @brief addPoint  add point and sort whole vector
     * @param c
     * @param r
     *
     * after adding point to the vector: points
     * makes sorting to achieve that first element is most top left
     * and last element is most bottom right
     * Then calcualte width and hight as differnece between cols of alst and fist
     * and hight as difference between bototm and top
     */
    void addPoint(size_t c, size_t r);
    size_t getWidth();
    size_t getHight();
    void setName(const std::string& name_);
    std::string getName();

    size_t size();
    T_GolfIndex operator[](const size_t i) const;
    std::vector<T_GolfIndex>::iterator begin();
    std::vector<T_GolfIndex>::iterator end();
};

#endif // T_GOLFPATTERNDESCRIPTION_H
