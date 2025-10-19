#include "db/dream_db.h"

#include <filesystem>

namespace WW
{

DreamDB::DreamDB(const std::string & root_path)
    : root_path_(root_path)
    , collections_()
{
    std::filesystem::create_directories(root_path_);
}

std::shared_ptr<Collection> DreamDB::CreateCollection(const std::string & name, int dimension, std::size_t segment_size)
{
    if (collections_.count(name) != 0) {
        return collections_[name];
    }

    CollectionMeta meta = CollectionMeta{name, root_path_, dimension, segment_size};
    std::shared_ptr<Collection> collection = std::make_shared<Collection>(meta);
    collections_[name] = collection;
    return collection;
}

std::shared_ptr<Collection> DreamDB::GetCollection(const std::string & name)
{
    if (collections_.count(name) != 0) {
        return collections_[name];
    }
    return nullptr;
}

bool DreamDB::DropCollection(const std::string & name)
{
    if (collections_.count(name) != 0) {
        collections_.erase(name);
        return true;
    }
    return false;
}

} // namespace WW
