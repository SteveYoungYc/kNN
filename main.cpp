#include <iostream>
#include "KNN.h"

int main() {
    std::vector<DataPoint> data = {
            {{1.0, 2.0}, {"USA"}, "A"},
            {{2.0, 3.0}, {"UK"}, "A"},
            {{5.0, 6.0}, {"India"}, "B"},
            {{6.0, 7.0}, {"USA"}, "B"}
    };

    KNN knn(data, 3);
    DataPoint testPoint = {{3.0, 4.0}, {"UK"}};
    std::cout << "Predicted Label: " << knn.predict(testPoint) << std::endl;

    return 0;
}