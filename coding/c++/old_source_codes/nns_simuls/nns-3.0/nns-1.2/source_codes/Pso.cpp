#include  "Pso.hpp"

//==============================================================================
//                     Definition of static variables
//==============================================================================
int			Pso::numberOfParticles_;
int			Pso::sizeOfDomains_;
bool        Pso::useParticleHistoryReset_;
bool        Pso::is_gBest_updated_;
double		Pso::w_;
double		Pso::c1_;
double		Pso::c2_;
double		Pso::VMax_;
double		Pso::XMin_;
double		Pso::XMax_;
double		Pso::V_initialValue_;

//double Pso::gBest_initialValue_;

//==============================================================================
//                        Static Public functions
//==============================================================================

// IMPORTANT! RUN THESE FUNCTIONS BEFORE THIS CLASS IS CONSTRUCTED!!!
void		Pso::configure( Config& configObj )
{
  assert( configObj.get_isConfigured_() );
  double pBest_initialValue;

  TrainingAlgorithms::configure( configObj );

  useParticleHistoryReset_ = configObj.get_psoObj_().get_useParticleHistoryReset_();
  numberOfParticles_       = configObj.get_psoObj_().get_numberOfParticles_();
  w_                       = configObj.get_psoObj_().get_w_();
  c1_                      = configObj.get_psoObj_().get_c1_();
  c2_                      = configObj.get_psoObj_().get_c2_();
  VMax_                    = configObj.get_psoObj_().get_VMax_();
  XMin_                    = configObj.get_psoObj_().get_XMin_();
  XMax_                    = configObj.get_psoObj_().get_XMax_();
  V_initialValue_          = configObj.get_psoObj_().get_V_initialValue_();
  pBest_initialValue       = configObj.get_psoObj_().get_pBest_initialValue_();

  PsoParticle::configure( XMin_, XMax_, V_initialValue_, pBest_initialValue );

//  gBest_initialValue_ = configObj.get_psoObj_().get_gBest_initialValue_();
}
int			Pso::get_numberOfParticles_()
{
  return numberOfParticles_;
}

int			Pso::get_sizeOfDomains_()
{
  return sizeOfDomains_;
}


// IMPORTANT! RUN THESE FUNCTIONS BEFORE THIS CLASS IS CONSTRUCTED!!!

//==============================================================================
//                            Public functions
//==============================================================================

Pso::Pso()
{
  assert( ( w_  > 0.0 ) );
  assert( ( c1_ > 0.0 ) );
  assert( ( c2_ > 0.0 ) );
  assert( ( VMax_ > 0.0 ) );

  assert( ( XMin_ < XMax_ ) );
  assert( XMax_ );
  assert( ( numberOfParticles_ > 0 ) );
  // Also, don't set the initial V_[i] to zero. It will also freeze a particle
  // to zero. If you don't like a large value, pick a small value around zero.
  assert( ( V_initialValue_ > 0.0 ) );
  // When gBest_initialValue_ = - numeric_limits<double>::max(), gBest_initialValue_ won't be used.
  // The initial value will be determined by either the CNN's initial weights (random) or externally loaded values (load_manually".
//  assert( ( gBest_initialValue_ >= 0.0 ) || gBest_initialValue_ == - numeric_limits<double>::max() );

  p_gBest_ = -1;  // Set it to a negative number to assert after the for loop.
  is_gBest_updated_ = false;  // A new feature for SRN
}

Pso::~Pso()
{
}

