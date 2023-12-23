#pragma once
#include <iostream>
#include <vector>
using namespace std;

using Point3D = vector<double>;

class Node {
    public:
        Point3D point;
        Node * left;
        Node * right;

        Node(){}
        Node(const Point3D& point){
            left = nullptr;
            right = nullptr;
            this->point = point;
        }
        ~Node(){}
};

ostream& operator<<(ostream& os, const Point3D& point) {
    os << "(";
    for (int i=0; i<point.size(); i++)
        os << point[i] << ( i!=point.size()-1 ? "," : "");
    os << ")";
    return os;
}
