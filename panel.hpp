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

	int width();

	void enable();
	
	void disable();

	bool enabled();
private:

	Position coords[8];
	int _width;
	std::vector<char*>* notation;
	bool show;
};

#endif