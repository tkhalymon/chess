#ifndef __DECART_HPP__
#define __DECART_HPP__

#include <math.h>
#include <iostream>

class Position
{
public:
	Position();
	Position(const double& x, const double& y);
	~Position();

	const double& x() const;
	const double& y() const;
	
	void x(const double& x);
	void y(const double& y);

	double distance() const;
	double distance(const Position& other) const;

	double angle() const;
	double angle(const Position& other) const;

	// array - [0] is x, [1] is y
	const double* v() const;

	const bool operator == (const Position&) const;
	const bool operator != (const Position&) const;

	const Position operator - (const Position&) const;
	const Position operator + (const Position&) const;
	
	void operator -= (const Position&);
	void operator += (const Position&);
	
	const Position operator * (const double&) const;
	const Position operator / (const double&) const;

	void operator *= (const double&);
	void operator /= (const double&);

	friend std::ostream& operator << (std::ostream& os, const Position& pos);
private:
	// coordinates
	double c[2];
};

#endif
