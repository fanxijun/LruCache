#include "LruCache.h"
#include <sstream>
#include <iostream>

using namespace lrucache;

const int TEST_ITEM_COUNT = 20;
const int TEST_CACHE_CAPACITY = 10;

void TestLruCacheCapacity()
{
    LruCache<int, std::string> lru_cache(TEST_CACHE_CAPACITY);

    //插入20个元素
    for(int i = 0; i < TEST_ITEM_COUNT; i++)
    {
        std::stringstream ssValue;
        ssValue << "value" << i;

        lru_cache.Put(i, ssValue.str());
    }

    //查询打印所有元素
    for(int i = 0; i < TEST_ITEM_COUNT; i++)
    {
        std::string value;
        try
        {
            value = lru_cache.Get(i);
        }
        catch(const std::exception& e)
        {
            std::cerr << "exception: " << e.what() << '\n';
        }
        
        std::cout << "get key:" << i << ", value:" << value << '\n';
    }
}

void TestLruCachePut()
{
    LruCache<int, std::string> lru_cache(1);

    lru_cache.Put(100, "value100");
    lru_cache.Put(100, "value100");

    std::string value = lru_cache.Get(100);
    std::cout << "get key:100, value:" << value << '\n';
}

void TestLruCacheRemove()
{
    LruCache<int, std::string> lru_cache(2);

    lru_cache.Put(200, "value200");

    std::string value = lru_cache.Get(200);
    std::cout << "get key:200, value:" << value << '\n';

    bool ret = lru_cache.Remove(200);
    value = lru_cache.Get(200);
    std::cout << "get key:200, value:" << value << '\n';
}



int main(int argc, char** argv) 
{
    TestLruCacheCapacity();
    TestLruCachePut();
    TestLruCacheRemove();

	return 0;
}
