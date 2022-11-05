#include <iostream>
#include <fstream>
#include <string>

#include "includes/algorithms.hpp"
#include <CGAL/Simple_cartesian.h>
#include <CGAL/squared_distance_2.h> 
#include <CGAL/convex_hull_2.h>
#include <CGAL/property_map.h>
#include <CGAL/intersections.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Polygon_2_algorithms.h>
#include <CGAL/Point_2.h>
#include <CGAL/Origin.h>

using namespace std; 
typedef CGAL::Simple_cartesian<double> K;
typedef K::Point_2 Point_2;
typedef CGAL::Polygon_2<K> Polygon_2;
typedef K::Segment_2 Segment_2;
typedef std::istream_iterator<Point_2> point2_iterator;
typedef std::istream_iterator<Segment_2> segment2_iterator;
typedef std::vector<Point_2> Points;
typedef std::vector <Segment_2> Segments;
typedef std::vector<Point_2>::iterator pveciterator;
typedef std::vector<Segment_2>::iterator sveciterator;
using std::cout; using std::endl;

int main(int argc, char *argv[]){
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

    // Points p;
    // p.push_back(Point_2(0,0));
    // p.push_back(Point_2(2,2));
    // p.push_back(Point_2(3,1));
    // p.push_back(Point_2(4,0));
    // //p.push_back(Point_2(4,1));
    // p.push_back(Point_2(6,1));
    // p.push_back(Point_2(6,2));
    // p.push_back(Point_2(8,0));

    // std::cout << "OUR  SET  OF POINTS " << std::endl;

    // for(int i=0; i<p.size(); i++){
    //     cout << p[i] << endl;
    // }

    int edge_selection=stoi(argv[8]);
    std::cout << "edge selection"<< std::endl;
    std::cout << edge_selection<< std::endl;
    //int edge_selection=3;
    Polygon_2 CV;
    CGAL::convex_hull_2( p.begin(), p.end(), std::back_inserter(CV) );  //computing the convex hull
    string algorithim = argv[6];
    Polygon_2 polyg;

    if(algorithim=="Convex_Hull") {polyg = Convex_Hull(edge_selection,p,CV);}
    //polyg = Convex_Hull(edge_selection,p,CV);

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
}