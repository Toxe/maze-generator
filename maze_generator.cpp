#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

struct Node {
    bool visited = false;
    bool has_north_wall = true;
    bool has_east_wall = true;
    bool has_south_wall = true;
    bool has_west_wall = true;
};

enum class Directions {
    North,
    East,
    South,
    West
};

struct Coordinates {
    int x, y;
};

class Maze {
public:
    Maze(const int width, const int height) : width_{width}, height_{height}, nodes_(width * height) {}

    int width() const { return width_; }
    int height() const { return height_; }

    Node* node(const Coordinates coords) { return &nodes_[coords.y * width_ + coords.x]; }
    bool valid_coords(const Coordinates coords) const { return coords.x >= 0 && coords.y >= 0 && coords.x < width_ && coords.y < height_; }

private:
    int width_;
    int height_;
    std::vector<Node> nodes_;
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
            const Node* node = maze.node({x, y});

            if (node->has_north_wall)
                std::cout << "+--";
            else
                std::cout << "+  ";
        }

        std::cout << "+" << std::endl;

        for (int x = 0; x < maze.width(); ++x) {
            const Node* node = maze.node({x, y});

            if (node->has_west_wall)
                std::cout << "|  ";
            else
                std::cout << "   ";

            if (x == maze.width() - 1)
                if (node->has_east_wall)
                    std::cout << "|" << std::endl;
        }


        if (y == maze.height() - 1) {
            for (int x = 0; x < maze.width(); ++x) {
                const Node* node = maze.node({x, y});

                if (node->has_south_wall)
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

    Node* current_node = maze.node(coords);

    current_node->visited = true;

    for (const auto dir : directions) {
        Coordinates new_coords{coords_in_direction(coords, dir)};

        if (maze.valid_coords(new_coords)) {
            Node* next_node = maze.node(new_coords);

            if (!next_node->visited) {
                switch (dir) {
                case Directions::North:
                    current_node->has_north_wall = false;
                    next_node->has_south_wall = false;
                    break;
                case Directions::East:
                    current_node->has_east_wall = false;
                    next_node->has_west_wall = false;
                    break;
                case Directions::South:
                    current_node->has_south_wall = false;
                    next_node->has_north_wall = false;
                    break;
                case Directions::West:
                    current_node->has_west_wall = false;
                    next_node->has_east_wall = false;
                    break;
                }

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
