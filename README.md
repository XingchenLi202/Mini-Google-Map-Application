# EE538 Final Project - Fall 2021 - TrojanMap
# Report

Xingchen Li:  xli31296@usc.edu

Yusong chen:  yusongc@usc.edu

## Overview

This project focuses on using data structures in C++ and implementing various graph algorithms to build a map application. It implements the trojan map application with seversal features. We will cover each feature in detail.

<p align="center"><img src="img/TrojanMap.png" alt="Trojan" width="500" /></p>

- 1. Autocomplete the location name
- 2. Find the place's Coordinates in the Map
- 3. Calculate shortest path between two places
- 4. The Traveling Trojan Problem
- 5. Cycle Detection
- 6. Topological Sort
- 7. Find K closest points

## The data Structure

Each point on the map is represented by the class Node shown below and defined in trojanmap.h.

The Node structure records the information of a location including the location's name and its latitude and longitude. Besides, the unique id of this location is assigned to each point in the map. And the adjacent Nodes' id of this location are represented in a vector.

```cpp
class Node {
  public:
    Node(){};
    Node(const Node &n){id = n.id; lat = n.lat; lon = n.lon; name = n.name; neighbors = n.neighbors;};
    std::string id;    // A unique id assign to each point
    double lat;        // Latitude
    double lon;        // Longitude
    std::string name;  // Name of the location. E.g. "Bank of America".
    std::vector<std::string> neighbors;  // List of the ids of all neighbor points.
};
```

## 1. Autocomplete the location name

Input: prefix of name
Output: complete possible name

First, traverse all positions and then convert them to the same lowercase form. Then find all the position‘s name that meet the requirements and return as a result.

The time complexity is O(n)

### Example
<p align="center"><img src="myoutput/step1-1.png" alt="Trojan" width="500" /></p>
<p align="center"><img src="myoutput/step1-2.png" alt="Trojan" width="500" /></p>


## 2. Find the place's Coordinates in the Map

Given a location name, return the latitude and longitude. There are no duplicated location names. You should mark the given locations on the map. If the location does not exist, return (-1, -1).

When a user inputs a location name, the program finds the longitude and latitude of the location and returns a coordinate point. If the location name does not exist, the program displays a prompt telling the user that there is no match.

The time complexity is O(n)

```c++
std::pair<double, double> GetPosition(std::string name);
```

- CVS:

```shell
2
**************************************************************
* 2. Find the position                                        
**************************************************************

Please input a location:CVS
*************************Results******************************
Latitude: 34.0235 Longitude: -118.279
**************************************************************
Time taken by function: 576 microseconds
```

<p align="center"><img src="myoutput/S2_CVS.jpeg" alt="Trojan" width="500" /></p>

- Ralphs:

```shell
2
**************************************************************
* 2. Find the position                                        
**************************************************************

Please input a location:Ralphs
*************************Results******************************
Latitude: 34.0318 Longitude: -118.291
**************************************************************
Time taken by function: 611 microseconds
```

<p align="center"><img src="myoutput/S2_Ralphs.jpeg" alt="Trojan" width="500" /></p>

- Starbucks:

```shell
2
**************************************************************
* 2. Find the position                                        
**************************************************************

Please input a location:Starbucks
*************************Results******************************
Latitude: 34.0186 Longitude: -118.282
**************************************************************
Time taken by function: 568 microseconds
```

<p align="center"><img src="myoutput/S2_Starbucks.jpeg" alt="Trojan" width="500" /></p>

## 3. Calculate shortest path between two places

We use two algorithms: Dijkstra and Bellman-ford.

### Dijkstra:
std::vector<std::string> TrojanMap::CalculateShortestPath_Dijkstra(
    std::string location1_name, std::string location2_name)
#### Algorithm:
1. get the id of start node and end node by using Node TrojanMap::GetNode(std::string name) and then check if they are empty or invalid.
2. define std::unordered_map<std::string, double> mindis to record current min distance from start node(id,distance).
3. define std::unordered_map<std::string, std::string> prev to record the provious node (curId,prevId).
4. initialize the mindis map by setting all its values to be MAX. iniliaze the prev node ids as "".
5. updata the distance of start case, use GetNeighborIDs(startId) to get the distance from start to its neighbors.
6. updata the distance of the rest case.
7. update distances of minId's neighbors, use CalculateDistance(minid,neighborId) to calculate the dis between minId and its neighbors. Ensure the node n is not in visited list, if true, update the mindis of minId's neighbors.
8. judge if there is no way.
9. generate the final path using the prev map.  
Time complexity: O(Vlog(V) + E), where E is the number of edges, V is the number of nodes.

