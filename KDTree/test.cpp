#include "includes/KDTree.hpp"
#include "includes/Kmeans.hpp"
#include "utils/Reader.hpp"
#include "utils/Grapher.hpp"
#include "utils/Tester.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace kdt;
using namespace rdr;
using namespace graph;

void testKmeans()
{
    CSVReader reader("pca_result.csv");
    KMeans kmeans;
    vector<Point3D> data = reader.readCSV();
    vector<Point3D> all_centroides = kmeans.obtenerCentroidesAleatorios(data, 8);
    vector<vector<Point3D>> clusteres = kmeans.KMeans_def(all_centroides, data);
    cout << "FINISH\n";
}

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
        KMeans kmeans;
        for (auto &row : data)
            kdtree.insert(row);

        CSVReader reader2("puntos.csv");
        vector<Point3D> _11_variables = reader2.readCSV();
        
        vector<Point3D> all_centroides = kmeans.obtenerCentroidesAleatorios(data,8);
        vector<vector<Point3D>> clusteres = kmeans.KMeans_def(_11_variables, data);

        int option;
        do
        {
            std::cout << "============ MENU ============" << std::endl;
            std::cout << "[1] Buscar" << std::endl;
            std::cout << "[2] Print KDTree" << std::endl;
            std::cout << "[3] Graficar KDTree (VTK)" << std::endl;
            std::cout << "[4] Graficar Clusteres" << std::endl;
            std::cout << "[5] GTEST" << std::endl;
            std::cout << "[0] Salir" << std::endl;
            std::cout << "-----------------------------" << std::endl;
            std::cout << " => ";
            std::cin >> option;
            std::cout << "==============================\n";

            switch (option)
            {
            case 1:
            {
                double x, y, z;
                std::cout << "Ingrese los tres numeros del punto a buscar" << std::endl;
                std::cout <<"  x: "; std::cin >> x; 
                std::cout <<"  y: "; std::cin >> y;
                std::cout <<"  z: "; std::cin >> z;
                cout << "Search Result: " << boolalpha << kdtree.search({x, y, z}) << endl;
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
            {
                Grapher grapher;
                grapher.printClusteres(clusteres);
                for (auto &row : _11_variables){
                    grapher.addVector(0.0, 0.0, 0.0, row[0], row[1], row[2], "White");
                    grapher.AddCentroide(row[0], row[1], row[2]);
                }
                grapher.DrawCentroides();
                grapher.ShowWindow();
                break;
            }
            case 5:
                testing::InitGoogleTest();
                return RUN_ALL_TESTS();
                break;
            case 0:
                break;
            default:
                std::cout << "Opcion invalida, seleccione una opcion valida." << std::endl;
                break;
            }
        } while (option != 0);
    }
    return 0;
}