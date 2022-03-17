/***********************************************
  The MIT License (MIT)

  Copyright (c) 2022 Athrun Arthur <athrunarthur@gmail.com>

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



// for Binary
namespace ff {
namespace mysql {
template <uint8_t Len> struct bin_m{
public:
  bin_m() : m_data(){};
  bin_m(const char *s) : m_data(s){};
  bin_m(const ::sql::SQLString &s) : m_data(s.c_str()) {}
  bin_m(const bin_m<Len> &s) : m_data(s.data()) {}
  bin_m(bin_m<Len> &&s) : m_data(std::move(s.m_data)) {}
  bin_m<Len> &operator=(const bin_m<Len> &s) {
    if (&s == this) {
      return *this;
    }
    m_data = s.m_data;
    return *this;
  };

  const std::string &data() const { return m_data; }//data的作用是什么？这两行函数的作用是什么？
  std::string &data() { return m_data; }

protected:
  std::string m_data;
};

namespace internal {
template <class T> struct dump_col_type_creation;
template <uint8_t Len> struct dump_col_type_creation<bin_m<Len>> {
  static void dump(std::stringstream &ss) { ss << " CHAR(" << Len << ") "; }
};
} // namespace internal
} // namespace mysql
namespace sql {
template <class STMT, class T> struct mysql_bind_setter;

template <class STMT, uint8_t Len>
struct mysql_bind_setter<STMT, ::ff::mysql::bin_m<Len>> {
  static void bind(STMT stmt, int index,
                   const ::ff::mysql::bin_m<Len> &value) {
    stmt->setString(index, value.data());
  }
};

template <class T> struct mysql_rs_getter;
template <uint8_t Len> struct mysql_rs_getter<::ff::mysql::bin_m<Len>> {
  template <typename RST>
  static ::ff::mysql::bin_m<Len> get(RST r, const std::string &name) {
    return ::ff::mysql::bin_m<Len>(r->getString(name));
  }
};

} // namespace sql
} // namespace ff





// for varbinary
namespace ff {
namespace mysql {
template <uint16_t Len> struct varbin_m {
public:
  varbin_m() : m_data(){};
  varbin_m(const char *s) : m_data(s){};
  varbin_m(const ::sql::SQLString &s) : m_data(s.c_str()) {}//c_str: return char*
  varbin_m(const varbin_m<Len> &s) : m_data(s.data()) {}
  varbin_m(varbin_m<Len> &&s) : m_data(std::move(s.m_data)) {}
  varbin_m<Len> &operator=(const varbin_m<Len> &s) {
    if (&s == this) {
      return *this;
    }
    m_data = s.m_data;
    return *this;
  };

  const std::string &data() const { return m_data; }//for s.data
  std::string &data() { return m_data; }

protected:
  std::string m_data;
};

namespace internal {
template <class T> struct dump_col_type_creation;
template <uint16_t Len> struct dump_col_type_creation<varbin_m<Len>> {
  static void dump(std::stringstream &ss) { ss << " VARCHAR(" << Len << ") "; }
};
} // namespace internal
} // namespace mysql
namespace sql {
template <class STMT, class T> struct mysql_bind_setter;

template <class STMT, uint16_t Len>
struct mysql_bind_setter<STMT, ::ff::mysql::varbin_m<Len>> {
  static void bind(STMT stmt, int index,
                   const ::ff::mysql::varbin_m<Len> &value) {
    stmt->setString(index, value.data());
  }
};

template <class T> struct mysql_rs_getter;
template <uint16_t Len> struct mysql_rs_getter<::ff::mysql::varbin_m<Len>> {
  template <typename RST>
  static ::ff::mysql::varbin_m<Len> get(RST r, const std::string &name) {
    return ::ff::mysql::varbin_m<Len>(r->getString(name));
  }
};

} // namespace sql
} // namespace ff





// for Blob
namespace ff {
namespace mysql {
struct blob_m {
public:
  inline blob_m() : m_data(){};
  inline blob_m(const char *s) : m_data(s){};
  inline blob_m(const std::istream *s) : ms_data(&*s){};
  inline blob_m(const ::sql::SQLString &s) : m_data(s.c_str()) {}
  inline blob_m(const blob_m &s) : m_data(s.data()) {}
  inline blob_m(blob_m &&s) : m_data(std::move(s.m_data)) {}
  blob_m  &operator=(const blob_m &s) {
    if (&s == this) {
      return *this;
    }
    m_data = s.m_data;
    return *this;
  };

  const std::string &data() const { return m_data; }//data的作用是什么？这两行函数的作用是什么？
  std::string &data() { return m_data; }

protected:
  std::string m_data;
  std::istream ms_data;
};

// namespace internal {
// template <class T> struct dump_col_type_creation;
// template <uint16_t Len> struct dump_col_type_creation<blob_m> {
//   static void dump(std::stringstream &ss) { ss << "TEXT(" << Len << ") "; }
// };
// } // namespace internal
} // namespace mysql
namespace sql {
template <class STMT, class T> struct mysql_bind_setter;

template <class STMT>
struct mysql_bind_setter<STMT, ::ff::mysql::blob_m > {
  static void bind(STMT stmt, int index,
                   const ::ff::mysql::blob_m  &value) {
    stmt->setBlob(index, value.data());
  }
};

template <class T> struct mysql_rs_getter;
template <> struct mysql_rs_getter<::ff::mysql::blob_m>{
  template <typename RST>
  static ::ff::mysql::blob_m get(RST r, const std::string &name) {
    return ::ff::mysql::blob_m (r->getBlob(name));
  }
};

} // namespace sql
} // namespace ff