### Example
Start: Ralphs		
Destination: 7Eleven

<p align="center"><img src="myoutput/Dijkstra1.png" alt="Trojan" width="500" /></p>
<p align="center"><img src="myoutput/Dijkstra2.png" alt="Trojan" width="500" /></p>

### Bellman-Ford:
std::vector<std::string> TrojanMap::CalculateShortestPath_Bellman_Ford(
    std::string location1_name, std::string location2_name)
#### Algorithm:
1. get the id of start node and end node by using Node TrojanMap::GetNode(std::string name) and then check if they are empty or invalid.
2. define std::unordered_map<std::string, double> mindis to record current min distance from start node(id,distance).
3. define std::unordered_map<std::string, std::string> prev to record the provious node (curId,prevId).
4. initialize the minDist map by setting all values to be MAX. Iniliaze the prev node ids of each node as "".
5. set the start node distance as 0, traverse all edges.
6. use one loop to set the minDist of each node, use another loop to iterate each edge, then calculate the distance from current node to next node, update the minDist of next node if the path length bypassing current node is improved.
7. if no improvement after iterating all edges, just break loop.
8. find all node ids from end node to start node using prev vector, the reverse it as return value.  
Time complexity: O(V * E), where E is the number of edges, V is the number of nodes.

### Example
Start: Ralphs		
Destination: 7Eleven

<p align="center"><img src="myoutput/bellman-ford1.png" alt="Trojan" width="500" /></p>
<p align="center"><img src="myoutput/bellman-ford2.png" alt="Trojan" width="500" /></p>

## Dijkstra vs Bellman-Ford
<p align="center"><img src="myoutput/D-vs-B.png" alt="Trojan" width="500" /></p>

## Compare with Google map
<p align="center"><img src="myoutput/google-map-R-7.png" alt="Trojan" width="500" /></p>
Comments:
The reason why the shortest path results are different from those of Google Map is that Trojan Map does not contain partial W Adams Blvd points. As shown in the figure below.
<p align="center"><img src="myoutput/TrojanMap3.png" alt="Trojan" width="500" /></p>



## 4. The Traveling Trojan Problem

In this section, we assume that a complete graph is given to you. That means each node is a neighbor of all other nodes. Given a vector of location ids, assume every location can reach all other locations in the vector (i.e. assume that the vector of location ids is a complete graph). Find the shortest route that covers all the locations exactly once and goes back to the start point.

This feature is to find shortest path that traverse multiple points. The user input the number of locations n, randomly selected in the whole map. The program needs to traverse all the points and return to the starting point to find the total length of the final path. Finally, we get the shortest route linking all the locations.

### Brute Force:

The first algorithm use Brute Force, which requires obtaining the permutation of all the locations, and this is the order in which we traverse all the locations. Then, figure out the length of each path, compare and update the minimum, and add shorter paths to the path vector. The last path we get is the minimum path.

The time complexity is O(n!)

```c++
std::pair<double, std::vector<std::vector<std::string>>> TravellingTrojan(
                              std::vector<std::string> &location_ids);
```

```shell
*************************Results******************************
269636426
122817160
123120147
7281805576
269633016
4015405545
122719213
6816180147
6816822864
4835551074
269636426
**************************************************************
The distance of the path is:5.77737 miles
**************************************************************
You could find your animation at src/lib/output.avi.          
Time taken by function: 370794 microseconds
```

The number of location is 10:

<p align="center"><img src="myoutput/S4_BForce10.jpeg" alt="Trojan" width="500" /></p>

<p align="center"><img src="myoutput/S4_BForce10.gif" alt="Trojan" width="500" /></p>

The number of location is 8:

<p align="center"><img src="myoutput/S4_BForce8.jpeg" alt="Trojan" width="500" /></p>

<p align="center"><img src="myoutput/S4_BForce8.gif" alt="Trojan" width="500" /></p>

