#include <iostream>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/algorithm.h>
#include "algorithms.hpp"

using namespace std; 
typedef CGAL::Simple_cartesian<double> K;
typedef K::Point_2 Point_2;
typedef CGAL::Polygon_2<K> Polygon_2;
typedef K::Segment_2 Segment_2;
//typedef K::Vertex_2 Vertex_2;
typedef std::istream_iterator<Point_2> point2_iterator;
typedef std::istream_iterator<Segment_2> segment2_iterator;
typedef std::vector<Point_2> Points;
typedef std::vector <Segment_2> Segments;
// using std::pair;
using std::cout; using std::endl;

bool is_visible(Segment_2 ed, Polygon_2 A, Point_2 x){
    Point_2 middle = CGAL::midpoint(ed);
    Segment_2 ps = Segment_2 (middle, x);   //this is a segment to the point x and the middle of its nearest segment of the polygon
    int count = 0;
    for(const Segment_2& e: A.edges()){     //check if this segment intersect with the other segments of the polygon,(count>1)   
        if(CGAL::do_intersect(ps, e)) count++;  
                    // std::cout << e << std::endl;
                    // std::cout << CGAL::do_intersect(ps, e) << std::endl;
    }
    if(count == 1){
        return true;
    }else{
        return false;
    }
}

int pos_min_area(Polygon_2 A, Point_2 x){  //returns the position of the polygonic line where we should insert x
    Segment_2 s;
    double pa ;
    // std::cout << "area" << std::endl;
    // std::cout << pa << std::endl;
    int pos=0, pos_s;   //pos = counts the position of the segments, pos_s =pos of the segment where if we insert x we have the minimum area.        
    for(const Segment_2& ed: A.edges()){    //for every segment of A , find those who are visible
        bool v=is_visible(ed,A,x);   
        if(v){  //segment ed of A is visible
            if(pos==1){ //if it is the first 
                A.insert(A.begin()+pos+1, x);   //insert x there 
                pa = A.area();      //find the area of A
                s = ed;
                pos_s = pos;        //find the position of the segment
                A.erase(A.begin()+pos+1);
            }else {  
                A.insert(A.begin()+pos+1, x);  //insert x to A
                if(A.area()<pa) {   //check if the area is less than before 
                    pa = A.area();  //change area
                    s = ed;
                    pos_s = pos;    
                }
                A.erase(A.begin()+pos+1);
            }
        }
        pos++;
    }
    return pos_s;
}

int pos_max_area(Polygon_2 A, Point_2 x){  //returns the position of the polygonic line where we should insert x
    Segment_2 s;
    double pa ;
    // std::cout << "area" << std::endl;
    // std::cout << pa << std::endl;
    int pos=0, pos_s;   //pos = counts the position of the segments, pos_s =pos of the segment where if we insert x we have the minimum area.        
    for(const Segment_2& ed: A.edges()){    //for every segment of A , find those who are visible
        bool v=is_visible(ed,A,x);
        if(v){  //segment ed of A is visible
            if(pos==1){ //if it is the first 
                A.insert(A.begin()+pos+1, x);   //insert x there 
                pa = A.area();      //find the area of A
                s = ed;
                pos_s = pos;        //find the position of the segment
                A.erase(A.begin()+pos+1);
            }else {  
                A.insert(A.begin()+pos+1, x);  //insert x to A
                if(A.area()>pa) {   //check if the area is less than before 
                    pa = A.area();  //change area
                    s = ed;
                    pos_s = pos;    
                }
                A.erase(A.begin()+pos+1);
            }
        }
        pos++;
    }
    return pos_s;
}

