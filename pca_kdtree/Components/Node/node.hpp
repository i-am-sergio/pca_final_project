#ifndef NODE_HPP
#define NODE_HPP
#include <iostream>
#include <vector>

using Point3D = std::vector<long double>;

class Node
{
public:
    using Point3D = std::vector<long double>;
    std::string PointID, data;
    Point3D point;
    Node *left;
    Node *right;

    Node();
    Node(const Point3D &point, const std::string &PointID, const std::string &data);
    ~Node();
    friend std::ostream &operator<<(std::ostream &os, const Node &node);
};

std::ostream &operator<<(std::ostream &os, const Point3D &point);
#endif // NODE_HPP