#pragma once
#include "ff/sql/columns.h"
#include "ff/sql/engine.h"
#include "ff/sql/mysql.hpp"
#include "ff/sql/mysql/blob.h"
#include "ff/util/ntobject.h"
#include <string>

namespace ff {
namespace sql {
namespace internal {
template <bool, typename T> struct check_key_index_type {};
template <typename T> struct check_key_index_type<true, T> {
  typedef typename util::nt_traits<T>::type data_type;
  static_assert(
      !std::is_same<data_type, std::string>::value,
      "TEXT column used in key/index specification without a key length");

  static_assert(
      !(::ff::mysql::is_blob<data_type>::value),
      "BLOB column used in key/index specification without a key length");
};

} // namespace internal
template <typename TM, typename T>
struct check_key_index<mysql<cppconn>, TM, T>
    : public internal::check_key_index_type<
          is_key<T>::value || is_index<T>::value, T> {};

template <typename TM, typename T, typename... ARGS>
struct check_key_index<mysql<cppconn>, TM, T, ARGS...>
    : public internal::check_key_index_type<
          is_key<T>::value || is_index<T>::value, T>,
      check_key_index<mysql<cppconn>, TM, ARGS...> {};
} // namespace sql
} // namespace ff
