#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

#include "knn.h"
#include "csv.h"

std::mutex mtx;

void processPrediction(KNN& knn, const CSV& test_csv, int& success, int& failure, int start, int end) {
    for (int i = start; i < end; i++) {
        DataPoint dataPoint;
        for (int j = 0; j < test_csv.numCols(i); j++) {
            std::string cell = test_csv.getCell(i, j);
            switch (CSV::desc[j]) {
                case -1: {
                    cell.pop_back();
                    dataPoint.label = cell;
                    break;
                }
                case 0: {
                    if (cell == "?") {
                        dataPoint.continuousFeatures.push_back(0);
                        break;
                    }
                    double val = std::stod(cell);
                    dataPoint.continuousFeatures.push_back(val);
                    break;
                }
                case 1: {
                    if (cell == "?") {
                        dataPoint.categoricalFeatures.push_back("MISSING");
                        break;
                    }
                    dataPoint.categoricalFeatures.push_back(cell);
                    break;
                }
            }
        }
        std::string predictedLabel = knn.predict(dataPoint);

        mtx.lock();
        if (predictedLabel == dataPoint.label) {
            ++success;
        } else {
            ++failure;
        }
        mtx.unlock();
    }
}

int main() {
    auto startTime = std::chrono::high_resolution_clock::now();

    CSV train_csv(R"(D:\NTU\Data Mining\chen\data\adult.data)");
    CSV test_csv(R"(D:\NTU\Data Mining\chen\data\adult.test)");
    std::vector<DataPoint> train_data;

    for (int i = 0; i < train_csv.numRows(); i++) {
        DataPoint dataPoint;
        for (int j = 0; j < train_csv.numCols(i); j++) {
            std::string cell = train_csv.getCell(i, j);
            switch (CSV::desc[j]) {
                case -1: {
                    dataPoint.label = cell;
                    break;
                }
                case 0: {
                    if (cell == "?") {
                        dataPoint.continuousFeatures.push_back(0);
                        break;
                    }
                    double val = std::stod(cell);
                    dataPoint.continuousFeatures.push_back(val);
                    break;
                }
                case 1: {
                    if (cell == "?") {
                        dataPoint.categoricalFeatures.push_back("MISSING");
                        break;
                    }
                    dataPoint.categoricalFeatures.push_back(cell);
                    break;
                }
            }
        }
        train_data.emplace_back(dataPoint);
    }

    KNN knn(train_data, 10);
    int success = 0;
    int failure = 0;

    unsigned int numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads(numThreads);
    std::cout << "Number of threads: " << numThreads << std::endl;

    int rowsPerThread = test_csv.numRows() / (int)numThreads;

    for (int i = 0; i < numThreads; i++) {
        int start = i * rowsPerThread;
        int end = (i == numThreads - 1) ? test_csv.numRows() : start + rowsPerThread;

        threads[i] = std::thread(processPrediction, std::ref(knn), std::ref(test_csv), std::ref(success), std::ref(failure), start, end);
    }

    for (int i = 0; i < numThreads; i++) {
        threads[i].join();
    }

    std::cout << "Accuracy: " << static_cast<double>(success) / (success + failure) * 100 << "%" << std::endl;
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    std::cout << "Time duration: " << duration.count() << " milliseconds" << std::endl;

    return 0;
}