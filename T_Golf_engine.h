#ifndef T_GOLF_ENGINE_H
#define T_GOLF_ENGINE_H

#include <vector>

enum {Golf_R = 5, Golf_C = Golf_R, Golf_Size = Golf_R * Golf_C};
class T_Golf_engine {

	bool data1[Golf_R][Golf_C];
	bool data2[Golf_R][Golf_C];	
	bool (*data_old)[Golf_R][Golf_C];
public:
	std::vector<int> Rules_D;
	std::vector<int> Rules_S;
	bool Torus;
	bool(*data_new)[Golf_R][Golf_C];
	
	T_Golf_engine();
	void reset();
	void calculate();
	void swap_data();
};

#endif // T_GOLF_ENGINE_H