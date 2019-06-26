#include "SafeFileReader.h"

#include "HasherException.h"

SafeFileReader::SafeFileReader(const boost::filesystem::path& phinputFile, unsigned uBlockSize)
    : m_uBlockSizeByte(uBlockSize * 1024 * 1024),
      m_bIsDataExist(true),
      m_uIndex(0)
{
    try
    {
        if(!boost::filesystem::exists(phinputFile))
            throw hasher_exception("Can't find input file");
    }
    catch(boost::filesystem::filesystem_error&)
    {
        throw hasher_exception("Can't proc input file");
    }

    m_ifIntutFile.open(phinputFile.string(), std::ios::in | std::ios::binary);
    if(!m_ifIntutFile.is_open())
        throw hasher_exception("Can't open input file");
}

std::pair<std::vector<char>, unsigned> SafeFileReader::readNext()
{
    std::lock_guard<std::mutex> Locker(m_Mutex);
    if(m_bIsDataExist)
        return std::make_pair(readDataBlock(), m_uIndex++);
    else
        return std::make_pair(std::vector<char>(), 0);
}

std::vector<char> SafeFileReader::readDataBlock()
{
    std::vector<char> vData(m_uBlockSizeByte, 0);
    if(!m_ifIntutFile.read(&vData[0], vData.size()))
        m_bIsDataExist = false;

    return vData;
}