#include "pngtex.hpp"

Texture::Texture()
{
	loaded = false;
}

Texture::Texture(const char* filename)
{
	this->load(filename);
}

Texture::~Texture()
{

}

void Texture::load(const char *fileName)
{
	if (!loaded)
	{
		std::vector<unsigned char> image;
		unsigned error = lodepng::decode(image, _w, _h, fileName);
		if (error != 0) exit(7);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, _w, _h, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
		image.clear();
		loaded = true;
	}
}

void Texture::use(void)
{
	glBindTexture(GL_TEXTURE_2D, texture);
}

unsigned Texture::w(void)
{
	return _w;
}

unsigned Texture::h(void)
{
	return _h;
}
