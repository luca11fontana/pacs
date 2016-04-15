#include <iostream> // input output
#include <cmath> // (for sqrt)
#include <vector>
#include <tuple>
#include "readParameters.hpp"
#include "GetPot.hpp"
#include "gnuplot-iostream.hpp"// interface with gnuplot
/*!
  @file main.cpp
  @brief Temperature distribution in a 1D bar.

  @detail
    We solve  \f$ -T^{\prime\prime}(x)+act*(T(x)-T_e)=0, 0<x<L \f$ with 
    boundary conditions \f$ T(0)=To; T^\prime(L)=0\f$
    
    **************************************************
    Linear finite elements
    Iterative resolution by Gauss Siedel.
    **************************************************
    
    Example adapted by Luca Formaggia from  a code found in 
    "Simulation numerique an C++" di I. Danaila, F. Hecht e
    O. Pironneau.
*/
//! helper function
void printHelp()
{
  std::cout<<"USAGE: main [-h] [-v] -p parameterFile (default: parameters.pot)"<<std::endl;
  std::cout<<"-h this help"<<std::endl;
  std::cout<<"-v verbose output"<<std::endl;
}

//! main program
int main(int argc, char** argv)
{
  using namespace std; // avoid std::
  int status(0); // final program status
  GetPot   cl(argc, argv);
  if( cl.search(2, "-h", "--help") )
    {
      printHelp();
      return 0;
    }
  // check if we want verbosity
  bool verbose=cl.search(1,"-v");
  // Get file with parameter values
  string filename = cl.follow("parameters.pot","-p");
  cout<<"Reading parameters from "<<filename<<std::endl;
  // read parameters
  const parameters param=readParameters(filename,verbose);
  // Transfer parameters to local variables
  // I use references to save memory (not really an issue here, it is just
  // to show a possible  use of references)
  // Here I use auto (remember that you need const and & if you want constant references)
  const auto& L= param.L;  // Bar length
  const auto& a1=param.a1; // First longitudinal dimension
  const auto& a2=param.a2; //  Second longitudinal dimension
  const auto& To=param.To; // Dirichlet condition
  const auto& Te=param.Te; // External temperature (Centigrades)
  const auto& k=param.k;  // Thermal conductivity
  const auto& hc=param.hc; // Convection coefficient
  const auto&    M=param.M; // Number of grid elements
  const auto&    outname=param.outname; // Name of the output file
  const auto&    outtype=param.outtype; // Type of the output
  

  //! Precomputed coefficient for adimensional form of equation
  const auto act=2.*(a1+a2)*hc*L*L/(k*a1*a2);

  // mesh size
  const auto h=1./M;
  
  // Solution vector
  vector<double> theta(M);
  double theta0 = To-Te;
  double a(2. + h*h*act);
  double b(-1);
  double c = b;
  vector<double> gamma(M, 0.), y(M,0);
  
  gamma[0] = 1 / a;
  for(auto i = 1; i<M-1; i++)
  	gamma[i] = 1 / ( a - b*gamma[i-1]*c );
  gamma[M-1] = 1 / ( 1 - b*gamma[M-2]*c );
  y[0] = gamma[0]*theta0;
  for(auto i = 1; i<M; i++)
  	y[i] = gamma[i]*( - b*y[i-1]);
  for(auto i = M-1; i>= 0; i--)
  	theta[i] = y[i] - gamma[i]*c*theta[i+1];
  theta.insert (theta.begin(), theta0);

 // Analitic solution

    vector<double> thetaa(M+1);
     for(int m=0;m <= M;m++)
       thetaa[m]=Te+(To-Te)*cosh(sqrt(act)*(1-m*h))/cosh(sqrt(act));

     // writing results with format
     // x_i u_h(x_i) u(x_i) and lauch gnuplot 

     Gnuplot gp;
     std::vector<double> coor(M+1);
     std::vector<double> sol(M+1);
     std::vector<double> exact(M+1);

     if(outtype != "screen") {
        cout<<"Result file: "<<outname.data()<<endl;
        ofstream f(outname.data());
        for(int m = 0; m<= M; m++) 
          f<<m*h*L<<"\t"<<Te+theta[m]<<"\t"<<thetaa[m]<<endl;
        f.close();
     }
     
	 // An example of use of tie and tuples!
     if(outtype != "file"){
         for(int m = 0; m<= M; m++) 
	         std::tie(coor[m],sol[m],exact[m])= std::make_tuple(m*h*L,Te+theta[m],thetaa[m]);
       // Using temporary files (another nice use of tie)
     gp<<"plot"<<gp.file1d(std::tie(coor,sol))<<
       "w lp title 'uh',"<< gp.file1d(std::tie(coor,exact))<<
       "w l title 'uex'"<<std::endl;
     }
     return status;
}
