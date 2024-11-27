#ifndef T_GOLFPATTERNSTOREHOUSE_H
#define T_GOLFPATTERNSTOREHOUSE_H
#include "T_GolfPatternDescription.h"
#include <initializer_list>


// vector + getPattern(name), rmPattern(name) methods
class T_GolfPatternStorehouse
{
public:
    std::vector<T_GolfPatternDescription> patterns;
    T_GolfPatternStorehouse();

    void addPattern(T_GolfPatternDescription& pt);  //push_back, emmplace_back
    void addPattern(std::string name_, std::initializer_list<T_GolfIndex> idxes);
    /**
     * @brief addPattern
     * @param name_
     * @param xy  - a list consisting of alternating cols and rows
     */
    void addPattern(std::string name_, std::initializer_list<size_t> xy);

    void rmPattern(std::string name_);
    void rmPattern(size_t idx); //patterns.erase()

    //the pattern can be read or modified (name, points) using the received pointer
    T_GolfPatternDescription* getPattern(std::string name_);
    T_GolfPatternDescription* getPattern(size_t idx);  //patterns[idx]
};

#endif // T_GOLFPATTERNSTOREHOUSE_H

//other abstract class (saver_loader) :
//storage type (file, db, ...)
// std::string fname;
// std::string path;
// void load();
// void save();
