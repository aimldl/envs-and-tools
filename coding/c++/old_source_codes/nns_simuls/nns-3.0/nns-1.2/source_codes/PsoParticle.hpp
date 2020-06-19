#ifndef  __PSOPARTICLE_HPP_
#define  __PSOPARTICLE_HPP_

#include   <iostream>
#include   <cstdlib>
#include   <cassert>
#include   <limits>  // For numeric_limits

using namespace  std;

//==============================================================================
//                              Class Declaration
//==============================================================================
class PsoParticle
{
public:
           PsoParticle( int identifier, int sizeOfDomains );
          ~PsoParticle();
          
  static   void     configure( double XMin, double XMax, double V_initialValue, double pBest_initialValue );
  void     reset( int sizeOfDomains );

  static   double   XMin_;                     // the minimum of location X
  static   double   XMax_;                     // the maximum of location X
  static   double   V_initialValue_;
  static   double   pBest_initialValue_;
  static   bool     isConfigured_;

  int      id_;       // ID or number
  double   fitness_;  // Best fitness for each particle. An example of fitness is MSE or absolute error
  double*  best_;     // Particle best or local bests, i.e.
                      // the best location for this particle so far.
  double*  V_;        // Velocity V
  double*  X_;        // Location X
};

#endif

//==============================================================================
//                                  Comments
//==============================================================================

// Use PsoParticle like a structure.
// When class PsoParticle is declared in a training algorithm, e.g. class Pso,
// declare it as a vector of class, neighter a pointer nor an array in order to
// use a constructor with arguments. That is,
//
//   vector<PsoParticle> particles_;  // Good.
//   PsoParticle*        particles_;  // Bad
//
// Refer to http://www.parashift.com/c++-faq-lite/ctors.html#faq-10.5
//
// As a matter of fact, it is possible to implement PsoParticle to be declared
// as a pointer if a constructor WITHOUT argument is used, i.e. PsoParticle().
// The drawback of this implementation is the class looks slightly messier
// because variables such as sizeOfDomains_, XMin_, and XMax_ are necessary.
// What this means is extra function configure( ... ) and initialize()
// to set values for them. Of course, only one instance of those variables can
// be made by setting them as static variables. However, initialize() can't be
// static because this function will initialize best_, V_, and
// X_, which can't static. Even if configure( ... ) can be static,
// function initialize() will be an overhead if thousands of particles are
// created.
//
// To summarize, declaring class PsoParticle as a vector is more compact or
// lightweight. I am not sure how much advantage there will be of doing this
// because looping a vector adds overhead compared to an array anyway.
//
// In other words, there may not be a big advantage of using vector for performance.
// However, it is possible to modify Pso so that it can change the number of
// particles. With this in mind, use of vector can be justified.
