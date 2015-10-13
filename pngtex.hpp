#ifndef __PNGTEX_HPP__
#define __PNGTEX_HPP__

#include <GL/glut.h>
#include <vector>
#include "lodepng.h"

class Texture
{
public:
	Texture();
	Texture(const char* filename);
	~Texture();

	void load(const char* filename);
	void use();

	unsigned w(void);
	unsigned h(void);

private:

	unsigned int texture;
	unsigned _w;
	unsigned _h;
	bool loaded;
};

#endif
