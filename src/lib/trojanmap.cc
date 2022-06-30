#include "trojanmap.h"
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <float.h>

#include <algorithm>
#include <fstream>
#include <locale>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <sstream>
#include <string>
#include <utility>
// #include <bits/stdc++.h>
#include <cmath>
#include <iostream>
#include <cctype>
#include <unordered_set>
#include <stack>
#include <chrono>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"

using namespace std;

//-----------------------------------------------------
// TODO (Students): You do not and should not change the following functions:
//-----------------------------------------------------

/**
 * PrintMenu: Create the menu
 * 
 */
void TrojanMap::PrintMenu() {

  std::string menu =
      "**************************************************************\n"
      "* Select the function you want to execute.                    \n"
      "* 1. Autocomplete                                             \n"
      "* 2. Find the position                                        \n"
      "* 3. CalculateShortestPath                                    \n"
      "* 4. Travelling salesman problem                              \n"
      "* 5. Cycle Detection                                          \n"
      "* 6. Topological Sort                                         \n"
      "* 7. Find K Closest Points                                    \n"
      "* 8. Exit                                                     \n"
      "**************************************************************\n";
  std::cout << menu << std::endl;
  std::string input;
  getline(std::cin, input);
  char number = input[0];
  switch (number)
  {
  case '1':
  {
    menu =
        "**************************************************************\n"
        "* 1. Autocomplete                                             \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input a partial location:";
    std::cout << menu;
    getline(std::cin, input);
    auto start = std::chrono::high_resolution_clock::now();
    auto results = Autocomplete(input);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.size() != 0) {
      for (auto x : results) std::cout << x << std::endl;
    } else {
      std::cout << "No matched locations." << std::endl;
    }
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '2':
  {
    menu =
        "**************************************************************\n"
        "* 2. Find the position                                        \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input a location:";
    std::cout << menu;
    getline(std::cin, input);
    auto start = std::chrono::high_resolution_clock::now();
    auto results = GetPosition(input);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.first != -1) {
      std::cout << "Latitude: " << results.first
                << " Longitude: " << results.second << std::endl;
      PlotPoint(results.first, results.second);
    } else {
      std::cout << "No matched locations." << std::endl;
    }
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '3':
  {
    menu =
        "**************************************************************\n"
        "* 3. CalculateShortestPath                                    \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input the start location:";
    std::cout << menu;
    std::string input1;
    getline(std::cin, input1);
    menu = "Please input the destination:";
    std::cout << menu;
    std::string input2;
    getline(std::cin, input2);
    auto start = std::chrono::high_resolution_clock::now();
    auto results = CalculateShortestPath_Bellman_Ford(input1, input2);//
    // auto results_BF =CalculateShortestPath_Dijkstra(input1, input2);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.size() != 0) {
      for (auto x : results) std::cout << x << std::endl;
      std::cout << "The distance of the path is:" << CalculatePathLength(results) << " miles" << std::endl;
      // std::cout<< std::endl;
      // for (auto y : results_BF) std::cout << y << std::endl;
      // std::cout << "The distance of the path is:" << CalculatePathLength(results_BF) << " miles" << std::endl;
      PlotPath(results);
    } else {
      std::cout << "No route from the start point to the destination."
                << std::endl;
    }
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '4':
  {
    menu =
        "**************************************************************\n"
        "* 4. Traveling salesman problem                              \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "In this task, we will select N random points on the map and you need to find the path to travel these points and back to the start point.";
    std::cout << menu << std::endl << std::endl;
    menu = "Please input the number of the places:";
    std::cout << menu;
    getline(std::cin, input);
    int num = std::stoi(input);
    std::vector<std::string> keys;
    for (auto x : data) {
      keys.push_back(x.first);
    }
    std::vector<std::string> locations;
    srand(time(NULL));
    for (int i = 0; i < num; i++)
      locations.push_back(keys[rand() % keys.size()]);
    PlotPoints(locations);
    std::cout << "Calculating ..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    auto results = TravellingTrojan_2opt(locations);//TravellingTrojan(locations);
    //auto results2 = TravellingTrojan_2opt(locations);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    CreateAnimation(results.second);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.second.size() != 0) {
      for (auto x : results.second[results.second.size()-1]) std::cout << x << std::endl;
      menu = "**************************************************************\n";
      std::cout << menu;
      std::cout << "The distance of the path is:" << results.first << " miles" << std::endl;
      //std::cout << "The distance of the path2 is:" << results2.first << " miles" << std::endl;
      PlotPath(results.second[results.second.size()-1]);
    } else {
      std::cout << "The size of the path is 0" << std::endl;
    }
    menu = "**************************************************************\n"
           "You could find your animation at src/lib/output.avi.          \n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '5':
  {
    menu =
        "**************************************************************\n"
        "* 5. Cycle Detection                                          \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input the left bound longitude(between -118.299 and -118.264):";
    std::cout << menu;
    getline(std::cin, input);
    std::vector<double> square;
    square.push_back(atof(input.c_str()));

    menu = "Please input the right bound longitude(between -118.299 and -118.264):";
    std::cout << menu;
    getline(std::cin, input);
    square.push_back(atof(input.c_str()));

    menu = "Please input the upper bound latitude(between 34.011 and 34.032):";
    std::cout << menu;
    getline(std::cin, input);
    square.push_back(atof(input.c_str()));

    menu = "Please input the lower bound latitude(between 34.011 and 34.032):";
    std::cout << menu;
    getline(std::cin, input);
    square.push_back(atof(input.c_str()));

    auto start = std::chrono::high_resolution_clock::now();
    auto results = CycleDetection(square);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results == true)
      std::cout << "there exists cycle in the subgraph " << std::endl;
    else
      std::cout << "there exist no cycle in the subgraph " << std::endl;
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '6':
  {
    menu =
        "**************************************************************\n"
        "* 6. Topological Sort                                         \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input the locations filename:";
    std::cout << menu;
    std::string locations_filename;
    getline(std::cin, locations_filename);
    menu = "Please input the dependencies filename:";
    std::cout << menu;
    std::string dependencies_filename;
    getline(std::cin, dependencies_filename);
    
    // Read location names from CSV file
    std::vector<std::string> location_names;
    if (locations_filename == "") 
      location_names = {"Cardinal Gardens", "Coffee Bean1","CVS"};
    else
      location_names = ReadLocationsFromCSVFile(locations_filename);
    
    // Read dependencies from CSV file
    std::vector<std::vector<std::string>> dependencies;
    if (dependencies_filename == "")
      dependencies = {{"Coffee Bean1","Cardinal Gardens"}, {"CVS","Cardinal Gardens"}, {"CVS","Coffee Bean1"}};
    else
      dependencies = ReadDependenciesFromCSVFile(dependencies_filename);

    // std::vector<std::string> location_names = {"Cardinal Gardens", "Coffee Bean1","CVS"};
    // std::vector<std::vector<std::string>> dependencies = {{"Coffee Bean1","Cardinal Gardens"}, {"CVS","Cardinal Gardens"}, {"CVS","Coffee Bean1"}};
    auto start = std::chrono::high_resolution_clock::now();
    auto result = DeliveringTrojan(location_names, dependencies);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************";
    std::cout << menu << std::endl;
    std::cout << "Topological Sorting Results:" << std::endl;
    for (auto x : result) std::cout << x << std::endl;
    std::vector<std::string> node_ids;
    for (auto x: result) {
      std::string id = GetID(x);
      node_ids.push_back(id);
    }
    PlotPointsOrder(node_ids);
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
    case '7':
  {
    menu =
        "**************************************************************\n"
        "* 7. Find K Closest Points                                    \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    
    menu = "Please input the locations:";
    std::cout << menu;
    std::string origin;
    getline(std::cin, origin);
    menu = "Please input k:";
    std::cout << menu;
    getline(std::cin, input);
    int k = std::stoi(input);
    
    auto start = std::chrono::high_resolution_clock::now();
    // auto result = FindKClosestPoints(origin, k);
    auto result = FindKClosestPoints_Sort(origin, k);
    // auto result = FindKClosestPoints_MaxHeap(origin, k);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************";
    std::cout << menu << std::endl;
    std::cout << "Find K Closest Points Results:" << std::endl;
    int cnt = 1;
    for (auto x : result) { 
      std::cout << cnt << " " << data[x].name << std::endl;
      cnt++;
    }
    PlotPointsLabel(result, GetID(origin));
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '8':
    break;
  default:
  {
    std::cout << "Please select 1 - 8." << std::endl;
    PrintMenu();
    break;
  }
  }
}


/**
 * CreateGraphFromCSVFile: Read the map data from the csv file
 * 
 */
void TrojanMap::CreateGraphFromCSVFile() {
  std::fstream fin;
  fin.open("src/lib/map.csv", std::ios::in);
  std::string line, word;

  getline(fin, line);
  while (getline(fin, line)) {
    std::stringstream s(line);

    Node n;
    int count = 0;
    while (getline(s, word, ',')) {
      word.erase(std::remove(word.begin(), word.end(), '\''), word.end());
      word.erase(std::remove(word.begin(), word.end(), '"'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '['), word.end());
      word.erase(std::remove(word.begin(), word.end(), ']'), word.end());
      if (count == 0)
        n.id = word;
      else if (count == 1)
        n.lat = stod(word);
      else if (count == 2)
        n.lon = stod(word);
      else if (count == 3)
        n.name = word;
      else {
        word.erase(std::remove(word.begin(), word.end(), ' '), word.end());
        n.neighbors.push_back(word);//get the neighbors of a node
      }
      count++;
    }
    data[n.id] = n;
  }
  fin.close();
}

/**
 * PlotPoint: Given a location id, plot the point on the map
 * 
 * @param  {std::string} id : location id
 */
void TrojanMap::PlotPoint(std::string id) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto result = GetPlotLocation(data[id].lat, data[id].lon);
  cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}
/**
 * PlotPoint: Given a lat and a lon, plot the point on the map
 * 
 * @param  {double} lat : latitude
 * @param  {double} lon : longitude
 */
void TrojanMap::PlotPoint(double lat, double lon) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto result = GetPlotLocation(lat, lon);
  cv::circle(img, cv::Point(int(result.first), int(result.second)), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  cv::startWindowThread();
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPath: Given a vector of location ids draws the path (connects the points)
 * 
 * @param  {std::vector<std::string>} location_ids : path
 */
void TrojanMap::PlotPath(std::vector<std::string> &location_ids) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto start = GetPlotLocation(data[location_ids[0]].lat, data[location_ids[0]].lon);
  cv::circle(img, cv::Point(int(start.first), int(start.second)), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  for (auto i = 1; i < location_ids.size(); i++) {
    auto start = GetPlotLocation(data[location_ids[i - 1]].lat, data[location_ids[i - 1]].lon);
    auto end = GetPlotLocation(data[location_ids[i]].lat, data[location_ids[i]].lon);
    cv::circle(img, cv::Point(int(end.first), int(end.second)), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
    cv::line(img, cv::Point(int(start.first), int(start.second)),
             cv::Point(int(end.first), int(end.second)), cv::Scalar(0, 255, 0),
             LINE_WIDTH);
  }
  cv::startWindowThread();
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPoints: Given a vector of location ids draws the points on the map (no path).
 * 
 * @param  {std::vector<std::string>} location_ids : points
 */
void TrojanMap::PlotPoints(std::vector<std::string> &location_ids) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  for (auto x : location_ids) {
    auto result = GetPlotLocation(data[x].lat, data[x].lon);
    cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPoints: Given a vector of location ids draws the points on the map (no path).
 * 
 * @param  {std::vector<std::string>} location_ids : points inside square
 * @param  {std::vector<double>} square : boundary
 */
void TrojanMap::PlotPointsandEdges(std::vector<std::string> &location_ids, std::vector<double> &square) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto upperleft = GetPlotLocation(square[2], square[0]);
  auto lowerright = GetPlotLocation(square[3], square[1]);
  cv::Point pt1(int(upperleft.first), int(upperleft.second));
  cv::Point pt2(int(lowerright.first), int(lowerright.second));
  cv::rectangle(img, pt2, pt1, cv::Scalar(0, 0, 255));
  for (auto x : location_ids) {
    auto result = GetPlotLocation(data[x].lat, data[x].lon);
    cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
    for(auto y : data[x].neighbors) {
      auto start = GetPlotLocation(data[x].lat, data[x].lon);
      auto end = GetPlotLocation(data[y].lat, data[y].lon);
      cv::line(img, cv::Point(int(start.first), int(start.second)),
              cv::Point(int(end.first), int(end.second)), cv::Scalar(0, 255, 0),
              LINE_WIDTH);
    }
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPointsOrder: Given a vector of location ids draws the points on the map (no path).
 * 
 * @param  {std::vector<std::string>} location_ids : points
 */
void TrojanMap::PlotPointsOrder(std::vector<std::string> &location_ids) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  for (auto x : location_ids) {
    auto result = GetPlotLocation(data[x].lat, data[x].lon);
    cv::putText(img, data[x].name, cv::Point(result.first, result.second), cv::FONT_HERSHEY_DUPLEX, 1.0, CV_RGB(255, 0, 0), 2);
  }
  // Plot dots and lines
  auto start = GetPlotLocation(data[location_ids[0]].lat, data[location_ids[0]].lon);
  cv::circle(img, cv::Point(int(start.first), int(start.second)), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  for (auto i = 1; i < location_ids.size(); i++) {
    auto start = GetPlotLocation(data[location_ids[i - 1]].lat, data[location_ids[i - 1]].lon);
    auto end = GetPlotLocation(data[location_ids[i]].lat, data[location_ids[i]].lon);
    cv::circle(img, cv::Point(int(end.first), int(end.second)), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
    cv::arrowedLine(img, cv::Point(int(start.first), int(start.second)),
             cv::Point(int(end.first), int(end.second)), cv::Scalar(0, 255, 0),
             LINE_WIDTH);
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPoints: Given a vector of location ids draws the points on the map (no path).
 * 
 * @param  {std::vector<std::string>} location_ids : points
 */
void TrojanMap::PlotPointsLabel(std::vector<std::string> &location_ids, std::string origin) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  int cnt = 1;
  auto result = GetPlotLocation(data[origin].lat, data[origin].lon);
  cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
               cv::Scalar(0, 255, 0), cv::FILLED);
  for (auto x : location_ids) {
    auto result = GetPlotLocation(data[x].lat, data[x].lon);
    cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
    cv::putText(img, std::to_string(cnt), cv::Point(result.first, result.second), cv::FONT_HERSHEY_DUPLEX, 1.0, CV_RGB(255, 0, 0), 2);
    cnt++;
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * CreateAnimation: Create the videos of the progress to get the path
 * 
 * @param  {std::vector<std::vector<std::string>>} path_progress : the progress to get the path
 */
void TrojanMap::CreateAnimation(std::vector<std::vector<std::string>> path_progress){
  cv::VideoWriter video("src/lib/output.avi", cv::VideoWriter::fourcc('M','J','P','G'), 10, cv::Size(1248,992));
  for(auto location_ids: path_progress) {
    std::string image_path = cv::samples::findFile("src/lib/input.jpg");
    cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
    auto start = GetPlotLocation(data[location_ids[0]].lat, data[location_ids[0]].lon);
    cv::circle(img, cv::Point(int(start.first), int(start.second)), DOT_SIZE,
              cv::Scalar(0, 0, 255), cv::FILLED);
    for (auto i = 1; i < location_ids.size(); i++) {
      auto start = GetPlotLocation(data[location_ids[i - 1]].lat, data[location_ids[i - 1]].lon);
      auto end = GetPlotLocation(data[location_ids[i]].lat, data[location_ids[i]].lon);
      cv::circle(img, cv::Point(int(end.first), int(end.second)), DOT_SIZE,
                cv::Scalar(0, 0, 255), cv::FILLED);
      cv::line(img, cv::Point(int(start.first), int(start.second)),
              cv::Point(int(end.first), int(end.second)), cv::Scalar(0, 255, 0),
              LINE_WIDTH);
    }
    video.write(img);
    cv::imshow("TrojanMap", img);
    cv::waitKey(1);
  }
	video.release();
}
/**
 * GetPlotLocation: Transform the location to the position on the map
 * 
 * @param  {double} lat         : latitude 
 * @param  {double} lon         : longitude
 * @return {std::pair<double, double>}  : position on the map
 */
std::pair<double, double> TrojanMap::GetPlotLocation(double lat, double lon) {
  std::pair<double, double> bottomLeft(34.01001, -118.30000);
  std::pair<double, double> upperRight(34.03302, -118.26502);
  double h = upperRight.first - bottomLeft.first;
  double w = upperRight.second - bottomLeft.second;
  std::pair<double, double> result((lon - bottomLeft.second) / w * 1248,
                                   (1 - (lat - bottomLeft.first) / h) * 992);
  return result;
}

//-----------------------------------------------------
// TODO: Student should implement the following:
//-----------------------------------------------------
/**
 * GetLat: Get the latitude of a Node given its id.
 * 
 * @param  {std::string} id : location id
 * @return {double}         : latitude
 */
double TrojanMap::GetLat(std::string id) {
  if(id.length() == 0 || data.find(id) == data.end()){//data is an unordered_map
    return -1;
  }
  return data.find(id)->second.lat;
}


/**
 * GetLon: Get the longitude of a Node given its id. 
 * 
 * @param  {std::string} id : location id
 * @return {double}         : longitude
 */
double TrojanMap::GetLon(std::string id) { 
  if(id.length() == 0 || data.find(id) == data.end()){//data is an unordered_map
    return -1;
  }
  return data.find(id)->second.lon;
}

/**
 * GetName: Get the name of a Node given its id.
 * 
 * @param  {std::string} id : location id
 * @return {std::string}    : name
 */
std::string TrojanMap::GetName(std::string id) { 
  if (id.length() == 0 || data.find(id) == data.end()) {
    return "";
  }
  return data.find(id)->second.name; 
}

/**
 * GetNeighborIDs: Get the neighbor ids of a Node.
 * 
 * @param  {std::string} id            : location id
 * @return {std::vector<std::string>}  : neighbor ids
 */
std::vector<std::string> TrojanMap::GetNeighborIDs(std::string id) {
  std::vector<std::string> ids;//neighbor list (using neighbors)
  if(id.length() == 0 || data.find(id) == data.end()) {
    return ids;
  }
  Node cur = data[id];//current new node is the data in the data vector with this id.
  for (std::string nextId : cur.neighbors) {// List of the ids of all neighbor points.
    ids.push_back(nextId);
  }
  return ids;
}

/**
 * CalculateDistance: Get the distance between 2 nodes. 
 * 
 * @param  {std::string} a  : a_id
 * @param  {std::string} b  : b_id
 * @return {double}  : distance in mile
 */
double TrojanMap::CalculateDistance(const std::string &a_id, const std::string &b_id) {
  // Do not change this function
  // TODO: Use Haversine Formula:
  // dlon = lon2 - lon1;
  // dlat = lat2 - lat1;
  // a = (sin(dlat / 2)) ^ 2 + cos(lat1) * cos(lat2) * (sin(dlon / 2)) ^ 2;
  // c = 2 * arcsin(min(1, sqrt(a)));
  // distances = 3961 * c;

  // where 3961 is the approximate radius of the earth at the latitude of
  // Washington, D.C., in miles
  Node a = data[a_id];
  Node b = data[b_id];
  double dlon = (b.lon - a.lon) * M_PI / 180.0;
  double dlat = (b.lat - a.lat) * M_PI / 180.0;
  double p = pow(sin(dlat / 2),2.0) + cos(a.lat * M_PI / 180.0) * cos(b.lat * M_PI / 180.0) * pow(sin(dlon / 2),2.0);
  double c = 2 * asin(std::min(1.0,sqrt(p)));
  return c * 3961;
}

/**
 * CalculatePathLength: Calculates the total path length for the locations inside the vector.
 * 
 * @param  {std::vector<std::string>} path : path
 * @return {double}                        : path length
 */
double TrojanMap::CalculatePathLength(const std::vector<std::string> &path) {
  // Do not change this function
  double sum = 0;
  for (int i = 0;i < path.size()-1; i++) {
    sum += CalculateDistance(path[i], path[i+1]);
  }
  return sum;
}

/**
 * Autocomplete: Given a parital name return all the possible locations with
 * partial name as the prefix.
 *
 * @param  {std::string} name          : partial name
 * @return {std::vector<std::string>}  : a vector of full names
 */
std::vector<std::string> TrojanMap::Autocomplete(std::string name){
  std::vector<std::string> results;

  if(name.length()==0){
    return results;
  }
  std::transform(name.begin(),name.end(),name.begin(),::tolower);//transform the name into lowercase 

  for(auto iter = data.begin(); iter != data.end(); iter++){
    std::string nodeName = iter->second.name;//the name of current node
    if(nodeName.length() >= name.length()){//iterate the node which has longer name than the input
      std::string t = nodeName;
      std::transform(t.begin(),t.end(),t.begin(),::tolower);//transform these longer name into lowercase
      if(t.substr(0,name.length()) == name){//if the first several characters are the substring of data's name
        results.push_back(nodeName);//push it into the result list
      }
    }
  }
  return results;
}

/**
 * GetPosition: Given a location name, return the position.
 *
 * @param  {std::string} name          : location name
 * @return {std::pair<double,double>}  : (lat, lon)
 */
std::pair<double, double> TrojanMap::GetPosition(std::string name) {
  std::pair<double, double> results(-1, -1);

  for(auto iter = data.begin();iter != data.end();iter++){//iterate all name
    std::string curName = iter->second.name;
    if(curName.compare(name) == 0){// compare the current name to every name in the list
      results.first = iter->second.lat;//lat
      results.second = iter->second.lon;//lon
    }
  }
  return results;
}



/**
 * GetID: Given a location name, return the id. 
 * If the node does not exist, return an empty string. 
 *
 * @param  {std::string} name          : location name
 * @return {std::string}  : id    //?int
 */
std::string TrojanMap::GetID(std::string name) {
  std::string res = "";
  
  Node curNode;

  for(auto iter = data.begin();iter!=data.end();iter++){
    
    if(iter->second.name == name){
      res = iter->second.id;
      return res;
    }
  }
  return res;
}



/**
 * CalculateShortestPath_Dijkstra: Given 2 locations, return the shortest path which is a
 * list of id.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Dijkstra(
    std::string location1_name, std::string location2_name) {
  std::vector<std::string> path;//result (list of id)
  //Specific cases
  //1.if the inputs is empty
  if (location1_name.length() == 0 || location2_name.length() == 0) {
    return path;
  }
  //2.if the inputs is invalid
  std::string startId = GetID(location1_name);
  std::string goalId = GetID(location2_name); 
  if(data.find(startId)==data.end() || data.find(goalId)==data.end()){
    return path;
  }
  //3.if the start or goal have no neighbor.
  if(GetNeighborIDs(startId).size()==0 || GetNeighborIDs(goalId).size() == 0){
    return path;
  }

  std::map<std::string, bool> visited;//visited node(id)
  std::map<std::string, double> mindis;//record current min distance from start node(id,distance)
  //initialize the distince = Max
  for (auto it : data){
    mindis[it.first] = DBL_MAX;
    visited[it.first] = false;
  }

  visited[startId] = true;//visited node list only has startId
  mindis[startId] = 0;//distance from start to start is 0
  std::map<std::string, std::string> pre;//record the provious node (curId,prevId)
  //updata the distance of start case
  for(auto neighborId : GetNeighborIDs(startId)){//get the distance from start to its neighbors
    mindis[neighborId] = CalculateDistance(startId, neighborId);
    pre[neighborId] = startId;
  }
  
  //updata the distance of the rest case
  for(auto it :mindis){
    string minid = findMinIDButNotInVisited(mindis,visited);
    if(minid == goalId){
      break;
    }   

    //update distances of minId's neighbors
    for(auto neighborId : GetNeighborIDs(minid)){ //iterate the neighbors of the minId
      double d = CalculateDistance(minid,neighborId);//calculate the dis between minId and its neighbors
      if(visited[neighborId]!=true  &&  mindis[minid]+d < mindis[neighborId]){//ensure the node n is not in visited list
        mindis[neighborId] = mindis[minid]+d;//update the mindis of minId's neighbors
        pre[neighborId] = minid;//(minId's neighbors,  minId)
      }
    } 
  }
  //there is no ways to the goal
  if(mindis[goalId] == DBL_MAX){
    return path;
  }
  path.push_back(goalId);
  //generate the final path using the prev map
  string temp = pre[goalId];
  while(temp != startId){
    path.insert(path.begin(),temp);//insert the previous node in the front of node
    temp = pre[temp];
  }
  path.insert(path.begin(),startId);
  return path;
}



/**
 * CalculateShortestPath_Dijkstra's helper function, find minId but not in visited
 * 
 * @param {std::map<std::string, double>} &mindis   : a map recording min distance from start node(id,distance)
 * @param {std::map<std::string, bool>} &visited     : visited list
 * @return {std::string} minId                      : minId but not in visited
 */
std::string TrojanMap::findMinIDButNotInVisited(std::map<std::string, double> &mindis, std::map<std::string, bool> &visited){
  
  std::string minId;
  double m = DBL_MAX;

  for(auto it : mindis){
    //if there is no node it in the visited list, and it has the min-dis 
    if(visited[it.first] != true && it.second < m){
      m = it.second;
      minId = it.first;
    }
  }
  visited[minId] = true;
  return minId;
}

/**
 * CalculateShortestPath_Bellman_Ford: Given 2 locations, return the shortest path which is a
 * list of id.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Bellman_Ford(
    std::string location1_name, std::string location2_name){
  std::vector<std::string> path;//result (list of id)
  std::map<std::string, double> mindis;//record current min distance from start node(id,distance)
  //initialize the distince = Max
  for(auto it: data){
    mindis[it.first] = DBL_MAX;
  }

  //Specific cases
  //1.if the inputs is empty
  if (location1_name.length() == 0 || location2_name.length() == 0) {
    return path;
  }
  //2.if the inputs is invalid
  std::string startId = GetID(location1_name);
  std::string goalId = GetID(location2_name); 
  if(data.find(startId)==data.end() || data.find(goalId)==data.end()){
    return path;
  }
  //3.if the start or goal have no neighbor.
  if(GetNeighborIDs(startId).size()==0 || GetNeighborIDs(goalId).size() == 0){
    return path;
  }

  std::map<std::string, std::string> pre;//record the provious node (curId,prevId)

  mindis[startId] = 0;
  for(int i = 1; i <= mindis.size()-1; i++ ){//the min-dis of first n-1 node
    for(auto it:mindis){//iterate all node's id with min-dis
      for(auto neighborId : GetNeighborIDs(it.first)){//min-dis nodes' neighbors
        if( mindis[neighborId] > CalculateDistance(it.first, neighborId)+it.second ){//find the min-dis
          mindis[neighborId] = CalculateDistance(it.first, neighborId)+it.second;
          pre[neighborId] = it.first;//"it" is the previous node of its neighbor
        }
      }
    }
  }
  path.push_back(goalId);
  //generate the final path using the prev map
  std::string temp = pre[goalId];
  while(temp != startId){
    path.insert(path.begin(), temp);//insert the previous node in front of this node
    temp = pre[temp];
  }
  path.insert(path.begin(),startId);
  
  return path;
}


/**
 * Travelling salesman problem: Given a list of locations, return the shortest
 * path which visit all the places and back to the start point.
 *
 * @param  {std::vector<std::string>} input : a list of locations needs to visit
 * @return {std::pair<double, std::vector<std::vector<std::string>>} : a pair of total distance and the all the progress to get final path
 */
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan(
                                    std::vector<std::string> &location_ids) {
  std::pair<double, std::vector<std::vector<std::string>>> results;
  unordered_set<int> numvisited;
  std::vector<int> curP;
  //input is empty
  if (location_ids.size() == 0) {
    return results;
  }
  // input has only one element, push the element into the final path
  if (location_ids.size() == 1) {
    results.first = 0;
    results.second = {{location_ids[0]}};
    return results;
  }
  //initialize weights
  std::vector<std::vector<double>> mapWei(location_ids.size(),std::vector<double>(location_ids.size()));
  for(auto i=0;i<location_ids.size();i++){
    for(auto j=i+1;j<location_ids.size();j++){
      mapWei[i][j] = CalculateDistance(location_ids[i],location_ids[j]);
      mapWei[j][i] = mapWei[i][j];
    }
  }
  //initialize
  numvisited.insert(0);
  curP.push_back(0);

  double resD = DBL_MAX;
  std::vector<std::vector<std::string>> resP;
  
  TravellingTrojanHelper(resP,location_ids,mapWei,numvisited,resD,curP,0);
  results = std::make_pair(resD,resP);

  return results;
}
/**
 * Try all permutations. Find all possible path
 * @param {std::vector<std::vector<std::string>>} &resP
 * @param {std::vector<std::string>} &location_ids
 * @param {std::vector<std::vector<double>>} &mapWei
 * @param {std::vector<std::vector<double>>} &numvisited
 * @param {double} &resD
 * @param {std::vector<std::string>} &curPath
 * @param {double} curDis
 */ 
void TrojanMap::TravellingTrojanHelper(std::vector<std::vector<std::string>> &resP,
                                      std::vector<std::string> &location_ids,
                                      std::vector<std::vector<double>> &mapWei,
                                      std::unordered_set<int> &numvisited,double &resD, 
                                      std::vector<int> &curP, double curD){

  if(curP.size()==location_ids.size()){
    double sumD = curD + mapWei[curP.back()][0];
    if(sumD<resD){
      std::vector<std::string> t;
      for(auto i:curP)
      t.push_back(location_ids[i]);
      t.push_back(location_ids[0]);
      resP.push_back(move(t));
      resD = sumD;
    }
  }
  if(curD<resD){
    for(auto i=1;i<location_ids.size();i++){
      if(numvisited.count(i)==0){
        numvisited.insert(i);
        double deltaDist = mapWei[curP.back()][i];
        curP.push_back(i);
        TravellingTrojanHelper(resP,location_ids,mapWei,numvisited,resD,curP,curD+deltaDist);
        curP.pop_back();
        numvisited.erase(i);
      }
    }
  }
}

   
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_2opt(
      std::vector<std::string> &location_ids){
  std::pair<double, std::vector<std::vector<std::string>>> results;
  std::vector<std::vector<std::string>> resP;  
  //input is empty
  if (location_ids.size() <= 1) {
    return results;
  }
  //initialize the min-distance and resP
  std::vector<std::string> curP = location_ids;
  curP.push_back(location_ids[0]);
  double minD = CalculatePathLength(curP);
  resP.push_back(curP);
  //get the best distance
  bool flag = true;
  while(flag){
    flag = false;//whether the distance and path is updated or not
    for(auto i=1;i<curP.size()-1;i++){
      for(auto j=i+1;j<curP.size();j++){
        reverse(curP.begin()+i,curP.begin()+j);//get all possible path
        double curD = CalculatePathLength(curP);//get all distance
        //get better path, updata the distance and path
        if(curD<minD){//compare
          flag = true;
          minD = curD;
          resP.push_back(curP);
        }
        else{
          reverse(curP.begin()+i,curP.begin()+j);
        }
      }
    }
  }
  results = std::make_pair(minD,resP);
  
  return results;
}

/**
 * Given CSV filename, it read and parse locations data from CSV file,
 * and return locations vector for topological sort problem.
 *
 * @param  {std::string} locations_filename     : locations_filename
 * @return {std::vector<std::string>}           : locations 
 */
std::vector<std::string> TrojanMap::ReadLocationsFromCSVFile(std::string locations_filename){
  std::vector<std::string> location_names_from_csv;
  
  std::fstream file;
  std::string line;
  std::string word;
  file.open(locations_filename, std::ios::in);//open the file
  getline(file,line);//extract the line

  while(getline(file,line)){
    std:stringstream s(line);
    while(getline(s,word,',')){//find the delimiter and discard it
      location_names_from_csv.push_back(word);
    }
  }
  file.close();
  return location_names_from_csv;
}

/**
 * Given CSV filenames, it read and parse dependencise data from CSV file,
 * and return dependencies vector for topological sort problem.
 *
 * @param  {std::string} dependencies_filename     : dependencies_filename
 * @return {std::vector<std::vector<std::string>>} : dependencies
 */
std::vector<std::vector<std::string>> TrojanMap::ReadDependenciesFromCSVFile(std::string dependencies_filename){
  std::vector<std::vector<std::string>> dependencies_from_csv;

  std::fstream file;
  std::string line;
  std::string word;
  file.open(dependencies_filename, std::ios::in);
  getline(file, line);//extract the line

  while (getline(file, line)) {
    std::stringstream s(line);
    std::vector<std::string> t;
    while (getline(s, word, ',')){//find the delimiter and discard it
      t.push_back(word);
    }
    dependencies_from_csv.push_back(t);    
  }
  file.close();
  return dependencies_from_csv;
}

/**
 * DeliveringTrojan: Given a vector of location names, it should return a sorting of nodes
 * that satisfies the given dependencies.
 *
 * @param  {std::vector<std::string>} locations                     : locations
 * @param  {std::vector<std::vector<std::string>>} dependencies     : prerequisites
 * @return {std::vector<std::string>} results                       : results
 */
std::vector<std::string> TrojanMap::DeliveringTrojan(std::vector<std::string> &locations,
                                                     std::vector<std::vector<std::string>> &dependencies){
  std::vector<std::string> result;
  
  std::unordered_map<std::string,std::vector<std::string>> neighbors;
  //initialize neighbors list
  for(auto &loc:locations){
    neighbors[loc] = std::vector<std::string>();//all neighbors of the location is empty
  }
  for(auto &n:dependencies){//iterate dependencies list
    //no feasible route exists
    if(neighbors.count(n[0])==0 || neighbors.count(n[1])==0){//one of the two depending elements are not in the neighnors list 
      return {};
    }
    //push n[1] into n[0]'s neighbors list
    neighbors[n[0]].push_back(n[1]);
  }
  //initialize the visited list
  std::unordered_map<std::string,int> states;
  for(auto &loc:locations){
    states[loc] = 0;
  }
  for(auto &loc:locations){
    //if unvisited node doesn't have the delivering path
    if(states[loc]==0 && !DeliveringTrojanHelper(loc,neighbors,states,result)){
      return {};
    }
  }
  reverse(result.begin(),result.end());
  return result;                                             
}
/**
 * look up the Delivering path
 * @param {std::string&} loc
 * @param {std::unordered_map<std::string,std::vector<std::string>> &} neighbors
 * @param {std::unordered_map<std::string,int> &} visited
 * @param {std::vector<std::string>&} result
 * @return {bool} : true if success, false if there is a cycle and failed
 */  
bool TrojanMap::DeliveringTrojanHelper(std::string &loc,
            std::unordered_map<std::string,std::vector<std::string>> &neighbors,
            std::unordered_map<std::string,int> &states,
            std::vector<std::string> &result){
  states[loc] = 1;//current location state
  for(std::string &n:neighbors[loc]){//get all neighbors of current location
    //if one of its neighbor is visited
    if(states[n]==1){
      return false;
    }
    //if the n is not visited, and it doesn't have the delivering path
    if(states[n]==0 && !DeliveringTrojanHelper(n,neighbors,states,result)){
      return false;
    }
  }
  states[loc] = 2;
  result.push_back(loc);
  return true;
}


/**
 * Cycle Detection: Given four points of the square-shape subgraph, return true if there
 * is a cycle path inside the square, false otherwise.
 * 
 * @param {std::vector<double>} square: four vertexes of the square area
 * @return {bool}: whether there is a cycle or not
 */
bool TrojanMap::CycleDetection(std::vector<double> &square) {
  //invalid case
  if(square.size()<4){
    return false;
  }
  //bounds
  double left = square[0];
  double right = square[1];
  double upper = square[2];
  double lower = square[3];
  //invalid case
  if (left >= right || upper <= lower) {
    return false;
  }

  std::vector<std::string> subIds;
  for(auto &n:data){//get the node in this subspace
    if(n.second.lon>=left && n.second.lon<=right && n.second.lat<=upper && n.second.lat>=lower){
      subIds.push_back(n.first);
    }
  }
  
  std::unordered_map<std::string,int> states;//visited node
  std::unordered_map<std::string, std::string> pre;
  //initialize the visited list
  for(auto &id:subIds){
    pre[id] = "";
    states[id] = 0;
  }
  //look up cycle
  std::vector<std::string> c;
  for (auto id: subIds) {
    if (states[id] == 0) {
      hasCycle(id,c,states,pre);
      if(c.size()>0){//if unvisited node has cycle
        PlotPointsandEdges(c, square);
        return true;
      } 
    }
  }
  return false;
}

/**
 * Find cycle
 * @param {std::map<std::string, Node>&} data
 * @param {std::string&} curId                    : current node
 * @param {std::map<std::string,bool>&} states    : whether the nodes is visited or not
 * @param {std::string&} pre                      : previous node
 * @return {bool} : whether there is a cycle or not
 */
void TrojanMap::hasCycle(std::string cur,std::vector<std::string>& c,
        std::unordered_map<std::string, int>& states, 
        std::unordered_map<std::string, std::string>& pre) {
    states[cur] = 1;//visited state
    for (std::string nei : data[cur].neighbors) {
      //if current node dosen't have neighbors
      if (states.find(nei)== states.end()) {
        continue;
      }
      if (c.size() > 0) {
        return;//recursion
      }
      //if the neighbor is not visited, and there is unvisited node
      if (states[nei]== 0) {
        pre[nei] = cur;
        hasCycle(nei,c,states, pre);//move to next node
      } 
      //find the cycle and push it in the cycle list
      //if the neighbor is visited, and it is not the previous one of current node
      else if (states[nei]== 1 && nei != pre[cur]) {
        std::string tId = cur;
        while(tId != nei) {
          c.push_back(tId);
          tId = pre[tId];
        }
        c.push_back(tId);
        return;
      }
    }
    states[cur] = 2; //in the cycle list
}


/**
 * FindKClosetPoints: Given a location id and k, find the k closest points on the map
 * 
 * @param {std::string} name: the name of the location
 * @param {int} k: number of closest points
 * @return {std::vector<std::string>}: k closest points
 */
// Use std::sort
std::vector<std::string> TrojanMap::FindKClosestPoints_Sort(std::string name, int k) {
  std::vector<std::string> res;
  std::string id = GetID(name);

  std::vector<std::pair<float, std::string>> id_distant;  //<distance, id>
  for(auto iter : data){

    // select locations which has name
    if(iter.second.name != "" && iter.second.name != name){
      // caculate the distant of each location and sort
      id_distant.push_back(std::pair<float, std::string>(CalculateDistance(iter.first, id), iter.first));
    }
    
  }

  std::sort(id_distant.begin(), id_distant.end());

  for(int i = 0; i < k; i++){
    res.push_back(id_distant[i].second);
  }
                                     
  
  return res; // res is id
} // Runtime: O(nlogn)

// Use max-heap
std::vector<std::string> TrojanMap::FindKClosestPoints_MaxHeap(std::string name, int k) {
  std::vector<std::string> res;
  std::string id = GetID(name);

  std::vector<std::pair<float, std::string>> id_distant;  //<distance, id>
  for(auto iter : data){

    // select locations which has name
    if(iter.second.name != "" && iter.second.name != name){
      // caculate the distant of each location 
      id_distant.push_back(std::pair<float, std::string>(CalculateDistance(iter.first, id), iter.first));
    }
  }

  // use max-heap to find k closest positions
  priority_queue<std::pair<float, std::string>> pq; // max_heap
  // First let the first K elements in id_distant heap
  for(int i = 0; i < k; ++i){
      pq.push(id_distant[i]);
  }
  // push item if it is smaller than the top
  for(int i = k; i < id_distant.size(); ++i){
      if(id_distant[i].first < pq.top().first){
          pq.pop();
          pq.push(id_distant[i]);
      }
  }
  // copy to res
  for(int i = 0; i < k; ++i) {
      res.push_back(pq.top().second);
      pq.pop();
  }
  reverse(res.begin(), res.end());                       
  return res; // res is id
}// O(nlogk)