#include <iostream>
#include <string>
#include "parameters.hpp"

const char* norm_name[] = {"RN", "H1", "L2"};

std::ostream & operator << (std::ostream & out,const parameters & p)
{
  out<<"PARAMETER VALUES:"<<"\n";
  out<<"L= "<<p.L<<"\n";
  out<<"a1= "<<p.a1<<"\n";
  out<<"a2= "<<p.a2<<"\n";
  out<<"To= "<<p.To<<"\n";
  out<<"Te= "<<p.Te<<"\n";
  out<<"k= "<<p.k<<"\n";
  out<<"hc= "<<p.hc<<"\n";
  out<<"M= "<<p.M<<"\n";
  out<<"name of the output file= "<<p.outname<<"\n";
  out<<"output type= "<<p.outtype<<"\n\n";
  return out;
}
