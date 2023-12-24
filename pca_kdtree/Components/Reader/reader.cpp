#include "reader.hpp"
namespace rdr
{
    CSVReader::CSVReader(const std::string &filename) : filename(filename) {}

    std::vector<Node> CSVReader::readCSV()
    {
        std::ifstream file(filename);
        std::vector<Node> nodes;
        if (!file.is_open())
        {
            std::cerr << "Error al abrir el archivo: " << filename << std::endl;
            return nodes;
        }
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
                std::string pointId = values[3];
                std::string data = values[4];
                if (!data.empty() && data.front() == '\"' && data.back() == '\"')
                    data = data.substr(1, data.size() - 2);
                nodes.emplace_back(pointValues, pointId, data);
            }
        }
        file.close();
        return nodes;
    }
} // namespace rdr