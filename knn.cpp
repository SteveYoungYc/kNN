#include "KNN.h"
#include <cmath>
#include <iostream>
#include <algorithm>

double KNN::euclideanDistance(const std::vector<double>& a, const std::vector<double>& b) {
    double sum = 0;
    for (size_t i = 0; i < a.size(); i++) {
        sum += (a[i] - b[i]) * (a[i] - b[i]);
    }
    return std::sqrt(sum);
}

int KNN::categoricalDistance(const std::string& a, const std::string& b) {
    return a == b ? 0 : 1;
}

KNN::KNN(const std::vector<DataPoint>& data, int kVal) : dataset(data), k(kVal) {}

std::string KNN::predict(const DataPoint& point) {
    std::vector<std::pair<double, DataPoint>> distances;
    int j = 0;
    for (const auto& dataPoint : dataset) {
        if (point.continuousFeatures.size() != dataPoint.continuousFeatures.size()) {
            std::cerr << j << std::endl;
        }
        double dist = euclideanDistance(point.continuousFeatures, dataPoint.continuousFeatures);
        for (size_t i = 0; i < point.categoricalFeatures.size(); i++) {
            dist += categoricalDistance(point.categoricalFeatures[i], dataPoint.categoricalFeatures[i]);
        }
        distances.emplace_back(dist, dataPoint);
        j++;
    }

    std::sort(distances.begin(), distances.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
    });

    std::map<std::string, int> voteMap;
    for (int i = 0; i < k; i++) {
        voteMap[distances[i].second.label]++;
    }

    std::string predictedLabel;
    int maxVotes = -1;
    for (const auto& [label, votes] : voteMap) {
        if (votes > maxVotes) {
            maxVotes = votes;
            predictedLabel = label;
        }
    }

    return predictedLabel;
}
