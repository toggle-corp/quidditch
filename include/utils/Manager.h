#pragma once

template<class T>
class Manager {
public:
    // Add new item
    template<class... Args>
    std::shared_ptr<T> add(const std::string& key, Args... args)
    {
        mItems[key] = std::shared_ptr<T>(new T(args...));
        return mItems[key];
    }

    // Add new item for a derived class
    template<class T1, class... Args>
    std::shared_ptr<T1> add(const std::string& key, Args... args)
    {
        mItems[key] = std::shared_ptr<T>(new T1(args...));
        return std::static_pointer_cast<T1>(mItems[key]);
    }

    // Remove item for a key
    void remove(const std::string& key) {
        auto iterator = mItems.find(key);
        if (iterator != mItems.end())
            mItems.erase(iterator);
    }

    // Check if key exists
    bool has(const std::string& key) {
        return mItems.find(key) != mItems.end();
    }

    // Get item for a key
    std::shared_ptr<T> get(const std::string& key) {
        return mItems[key];
    }

    // A shared global/static manager
    static Manager<T>& get() {
        static Manager<T> manager;
        return manager;
    }

private:
    std::map<std::string, std::shared_ptr<T>> mItems;
};