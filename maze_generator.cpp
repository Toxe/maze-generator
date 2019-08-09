#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

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

const WallFlags wall_in_direction[] = { WallFlags::North, WallFlags::East, WallFlags::South, WallFlags::West };
const Directions opposite_direction[] = { Directions::South, Directions::West, Directions::North, Directions::East };

class Maze {
public:
    Maze(const int width, const int height)
        : width_{width},
          height_{height},
          nodes_(width * height, static_cast<unsigned char>(WallFlags::North) | static_cast<unsigned char>(WallFlags::East) | static_cast<unsigned char>(WallFlags::South) | static_cast<unsigned char>(WallFlags::West)) {}

    int width() const { return width_; }
    int height() const { return height_; }

    bool valid_coords(const Coordinates coords) const { return coords.x >= 0 && coords.y >= 0 && coords.x < width_ && coords.y < height_; }

    bool node_visited(const Coordinates coords) const { return nodes_[coords.y * width_ + coords.x] & 0b10000; }
    void set_node_visited(const Coordinates coords) { nodes_[coords.y * width_ + coords.x] |= 0b10000; }

    bool has_wall(const Coordinates coords, WallFlags wall) const { return nodes_[coords.y * width_ + coords.x] & static_cast<unsigned char>(wall); }

    void clear_walls(const Coordinates orig, const Coordinates dest, Directions dir) {
        const WallFlags orig_wall = wall_in_direction[static_cast<int>(dir)];
        const WallFlags dest_wall = wall_in_direction[static_cast<int>(opposite_direction[static_cast<int>(dir)])];
        nodes_[orig.y * width_ + orig.x] &= ~(static_cast<unsigned char>(orig_wall));
        nodes_[dest.y * width_ + dest.x] &= ~(static_cast<unsigned char>(dest_wall));
    }

private:
    int width_;
    int height_;
    std::vector<unsigned char> nodes_;
};

Coordinates coords_in_direction(const Coordinates coords, const Directions dir)
{
    Coordinates new_coords{coords};

    switch (dir) {
    case Directions::North:
        new_coords.y = coords.y - 1;
        break;
    case Directions::East:
        new_coords.x = coords.x + 1;
        break;
    case Directions::South:
        new_coords.y = coords.y + 1;
        break;
    case Directions::West:
        new_coords.x = coords.x - 1;
        break;
    }

    return new_coords;
}

void print(Maze& maze)
{
    for (int y = 0; y < maze.height(); ++y) {
        for (int x = 0; x < maze.width(); ++x) {
            if (maze.has_wall({x, y}, WallFlags::North))
                std::cout << "+--";
            else
                std::cout << "+  ";
        }

        std::cout << "+" << std::endl;

        for (int x = 0; x < maze.width(); ++x) {
            if (maze.has_wall({x, y}, WallFlags::West))
                std::cout << "|  ";
            else
                std::cout << "   ";

            if (x == maze.width() - 1)
                if (maze.has_wall({x, y}, WallFlags::East))
                    std::cout << "|" << std::endl;
        }

        if (y == maze.height() - 1) {
            for (int x = 0; x < maze.width(); ++x) {
                if (maze.has_wall({x, y}, WallFlags::South))
                    std::cout << "+--";
                else
                    std::cout << "+  ";
            }

            std::cout << "+" << std::endl;
        }
    }
}

void visit(Maze& maze, const Coordinates coords)
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::vector<Directions> directions{Directions::North, Directions::East, Directions::South, Directions::West};
    std::shuffle(directions.begin(), directions.end(), g);

    maze.set_node_visited(coords);

    for (const auto dir : directions) {
        Coordinates new_coords{coords_in_direction(coords, dir)};

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
