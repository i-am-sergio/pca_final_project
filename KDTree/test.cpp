#include "includes/KDTree.hpp"
#include "utils/Reader.hpp"
#include "utils/Grapher.hpp"

#include <iostream>
#include <vector>

using namespace std;
using namespace kdt;
using namespace rdr;
using namespace graph;

void test1(){
    KDTree<3> kdtree;
    kdtree.insert({4,5,6});
    kdtree.insert({1,2,3});
    kdtree.insert({2,3,4});
    kdtree.insert({6,7,8});
    kdtree.insert({3,4,5});
    kdtree.insert({5,6,7});
    kdtree.print();
    cout << "Search: " << boolalpha << kdtree.search({3,4,5}) << endl;
}

void test2(){
    CSVReader reader("../pca_result.csv");
    vector<Point3D> data = reader.readCSV();
    
    KDTree<3> kdtree;
    for (auto& row : data)
        kdtree.insert(row);
    // kdtree.print();
    cout<<"Search: "<<boolalpha<<kdtree.search({-0.008428919807470295,0.04253583034486411,0.2300451309688243})<<"\n";
}

void test3(){
    CSVReader reader("pca_result.csv");
    vector<Point3D> data = reader.readCSV();
    
    Grapher grapher;
    for (auto& row : data)
        grapher.AddPoint(row[0], row[1], row[2]);
    grapher.DrawPoints();
    grapher.ShowWindow();
}

void test4(){
    CSVReader reader("pca_result.csv");
    vector<Point3D> data = reader.readCSV();
    
    Grapher grapher;
    for (auto& row : data)
        grapher.AddPoint(row[0], row[1], row[2]);
    grapher.DrawPoints();
    grapher.DrawSphere(0.0, 0.0, 0.0, 5.0, "SkyBlue");
    grapher.ShowWindow();

}

int main(){
    test4();

    return 0;
}