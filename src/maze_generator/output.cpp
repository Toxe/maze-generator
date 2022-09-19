#include "output.hpp"

#include <fstream>
#include <iostream>

#include "maze.hpp"

namespace maze_generator {

void output_info(std::ostream& out, const Maze* maze, const OutputFormat output_format, const int zoom)
{
    const auto size = maze->size();

    out << "width=" << size.width << '\n';
    out << "height=" << size.height << '\n';
    out << "seed=" << maze->seed() << '\n';

    if (output_format == OutputFormat::Raw) {
        out << "image width=" << (zoom * (2 * size.width + 1)) << '\n';
        out << "image height=" << (zoom * (2 * size.height + 1)) << '\n';
        out << "image format=1 byte per pixel, grayscale\n";
    }
}

void output(Maze* maze, const std::string& filename, const OutputFormat output_format, const int zoom, const bool show_info)
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
    const auto size = maze->size();
    const int grid_width = 2 * size.width + 1;
    const int grid_height = 2 * size.height + 1;
    std::vector<std::vector<Maze::Node>> grid(static_cast<std::size_t>(grid_height));

    for (std::size_t y = 0; y < static_cast<std::size_t>(grid_height); ++y) {
        grid[y].reserve(static_cast<std::size_t>(grid_width));

        for (std::size_t x = 0; x < static_cast<std::size_t>(grid_width); ++x)
            grid[y].push_back(0);
    }

    for (std::size_t y = 0; y < static_cast<std::size_t>(size.height); ++y) {
        for (std::size_t x = 0; x < static_cast<std::size_t>(size.width); ++x) {
            if (maze->has_wall({x, y}, Maze::WallFlags::North)) {
                grid[2 * y][2 * x] |= static_cast<Maze::Node>(Maze::WallFlags::East);
                grid[2 * y][2 * x + 1] |= static_cast<Maze::Node>(Maze::WallFlags::East) | static_cast<Maze::Node>(Maze::WallFlags::West);
                grid[2 * y][2 * x + 2] |= static_cast<Maze::Node>(Maze::WallFlags::West);
            }

            if (maze->has_wall({x, y}, Maze::WallFlags::East)) {
                grid[2 * y][2 * x + 2] |= static_cast<Maze::Node>(Maze::WallFlags::South);
                grid[2 * y + 1][2 * x + 2] |= static_cast<Maze::Node>(Maze::WallFlags::North) | static_cast<Maze::Node>(Maze::WallFlags::South);
                grid[2 * y + 2][2 * x + 2] |= static_cast<Maze::Node>(Maze::WallFlags::North);
            }

            if (maze->has_wall({x, y}, Maze::WallFlags::South)) {
                grid[2 * y + 2][2 * x] |= static_cast<Maze::Node>(Maze::WallFlags::East);
                grid[2 * y + 2][2 * x + 1] |= static_cast<Maze::Node>(Maze::WallFlags::East) | static_cast<Maze::Node>(Maze::WallFlags::West);
                grid[2 * y + 2][2 * x + 2] |= static_cast<Maze::Node>(Maze::WallFlags::West);
            }

            if (maze->has_wall({x, y}, Maze::WallFlags::West)) {
                grid[2 * y][2 * x] |= static_cast<Maze::Node>(Maze::WallFlags::South);
                grid[2 * y + 1][2 * x] |= static_cast<Maze::Node>(Maze::WallFlags::North) | static_cast<Maze::Node>(Maze::WallFlags::South);
                grid[2 * y + 2][2 * x] |= static_cast<Maze::Node>(Maze::WallFlags::North);
            }
        }
    }

    if (output_format == OutputFormat::Text) {
        for (std::size_t y = 0; y < grid.size(); ++y) {
            for (std::size_t x = 0; x < grid[y].size(); ++x)
                out << (grid[y][x] == 0 ? ' ' : '#');

            out << '\n';
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
                    case 0b0000: out << reinterpret_cast<const char*>(u8"  "); break;  // |  |
                    case 0b0001: out << reinterpret_cast<const char*>(u8"\u2575 "); break;  // |╵ |
                    case 0b0010: out << reinterpret_cast<const char*>(u8" \u2500"); break;  // | ─|
                    case 0b0011: out << reinterpret_cast<const char*>(u8"\u2514\u2500"); break;  // |└─|
                    case 0b0100: out << reinterpret_cast<const char*>(u8"\u2577 "); break;  // |╷ |
                    case 0b0101: out << reinterpret_cast<const char*>(u8"\u2502 "); break;  // |│ |
                    case 0b0110: out << reinterpret_cast<const char*>(u8"\u250c\u2500"); break;  // |┌─|
                    case 0b0111: out << reinterpret_cast<const char*>(u8"\u251C\u2500"); break;  // |├─|
                    case 0b1000: out << reinterpret_cast<const char*>(u8"\u2500 "); break;  // |─ |
                    case 0b1001: out << reinterpret_cast<const char*>(u8"\u2518 "); break;  // |┘ |
                    case 0b1010: out << reinterpret_cast<const char*>(u8"\u2500\u2500"); break;  // |──|
                    case 0b1011: out << reinterpret_cast<const char*>(u8"\u2534\u2500"); break;  // |┴─|
                    case 0b1100: out << reinterpret_cast<const char*>(u8"\u2510 "); break;  // |┐ |
                    case 0b1101: out << reinterpret_cast<const char*>(u8"\u2524 "); break;  // |┤ |
                    case 0b1110: out << reinterpret_cast<const char*>(u8"\u252C\u2500"); break;  // |┬─|
                    case 0b1111: out << reinterpret_cast<const char*>(u8"\u253C\u2500"); break;  // |┼─|
                }
            }

            out << '\n';
        }
    } else if (output_format == OutputFormat::Data) {
        for (int y = 0; y < size.height; ++y) {
            for (int x = 0; x < size.width; ++x) {
                out << (maze->has_wall({x, y}, Maze::WallFlags::North) ? "N" : "-");
                out << (maze->has_wall({x, y}, Maze::WallFlags::East) ? "E" : "-");
                out << (maze->has_wall({x, y}, Maze::WallFlags::South) ? "S" : "-");
                out << (maze->has_wall({x, y}, Maze::WallFlags::West) ? "W" : "-");

                if (x < size.width - 1)
                    out << "|";
            }

            out << '\n';
        }
    }
}

}  // namespace maze_generator
