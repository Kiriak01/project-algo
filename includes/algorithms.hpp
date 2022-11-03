#include <iostream>
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

Polygon_2 Convex_Hull(int edge_selection, Points p, Polygon_2 CV);