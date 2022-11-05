#include "algorithms.hpp"
#include <iostream>
#include <vector>
using namespace std; 



Polygon_2 calc_convex_hull(Polygon_2 polygon) {
    Points result; 
    Polygon_2 convex_hull; 
    CGAL::convex_hull_2(polygon.begin(), polygon.end(), std::back_inserter(result));             
    for(auto it = result.begin(); it!= result.end();++it) { 
        convex_hull.push_back(*it);
    }
    return convex_hull; 
}

bool pointIsOnPolygon(Point_2 p, Polygon_2 polygon) {
    for(const Point_2& point : polygon.vertices()){
        if (point == p) {
            return true; 
        }
    }
    return false; 
}

bool segmentIsOnPolygon(Segment_2 p, Polygon_2 polygon) {
    for(const Segment_2& segment : polygon.edges()){
        Segment_2 reverse_seg(segment.target(),segment.source()); 
        if ((p == segment) || (p == reverse_seg)) {
            return true; 
        }
    }
    return false; 
}

int findIterator(std::vector<std::pair<Point_2,int>> vertex_iterators, Point_2 point) {
    for(int i = 0; i < vertex_iterators.size(); i++)
    {
        if (point == vertex_iterators[i].first) {
            return vertex_iterators[i].second; 
        }
    }
    return -1;
}

void reform(std::vector<std::pair<Point_2,int>>& vertex_iterators ,Polygon_2 polygon) {
    vertex_iterators.clear(); 
    int i = 0;
    for (const Point_2& poly_vertex : polygon.vertices()) {
        vertex_iterators.push_back(make_pair(poly_vertex,i));
        i++; 
    }

}

Segment_2 findReplaceableEdge(Polygon_2 polygon, Segment_2 red_edge, Point_2 p,std::vector<std::pair<Point_2,int>>& vertex_iterators, bool max_area_selection, bool min_area_selection) {
    vector<Segment_2> hidden_edges; 
    vector<Segment_2> max_area_edges; 
    vector<Segment_2> min_area_edges; 
    for (const Segment_2& p_edge : polygon.edges()) {
        if ( (p_edge.source() == red_edge.source()) || (p_edge.source() == red_edge.target()) || (p_edge.target() == red_edge.source()) || (p_edge.target() == red_edge.target())){
            hidden_edges.push_back(p_edge); 
         }
    }
    for (const Segment_2& hidden_edge : hidden_edges) {
        Segment_2 pToMidPoint(p,midpoint(hidden_edge.source(),hidden_edge.target())); 
        int counter = 0;    
        for (const Segment_2& e2 : polygon.edges()) {
            if (hidden_edge == e2) {
                continue; 
            }else if (intersection(pToMidPoint,e2)) {  
                counter++;                                                   
                continue;                                                               
            }else {
            }
        }
        if (counter == 0) {
            if (max_area_selection) {
                max_area_edges.push_back(hidden_edge);
                continue; 
            }else if (min_area_selection) {
                min_area_edges.push_back(hidden_edge);
                continue; 
            }else {
            return hidden_edge;      //rand selection of visible edge
            } 
        }
    }
    if( max_area_selection) {
        Segment_2 max_edge = getMaxEdge(max_area_edges,polygon,vertex_iterators,p);
        return max_edge; 
    }else if (min_area_selection) {
        Segment_2 min_edge = getMinEdge(min_area_edges,polygon,vertex_iterators,p); 
        return min_edge;
    }
}

Segment_2 getMaxEdge(std::vector<Segment_2> max_edges, Polygon_2 polygon,std::vector<std::pair<Point_2,int>>& vertex_iterators, Point_2 point) {
    Segment_2 max_edge = max_edges[0]; 
    int sourceIt,targetIt = -1; 
    sourceIt = findIterator(vertex_iterators,max_edge.source());  
    targetIt = findIterator(vertex_iterators,max_edge.target());  
    int max_area; 
    if ((sourceIt!=-1) && (targetIt!=-1)) {
        int maxIt = max(sourceIt,targetIt); 
        polygon.insert(polygon.begin() + maxIt , point); 
        max_area = abs(polygon.area());
        polygon.erase(polygon.begin()+ maxIt); 
    } else { 
    if (sourceIt != -1) {
        polygon.insert(polygon.begin() + sourceIt , point); 
        max_area = abs(polygon.area());
        polygon.erase(polygon.begin()+ sourceIt);  
    }
    }

    for (const Segment_2& s : max_edges){
        if (s == max_edges[0]){
            continue;
        }
        int sSourceIt, sTargetIt = -1; 
        sSourceIt = findIterator(vertex_iterators,s.source());  
        sTargetIt = findIterator(vertex_iterators,s.target());  
        int s_area; 
        if ((sSourceIt!=-1) && (sTargetIt!=-1)) {
            int maxIt = max(sSourceIt,sTargetIt); 
            polygon.insert(polygon.begin() + maxIt , point); 
            s_area = abs(polygon.area());
            if (s_area > max_area) {
                max_area = s_area; 
                max_edge = s; 
            }
            polygon.erase(polygon.begin()+ maxIt); 
        } else { 
        if (sourceIt != -1) {
            polygon.insert(polygon.begin() + sourceIt , point); 
            s_area = abs(polygon.area());
            if (s_area > max_area) {
                max_area = s_area; 
                max_edge = s; 
            }
            polygon.erase(polygon.begin()+ sourceIt);  
        }
        }
    }
    return max_edge; 
}


