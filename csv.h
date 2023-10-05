#include <vector>
#include <string>
#include <sstream>

class CSV {
private:
    std::vector<std::vector<std::string>> data;

public:
    CSV(const char* filePath);  // 新增的构造函数，接受文件路径
    std::vector<std::string> getRow(int rowIndex) const;
    std::string getCell(int rowIndex, int colIndex) const;
    int numRows() const;
    int numCols(int rowIndex) const;
    void print() const;
};
