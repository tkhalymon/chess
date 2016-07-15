#ifndef __PANEL_HPP__
#define __PANEL_HPP__

#include "position.hpp"
#include <vector>

class Panel
{
public:
	Panel();
	~Panel();

	// draws side panel
	void render();

	// processes window size changing
	void reshape();

	// panel width (without frame)
	int width();

	void enable();
	
	void disable();

	// check if enabled
	bool enabled();
private:

	Position coords[8];
	int _width;
	bool show;
};

#endif