#pragma once

#include <algorithm>
#include <map>
#include <utility>
#include <vector>

namespace oms::ingredients {
    template <typename Key, typename Value, typename Compare = std::less<Key>>
    struct flat_map {
        using value_type = std::pair<Key, Value>;
        using container_type = std::vector<value_type>;
        using iterator = container_type::iterator;
        using const_iterator = container_type::const_iterator;
        using reverse_iterator = container_type::reverse_iterator;
        using const_reverse_iterator = container_type::const_reverse_iterator;

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

        bool contains(const Key& key) const {
            auto it = lower_bound(key);

            if (it == data_.end()) {
                return false;
            }

            return it != data_.end() && !comp_(key, it->first) && !comp_(it->first, key);
        }

        bool erase(const Key& key) {
            auto it = lower_bound(key);
            if (it != data_.end() && !comp_(key, it->first) && !comp_(it->first, key)) {
                data_.erase(it);
                return true;
            }
            return false;
        }

        void reserve(size_t n) { data_.reserve(n); }

        void clear() {
            data_.clear();
        }

        template <typename... Args>
        void emplace(const Key& key, Args&&... args) {
            auto it = lower_bound(key);
            if (it == data_.end() || comp_(key, it->first)) {
                data_.emplace(it, key, Value(std::forward<Args>(args)...));
            } else {
                it->second = Value(std::forward<Args>(args)...);
            }
        }

        // Iterators
        iterator begin() { return data_.begin(); }
        iterator end() { return data_.end(); }
        const_iterator begin() const { return data_.begin(); }
        const_iterator end() const { return data_.end(); }
        reverse_iterator rbegin() { return data_.rbegin(); }
        reverse_iterator rend() { return data_.rend(); }
        const_iterator cbegin() const { return data_.begin(); }
        const_iterator cend() const { return data_.end(); }
        const_reverse_iterator crbegin() const { return data_.rbegin(); }
        const_reverse_iterator crend() const { return data_.rend(); }

        // Capacity
        [[nodiscard]] constexpr bool empty() const { return data_.empty(); }
        [[nodiscard]] constexpr size_t size() const { return data_.size(); }

    private:
        container_type data_;
        Compare comp_;

        iterator lower_bound(const Key& key) {
            return std::lower_bound(data_.begin(), data_.end(), key,
                [this](const value_type& kv, const Key& k) {
                    return comp_(kv.first, k);
                });
        }

        iterator upper_bound(const Key& key) {
            return std::upper_bound(data_.begin(), data_.end(), key,
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
}