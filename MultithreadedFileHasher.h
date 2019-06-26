#pragma once

#include "SafeFileReader.h"
#include "FileWriter.h"
#include "ThreadedHasher.h"

class MultithreadedFileHasher
{
    enum
    {
        en_max_memory_mb = 1 * 1024
    };


public:
    MultithreadedFileHasher (const std::shared_ptr<SafeFileReader>& pFileReader,
                             const std::shared_ptr<FileWriter>& pFileWriter,
                             unsigned uBlockSizeMb);

    void waitForAll();

private:
    std::shared_ptr<FileWriter> m_pFileWriter;

    std::vector< std::shared_ptr<ThreadedHasher> > m_vHashers;
};
