/***********************************************
  The MIT License (MIT)

  Copyright (c) 2022 zi wang <zzziwang@outlook.com>

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
 *************************************************/
#pragma once
#include "ff/sql/table_create.h"
#include <cppconn/sqlstring.h>

// for char
namespace ff {
namespace mysql {
template <uint8_t Len> struct char_m : public std::string {
public:
  char_m() : std::string(){};
  char_m(const char *s) : std::string(s){};
  char_m(const ::sql::SQLString &s) : std::string(s.c_str()) {}
  char_m(const char_m<Len> &s) : std::string(s.c_str()) {}
};

} // namespace mysql
namespace sql {
namespace internal {
template <class T> struct dump_col_type_creation;
template <uint8_t Len> struct dump_col_type_creation<::ff::mysql::char_m<Len>> {
  static void dump(std::stringstream &ss) { ss << " CHAR(" << Len << ") "; }
};
} // namespace internal
template <class STMT, class T> struct mysql_bind_setter;

template <class STMT, uint8_t Len>
struct mysql_bind_setter<STMT, ::ff::mysql::char_m<Len>> {
  static void bind(STMT stmt, int index,
                   const ::ff::mysql::char_m<Len> &value) {
    stmt->setString(index, value);
  }
};

template <class T> struct mysql_rs_getter;
template <uint8_t Len> struct mysql_rs_getter<::ff::mysql::char_m<Len>> {
  template <typename RST>
  static ::ff::mysql::char_m<Len> get(RST r, const std::string &name) {
    return ::ff::mysql::char_m<Len>(r->getString(name));
  }
};

} // namespace sql
} // namespace ff

// for varchar
namespace ff {
namespace mysql {
template <uint16_t Len> struct varchar_m : public std::string {
public:
  varchar_m() : std::string(){};
  varchar_m(const char *s) : std::string(s){};
  varchar_m(const ::sql::SQLString &s)
      : std::string(s.c_str()) {} // c_str: return char*
  varchar_m(const varchar_m<Len> &s) : std::string(s.c_str()) {}
};

} // namespace mysql
namespace sql {
namespace internal {
template <class T> struct dump_col_type_creation;
template <uint16_t Len>
struct dump_col_type_creation<::ff::mysql::varchar_m<Len>> {
  static void dump(std::stringstream &ss) { ss << " VARCHAR(" << Len << ") "; }
};
} // namespace internal
template <class STMT, class T> struct mysql_bind_setter;

template <class STMT, uint16_t Len>
struct mysql_bind_setter<STMT, ::ff::mysql::varchar_m<Len>> {
  static void bind(STMT stmt, int index,
                   const ::ff::mysql::varchar_m<Len> &value) {
    stmt->setString(index, value);
  }
};

template <class T> struct mysql_rs_getter;
template <uint16_t Len> struct mysql_rs_getter<::ff::mysql::varchar_m<Len>> {
  template <typename RST>
  static ::ff::mysql::varchar_m<Len> get(RST r, const std::string &name) {
    return ::ff::mysql::varchar_m<Len>(r->getString(name));
  }
};

} // namespace sql
} // namespace ff
