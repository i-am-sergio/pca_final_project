#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>



namespace rdr {
    
    using namespace std;

    class CSVReader {
        public:
            CSVReader(const string& filename) : filename(filename) {}

            vector<vector<double>> readCSV() {
                ifstream file(filename);
                vector<vector<double>> data;

                if (!file.is_open()) {
                    cerr << "Error al abrir el archivo: " << filename << endl;
                    return data;
                }

                string line;
                while (getline(file, line)) {
                    vector<double> row;
                    stringstream ss(line);
                    string value;

                    int i = 0;
                    while (getline(ss, value, ',')) {
                        // Convierte cada valor de cadena a un double y lo agrega a la fila
                        row.push_back(stod(value));
                        i++;
                        if (i == 3) break;
                    }

                    // Agrega la fila al vector bidimensional
                    data.push_back(row);
                }

                file.close();
                return data;
            }

        private:
            string filename;
        };

}