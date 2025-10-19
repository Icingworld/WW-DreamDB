#include "common/types/index_type.h"

#include <stdexcept>

namespace WW::Types
{

std::string IndexTypeToString(IndexType index_type)
{
    switch (index_type)
    {
    case IndexType::BRUTE_FORCE:
        return "brute_force";
    case IndexType::PQ:
        return "pq";
    case IndexType::IVF:
        return "ivf";
    case IndexType::IVFPQ:
        return "ivf-pq";
    case IndexType::HNSW:
        return "hnsw";
    default:
        throw std::invalid_argument("Unsupported index type");
    }
}

IndexType StringToIndexType(const std::string & str)
{
    if (str == "brute_force")
        return IndexType::BRUTE_FORCE;
    else if (str == "pq")
        return IndexType::PQ;
    else if (str == "ivf")
        return IndexType::IVF;
    else if (str == "ivf-pq")
        return IndexType::IVFPQ;
    else if (str == "hnsw")
        return IndexType::HNSW;
    else
        throw std::invalid_argument("Unsupported index type");
}

} // namespace WW::Types
