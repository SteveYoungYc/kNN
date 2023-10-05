#ifndef CHEN_DATAPOINT_H
#define CHEN_DATAPOINT_H

#include <vector>
#include <string>
#include <map>

struct DataPoint {
    std::vector<double> continuousFeatures;
    std::vector<std::string> categoricalFeatures;
    std::string label;
};

#endif
