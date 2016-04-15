#ifndef HH_Parameters_HH
#define HH_Parameters_HH
#include <iosfwd>
#include <string>

struct parameters
{
  //! Bar length
   double L;
  //! First longitudinal dimension
  double a1;
 //! Second longitudinal dimension
  double a2;
  //! Dirichlet condition
  double To;
  //! External temperature 
  double Te;
  //! Conductivity
  double k;
  //! Convection coefficient
  double hc;
  //! Number of elements
  int M;
  //! Name of the output file
  std::string outname;
  // output type
  std::string outtype;
  //! Constructor takes default values
  parameters():
    L(40.),
    a1(4.),
    a2(50.),
    To(46.),
    Te(20.),
    k(0.164),
    hc(1.e-6*200.),
    M(100),
    outname("result.dat"),
    outtype("both")
  {}
};
//! Prints parameters
std::ostream & operator << (std::ostream &,const parameters &);
#endif
