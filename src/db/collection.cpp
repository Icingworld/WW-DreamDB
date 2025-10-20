#include "db/collection.h"

#include <filesystem>
#include <algorithm>

namespace WW
{

Collection::Collection(const Meta::CollectionMeta & meta)
    : meta_(meta)
    , active_segment_(nullptr)
    , segments_()
    , segment_cache_()
{
    // 创建 collection 根目录
    std::filesystem::create_directories(meta_.root_path + "/" + meta_.name);
}

bool Collection::Insert(const std::string & id, const std::vector<float> & vector)
{
    // if (segments_.empty() || segments_.back()->Size() >= meta_.segment_size) {
    //     std::string seg_path = meta_.root_path + "/" + meta_.name + "/segment_" + std::to_string(segments_.size()) + ".seg";
    //     Meta::SegmentMeta meta = {seg_path, meta_.dimension};
    //     segments_.push_back(std::make_shared<Segment>(meta));
    // }

    // return segments_.back()->Insert(id, vector);
}

std::vector<Types::SearchResult> Collection::Search(const std::vector<float> & vector, int top_k) const
{
    // // 准备空间
    // std::vector<Types::SearchResult> all_results;
    // all_results.reserve(top_k * segments_.size());

    // // 从每个段落获取结果
    // for (const auto & seg : segments_) {
    //     auto results = seg->Search(vector, top_k);
    //     all_results.insert(all_results.end(), results.begin(), results.end());
    // }

    // // 聚合排序
    // std::partial_sort(all_results.begin(), all_results.begin() + top_k, all_results.end(), 
    //     [](const Types::SearchResult & a, const Types::SearchResult & b) {
    //         return a.score < b.score;
    //     }
    // );

    // return std::vector<Types::SearchResult>(all_results.begin(), all_results.begin() + top_k);
}

void Collection::Flush() const
{
    // for (const auto & seg : segments_) {
    //     seg->Seal();
    // }
}


void Collection::Load()
{
    // std::filesystem::path dir = meta_.root_path + "/" + meta_.name;
    // if (!std::filesystem::exists(dir)) return;
    // for (auto& entry : std::filesystem::directory_iterator(dir)) {
    //     if (entry.path().extension() == ".seg") {
    //         Meta::SegmentMeta meta = {entry.path().string(), meta_.dimension};
    //         auto seg = std::make_shared<Segment>(meta);
    //         seg->Load();
    //         segments_.push_back(seg);
    //     }
    // }
}

} // namespace WW
