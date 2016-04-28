#include "Grid.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>

using namespace Geometry;
using namespace std;

void Grid::read_file( ifstream & ifile)
{
  points.clear();
  polygons.clear();
  string s;
  int npoly(0), nvert(0);

  getline(ifile, s);
  stringstream ss(s);
  getline(ss, s, ' ');
  nvert = stoi(s);
  getline(ss, s, ' ');
  npoly = stoi(s);

  double x,y;
  for(auto i=0; i<nvert; i++){
    getline(ifile, s);
    stringstream s1(s);
    getline(s1, s, ' ');
    getline(s1, s, ' ');
    x = stod(s);
    getline(s1, s, ' ');
    y = stod(s);
    Point2D aux(x, y);
    points.push_back(aux);
  }

  char type;
  int k;
  Vertices v;
  for(auto i=0; i<npoly; i++){
    getline(ifile, s);
    k = s.find(" ");
    s.erase(s.begin(), s.begin() + k +1);
    type = s[0];
    s.erase(s.begin(), s.begin() + 2);
    stringstream ss(s);
    while(getline(ss,s, ' '))
      v.emplace_back( points[stoi(s)]);
    if(type=='0'){
      auto pointer = std::make_shared<Triangle>(Triangle(v));
      polygons.emplace_back(pointer);
    }
    else if (type == '1'){
      auto pointer = std::make_shared<Square>(Square(v));
      polygons.emplace_back(pointer);
    }
    else {
      auto pointer = std::make_shared<Polygon>(Polygon(v));
      polygons.emplace_back(pointer);
    }
    v.clear();
  }

}

void Grid::print_grid()
{
  cout<<"Mesh points:"<<endl;
  for(auto i=0; i<points.size(); i++)
    cout<<i<<": x="<<points[i].x()<<" y="<<points[i].y()<<endl;
  cout<<"POLYGONS:"<<endl;
  for(auto i=0; i<polygons.size(); i++){
    polygons[i]->showMe();
    cout<<endl;
  } 
}

double Grid::total_area()
{
  cout<<endl<<"Total area: ";
  double out;
  for(auto i=0; i<polygons.size(); i++)
    out += polygons[i]->area();
  cout<<out<<endl; 
  return out;
}