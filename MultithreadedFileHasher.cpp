#include "MultithreadedFileHasher.h"

unsigned get_threads_count_by_block_size(unsigned uMaxMemorySizeMb, unsigned uBlockSizeMb)
{
    return uMaxMemorySizeMb / uBlockSizeMb;
}

MultithreadedFileHasher::MultithreadedFileHasher (const std::shared_ptr<SafeFileReader>& pFileReader,
                         const std::shared_ptr<FileWriter>& pFileWriter,
                         unsigned uBlockSizeMb)
                         : m_pFileWriter(pFileWriter)
{
    unsigned uThreadCnt = get_threads_count_by_block_size(en_max_memory_mb, uBlockSizeMb);

    for(auto i = 0; i != uThreadCnt; ++i)
        m_vHashers.push_back(std::make_shared<ThreadedHasher>(pFileReader, pFileWriter));
}

void MultithreadedFileHasher::waitForAll()
{
    std::for_each(m_vHashers.begin(), m_vHashers.end(), std::bind(&ThreadedHasher::join, std::placeholders::_1));
    m_pFileWriter->waitForFlushAllData();
}