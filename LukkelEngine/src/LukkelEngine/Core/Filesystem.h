#ifndef _FILESYSTEM_H
#define _FILESYSTEM_H

/* TODO: Precompiled Header */
#include <filesystem>
#include <fstream>
#include <LukkelEngine/Core/Buffer.h>

namespace LukkelEngine {

	class FileSystem
	{
	public:
		static Buffer ReadFileBinary(const std::filesystem::path& filepath);
	};

}

#endif /* _FILESYSTEM_H */