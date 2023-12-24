#include "Components/KDTree/kdtree.hpp"
#include "Components/Reader/reader.hpp"
#include <gtest/gtest.h>
#include "Components/Grapher/grapher.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace kdt;
using namespace rdr;
using namespace graph;

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
        CSVReader reader("../pca_result.csv");
        vector<Node> data = reader.readCSV();
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
                long double x, y, z;
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
                for (auto &row : data)
                    grapher.AddPoint(row.point[0], row.point[1], row.point[2]);
                grapher.DrawPoints();
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
