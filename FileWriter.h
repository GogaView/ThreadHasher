#pragma once

#include <boost/filesystem.hpp>

#include <map>
#include <fstream>
#include <thread>

class FileWriter
{

public:
    explicit FileWriter(const boost::filesystem::path& phinputFile);
    ~FileWriter();

    void addHash(unsigned uIndex, size_t vHash);

    void waitForFlushAllData();

private:
    size_t takeHashByIndex(unsigned uIndex);
    void flashHash();

private:
    std::mutex m_Mutex;
    std::ofstream m_ofOutputFile;
    unsigned m_uCurrIndex;

    std::map<unsigned, size_t > m_MapHash;
    std::unique_ptr<std::thread> m_pFlusherThread;
};
