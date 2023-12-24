#include "Components/KDTree/kdtree.hpp"
#include "Components/Reader/reader.hpp"
#include "Components/Grapher/grapher.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace kdt;
using namespace rdr;
using namespace graph;
void test1()
{
    KDTree<3> kdtree;
    kdtree.insert(Node({1, 2, 3}, "1", "1"));
    kdtree.insert(Node({4, 5, 6}, "2", "2"));
    kdtree.insert(Node({7, 8, 9}, "3", "3"));
    kdtree.insert(Node({10, 11, 12}, "4", "4"));
    kdtree.insert(Node({13, 14, 15}, "5", "5"));
    kdtree.insert(Node({16, 17, 18}, "6", "6"));
    kdtree.print();
    cout << "Search: " << boolalpha << kdtree.search({4, 5, 6}) << endl;
}
void test2()
{
    CSVReader reader("../pca_result.csv");
    vector<Node> data = reader.readCSV();

    KDTree<3> kdtree;
    for (auto &row : data)
        kdtree.insert(row);
    // kdtree.print();
    cout << "Search: " << boolalpha << kdtree.search({1.6820010169547652, -1.038822881689953, -2.215253941708522}) << "\n";
}

void test3()
{
    Grapher grapher;
    grapher.AddPoint(1, 2, 3);
    grapher.AddPoint(4, 5, 6);
    grapher.AddPoint(7, 8, 9);
    grapher.AddPoint(10, 11, 12);
    grapher.AddPoint(13, 14, 15);
    grapher.AddPoint(16, 17, 18);
    grapher.AddPoint(19, 20, 21);
    grapher.AddPoint(22, 23, 24);
    grapher.AddPoint(25, 26, 27);
    grapher.AddPoint(28, 29, 40);
    grapher.DrawPoints();
    grapher.ShowWindow();
}

void test4()
{
    CSVReader reader("pca_result.csv");
    vector<Node> data = reader.readCSV();
    // for (const auto &row : data)
    // cout << row << endl;
    Grapher grapher;
    for (auto &row : data)
        grapher.AddPoint(row.point[0], row.point[1], row.point[2]);
    grapher.DrawPoints();
    grapher.ShowWindow();
}

int main()
{
    test1();
    test2();
    test3();
    test4();

    return 0;
}