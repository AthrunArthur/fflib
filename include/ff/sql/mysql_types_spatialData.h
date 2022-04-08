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
#include <iostream>
#include <fstream>


/* Geometry is an abstract class. However, in the prepared statement, we did not find its set method (in file:mysql_prepared_statement). 
At the same time, there are no judgement of responding class in getResult (mysql_ps_resultset.cpp). 
Also, we did not find the responding class in mysql include file.

Thus, we only define this type as usual string type here. Then, it may should be change base on relative classes.
*/

//for json_m
namespace ff {
namespace mysql {
struct json_m {
public:
  inline json_m() : m_data(){};
  inline json_m(const char *s) : m_data(s){};
  inline json_m(const ::sql::SQLString &s) : m_data(s.c_str()) {}
  inline json_m(const json_m &s) : m_data(s.data()) {}
  json_m(json_m &&s) : m_data(std::move(s.m_data)) {}
  json_m  &operator=(const json_m &s) {
    if (&s == this) {
      return *this;
    }
    m_data = s.m_data;
    return *this;
  };

  const std::string &data() const { return m_data; }
  std::string &data() { return m_data; }

protected:
  std::string m_data;
};

// namespace internal {
// template <class T> struct dump_col_type_creation;
// template <uint16_t Len> struct dump_col_type_creation<json_m> {
//   static void dump(std::stringstream &ss) { ss << "JSON(" << Len << ") "; }
// };
// } // namespace internal
} // namespace mysql
namespace sql {
template <class STMT, class T> struct mysql_bind_setter;

template <class STMT>
struct mysql_bind_setter<STMT, ::ff::mysql::json_m > {
  static void bind(STMT stmt, int index,
                   const ::ff::mysql::json_m  &value) {
    stmt->setString(index, value.data());
  }
};

template <class T> struct mysql_rs_getter;
template <> struct mysql_rs_getter<::ff::mysql::json_m>{
  template <typename RST>
  static ::ff::mysql::json_m get(RST r, const std::string &name) {
    return ::ff::mysql::json_m (r->getString(name));
  }
};

} // namespace sql
} // namespace ff



// namespace ff {
// namespace mysql {
// template <uint8_t Len> struct bin_m{
// public:
//   bin_m() : m_data(){};
//   bin_m(const char *s) : m_data(s){};
//   bin_m(const ::sql::SQLString &s) : m_data(s.c_str()) {}
//   bin_m(const bin_m<Len> &s) : m_data(s.data()) {}
//   bin_m(bin_m<Len> &&s) : m_data(std::move(s.m_data)) {}
//   bin_m<Len> &operator=(const bin_m<Len> &s) {
//     if (&s == this) {
//       return *this;
//     }
//     m_data = s.m_data;
//     return *this;
//   };

//   const std::string &data() const { return m_data; }
//   std::string &data() { return m_data; }

// protected:
//   std::string m_data;
// };

// namespace internal {
// template <class T> struct dump_col_type_creation;
// template <uint8_t Len> struct dump_col_type_creation<bin_m<Len>> {
//   static void dump(std::stringstream &ss) { ss << " CHAR(" << Len << ") "; }
// };
// } // namespace internal
// } // namespace mysql
// namespace sql {
// template <class STMT, class T> struct mysql_bind_setter;

// template <class STMT, uint8_t Len>
// struct mysql_bind_setter<STMT, ::ff::mysql::bin_m<Len>> {
//   static void bind(STMT stmt, int index,
//                    const ::ff::mysql::bin_m<Len> &value) {
//     stmt->setString(index, value.data());
//   }
// };

// template <class T> struct mysql_rs_getter;
// template <uint8_t Len> struct mysql_rs_getter<::ff::mysql::bin_m<Len>> {
//   template <typename RST>
//   static ::ff::mysql::bin_m<Len> get(RST r, const std::string &name) {
//     return ::ff::mysql::bin_m<Len>(r->getString(name));
//   }
// };

// } // namespace sql
// } // namespace ff