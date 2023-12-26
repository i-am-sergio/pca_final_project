#include "includes/KDTree.hpp"
#include "utils/Reader.hpp"
#include "utils/Grapher.hpp"
#include "utils/Tester.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace kdt;
using namespace rdr;
using namespace graph;
/*
void test1()
{
    KDTree<3> kdtree;
    kdtree.insert({4, 5, 6});
    kdtree.insert({1, 2, 3});
    kdtree.insert({2, 3, 4});
    kdtree.insert({6, 7, 8});
    kdtree.insert({3, 4, 5});
    kdtree.insert({5, 6, 7});
    kdtree.print();
    cout << "Search: " << boolalpha << kdtree.search({3, 4, 5}) << endl;
}

void test2()
{
    CSVReader reader("../pca_result.csv");
    vector<Point3D> data = reader.readCSV();

    KDTree<3> kdtree;
    for (auto &row : data)
        kdtree.insert(row);
    kdtree.print();
    cout << "Search: " << boolalpha << kdtree.search({6.681046678649641, -0.041085165257433574, 0.023819628573979304}) << "\n";
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
    vector<Point3D> data = reader.readCSV();

    Grapher grapher;
    for (auto &row : data)
        grapher.AddPoint(row[0], row[1], row[2]);
    grapher.DrawPoints();
    grapher.ShowWindow();
}

void test5()
{
    CSVReader reader("pca_result.csv");
    vector<Point3D> data = reader.readCSV();
    KDTree<3> kdtree;
    for (auto &row : data)
        kdtree.insert(row);
    Grapher grapher;
    grapher.printKD(kdtree);
    grapher.DrawPoints();
    grapher.DrawLines();
    grapher.ShowWindow();
}

int main()
{
    // test4();
    test5();

    return 0;
}*/

int main(int argc, char **argv)
{
    if (argc > 1 && std::string(argv[1]) == "--run-tests")
    {
        // Ejecutar las pruebas
        testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
    else
    {
        CSVReader reader("pca_result.csv");
        vector<Point3D> data = reader.readCSV();
        KDTree<3> kdtree;
        for (auto &row : data)
            kdtree.insert(row);

        int option;
        do
        {
            std::cout << "Seleccione una opcion:" << std::endl;
            std::cout << "1. Buscar" << std::endl;
            std::cout << "2. Mostrar KDTree" << std::endl;
            std::cout << "3. Mostrar (VTK)" << std::endl;
            std::cout << "4. GTEST" << std::endl;
            std::cout << "5. Salir" << std::endl;
            std::cin >> option;

            switch (option)
            {
            case 1:
            {
                double x, y, z;
                std::cout << "Ingrese los tres numeros del punto a buscar" << std::endl;
                std::cin >> x >> y >> z;
                cout << "Search: " << boolalpha << kdtree.search({x, y, z}) << endl;
                break;
            }
            case 2:
                kdtree.print();
                break;
            case 3:
            {
                Grapher grapher;
                grapher.printKD(kdtree);
                grapher.DrawPoints();
                grapher.DrawLines();
                grapher.ShowWindow();
                break;
            }
            case 4:
                testing::InitGoogleTest();
                return RUN_ALL_TESTS();
                break;
            case 5:
                break;
            default:
                std::cout << "Opcion invalida, seleccione una opcion valida." << std::endl;
                break;
            }
        } while (option != 5);
    }
    return 0;
}