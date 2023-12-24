#ifndef READER_HPP
#define READER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "../Node/node.hpp"
namespace rdr
{
    class CSVReader
    {
    public:
        CSVReader(const std::string &filename);

        std::vector<Node> readCSV();

    private:
        std::string filename;
    };
} // namespace rdr
#endif // READER_HPP