The number of location is 5:

<p align="center"><img src="myoutput/S4_BForce5.jpeg" alt="Trojan" width="500" /></p>

<p align="center"><img src="myoutput/S4_BForce5.gif" alt="Trojan" width="500" /></p>

### 2-opt Heuristic:

The difference from the last one is that we use two for loops to get sub-location-ID and reverse the sub part, then find the length of the path and keep updating the path to the shortest one until the optimal solution is obtained. The Heuristic algorithm get the global minimum path by getting the local minimum path.

The time complexity in worst case is O(n^2). But, generally, it is uncertain because the Heuristic algorithm will be in different case.

```c++
std::pair<double, std::vector<std::vector<std::string>>> TravellingTrojan_2opt(
                              std::vector<std::string> &location_ids)
```

```shell
*************************Results******************************
6807905595
6807909279
2613117885
4015372470
4020099336
7023424980
6813379461
6045067407
6816305558
1400581340
6807905595
**************************************************************
The distance of the path is:4.62675 miles
**************************************************************
You could find your animation at src/lib/output.avi.          
Time taken by function: 3276 microseconds
```

The number of location is 10:

<p align="center"><img src="myoutput/S4_2_opt10.jpeg" alt="Trojan" width="500" /></p>

<p align="center"><img src="myoutput/S4_2_opt10.gif" alt="Trojan" width="500" /></p>

The number of location is 8:

<p align="center"><img src="myoutput/S4_2_opt8.jpeg" alt="Trojan" width="500" /></p>

<p align="center"><img src="myoutput/S4_2_opt8.gif" alt="Trojan" width="500" /></p>

The number of location is 5:

<p align="center"><img src="myoutput/S4_2_opt5.jpeg" alt="Trojan" width="500" /></p>

<p align="center"><img src="myoutput/S4_2_opt5.gif" alt="Trojan" width="500" /></p>

### Comparing the results of the two algorithms

<p align="center"><img src="myoutput/S4_Com.png" alt="Trojan" width="500" /></p>

As we can see in the picture, when the number of node is gradually increasing, the time complexity of Brute Force Algorithm dramatically increases. However, the run time of 2-opt Heuristic Algorithm just show a slow growth. We can conclude that the brute force is not practical when the number of node is large. 

## 5. Cycle Detection
bool TrojanMap::CycleDetection(std::vector<double> &square)

1. The input is a numbers of coordinates composed of longitude and latitude. 
2. Use void TrojanMap::hasCycle(std::string cur,std::vector<std::string>& c,
        std::unordered_map<std::string, int>& states, 
        std::unordered_map<std::string, std::string>& pre) 
   to find a circle in this range.  
   a. initialize visited states.  
   b. if current node dosen't have neighbors, continue.  
   c. iterate each id in ids vector in square, if it's marked as 0 (unvisited), then do dfs starting from that id.
   c. in dfs, mark current id as 1 (being visited), then iterate its neighbor ids.  
      if the neighbor id is in visited set (in square)  
         if next neighbor id marked as 0 (not visited), just call dfs again on that neighbor id.  
      if next neighbor id marked as 1 (being visited) and it's not the previous node of current node, cycle found, find all node ids in prev vector starting from current node id, end at neighbor node id, add into cycle vector.  
   d. mark current node (id) as 2 (has been visited)  

Time complexity: O(n), n is the number of nodes in square.

### Example
<p align="center"><img src="myoutput/cycle-D1.png" alt="Trojan" width="500" /></p>
<p align="center"><img src="myoutput/cycle-D2.png" alt="Trojan" width="500" /></p>
<p align="center"><img src="myoutput/cycle-D3.png" alt="Trojan" width="500" /></p>

## 6. Topological Sort

`topologicalsort_locations.csv` gives the nodes what we want to connect. 

`topologicalsort_dependencies.csv` gives the order of each two nodes.

This step is the realization of topological sorting. We input a vector of location. Their topological order is obtained based on the given set of dependencies. Firstly, DFS starts with the starting point, and when all children of a node have been accessed, it can be added to a list. Then the nodes that have never been accessed start DFS again. Finally, the vector is reversed to obtain topological sequence.

The time complexity is O(n)

