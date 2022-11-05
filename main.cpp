#include <iostream>
#include <algorithm>   
#include <vector>
#include "includes/algorithms.hpp"
#include <fstream>
#include <string> 
using namespace std; 
                             

int main(int argc, char* argv[]) 
{
                                        ///giorgos if algorithm 
    clock_t start, end;
    start = clock();

vector <string> argPoints;                                               

    if (argc > 1) {
    } else {
        cout << "No file name entered. Exiting...";
        return -1;
    }
    ifstream infile(argv[2]); //open the file
    
    if (infile.is_open() && infile.good()) {
        string line = "";
        while (getline(infile, line)){
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


for (int i = 3, j = 4; i,j < argPoints.size(); i+=3, j+=3) {               
    int x = stoi(argPoints[i]); 
    int y = stoi(argPoints[j]);
    mypoints.push_back(Point_2(x,y)); 
};


string algorithm = argv[6]; 

int edge_selection = stoi(argv[8]); 

bool max_area_selection, min_area_selection; 
if (edge_selection == 1) {
    max_area_selection = false;             //1.4416  1.68693  1.20027  london -----45
    min_area_selection = false; 
}else if (edge_selection == 2) {
    max_area_selection = false;             
    min_area_selection = true; 
}else if (edge_selection == 3) {
    max_area_selection = true;             
    min_area_selection = false;  
} else {
    cout << "wrong edge selection given from input. Can only give 1 or 2 or 3." << endl;
    EXIT_FAILURE;
}

string init = argv[10]; 

if (init == "1a") {
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

for (int i=0; i<mypoints.size(); i++)
    {
        cout << mypoints[i] << endl;
    }

for (int i=0; i<3; i++) {
    polyg_line.push_back(mypoints[0]);
    vertex_iterators.push_back(make_pair(mypoints[0],i)); 
    mypoints.erase(mypoints.begin()); 
}


Points result; 
Polygon_2 convex_h; 
vector <Segment_2> red_edges;

 
while (mypoints.size()) {
    convex_h = calc_convex_hull(polyg_line); 
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
            bool redEdgeOnPolyg = segmentIsOnPolygon(e,polyg_line);
            if (redEdgeOnPolyg) {                                   //if red edge already in polygonial line, that means it is replaceable and can be replaced immediatly
                insertOnPolygLine(e,polyg_line,vertex_iterators,mypoints[0]);   
                break;
            }else { 
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

}



//valia 

#include <iostream>
#include <fstream>
#include <string>

#include "includes/algorithms.hpp"
#include <CGAL/Simple_cartesian.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/property_map.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Polygon_2_algorithms.h>
#include <CGAL/Point_2.h>
#include <CGAL/Origin.h>

using namespace std; 
typedef CGAL::Simple_cartesian<double> K;
typedef K::Point_2 Point_2;
typedef CGAL::Polygon_2<K> Polygon_2;
typedef K::Segment_2 Segment_2;
typedef std::vector<Point_2> Points;
typedef std::vector <Segment_2> Segments;
using std::cout; using std::endl;

int main(int argc, char *argv[]){
    clock_t start, end;
    start = clock();
    std::vector<string> argPoints;

    ifstream infile(argv[2]);

    if(infile.is_open() && infile.good()){
        int current_line = 0;
        string line="";
        while(getline(infile,line)){
            // cout << "line" << endl;
            istringstream ss(line);
            string substr;
            while(getline(ss, substr, '\t')){
                argPoints.push_back(substr);
            }
       }
    }else{
        cout << "Error..this file not exist" << endl;
    }

    Points p;

    for(int i=3, j=4; i,j< argPoints.size(); i+=3, j+=3){
        int x = stoi(argPoints[i]);
        int y = stoi(argPoints[j]);
        p.push_back(Point_2(x,y));
    }

    int edge_selection=stoi(argv[8]);
    std::cout << "edge selection"<< std::endl;
    std::cout << edge_selection<< std::endl;
    //int edge_selection=3;
    Polygon_2 CV;
    CGAL::convex_hull_2( p.begin(), p.end(), std::back_inserter(CV) );  //computing the convex hull
    string algorithim = argv[6];
    Polygon_2 polyg;

    if(algorithim=="Convex_Hull") {polyg = Convex_Hull(edge_selection,p,CV);}
    end = clock();

    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    time_taken *=1000;

    std::cout << "Polygonization"<< std::endl;
    
    for(auto it = polyg.begin(); it!= polyg.end();++it){
        std::cout << *it << std::endl;
    }

    for(const Segment_2& e: polyg.edges()){
        std::cout << e << std::endl;
    }
   
    std::cout << "Algorithm: "<< algorithim << std::endl;
    std::cout << "area: " << polyg.area() << std::endl;
    std::cout << "ratio: " << polyg.area()/CV.area() << std::endl;
    cout << "Construction time: " << fixed << round(time_taken) << setprecision(5);
    cout << " ms " << endl;    
}