
#include "ThreadedHasher.h"

#include <functional>

ThreadedHasher::ThreadedHasher(std::shared_ptr<SafeFileReader> pFileReader, std::shared_ptr<FileWriter> pFileWriter)
    : m_pFileReader(pFileReader),
      m_pFileWriter(pFileWriter)
{
    m_pThread.reset(new std::thread(std::bind(&ThreadedHasher::thread_proc, this)));
}

void ThreadedHasher::thread_proc()
{
    while(true)
    {
        auto pairParams = m_pFileReader->readNext();
        if(pairParams.first.empty())
            break;

        auto uHash = m_hashFunc( std::string(pairParams.first.begin(), pairParams.first.end()) );

        m_pFileWriter->addHash(pairParams.second, uHash);
    }
}

void ThreadedHasher::join()
{
    if(m_pThread)
        m_pThread->join();
}