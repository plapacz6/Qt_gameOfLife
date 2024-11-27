#include "T_GolfPatternStorehouse.h"
#include <algorithm>
#include <cassert>
using namespace  std;

T_GolfPatternStorehouse::T_GolfPatternStorehouse() {

}

void T_GolfPatternStorehouse::addPattern(T_GolfPatternDescription &pt)
{
    patterns.push_back(pt);
}

void T_GolfPatternStorehouse::addPattern(std::string name_, std::initializer_list<T_GolfIndex> idxes)
{
    T_GolfPatternDescription pt{name_};
    for(const T_GolfIndex& idx: idxes) {
        pt.addPoint(idx.col, idx.row);
    }
    patterns.emplace_back(std::move(pt));
}

void T_GolfPatternStorehouse::addPattern(std::string name_, std::initializer_list<size_t> xy)
{
    T_GolfPatternDescription pt{name_};
    assert(xy.size() % 2 == 0);
    auto itxy = xy.begin();
    for(size_t i = 0; i < xy.size(); i+=2) {
        pt.addPoint(*itxy, *(itxy + 1));
        ++itxy;
        ++itxy;
    }
    patterns.emplace_back(std::move(pt));
}

void T_GolfPatternStorehouse::rmPattern(std::string name_)
{
    auto itpd = find_if(patterns.begin(), patterns.end(),
                        [name_](T_GolfPatternDescription& pd) {
                                if(pd.getName() == name_) {
                                    return true;
                                }
                                return false;
                        });
    if(itpd != patterns.end()) {
        patterns.erase(itpd);
    }
}

void T_GolfPatternStorehouse::rmPattern(size_t idx)
{
    if(idx < patterns.size()) {
        auto itpd = patterns.begin() + idx;
        patterns.erase(itpd);
    }
}

T_GolfPatternDescription *T_GolfPatternStorehouse::getPattern(std::string name_)
{
    auto itpd = find_if(patterns.begin(), patterns.end(),
                        [name_](T_GolfPatternDescription& pd) {
                            if(pd.getName() == name_) {
                                return true;
                            }
                            return false;
                        });
    if(itpd != patterns.end()) {
        return itpd.base();
    }
    return nullptr;
}

T_GolfPatternDescription *T_GolfPatternStorehouse::getPattern(size_t idx)
{
    if(idx < patterns.size()) {
        return &patterns[idx];
    }
    return nullptr;
}
