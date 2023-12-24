#ifndef READER_HPP
#define READER_HPP
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Node.hpp"
using namespace std;

namespace rdr
{
    class CSVReader
    {
    public:
        CSVReader(const string &filename) : filename(filename) {}

        vector<Node> readCSV()
        {
            ifstream file(filename);
            vector<Node> nodes;
            if (!file.is_open())
            {
                cerr << "Error al abrir el archivo: " << filename << endl;
                return nodes;
            }
            string line;
            while (getline(file, line))
            {
                stringstream ss(line);
                string value;
                vector<string> values;
                while (getline(ss, value, ','))
                {
                    if (value.front() == '\"' && value.back() != '\"')
                    {
                        string temp;
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
                    vector<double> pointValues;
                    for (int i = 0; i < 3; ++i)
                        pointValues.push_back(stod(values[i]));
                    string pointId = values[3];
                    string data = values[4];
                    if (!data.empty() && data.front() == '\"' && data.back() == '\"')
                        data = data.substr(1, data.size() - 2);
                    nodes.emplace_back(pointValues, pointId, data);
                }
            }
            file.close();
            return nodes;
        }

    private:
        string filename;
    };

}
#endif // READER_HPP