Segment_2 getMinEdge(std::vector<Segment_2> min_edges, Polygon_2 polygon,std::vector<std::pair<Point_2,int>>& vertex_iterators, Point_2 point) {
    Segment_2 min_edge = min_edges[0]; 
    int sourceIt,targetIt = -1; 
    sourceIt = findIterator(vertex_iterators,min_edge.source());  
    targetIt = findIterator(vertex_iterators,min_edge.target());  
    int min_area; 
    if ((sourceIt!=-1) && (targetIt!=-1)) {
        int maxIt = max(sourceIt,targetIt); 
        polygon.insert(polygon.begin() + maxIt , point); 
        min_area = abs(polygon.area());
        polygon.erase(polygon.begin()+ maxIt); 
    } else { 
    if (sourceIt != -1) {
        polygon.insert(polygon.begin() + sourceIt , point); 
        min_area = abs(polygon.area());
        polygon.erase(polygon.begin()+ sourceIt);  
    }
    }

    for (const Segment_2& s : min_edges){
        if (s == min_edges[0]){
            continue;
        }
        int sSourceIt, sTargetIt = -1; 
        sSourceIt = findIterator(vertex_iterators,s.source());  
        sTargetIt = findIterator(vertex_iterators,s.target());  
        int s_area; 
        if ((sSourceIt!=-1) && (sTargetIt!=-1)) {
            int maxIt = max(sSourceIt,sTargetIt); 
            polygon.insert(polygon.begin() + maxIt , point); 
            s_area = abs(polygon.area());
            if (s_area < min_area) {
                min_area = s_area; 
                min_edge = s; 
            }
            polygon.erase(polygon.begin()+ maxIt); 
        } else { 
        if (sourceIt != -1) {
            polygon.insert(polygon.begin() + sourceIt , point); 
            s_area = abs(polygon.area());
            if (s_area < min_area) {
                min_area = s_area; 
                min_edge = s; 
            }
            polygon.erase(polygon.begin()+ sourceIt);  
        }
        }
    }
    return min_edge; 
}



void insertOnPolygLine(Segment_2 e, Polygon_2& polygon, std::vector<std::pair<Point_2,int>>& vertex_iterators, Point_2 point) {
    reform(vertex_iterators,polygon);
    int sourceIt,targetIt = -1; 
    sourceIt = findIterator(vertex_iterators,e.source());  
    targetIt = findIterator(vertex_iterators,e.target());  
    if ((sourceIt!=-1) && (targetIt!=-1)) {
        int maxIt = max(sourceIt,targetIt); 
        polygon.insert(polygon.begin() + maxIt , point); 
    } else { 
    if (sourceIt != -1) {
        polygon.insert(polygon.begin() + sourceIt , point); 
    }
    }
    reform(vertex_iterators, polygon);
}

bool sortbysecInc(const Point_2 &a,
              const Point_2 &b)
{
    
    return (a.y() > b.y());                   
}

bool sortbysecDec(const Point_2 &a,
              const Point_2 &b)
{
    
    return (a.y() < b.y());                   
}


//valia 

#include <iostream>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/algorithm.h>
#include "algorithms.hpp"
 
using namespace std;
typedef CGAL::Simple_cartesian<double> K;
typedef K::Point_2 Point_2;
typedef CGAL::Polygon_2<K> Polygon_2;
typedef K::Segment_2 Segment_2;
typedef std::vector<Point_2> Points;
typedef std::vector <Segment_2> Segments;
using std::cout; using std::endl;

//function for finding visible edges
bool is_visible(Segment_2 ed, Polygon_2 A, Point_2 x){
    Point_2 middle = CGAL::midpoint(ed);
    Segment_2 ps = Segment_2 (middle, x);   //this is a segment to the point x and the middle of its nearest segment of the polygon
    int count = 0;
    for(const Segment_2& e: A.edges()){     //check if this segment intersect with the other segments of the polygon,(count>1)   
        if(CGAL::do_intersect(ps, e)) count++;  
    }
    if(count == 1){
        return true;
    }else{
        return false;
    }
}

