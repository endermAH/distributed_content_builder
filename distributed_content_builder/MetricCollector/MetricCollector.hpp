#ifndef METRIC_COLLECTOR_HPP
#define METRIC_COLLECTOR_HPP

#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iostream>
#include <sstream>

class MetricCollector
{
public:
    struct Metric
    {
        std::string name;
        std::string value;
    };

    struct IterationMetric
    {
        std::string name;
        int iteration;
        std::string value;
    };

    static void AddSingleMetric(const std::string& name, std::string value);
    static void AddIterationMetric(const std::string& name, int iteration, std::string value);
    static void CreateDataFiles(const std::string& singleMetricsFileName, const std::string& iterationMetricsFileName);
    static std::string GetCurrentTimestamp();

private:
    static std::vector<Metric> singleMetrics_;
    static std::vector<IterationMetric> iterationMetrics_;
};

#endif
