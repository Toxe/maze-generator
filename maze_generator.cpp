#include "clipp.h"
#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <random>
#include <tuple>
#include <vector>

class Maze {
public:
    using Node = unsigned char;

    enum class Directions { North = 0, East, South, West };
    enum class WallFlags { North = 0b0001, East = 0b0010, South = 0b0100, West = 0b1000 };

    struct Coordinates { int x, y; };

    Maze(const int width, const int height, const int seed = -1)
        : width_{width},
          height_{height},
          nodes_(static_cast<std::size_t>(width * height), static_cast<Node>(WallFlags::North) | static_cast<Node>(WallFlags::East) | static_cast<Node>(WallFlags::South) | static_cast<Node>(WallFlags::West)),
          random_device_(),
          random_generator_(random_device_()),
          random_dist_{0, 23} {
              if (seed >= 0)
                  random_generator_.seed(seed);
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

private:
    const int width_;
    const int height_;
    std::vector<Node> nodes_;

    std::random_device random_device_;
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

enum class OutputFormat { Text, RGB };

void output(Maze& maze, std::string filename, OutputFormat output_format)
{
    std::ofstream out{filename, std::ofstream::binary};

    if (output_format == OutputFormat::Text) {
        out << "width=" << maze.width() << "\n";
        out << "height=" << maze.height() << "\n";

        for (int y = 0; y < maze.height(); ++y) {
            for (int x = 0; x < maze.width(); ++x)
                out << (maze.has_wall({x, y}, Maze::WallFlags::North) ? "##" : "# ");

            out << "#" << "\n";

            for (int x = 0; x < maze.width(); ++x)
                out << (maze.has_wall({x, y}, Maze::WallFlags::West) ? "# " : "  ");

            out << "#" << "\n";
        }

        for (int x = 0; x < maze.width(); ++x)
            out << "##";

        out << "#" << "\n";
    } else {
        const unsigned char black = 0x00;
        const unsigned char white = 0xff;

        for (int y = 0; y < maze.height(); ++y) {
            for (int x = 0; x < maze.width(); ++x)
                if (maze.has_wall({x, y}, Maze::WallFlags::North))
                    out << white << white;
                else
                    out << white << black;

            out << white;

            for (int x = 0; x < maze.width(); ++x)
                if (maze.has_wall({x, y}, Maze::WallFlags::West))
                    out << white << black;
                else
                    out << black << black;

            out << white;
        }

        for (int x = 0; x < maze.width(); ++x)
            out << white << white;

        out << white;
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

bool str_ends_with(const std::string_view s, const std::string_view look_for)
{
    if (look_for.size() > s.size())
        return false;

    return s.find(look_for) == (s.size() - look_for.size());
}

std::optional<OutputFormat> get_output_format(const std::string& filename)
{
    if (str_ends_with(filename, ".maze"))
        return OutputFormat::Text;
    else if (str_ends_with(filename, ".raw"))
        return OutputFormat::RGB;

    return std::nullopt;
}

void show_usage_and_exit(const clipp::group& cli, const char* argv0, const char* error_message = nullptr)
{
    if (error_message)
        std::cout << error_message << "\n\n";

    std::string progname{std::filesystem::path{argv0}.filename().string()};
    std::cout << clipp::make_man_page(cli, progname).append_section("EXAMPLE", "        " + progname + " 20 20 test.maze") << std::endl;

    std::exit(1);
}

std::tuple<int, int, int, std::string, OutputFormat> eval_args(int argc, char* argv[])
{
    int seed = -1;
    int width, height;
    std::string filename;

    auto cli = (
        (clipp::option("-s", "--seed") & clipp::integer("seed", seed)) % "random seed (0 or bigger)",
        clipp::integer("width", width)                                 % "maze width",
        clipp::integer("height", height)                               % "maze height",
        clipp::value("filename", filename)                             % "output filename (has to end in .maze or .raw)"
    );

    if (!clipp::parse(argc, argv, cli))
        show_usage_and_exit(cli, argv[0]);

    if (width < 1 || height < 1)
        show_usage_and_exit(cli, argv[0], "Error: Maze width and height need to be at least 1");

    auto output_format = get_output_format(filename);

    if (!output_format.has_value())
        show_usage_and_exit(cli, argv[0], "Error: Output filename has to end in either .maze or .raw");

    return std::make_tuple(seed, width, height, filename, *output_format);
}

int main(int argc, char* argv[])
{
    auto [seed, width, height, filename, output_format] = eval_args(argc, argv);

    Maze maze(width, height, seed);

    generate(maze, {0, 0});
    output(maze, filename, output_format);
}
