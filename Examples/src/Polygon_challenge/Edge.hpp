#ifndef HH_EDGE_HH
#define HH_EDGE_HH
#include "Polygon.hpp"
#include <iostream>
#include <vector>
#include <memory>

using namespace Geometry;

class Edge
{
public:
	//default constructor
	Edge() = default;
	Edge(unsigned int a, unsigned int b): a(a), b(b) {};
	//copy constructor
	Edge(const Edge&) = default;
	//assignment operator
	Edge & operator=(Edge&)=default;
	void set(unsigned int, unsigned int);
	std::array<unsigned int, 2> get() const;
	friend std::ostream& operator<<(std::ostream&, Edge const&);
private:
	unsigned int a,b;
};

#endif
