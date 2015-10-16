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

	Position inside[2];
	Position outside[2];
	int width;
	std::vector<char*>* notation;
};

#endif