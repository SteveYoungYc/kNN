#include "CSV.h"
#include <iostream>
#include <fstream>
#include <algorithm>


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
            cell.erase(std::remove(cell.begin(), cell.end(), ' '), cell.end());  // 删除空格
            row.push_back(cell);
        }

        data.push_back(row);
    }

    file.close();
}

std::vector<std::string> CSV::getRow(int rowIndex) const {
    if (rowIndex >= 0 && rowIndex < data.size()) {
        return data[rowIndex];
    }
    return {};
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
    return data.size();
}

int CSV::numCols(int rowIndex) const {
    if (rowIndex >= 0 && rowIndex < data.size()) {
        return data[rowIndex].size();
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
