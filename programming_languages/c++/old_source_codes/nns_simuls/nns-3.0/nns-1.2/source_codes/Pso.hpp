#ifndef  __PSO_HPP_
#define  __PSO_HPP_

#include  "PsoParticle.hpp"
#include  "TrainingAlgorithms.hpp"
#include  "Neuron.hpp"  // For Neuron in Pso::initialize( ... )

using namespace std;

//==============================================================================
//                              Type Definitions
//==============================================================================
typedef vector<PsoParticle> vpsop;
typedef vector<int>         vint;

//==============================================================================
//                              Class Declaration
//==============================================================================
class      Pso : public TrainingAlgorithms
{ 
public:
           Pso();
          ~Pso();
  static
  void     configure( Config& configObj );  // IMPORTANT! RUN THESE FUNCTIONS BEFORE THIS CLASS IS CONSTRUCTED!!!
  static
  int      get_numberOfParticles_();
  static
  int      get_sizeOfDomains_();
  bool     initialize( int sizeOfDomains, bool matchInitialWeights, Neuron* neurons,
                       int totalNumOfLayers, int* numOfNeurons, int totalNumOfNeurons );
  double*  get_weights_( int index ) const;
  int      get_p_gBest_() const;
  void     set_p_gBest_( int indexGBestParticle );
  double   get_globalFitness_() const;
  bool     get_useParticleHistoryReset_() const;  // A new feature for SRN
  bool     get_is_gBest_updated_() const;  // A new feature for SRN
  vpsop    get_particles_() const;

  void     evaluate( int epoch, double* errorForParticles, int numberOfParticles );
  void     update_pBest( double* errorForParticles, int numberOfParticles );
  void     update_gBest_( int numberOfParticles );
  void     update_gBestWtHistoryReset_( int numberOfParticles, int cellIndex );
  void     updateVelocityEquation( int numberOfParticles, int sizeOfDomains );
  void     updatePositionEquation( int numberOfParticles, int sizeOfDomains );
  void     resetParticleHistory( int time_o, int time_i, int numberOfParticles, int sizeOfDomains, int cellIndex );

private:
  static
  int      numberOfParticles_;        // Number of particles
  static
  int      sizeOfDomains_;            // Domain size of PSO should be equal to totalNumOfVariableWeights in Neural Networks.
  static
  bool     useParticleHistoryReset_;  // A new feature for SRN
  static
  bool     is_gBest_updated_;         // A new feature for SRN
  static
  double   w_;                        // inertia of the previous velocity
  static
  double   c1_;                       // cognitive acceleration term
  static
  double   c2_;                       // social acceleration term
  static
  double   VMax_;                     // the maximum of the velocity V
  static
  double   XMin_;                     // the minimum of location X
  static
  double   XMax_;                     // the maximum of location X
  static
  double   V_initialValue_;

  int      epoch_;                    // This is not necessary, but...
  int      p_gBest_;                  // Index for the global best particle
  vint     bestParticles_;            // A new feature for history reset. Store all the best particles
  double   globalFitness_;            // Best fitness of all the particles
  double*  gBest_;                    // Global best
  vpsop    particles_;                // For best_ & fitness_, refer to class PsoParticle.
};

#endif

//==============================================================================
//                                  Comments
//==============================================================================

// PSO (Particle Swarm Optimization)
// RPSO (Recurrent Particle Swarm Optimization)
