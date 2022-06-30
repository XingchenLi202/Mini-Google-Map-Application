#include <map>
#include <vector>
#include <unordered_set>

#include <stdio.h>
#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"

// Step 1
// Autocomplete
TEST(TrojanMapStudentTest, Autocomplete) {
  TrojanMap x;
  x.CreateGraphFromCSVFile();
  auto a1 = x.Autocomplete("");
  std::vector<std::string> r1 = {};

  auto a2 = x.Autocomplete("ch");
  std::vector<std::string> r2 = {"ChickfilA", "Chipotle Mexican Grill"};

  auto a3 = x.Autocomplete("CH");
  std::vector<std::string> r3 = {"ChickfilA", "Chipotle Mexican Grill"};

  auto a4 = x.Autocomplete("tA");
  std::vector<std::string> r4 = {"Tap Two Blue","Target"};

  EXPECT_EQ(a1, r1);
  EXPECT_EQ(a2, r2);
  EXPECT_EQ(a3, r3);
  EXPECT_EQ(a4, r4);

}

//Step 2
//GetPosition
TEST(TrojanMapStudentTest, GetPosition) {
  TrojanMap x;
  x.CreateGraphFromCSVFile();

  auto p1 = x.GetPosition("ChickfilA");
  std::pair<double, double> r1 (34.0167334, -118.2825307);

  auto p2 = x.GetPosition("Ralphs");
  std::pair<double, double> r2 (34.0317653, -118.2908339);

  auto p3 = x.GetPosition("Target");
  std::pair<double, double> r3 (34.0257016, -118.2843512);

  EXPECT_EQ(p1, r1);
  EXPECT_EQ(p2, r2);
  EXPECT_EQ(p3, r3);
}

//Step 3_1
//CalculateShortestPath_Dijkstra
TEST(TrojanMapTest, CalculateShortestPath_Dijkstra) {
  TrojanMap x;
  x.CreateGraphFromCSVFile();

  auto p1 = x.CalculateShortestPath_Dijkstra("Ralphs", "ChickfilA");
  std::vector<std::string> r1 = {
      "2578244375", "5559640911", "6787470571", "6808093910", "6808093913", "6808093919", "6816831441",
      "6813405269", "6816193784", "6389467806", "6816193783", "123178876", "2613117895", "122719259",
      "2613117861", "6817230316", "3642819026", "6817230310", "7811699597", "5565967545", "123318572",
      "6813405206", "6813379482", "544672028", "21306059", "6813379476", "6818390140", "63068610", 
      "6818390143", "7434941012", "4015423966", "5690152766", "6813379440", "6813379466", "21306060",
      "6813379469", "6813379427", "123005255", "6807200376", "6807200380", "6813379451", "6813379463",
      "123327639", "6813379460", "4141790922", "4015423963", "1286136447", "1286136422", "4015423962",
      "6813379494", "63068643", "6813379496", "123241977", "4015372479", "4015372477", "1732243576",
      "6813379548", "4015372476", "4015372474", "4015372468", "4015372463", "6819179749", "1732243544",
      "6813405275", "348121996", "348121864", "6813405280", "1472141024", "6813411590", "216155217", 
      "6813411589", "1837212103", "1837212101", "6820935911", "4547476733"};
  auto p2 = x.CalculateShortestPath_Dijkstra("", "ChickfilA");
  std::vector<std::string> r2 = {};
  auto p3 = x.CalculateShortestPath_Dijkstra("Ralphs", "");
  std::vector<std::string> r3 = {};
  auto p4 = x.CalculateShortestPath_Dijkstra("Target", "Popeyes Louisiana Kitchen");
  std::vector<std::string> r4 = {
      "5237417650", "6813379479", "5237381975", "4399698012", "4399698013", "4399698011", "4399698010", 
      "123044712", "4399698009", "4399698008", "123005253", "6813379513", "6813379517", "6813379521", 
      "123327627", "4399697999", "6813565290", "122719210", "6813379407", "2613117879", "6813379406", 
      "6807905595", "6787803635", "2613117867", "4835551110", "6813565296", "122719205", "6813565294", "4835551232", 
      "4835551104", "4012842272", "4835551103", "123178841", "6813565313", "122814435", "6813565311", "4835551228", 
      "6813513565", "4835551090", "4835551081", "6813513564", "20400292", "5556117120", "5556117115", "4835551064", 
      "4012842277", "6813565326", "123241961", "6813565322", "4835551070", "5695236164"};
  EXPECT_EQ(p1, r1);
  EXPECT_EQ(p2, r2);
  EXPECT_EQ(p3, r3);
  EXPECT_EQ(p4, r4);
}

