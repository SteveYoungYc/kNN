#ifndef CSV_H
#define CSV_H

#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>

class CSV {
private:
    std::vector<std::vector<std::string>> data;

public:
    static std::vector<int> desc;

    explicit CSV(const char* filePath);
    std::string getCell(int rowIndex, int colIndex) const;
    int numRows() const;
    int numCols(int rowIndex) const;
    void print() const;
};

#endif