bool
Pso::initialize( int sizeOfDomains, bool matchInitialWeights, Neuron* neurons,
                 int totalNumOfLayers, int* numOfNeurons, int totalNumOfNeurons )
{
  if ( trace4dbg_ ) tout << "  bool Pso::initialize( ... )" << endl;

  assert( ( sizeOfDomains > 0 ) );
  assert( matchInitialWeights );
  assert( ( totalNumOfLayers > 0 ) );
  assert( ( totalNumOfLayers > 0 ) );

  bool isInitialWeightMatchDone;
  int numOfWeights;
  int n;  // Count for "n"eurons
  int d;  // Count for "d"imension of PSO particle. It's related to sizeOfDomains_.
  int w;  // Count for "w"eights. It's related to numOfWeights_" in a neuron "neurons[ n ]".

  // Design issue: Use a vector rather than a pointer.
  //   Using a one dimensional double type pointer to store weights is definitely possible.
  //   But to ensure there is no possibility to override an existing memory location by accident,
  //   I'll use a vector. In other words, the following lines are replaced by lines for a vector.
  //
  //   double* weights;
  //   int     numOfWeights;
  //   numOfWeights = neurons[ n ].fetch_numOfWeights_();
  //   weights = new double [ numOfWeights ];
  //
  //   Use a vector pointer so that the content of the vector can be kept even when the vector is passed
  //   to a different function.
  vdouble* weights_vector_p = new vdouble [1];

  sizeOfDomains_ = sizeOfDomains;

  // TODO: Is this really necessary?
  // Isn't it just sufficient to point to X, e.g. particles_.at( p_min ).X_?
  // Don't ever set gBest_[d] to infinity (You mean zero?).
  // It will end up setting the velocity to zero all the time.
  gBest_    = new double [ sizeOfDomains_ ];
  if ( matchInitialWeights )
  {
    // This loop will skip the input layer because numOfNeurons_[ 0 ] = 0.
    // Note the number of neurons at each layer may differ.
    // l stands for layer.
    n = 0;
    d = 0;
    for ( int l = 1; l < totalNumOfLayers; l++ )
    {
      if ( trace4dbg_ ) tout << "  layer " << l << endl;
      for ( int i = 0; i < numOfNeurons[ l ]; i++ )
      {
        // Fetch the values in weights of a neuron "neurons[n]".
        // Design issues: These values are stored in a vector pointer weights_vector_p.
        //   If just a vector is used, the values aren't stored when the function
        //   fetch_weights_ is exited. In order to store the values, a vector pointer is used.
        neurons[ n ].fetch_weights_( weights_vector_p );
        numOfWeights = neurons[ n ].get_numOfWeights_();

        // This part is redundant when the function works as it's designed.
        // "weights_vector_p->size()" should be equal to "numOfWeights_" in a neuron "neurons[ n ]".
        assert( !( weights_vector_p->size() - numOfWeights ) );

        for ( w = 0; w < numOfWeights; w++ )
        {
      	  gBest_[ d ] = weights_vector_p->at( w );
      	  if ( trace4dbg_ )
      	  {
            tout << "    " << "neurons[" << n << "].weights[" << w << "]=" << weights_vector_p->at( w )
            	   << "  => gBest_[" << d <<"]=" << gBest_[ d ] << endl;

      	  }
    	  d++;
        }
        n++;
      }
    }
    assert( ! ( n - totalNumOfNeurons ) );  // n should be equal to totalNumOfNeurons_. Otherwise, array index for neurons does not match totalNumOfNeurons_.
    assert( ! ( d - sizeOfDomains_ ) );     // d should be equal to sizeOfDomains_.

    isInitialWeightMatchDone = true;
  }
  else
  {
	for ( int d = 0; d < sizeOfDomains_; d++ )
	{
	  gBest_[ d ] = numeric_limits<double>::max();
//	  gBest_[ d ] = gBest_initialValue_;
	}
	isInitialWeightMatchDone = false;
  }

  for ( int p = 0; p < numberOfParticles_; p++ )
    particles_.push_back( PsoParticle( p, sizeOfDomains ) );

  globalFitness_ =  numeric_limits<double>::max();          // infinity

  return isInitialWeightMatchDone;
}

double*		Pso::get_weights_( int index ) const
{
  return particles_.at( index ).X_;
}

int			Pso::get_p_gBest_() const
{
  return p_gBest_;
}

void     	Pso::set_p_gBest_( int indexGBestParticle )
{
  p_gBest_ = indexGBestParticle;
}

double		Pso::get_globalFitness_() const  // globalFitness_ is the best fitness, e.g. error, achived so far.
{
  return globalFitness_;
}

bool
Pso::get_useParticleHistoryReset_() const
{
  return useParticleHistoryReset_;
}

bool
Pso::get_is_gBest_updated_() const
{
  return is_gBest_updated_;
}

vpsop
Pso::get_particles_() const
{
  return particles_;
}


// Pso::evaluate( ... )
//
// update_pBest( errorForParticles );
//   Given the MSEs at the current epoch, update a particle's fitness_
//   if any of the current MSE is better than the particle's "history".
// update_gBest_();
//   Update globalFitness_ if any fitness_ is smaller than the current
//   globalFitness_.

void
Pso::evaluate( int epoch, double* errorForParticles, int numberOfParticles )
{
//***  tout << "Pso::evaluate( int epoch, double* errorForParticles, int numberOfParticles )" << endl;
//***  tout << "\tepoch = " << epoch << endl;
//***  for ( int p = 0; p < numberOfParticles; p++ )
//***    tout << "    errorForParticles[" << p << "] = " << errorForParticles[p] << endl;
  update_pBest( errorForParticles, numberOfParticles );
  update_gBest_( numberOfParticles );
}

