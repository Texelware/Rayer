#include <fstream>
#include <Rayer/Filesystem/FileSystem.h>


namespace Rayer {

    std::string RayerFileSystem::ReadFileToString(const std::string& path) {

        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << path << std::endl;
            return "";
        }

        std::string content((std::istreambuf_iterator<char>(file)),
            (std::istreambuf_iterator<char>()));

        return content;
    }

}