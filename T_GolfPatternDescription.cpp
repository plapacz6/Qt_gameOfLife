#include "T_GolfPatternDescription.h"
#include <algorithm>
using namespace std;

T_GolfPatternDescription::T_GolfPatternDescription(std::string name_) {
    name = name_;
    width = 0;
    hight = 0;
}

void T_GolfPatternDescription::addPoint(size_t c, size_t r)
{
    points.emplace_back(T_GolfIndex{c, r});
    sort(points.begin(), points.end(),
        [](T_GolfIndex& a, T_GolfIndex& b){
            return (a.row <= b.row && a.col <= b.col);
        }
    );
    width = points[points.size() - 1].col - points[0].col;
    hight = points[points.size() - 1].row - points[0].row;
}

size_t T_GolfPatternDescription::getWidth()
{
    return width;
}

size_t T_GolfPatternDescription::getHight()
{
    return hight;
}

void T_GolfPatternDescription::setName(const std::string& name_)
{
    name = name_;
}

string T_GolfPatternDescription::getName()
{
    return name;
}

size_t T_GolfPatternDescription::size()
{
    return points.size();
}

T_GolfIndex T_GolfPatternDescription::operator[](const size_t i) const
{
    return points[i];
}

vector<T_GolfIndex>::iterator T_GolfPatternDescription::begin()
{
    return points.begin();
}

vector<T_GolfIndex>::iterator T_GolfPatternDescription::end()
{
    return points.end();
}
