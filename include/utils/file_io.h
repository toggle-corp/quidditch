#pragma once

// Read complete file to a string
inline std::string readFile(const std::string& filename) {
    std::ifstream file;
    file.open(filename);

    std::stringstream stream;
    stream << file.rdbuf();
    return stream.str();
}

// Read first the number of characters, then the actual string from a file
inline std::string readString(std::ifstream& file)
{
    unsigned int sz;
    file.read((char*)&sz, sizeof(sz));
    std::string s(sz+1, 0);
    file.read(&s[0], sz);
    return s;
}

// Get only the filename from a path
inline std::string getFilename(const std::string& path)
{
    std::string temp = path;

    size_t s = temp.find_last_of("/");
    if (s != std::string::npos)
        temp = temp.substr(s+1, temp.size()-s-1);

    return temp;
}

// Get parent folder containing file representing the path
inline std::string getFolder(const std::string& path)
{
    std::string temp = path;

    size_t s = temp.find_last_of("/");
    if (s != std::string::npos)
        temp = temp.substr(0, s);

    return temp;
}

// Check if file exists at a path
inline bool fileExists(const std::string& path) {
    return access(path.c_str(), F_OK) != -1;
}