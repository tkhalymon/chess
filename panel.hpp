#ifndef __PANEL_HPP__
#define __PANEL_HPP__

#include "position.hpp"
#include <vector>

class Panel
{
public:
	Panel();
	~Panel();

	void render();

	void reshape();

	void init(std::vector<char *>* notation);
private:

	Position coords[8];
	int width;
	std::vector<char*>* notation;
};

#endif