#include "Grid.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace Geometry;
using namespace std;

void Grid::read_file( ifstream & ifile)
{
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

  int type, k;
  vector<int> v;
  for(auto i=0; i<npoly; i++){
    getline(ifile, s);
    k = s.find(" ");
    s.erase(s.begin(), s.begin() + k +1);
    type = s.front();
    s.erase(s.begin(), s.begin() + 2);
    stringstream ss(s);
    while(getline(ss,s, ' ')){
      v.push_back( stoi(s));
      cout<<stoi(s)<<" ";
    }
    cout<<endl;
  }

}

void Grid::print()
{
  cout<<"Mesh points:"<<endl;
  for(auto i=0; i<points.size(); i++)
    cout<<i<<": x="<<points[i].x()<<" y="<<points[i].y()<<endl;
}