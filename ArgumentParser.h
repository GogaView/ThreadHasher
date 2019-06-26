#pragma once

#include <boost/filesystem.hpp>

class ArgumentParser
{
public:
    explicit ArgumentParser(int argc, char** argv);

    boost::filesystem::path getInputFileName() const;
    boost::filesystem::path getOutputFileName() const;
    unsigned getBlockSize() const;

private:
    boost::filesystem::path m_phInputFileName;
    boost::filesystem::path m_phOutputFileName;
    unsigned m_uBlockSizeMb;
};