```c++
std::vector<std::string> DeliveringTrojan(std::vector<std::string> &location_names,
                              std::vector<std::vector<std::string>> &dependencies);
```

```shell
6
**************************************************************
* 6. Topological Sort                                         
**************************************************************

Please input the locations filename:/Users/apple/EE538/final-project-XingchenLi202/input/topologicalsort_locations.csv
Please input the dependencies filename:/Users/apple/EE538/final-project-XingchenLi202/input/topologicalsort_dependencies.csv
*************************Results******************************
Topological Sorting Results:
Cardinal Gardens
Target
CVS
**************************************************************
Time taken by function: 42 microseconds
```

<p align="center"><img src="myoutput/S6_3points.jpeg" alt="Trojan" width="500" /></p>

```shell
6
**************************************************************
* 6. Topological Sort                                         
**************************************************************

Please input the locations filename:/Users/apple/EE538/final-project-XingchenLi202/input/topologicalsort_locations.csv
Please input the dependencies filename:/Users/apple/EE538/final-project-XingchenLi202/input/topologicalsort_dependencies.csv
*************************Results******************************
Topological Sorting Results:
Lawn
Freeway Insurance
LATTCOrtho Institute
Coffee Bean1
Starbucks
Hill 38 Washington
John Adams Middle School
Cardinal Gardens
Target
CVS
**************************************************************
Time taken by function: 85 microseconds
```

<p align="center"><img src="myoutput/S6_10points.jpeg" alt="Trojan" width="500" /></p>

## 7. Find K closest points
We use 2 algorithms in this step: std::sort and max-heap.

### std::sort
First calculate the distance of all positions from the input position, and the key is id，the value is the distance, then sort to find the first k closest positions as output.  
Runtime: O(nlogn)

### max-heap
1. calculate the distance of all positions from the input position, and the key is id，the value is the distance.
2. init max-heap by using priority_queue<std::pair<float, std::string>> pq.
3. put the first K elements in id_distant into the heap.
4. push item if it is smaller than the top.
5. copy items in heap to res as result.  
Runtime: O(nlogk)

### Output Example
<p align="center"><img src="myoutput/FindK11.png" alt="Trojan" width="500" /></p>
<p align="center"><img src="myoutput/FindK2.png" alt="Trojan" width="500" /></p>

### std::sort vs max-heap
<p align="center"><img src="myoutput/FindK-vs.png" alt="Trojan" width="500" /></p>


# Acknowledgement
I am very grateful to the professors and TAs. They helped me a lot during this semester. Through this project, my C++ and algorithm skills have been greatly improved. In addition, this is also very helpful for my future job interviews. Thanks again to the teachers and TAs, I wish you good health and success in your work!  


# Appendix: Project requirements

## Deadline: 

Video Presentation: Friday, December 3 by 2 pm

Code submission: Monday, December 7 by 23:59 pm

## TrojanMap

This project focuses on using data structures in C++ and implementing various graph algorithms to build a map application.

<p align="center"><img src="img/TrojanMap.png" alt="Trojan" width="500" /></p>

- Please clone the repository, look through [README.md](README.md) and fill up functions to finish in the project.
- Please make sure that your code can run `bazel run/test`.
- In this project, you will need to fill up [trojanmap.cc](src/lib/trojanmap.cc) and add unit tests in the `tests` directory.

---

## The data Structure

Each point on the map is represented by the class **Node** shown below and defined in [trojanmap.h](src/lib/trojanmap.h).

```cpp
class Node {
  public:
    std::string id;    // A unique id assign to each point
    double lat;        // Latitude
    double lon;        // Longitude
    std::string name;  // Name of the location. E.g. "Bank of America".
    std::vector<std::string>
        neighbors;  // List of the ids of all neighbor points.
};

```

---

## Prerequisites

### OpenCV Installation

For visualization, we use OpenCV library. You will use this library as a black box and don't need to worry about the graphic details.

Use the following commands to install OpenCV.

```shell
$ cd 2021Fall_TrojanMap
$ git clone https://github.com/opencv/opencv.git
```

### Other library Installations

For Ubuntu:
```shell
$ sudo apt-get install cmake libgtk2.0-dev pkg-config
$ sudo apt install libcanberra-gtk-module libcanberra-gtk3-module
$ sudo apt-get install libncurses5-dev libncursesw5-dev
$ cp ubuntu/* ./
```

