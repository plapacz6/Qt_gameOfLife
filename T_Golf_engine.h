#ifndef T_GOLF_ENGINE_H
#define T_GOLF_ENGINE_H

#include <cstdlib>
#include <vector>

enum {Golf_R = 75, Golf_C = Golf_R, Golf_Size = Golf_R * Golf_C};
class T_Golf_engine {
    int golf_engine_rows = Golf_R;
    int golf_engine_cols = Golf_C;
	bool data1[Golf_R][Golf_C];
	bool data2[Golf_R][Golf_C];	
    bool (*data_old)[Golf_R];
    int check_neighbors(size_t r_, size_t c_);
    bool check_rules(std::vector<int>& vr, int neighbors);
public:
    bool Torus;
    int get_rows();
    int get_cols();
    bool get_cell(int r, int c);
    void set_cell(int r, int c, bool v);

	std::vector<int> Rules_D;
	std::vector<int> Rules_S;

    bool(*data_new)[Golf_R];
	
	T_Golf_engine();
	void reset();
	void calculate();
	void swap_data();
};

#endif // T_GOLF_ENGINE_H
