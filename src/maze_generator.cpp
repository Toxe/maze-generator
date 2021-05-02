#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "cli.h"

class Maze {
public:
    using Node = unsigned char;

    enum class Directions { North = 0, East, South, West };
    enum class WallFlags { North = 0b0001, East = 0b0010, South = 0b0100, West = 0b1000 };

    struct Coordinates {
        Coordinates(const int ix, const int iy) : x{ix}, y{iy} {}
        Coordinates(const std::size_t ix, const std::size_t iy) : x{static_cast<int>(ix)}, y{static_cast<int>(iy)} {}
        int x, y;
    };

    Maze(const int width, const int height, const int seed = -1)
        : width_{width},
          height_{height},
          nodes_(static_cast<std::size_t>(width * height), static_cast<Node>(WallFlags::North) | static_cast<Node>(WallFlags::East) | static_cast<Node>(WallFlags::South) | static_cast<Node>(WallFlags::West)),
          random_device_(),
          random_generator_(random_device_()),
          random_dist_{0, 23}
    {
        seed_ = (seed >= 0) ? static_cast<std::random_device::result_type>(seed) : random_device_();
        random_generator_.seed(seed_);
    }

    int width() const { return width_; }
    int height() const { return height_; }

    bool valid_coords(const Coordinates coords) const { return coords.x >= 0 && coords.y >= 0 && coords.x < width_ && coords.y < height_; }

    Coordinates coords_in_direction(const Coordinates coords, const Directions dir) {
        const Coordinates offset{direction_coords_offset_[static_cast<int>(dir)]};
        return Coordinates{coords.x + offset.x, coords.y + offset.y};
    }

    const Directions* random_directions() { return all_possible_random_directions[random_dist_(random_generator_)]; }

    Node& node(const Coordinates coords) { return nodes_[static_cast<std::size_t>(coords.y * width_ + coords.x)]; }
    bool node_visited(const Coordinates coords) { return node(coords) & 0b10000; }
    void set_node_visited(const Coordinates coords) { node(coords) |= 0b10000; }

    bool has_wall(const Coordinates coords, WallFlags wall) { return node(coords) & static_cast<Node>(wall); }
    void clear_walls(const Coordinates orig, const Coordinates dest, Directions dir) {
        const WallFlags orig_wall = wall_in_direction_[static_cast<int>(dir)];
        const WallFlags dest_wall = wall_in_direction_[static_cast<int>(opposite_direction_[static_cast<int>(dir)])];
        node(orig) &= ~(static_cast<Node>(orig_wall));
        node(dest) &= ~(static_cast<Node>(dest_wall));
    }

    std::random_device::result_type seed() const { return seed_; }

private:
    const int width_;
    const int height_;
    std::vector<Node> nodes_;

    std::random_device random_device_;
    std::random_device::result_type seed_;
    std::mt19937 random_generator_;
    std::uniform_int_distribution<> random_dist_;

    const WallFlags wall_in_direction_[4] = { WallFlags::North, WallFlags::East, WallFlags::South, WallFlags::West };
    const Directions opposite_direction_[4] = { Directions::South, Directions::West, Directions::North, Directions::East };
    const Coordinates direction_coords_offset_[4] = { Coordinates{0, -1}, Coordinates{1, 0}, Coordinates{0, 1}, Coordinates{-1, 0} };
    const Directions all_possible_random_directions[24][4] = {
        {Directions::North, Directions::East,  Directions::South, Directions::West},
        {Directions::North, Directions::East,  Directions::West,  Directions::South},
        {Directions::North, Directions::South, Directions::East,  Directions::West},
        {Directions::North, Directions::South, Directions::West,  Directions::East},
        {Directions::North, Directions::West,  Directions::East,  Directions::South},
        {Directions::North, Directions::West,  Directions::South, Directions::East},
        {Directions::East,  Directions::North, Directions::South, Directions::West},
        {Directions::East,  Directions::North, Directions::West,  Directions::South},
        {Directions::East,  Directions::South, Directions::North, Directions::West},
        {Directions::East,  Directions::South, Directions::West,  Directions::North},
        {Directions::East,  Directions::West,  Directions::North, Directions::South},
        {Directions::East,  Directions::West,  Directions::South, Directions::North},
        {Directions::South, Directions::North, Directions::East,  Directions::West},
        {Directions::South, Directions::North, Directions::West,  Directions::East},
        {Directions::South, Directions::East,  Directions::North, Directions::West},
        {Directions::South, Directions::East,  Directions::West,  Directions::North},
        {Directions::South, Directions::West,  Directions::North, Directions::East},
        {Directions::South, Directions::West,  Directions::East,  Directions::North},
        {Directions::West,  Directions::North, Directions::East,  Directions::South},
        {Directions::West,  Directions::North, Directions::South, Directions::East},
        {Directions::West,  Directions::East,  Directions::North, Directions::South},
        {Directions::West,  Directions::East,  Directions::South, Directions::North},
        {Directions::West,  Directions::South, Directions::North, Directions::East},
        {Directions::West,  Directions::South, Directions::East,  Directions::North}};
};

