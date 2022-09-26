#include "catch2/catch_test_macros.hpp"

#include "node.hpp"

namespace maze_generator::maze {

TEST_CASE("maze::Node")
{
    SECTION("a new Node has no walls set")
    {
        const Node node;

        CHECK(!node.has_wall(Wall::North));
        CHECK(!node.has_wall(Wall::East));
        CHECK(!node.has_wall(Wall::South));
        CHECK(!node.has_wall(Wall::West));
    }

    SECTION("a new Node has not been visited yet")
    {
        const Node node;

        CHECK(!node.visited());
    }

    SECTION("can create Node with a Wall")
    {
        const Node node(Wall::East);

        CHECK(node.has_wall(Wall::East));
        CHECK(!node.has_wall(Wall::North));
        CHECK(!node.has_wall(Wall::South));
        CHECK(!node.has_wall(Wall::West));
    }

    SECTION("can create Node with a bitmask")
    {
        const Node node(static_cast<uint8_t>(Wall::South));

        CHECK(node.has_wall(Wall::South));
        CHECK(!node.has_wall(Wall::North));
        CHECK(!node.has_wall(Wall::East));
        CHECK(!node.has_wall(Wall::West));
    }

    SECTION("with_all_walls() creates a Node with all walls set")
    {
        const auto node = Node::with_all_walls();

        CHECK(node.has_wall(Wall::North));
        CHECK(node.has_wall(Wall::East));
        CHECK(node.has_wall(Wall::South));
        CHECK(node.has_wall(Wall::West));
    }

    SECTION("can set walls")
    {
        Node node;

        node.set_wall(Wall::West);

        CHECK(node.has_wall(Wall::West));
        CHECK(!node.has_wall(Wall::North));
        CHECK(!node.has_wall(Wall::East));
        CHECK(!node.has_wall(Wall::South));
    }

    SECTION("can clear walls")
    {
        auto node = Node::with_all_walls();

        node.clear_wall(Wall::West);

        CHECK(!node.has_wall(Wall::West));
        CHECK(node.has_wall(Wall::North));
        CHECK(node.has_wall(Wall::East));
        CHECK(node.has_wall(Wall::South));
    }

    SECTION("can set visited flag")
    {
        Node node;

        node.set_visited();

        CHECK(node.visited());
    }

    SECTION("value() returns the wall bitmask")
    {
        const Node node(0b1111);

        CHECK(node.value() == 0b1111);
    }

    SECTION("value() bitmask does not contain the visited flag")
    {
        Node node(0b1111);

        node.set_visited();

        CHECK(node.value() == 0b1111);
    }
}

}  // namespace maze_generator::maze