// pBest is the location X for best fitness_ for the (local) particle
// found so far. If a new location with a better fitness_ is found,
// pBest should be changed/updated.
//
// In this function, MSE (Mean-Sqaured Error) is the fitness criterion.
// So, a better fitness_ means a lower MSE.
// Assume all the fitness_ are initialized with an infinity.
// In this way, the locations in the first epoch are stored without exception.

void
Pso::update_pBest( double* errorForParticles, int numberOfParticles )
{
//***  tout << "Pso::update_pBest( double* errorForParticles, int numberOfParticles )" << endl;

  double tmpError;
  for ( int p = 0; p < numberOfParticles; p++ )
  {
    tmpError = errorForParticles[ p ];
//***    tout << "    errorForParticles[" << p << "] = " << errorForParticles[ p ] << endl;

    // If the new tmpError is smaller/better than any of the previous one
    // stored in fitness_, renew fitness_ and best_.
    // Note fitness_ is assumed to be initialized to infinity.
    // Note also that the following if statement is called for all the particles
    // at the first epoch because the first values in tmpError are the smallest
    // Mse anyway.
    if ( particles_.at( p ).fitness_ > tmpError )
    {
      particles_.at( p ).fitness_ = tmpError;
      particles_.at( p ).best_    = particles_.at( p ).X_;

//***      tout << "      particles_.at(" << p << ").fitness_ = " << tmpError << endl;
//***      tout << "      particles_.at(" << p << ").X_[0] = " << particles_.at( p ).X_[0] << endl;
    }
  }
}

// Check if the minimum of the current fitness_ is better/smaller than globalFitness_.
// If so, update globalFitness_ to the minimum.
//
// Note there can be a multiple number of best particles.
// It's important to set p_min in a range other than
// 0 <= p_min < numberOfParticles. By doing this, a logical bug can be avoided.
//
// Set minimum to infinity so that the first value is stored as minimum.
// globalFitness_ is assumed to be initialized as infinity.
// p_gBest_ is assumed to be initialized as -1.

void
Pso::update_gBestWtHistoryReset_( int numberOfParticles, int cellIndex )
{
  double minimum = numeric_limits<double>::max();

  is_gBest_updated_ = false;  // If the global best is updated, reset particle history.

  for ( int p = 0; p < numberOfParticles; p++ )  // Find the minimum
  {
    if ( minimum > particles_.at( p ).fitness_ )
      minimum = particles_.at( p ).fitness_;
  }

  // Store all particles with the best fitness. In this way, all the best particles can be found.
  bestParticles_.clear();
  for ( int p = 0; p < numberOfParticles; p++ )
  {
    if ( minimum == particles_.at( p ).fitness_ )
      bestParticles_.push_back( p );
  }

  // Keep the best particle as it is when the global fitness doesn't change.
  // If the fitness has been changed, set the first particle as the best particle.
  if ( minimum < globalFitness_ )
  {
    p_gBest_          = bestParticles_.at( 0 );
    globalFitness_    = particles_.at( p_gBest_ ).fitness_;
    gBest_            = particles_.at( p_gBest_ ).X_;
    is_gBest_updated_ = true;
  }

  // Do not remove the following line. It looks redundant, but essential.
  // When update_pBest() fails to set any fitness_, a logical error/bug can be detected here.
  assert( ( p_gBest_ >= 0 ) && ( p_gBest_ < numberOfParticles) );
}

// Check if the minimum of the current fitness_ is better/smaller than globalFitness_.
// If so, update globalFitness_ to the minimum.

void
Pso::update_gBest_( int numberOfParticles )
{
  int    p_min;
  double minimum;

  // It's important to set p_min in a range other than
  // 0 <= p_min < numberOfParticles. By doing this, a logical bug can be avoided.
  //
  // Set minimum to infinity so that the first value is stored as minimum.
  p_min = -1;  // Set p_min to a negative number to assert after the for loop.
  minimum = numeric_limits<double>::max();

  // Determine the particle with the smallest MSE/fitness_.
  for ( int p = 0; p < numberOfParticles; p++ )
  {
//***    tout << "  p = " << p << endl;
//***    tout << "    particles_.at(" << p << ").fitness_ = " << particles_.at( p ).fitness_ << endl;

    if ( minimum > particles_.at( p ).fitness_ )
    {
      p_min   = p;
      minimum = particles_.at( p ).fitness_;
      p_gBest_ = p_min;  // For debugging, PSRN, and CSRN.

//***      tout << "    p_min = " << p_min << ": minimum = " << minimum << endl;
    }
  }
//***  tout << "  p_min = " << p_min << ": fitness_(min) = " << minimum << endl;

  // Do not remove the following line. It looks redundant, but essential.
  // When update_pBest() fails to set any fitness_, a logical error/bug
  // can be detected here.
  assert( ( p_min >= 0 ) && ( p_min < numberOfParticles) );

  // If the particle with the smallest fitness_ in this epoch has smaller
  // fitness value, e.g. MSE, than the global best so far, update the global
  // best.
  if ( globalFitness_ > particles_.at( p_min ).fitness_ )
  {
    globalFitness_ = particles_.at( p_min ).fitness_;
    gBest_    = particles_.at( p_min ).X_;

//***    tout << "  globalFitness_ >  particles_.at(" << p_min << ").fitness_ " << endl;
//***    tout << "  " << globalFitness_ << ">" << particles_.at( p_min ).fitness_ << endl;
  }

//***  if ( globalFitness_ <= particles_.at( p_min ).fitness_ )
//***  {
//***    tout << "  globalFitness_ <= particles_.at(" << p_min << ").fitness_ " << endl;
//***    tout << "  " << globalFitness_ << "<=" << particles_.at( p_min ).fitness_ << endl;
//***  }
}

