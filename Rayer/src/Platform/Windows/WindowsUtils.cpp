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

}