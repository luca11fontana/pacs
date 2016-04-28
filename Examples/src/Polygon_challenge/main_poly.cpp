#include "Polygon.hpp"
#include "Grid.hpp"
#include <fstream>
#include <iostream>
//! Main program
int main()
{
  using namespace Geometry;
  ifstream ifile;
  ifile.open("mesh.dat");
  Grid mygrid;
  mygrid.read_file(ifile);
  mygrid.print();
  mygrid.total_area();



}
  

