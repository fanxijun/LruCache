all: lru_cache_test

lru_cache_test: 
	$(CXX) -std=c++11 LruCacheTest.cpp -o lru_cache_test

clean:
	rm lru_cache_test
