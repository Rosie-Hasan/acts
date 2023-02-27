#include <string>
#include <vector>
#include <optional>

#include "ActsExamples/Framework/BareAlgorithm.hpp" 


namespace ActsExamples {

class RosieTestFunc final : public BareAlgorithm {
 public:
  struct Config {
    std::string RosieTest; 
    std::string Adding; 
    //std::string RosieAdd(std::string input); 
    //std::string RosieAdd(std::string input);// (std::string input) {return input + adding ;} ;
  };
    // std::string RosieAdd(std::string input); 
//   / Construct the  algorithm.
  /// @param cfg is the algorithm configuration
  /// @param lvl is the logging level

  RosieTestFunc(Config cfg, Acts::Logging::Level lvl);
  //RosieTestFunc(std::string RT, Acts::Logging::Level lvl) ; 

 

    /// Run the seeding algorithm.
  ///
  /// @param txt is the algorithm context with event information
  /// @return a process code indication success or failure
  ProcessCode execute(const AlgorithmContext& ctx) const override;

  /// Const access to the config
  const Config& config() const { return m_cfg; }


 private:
  Config m_cfg;

}; 
} 
