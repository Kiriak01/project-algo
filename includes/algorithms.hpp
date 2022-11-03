#include <CGAL/convex_hull_2.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Convex_hull_traits_adapter_2.h>
#include <CGAL/property_map.h>
#include <CGAL/Polygon_2_algorithms.h>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/intersections.h>
#include <algorithm>   
#include <vector>
#include <cmath>


typedef CGAL::Simple_cartesian<double> Kernel;
typedef CGAL::Polygon_2<Kernel> Polygon_2;
typedef Kernel::Point_2 Point_2;
typedef Kernel::Segment_2 Segment_2;
typedef std::vector<Point_2> Points;
typedef Kernel::Intersect_2 Intersect_2;
typedef CGAL::Triangle_2<Kernel> Triangle_2;

Polygon_2 calc_convex_hull(Polygon_2); 
bool pointIsOnPolygon(Point_2, Polygon_2);  
bool segmentIsOnPolygon(Segment_2, Polygon_2);
int findIterator(std::vector<std::pair<Point_2,int>>, Point_2);
void reform(std::vector<std::pair<Point_2,int>>&,Polygon_2);
Segment_2 findReplaceableEdge(Polygon_2,Segment_2, Point_2,std::vector<std::pair<Point_2,int>>&, bool, bool); 
void insertOnPolygLine(Segment_2, Polygon_2&, std::vector<std::pair<Point_2,int>>&, Point_2); 
Segment_2 getMaxEdge(std::vector<Segment_2>, Polygon_2,std::vector<std::pair<Point_2,int>>&, Point_2);
Segment_2 getMinEdge(std::vector<Segment_2>, Polygon_2,std::vector<std::pair<Point_2,int>>&, Point_2);
bool sortbysecDec(const Point_2& , const Point_2&); 
bool sortbysecInc(const Point_2&, const Point_2&);  