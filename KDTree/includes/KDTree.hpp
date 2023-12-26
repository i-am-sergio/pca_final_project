#pragma once
#include "Node.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <iomanip>
using namespace std;


namespace kdt {

    template <int dimension>
    class KDTree {
        private:
            Node * root;

        public:
            KDTree(){
                root = nullptr;
            }
            ~KDTree(){
                delete root; 
                root = nullptr;
            }
            void insert(Point3D point){
                root = insertRecursivo(root, point);
            }
            bool search(Point3D point){
                return searchRecursive(root, point);
            }
            void print(){
                printRecursive(root);
            }

            vector<Point3D> searchKNN(Point3D point, int k) {
                k = k+1;
                priority_queue<pair<double, Node*>> nearestNeighbors;
                KNNRecursive(root,point,k,nearestNeighbors,0);
                vector<Point3D> kNeighbors;
                while(!nearestNeighbors.empty()){
                    kNeighbors.push_back(nearestNeighbors.top().second->point);
                    nearestNeighbors.pop();
                }
                if(!kNeighbors.empty()) kNeighbors.pop_back();
                return kNeighbors;
            }

            priority_queue<pair<double, Node*>> searchKNN2(Point3D point, int k) {
                k = k+1;
                priority_queue<pair<double, Node*>> nearestNeighbors;
                KNNRecursive(root,point,k,nearestNeighbors,0);
                return nearestNeighbors;
            }
            void deleteNode(Point3D point){
                this->root = deleteNodeRec(this->root, point, 0);
            }

        protected:
            /*
            * `insertRecursivo` es una función recursiva que inserta un punto en un KDTree.
            * @param current: el nodo actual en el que se encuentra la recursión.
            * @param point: el punto a insertar.
            * @param depth: la profundidad actual en la que se encuentra la recursión.
            * @return: el nodo actualizado.
            * @complexity: O(log(n))
            */
            Node * insertRecursivo(Node * current, Point3D point, int depth = 0){
                if(current == nullptr){
                    return new Node(point);
                }
                
                int axis = depth % dimension;

                if (point[axis] < current->point[axis]) {
                    current->left = insertRecursivo(current->left, point, depth+1);
                } else {
                    current->right = insertRecursivo(current->right, point, depth+1);
                }
                return current;
            }

            bool searchRecursive(Node * node, Point3D point, int depth = 0){
                if(node == nullptr){
                    return false;
                }
                if(node->point == point){
                    return true;
                }

                int axis = depth % dimension;

                if(point[axis] < node->point[axis]){
                    return searchRecursive(node->left, point, depth+1);
                } else {
                    return searchRecursive(node->right, point, depth+1);
                }
            }

            void printRecursive(Node *node, int depth = 0){
                if(node == nullptr){
                    return;
                }
                printRecursive(node->right, depth+1);
                for(int i = 0; i < depth; i++){
                    cout<<setw(6*depth);
                }
                cout<<node->point;
                cout<<"["<<depth<<"]"<<endl;// depth
                printRecursive(node->left, depth+1);
            }

            double distanceL2(const Point3D& p1, const Point3D& p2) {
                double distancia = 0.0;
                for (int i = 0; i < p1.size(); i++) {
                    distancia += pow(p1[i] - p2[i], 2);
                }
                return sqrt(distancia);
            }
            
            /*
            *`KNNRecursive` es una función recursiva que realiza una búsqueda de k vecinos más cercanos en un KDTree.
            * @param node: el nodo actual en el que se encuentra la recursión.
            * @param point: el punto de consulta.
            * @param k: el número de vecinos más cercanos a encontrar.
            * @param nearestNeighbors: una cola de prioridad que contiene los k vecinos más cercanos.
            * @param depth: la profundidad actual en la que se encuentra la recursión.
            * @return: void.
            */
            void KNNRecursive(Node* node, const Point3D& point, int k, priority_queue<pair<double, Node*>>& nearestNeighbors, int depth = 0) {
                if (node == nullptr) {
                    return;
                }

                int axis = depth % point.size();
                double distance = distanceL2(point, node->point);

                if (nearestNeighbors.size() < k || distance < nearestNeighbors.top().first) {
                    if (nearestNeighbors.size() == k) {
                        nearestNeighbors.pop();
                    }
                    nearestNeighbors.push({distance, node});
                }

                if (point[axis] < node->point[axis]) {
                    KNNRecursive(node->left, point, k , nearestNeighbors, depth + 1);
                    if (nearestNeighbors.size() < k || abs(node->point[axis] - point[axis]) < nearestNeighbors.top().first) {
                        KNNRecursive(node->right, point, k, nearestNeighbors, depth + 1);
                    }
                } else {
                    KNNRecursive(node->right, point, k, nearestNeighbors, depth + 1);
                    if (nearestNeighbors.size() < k || abs(node->point[axis] - point[axis]) < nearestNeighbors.top().first) {
                        KNNRecursive(node->left, point, k, nearestNeighbors, depth + 1);
                    }
                }
            }