struct StackNode {
    StackNode(const Maze::Coordinates c, const Maze::Directions* d) : coords{c}, check_directions{d}, rnd_idx{0} {}

    const Maze::Coordinates coords;
    const Maze::Directions* check_directions;
    int rnd_idx;
};

void output_info(std::ostream& out, const Maze& maze, OutputFormat output_format, int zoom)
{
    out << "width=" << maze.width() << "\n";
    out << "height=" << maze.height() << "\n";
    out << "seed=" << maze.seed() << "\n";

    if (output_format == OutputFormat::Raw) {
        out << "image width=" << (zoom * (2 * maze.width() + 1)) << "\n";
        out << "image height=" << (zoom * (2 * maze.height() + 1)) << "\n";
        out << "image format=1 byte per pixel, grayscale\n";
    }
}

void output(Maze& maze, const std::string& filename, OutputFormat output_format, int zoom, bool show_info)
{
    std::streambuf* sbuf;
    std::ofstream out_file;

    // write output to either file or stdout
    if (filename != "") {
        out_file.open(filename, std::ofstream::binary);
        sbuf = out_file.rdbuf();
    } else {
        sbuf = std::cout.rdbuf();
    }

    std::ostream out(sbuf);

    if (show_info) {
        if (output_format == OutputFormat::Raw) {
            // info in Raw mode always goes to stdout and only if writing maze data to a file
            if (filename != "")
                output_info(std::cout, maze, output_format, zoom);
        } else {
            output_info(out, maze, output_format, zoom);
        }
    }

    // create grid with wall data
    const int grid_width = 2 * maze.width() + 1;
    const int grid_height = 2 * maze.height() + 1;
    std::vector<std::vector<Maze::Node>> grid(static_cast<std::size_t>(grid_height));

    for (std::size_t y = 0; y < static_cast<std::size_t>(grid_height); ++y) {
        grid[y].reserve(static_cast<std::size_t>(grid_width));

        for (std::size_t x = 0; x < static_cast<std::size_t>(grid_width); ++x)
            grid[y].push_back(0);
    }

    for (std::size_t y = 0; y < static_cast<std::size_t>(maze.height()); ++y) {
        for (std::size_t x = 0; x < static_cast<std::size_t>(maze.width()); ++x) {
            if (maze.has_wall({x, y}, Maze::WallFlags::North)) {
                grid[2*y][2*x    ] |= static_cast<Maze::Node>(Maze::WallFlags::East);
                grid[2*y][2*x + 1] |= static_cast<Maze::Node>(Maze::WallFlags::East) | static_cast<Maze::Node>(Maze::WallFlags::West);
                grid[2*y][2*x + 2] |= static_cast<Maze::Node>(Maze::WallFlags::West);
            }

            if (maze.has_wall({x, y}, Maze::WallFlags::East)) {
                grid[2*y    ][2*x + 2] |= static_cast<Maze::Node>(Maze::WallFlags::South);
                grid[2*y + 1][2*x + 2] |= static_cast<Maze::Node>(Maze::WallFlags::North) | static_cast<Maze::Node>(Maze::WallFlags::South);
                grid[2*y + 2][2*x + 2] |= static_cast<Maze::Node>(Maze::WallFlags::North);
            }

            if (maze.has_wall({x, y}, Maze::WallFlags::South)) {
                grid[2*y + 2][2*x    ] |= static_cast<Maze::Node>(Maze::WallFlags::East);
                grid[2*y + 2][2*x + 1] |= static_cast<Maze::Node>(Maze::WallFlags::East) | static_cast<Maze::Node>(Maze::WallFlags::West);
                grid[2*y + 2][2*x + 2] |= static_cast<Maze::Node>(Maze::WallFlags::West);
            }

            if (maze.has_wall({x, y}, Maze::WallFlags::West)) {
                grid[2*y    ][2*x] |= static_cast<Maze::Node>(Maze::WallFlags::South);
                grid[2*y + 1][2*x] |= static_cast<Maze::Node>(Maze::WallFlags::North) | static_cast<Maze::Node>(Maze::WallFlags::South);
                grid[2*y + 2][2*x] |= static_cast<Maze::Node>(Maze::WallFlags::North);
            }
        }
    }

    if (output_format == OutputFormat::Text) {
        for (std::size_t y = 0; y < grid.size(); ++y) {
            for (std::size_t x = 0; x < grid[y].size(); ++x)
                out << (grid[y][x] == 0 ? ' ' : '#');

            out << "\n";
        }
    } else if (output_format == OutputFormat::Raw) {
        const unsigned char black = 0x00;
        const unsigned char white = 0xff;

        for (std::size_t y = 0; y < grid.size(); ++y) {
            for (int r = 0; r < zoom; ++r) {
                for (std::size_t x = 0; x < grid[y].size(); ++x) {
                    auto c = grid[y][x];

                    for (int z = 0; z < zoom; ++z)
                        out << (c == 0 ? black : white);
                }
            }
        }
    } else if (output_format == OutputFormat::Pretty) {
        for (std::size_t y = 0; y < grid.size(); ++y) {
            for (std::size_t x = 0; x < grid[y].size(); ++x) {
                switch (grid[y][x]) {
                    case 0b0000: out << reinterpret_cast<const char*>(u8"  ");           break;  // |  |
                    case 0b0001: out << reinterpret_cast<const char*>(u8"\u2575 ");      break;  // |╵ |
                    case 0b0010: out << reinterpret_cast<const char*>(u8" \u2500");      break;  // | ─|
                    case 0b0011: out << reinterpret_cast<const char*>(u8"\u2514\u2500"); break;  // |└─|
                    case 0b0100: out << reinterpret_cast<const char*>(u8"\u2577 ");      break;  // |╷ |
                    case 0b0101: out << reinterpret_cast<const char*>(u8"\u2502 ");      break;  // |│ |
                    case 0b0110: out << reinterpret_cast<const char*>(u8"\u250c\u2500"); break;  // |┌─|
                    case 0b0111: out << reinterpret_cast<const char*>(u8"\u251C\u2500"); break;  // |├─|
                    case 0b1000: out << reinterpret_cast<const char*>(u8"\u2500 ");      break;  // |─ |
                    case 0b1001: out << reinterpret_cast<const char*>(u8"\u2518 ");      break;  // |┘ |
                    case 0b1010: out << reinterpret_cast<const char*>(u8"\u2500\u2500"); break;  // |──|
                    case 0b1011: out << reinterpret_cast<const char*>(u8"\u2534\u2500"); break;  // |┴─|
                    case 0b1100: out << reinterpret_cast<const char*>(u8"\u2510 ");      break;  // |┐ |
                    case 0b1101: out << reinterpret_cast<const char*>(u8"\u2524 ");      break;  // |┤ |
                    case 0b1110: out << reinterpret_cast<const char*>(u8"\u252C\u2500"); break;  // |┬─|
                    case 0b1111: out << reinterpret_cast<const char*>(u8"\u253C\u2500"); break;  // |┼─|
                }
            }

            out << "\n";
        }
    } else if (output_format == OutputFormat::Data) {
        for (int y = 0; y < maze.height(); ++y) {
            for (int x = 0; x < maze.width(); ++x) {
                out << (maze.has_wall({x, y}, Maze::WallFlags::North) ? "N" : "-");
                out << (maze.has_wall({x, y}, Maze::WallFlags::East)  ? "E" : "-");
                out << (maze.has_wall({x, y}, Maze::WallFlags::South) ? "S" : "-");
                out << (maze.has_wall({x, y}, Maze::WallFlags::West)  ? "W" : "-");

                if (x < maze.width() - 1)
                    out << "|";
            }

            out << "\n";
        }
    }
}

void generate(Maze& maze, const Maze::Coordinates starting_point)
{
    std::vector<StackNode> stack;

    maze.set_node_visited(starting_point);
    stack.emplace_back(starting_point, maze.random_directions());

    while (!stack.empty()) {
        StackNode& current_node = stack.back();

        if (current_node.rnd_idx < 4) {
            bool keep_checking = true;

            while (keep_checking && current_node.rnd_idx < 4) {
                const auto dir = current_node.check_directions[current_node.rnd_idx];
                ++current_node.rnd_idx;

                Maze::Coordinates next_coords{maze.coords_in_direction(current_node.coords, dir)};

                if (maze.valid_coords(next_coords) && !maze.node_visited(next_coords)) {
                    maze.clear_walls(current_node.coords, next_coords, dir);
                    maze.set_node_visited(next_coords);

                    stack.emplace_back(next_coords, maze.random_directions());
                    keep_checking = false;
                }
            }
        } else {
            stack.pop_back();
        }
    }
}

int main(int argc, char* argv[])
{
    auto [seed, width, height, filename, output_format, zoom, info] = eval_args(argc, argv);
    Maze maze(width, height, seed);

    generate(maze, {0, 0});
    output(maze, filename, output_format, zoom, info);
}
