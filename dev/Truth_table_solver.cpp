#include <unordered_set>
#include <cstdint>
#include <vector>

typedef std::uint16_t us;
struct vert{
    const std::unordered_set<us> signals;
    const vert* parent;

};