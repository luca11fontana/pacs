#include "Grid.hpp"
#include "Edge.hpp"
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
  vector<unsigned int> edges;
  set<Edge> edges_set, internal_set;
  for(auto i=0; i<npoly; i++){
    getline(ifile, s);
    k = s.find(" ");
    s.erase(s.begin(), s.begin() + k +1);
    type = s[0];
    s.erase(s.begin(), s.begin() + 2);
    stringstream ss(s);
    while(getline(ss,s, ' ')){
      //cout<<stoi(s)<<" ";
      v.emplace_back( points[stoi(s)]);
      edges.push_back(stoi(s));
    }
    // create the vector of shared ptr to abstract polygon
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
    // create all the edges of the polygon and add them to the sets
    for(auto i=0; i < edges.size(); i++){
      Edge e(edges[i], edges[(i+1) % edges.size()]);
      auto insertion = edges_set.insert(e);
      // if I have already inserted the edge, then it is internal
      if (!insertion.second)
        internal_set.insert(e);
    }
    v.clear();
    edges.clear();
    //cout<<endl;
  }
  alledges.resize(edges_set.size());
  copy(edges_set.begin(), edges_set.end(), alledges.begin());
  // the Boundary set is given as all - internals; I can copy it directly in the vector
  boundary.resize(edges_set.size() - internal_set.size());
  set_difference(edges_set.begin(), edges_set.end(), internal_set.begin(),
              internal_set.end(),boundary.begin());
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

void Grid::print_edges(){
  cout<<std::endl<<"ALL EDGES: "<<std::endl;
  for(auto i=alledges.begin(); i != alledges.end(); i++)
    cout<<*i;
  cout<<std::endl<<"BOUNDARY EDGES: "<<std::endl;
  for(auto i=boundary.begin(); i != boundary.end(); i++)
    cout<<*i;
}

void Grid::print_edges_file(){
  ofstream ofile;
  ofile.open("AllEdges.txt");
  ofile<<std::endl<<"ALL EDGES: "<<std::endl;
  for(auto i=alledges.begin(); i != alledges.end(); i++)
    ofile<<*i;
  ofile.close();
  ofile.open("BoundaryEdges.txt");
  ofile<<std::endl<<"BOUNDARY EDGES: "<<std::endl;
  for(auto i=boundary.begin(); i != boundary.end(); i++)
    ofile<<*i;
  ofile.close();
}