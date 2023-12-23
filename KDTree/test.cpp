#include "KDTree.hpp"
#include "Reader.hpp"
#include "Grapher.hpp"

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
    kdtree.print();
    cout<<"Search: "<<boolalpha<<kdtree.search({6.681046678649641,-0.041085165257433574,0.023819628573979304})<<"\n";
}

void test3(){
    Grapher grapher;
    grapher.AddPoint(1,2,3);
    grapher.AddPoint(4,5,6);
    grapher.AddPoint(7,8,9);
    grapher.AddPoint(10,11,12);
    grapher.AddPoint(13,14,15);
    grapher.AddPoint(16,17,18);
    grapher.AddPoint(19,20,21);
    grapher.AddPoint(22,23,24);
    grapher.AddPoint(25,26,27);
    grapher.AddPoint(28,29,40);
    grapher.DrawPoints();
    grapher.ShowWindow();
}

int main(){
    test3();

    return 0;
}