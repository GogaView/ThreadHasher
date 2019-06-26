#pragma once

#include <thread>

#include "SafeFileReader.h"
#include "FileWriter.h"

class ThreadedHasher
{
public:
    explicit ThreadedHasher(std::shared_ptr<SafeFileReader> pFileReader,
            std::shared_ptr<FileWriter> pFileWriter);

    void join();

private:
    void thread_proc();

private:
    std::shared_ptr<SafeFileReader> m_pFileReader;
    std::shared_ptr<FileWriter> m_pFileWriter;

    std::unique_ptr<std::thread> m_pThread;
    std::hash<std::string> m_hashFunc;
};
