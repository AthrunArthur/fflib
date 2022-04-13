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
/**
types method of date, time, datetime, timestamp, year are defined in setDatetime and getString,
the type defination as one data structure MYSQL_TIME on : usr/include/mysql/mysql_time.h
It seem that the difference of all time type will be separated in the setDatetime and getString.
The important is how to use these type like time, date in the fflib.
*/

// for time
namespace ff {
namespace mysql {
struct time_m {
public:
  inline time_m() : m_data(){};
  inline time_m(const char *s) : m_data(s){};
  inline time_m(const ::sql::SQLString &s) : m_data(s.c_str()) {}
  inline time_m(const time_m &s) : m_data(s.data()) {}
  time_m(time_m &&s) : m_data(std::move(s.m_data)) {}
  time_m  &operator=(const time_m &s) {
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
} // namespace mysql
namespace sql {
template <class STMT, class T> struct mysql_bind_setter;

template <class STMT>
struct mysql_bind_setter<STMT, ::ff::mysql::time_m > {
  static void bind(STMT stmt, int index,
                   const ::ff::mysql::time_m  &value) {
    stmt->setDateTime(index, value.data());
  }
};

template <class T> struct mysql_rs_getter;
template <> struct mysql_rs_getter<::ff::mysql::time_m>{
  template <typename RST>
  static ::ff::mysql::time_m get(RST r, const std::string &name) {
    return ::ff::mysql::time_m (r->getString(name));
  }
};

} // namespace sql
} // namespace ff


// for date
namespace ff {
namespace mysql {
struct date_m {
public:
  inline date_m() : m_data(){};
  inline date_m(const char *s) : m_data(s){};
  inline date_m(const ::sql::SQLString &s) : m_data(s.c_str()) {}
  inline date_m(const date_m &s) : m_data(s.data()) {}
  date_m(date_m &&s) : m_data(std::move(s.m_data)) {}
  date_m  &operator=(const date_m &s) {
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

} // namespace mysql
namespace sql {
template <class STMT, class T> struct mysql_bind_setter;

template <class STMT>
struct mysql_bind_setter<STMT, ::ff::mysql::date_m > {
  static void bind(STMT stmt, int index,
                   const ::ff::mysql::date_m  &value) {
    stmt->setDateTime(index, value.data());
  }
};

template <class T> struct mysql_rs_getter;
template <> struct mysql_rs_getter<::ff::mysql::date_m>{
  template <typename RST>
  static ::ff::mysql::date_m get(RST r, const std::string &name) {
    return ::ff::mysql::date_m (r->getString(name));
  }
};

} // namespace sql
} // namespace ff

// for datetime
namespace ff {
namespace mysql {
struct datetime_m {
public:
  inline datetime_m() : m_data(){};
  inline datetime_m(const char *s) : m_data(s){};
  inline datetime_m(const ::sql::SQLString &s) : m_data(s.c_str()) {}
  inline datetime_m(const datetime_m &s) : m_data(s.data()) {}
  datetime_m(datetime_m &&s) : m_data(std::move(s.m_data)) {}
  datetime_m  &operator=(const datetime_m &s) {
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

} // namespace mysql
namespace sql {
template <class STMT, class T> struct mysql_bind_setter;

template <class STMT>
struct mysql_bind_setter<STMT, ::ff::mysql::datetime_m > {
  static void bind(STMT stmt, int index,
                   const ::ff::mysql::datetime_m  &value) {
    stmt->setDateTime(index, value.data());
  }
};

template <class T> struct mysql_rs_getter;
template <> struct mysql_rs_getter<::ff::mysql::datetime_m>{
  template <typename RST>
  static ::ff::mysql::datetime_m get(RST r, const std::string &name) {
    return ::ff::mysql::datetime_m (r->getString(name));
  }
};

} // namespace sql
} // namespace ff

// for timestamp
namespace ff {
namespace mysql {
struct timestamp_m {
public:
  inline timestamp_m() : m_data(){};
  inline timestamp_m(const char *s) : m_data(s){};
  inline timestamp_m(const ::sql::SQLString &s) : m_data(s.c_str()) {}
  inline timestamp_m(const timestamp_m &s) : m_data(s.data()) {}
  timestamp_m(timestamp_m &&s) : m_data(std::move(s.m_data)) {}
  timestamp_m  &operator=(const timestamp_m &s) {
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

} // namespace mysql
namespace sql {
template <class STMT, class T> struct mysql_bind_setter;

template <class STMT>
struct mysql_bind_setter<STMT, ::ff::mysql::timestamp_m > {
  static void bind(STMT stmt, int index,
                   const ::ff::mysql::timestamp_m  &value) {
    stmt->setDateTime(index, value.data());
  }
};

template <class T> struct mysql_rs_getter;
template <> struct mysql_rs_getter<::ff::mysql::timestamp_m>{
  template <typename RST>
  static ::ff::mysql::timestamp_m get(RST r, const std::string &name) {
    return ::ff::mysql::timestamp_m (r->getString(name));
  }
};

} // namespace sql
} // namespace ff
