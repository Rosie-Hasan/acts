//practicing making a  map 

#include <iostream>
#include <map>
#include <fstream>
#include <vector> 
#include <sstream>

using namespace std; 


int main() {

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

    for (auto t : ACTS_FTF)
        std::cout << t.first.first << " " 
                << t.first.second << " " 
                << t.second << "\n";
        

    std::cout << ACTS_FTF.size(); 

    auto Find = ACTS_FTF.find(make_pair(19,12));
    //find returns a pointer to the element 
    int FTF_id = Find->second ;
    std::cout << FTF_id ; 
}
//to run this: g++ unordered_map.cpp -std=c++11 then ./a.out 