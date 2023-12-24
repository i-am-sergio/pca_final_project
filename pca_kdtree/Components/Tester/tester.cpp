#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "../KDTree/kdtree.hpp"
#include "../Reader/reader.hpp"

using namespace std;
using namespace kdt;
using namespace rdr;

void validating(KDTree<3> kdtree, std::string filename)
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
        std::stringstream ss(line);
        std::string value;
        std::vector<std::string> values;
        while (getline(ss, value, ','))
        {
            if (value.front() == '\"' && value.back() != '\"')
            {
                std::string temp;
                while (getline(ss, temp, ','))
                {
                    value += "," + temp;
                    if (temp.back() == '\"')
                        break;
                }
            }
            values.push_back(value);
        }
        if (values.size() >= 5)
        {
            std::vector<long double> pointValues;
            for (int i = 0; i < 3; ++i)
                pointValues.push_back(stold(values[i]));
            // std::cout << "Nro " << count++ << " Search: " << boolalpha << kdtree.search({pointValues[0], pointValues[1], pointValues[2]}) << endl;
            // std::cout << std::fixed << std::setprecision(15);
            // std::cout << "Point :" << pointValues[0] << " " << pointValues[1] << " " << pointValues[2] << endl;
            EXPECT_TRUE(kdtree.search({pointValues[0], pointValues[1], pointValues[2]}));
        }
    }
    file.close();
}

TEST(KDTreeTest, Test1)
{
    KDTree<3> kdtree;
    kdtree.insert(Node({1, 2, 3}, "1", "1"));
    kdtree.insert(Node({4, 5, 6}, "2", "2"));
    kdtree.insert(Node({7, 8, 9}, "3", "3"));
    kdtree.insert(Node({10, 11, 12}, "4", "4"));
    kdtree.insert(Node({13, 14, 15}, "5", "5"));
    kdtree.insert(Node({16, 17, 18}, "6", "6"));
    EXPECT_TRUE(kdtree.search({4, 5, 6}));
}

TEST(KDTreeTest, Test2)
{
    CSVReader reader("../pca_result.csv");
    vector<Node> data = reader.readCSV();
    KDTree<3> kdtree;
    for (auto &row : data)
        kdtree.insert(row);
    validating(kdtree, "../pca_result.csv");
}