#include "Polygon.hpp"
#include "Grid.hpp"
#include "Edge.hpp"
#include <fstream>
#include <iostream>
//! Main program
int main()
{
  using namespace Geometry;
  using namespace std;
  
  ifstream ifile;
  ifile.open("mesh.dat");
  Grid mygrid;
  mygrid.read_file(ifile);
  mygrid.print_grid();
  mygrid.total_area();



}
  

