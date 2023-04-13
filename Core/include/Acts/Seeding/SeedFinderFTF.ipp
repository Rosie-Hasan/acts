//SeedFinderFTF.ipp
//accidently based on ipp, not sure if I'll neded 

//basing on ortho seed finder 

#include "Acts/Geometry/Extent.hpp"
#include "Acts/Seeding/SeedFilter.hpp"
#include "Acts/Seeding/SeedFinder.hpp"
#include "Acts/Seeding/SeedFinderFTFConfig.hpp"
#include "Acts/Seeding/SeedFinderUtils.hpp"
#include "Acts/Utilities/BinningType.hpp"

#include <cmath>
#include <functional>
#include <numeric>
#include <type_traits>

//core so in ACTS namespace

namespace Acts {

//valid tuple ortho range function RH and LH 
//valid tuple funtion 


//this is the definition of constructos 

template <typename external_spacepoint_t>
SeedFinderFTF<external_spacepoint_t>::SeedFinderFTF(
    const SeedFinderFTFConfig<external_spacepoint_t> &config)
    : m_config(config) {
  //schecks if internal units funciton used 
  // if (not config.isInInternalUnits) {
  //   throw std::runtime_error(
  //       "SeedFinderOrthogonalConfig not in ACTS internal units in "
  //       "SeedFinderOrthogonal");
}



//filter canditates function 
//fucntion processFromMiddleSP 

//create tree function- called in seeds 

//need create seeds function 

template <typename external_spacepoint_t>
template <typename input_container_t, typename output_container_t,
          typename callable_t>
void SeedFinderFTF<external_spacepoint_t>::createSeeds(
    const Acts::SeedFinderOptions &options,
    const input_container_t &spacePoints, output_container_t &out_cont,
    callable_t &&extract_coordinates) const {

} 

template <typename external_spacepoint_t>
template <typename input_container_t, typename callable_t>
std::vector<Seed<external_spacepoint_t>>
SeedFinderFTF<external_spacepoint_t>::createSeeds(
    const Acts::SeedFinderOptions &options,
    const input_container_t &spacePoints,
    callable_t &&extract_coordinates) const {
  std::vector<seed_t> r;
  createSeeds(options, spacePoints, r,
              std::forward<callable_t>(extract_coordinates));
  return r;
}





} //end of Acts namespace 