// Step 3_2
// CalculateShortestPath_Bellman_Ford
TEST(TrojanMapTest, CalculateShortestPath_Bellman_Ford) {
  TrojanMap x;
  x.CreateGraphFromCSVFile();
  auto p1 = x.CalculateShortestPath_Bellman_Ford("Ralphs", "ChickfilA");
  std::vector<std::string> r1 = {
      "2578244375", "5559640911", "6787470571", "6808093910", "6808093913", "6808093919", "6816831441",
      "6813405269", "6816193784", "6389467806", "6816193783", "123178876", "2613117895", "122719259",
      "2613117861", "6817230316", "3642819026", "6817230310", "7811699597", "5565967545", "123318572",
      "6813405206", "6813379482", "544672028", "21306059", "6813379476", "6818390140", "63068610", 
      "6818390143", "7434941012", "4015423966", "5690152766", "6813379440", "6813379466", "21306060",
      "6813379469", "6813379427", "123005255", "6807200376", "6807200380", "6813379451", "6813379463",
      "123327639", "6813379460", "4141790922", "4015423963", "1286136447", "1286136422", "4015423962",
      "6813379494", "63068643", "6813379496", "123241977", "4015372479", "4015372477", "1732243576",
      "6813379548", "4015372476", "4015372474", "4015372468", "4015372463", "6819179749", "1732243544",
      "6813405275", "348121996", "348121864", "6813405280", "1472141024", "6813411590", "216155217", 
      "6813411589", "1837212103", "1837212101", "6820935911", "4547476733"};
  auto p2 = x.CalculateShortestPath_Bellman_Ford("", "ChickfilA");
  std::vector<std::string> r2 = {};
  auto p3 = x.CalculateShortestPath_Bellman_Ford("Ralphs", "");
  std::vector<std::string> r3 = {};
  auto p4 = x.CalculateShortestPath_Bellman_Ford("Target", "Popeyes Louisiana Kitchen");
  std::vector<std::string> r4 = {
      "5237417650", "6813379479", "5237381975", "4399698012", "4399698013", "4399698011", "4399698010", 
      "123044712", "4399698009", "4399698008", "123005253", "6813379513", "6813379517", "6813379521", 
      "123327627", "4399697999", "6813565290", "122719210", "6813379407", "2613117879", "6813379406", 
      "6807905595", "6787803635", "2613117867", "4835551110", "6813565296", "122719205", "6813565294", "4835551232", 
      "4835551104", "4012842272", "4835551103", "123178841", "6813565313", "122814435", "6813565311", "4835551228", 
      "6813513565", "4835551090", "4835551081", "6813513564", "20400292", "5556117120", "5556117115", "4835551064", 
      "4012842277", "6813565326", "123241961", "6813565322", "4835551070", "5695236164"};
  EXPECT_EQ(p1, r1);
  EXPECT_EQ(p2, r2);
  EXPECT_EQ(p3, r3);
  EXPECT_EQ(p4, r4);
}

//Step 4_1
//TravellingTrojan
TEST(TrojanMapTest, TravellingTrojan) {
  TrojanMap x;
  x.CreateGraphFromCSVFile();
  std::vector<std::string> input;
  std::pair<double, std::vector<std::vector<std::string>>> emp;
  auto r = x.TravellingTrojan(input);
  EXPECT_EQ(r, emp);   
}

//Step 4_2
//1 TravellingTrojan_2opt
TEST(TrojanMapTest, TravellingTrojan_2opt) {
  TrojanMap x;
  x.CreateGraphFromCSVFile();
  std::vector<std::string> input;
  std::pair<double, std::vector<std::vector<std::string>>> emp;
  auto r = x.TravellingTrojan_2opt(input);
  EXPECT_EQ(r, emp);  
}
//2 TravellingTrojan_2opt
TEST(TrojanMapTest, TSP) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> input{"1873056015", "6905329551", "213332060", "1931345270"}; // Input location ids 
  auto result = m.TravellingTrojan_2opt(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"1873056015", "213332060", "1931345270", "6905329551", "1873056015"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) 
    flag = true;
  
  EXPECT_EQ(flag, true);
}
//2 TravellingTrojan_2opt
TEST(TrojanMapTest, TSP2) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> input{"1862312636", "7424270441", "67666219", "4015405548", "4015203110", "6807439002"}; // Input location ids 
  auto result = m.TravellingTrojan_2opt(input);
  std::cout << "My path length: " << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"1862312636", "4015405548", "4015203110", "6807439002", "7424270441", "67666219", "1862312636"}; // Expected order
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the groundtruth path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) // counterclockwise
    flag = true;
  EXPECT_EQ(flag, true);
}


