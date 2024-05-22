#pragma once
#include "Event.h"

namespace Rayer {

	class FileDroppedEvent : public Event {

	public:

		FileDroppedEvent(int _fileCount, const char** _paths) : fileCount(_fileCount), paths(_paths) {}

		int GetFileCount() const { return fileCount; }
		const char** GetPaths() const { return paths; }

		virtual std::string ToString() const override {

			std::stringstream ss;
			ss << "FileDroppedEvent : " << "FileCount: " << fileCount << std::endl;

			for (int i = 0; i < fileCount; ++i) {

				ss << "Path: " << paths[i] << std::endl;

			}

			return ss.str();
		}

		EVENT_CLASS_TYPE(FileDropped)
			EVENT_CLASS_CATEGORY(EventCategoryDragDrop | EventCategoryInput)

	private:

		int fileCount;
		const char** paths;

	};

}