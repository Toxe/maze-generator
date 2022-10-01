#pragma once

#include <cstdint>

#include "types.hpp"

namespace maze_generator::maze {

class Node {
public:
    constexpr Node() : node_(0) { }
    constexpr explicit Node(const uint8_t bitmask) : node_(bitmask) { }
    constexpr explicit Node(const Wall wall) : node_(static_cast<uint8_t>(wall)) { }

    [[nodiscard]] constexpr static Node with_all_walls()
    {
        return Node{Wall::North | Wall::East | Wall::South | Wall::West};
    }

    [[nodiscard]] constexpr bool has_wall(const Wall wall) const
    {
        return (node_ & static_cast<uint8_t>(wall)) == static_cast<uint8_t>(wall);
    }

    constexpr void set_wall(const uint8_t bitmask)
    {
        node_ |= bitmask;
    }

    constexpr void set_wall(const Wall wall)
    {
        set_wall(static_cast<uint8_t>(wall));
    }

    constexpr void clear_wall(const Wall wall)
    {
        const uint8_t bits = ~static_cast<uint8_t>(wall);
        node_ &= bits;
    }

    [[nodiscard]] constexpr bool visited() const { return (node_ & 0b10000) == 0b10000; }
    constexpr void set_visited() { node_ |= 0b10000; }

    [[nodiscard]] constexpr uint8_t value() const { return node_ & 0b1111; }

private:
    uint8_t node_;
};

}  // namespace maze_generator::maze
