#include "T_Golf_engine.h"
#include <vector>
using namespace std;

T_Golf_engine::T_Golf_engine() {
	data_new = data1;
	ptr_ptr_data = &data_new;
    Torus = false;
}
voidT_Golf_engine::swap_data() {
    swap(data_new, data_old);
}
void T_Golf_engine::reset() {

    bool* ptr_Golf_data1 = reinterpret_cast<bool*>(&Golf_data1);
    bool* ptr_Golf_data2 = reinterpret_cast<bool*>(&Golf_data2);
    for (size_t i = 0; i < Golf_Size; ++i) {
        *ptr_Golf_data1 = false;
        *ptr_Golf_data2 = false;
        ++ptr_Golf_data1;
        ++ptr_Golf_data2;
    }
}
int check_neighbors(size_t r, size_t c) {
    int counter = 0;
    size_t row = 0;
    size_t col = 0;
    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            encounter_border = false;
            if ((r + i) >= 0 && (r + i) < Golf_R) {
                row = r + i;
            }
            else {
                if (Torus) {  
                    if ((r + i) < 0) {
                        row = r + Golf_R - i;
                    }
                    else {
                        row = r - Golf_R + i;
                    }
                }
                else {
                    encounter_border = true;
                }
            }
            if ((c + j) >= 0 && (c + j) < Golf_C) {
                col = c + j;
            } 
            else {
                if (Torus) {                    
                    if ((c + j) < 0) {
                        col = c + Golf_C - j;
                    }
                    else {
                        col = c - Golf_C + j;
                    }
                }
                else {
                    encounter_border = true;
                }
            }
            if (!encounter_border) {
                if (data_old[row, col]{
                    ++counter;
                }
            }//if
        }//for j
    }//for i
    return counter;
}
bool check_rules(vector<int>& vr, int neighbors) {
    for (auto rule : vr) {
        if (rule == neighbors) {
            return true;
        }
    }
    return false;
}
void T_Golf_engine::calculate(){
    int Live_neighbors = 0;
    swap(data_new, data_old);
    for (size_t r = 0; r < Golf_R; ++r) {
        for (size_t c = 0; c < Golf_C; ++c) {
            Live_neighbors = check_neighbors(r, c);
            if (check_rules(Rules_D, Live_neighbors) 
                && check_rules(Rules_S, Live_neighbors)) {
                data_new[r][c] = true;
            }
            else {
                data_new[r][c] = false;
            }
        }
    }
}