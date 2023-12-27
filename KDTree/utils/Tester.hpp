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

TEST(KDTreeTest, Test_Delete)
{
    KDTree<3> kdtree;
    kdtree.insert({1, 2, 3});
    kdtree.insert({4, 5, 6});
    kdtree.insert({7, 8, 9});
    kdtree.insert({10, 11, 12});
    kdtree.insert({13, 14, 15});
    kdtree.insert({16, 17, 18});
    EXPECT_NO_THROW(kdtree.deleteNode({4, 5, 6}));
    EXPECT_NO_THROW(kdtree.deleteNode({10,11,12}));
    EXPECT_NO_THROW(kdtree.deleteNode({16,17,18}));
    EXPECT_NO_THROW(kdtree.deleteNode({1,2,3}));
    EXPECT_NO_THROW(kdtree.deleteNode({7,8,9}));
    EXPECT_NO_THROW(kdtree.deleteNode({13,14,15}));
    EXPECT_FALSE(kdtree.search({4, 5, 6}));
    EXPECT_FALSE(kdtree.search({10,11,12}));
    EXPECT_FALSE(kdtree.search({16,17,18}));
    EXPECT_FALSE(kdtree.search({1,2,3}));
    EXPECT_FALSE(kdtree.search({7,8,9}));
    EXPECT_FALSE(kdtree.search({13,14,15}));
}
