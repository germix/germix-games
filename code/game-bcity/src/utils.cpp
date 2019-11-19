#include <src/utils.h>

#include <windows.h>

static std::vector<String> getMapsFromFolder(const String& dir)
{
	std::vector<String> list;
	HANDLE hFind;
	WIN32_FIND_DATA wfd;
	char sz[MAX_PATH];
	char fname[MAX_PATH];
	
	sprintf(sz, "%s/*.tmx", dir.c_str());
	if(INVALID_HANDLE_VALUE != (hFind = FindFirstFile(sz, &wfd)))
	{
		do
		{
			char* ptr = strchr(wfd.cFileName, '.');
			int   len = ptr-wfd.cFileName;
			
			strncpy(fname, wfd.cFileName, len);
			fname[len] = '\0';
			
			list.push_back(fname);
		}
		while(FindNextFile(hFind, &wfd));
		FindClose(hFind);
	}
	return list;
}
std::vector<String> getMapsFromCustomMapsFolder()
{
	return getMapsFromFolder("bcity/custommaps");
}
std::vector<String> getMapsFromDefaultMapsFolder()
{
	return getMapsFromFolder("bcity/maps");
}
