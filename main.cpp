#include <iostream>
#include <algorithm>   
#include <vector>
#include "includes/algorithms.hpp"
#include <fstream>
#include <string> 
using namespace std; 
                             





//vale to apo panw function sto includes/algorithms.cpp 
int main(int argc, char* argv[]) 
{
    clock_t start, end;
    start = clock();

// cout << "argc = " << argc << endl;                                              //uncomment when using args
// cout << "argv[0] = " << argv[0] << endl; 
vector <string> argPoints;                                               

    if (argc > 1) {
        // cout << "argv[1] = " << argv[1] << endl; 
    } else {
        cout << "No file name entered. Exiting...";
        return -1;
    }
    ifstream infile(argv[2]); //open the file
    
    if (infile.is_open() && infile.good()) {
        // cout << "File is now open!\nContains:\n";
        string line = "";
        while (getline(infile, line)){
            // cout << line << '\n';
            istringstream ss(line);
            string substr;
            while(getline(ss, substr, '\t'))
            {
                argPoints.push_back(substr); 
            }
        }
        
    } else {
        cout << "Failed to open file..";
    }


vector <Point_2> mypoints; 
vector <Segment_2> polyg_segments;
Polygon_2 polyg_line; 
Polygon_2 test_polyg_line; 
std::vector<Polygon_2>::iterator ret_test_it;
std::vector<pair<Point_2,int>> vertex_iterators; 


for (int i = 3, j = 4; i,j < argPoints.size(); i+=3, j+=3) {               //uncomment when using args
    int x = stoi(argPoints[i]); 
    int y = stoi(argPoints[j]);
    mypoints.push_back(Point_2(x,y)); 
};

// cout << "argv[4] = output file " << endl; 
// cout << "argv[6] = " << argv[6] << endl;         //if argv[6] = incremental tote argv[]

// cout << "argv[8] = " << argv[8] << endl; 
// cout << "argv[10] = " << argv[10] << endl; 
string algorithm = argv[6]; 

int edge_selection = stoi(argv[8]); 
// cout << "edge selection is " << edge_selection << endl; 
bool max_area_selection, min_area_selection; 
if (edge_selection == 1) {
    bool max_area_selection = false;             //1.4416  1.68693  1.20027  london -----45
    bool min_area_selection = false; 
}else if (edge_selection == 2) {
    bool max_area_selection = false;             
    bool min_area_selection = true; 
}else if (edge_selection == 3) {
    bool max_area_selection = true;             
    bool min_area_selection = false;  
} else {
    cout << "wrong edge selection given from input. Can only give 1 or 2 or 3." << endl;
    EXIT_FAILURE;
}

string init = argv[10]; 

if (init == "1a") {
    cout << "1a" << endl; 
    sort(mypoints.begin(), mypoints.end(),greater<Point_2>());   
}else if (init == "1b") {
    sort(mypoints.begin(), mypoints.end());
}else if (init == "2a") {
    sort(mypoints.begin(), mypoints.end(), sortbysecInc);
}else if (init == "2b") {
    sort(mypoints.begin(), mypoints.end(), sortbysecDec);
}

Points c_result; 
Polygon_2 init_convex_hull; 
CGAL::convex_hull_2(mypoints.begin(), mypoints.end(), std::back_inserter(c_result));             
for(auto it = c_result.begin(); it!= c_result.end();++it) { 
    init_convex_hull.push_back(*it);
}
double init_ch_area = abs(init_convex_hull.area());

// mypoints.push_back(Point_2(0,0));
// mypoints.push_back(Point_2(2,2));
// mypoints.push_back(Point_2(4,0));
// mypoints.push_back(Point_2(5,3));
// mypoints.push_back(Point_2(6,6));
// mypoints.push_back(Point_2(10,10));
// mypoints.push_back(Point_2(8,3));
// mypoints.push_back(Point_2(9,4));
// mypoints.push_back(Point_2(10,8));



// cout << "my points are "<< endl; 
for (int i=0; i<mypoints.size(); i++)
    {
        cout << mypoints[i] << endl;
    }

for (int i=0; i<3; i++) {
    // cout << "popping " << mypoints[0] << endl;     //creating the initial polygonial line in the form of a triangle 
    polyg_line.push_back(mypoints[0]);
    vertex_iterators.push_back(make_pair(mypoints[0],i)); 
    mypoints.erase(mypoints.begin()); 
}


// cout << "Initialized the polygonial line in the form of a triangle" << endl; 

// for(const Segment_2& e : polyg_line.edges()){
//     std::cout << e << std::endl;
// }

//  cout << "last element of polygonial line " << polyg_line[polyg_line.size() - 1] << endl;

Points result; 
Polygon_2 convex_h; 
vector <Segment_2> red_edges;

 
while (mypoints.size()) {
    convex_h = calc_convex_hull(polyg_line); 
    // cout << "convex hull segments " << endl; 
    // for(const Segment_2& e : convex_h.edges()){
    // std::cout << e << std::endl;
    // }

    // cout << "checking for point: " << mypoints[0] << endl; 
    Point_2 lastPoint = polyg_line[polyg_line.size() - 1];
    std::vector<Segment_2>::iterator it;
    for(const Segment_2& e : convex_h.edges()){ 
        Segment_2 pToMidPoint(mypoints[0],midpoint(e.source(),e.target())); 
        int counter = 0;    
        for (const Segment_2& e2 : convex_h.edges()) {
            if (e == e2) {
                continue; 
            }else if (intersection(pToMidPoint,e2)) { 
                counter++;                                                   
                continue;                                                               
            }else {
            }
        }
        if (counter == 0) {
            // cout << e << " is a red edge for point " << mypoints[0] << endl;     
            bool redEdgeOnPolyg = segmentIsOnPolygon(e,polyg_line);
            if (redEdgeOnPolyg) {                                   ////if red edge already in polygonial line, that means it is replaceable and can be replaced immediatly
                // cout << e << " of convex hull is on polyg line also , so it is replaceable" << endl; 
                insertOnPolygLine(e,polyg_line,vertex_iterators,mypoints[0]);   
                break;
            }else { 
                // cout << "edge : " << e << " of convex hull is not on polygon so find replaceable edges of polyg line from its vertices " << endl; 
                Segment_2 v1ReplaceableEdge = findReplaceableEdge(polyg_line,e,mypoints[0],vertex_iterators,max_area_selection,min_area_selection);
                insertOnPolygLine(v1ReplaceableEdge,polyg_line,vertex_iterators,mypoints[0]); 
                break; 
            }
        }
    }
    mypoints.erase(mypoints.begin());  
}

end = clock();

double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
time_taken *=1000;
// cout << " final polygonial line " << endl; 
for(const Segment_2& e : polyg_line.edges()){
 std::cout << e << std::endl;
 }
cout << "Algorithm: " << algorithm << " _edge_selection " << edge_selection << " _initialization " << init << endl; 
double polyg_line_area = abs(polyg_line.area()); 
cout << "Area of polygon: " << polyg_line_area << endl; 
double ratio = polyg_line_area/init_ch_area; 
cout << "Ratio: " << ratio << endl; 
cout << "Construction time: " << fixed
         << round(time_taken) << setprecision(5);
    cout << " ms " << endl;

return 0;
}