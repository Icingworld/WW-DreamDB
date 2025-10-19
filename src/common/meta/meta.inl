#include <fstream>
#include <stdexcept>

#include "common/json.h"

namespace WW::Meta
{

template <typename MetaType>
void SaveMeta(const MetaType & meta, const std::string & path)
{
    std::ofstream ofs(path);
    if (!ofs.is_open()) {
        throw std::runtime_error("Failed to open meta file: " + path);
    }

    ofs << meta.ToJson().dump(4);
}

template <typename MetaType>
void LoadMeta(MetaType & meta, const std::string & path)
{
    std::ifstream ifs(path);
    if (!ifs.is_open()) {
        throw std::runtime_error("Failed to open meta file: " + path);
    }

    Json j;
    ifs >> j;

    meta.FromJson(j);
    return meta;
}

} // namespace WW::Math
