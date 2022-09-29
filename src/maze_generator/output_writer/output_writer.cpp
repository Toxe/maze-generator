#include "output_writer.hpp"

#include <iostream>

#include "writers/data_output_writer.hpp"
#include "writers/pretty_output_writer.hpp"
#include "writers/raw_output_writer.hpp"
#include "writers/text_output_writer.hpp"

namespace maze_generator::output_writer {

void OutputWriter::output_info(const maze::Maze& maze, const int)
{
    const auto size = maze.size();

    std::cout << "width: " << size.width << '\n';
    std::cout << "height: " << size.height << '\n';
    std::cout << "seed: " << maze.seed() << '\n';
}

void OutputWriter::write(const char c)
{
    out_ << c;
}

void OutputWriter::write(const unsigned char c)
{
    out_ << c;
}

void OutputWriter::write(const char* s)
{
    out_ << s;
}

std::unique_ptr<OutputWriter> create_output_writer(output_target::OutputTarget& output_stream, OutputFormat output_format)
{
    switch (output_format) {
        case OutputFormat::Text: return std::make_unique<TextOutputWriter>(output_stream);
        case OutputFormat::Raw: return std::make_unique<RawOutputWriter>(output_stream);
        case OutputFormat::Pretty: return std::make_unique<PrettyOutputWriter>(output_stream);
        case OutputFormat::Data: return std::make_unique<DataOutputWriter>(output_stream);
        default:
            return nullptr;
    }
}

}  // namespace maze_generator::output_writer
