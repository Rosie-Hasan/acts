#include <string>
#include <vector>
#include <optional>

#include "ActsExamples/Framework/BareAlgorithm.hpp" 
#include "ActsExamples/TrackFinding/RosieTestFunc.hpp" 

namespace ActsExamples { 



ActsExamples::RosieTestFunc::RosieTestFunc(
    ActsExamples::RosieTestFunc::Config cfg, 
    Acts::Logging::Level lvl)
    : ActsExamples::BareAlgorithm("RosieTestFunc", lvl),
        m_cfg(std::move(cfg)) {
     m_cfg.RosieTest = m_cfg.RosieTest + m_cfg.Adding;
     std::cout << "testing if can print in function:  " << m_cfg.RosieTest ;  

  
} ; 



ActsExamples::ProcessCode ActsExamples::RosieTestFunc::execute(
    const AlgorithmContext& ctx) const {
  // construct the combined input container of space point pointers from all
  // configured input sources.
  // pre-compute the total size required so we only need to allocate once
//   size_t nSpacePoints = 0;
//   for (const auto& isp : m_cfg.inputSpacePoints) {
//     nSpacePoints += ctx.eventStore.get<SimSpacePointContainer>(isp).size();
  }

} 