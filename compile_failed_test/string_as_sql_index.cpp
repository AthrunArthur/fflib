#include "db_info.h"
#include "ff/sql/mysql.hpp"
#include "ff/sql/table.h"

struct mymeta {
  constexpr static const char *table_name = "failed_string2";
};

define_column(c1, key, ff::mysql::binary<64>, "id");
define_column(c2, index, std::string, "event");
define_column(sex, column, ff::mysql::binary<64>, "sex");
define_column(msex, column, ff::mysql::var_binary<64>, "msex");

typedef ff::sql::table<ff::sql::mysql<ff::sql::cppconn>, mymeta, c1, c2, sex,
                       msex>
    mytable;

int main(int argc, char *argv[]) {

  ff::sql::mysql<ff::sql::cppconn> engine(DB_CONNECTION, DB_USER, DB_PASSWORD,
                                          DB_DATABASENAME);
  engine.create_database();
  try {
    mytable::drop_table(&engine);
  } catch (...) {
    std::cout << "drop_table failed" << std::endl;
  }
  mytable::create_table(&engine);


  return 0;
}
