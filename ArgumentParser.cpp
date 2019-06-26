#include "ArgumentParser.h"
#include "HasherException.h"

#include <boost/program_options.hpp>

namespace po = boost::program_options;
namespace filesystem = boost::filesystem;

ArgumentParser::ArgumentParser(int argc, char** argv)
{
    po::options_description desc("General options");
    desc.add_options()
            ("help,h", "Show help")
            ("input,i", po::value<filesystem::path>(&m_phInputFileName), "Input file")
            ("output,o", po::value<filesystem::path>(&m_phOutputFileName), "Output file")
            ("size,s", po::value<unsigned>(&m_uBlockSizeMb)->default_value(1), "Block size (mb)");

    po::variables_map vm;
    try {
        auto parsed = po::command_line_parser(argc, argv).options(desc).allow_unregistered().run();
        po::store(parsed, vm);
        po::notify(vm);
    }
    catch(po::error& err)
    {
    }

    if(vm.count("help"))
    {
        std::stringstream ss;
        ss << desc;
        throw hasher_exception(ss.str());
    }

    if(m_phInputFileName.empty())
        throw hasher_exception("Invalid input path");

    if(m_phInputFileName.empty())
        throw hasher_exception("Invalid output path");

    if(m_uBlockSizeMb == 0)
        throw hasher_exception("Invalid block size");

}

boost::filesystem::path ArgumentParser::getInputFileName() const
{
    return m_phInputFileName;
}

boost::filesystem::path ArgumentParser::getOutputFileName() const
{
    return m_phOutputFileName;
}

unsigned ArgumentParser::getBlockSize() const
{
    return m_uBlockSizeMb;
}