Polygon_2 Convex_Hull(int edge_selection, Points p, Polygon_2 CV){
    
    Polygon_2 A;    //CV=Convex Hull    A=Polygonic Line    I=Internal Points
    Points I;

    std::cout << "CONVEX HULL" << std::endl;
    for(auto it = CV.begin(); it!= CV.end();++it){
        std::cout << *it << std::endl;
    }
    //initialize the polygonic line, considering that it is the same with the convex hull at first
    for(auto it = CV.begin(); it!= CV.end();++it){
        A.push_back(*it);
    }
    std::cout << "POLYGONIC LINE" << std::endl;
    for(auto it = A.begin(); it!= A.end();++it){
        std::cout << *it << std::endl;
    }
    //finding the internal points 
    for(int i=0; i<p.size(); i++){
        bool b=false;
        for(auto it = CV.begin(); it!= CV.end();++it){
           if(*it == p[i]) b=true;
        }
        if(b == false) I.push_back(p[i]);     
    }

    std::cout << "INTERNAL POINTS" << std::endl;
    for(int i=0; i<I.size(); i++){
        cout << I[i] << endl;
    }
    std::vector<pair<Point_2,int>> vertex_iterators;

    for(int i=0; i<A.size(); i++){
        vertex_iterators.push_back(make_pair(A[i],i));
    }

    if(edge_selection==1 ){    //tuxaia epilogi akmis
        while(I.size()!=0){     //find internal points to the nearest edge until all of them have been inserted to A
            Segment_2 ed = A.edge(0);
            K::FT d;
            d = CGAL::squared_distance(I[0],ed);    
            // std::cout << "first distance" << std::endl;
            // std::cout << d << std::endl;
            Point_2 x = I[0];
            int position_x, position_e;
            Point_2 et;
            std::cout << "d=" << d << std::endl;
            for(const Segment_2& e: A.edges()){
                 for(int j=0; j<I.size(); j++){
                    if(CGAL::squared_distance(I[j], e) < d){
                        d = CGAL::squared_distance(I[j], e);
                        // std::cout << "distance" << endl;
                        // std::cout << d << std::endl;
                        x = I[j];
                        position_x = j;
                        ed = e;
                        et = e.target();
                        // std::cout << "target" <<std:: endl;
                        // std::cout<< et << std::endl;
                    }
                }
            }


            int pos;
            for(int i=0; i<vertex_iterators.size(); i++){
                if(et==vertex_iterators[i].first){
                    pos = vertex_iterators[i].second;
                } 
            }
            // std::cout << "POSITION EDGE" << std::endl;
            // std::cout << position_e << std::endl;

            // std::cout << "POINT x with the minimum distance" << std::endl;    //internal point with the minimum distance from the polygonic line
            // std::cout << x << std::endl;    

            // std::cout << "distance" << std::endl;
            // std::cout << d << std::endl;
            
            // std::cout << "EDGE"<< std::endl;
            // std::cout << ed << std::endl;

            bool is = ed.has_on(x);     //looking if the point in on the edge and we insert the point between this two points. 
            if(is == true ){     //if it is, we are insert it between the two points of the edge, because it means that the three of them are coolinear
                A.insert(A.begin()+pos, x);

                // std::cout << "IS ON THE SEGMENT" << std::endl;
            }else{
                //check if the nearest point is visible to its nearest segment              
                // std::cout << "IT ISN'T ONT THE SEGMENT" << std::endl; 
                bool v = is_visible(ed,A,x);
                if(v) {
                    // position_e=position_e+1;
                    // vi iter=A.begin()+position_e;
                    // std::cout << "visble" << std::endl;
                    A.insert(A.begin()+pos, x);
                }else {
                    Point_2 poi;           
                    for(const Segment_2& ed: A.edges()){
                        bool vis = is_visible(ed,A,x); 
                        if(vis) break;
                        poi=ed.target();
                    }
                    int pos1;
                    for(int i=0;i<vertex_iterators.size(); i++){
                        if(vertex_iterators[i].first==poi){
                            pos1 = vertex_iterators[i].second;
                        }
                    }
                    // vi iter=A.begin()+pos;
                    // std::cout << "visble" << std::endl;
                    A.insert(A.begin() + pos1, x);
                    // A.insert(A.+1, x);
                }
            }
            
            std::cout << "POLYGONIC LINE" << std::endl;
            for(auto it = A.begin(); it!= A.end();++it){
                std::cout << *it << std::endl;
            }
            
            I.erase(I.begin() + position_x);  //erase the point x from the internals as it is inserted to the polygonic line.
            if (I.size()!=0){
                std::cout << "INTERNAL POINTS" << std::endl;
                for(int i=0; i<I.size(); i++){
                    cout << I[i] << endl;
                }
            }else{
                std::cout << "NO MORE INTERNAL POINTS" << std::endl;
            }
            
       }
       return A;
    }else if(edge_selection == 2){  //min area
          while(I.size()!=0){     //find internal points to the nearest edge until all of them have been inserted to A
            Segment_2 ed = A.edge(1);
            K::FT d;
            d = CGAL::squared_distance(I[0],ed);    
            // std::cout << "first distance" << std::endl;
            // std::cout << d << std::endl;
            Point_2 x = I[0];
            int position_x, position_e, i=0;

            for(const Segment_2& e: A.edges()){
                 for(int j=0; j<I.size(); j++){
                    if(CGAL::squared_distance(I[j], e) < d){
                        d = CGAL::squared_distance(I[j], e);
                        // std::cout << d << std::endl;
                        x = I[j];
                        position_x = j;
                        ed = e;
                        position_e = i;
                    }
                }
                ++i;
            }

            // std::cout << "POINT x with the minimum distance" << std::endl;    //internal point with the minimum distance from the polygonic line
            // std::cout << x << std::endl;    

            // std::cout << "EDGE"<< std::endl;
            // std::cout << ed << std::endl;

            bool is = ed.has_on(x);     //looking if the point in on the edge and we insert the point between this two points. 

            if(is == true){     //if it is, we are insert it between the two points of the edge, because it means that the three of them are coolinear
                A.insert((A.begin()+position_e)++, x);
                std::cout << "IS ON THE SEGMENT" << std::endl;
            }else{
                std::cout << "IT ISN'T ONT THE SEGMENT" << std::endl; 
               int pos_s=pos_min_area(A,x);
                A.insert(A.begin()+pos_s+1, x);
            }

            // std::cout << "last area" << std::endl;
            // std::cout << A.area() << std::endl;
            // std::cout << "POLYGONIC LINE" << std::endl;
            // for(auto it = A.begin(); it!= A.end();++it){
            //     std::cout << *it << std::endl;
            // }
            
            I.erase(I.begin() + position_x);  //erase the point x from the internals as it is inserted to the polygonic line.
            if (I.size()!=0){
                std::cout << "INTERNAL POINTS" << std::endl;
                for(int i=0; i<I.size(); i++){
                    cout << I[i] << endl;
                }
            }else{
                std::cout << "NO MORE INTERNAL POINTS" << std::endl;
            }
            
       }   
       return A;    
    }else{ //max area
    //find internal points to the nearest edge until all of them have been inserted to A
       while(I.size()!=0){     //find internal points to the nearest edge until all of them have been inserted to A
            Segment_2 ed = A.edge(1);
            K::FT d;
            d = CGAL::squared_distance(I[0],ed);    
            // std::cout << "first distance" << std::endl;
            // std::cout << d << std::endl;
            Point_2 x = I[0];
            int position_x, position_e, i=0;

            for(const Segment_2& e: A.edges()){
                 for(int j=0; j<I.size(); j++){
                    if(CGAL::squared_distance(I[j], e) < d){
                        d = CGAL::squared_distance(I[j], e);
                        // std::cout << d << std::endl;
                        x = I[j];
                        position_x = j;
                        ed = e;
                        position_e = i;
                    }
                }
                ++i;
            }

            // std::cout << "POINT x with the minimum distance" << std::endl;    //internal point with the minimum distance from the polygonic line
            // std::cout << x << std::endl;    

            // std::cout << "EDGE"<< std::endl;
            // std::cout << ed << std::endl;

            bool is = ed.has_on(x);     //looking if the point in on the edge and we insert the point between this two points. 

            if(is == true ){     //if it is, we are insert it between the two points of the edge, because it means that the three of them are coolinear
                A.insert(A.begin()+position_e+1, x);
                std::cout << "IS ON THE SEGMENT" << std::endl;
            }else{
                std::cout << "IT ISN'T ONT THE SEGMENT" << std::endl; 
                int pos_s=pos_max_area(A,x);
                A.insert(A.begin()+pos_s+1, x);
            }

            // std::cout << "last area" << std::endl;
            // std::cout << A.area() << std::endl;
            // std::cout << "POLYGONIC LINE" << std::endl;
            // for(auto it = A.begin(); it!= A.end();++it){
            //     std::cout << *it << std::endl;
            // }
            
            I.erase(I.begin() + position_x);  //erase the point x from the internals as it is inserted to the polygonic line.
            if (I.size()!=0){
                std::cout << "INTERNAL POINTS" << std::endl;
                for(int i=0; i<I.size(); i++){
                    cout << I[i] << endl;
                }
            }else{
                std::cout << "NO MORE INTERNAL POINTS" << std::endl;
            }
            
       }  
       return A;
    }   
}