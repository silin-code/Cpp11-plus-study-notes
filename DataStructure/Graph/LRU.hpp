#pragma once
#include<list>
#include<vector>
#include<unordered_map>
using namespace std;

class LRUCache {
    using LtIter = list<pair<int, int>>::iterator;

public:
    LRUCache(int capacity) { _capacity = capacity; }

    int get(int key) {
        auto ret = _hashMap.find(key);
        if (ret != _hashMap.end()) {
            // 更新key对应值的位置
            LtIter it = ret->second;
            // 方案一:erase+push_front
            // 方案二:转移节点(list标准库函数)
            _LRUList.splice(_LRUList.begin(), _LRUList, it);

            return ret->second->second;
        }
        return -1;
    }

    void put(int key, int value) {
        // 1:新增
        // 2:更新
        auto It = _hashMap.find(key);
        if (It == _hashMap.end()) {
            // 满了先删除LRU数据
            if (_capacity == _hashMap.size()) {
                pair<int, int>& back = _LRUList.back();
                _hashMap.erase(back.first);
                _LRUList.pop_back();
            }

            _LRUList.push_front({ key,value });
            _hashMap[key] = _LRUList.begin();
        }
        else
        {
            auto it = It->second;
            it->second = value;
            _LRUList.splice(_LRUList.begin(), _LRUList, it);

        }
    }

private:
    unordered_map<int, LtIter> _hashMap;
    // LRU
    list<pair<int, int>> _LRUList;
    int _capacity;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */