#include <iostream>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/property_map.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Point_2.h>

using namespace std; 
typedef CGAL::Simple_cartesian<double> K;
typedef K::Point_2 Point_2;
typedef CGAL::Polygon_2<K> Polygon_2;
typedef std::vector<Point_2> Points;
using std::cout; using std::endl;

Polygon_2 Convex_Hull(int edge_selection, Points p, Polygon_2 CV);
