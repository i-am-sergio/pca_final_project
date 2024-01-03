#pragma once
#include "Node.hpp"
#include "KDTree.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <ctime>
#include <iomanip>
#include <random>
#include <algorithm>

using namespace std;

class KMeans
{
public:
    void printVector(const vector<Point3D> &vec)
    {
        std::cout << "Vector Elements: ";
        for (const auto &element : vec)
            std::cout << element << "\n";
        std::cout << "\n";
    }

    void printVV(const std::vector<std::vector<Point3D>> &vectorOfVectors)
    {
        for (const auto &innerVector : vectorOfVectors)
        {
            for (const auto &element : innerVector)
            {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }
    }

    // obtener 3 centroides random
    std::vector<Point3D> obtenerCentroidesAleatorios(const std::vector<Point3D> &puntos, int quantity)
    {
        std::vector<Point3D> all_centroides;
        if (puntos.size() < quantity || quantity < 1)
            return all_centroides;
        std::mt19937 gen(static_cast<long unsigned int>(12));
        std::uniform_int_distribution<int> distribution(0, puntos.size() - 1);
        for (int i = 0; i < quantity; ++i)
        {
            int indice = distribution(gen);
            while (std::find(all_centroides.begin(), all_centroides.end(), puntos[indice]) != all_centroides.end())
                indice = distribution(gen);
            all_centroides.push_back(puntos[indice]);
        }
        return all_centroides;
    }

    vector<Point3D> newCenters(vector<vector<Point3D>> clusteres)
    {
        vector<Point3D> newCentroides;
        for (int i = 0; i < clusteres.size(); i++)
        {
            Point3D newCentroide = {0, 0, 0};
            for (const auto &point : clusteres[i])
                newCentroide = newCentroide + point;
            int size = clusteres[i].size();
            if (size != 0)
                newCentroide = newCentroide / size;
            newCentroides.push_back(newCentroide);
        }
        return newCentroides;
    }

    vector<vector<Point3D>>
    KMeans_def(const vector<Point3D> &all_centroides, vector<Point3D> &all_points)
    {
        kdt::KDTree<3> kdtree_centroides;
        for (auto &row : all_centroides)
            kdtree_centroides.insert(row);
        vector<vector<Point3D>> clusters(all_centroides.size());
        for (int i = 0; i < all_points.size(); i++)
        {
            vector<Point3D> num = kdtree_centroides.searchKNN2(all_points[i], 1);
            for (int j = 0; j < all_centroides.size(); ++j)
            {
                if (num[0] == all_centroides[j])
                {
                    clusters[j].push_back(all_points[i]);
                    break;
                }
            }
        }
        vector<Point3D> newCentroides = newCenters(clusters);
        double distanceThreshold = 8.4;
        double distance = 0.0;
        for (int i = 0; i < all_centroides.size(); ++i)
            distance += EuclideanDistance(all_centroides[i], newCentroides[i]);
        if (distance < distanceThreshold)
        {
            // std::cout << "Algoritmo convergió. Distancia: " << distance << std::endl;
            return clusters;
        }
        //std::cout << "Algoritmo no convergió. Distancia: " << distance << std::endl;
        return KMeans_def(newCentroides, all_points);
    }
};