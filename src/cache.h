#pragma once

#include <cassert>
#include <utility>

namespace sren {

template <class T>
class Cache {
 public:
  Cache() = default;
  Cache(T data) : data_(std::move(data)) {}

  void mark_dirty() { dirty_ = true; }

  bool is_dirty() const { return dirty_; }

  T const &data() const {
    assert(!dirty_);
    return data_;
  }

  void set_data(T data) {
    data_ = std::move(data);
    dirty_ = false;
  }

 private:
  bool dirty_{true};
  T data_{};
};

}  // namespace sren
