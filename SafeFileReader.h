#pragma once

#include <boost/filesystem.hpp>

#include <mutex>
#include <fstream>

class SafeFileReader
{
public:
    explicit SafeFileReader(const boost::filesystem::path& phinputFile, unsigned uBlockSize);
    std::pair<std::vector<char>, unsigned> readNext();

private:
    std::vector<char> readDataBlock();

private:
    const unsigned m_uBlockSizeByte;
    std::mutex m_Mutex;

    std::ifstream m_ifIntutFile;
    bool m_bIsDataExist;
    unsigned m_uIndex;
};

