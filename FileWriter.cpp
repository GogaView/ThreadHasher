#include "FileWriter.h"
#include "HasherException.h"

FileWriter::FileWriter(const boost::filesystem::path& phOutputFile)
    : m_uCurrIndex(0)
{
    try
    {
        if(!boost::filesystem::exists(phOutputFile.parent_path()))
            boost::filesystem::create_directories(phOutputFile.parent_path());
    }
    catch(boost::filesystem::filesystem_error&)
    {
        throw hasher_exception("Can't create output dir");
    }

    m_ofOutputFile.open(phOutputFile.string(), std::ios::out | std::ios::binary);
    if(!m_ofOutputFile.is_open())
        throw hasher_exception("Can't open output file");
}

FileWriter::~FileWriter()
{
    if(m_pFlusherThread && m_pFlusherThread->joinable())
        m_pFlusherThread->join();
}

void FileWriter::addHash(unsigned uIndex, size_t vHash)
{
    std::lock_guard<std::mutex> Locker(m_Mutex);

    m_MapHash[uIndex] = vHash;
    flashHash();
}

void FileWriter::waitForFlushAllData()
{
    if(m_pFlusherThread)
        m_pFlusherThread->join();
}

size_t FileWriter::takeHashByIndex(unsigned uIndex)
{
    auto it = m_MapHash.find(uIndex);
    if(it != m_MapHash.end())
    {
        auto vHash = it->second;
        m_MapHash.erase(it);
        return vHash;
    }
    else
        return 0;
}

void FileWriter::flashHash()
{
    while(true)
    {
        auto Hash = takeHashByIndex(m_uCurrIndex);
        if(!Hash)
            break;
        else{
            m_ofOutputFile.write(reinterpret_cast<char *>(&Hash), sizeof(Hash));
            ++m_uCurrIndex;
        }
    }
}