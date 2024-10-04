#include "WindowsUtils.h"

namespace Rayer {

	std::filesystem::path WindowsUtils::OpenFileDialog(const std::string filter) {

		OPENFILENAME ofn;
        WCHAR szFile[MAX_PATH] = { 0 };

        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);

        // Convert extension string to wide string
        std::wstring wExtension = std::wstring(filter.begin(), filter.end());
        wExtension += L'\0'; // Add null terminator
        wExtension += L'*';  // Add wildcard character for all files
        wExtension += L'\0'; // Add second null terminator

        // Set filter specification
        ofn.lpstrFilter = wExtension.c_str();

        ofn.nFilterIndex = 1;
        ofn.lpstrTitle = L"Open File";
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        if (GetOpenFileName(&ofn) == TRUE) {
            std::wstring wFilePath(szFile);
            return std::filesystem::path(wFilePath);
        }
        else {
            // Handle error or cancellation
            std::cout << "No file selected." << std::endl;
            return std::filesystem::path(""); // Return an empty path to indicate no file selected
        }

	}

    std::filesystem::path WindowsUtils::SaveFile(const char* filter, const char* extension)
    {
        OPENFILENAMEA ofn;
        CHAR szFile[260] = { 0 };  // Buffer to store the file name
        CHAR currentDir[256] = { 0 };  // Buffer to store the current directory

        ZeroMemory(&ofn, sizeof(OPENFILENAMEA));  // Clear the structure

        ofn.lStructSize = sizeof(OPENFILENAMEA);  // Set structure size
        ofn.hwndOwner = NULL;  // No owner window required

        ofn.lpstrFile = szFile;  // Pointer to the file buffer
        ofn.nMaxFile = sizeof(szFile);  // Max file buffer size

        if (GetCurrentDirectoryA(256, currentDir))  // Get current directory
            ofn.lpstrInitialDir = currentDir;  // Set it as the initial directory

        // Use the provided filter (e.g., "Rayer Files\0*.rayer\0All Files\0*.*\0")
        ofn.lpstrFilter = filter;
        ofn.nFilterIndex = 1;  // Default filter index
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;

        // Set the provided extension (e.g., "rayer", without the dot)
        ofn.lpstrDefExt = extension;

        // Show the Save As dialog
        if (GetSaveFileNameA(&ofn) == TRUE) {
            std::string filePath = ofn.lpstrFile;

            // Ensure the file ends with the provided extension
            std::string extWithDot = std::string(".") + extension;
            if (filePath.find(extWithDot) == std::string::npos) {
                filePath += extWithDot;  // Append the extension if it's missing
            }

            // Return the file path with the extension
            return std::filesystem::path(filePath);
        }

        // If canceled or failed, return an empty path
        return std::filesystem::path();
    }



}