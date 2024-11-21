#include "T_Golf_engine.h"
#include <vector>
#include <iostream>
#include <cassert>
using namespace std;

T_Golf_engine::T_Golf_engine() {
    data_new = data1;
    data_old = data2;
    // ptr_ptr_data = &data_new;
    Torus = true;
    Rules_D.push_back(3);
    Rules_S.push_back(2);
    Rules_S.push_back(3);
}
void T_Golf_engine::swap_data() {
    swap(data_new, data_old);
}
void T_Golf_engine::reset() {

    bool* ptr_Golf_data1 = reinterpret_cast<bool*>(&data1);
    bool* ptr_Golf_data2 = reinterpret_cast<bool*>(&data2);
    for (size_t i = 0; i < Golf_Size; ++i) {
        *ptr_Golf_data1 = false;
        *ptr_Golf_data2 = false;
        ++ptr_Golf_data1;
        ++ptr_Golf_data2;
    }
}
int T_Golf_engine::check_neighbors(size_t r_, size_t c_) {

    int counter = 0;
    size_t row = 0;
    size_t col = 0;
    bool border_encounted = false;

    size_t r = r_;
    size_t c = c_;
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            
            if(i == 1 && j == 1) {  //don't count yourself
                continue;
            }

            border_encounted = false;
            if(r == 0) {
                if(i == 0) {
                    if(this->Torus) {
                        row = Golf_R - 1;
                    }
                    else {
                        border_encounted = true;
                    }
                }
                else
                if(i == 1) {
                    row = r + i - 1;
                }
                else {
                    row = r + i - 1;
                }
            }
            else
            if(r == Golf_R - 1) {
                if(i == 0) {
                    row = r + i - 1;
                }
                else
                if(i == 1) {
                    row = r + i - 1;
                }
                else {
                    if(this->Torus) {
                        row = 0;
                    }
                    else {
                        border_encounted = true;
                    }
                }
            }
            else {
                row = r + i - 1;
            }

            if(c == 0) {
                if(j == 0) {
                    if(this->Torus) {
                        col = Golf_C - 1;
                    }
                    else {
                        border_encounted = true;
                    }
                }
                else
                    if(j == 1) {
                        col = c + j - 1;
                    }
                    else {
                        col = c + j - 1;
                    }
            }
            else
            if(c == Golf_C - 1) {
                if(j == 0) {
                    col = c + j - 1;
                }
                else
                    if(j == 1) {
                        col = c + j - 1;
                    }
                    else {
                        if(this->Torus) {
                            col = 0;
                        }
                        else {
                            border_encounted = true;
                        }
                    }
            }
            else {
                col = c + j - 1;
            }



            if (!border_encounted) {
                if (data_old[row][col]){
                    ++counter;
                    // cout << "[" << counter << "]->";
                }
            }//if
        }//for j
    }//for i
    // cout << "neighbour counter: [" << counter << "]\n";
    return counter;
}

int T_Golf_engine::check_neighbors_int(size_t r_, size_t c_) {
        int r = static_cast<int>(r_);
        int c = static_cast<int>(c_);
        int Golf_r = static_cast<int>(Golf_R);
        int Golf_c = static_cast<int>(Golf_C);
        int counter = 0;
        size_t row = 0;
        size_t col = 0;
        bool border_encounted = false;
        for (int i = -1; i < 2; ++i) {
            for (int j = -1; j < 2; ++j) {

                if(i == 0 && j == 0) {  //don't count yourself
                    continue;
                }
                border_encounted = false;

                if ((r + i) >= 0 && (r + i) < Golf_r) {
                    row = r + i;
                }
                else {
                    if (this->Torus) {
                        if ((r + i) < 0) {
                            row = r + Golf_r + i;
                        }
                        else {
                            row = r - Golf_r + i;
                        }
                    }
                    else {
                        border_encounted = true;
                    }
                }
                if ((c + j) >= 0 && (c + j) < Golf_c) {
                    col = c + j;
                }
                else {
                    if (this->Torus) {
                        if ((c + j) < 0) {
                            col = c + Golf_c + j;
                        }
                        else {
                            col = c - Golf_c + j;
                        }
                    }
                    else {
                        border_encounted = true;
                    }
                }
                if (!border_encounted) {
                    if (data_old[row][col]){
                        ++counter;
                        cout << "[" << counter << "]->";
                    }
                }//if
            }//for j
        }//for i
        // cout << "neighbour counter: [" << counter << "]\n";
        return counter;
}

bool T_Golf_engine::check_rules(std::vector<int>& vr, int neighbors) {
    for (auto rule : vr) {
        if (rule == neighbors) {
            return true;
        }
    }
    return false;
}

int T_Golf_engine::get_rows()
{
    return golf_engine_rows;
}

int T_Golf_engine::get_cols()
{
    return golf_engine_cols;
}

bool T_Golf_engine::get_cell(int r_, int c_)
{
    size_t r = static_cast<int>(r_);
    size_t c = static_cast<int>(c_);
    // cout << "r:" << r << ",c:" << c << endl; cout.flush();
    assert(r >= 0);
    assert(r < Golf_R);
    assert(c >= 0);
    assert(c < Golf_C);

    return data_new[r][c];
}

void T_Golf_engine::set_cell(int r_, int c_, bool v)
{
    size_t r = static_cast<int>(r_);
    size_t c = static_cast<int>(c_);
    // cout << "r:" << r << ",c:" << c << endl; cout.flush();
    assert(r >= 0);
    assert(r < Golf_R);
    assert(c >= 0);
    assert(c < Golf_C);

    data_new[r][c] = v;
}
void T_Golf_engine::calculate(){
    cout << __PRETTY_FUNCTION__ << endl;
    int live_neighbors = 0;
    swap(data_new, data_old);
    for (size_t r = 0; r < Golf_R; ++r) {
        for (size_t c = 0; c < Golf_C; ++c) {
            live_neighbors = check_neighbors(r, c);

            assert(live_neighbors == check_neighbors_int(r, c));  //comparison int aritmetic with unsigned int

            /* Rules by: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Li */
            if(data_old[r][c]) {
                //rules 1-3
                if (check_rules(Rules_S, live_neighbors)) {
                    data_new[r][c] = true;
                }
                else {
                    data_new[r][c] = false;
                }
            }
            else {
                //rule 4
                if (check_rules(Rules_D, live_neighbors)) {
                    data_new[r][c] = true;
                }
                else {
                    data_new[r][c] = false;
                }
            }
        }
    }
}
