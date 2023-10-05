#ifndef KNN_H
#define KNN_H

#include <vector>
#include <string>
#include <map>

#include "datapoint.h"

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

#endif
