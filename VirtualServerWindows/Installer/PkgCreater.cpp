#include "PkgCreater.h"
//#include "chilkat-9.5.0-x86-vc12\include\CkZip.h"
#include <queue>
#include <fstream>
#include "XmlHelper.h"

PkgCreater::PkgCreater(std::string from, std::string to, std::string pkgName) : _from(from), _to(to), _pkgName(pkgName)
{
	if (!FileSystem::Directory::exists(_to))
		FileSystem::Directory::create(_to);
}

PkgCreater::~PkgCreater(){}

// create pkg according to a list of modules
bool PkgCreater::createPkg(std::vector<m_data> meta)
{
	//create a new dir for the pkg
	//std::string path = _to + "\\Download";
	std::string path = _to + FILE_SEPARATOR + _pkgName;

	FileSystem::Directory::create(path);

	//traverse the meta list to make the new pkg
	for (int i = 0; i < (int)meta.size(); i++)
	{
		// update cnt
		updateCnt(meta[i]);

		// update map
		updateMap(_from + FILE_SEPARATOR + meta[i].name + FILE_SEPARATOR + "Module.xml");

		// create module dir
		FileSystem::Directory::create(path + FILE_SEPARATOR + meta[i].name);

		// get subdirs and files
		std::vector<std::string> subdir = FileSystem::Directory::getDirectories(_from + FILE_SEPARATOR + meta[i].name);
		std::vector<std::string> files = FileSystem::Directory::getFiles(_from + FILE_SEPARATOR + meta[i].name);

		// copy subdirs
		for (int j = 0; j < (int)subdir.size(); j++)
		{
			if (subdir[j] == "." || subdir[j] == "..")
				continue;

			std::string str = FILE_SEPARATOR + meta[i].name + FILE_SEPARATOR + subdir[j];
			FileSystem::FileMng::copyDir(_from + str, path + str);
		}
		
		// copy files
		for (int j = 0; j < (int)files.size(); j++)
		{	
			if (!IsLib(files[j]))
			{
				std::string str = FILE_SEPARATOR + meta[i].name + FILE_SEPARATOR + files[j];
				FileSystem::FileMng::copyFile(_from + str, path + str);
			}
			else
			{
				for (auto p : meta[i].pfs)
				{ 
					if (files[j] == _typemap[p])
					{
						std::string str = FILE_SEPARATOR + meta[i].name + FILE_SEPARATOR + _typemap[p];
						FileSystem::FileMng::copyFile(_from + str, path + str);
					}				
				}
			}				
		}
	}

	// copy excecutables
	if (_cnt.find("Windows") != _cnt.end())
		FileSystem::FileMng::copyFile(_from + FILE_SEPARATOR + "run.bat", path + FILE_SEPARATOR + "run.bat");
	if (_cnt.find("Linux x86") != _cnt.end() || _cnt.find("Linux x64") != _cnt.end())
		FileSystem::FileMng::copyFile(_from + FILE_SEPARATOR + "run.sh", path + FILE_SEPARATOR + "run.sh");

	return true;
}

// check if a file is a lib file
bool PkgCreater::IsLib(std::string str)
{
	for (auto t : _typemap)
	{
		if (str == t.second)
			return true;
	}

	return false;
}


// update _typemap
void PkgCreater::updateMap(std::string path)
{
	// update new content
	std::ifstream ifs(path);
	std::string content;

	if (ifs.good())
	{
		content.assign((std::istreambuf_iterator<char>(ifs)),
			std::istreambuf_iterator<char>());
	}

	XmlHelper::updateMap(content, _typemap);
}

// zip a dir tree and return the path of the zip file
std::string PkgCreater::pkgZipper()
{
	CkZip zip;

	bool success;

	//std::string path = _to + "\\Download.zip";
	std::string path = _to + FILE_SEPARATOR + _pkgName + ".zip";

	if (FileSystem::File::exists(path))
		FileSystem::File::remove(path);

	success = zip.NewZip(path.c_str());

	if (success != true) {
		printf("%s\n", zip.lastErrorText());
		return "";
	}

	//  Any string unlocks the component for the 1st 30-days.
	success = zip.UnlockComponent("Anything for 30-day trial");
	if (success != true) {
		printf("%s\n", zip.lastErrorText());
		return "";
	}

	// append a dir tree to the zip file recursively

	bool recurse = true;
	success = zip.AppendFiles((_to + FILE_SEPARATOR + _pkgName/*"\\Download"*/).c_str(), recurse);
	if (success != true) {
		printf("%s\n", zip.lastErrorText());
		return "";
	}

	success = zip.WriteZipAndClose();
	if (success != true) {
		printf("%s\n", zip.lastErrorText());
		return "";
	}

	//printf("Zip Created!\n");

	// delete download folder
	FileSystem::FileMng::deleteDir(_to + FILE_SEPARATOR + _pkgName);

	return path;
}

// update _cnt
void PkgCreater::updateCnt(m_data m)
{
	for (int i = 0; i < m.pfs.size(); i++)
	{
		if (_cnt.find(m.pfs[i]) == _cnt.end())
			_cnt[m.pfs[i]] = 1;
	}
}