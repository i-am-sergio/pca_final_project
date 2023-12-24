#pragma once
#include <iostream>
#include <vector>
using namespace std;

using Point3D = vector<double>;

class Node
{
public:
    string PointID, data;
    Point3D point;
    Node *left;
    Node *right;

    Node() {}
    Node(const Point3D &point, const string &PointID, const string &data)
    {
        left = nullptr;
        right = nullptr;
        this->point = point;
        this->PointID = PointID;
        this->data = data;
    }
    ~Node() {}
    friend ostream &operator<<(ostream &os, const Node &node)
    {
        os << "PointID: " << node.PointID << ", data: " << node.data << ", point: [";
        for (size_t i = 0; i < node.point.size(); ++i)
        {
            os << node.point[i];
            if (i != node.point.size() - 1)
                os << ", ";
        }
        os << "]";
        return os;
    }
};

ostream &operator<<(ostream &os, const Point3D &point)
{
    os << "(";
    for (int i = 0; i < point.size(); i++)
        os << point[i] << (i != point.size() - 1 ? "," : "");
    os << ")";
    return os;
}