// Lots of dummy variables are used for debugging purposes.
// Leave them as they are for debugging for the future.
void
Pso::updateVelocityEquation( int numberOfParticles, int sizeOfDomains )
{
  assert( (numberOfParticles > 0) && (sizeOfDomains>0) );

  double newVelocity;
  for ( int p = 0; p < numberOfParticles; p++ )
  {  // Update velocity
    for ( int d = 0; d < sizeOfDomains; d++ )
    {
      // Design issue: Do not define uniformRV().
      //   I don't know why exactly this happens, but it will behave weirdly in the following code.
      //   Instead, use "(double) ( (double) rand() / (double) RAND_MAX )".
      newVelocity
        = w_ *  particles_.at( p ).V_[ d ]          // Inertia term
        + c1_*( particles_.at( p ).best_[ d ] - particles_.at( p ).X_[ d ] )
             * (double) ( (double) rand() / (double) RAND_MAX )
        + c2_*( gBest_[ d ] - particles_.at( p ).X_[ d ] )
             * (double) ( (double) rand() / (double) RAND_MAX );
      particles_.at( p ).V_[ d ] = newVelocity;

    // Check the boundary
      if ( particles_.at( p ).V_[ d ] > VMax_ )
        particles_.at( p ).V_[ d ] = VMax_;
      else if ( particles_.at( p ).V_[ d ] < -VMax_ )
        particles_.at( p ).V_[ d ] = -VMax_;
    }
  }
}

void
Pso::updatePositionEquation( int numberOfParticles, int sizeOfDomains )
{
  assert( (numberOfParticles > 0) && (sizeOfDomains>0) );

  double tmpX;  // Compilation error if this is included in the if statement.
  for ( int p = 0; p < numberOfParticles; p++ )
  {
    for ( int d = 0; d < sizeOfDomains; d++ )
    {
      tmpX                       = particles_.at( p ).X_[ d ];
      particles_.at( p ).X_[ d ] = particles_.at( p ).X_[ d ] + particles_.at( p ).V_[ d ];

      if ( particles_.at( p ).X_[ d ] > XMax_ )  // Check the boundary
        particles_.at( p ).X_[ d ] = XMax_;
      else if ( particles_.at( p ).X_[ d ] < XMin_ )
        particles_.at( p ).X_[ d ] = XMin_;
    }
  }
}

// This is a new feature added to the conventional PSO.
// What this function does is to reset all the particles history except one with global best.
// Note there can be a multiple number of best particles.
// Their histories are all valide, so do not reset their histories.

void
Pso::resetParticleHistory( int time_o, int time_i, int numberOfParticles, int sizeOfDomains, int cellIndex )
{
  assert( !bestParticles_.empty() );
  assert( sizeOfDomains > 0 );

  bool reset;

  lout[ cellIndex ] << "\nvoid Pso::resetParticleHistory( int time_o, int time_i, int numberOfParticles, int sizeOfDomains, int cellIndex )" << endl;
  lout[ cellIndex ] << "time_o=" << time_o << " time_i=" << time_i << " Best particle: ";
  for ( int c = 0; c < bestParticles_.size(); c++ )
	lout[ cellIndex ] << bestParticles_.at( c ) << " ";
  lout[ cellIndex ] << endl;

  for ( int p = 0; p < numberOfParticles; p++ )
  {
	reset = true;
	for ( int c = 0; c < bestParticles_.size(); c++ )
	{
	  if ( p == bestParticles_.at( c ) )  // Reset except the global best particle
        reset = false;
	}
	if ( reset )
	  particles_.at( p ).reset( sizeOfDomains );
  }
}

//==============================================================================
//                            Protected functions
//==============================================================================
//==============================================================================
//                            Private functions
//==============================================================================
