#include <algorithm>
#include <stdexcept>
#include <fstream>

namespace WW
{

template <Types::MetricType M>
BruteForceIndex<M>::BruteForceIndex(int dimension)
    : dimension_(dimension)
    , index_()
{ // do nothing
}

template <Types::MetricType M>
bool BruteForceIndex<M>::AddVector(const std::string & id, const std::vector<float> & vector)
{
    if (vector.size() != dimension_) {
        throw std::invalid_argument("Vector size mismatch in AddVector()");
    }
    
    if (id_to_index_.find(id) != id_to_index_.end()) {
        return false;
    }

    id_to_index_.emplace(id, index_.size());
    index_.emplace_back(id, vector);
    return true;
}

template <Types::MetricType M>
std::vector<Types::SearchResult> BruteForceIndex<M>::Search(const std::vector<float> & query, int top_k) const
{
    std::vector<SearchResult> results;

    // 检查维度是否一致
    if (static_cast<int>(query.size()) != dimension_) {
        return results;
    }

    // 准备空间
    results.reserve(std::min<std::size_t>(top_k, index_.size()));

    // 计算距离
    for (const auto & [id, vector] : index_) {
        float distance = ComputeDistance<M>(query, vector);
        results.emplace_back(id, distance);
    }

    if (results.empty()) {
        return results;
    }

    // 按照距离排序
    if (static_cast<int>(results.size()) > top_k) {
        // 部分排序获取 top_k 最小
        std::partial_sort(results.begin(), results.begin() + top_k, results.end(), [](const SearchResult & a, const SearchResult & b) {
            return a.score < b.score;
        });

        results.resize(top_k);
    } else {
        // 全排序
        std::sort(results.begin(), results.end(), [](const SearchResult & a, const SearchResult & b) {
            return a.score < b.score;
        });
    }

    return results;
}

template <Types::MetricType M>
void BruteForceIndex<M>::Save(const std::string & path) const
{
    std::ofstream ofs(path, std::ios::binary);
    if (!ofs.is_open()) {
        throw std::runtime_error("Failed to open index file: " + path);
    }

    // 存储主体格式：[id_len][id_bytes][vector_floats]
    for (const auto & entry : index_) {
        const std::string & id = entry.id;
        const std::vector<float> & vector = entry.vector;

        std::size_t id_len = id.size();
        ofs.write(reinterpret_cast<const char *>(&id_len), sizeof(id_len));
        ofs.write(id.data(), id_len);
        ofs.write(reinterpret_cast<const char *>(vector.data()), vector.size() * sizeof(vector[0]));
    }

    ofs.close();
}

template <Types::MetricType M>
void BruteForceIndex<M>::Load(const std::string & path)
{
    std::ifstream ifs(path, std::ios::binary);
    if (!ifs.is_open()) {
        throw std::runtime_error("Failed to open index file: " + path);
    }

    // 读取主体格式：[id_len][id_bytes][vector_floats]
    while (true) {
        std::size_t id_len = 0;
        if (!ifs.read(reinterpret_cast<char *>(&id_len), sizeof(id_len))) {
            break;
        }

        std::string id(id_len, '\0');
        if (!ifs.read(id.data(), id_len)) {
            break;
        }

        std::vector<float> vector(dimension_);
        if (!ifs.read(reinterpret_cast<char *>(vector.data()), dimension_ * sizeof(float))) {
            break;
        }

        AddVector(id, vector);
    }

    ifs.close();
}

} // namespace WW
