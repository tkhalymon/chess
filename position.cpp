#include "position.hpp"

const double PI = acos(- 1);

Position::Position() : c {0, 0}
{}

Position::Position(const double& x, const double& y) : c {x, y}
{}

Position::~Position()
{}

const double& Position::x() const
{
	return c[0];
}

const double& Position::y() const
{
	return c[1];
}

void Position::x(const double& x)
{
	c[0] = x;
}

void Position::y(const double& y)
{
	c[1] = y;
}

double Position::distance() const
{
	return sqrt(c[0] * c[0] + c[1] * c[1]);
}

double Position::distance(const Position& v) const
{
	return sqrt((c[0] - v.c[0]) * (c[0] - v.c[0]) + (c[1] - v.c[1]) * (c[1] - v.c[1]));
}

double Position::angle() const
{
	if (c[1] > 0)
		return acos(c[0] / distance());
	else
		return 2 * PI - acos(c[0] / distance());
}

double Position::angle(const Position& v) const
{
	if (c[1] - v.c[1] > 0)
		return acos((c[0] - v.c[0]) / distance(v));
	else
		return 2 * PI - acos((c[0] - v.c[0]) / distance(v));
}

const double* Position::v() const
{
	return c;
}

const bool Position::operator == (const Position& v) const
{
	if (c[0] == v.c[0] && c[1] == v.c[1]) return true;
	return false;
}

const bool Position::operator != (const Position& v) const
{
	if (c[0] == v.c[0] && c[1] == v.c[1]) return false;
	return true;
}


const Position Position::operator - (const Position& v) const
{
	return Position (c[0] - v.c[0], c[1] - v.c[1]);
}

const Position Position::operator + (const Position& v) const
{
	return Position (c[0] + v.c[0], c[1] + v.c[1]);	
}

void Position::operator -= (const Position& v)
{
	c[0] -= v.c[0];
	c[1] -= v.c[1];
}

void Position::operator += (const Position& v)
{
	c[0] += v.c[0];
	c[1] += v.c[1];
}

const Position Position::operator * (const double& k) const
{
	return Position(c[0] * k, c[1] * k);
}

const Position Position::operator / (const double& k) const
{
	return Position(c[0] / k, c[1] / k);
}

void Position::operator *= (const double& k)
{
	c[0] *= k;
	c[1] *= k;
}

void Position::operator /= (const double& k)
{
	c[0] /= k;
	c[1] /= k;
}

std::ostream& operator << (std::ostream& os, const Position& pos)
{
	
}