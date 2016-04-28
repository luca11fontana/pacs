#ifndef HH_GRID_HH
#define HH_GRID_HH
#include "Polygon.hpp"
#include <iostream>
#include <vector>
#include <memory>

using namespace Geometry;
using namespace std;

class Grid
{
public:
	//default constructor
	Grid() = default;
	//copy constructor
	Grid(const Grid&) = default;
	//assignment operator
	Grid & operator=(Grid&)=default;
	void read_file( ifstream & ifile);
	void print();
	double total_area();
private:
	Vertices points;
	vector<shared_ptr<AbstractPolygon>> polygons;
};


#endif
