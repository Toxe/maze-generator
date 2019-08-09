#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

class Maze {
    using Node = unsigned char;

public:
    enum class Directions {
        North = 0,
        East,
        South,
        West
    };

    enum class WallFlags {
        North = 0b0001,
        East  = 0b0010,
        South = 0b0100,
        West  = 0b1000
    };

    struct Coordinates {
        int x, y;
    };

    Maze(const int width, const int height)
        : width_{width},
          height_{height},
          nodes_(width * height, static_cast<Node>(Maze::WallFlags::North) | static_cast<Node>(Maze::WallFlags::East) | static_cast<Node>(Maze::WallFlags::South) | static_cast<Node>(Maze::WallFlags::West)) {}

    int width() const { return width_; }
    int height() const { return height_; }

    bool valid_coords(const Maze::Coordinates coords) const { return coords.x >= 0 && coords.y >= 0 && coords.x < width_ && coords.y < height_; }

    Maze::Coordinates coords_in_direction(const Maze::Coordinates coords, const Maze::Directions dir) {
        const Maze::Coordinates offset{direction_coords_offset_[static_cast<int>(dir)]};
        return Maze::Coordinates{coords.x + offset.x, coords.y + offset.y};
    }

    bool node_visited(const Maze::Coordinates coords) const { return nodes_[coords.y * width_ + coords.x] & 0b10000; }
    void set_node_visited(const Maze::Coordinates coords) { nodes_[coords.y * width_ + coords.x] |= 0b10000; }

    bool has_wall(const Maze::Coordinates coords, Maze::WallFlags wall) const { return nodes_[coords.y * width_ + coords.x] & static_cast<Node>(wall); }

    void clear_walls(const Maze::Coordinates orig, const Maze::Coordinates dest, Maze::Directions dir) {
        const Maze::WallFlags orig_wall = wall_in_direction_[static_cast<int>(dir)];
        const Maze::WallFlags dest_wall = wall_in_direction_[static_cast<int>(opposite_direction_[static_cast<int>(dir)])];
        nodes_[orig.y * width_ + orig.x] &= ~(static_cast<Node>(orig_wall));
        nodes_[dest.y * width_ + dest.x] &= ~(static_cast<Node>(dest_wall));
    }

private:
    const int width_;
    const int height_;
    std::vector<Node> nodes_;

    const Maze::WallFlags wall_in_direction_[4] = { Maze::WallFlags::North, Maze::WallFlags::East, Maze::WallFlags::South, Maze::WallFlags::West };
    const Maze::Directions opposite_direction_[4] = { Maze::Directions::South, Maze::Directions::West, Maze::Directions::North, Maze::Directions::East };
    const Maze::Coordinates direction_coords_offset_[4] = { Maze::Coordinates{0, -1}, Maze::Coordinates{1, 0}, Maze::Coordinates{0, 1}, Maze::Coordinates{-1, 0} };
};

void print(Maze& maze)
{
    for (int y = 0; y < maze.height(); ++y) {
        for (int x = 0; x < maze.width(); ++x) {
            if (maze.has_wall({x, y}, Maze::WallFlags::North))
                std::cout << "+--";
            else
                std::cout << "+  ";
        }

        std::cout << "+" << std::endl;

        for (int x = 0; x < maze.width(); ++x) {
            if (maze.has_wall({x, y}, Maze::WallFlags::West))
                std::cout << "|  ";
            else
                std::cout << "   ";

            if (x == maze.width() - 1)
                if (maze.has_wall({x, y}, Maze::WallFlags::East))
                    std::cout << "|" << std::endl;
        }

        if (y == maze.height() - 1) {
            for (int x = 0; x < maze.width(); ++x) {
                if (maze.has_wall({x, y}, Maze::WallFlags::South))
                    std::cout << "+--";
                else
                    std::cout << "+  ";
            }

            std::cout << "+" << std::endl;
        }
    }
}

void visit(Maze& maze, const Maze::Coordinates coords)
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::vector<Maze::Directions> directions{Maze::Directions::North, Maze::Directions::East, Maze::Directions::South, Maze::Directions::West};
    std::shuffle(directions.begin(), directions.end(), g);

    maze.set_node_visited(coords);

    for (const auto dir : directions) {
        Maze::Coordinates new_coords{maze.coords_in_direction(coords, dir)};

        if (maze.valid_coords(new_coords)) {
            if (!maze.node_visited(new_coords)) {
                maze.clear_walls(coords, new_coords, dir);
                visit(maze, new_coords);
            }
        }
    }
}

int main()
{
    constexpr int num_rows = 10;
    constexpr int num_cols = 10;

    Maze maze(num_cols, num_rows);

    visit(maze, {0, 0});
    print(maze);
}
