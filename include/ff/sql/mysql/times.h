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
#include <chrono>
#include <cppconn/sqlstring.h>
/**
types method of date, time, datetime, timestamp, year are defined in setDatetime and getString,
the type defination as one data structure MYSQL_TIME on : usr/include/mysql/mysql_time.h
It seem that the difference of all time type will be separated in the setDatetime and getString.
The important is how to use these type like time, date in the fflib.
*/

// for timestamp
namespace ff {
namespace sql {
namespace internal {
template <class T> struct dump_col_type_creation;
template <typename Clock, typename Rep, std::intmax_t Denom>
struct dump_col_type_creation<std::chrono::time_point<
    Clock, std::chrono::duration<Rep, std::ratio<1, Denom>>>> {
  static void dump(std::stringstream &ss) {
    ss << " TIMESTAMP (" << Denom << ") ";
  }
};
} // namespace internal
template <class STMT, class T> struct mysql_bind_setter;

// template <class STMT> struct mysql_bind_setter<STMT,
// ::ff::mysql::timestamp_m> { static void bind(STMT stmt, int index, const
// ::ff::mysql::timestamp_m &value) {
// stmt->setDateTime(index, value.data());
//}
//};

// template <class T> struct mysql_rs_getter;
// template <> struct mysql_rs_getter<::ff::mysql::timestamp_m> {
// template <typename RST>
// static ::ff::mysql::timestamp_m get(RST r, const std::string &name) {
// return ::ff::mysql::timestamp_m(r->getString(name));
//}
//};

} // namespace sql
} // namespace ff

// for time
namespace ff {
namespace mysql {
struct time_m : public std::string {
public:
  time_m() : std::string(){};
  time_m(const char *s) : std::string(s){};
  time_m(const ::sql::SQLString &s) : std::string(s.c_str()){};
  time_m(const time_m &s) : std::string(s.c_str()){};
};

} // namespace mysql
namespace sql {
namespace internal {
template <class T> struct dump_col_type_creation;
template <> struct dump_col_type_creation<::ff::mysql::time_m> {
  static void dump(std::stringstream &ss) { ss << "TIME"; }
};
} // namespace internal
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
struct date_m : public std::string {
public:
  date_m() : std::string(){};
  date_m(const char *s) : std::string(s){};
  date_m(const ::sql::SQLString &s) : std::string(s.c_str()){};
  date_m(const time_m &s) : std::string(s.c_str()){};
};

} // namespace mysql
namespace sql {
namespace internal {
template <class T> struct dump_col_type_creation;
template <> struct dump_col_type_creation<::ff::mysql::date_m> {
  static void dump(std::stringstream &ss) { ss << "DATE"; }
};
} // namespace internal

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
struct datetime_m : public std::string{
public:
  datetime_m() : std::string(){}
  datetime_m(char *s) : std::string(s){};
  datetime_m(const ::sql::SQLString &s) : std::string(s.c_str()){}
  datetime_m(const datetime_m &s) : std::string(s.c_str()){}
};


namespace sql {
namespace internal {
template <class T> struct dump_col_type_creation;
template <> struct dump_col_type_creation<::ff::mysql::datetime_m> {
  static void dump(std::stringstream &ss) { ss << "DATETIME"; }
};
} // namespace internal
} // namespace mysql
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




