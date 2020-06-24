#include  "PsoParticle.hpp"

//==============================================================================
//                     Definition of static variables
//==============================================================================
double		PsoParticle::XMin_;
double		PsoParticle::XMax_;
double		PsoParticle::V_initialValue_;
double		PsoParticle::pBest_initialValue_;
bool        PsoParticle::isConfigured_;

//==============================================================================
//                        Static Public functions
//==============================================================================

void
PsoParticle::configure( double XMin, double XMax, double V_initialValue, double pBest_initialValue )
{
  assert( ( pBest_initialValue_  >= 0.0 ) );  // pBest_initialValue_ can be zero.

  XMin_               = XMin;
  XMax_               = XMax;
  V_initialValue_     = V_initialValue;
  pBest_initialValue_ = pBest_initialValue;

  isConfigured_ = true;
}

//==============================================================================
//                            Public functions
//==============================================================================

// Assume configure( .. ) is run in class Pso BEFORE class PsoParticle is instantiated.
// In this way, PsoParticle is guaranteed to be initialized.
// X_[ d ] takes an uniform RV between [ XMin, XMax ].
// Don't set best_[ d ] to infinity. It will end up setting velocity V_[d] to zero all the time.
// Also, don't set the initial V_[d] to zero. It will also freeze a particle
// to zero. If you don't like a large value, pick a small value around zero.

PsoParticle::PsoParticle( int identifier, int sizeOfDomains )
{
  assert( isConfigured_ );
  assert( ( sizeOfDomains > 0 ) );

  id_      = identifier;
  fitness_ = numeric_limits<double>::max();  // infinity

  best_    = new double [ sizeOfDomains ];
  V_       = new double [ sizeOfDomains ];
  X_       = new double [ sizeOfDomains ];

  reset( sizeOfDomains );
}

PsoParticle::~PsoParticle()
{
}

void
PsoParticle::reset( int sizeOfDomains )
{
  assert( isConfigured_ );
  assert( ( sizeOfDomains > 0 ) );

  for ( int d = 0; d < sizeOfDomains; d++ )
  {
    V_[ d ]    = V_initialValue_;
    X_[ d ]    = XMin_ + ( XMax_ - XMin_ ) * (double) ( (double) rand() / (double) RAND_MAX );
    best_[ d ] = pBest_initialValue_;
  }
}
//==============================================================================
//                            Protected functions
//==============================================================================

//==============================================================================
//                            Private functions
//==============================================================================
