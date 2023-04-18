//basijng on seeding ortho and rosie test 
#include "ActsExamples/TrackFinding/SeedingFTFAlgorithm.hpp"

#include "Acts/Seeding/Seed.hpp"
#include "Acts/Seeding/SeedFilter.hpp"
#include "ActsExamples/EventData/IndexSourceLink.hpp"
#include "ActsExamples/EventData/ProtoTrack.hpp"
#include "ActsExamples/EventData/SimSeed.hpp"
#include "ActsExamples/Framework/WhiteBoard.hpp"

#include <iostream>
#include <map>
#include <fstream>
#include <vector> 
#include <sstream>

using namespace std;

//constructor: 
ActsExamples::SeedingFTFAlgorithm::SeedingFTFAlgorithm(
    ActsExamples::SeedingFTFAlgorithm::Config cfg, 
    Acts::Logging::Level lvl) 
    : ActsExamples::IAlgorithm("SeedingAlgorithm", lvl), 
      m_cfg(std::move(cfg)) {
    //fill config struct

    //now interal units error on SeedFilter so using on all 3 

    m_cfg.seedFilterConfig = m_cfg.seedFilterConfig.toInternalUnits();
 
    //got error "SeedFInderOrthoConfig not in ACTS internal units": 
    m_cfg.seedFinderConfig =
    m_cfg.seedFinderConfig.toInternalUnits().calculateDerivedQuantities();
    //because this is ortho type uses function in this class 

    m_cfg.seedFinderOptions =
      m_cfg.seedFinderOptions.toInternalUnits().calculateDerivedQuantities(
          m_cfg.seedFinderConfig);


  for (const auto &spName : m_cfg.inputSpacePoints) {
    if (spName.empty()) {
      throw std::invalid_argument("Invalid space point input collection");
    }

    auto &handle = m_inputSpacePoints.emplace_back(
        std::make_unique<ReadDataHandle<SimSpacePointContainer>>(
            this,
            "InputSpacePoints#" + std::to_string(m_inputSpacePoints.size())));
    handle->initialize(spName);
  }


    //throw statements for differnet cases 
    m_outputSeeds.initialize(m_cfg.outputSeeds);


    //filling the memeber of class (not const) from member of const 
    //at the ned of both 
    m_cfg.seedFinderConfig.seedFilter =
      std::make_unique<Acts::SeedFilter<SimSpacePoint>>(
          Acts::SeedFilter<SimSpacePoint>(m_cfg.seedFilterConfig));
    m_seedFinder = Acts::SeedFinderFTF<SimSpacePoint>(m_cfg.seedFinderConfig);
      } //want to change 37 to SeedFinderFTF

//exectute: 

ActsExamples::ProcessCode ActsExamples::SeedingFTFAlgorithm::execute(
    const AlgorithmContext& ctx) const {

  //defining things need for seeds function, need to go through to understand 
  std::vector<const SimSpacePoint *> spacePoints;

//for loop filling space points, seeing if can do without 
  for (const auto &isp : m_inputSpacePoints) {
    for (const auto &spacePoint : (*isp)(ctx)) {
      spacePoints.push_back(&spacePoint);
    }
  } 

  Acts::SeedFinderFTF<SimSpacePoint> finder(m_cfg.seedFinderConfig); 
  //want to change 50 to SeedFinderFTF

  //need this function as create_coords is needed for seeds 
  std::function<std::pair<Acts::Vector3, Acts::Vector2>(
      const SimSpacePoint *sp)>
      create_coordinates = [](const SimSpacePoint *sp) {
        Acts::Vector3 position(sp->x(), sp->y(), sp->z());
        Acts::Vector2 variance(sp->varianceR(), sp->varianceZ());
        return std::make_pair(position, variance);
        
      };  


      //output of function needed for seed


 
  SimSeedContainer seeds = finder.createSeeds(m_cfg.seedFinderOptions,
                                              spacePoints, create_coordinates);

  //prototracks part, so far can just state, there is a loop over seeds  
  //since update the last steps have changed: 


  // ProtoTrackContainer protoTracks;                                

  // //debug statement
  

  m_outputSeeds(ctx, std::move(seeds));


  //think I should make the map here 
  map<std::pair<int, int>,int> ACTS_FTF;

  std::ifstream  data("ACTS_FTF_mapinput.csv");
  std::string line;
  std::vector<std::vector<std::string> > parsedCsv;
  while(std::getline(data,line))
  {
      std::stringstream lineStream(line);
      std::string cell;
      std::vector<std::string> parsedRow;
      while(std::getline(lineStream,cell,','))
      {
          parsedRow.push_back(cell); 
      }

      parsedCsv.push_back(parsedRow);
            
  }

  for (auto i : parsedCsv){
        
      int FTF = stoi(i[0]); 
      int ACTS_vol = stoi(i[1]); 
      int ACTS_lay = stoi(i[2]);
      ACTS_FTF.insert({{ACTS_vol,ACTS_lay},FTF}) ; 

  }


  //trying to print z and r 

  for (const auto &isp : m_inputSpacePoints) {
    for (const auto &spacePoint : (*isp)(ctx)) {

      float z = spacePoint.z() ; 
      float r = spacePoint.r() ; 
      int vol_id = spacePoint.vol_id() ;
      int lay_id = spacePoint.lay_id() ;  
      //std::cout << "Space point" << " z= " << z << " r=  " << r << " vol=  " << vol_id << "  lay= " << lay_id << "  " ; //cant print space point as no << operator 
      //use these vol and layer ids to look up FTF info 
      auto Find = ACTS_FTF.find(std::make_pair(vol_id,lay_id)) ; 
      int FTF_id = Find->second ;//find returns pointer to entry, need to ask for second part 
      std::cout << "Space point" <<  " vol=  " << vol_id << "  lay= " << lay_id << "  FTF_ID " << FTF_id "\n" ;
    }
  }




  return ActsExamples::ProcessCode::SUCCESS;
}

//defenitions of print functions, leaving for now 