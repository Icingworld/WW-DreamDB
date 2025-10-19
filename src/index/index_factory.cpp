#include "index/index_factory.h"

#include "index/brute_force_index.h"

namespace WW
{

std::unique_ptr<IndexBase> IndexFactory::CreateIndex(Types::IndexType type, Types::MetricType metric, int dimension)
{
    switch (type)
    {
    case Types::IndexType::BRUTE_FORCE:
        return IndexFactory::CreateBruteForceIndex(metric, dimension);
    default:
        return nullptr;
    }
}

std::unique_ptr<IndexBase> IndexFactory::CreateBruteForceIndex(Types::MetricType metric, int dimension)
{
    switch (metric) {
    case Types::MetricType::L2:
        return std::make_unique<BruteForceIndex<Types::MetricType::L2>>(dimension);
    case Types::MetricType::COSINE:
        return std::make_unique<BruteForceIndex<Types::MetricType::COSINE>>(dimension);
    default:
        throw std::invalid_argument("Unsupported metric type");
    }
}

} // namespace WW
