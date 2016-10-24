#pragma once

inline std::string readFile(const std::string& filename) {
    std::ifstream file;
    file.open(filename);

    std::stringstream stream;
    stream << file.rdbuf();
    return stream.str();
}

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