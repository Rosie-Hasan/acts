//SeedFinderFTF.ipp
//basing on ortho seed finder 

#include "Acts/Geometry/Extent.hpp"
#include "Acts/Seeding/SeedFilter.hpp"
#include "Acts/Seeding/SeedFinder.hpp"
#include "Acts/Seeding/SeedFinderFTFConfig.hpp"
#include "Acts/Seeding/SeedFinderUtils.hpp"
#include "Acts/Utilities/BinningType.hpp"

#include<fstream>
#include<vector>

#include <cmath>
#include <functional>
#include <numeric>
#include <type_traits>

//core so in ACTS namespace

namespace Acts {

template <typename external_spacepoint_t>
SeedFinderFTF<external_spacepoint_t>::SeedFinderFTF(
    const SeedFinderFTFConfig<external_spacepoint_t> &config)
    : m_config(config) {
  
  //checks if internal units funciton used 
  // if (not config.isInInternalUnits) {
  //   throw std::runtime_error(
  //       "SeedFinderOrthogonalConfig not in ACTS internal units in "
  //       "SeedFinderOrthogonal");


  std::vector<TrigInDetSiLayer> input_vector ; 
  std::ifstream input_ifstream(m_config.fastrack_input_file) ; 
  FasTrackConnector input_fastrack(input_ifstream) ; 
  TrigFTF_GNN_Geometry<external_spacepoint_t> mGNNgeo(input_vector, &input_fastrack);
  m_storage = new TrigFTF_GNN_DataStorage(mGNNgeo);
 

}

template <typename external_spacepoint_t>
SeedFinderFTF<external_spacepoint_t>::~SeedFinderFTF(){
  delete m_storage ; 
  m_storage = nullptr ; 
}


//define loadspace points funciton 
 //when calling put input of vector<simspacepoints>, now can call space_point_t 
template <typename external_spacepoint_t>
void SeedFinderFTF<external_spacepoint_t>::loadSpacePoints(const std::vector<FTF_SP<external_spacepoint_t>> SP){

  for(auto& sp : SP) {
    bool is_Pixel = sp.SP->isPixel(); //FTF actual object then sim is pointer 
    if(!is_Pixel) continue;

    m_storage->addSpacePoint((sp), (m_config.m_useTrigSeedML > 0)); //add is a funciton FTFtype 

  }

  m_config.m_phiSliceWidth = 2*m_config.phiMax/m_config.m_nMaxPhiSlice;

  m_storage->sortByPhi();
  m_storage->generatePhiIndexing(1.5*m_config.m_phiSliceWidth);

}


//still to be developed 
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
