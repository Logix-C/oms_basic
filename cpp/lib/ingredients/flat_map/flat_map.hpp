#pragma once

#include <algorithm>
#include <map>
#include <utility>
#include <vector>

template <typename Key, typename Value, typename Compare = std::less<Key>>
struct flat_map {
    using value_type = std::pair<const Key, Value>;
    using container_type = std::vector<value_type>;
    using iterator = container_type::iterator;
    using const_iterator = container_type::const_iterator;

    explicit flat_map(Compare comp = Compare{}) : comp_(comp) {}

    Value& operator[](const Key& key) {
        auto it = lower_bound(key);
        if (it != data_.end() && !comp_(key, it->first) && !comp_(it->first, key)) {
            return it->second;
        }
        return data_.insert(it, {key, Value{}})->second;
    }

    iterator find(const Key& key) {
        auto it = lower_bound(key);
        if (it != data_.end() && !comp_(key, it->first) && !comp_(it->first, key)) {
            return it;
        }
        return data_.end();
    }

    const_iterator find(const Key& key) const {
        auto it = lower_bound(key);
        if (it != data_.end() && !comp_(key, it->first) && !comp_(it->first, key)) {
            return it;
        }
        return data_.end();
    }

    void insert(const value_type& kv) {
        auto it = lower_bound(kv.first);
        if (it == data_.end() || comp_(kv.first, it->first)) {
            data_.insert(it, kv);
        } else {
            it->second = kv.second;
        }
    }

    iterator begin() { return data_.begin(); }
    iterator end() { return data_.end(); }
    const_iterator begin() const { return data_.begin(); }
    const_iterator end() const { return data_.end(); }

private:
    container_type data_;
    Compare comp_;

    iterator lower_bound(const Key& key) {
        return std::lower_bound(data_.begin(), data_.end(), key,
            [this](const value_type& kv, const Key& k) {
                return comp_(kv.first, k);
            });
    }

    const_iterator lower_bound(const Key& key) const {
        return std::lower_bound(data_.begin(), data_.end(), key,
            [this](const value_type& kv, const Key& k) {
                return comp_(kv.first, k);
            });
    }
};