            /*
            * `KNNRecursive2` es una función recursiva que realiza una búsqueda de k vecinos más cercanos en un KDTree.
            * @param current: el nodo actual en el que se encuentra la recursión.
            * @param point: el punto de consulta.
            * @param k: el número de vecinos más cercanos a encontrar.
            * @param nearestNeighbors: una cola de prioridad que contiene los k vecinos más cercanos.
            * @param depth: la profundidad actual en la que se encuentra la recursión.
            * @return: void.
            */

            void KNNRecursive2(Node *current, const Point3D& point, int k,
                        priority_queue<pair<double, Node*>>& nearestNeighbors, int depth = 0) {
                if (current == nullptr) {
                    return;
                }

                int axis = depth % dimension;
                double distance = distanceL2(current->point, point);

                nearestNeighbors.push({distance, current});

                if (nearestNeighbors.size() > k) {
                    nearestNeighbors.pop();
                }

                Node *first, *second;
                if (point[axis] < current->point[axis]) {
                    first = current->left;
                    second = current->right;
                } else {
                    first = current->right;
                    second = current->left;
                }

                KNNRecursive2(first, point, k, nearestNeighbors, depth + 1);

                if (fabs(point[axis] - current->point[axis]) <= nearestNeighbors.top().first) {
                    KNNRecursive2(second, point, k, nearestNeighbors, depth + 1);
                }
            }
   //-------------------------------------------------------------------------------- 
            bool arePointsSame(Point3D &point1, Point3D &point2){
                // Compare individual pointinate values
                for (int i = 0; i < (int)point1.size(); ++i)
                    if (point1[i] != point2[i])
                        return false;
                return true;
            }
             
            // Copies point p2 to p1
            void copyPoint(Point3D &p1, Point3D &p2){
               for (int i=0; i<(int)p1.size(); i++)
                   p1[i] = p2[i];
            }

            Node *minNode(Node *x, Node *y, Node *z, int d){
                Node *res = x;
                if (y != nullptr && y->point[d] < res->point[d])
                    res = y;
                if (z != nullptr && z->point[d] < res->point[d])
                    res = z;
                return res;
            }

            Node *findMinRec(Node *root, int d, unsigned depth){
                // Base cases
                if (root == nullptr)
                    return nullptr;
        
                // Current dimension is computed using current depth and total
                // dimensions (k)
                unsigned cd = depth % dimension;
        
                // Compare point with root with respect to cd (Current dimension)
                if (cd == d){
                    if (root->left == nullptr)
                        return root;
                    return findMinRec(root->left, d, depth+1);
                }
        
                // If current dimension is different then minimum can be anywhere
                // in this subtree
                return minNode(root,
                               findMinRec(root->left, d, depth+1),
                               findMinRec(root->right, d, depth+1), d);
            }

            Node *findMin(Node* root, int d){
                // Pass current level or depth as 0
                return findMinRec(root, d, 0);
            }
            Node *deleteNodeRec(Node *root, Point3D &point, int depth){
                // Given point is not present
                if (root == nullptr)
                    return nullptr;
        
                // Find dimension of current node
                int cd = depth % dimension;
        
                // If the point to be deleted is present at root
                if (arePointsSame(root->point, point)){
                    // 2.b) If right child is not nullptr
                    if (root->right != nullptr){
                            // Find minimum of root's dimension in right subtree
                            Node *min = findMin(root->right, cd);
                            // Copy the minimum to root
                            copyPoint(root->point, min->point);
                            // Recursively delete the minimum
                            root->right = deleteNodeRec(root->right, min->point, depth+1);
                        }
                    else if (root->left != nullptr) // same as above
                        {
                        Node *min = findMin(root->left, cd);
                        copyPoint(root->point, min->point);
                        root->right = deleteNodeRec(root->left, min->point, depth+1);
                        root->left = nullptr;
                    }
                    else // If node to be deleted is leaf node
                    {
                        delete root;
                        return nullptr;
                    }
                    return root;
                }
        
                // 2) If current node doesn't contain point, search downward
                if (point[cd] < root->point[cd])
                    root->left = deleteNodeRec(root->left, point, depth+1);
                else
                    root->right = deleteNodeRec(root->right, point, depth+1);
                return root;
            }
};
    
}

