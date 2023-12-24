#ifndef KDTREE_HPP
#define KDTREE_HPP

#include "../Node/node.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <iomanip>

namespace kdt
{
    template <int dimension>
    class KDTree
    {
    private:
        Node *root;

    public:
        KDTree() : root(nullptr) {}
        ~KDTree()
        {
            delete root;
            root = nullptr;
        }
        void insert(Node point)
        {
            root = insertRecursivo(root, point);
        }
        bool search(Point3D point)
        {
            return searchRecursivo(root, point);
        }
        void print()
        {
            printRecursive(root);
        }
        std::vector<Point3D> searchKNN(Point3D point, int k)
        {
            k = k + 1;
            std::priority_queue<std::pair<double, Node *>> nearestNeighbors;
            KNNRecursive(root, point, k, nearestNeighbors, 0);
            std::vector<Point3D> kNeighbors;
            while (!nearestNeighbors.empty())
            {
                kNeighbors.push_back(nearestNeighbors.top().second->point);
                nearestNeighbors.pop();
            }
            if (!kNeighbors.empty())
                kNeighbors.pop_back();
            return kNeighbors;
        }
        std::priority_queue<std::pair<double, Node *>> searchKNN2(Point3D point, int k)
        {
            k = k + 1;
            std::priority_queue<std::pair<double, Node *>> nearestNeighbors;
            KNNRecursive(root, point, k, nearestNeighbors, 0);
            return nearestNeighbors;
        }

    protected:
        Node *insertRecursivo(Node *current, Node node, int depth = 0)
        {
            if (current == nullptr)
                return new Node(node);
            int axis = depth % dimension;
            if (node.point[axis] < current->point[axis])
                current->left = insertRecursivo(current->left, node, depth + 1);
            else
                current->right = insertRecursivo(current->right, node, depth + 1);
            return current;
        }
        bool searchRecursivo(Node *node, Point3D point, int depth = 0)
        {
            if (node == nullptr)
                return false;
            if (node->point == point)
                return true;
            int axis = depth % dimension;
            if (point[axis] < node->point[axis])
                return searchRecursivo(node->left, point, depth + 1);
            return searchRecursivo(node->right, point, depth + 1);
        }
        void printRecursive(Node *node, int depth = 0)
        {
            if (node == nullptr)
                return;
            printRecursive(node->left, depth + 1);
            std::cout << node->point << " ";
            printRecursive(node->right, depth + 1);
        }

        double distanceL2(const Point3D &p1, const Point3D &p2)
        {
            double distancia = 0.0;
            for (int i = 0; i < p1.size(); i++)
                distancia += pow(p1[i] - p2[i], 2);
            return sqrt(distancia);
        }
        void KNNRecursive(Node *node, const Point3D &point, int k, std::priority_queue<std::pair<double, Node *>> &nearestNeighbors, int depth = 0)
        {
            if (node == nullptr)
                return;
            int axis = depth % point.size();
            double distance = distanceL2(point, node->point);
            if (nearestNeighbors.size() < k || distance < nearestNeighbors.top().first)
            {
                if (nearestNeighbors.size() == k)
                    nearestNeighbors.pop();
                nearestNeighbors.push({distance, node});
            }

            if (point[axis] < node->point[axis])
            {
                KNNRecursive(node->left, point, k, nearestNeighbors, depth + 1);
                if (nearestNeighbors.size() < k || abs(node->point[axis] - point[axis]) < nearestNeighbors.top().first)
                    KNNRecursive(node->right, point, k, nearestNeighbors, depth + 1);
            }
            else
            {
                KNNRecursive(node->right, point, k, nearestNeighbors, depth + 1);
                if (nearestNeighbors.size() < k || abs(node->point[axis] - point[axis]) < nearestNeighbors.top().first)
                    KNNRecursive(node->left, point, k, nearestNeighbors, depth + 1);
            }
        }
        void KNNRecursive2(Node *current, const Point3D &point, int k,
                           std::priority_queue<std::pair<double, Node *>> &nearestNeighbors, int depth = 0)
        {
            if (current == nullptr)
                return;
            int axis = depth % dimension;
            double distance = distanceL2(current->point, point);
            nearestNeighbors.push({distance, current});
            if (nearestNeighbors.size() > k)
                nearestNeighbors.pop();
            Node *first, *second;
            if (point[axis] < current->point[axis])
            {
                first = current->left;
                second = current->right;
            }
            else
            {
                first = current->right;
                second = current->left;
            }
            KNNRecursive2(first, point, k, nearestNeighbors, depth + 1);
            if (fabs(point[axis] - current->point[axis]) <= nearestNeighbors.top().first)
                KNNRecursive2(second, point, k, nearestNeighbors, depth + 1);
        }
    };

}
#endif // KDTREE_HPP