For MacOS:
```shell
$ brew install cmake
$ brew install ncurses
```

Next, type the following, but make sure that you set the **path_to_install_folder** to be the absolute path to the install folder under opencv.

```shell
$ cd opencv/
$ mkdir build install
$ cd build
$ cmake -D CMAKE_INSTALL_PREFIX=/Users/apple/EE538/final-project-XingchenLi202/opencv/install\
 -D BUILD_LIST=core,highgui,imgcodecs,imgproc,videoio\
 -D WITH_TBB=ON -D WITH_OPENMP=ON -D WITH_IPP=ON\
 -D CMAKE_BUILD_TYPE=RELEASE -D BUILD_EXAMPLES=OFF\
 -D WITH_NVCUVID=ON\
 -D WITH_CUDA=ON\
 -D BUILD_DOCS=OFF\
 -D BUILD_PERF_TESTS=OFF\
 -D BUILD_TESTS=OFF\
 -D WITH_CSTRIPES=ON\
 -D WITH_OPENCL=ON ..
$ make install
```

For example, if cloned this repo under "/Users/ari/github/TrojanMap", you should type:

```shell
$ cd opencv/
$ mkdir build install
$ cd build
$ cmake -D CMAKE_INSTALL_PREFIX=/Users/ari/github/TrojanMap/opencv/install\
 -D BUILD_LIST=core,highgui,imgcodecs,imgproc,videoio\
 -D WITH_TBB=ON -D WITH_OPENMP=ON -D WITH_IPP=ON\
 -D CMAKE_BUILD_TYPE=RELEASE -D BUILD_EXAMPLES=OFF\
 -D WITH_NVCUVID=ON\
 -D WITH_CUDA=ON\
 -D BUILD_DOCS=OFF\
 -D BUILD_PERF_TESTS=OFF\
 -D BUILD_TESTS=OFF\
 -D WITH_CSTRIPES=ON\
 -D WITH_OPENCL=ON ..
$ make install
```

---

## Run the program

Please run:

```shell
$ bazel run src/main:main
```

If everything is correct, this menu will show up.

```shell
Torjan Map
**************************************************************
* Select the function you want to execute.                    
* 1. Autocomplete                                             
* 2. Find the position                                        
* 3. CalculateShortestPath                                    
* 4. Travelling salesman problem                              
* 5. Cycle Detection                                          
* 6. Topological Sort                                         
* 7. Find K Closest Points                                    
* 8. Exit                                                     
**************************************************************
Please select 1 - 8:
```

## Test the program

We created some tests for you to test your program, please run
```shell
$ bazel test tests:trojanmap_test
```

Please add you test in the [trojanmap_test_student.cc](tests/trojanmap_test_student.cc) and run

```shell
$ bazel test tests:trojanmap_test_student
```

## First task is to implement a function for each menu item

## Step 1: Autocomplete the location name

```c++
std::vector<std::string> Autocomplete(std::string name);
```

We consider the names of nodes as the locations. Implement a method to type the partial name of the location and return a list of possible locations with partial name as prefix. Please treat uppercase and lower case as the same character.

Example:

Input: "ch" \
Output: ["ChickfilA", "Chipotle Mexican Grill"]

Input: "ta" \
Output: ["Target", "Tap Two Blue"]

```shell
1
**************************************************************
* 1. Autocomplete                                             
**************************************************************

Please input a partial location:ch
*************************Results******************************
ChickfilA
Chipotle Mexican Grill
**************************************************************
Time taken by function: 1904 microseconds
```

## Step 2: Find the place's Coordinates in the Map

```c++
std::pair<double, double> GetPosition(std::string name);
```

Given a location name, return the latitude and longitude. There are no duplicated location names. You should mark the given locations on the map. If the location does not exist, return (-1, -1).

Example:

Input: "ChickfilA" \
Output: (34.0167334, -118.2825307)

Input: "Ralphs" \
Output: (34.0317653, -118.2908339)

Input: "Target" \
Output: (34.0257016, -118.2843512)

