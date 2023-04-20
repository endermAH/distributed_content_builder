#include "MetricCollector.hpp"

std::vector<MetricCollector::Metric> MetricCollector::singleMetrics_;
std::vector<MetricCollector::IterationMetric> MetricCollector::iterationMetrics_;

std::string MetricCollector::GetCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::ctime(&time);
    std::string timestamp = ss.str();
    return timestamp;
}

void MetricCollector::AddSingleMetric(const std::string& name, std::string value)
{
    singleMetrics_.push_back({name, value});
}

void MetricCollector::AddIterationMetric(const std::string& name, int iteration, std::string value)
{
    iterationMetrics_.push_back({name, iteration, value});
}

void MetricCollector::CreateDataFiles(const std::string& singleMetricsFileName, const std::string& iterationMetricsFileName)
{
    // Create single metrics file
    std::ofstream singleMetricsFile(singleMetricsFileName);
    if (singleMetricsFile.is_open())
    {
        singleMetricsFile << "Metric,Value" << std::endl;
        for (const auto& metric : singleMetrics_)
        {
            singleMetricsFile << metric.name << "," << metric.value << std::endl;
        }
        singleMetricsFile.close();
    }

    // Create iteration metrics file
    std::ofstream iterationMetricsFile(iterationMetricsFileName);
    if (iterationMetricsFile.is_open())
    {
        iterationMetricsFile << "Metric,Iteration,Value" << std::endl;
        for (const auto& metric : iterationMetrics_)
        {
            iterationMetricsFile << metric.name << "," << metric.iteration << "," << metric.value << std::endl;
        }
        iterationMetricsFile.close();
    }
}
