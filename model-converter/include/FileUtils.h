#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


inline std::string getFilename(const std::string& path)
{
    std::string temp = path;

    size_t s = temp.find_last_of("/");
    if (s != std::string::npos)
        temp = temp.substr(s+1, temp.size()-s-1);

    return temp;
}


inline std::string getFolder(const std::string& path)
{
    std::string temp = path;

    size_t s = temp.find_last_of("/");
    if (s != std::string::npos)
        temp = temp.substr(0, s);

    return temp;
}


inline void writeString(std::ofstream& file, const std::string& string)
{
    unsigned int num = string.size();
    file.write((char*)&num, sizeof(num));
    file.write(string.c_str(), num);
}


inline int createDirectory(const std::string& path)
{
    return mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}


inline bool doesFileExist(const std::string& path)
{
    return access(path.c_str(), F_OK) != -1;
}


inline void copyFile(const std::string& source,
    const std::string& destination)
{
    std::ifstream src(source, std::ios::binary);
    std::ofstream dest(destination, std::ios::binary);
    dest << src.rdbuf();
}
