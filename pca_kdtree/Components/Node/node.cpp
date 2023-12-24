#include "node.hpp"

Node::Node() : left(nullptr), right(nullptr) {}

Node::Node(const Point3D &point, const std::string &PointID, const std::string &data)
    : point(point), PointID(PointID), data(data), left(nullptr), right(nullptr) {}

Node::~Node() {}

std::ostream &operator<<(std::ostream &os, const Node &node)
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

std::ostream &operator<<(std::ostream &os, const Node::Point3D &point)
{
    os << "(";
    for (size_t i = 0; i < point.size(); ++i)
        os << point[i] << (i != point.size() - 1 ? "," : "");
    os << ")";
    return os;
}
