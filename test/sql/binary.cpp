#include "db_info.h"
#include "ff/sql/mysql.hpp"
#include "ff/sql/table.h"

struct mymeta {
  constexpr static const char *table_name = "xxxyyy_binary";
};

define_column(c1, column, uint64_t, "id");
define_column(c2, key, ff::mysql::varchar_m<64>, "event");
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

  mytable::row_collection_type rows;

  mytable::row_collection_type::row_type t1, t2;
  t1.set<c1, c2, sex, msex>(1, "1992-08-07 13:05:01", "male", "female");
  char tc[64];
  for (int i = 0; i < 64; i++) {
    tc[i] = rand() % 256;
  }
  t2 = t1;
  t2.set<sex>(ff::mysql::binary<64>(tc, 64));
  rows.push_back(std::move(t1));
  rows.push_back(std::move(t2));

  mytable::insert_or_replace_rows(&engine, rows);

  auto ret1 = mytable::select<c1, c2, sex, msex>(&engine).eval();
  std::cout << "size: " << ret1.size() << std::endl;
  for (size_t i = 0; i < ret1.size(); ++i) {
    std::cout << ret1[i].get<c1>() << ", " << ret1[i].get<c2>() << ", "
              << ret1[i].get<sex>() << ", " << ret1[i].get<msex>() << std::endl;
  }
  std::cout << "---------------" << std::endl;
  mytable::select<c1, c2>(&engine).where(c1::eq(1)).eval();

  return 0;
}
