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

    void RayerFileSystem::CopyFileToDirectory(const fs::path& source, const fs::path& destination) {

        if (!std::filesystem::exists(source)) {
            std::cerr << "Source file does not exist: " << source << std::endl;
            return;
        }

        if (!std::filesystem::is_directory(destination)) {
            std::cerr << "Destination is not a directory: " << destination << std::endl;
            return;
        }

        fs::path _final = destination / source.filename();

        fs::copy(source, _final, fs::copy_options::overwrite_existing);

    }

    fs::path RayerFileSystem::_currentWorkingPath = fs::current_path();

}