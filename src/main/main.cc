#include <iostream>
#include <map>
#include <vector>
#include "src/lib/trojanmap.h"
using namespace std;

int main() {
  TrojanMap m;
  m.CreateGraphFromCSVFile();

  //std::string startId = m.GetID("Ralphs");
  //cout << startId<<endl;

  // auto a3 = m.Autocomplete("CH");
  // for(int i = 0; i < a3.size();i++){
  //   cout << a3[i]<<endl;
  // }//std::vector<std::string> r3 = {"ChickfilA", "Chipotle Mexican Grill"};

  // auto names = m.CalculateShortestPath_Dijkstra("Ralphs", "ChickfilA");
  // for(int i = 0; i < names.size();i++){
  //   cout << names[i]<<endl;
  // }

  //auto p1 = m.CalculateShortestPath_Bellman_Ford("Ralphs", "ChickfilA");
  // auto p4 = m.CalculateShortestPath_Bellman_Ford("Target", "Popeyes Louisiana Kitchen");


  // TrojanMap m;
  // m.CreateGraphFromCSVFile();

  // // std::vector<std::string> input{"1862312636"};
  // // auto result = m.TravellingTrojan(input);
  // // std::cout << "My path length: " << result.first << "miles" << std::endl; // Print the result path lengths

  // std::vector<std::string> input{"1862312636", "7424270441", "67666219", "4015405548", "4015203110", "6807439002"}; // Input location ids 
  // auto result = m.TravellingTrojan_2opt(input);
  // std::cout << "My path length: " << result.first << "miles" << std::endl; // Print the result path lengths
  // std::vector<std::string> gt{"1862312636", "4015405548", "4015203110", "6807439002", "7424270441", "67666219", "1862312636"}; // Expected order
  // std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the groundtruth path lengths
  // bool flag = false;
  // if (gt == result.second[result.second.size()-1]) // clockwise
  //   flag = true;
  // std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  // if (gt == result.second[result.second.size()-1]) // counterclockwise
  //   flag = true;

  // TrojanMap m;
  // m.CreateGraphFromCSVFile();
  // std::vector<std::string> input{"123120189", "4011837229", "4011837224", "2514542032", "2514541020", "1931345270", "4015477529", "214470792", "63068532", "6807909279"}; // Input location ids 
  // auto result = m.TravellingTrojan_2opt(input);
  // std::cout << "My path length: " <<result.first << "miles" << std::endl; // Print the result path lengths
  // std::vector<std::string> gt{"123120189", "1931345270", "4011837224", "4011837229", "2514542032", "2514541020", "6807909279", "63068532", "214470792", "4015477529", "123120189"}; // Expected order
  // std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the groundtruth path lengths
  // bool flag = false;
  // if (gt == result.second[result.second.size()-1]) // clockwise
  //   flag = true;
  // std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  // if (gt == result.second[result.second.size()-1]) // counterclockwise
  //   flag = true;
  // for(int i=0;i<result.second.size();i++){
  //   for(int j=0;j<result.second[i].size();j++){
  //     cout<<result.second[i][j]<<"   ";
  //   }
  //   cout<<endl;
  // }
  // cout<<endl;


  // TrojanMap m;
  // m.CreateGraphFromCSVFile();
  // auto result = m.FindKClosestPoints("Ralphs",10);
  // //cout<<endl;
  // for(int j=0;j<result[j].size();j++){
  //   cout<<result[j]<<endl;
  // }
  // std::vector<std::string> gt{
  // "3724125231", "358791507", "7158047272", "358828789", "358794109",
  // "5757277355", "7204975815", "6510335101", "6807374558", "6510335102"};

  
  m.PrintMenu();
  return 0;
}