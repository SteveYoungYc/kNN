#include <vector>
#include <string>
#include <map>

struct DataPoint {
    std::vector<double> continuousFeatures;
    std::vector<std::string> categoricalFeatures;
    std::string label;
};

class KNN {
private:
    std::vector<DataPoint> dataset;
    int k;

    double euclideanDistance(const std::vector<double>& a, const std::vector<double>& b);
    int categoricalDistance(const std::string& a, const std::string& b);

public:
    KNN(const std::vector<DataPoint>& data, int kVal);
    std::string predict(const DataPoint& point);
};
