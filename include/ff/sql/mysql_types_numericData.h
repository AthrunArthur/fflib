//bit
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
#include <assert.h>


#define medIntMax 1677215 //3byte for mediumInt 


//for decimal
namespace ff {
namespace mysql {
template <uint64_t Len> struct decimal_m{
public:
  decimal_m() : m_data(){};
  decimal_m(const char *s) : m_data(s){};
  decimal_m(const ::sql::SQLString &s) : m_data(s.c_str()) {}
  decimal_m(const decimal_m<Len> &s) : m_data(s.data()) {}
  decimal_m(decimal_m<Len> &&s) : m_data(std::move(s.m_data)) {}
  decimal_m<Len> &operator=(const decimal_m<Len> &s) {
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

namespace internal {
template <typename T> struct checkLength;
template <uint64_t Len> struct checkLength<decimal_m<Len>> {
  static void checklength(){
  assert(Len < medIntMax);
  } 
};

template <typename T> struct dump_col_type_creation;
template <uint64_t Len> struct dump_col_type_creation<decimal_m<Len>> {
  static void dump(std::stringstream &ss) { 
    ss << " Decimal(" << Len << ") "; }
};
} // namespace internal
} // namespace mysql
namespace sql {
template <class STMT, class T> struct mysql_bind_setter;

template <class STMT, uint64_t Len>
struct mysql_bind_setter<STMT, ::ff::mysql::decimal_m<Len>> {
  static void bind(STMT stmt, int index,
                   const ::ff::mysql::decimal_m<Len> &value) {
    stmt->setString(index, value.data());
  }
};

template <class T> struct mysql_rs_getter;
template <uint64_t Len> struct mysql_rs_getter<::ff::mysql::decimal_m<Len>> {
  template <typename RST>
  static ::ff::mysql::decimal_m<Len> get(RST r, const std::string &name) {
    return ::ff::mysql::decimal_m<Len>(r->getString(name));
  }
};

} // namespace sql
} // namespace ff




//for mediumInt
namespace ff {
namespace mysql {
template <uint64_t Len> struct medInt_m{
public:
  medInt_m() : m_data(){};
  medInt_m(const char *s) : m_data(s){};
  medInt_m(const ::sql::SQLString &s) : m_data(s.c_str()) {}
  medInt_m(const medInt_m<Len> &s) : m_data(s.data()) {}
  medInt_m(medInt_m<Len> &&s) : m_data(std::move(s.m_data)) {}
  medInt_m<Len> &operator=(const medInt_m<Len> &s) {
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

namespace internal {


// assert Len match the length of mediumInt
template <typename T> struct checkLength;
template <uint64_t Len> struct checkLength<medInt_m<Len>> {
  static void checklength(){
  assert(Len < medIntMax);
  } 
};

template <typename T> struct dump_col_type_creation;
template <uint64_t Len> struct dump_col_type_creation<medInt_m<Len>> {
  static void dump(std::stringstream &ss) { 
    ss << " MediumInt(" << Len << ") "; }
};
} // namespace internal
} // namespace mysql
namespace sql {
template <class STMT, class T> struct mysql_bind_setter;

template <class STMT, uint64_t Len>
struct mysql_bind_setter<STMT, ::ff::mysql::medInt_m<Len>> {
  static void bind(STMT stmt, int index,
                   const ::ff::mysql::medInt_m<Len> &value) {
    stmt->setInt64(index, value.data());
  }
};

template <class T> struct mysql_rs_getter;
template <uint64_t Len> struct mysql_rs_getter<::ff::mysql::medInt_m<Len>> {
  template <typename RST>
  static ::ff::mysql::medInt_m<Len> get(RST r, const std::string &name) {
    return ::ff::mysql::medInt_m<Len>(r->getInt64(name));
  }
};

} // namespace sql
} // namespace ff