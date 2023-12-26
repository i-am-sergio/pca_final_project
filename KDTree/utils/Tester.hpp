#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <random>
#include "../includes/KDTree.hpp"
#include "Reader.hpp"

using namespace std;
using namespace kdt;
using namespace rdr;

void validating(KDTree<3> &kdtree, const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error al abrir el archivo: " << filename << std::endl;
        return;
    }
    int count = 1;
    std::string line;
    while (getline(file, line))
    {
        vector<double> row;
        stringstream ss(line);
        string value;
        int i = 0;
        while (getline(ss, value, ','))
        {
            row.push_back(stod(value));
            i++;
            if (i == 3)
                break;
        }
        if (row.size() == 3)
            ASSERT_TRUE(kdtree.search({row[0], row[1], row[2]}));
    }
    file.close();
}

TEST(KDTreeTest, Test1)
{
    KDTree<3> kdtree;
    kdtree.insert({1, 2, 3});
    kdtree.insert({4, 5, 6});
    kdtree.insert({7, 8, 9});
    kdtree.insert({10, 11, 12});
    kdtree.insert({13, 14, 15});
    kdtree.insert({16, 17, 18});
    EXPECT_TRUE(kdtree.search({4, 5, 6}));
}

TEST(KDTreeTest, Test_Insert)
{
    CSVReader reader("pca_result.csv");
    vector<Point3D> data = reader.readCSV();
    KDTree<3> kdtree;
    for (auto &row : data)
        EXPECT_NO_THROW(kdtree.insert(row));
}

TEST(KDTreeTest, Test_Insert_Search)
{
    CSVReader reader("pca_result.csv");
    vector<Point3D> data = reader.readCSV();
    KDTree<3> kdtree;
    for (auto &row : data)
        EXPECT_NO_THROW(kdtree.insert(row));
    validating(kdtree, "pca_result.csv");
}

TEST(KDTreeTest, Test2)
{
    KDTree<3> kdtree;
    kdtree.insert({1, 2, 3});
    kdtree.insert({4, 5, 6});
    kdtree.insert({7, 8, 9});
    kdtree.insert({10, 11, 12});
    kdtree.insert({13, 14, 15});
    kdtree.insert({16, 17, 18});
    EXPECT_NO_THROW(kdtree.deleteNode({4, 5, 6}));
    EXPECT_FALSE(kdtree.search({4, 5, 6}));
}

TEST(KDTreeTest, Test_Delete_All)
{
    CSVReader reader("pca_result.csv");
    vector<Point3D> data = reader.readCSV();
    vector<Point3D> data2 = data;
    KDTree<3> kdtree;
    for (auto &row : data)
        EXPECT_NO_THROW(kdtree.insert(row));

    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(data2.begin(), data2.end(), rng);
    int countTrue = 0;
    for (auto &row : data2)
    {
        EXPECT_NO_THROW(kdtree.deleteNode(row));
        if (kdtree.search(row))
        {
            countTrue++;
        }
    }
    for (auto &row : data)
        EXPECT_FALSE(kdtree.search(row));
    std::cout << "Number of times kdtree.search(row) is true after node deletion: " << countTrue << std::endl;
}