//function for finding the position of the polygon or set of points we want to insert or erase a point
int position_to_replace(std::vector<std::pair<Point_2,int>> vertex_iterators, Point_2 x) {
    for(int i = 0; i<vertex_iterators.size(); i++){
        if ( x == vertex_iterators[i].first){
            return vertex_iterators[i].second; 
        }
    }
    return -1;
}

//function for change the vertex iterators after insert/erase a point for a polygon
void change(std::vector<std::pair<Point_2,int>>& vertex_iterators ,Polygon_2 polygon) {
    vertex_iterators.clear(); 
    int i = 0;
    for (const Point_2& v: polygon.vertices()) {
        vertex_iterators.push_back(make_pair(v,i));
        i++; 
    }
}

//function for change the vertex iterators after insert/erase a point for a set of points
void change_P(std::vector<std::pair<Point_2,int>>& vertex_iterators ,Points p) {
    vertex_iterators.clear();
    for (int i=0; i<p.size(); i++) {
        vertex_iterators.push_back(make_pair(p[i],i));
    }
}

//this function returns the position of the polygonic line where we should insert x
int pos_min_area(Polygon_2 A, Point_2 x, std::vector<std::pair<Point_2,int>>& vertex_iterators){
    double pa ;
    int i=0, pos_s;   //pos = counts the position of the segments, pos_s =pos of the segment where if we insert x we have the minimum area.        
    for(const Segment_2& ed : A.edges()){    //for every segment of A , find those who are visible
        bool v=is_visible(ed,A,x);   
        if(v){  //segment ed of A is visible
            if(i==1){ //if it is the first 
                int pi = position_to_replace(vertex_iterators, ed.target());
                A.insert(A.begin()+pi, x);   //insert x there 
                change(vertex_iterators,A);
                pa = A.area();      //find the area of A
                pos_s = pi;
                A.erase(A.begin()+pi);
                change(vertex_iterators,A);
            }else{  
                int pi = position_to_replace(vertex_iterators, ed.target());
                A.insert(A.begin()+pi, x);   //insert x there
                change(vertex_iterators,A); 
                if(A.area()<pa) {   //check if the area is less than before 
                    pa = A.area();  //change area
                    pos_s = pi;    
                }
                A.erase(A.begin()+pi);
                change(vertex_iterators,A);
            }
        }
        i++;
    }
    return pos_s;
}

//this function returns the position of the polygonic line where we should insert x
int pos_max_area(Polygon_2 A, Point_2 x, std::vector<std::pair<Point_2,int>>& vertex_iterators){ 
    double pa ;
    int i=0, pos_s;   //pos = counts the position of the segments, pos_s =pos of the segment where if we insert x we have the minimum area.        
    for(const Segment_2& ed : A.edges()){    //for every segment of A , find those who are visible
        bool v=is_visible(ed,A,x);   
        if(v){  //segment ed of A is visible
            if(i==1){ //if it is the first 
                int pi = position_to_replace(vertex_iterators, ed.target());
                A.insert(A.begin()+pi, x);   //insert x there
                pa = A.area();      //find the area of A
                pos_s = pi;
                A.erase(A.begin()+pi);
            }else{  
                int pi = position_to_replace(vertex_iterators, ed.target());
                A.insert(A.begin()+pi, x);   //insert x there 
                if(A.area()>pa) {   //check if the area is less than before 
                    pa = A.area();  //change area
                    pos_s = pi;    
                }
                A.erase(A.begin()+pi);
            }
        }
        i++;
    }
    return pos_s;
}

