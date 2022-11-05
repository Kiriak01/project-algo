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
