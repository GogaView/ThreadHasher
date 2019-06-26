#include <iostream>

#include "ArgumentParser.h"
#include "HasherException.h"
#include "SafeFileReader.h"
#include "FileWriter.h"
#include "MultithreadedFileHasher.h"


int main(int argc, char** argv)
{
    try
    {
        ArgumentParser ArgParams(argc, argv);

        auto pFileReader = std::make_shared<SafeFileReader>(ArgParams.getInputFileName(), ArgParams.getBlockSize());
        auto pFileWriter = std::make_shared<FileWriter>(ArgParams.getOutputFileName());

        MultithreadedFileHasher hasher(pFileReader, pFileWriter, ArgParams.getBlockSize());
        hasher.waitForAll();
    }
    catch(hasher_exception& err)
    {
        std::cout << err.what() << std::endl;
    }

    return 0;
}