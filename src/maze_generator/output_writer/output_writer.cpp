#include "output_writer.hpp"

#include "data_output_writer.hpp"
#include "pretty_output_writer.hpp"
#include "raw_output_writer.hpp"
#include "text_output_writer.hpp"

namespace maze_generator::output_writer {

std::unique_ptr<OutputWriter> create_output_writer(output_target::OutputTarget& output_stream, OutputFormat output_format)
{
    switch (output_format) {
        case OutputFormat::Text: return std::make_unique<TextOutputWriter>(output_stream);
        case OutputFormat::Raw: return std::make_unique<RawOutputWriter>(output_stream);
        case OutputFormat::Pretty: return std::make_unique<PrettyOutputWriter>(output_stream);
        case OutputFormat::Data: return std::make_unique<DataOutputWriter>(output_stream);
    }
}

}  // namespace maze_generator::output_writer
