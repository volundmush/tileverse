#include "tileverse/Prelude.hpp"
#include <unordered_set>

static std::unordered_set<std::string> pool;

std::string_view intern(const std::string& str) {
    auto it = pool.find(str);
    if (it != pool.end()) {
        return std::string_view(it->c_str(), it->size());
    }
    auto [newIt, success] = pool.emplace(str);
    return std::string_view(newIt->c_str(), newIt->size());
}