#ifndef _LRU_CACHE_H_
#define _LRU_CACHE_H_

#include <list>
#include <unordered_map>
#include <stdexcept>
#include <mutex>

namespace lrucache
{

template<typename K, typename V>
class LruCache
{
    typedef typename std::pair<K, V> KVPair;
    typedef typename std::list<KVPair>::iterator KVPairListIter;

public:
    explicit LruCache(size_t max_size): max_size_(max_size) {}

    const V& Get(const K& key) 
    {
        std::lock_guard<std::mutex> lock(mutex_);

        auto iter = item_map_.find(key);
        if(iter == item_map_.end())
        {
            throw std::invalid_argument("Key not found in cache");
        }

        item_list_.splice(item_list_.begin(), item_list_, iter->second);
        return iter->second->second;
    }

    void Put(const K& key, const V& value)
    {
        std::lock_guard<std::mutex> lock(mutex_);

        auto iter = item_map_.find(key);
        if(iter != item_map_.end())
        {
            item_list_.erase(iter->second);
            item_map_.erase(iter);
        }

        item_list_.push_front(KVPair(key, value));
        item_map_[key] = item_list_.begin();

        if(item_map_.size() > max_size_) 
        {
            auto last = item_list_.end();
            last--;
            item_map_.erase(last->first);
            item_list_.pop_back();
        }
    }

    bool Remove(const K& key)
    {
        std::lock_guard<std::mutex> lock(mutex_);

        auto iter = item_map_.find(key);
        if(iter == item_map_.end()) 
        {
            return false;
        }

        item_map_.erase(iter->first);
        item_list_.erase(iter->second);
        return true;
    }

private:
    std::list<KVPair> item_list_;
    std::unordered_map<K, KVPairListIter> item_map_;
    size_t max_size_;
    std::mutex mutex_;
};

};

#endif
