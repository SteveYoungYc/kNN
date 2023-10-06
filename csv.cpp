#include "CSV.h"
#include <iostream>
#include <fstream>
#include <algorithm>

std::vector<int> CSV::desc = {
    0, // age
    1, // workclass
    0, // fnlwgt
    1, // education
    0, // education-num
    1, // marital-status
    1, // occupation
    1, // relationship
    1, // race
    1, // sex
    0, // capital-gain
    0, // capital-loss
    0, // hours-per-week
    1, // native-country
    -1,
};

CSV::CSV(const char* filePath) {
    std::ifstream file(filePath);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return;
    }

    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream lineStream(line);
        std::string cell;

        while (std::getline(lineStream, cell, ',')) {
            cell.erase(std::remove(cell.begin(), cell.end(), ' '), cell.end());
            row.push_back(cell);
        }

        data.push_back(row);
    }

    file.close();
}

std::string CSV::getCell(int rowIndex, int colIndex) const {
    if (rowIndex >= 0 && rowIndex < data.size()) {
        if (colIndex >= 0 && colIndex < data[rowIndex].size()) {
            return data[rowIndex][colIndex];
        }
    }
    return "";
}

int CSV::numRows() const {
    return (int)data.size();
}

int CSV::numCols(int rowIndex) const {
    if (rowIndex >= 0 && rowIndex < data.size()) {
        return (int)data[rowIndex].size();
    }
    return -1;
}

void CSV::print() const {
    for (const auto& row : data) {
        for (const auto& cell : row) {
            std::cout << cell << "|";
        }
        std::cout << std::endl;
    }
}
