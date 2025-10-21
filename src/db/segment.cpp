#include "db/segment.h"

#include <fstream>
#include <iostream>

#include "common/meta/meta.h"

namespace WW
{

Segment::Segment(const Meta::SegmentMeta & meta)
    : meta_(meta)
    , data_()
{ // do nothing
}

bool Segment::Insert(const std::string & id, const std::vector<float> & vector)
{
    if (vector.size() != meta_.dimension)
    {
        return false;
    }

    if (index_->AddVector(id, vector)) {
        data_.emplace_back(id, vector);
    }

    return true;
}

std::vector<Types::SearchResult> Segment::Search(const std::vector<float> & vector, int top_k) const
{
    return index_->Search(vector, top_k);
}

std::string Segment::Name() const
{
    return meta_.name;
}

std::size_t Segment::Size() const
{
    return data_.size();
}

void Segment::Seal()
{
    // 文件结构设计
    // path: [collection_name]/segments/[prefix]/segment_[UUIDv4]/
    // 文件结构：
    // [collection_name]/
    // ├── meta.json
    // ├── segments/
    // │   └── [prefix]/
    // │       ├── segment_[UUIDv4]/
    // │       │   ├── meta.json
    // │       │   ├── index.bin
    // │       │   └── data.bin
    // │       └── segment_[UUIDv4]/
    // │           ├── meta.json
    // │           ├── index.bin
    // │           └── data.bin

    // 写 meta.json 到 path/meta.json
    Meta::SaveMeta(meta_, meta_.root_path + "/" + meta_.name + "/meta.json");

    // 写 index.bin 到 path/index.bin
    index_->Build();
    index_->Save(meta_.root_path + "/" + meta_.name + "/index.bin");

    // 写 data.bin 到 path/data.bin
    // 格式：[id_len][id_bytes][vector_floats]
    std::ofstream ofs(meta_.root_path + "/" + meta_.name + "/data.bin", std::ios::binary);
    if (!ofs.is_open()) {
        throw std::runtime_error("Failed to open data file: " + meta_.root_path + "/" + meta_.name + "/data.bin");
    }

    for (const auto & entry : data_) {
        const std::string & id = entry.id;
        const std::vector<float> & vector = entry.vector;

        std::size_t id_len = id.size();
        ofs.write(reinterpret_cast<const char *>(&id_len), sizeof(id_len));
        ofs.write(id.data(), id_len);
        ofs.write(reinterpret_cast<const char *>(vector.data()), vector.size() * sizeof(vector[0]));
    }

    ofs.close();
}

void Segment::LoadMeta()
{
    // 读取 meta.json
    Meta::LoadMeta(meta_, meta_.root_path + "/" + meta_.name + "/meta.json");
}

void Segment::LoadIndex()
{
    // 读取 index.bin
    index_->Load(meta_.root_path + "/" + meta_.name + "/index.bin");
}

void Segment::LoadData()
{
    // 从 data.bin 中读取数据
    std::ifstream ifs(meta_.root_path + "/" + meta_.name + "/data.bin", std::ios::binary);
    if (!ifs.is_open()) {
        throw std::runtime_error("Failed to open data file: " + meta_.root_path + "/" + meta_.name + "/data.bin");
    }

    while (true) {
        std::size_t id_len = 0;
        if (!ifs.read(reinterpret_cast<char *>(&id_len), sizeof(id_len))) {
            break;
        }

        std::string id(id_len, '\0');
        if (!ifs.read(id.data(), id_len)) {
            break;
        }

        std::vector<float> vector(meta_.dimension);
        if (!ifs.read(reinterpret_cast<char *>(vector.data()), meta_.dimension * sizeof(float))) {
            break;
        }

        data_.emplace_back(id, vector);
    }

    ifs.close();
}

} // namespace WW