```shell
2
**************************************************************
* 2. Find the position                                        
**************************************************************

Please input a location:Target
*************************Results******************************
Latitude: 34.0257 Longitude: -118.284
**************************************************************
Time taken by function: 1215 microseconds
```

<p align="center"><img src="img/Target.png" alt="Target" width="500"/></p>

## Step 3: CalculateShortestPath between two places

```c++
std::vector<std::string> CalculateShortestPath_Dijkstra(std::string &location1_name,
                                               std::string &location2_name);
std::vector<std::string> CalculateShortestPath_Bellman_Ford(std::string &location1_name,
                                               std::string &location2_name);
```

Given 2 locations A and B, find the best route from A to B. The distance between 2 points is the euclidean distance using latitude and longitude. You should use both Dijkstra algorithm and Bellman-Ford algorithm. Compare the time for the different methods. Show the routes on the map. If there is no path, please return empty vector.

Please report and compare the time spent by these 2 algorithms.

Example:

Input: "Ralphs", "ChickfilA" \
Output: ["2578244375", "5559640911", "6787470571", "6808093910", "6808093913", "6808093919", "6816831441",
      "6813405269", "6816193784", "6389467806", "6816193783", "123178876", "2613117895", "122719259",
      "2613117861", "6817230316", "3642819026", "6817230310", "7811699597", "5565967545", "123318572",
      "6813405206", "6813379482", "544672028", "21306059", "6813379476", "6818390140", "63068610", 
      "6818390143", "7434941012", "4015423966", "5690152766", "6813379440", "6813379466", "21306060",
      "6813379469", "6813379427", "123005255", "6807200376", "6807200380", "6813379451", "6813379463",
      "123327639", "6813379460", "4141790922", "4015423963", "1286136447", "1286136422", "4015423962",
      "6813379494", "63068643", "6813379496", "123241977", "4015372479", "4015372477", "1732243576",
      "6813379548", "4015372476", "4015372474", "4015372468", "4015372463", "6819179749", "1732243544",
      "6813405275", "348121996", "348121864", "6813405280", "1472141024", "6813411590", "216155217", 
      "6813411589", "1837212103", "1837212101", "6820935911", "4547476733"]

```shell
3
**************************************************************
* 3. CalculateShortestPath
**************************************************************

Please input the start location:Ralphs
Please input the destination:ChickfilA
*************************Results******************************
The distance of the path is:1.53852 miles
**************************************************************
Time taken by function: 45149 microseconds
```

<p align="center"><img src="img/Routing.png" alt="Routing" width="500"/></p>

## Step 4: The Traveling Trojan Problem (AKA Traveling Salesman!)

In this section, we assume that a complete graph is given to you. That means each node is a neighbor of all other nodes.
Given a vector of location ids, assume every location can reach all other locations in the vector (i.e. assume that the vector of location ids is a complete graph).
Find the shortest route that covers all the locations exactly once and goes back to the start point. 

You will need to return the progress to get the shortest route which will then be converted to an animation.  

We will use the following algorithms:

