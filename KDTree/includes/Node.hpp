#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <iomanip>
using namespace std;

using Point3D = vector<double>;

class Node
{
public:
    Point3D point;
    Node *left;
    Node *right;

    Node() {}
    Node(const Point3D &point)
    {
        left = nullptr;
        right = nullptr;
        this->point = point;
    }
    ~Node()
    {
        Point3D().swap(point);
    }
};

double EuclideanDistance(const Point3D &p1, const Point3D &p2)
{
    if (p1.size() != p2.size())
        throw invalid_argument("Los puntos tienen dimensiones diferentes");
    double sum = 0;
    for (size_t i = 0; i < p1.size(); ++i)
        sum += pow(p1[i] - p2[i], 2);
    return sqrt(sum);
}

ostream &operator<<(ostream &os, const Point3D &point)
{
    os << "(";
    for (int i = 0; i < point.size(); i++)
        os << point[i] << (i != point.size() - 1 ? "," : "");
    os << ")";
    return os;
}
Point3D operator+(const Point3D &p1, const Point3D &p2)
{
    if (p1.size() != p2.size())
        throw invalid_argument("Los puntos tienen dimensiones diferentes");
    Point3D suma;
    for (size_t i = 0; i < p1.size(); ++i)
        suma.push_back(p1[i] + p2[i]);
    return suma;
}
Point3D operator/(const Point3D &point, int divisor)
{
    Point3D result;
    if (divisor != 0)
    {
        result.reserve(point.size());
        for (const auto &element : point)
            result.push_back(element / static_cast<double>(divisor));
    }
    else
        std::cerr << "Error: Division by zero" << std::endl;
    return result;
}
