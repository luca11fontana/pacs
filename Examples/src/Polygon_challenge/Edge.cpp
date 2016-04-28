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

// overloading of "less than" operator for a 2-dimensional array
bool operator<(Edge const &e, Edge const &f) {
	auto aux1 = std::minmax(e.a, e.b);
	auto aux2 = std::minmax(f.a, f.b);
	if(aux1.first==aux2.first)
		return aux1.second < aux2.second;
	return aux1.first < aux2.first;
};
