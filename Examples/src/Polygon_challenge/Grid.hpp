#ifndef HH_GRID_HH
#define HH_GRID_HH
#include "Polygon.hpp"
#include "Edge.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <set>

using namespace Geometry;

class Grid
{
public:
	//default constructor
	Grid() = default;
	//copy constructor
	Grid(const Grid&) = default;
	//assignment operator
	Grid & operator=(Grid&)=default;
	void read_file( std::ifstream & ifile);
	void print_grid();
	double total_area();
	void print_edges();
	void print_edges_file();
private:
	Vertices points;
	std::vector<std::shared_ptr<AbstractPolygon>> polygons;
	std::vector<Edge> alledges;
	std::vector<Edge> boundary;
};


#endif