//FUNCTION FOR COMPUTING OUR POLYGON using convex hull
Polygon_2 Convex_Hull(int edge_selection, Points p, Polygon_2 CV){
    Polygon_2 A;    //CV=Convex Hull    A=Polygonic Line    I=Internal Points
    Points I;
    //initialize the polygonic line, considering that it is the same with the convex hull at first
    for(auto it = CV.begin(); it!= CV.end();++it){
        A.push_back(*it);
    }
    //finding the internal points 
    for(int i=0; i<p.size(); i++){
        bool b=false;
        for(auto it = CV.begin(); it!= CV.end();++it){
           if(*it == p[i]) b=true;
        }
        if(b == false) I.push_back(p[i]);     
    }

    std::vector<pair<Point_2,int>> vertex_iterators;
    std::vector<pair<Point_2,int>> vertex_iterators_i;

    for(int i=0; i<A.size(); i++){  //iterators for the polygonic line
        vertex_iterators.push_back(make_pair(A[i],i));
    }
     for(int i=0; i<I.size(); i++){ //iterators for the internal points
        vertex_iterators_i.push_back(make_pair(I[i],i));
    }

    if(edge_selection==1){    //tuxaia epilogi akmis
        while(I.size()!=0){     //find internal points to the nearest edge until all of them have been inserted to A
            Segment_2 ed = A.edge(0);
            K::FT d;
            d = CGAL::squared_distance(I[0],ed);    
            Point_2 x = I[0];
            for(const Segment_2& e: A.edges()){
                 for(int j=0; j<I.size(); j++){
                    if(CGAL::squared_distance(I[j], e) < d){
                        d = CGAL::squared_distance(I[j], e);
                        x = I[j];
                        ed = e;
                    }
                }
            }

            int pos=position_to_replace(vertex_iterators,ed.target());

            bool is = ed.has_on(x);     //looking if the point in on the edge and we insert the point between this two points. 
            if(is == true ){     //if it is, we are insert it between the two points of the edge, because it means that the three of them are coolinear
                A.insert(A.begin()+pos, x);
                change(vertex_iterators,A);
            }else{
                //check if the nearest point is visible to its nearest segment              
                bool v = is_visible(ed,A,x);
                if(v) {
                    A.insert(A.begin()+pos, x);
                    change(vertex_iterators,A);
                }else {
                    Point_2 poi;           
                    for(const Segment_2& ed: A.edges()){
                        bool vis = is_visible(ed,A,x); 
                        if(vis) break;
                        poi=ed.target();
                    }
                    int pos1=position_to_replace(vertex_iterators,poi);
                    A.insert(A.begin() + pos1, x);
                    change(vertex_iterators,A);
                }
            }
            
            int position_x = position_to_replace(vertex_iterators_i,x);
            I.erase(I.begin() + position_x);  //erase the point x from the internals as it is inserted to the polygonic line.
            change_P(vertex_iterators_i,I);  
       }
       return A;
    }else if(edge_selection == 2){  //min area
          while(I.size()!=0){     //find internal points to the nearest edge until all of them have been inserted to A
            Segment_2 ed = A.edge(0);
            K::FT d;
            d = CGAL::squared_distance(I[0],ed);    
            Point_2 x = I[0];
            for(const Segment_2& e: A.edges()){
                 for(int j=0; j<I.size(); j++){
                    if(CGAL::squared_distance(I[j], e) < d){
                        d = CGAL::squared_distance(I[j], e);
                        x = I[j];
                        ed = e;
                    }
                }
            }
            int pos = position_to_replace(vertex_iterators,ed.target());
            bool is = ed.has_on(x);     //looking if the point in on the edge and we insert the point between this two points. 
            if(is == true){     //if it is, we are insert it between the two points of the edge, because it means that the three of them are coolinear
                A.insert(A.begin()+pos, x);
                change(vertex_iterators,A);
            }else{
                int pos_s=pos_min_area(A,x,vertex_iterators);
                A.insert(A.begin()+pos, x);
                change(vertex_iterators,A);
            }
            int position_x =position_to_replace(vertex_iterators_i,x);
            I.erase(I.begin() + position_x);  //erase the point x from the internals as it is inserted to the polygonic line.
            change_P(vertex_iterators_i,I);
       }   
       return A;    
    }else if(edge_selection==3){ //max area
         while(I.size()!=0){     //find internal points to the nearest edge until all of them have been inserted to A
            Segment_2 ed = A.edge(0);
            K::FT d;
            d = CGAL::squared_distance(I[0],ed);    
            Point_2 x = I[0];
            for(const Segment_2& e: A.edges()){
                 for(int j=0; j<I.size(); j++){
                    if(CGAL::squared_distance(I[j], e) < d){
                        d = CGAL::squared_distance(I[j], e);
                        x = I[j];
                        ed = e;
                    }
                }
            }
            int pos = position_to_replace(vertex_iterators,ed.target());
            bool is = ed.has_on(x);     //looking if the point in on the edge and we insert the point between this two points. 
            if(is == true){     //if it is, we are insert it between the two points of the edge, because it means that the three of them are coolinear
                A.insert(A.begin()+pos, x);
                change(vertex_iterators,A);
            }else{ 
                int pos_s=pos_max_area(A,x,vertex_iterators);
                A.insert(A.begin()+pos, x);
                change(vertex_iterators,A);
            }

            int position_x =position_to_replace(vertex_iterators_i,x);
            I.erase(I.begin() + position_x);  //erase the point x from the internals as it is inserted to the polygonic line.
            change_P(vertex_iterators_i,I); 
        } 
       return A;    
    }else{
        std::cout << "Enter 1,2 or 3 for edge selection" << std::endl;
        return A;
    }
}