- Backtracking
```c++
std::pair<double, std::vector<std::vector<std::string>>> TravellingTrojan(
      std::vector<std::string> &location_ids);
```
- [2-opt Heuristic](https://en.wikipedia.org/wiki/2-opt). Also see [this paper](http://cs.indstate.edu/~zeeshan/aman.pdf)
```c++
std::pair<double, std::vector<std::vector<std::string>>> TravellingTrojan_2opt(
      std::vector<std::string> &location_ids);
```

Please report and compare the time spent by these 2 algorithms. 2-opt algorithm may not get the optimal solution. Please show how far your solution is from the optimal solution.

Show the routes on the map. For each intermediate solution, create a new plot. Your final video presentation should include the changes to your solution.

We will randomly select N points in the map and run your program.

```shell
4
**************************************************************
* 4. Travelling salesman problem                              
**************************************************************

In this task, we will select N random points on the map and you need to find the path to travel these points and back to the start point.

Please input the number of the places:10
Calculating ...
*************************Results******************************
The distance of the path is:4.70299 miles
**************************************************************
You could find your animation at src/lib/output.avi.          
Time taken by function: 152517394 microseconds
```

<p align="center"><img src="img/TSP.png" alt="TSP" width="500"/></p>

<p align="center"><img src="img/output.gif" alt="TSP videos" width="500"/></p>

## Step 5: Cycle Detection

```c++
bool CycleDetection(std::vector<double> &square);
```

In this section, we use a square-shaped subgraph of the original graph by using four coordinates stored in ```std::vector<double> square```, which follows the order of left, right, upper, and lower bounds. 

Then try to determine if there is a cycle path in the that subgraph. If it does, return true and report that path on the map. Otherwise return false.

Example 1:
```shell
Input: square = {-118.299, -118.264, 34.032, 34.011}
Output: true
```
Here we use the whole original graph as our subgraph. 
<p align="center"><img src="img/cycle1.png" alt="TSP" width="500"/></p>

Example 2:
```shell
Input: square = {-118.290919, -118.282911, 34.02235, 34.019675}
Output: false
```
Here we use a square area inside USC campus as our subgraph
<p align="center"><img src="img/cycle2.png" alt="TSP" width="500"/></p>

Note: You could use the function below to visualize the subgraph. 

```c++
/**
 * PlotPoints: Given a vector of location ids draws the points on the map (no path).
 * 
 * @param  {std::vector<std::string>} location_ids : points inside square
 * @param  {std::vector<double>} square : boundary
 */
void TrojanMap::PlotPointsandEdges(std::vector<std::string> &location_ids, std::vector<double> &square)
```
```shell
5
**************************************************************
* 5. Cycle Detection                                          
**************************************************************

Please input the left bound longitude(between -118.299 and -118.264):-118.299
Please input the right bound longitude(between -118.299 and -118.264):-118.264
Please input the upper bound latitude(between 34.011 and 34.032):34.032
Please input the lower bound latitude(between 34.011 and 34.032):34.011
*************************Results******************************
there exists cycle in the subgraph 
**************************************************************
Time taken by function: 273734 microseconds

5
**************************************************************
* 5. Cycle Detection                                          
**************************************************************

Please input the left bound longitude(between -118.299 and -118.264):-118.290919
Please input the right bound longitude(between -118.299 and -118.264):-118.282911
Please input the upper bound latitude(between 34.011 and 34.032):34.02235
Please input the lower bound latitude(between 34.011 and 34.032):34.019675
*************************Results******************************
there exist no cycle in the subgraph 
**************************************************************
Time taken by function: 290371 microseconds
```
## Step 6: Topological Sort

```c++
std::vector<std::string> DeliveringTrojan(std::vector<std::string> &location_names,
                                            std::vector<std::vector<std::string>> &dependencies);
```

Tommy Trojan got a part-time job from TrojanEats, for which he needs to pick up and deliver food from local restaurants to various location near the campus. Tommy needs to visit a few different location near the campus with certain order, since there are some constraints. For example, he must first get the food from the restaurant before arriving at the delivery point. 

The TrojanEats app will have some instructions about these constraints. So, Tommy asks you to help him figure out the feasible route!

Here we will give you a vector of location names that Tommy needs to visit, and also some dependencies between those locations.


For example, 

```shell
Input: 
location_names = {"Cardinal Gardens", "Coffee Bean1", "CVS"}
dependencies = {{"Cardinal Gardens","Coffee Bean1"}, {"Cardinal Gardens","CVS"}, {"Coffee Bean1","CVS"}}
```

Here, ```{"Cardinal Gardens","Coffee Bean1"}``` means
that Tommy must go to `Cardinal Gardens` prior to `Coffee Bean1`.

Your output should be:
```shell
Output: Cardinal Gardens -> Coffee Bean1 -> CVS
```
Also, we provide ```PlotPointsOrder``` function that can visualize the results on the map. It will plot each location name and also some arrowed lines to demonstrate a feasible route.

If no feasible route exists, you could simply return an empty vector.

Hint:
- You also need to finish ```ReadLocationsFromCSVFile``` and ```ReadDependenciesFromCSVFile``` functions, so you could read and parse data from you own CSV files. We also give two sample CSV files under ```input``` folder, which could be a reference. 
- When it asks you filenames, you need to give the absolute path.
- If you do not have ```ReadLocationsFromCSVFile``` and ```ReadDependenciesFromCSVFile``` functions ready yet, you can just press enter when it asks you filenames. It will call the default locations and dependencies.
- The locations are actually nodes, and the dependencies could be directed edges. You may want to first construct a DAG and then implement topological sort algorithm to get the route.

```shell
6
*************************Results******************************
Topological Sorting Results:
Cardinal Gardens
Coffee Bean1
CVS
**************************************************************
Time taken by function: 43 microseconds
```
<p align="center"><img src="img/TopologicalSort.png" alt="TSP" width="500"/></p>

In the user interface, we read the locations and dependencies from `topologicalsort_dependencies.csv` and `topologicalsort_locations.csv` to modify your input there.

## Step 7: Find K closest points

Given a location name and a integer k , find the k closest locations with name on the map and return a vector of string ids. 

We will use the following algorithms:

- Backtracking
```c++
std::vector<std::string> FindKClosestPoints(std::string name, int k);
```

Please report and compare the time spent by this algorithm and show the points on the map.

```shell
**************************************************************
* 7. Find K Closest Points                                    
**************************************************************

7
**************************************************************
* 7. Find K Closest Points                                    
**************************************************************

Please input the locations:Ralphs
Please input k:5
*************************Results******************************
Find K Closest Points Results:
1 St Agnes Church
2 Saint Agnes Elementary School
3 Warning Skate Shop
4 Menlo AvenueWest Twentyninth Street Historic District
5 Vermont Elementary School
**************************************************************
Time taken by function: 1975 microseconds
```

<p align="center"><img src="img/Kclosest.png" alt="Kclosest" width="500"/></p>


## Reporting Runtime:
For each menu item, your program should show the time it took to finish each task.

Please make sure to provide various examples when you report the runtime. For example for topological sort, show an example with few nodes and another example with 10 or more nodes. The idea is to see how your runtime grows as input size grows.

## Runtime Comparison
For shortest path algorithms, you should compare solving the same problem with different algorithms (Dijkstra and Bellman-Ford). Please show the results on at least 10 different examples.

Similarly for TSP problem, please provide various examples that show the runtime comparison. In particular, you should show at what point using the exhaustive search is not practical and compare the same input with the heuristic implementation.


## Report and Rubrics:

Your final project should be checked into Github. The README of your project is your report. 

### Report:

Your README file should include two sections:

1. High-level overview of your design (Use diagrams and pictures for your data structures).

2. Detailed description of each function and its time complexity.

3. Time spent for each function.
4. Discussion, conclusion, and lessons learned.

### Rubrics:

1. Implementation of auto complete: 5 points.
2. Implementation of GetPosition: 5 points.
3. Implementation of shortest path: 15 points.
   1. Bellman-Ford implementation
   2. Dijkstra implementation
   3. Plot two paths, and measure and report time spent by two algorithms.
4. Implementation of Travelling Trojan: 
   1. Brute Force: 10 points.
   2. 2-opt: 10 points.
   3. Animated plot: 5 points.
4. Implement of Cycle detection: 10 points.
   1. Boolean value and draw the cycle if there exists one.
5. Topological Sort: 10 points.
   1. Check whether there exist a topological sort or not
   2. Return the correct order and plot those point on the map
6. Creating reasonable unit tests: 10 points.
   1. Three different unit tests for each item.
7. Find K closest points: 10 points.
   1. Return the correct ids and draw the points.
8. Video presentation and report: 10 points.

9. **Extra credit items**: Maximum of 20 points:
   1. [3-opt](http://cs.indstate.edu/~zeeshan/aman.pdf): 10 points.
   2. [Genetic algorithm](https://www.geeksforgeeks.org/traveling-salesman-problem-using-genetic-algorithm/) implementation for Travelling Trojan: 10 points
   3. Create dynamic and animated UI using [ncurses](https://en.wikipedia.org/wiki/Ncurses): 10 points
      - You could check https://github.com/ourarash/ncurses_bazel
      - Please develope your own UI.
      - Example
      - Accurate measurement of your algorithm runtime using Google Benchmark while sweeping the input size and providing a diagram of how the runtime grows based on the input size.
<p align="center"><img src="img/ncurses example.gif" alt="example" width="500"/></p>
   Note: For Ubuntu, you main need to use the following command to prevent errors.
   
   ```shell
   $ bazel run --cxxopt='-std=c++17' src/main:main
   ```

