#include "Edge.hpp"

void Edge::set(unsigned int i, unsigned int j){
	a = i;
	b = j;
};

std::array<unsigned int, 2> Edge::get() const{
	std::array<unsigned int, 2> v={a,b};
	return v;
};

std::ostream& operator<<(std::ostream& ost, Edge const& ed){
	std::array<unsigned int, 2> v=ed.get();
	ost<<v[0]<<","<<v[1]<<std::endl;
	return ost;
};

