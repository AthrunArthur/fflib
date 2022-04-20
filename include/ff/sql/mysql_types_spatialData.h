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

/* Geometry is an abstract class. However, in the prepared statement, we did not find its set method (in file:mysql_prepared_statement). 
At the same time, there are no judgement of responding class in getResult (mysql_ps_resultset.cpp). 
Also, we did not find the responding class in mysql include file.

Thus, we only define this type as usual string type here. Then, it may should be change base on relative classes.
*/

//for json_m
namespace ff {
namespace mysql {
struct json : public std::string {
public:
  json() : std::string(){};
  json(const char *s) : std::string(s){};
  json(const ::sql::SQLString &s) : std::string(s.c_str()){};
  json(const json &s) : std::string(s.c_str()){};
};

} // namespace mysql
namespace sql {
namespace internal {
template <class T> struct dump_col_type_creation;
template <> struct dump_col_type_creation<::ff::mysql::json> {
  static void dump(std::stringstream &ss) { ss << "JSON"; }
};
} // namespace internal
template <class STMT, class T> struct mysql_bind_setter;

template <class STMT>
struct mysql_bind_setter<STMT, ::ff::mysql::json > {
  static void bind(STMT stmt, int index,
                   const ::ff::mysql::json  &value) {
    stmt->setString(index, value);
  }
};

template <class T> struct mysql_rs_getter;
template <> struct mysql_rs_getter<::ff::mysql::json>{
  template <typename RST>
  static ::ff::mysql::json get(RST r, const std::string &name) {
    return ::ff::mysql::json (r->getString(name));
  }
};

} // namespace sql
} // namespace ff