
/***********************************************
  The MIT License (MIT)

  Copyright (c) 2012-2020 Athrun Arthur <athrunarthur@gmail.com>

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
#include "ff/util/internal/user_new_type.h"
#include "ff/util/preprocessor.h"
#include "ff/util/tuple_type.h"
#include "ff/util/type_list.h"
#include <memory>
#include <vector>

namespace ff {
namespace util {
template <typename... ARGS> class ntobject;

template <typename... ARGS> struct nt_collect {
  typedef typename util::type_list<ARGS...> type_list;
};

template <typename... ARGS> struct nt_layout {
  typedef typename util::type_list<ARGS...> type_list;
};

namespace internal {

template <typename... ARGS> class nt_collect_storage;

template <typename ARG, typename... ARGS>
class nt_collect_storage<ARG, ARGS...> {
public:
  typedef typename util::type_list<ARG, ARGS...> type_list;

  template <typename CT>
  void set(size_t index, const typename internal::nt_traits<CT>::type &val) {
    static_assert(
        is_type_in_type_list<CT, util::type_list<ARG, ARGS...>>::value,
        "Cannot set a value that's not in nt_collect_storage!");
    const static int Index =
        get_index_of_type_in_typelist<CT, util::type_list<ARG, ARGS...>>::value;
    std::get<Index>(m_data[index]) = val;
  }

  template <typename CT, typename CT1, typename... CARGS, typename... PARGS>
  void set(size_t index, const typename internal::nt_traits<CT>::type &val,
           const typename internal::nt_traits<CT1>::type &val1,
           PARGS... params) {
    static_assert(
        is_type_in_type_list<CT, util::type_list<ARG, ARGS...>>::value,
        "Cannot set a value that's not in nt_collect_storage!");
    static_assert(
        is_type_in_type_list<CT1, util::type_list<ARG, ARGS...>>::value,
        "Cannot set a value that's not in nt_collect_storage!");
    const static int Index =
        get_index_of_type_in_typelist<CT, util::type_list<ARG, ARGS...>>::value;
    std::get<Index>(m_data[index]) = val;

    set<CT1, CARGS...>(index, val1, params...);
  }

  template <typename CT>
  typename internal::nt_traits<CT>::type get(size_t index) const {
    static_assert(
        is_type_in_type_list<CT, util::type_list<ARG, ARGS...>>::value,
        "Cannot get a value that's not in nt_collect_storage!");
    const static int Index =
        get_index_of_type_in_typelist<CT, util::type_list<ARG, ARGS...>>::value;
    return std::get<Index>(m_data[index]);
  }

  size_t size() const { return m_data.size(); }

protected:
  typedef
      typename convert_type_list_to_tuple<typename nt_extract_content_type_list<
          util::type_list<ARG, ARGS...>>::type>::type content_type;
  std::vector<content_type> m_data;
};

template <typename ARG> class nt_collect_storage<ARG> {
public:
  typedef typename util::type_list<ARG> type_list;

  template <typename CT>
  void set(size_t index, const typename internal::nt_traits<CT>::type &val) {
    static_assert(is_type_in_type_list<CT, util::type_list<ARG>>::value,
                  "Cannot set a value that's not in nt_collect_storage!");
    m_data[index] = val;
  }
  template <typename CT>
  typename internal::nt_traits<CT>::type get(size_t index) const {
    static_assert(is_type_in_type_list<CT, util::type_list<ARG>>::value,
                  "Cannot get a value that's not in the ntobject/row!");
    return m_data[index];
  }

  size_t size() const { return m_data.size(); }

protected:
  std::vector<ARG> m_data;
};

template <typename CollectType> struct get_collect_storage_type {};
template <typename... ARGS>
struct get_collect_storage_type<nt_collect<ARGS...>> {
  typedef nt_collect_storage<ARGS...> type;
};

template <typename TL> struct map_collect_list_to_storage_list {};
template <typename T1, typename T2, typename... TS>
struct map_collect_list_to_storage_list<type_list<T1, T2, TS...>> {
  typedef typename merge_type_list<
      type_list<typename get_collect_storage_type<T1>::type>,
      typename map_collect_list_to_storage_list<type_list<T2, TS...>>::type>::
      type type;
};
template <typename T1> struct map_collect_list_to_storage_list<type_list<T1>> {
  typedef type_list<typename get_collect_storage_type<T1>::type> type;
};

template <typename TC, typename CollectTypeList>
struct get_index_of_type_in_collect_typelist {
  const static int value = -1;
};
template <typename TC, typename TL1, typename... TS>
struct get_index_of_type_in_collect_typelist<TC, type_list<TL1, TS...>> {
  const static int value = std::conditional<
      get_index_of_type_in_typelist<TC, typename TL1::type_list>::value != -1,
      int_number_type<0>,
      int_number_type<1 + get_index_of_type_in_collect_typelist<
                              TC, type_list<TS...>>::value>>::type::value;
};

template <typename... ARGS> class nt_layout_storage {
public:
  template <typename CT>
  void set(size_t index, const typename internal::nt_traits<CT>::type &val) {
    const static int CIndex =
        get_index_of_type_in_collect_typelist<CT,
                                              util::type_list<ARGS...>>::value;
    static_assert(CIndex != -1,
                  "Cannot set a value that's not in the nt_object!");
    std::get<CIndex>(m_data).template set<CT>(index, val);
  }

  template <typename CT, typename CT1, typename... CARGS, typename... PARGS>
  void set(size_t index, const typename internal::nt_traits<CT>::type &val,
           const typename internal::nt_traits<CT1>::type &val1,
           PARGS... params) {
    const static int CIndex =
        get_index_of_type_in_collect_typelist<CT,
                                              util::type_list<ARGS...>>::value;
    static_assert(CIndex != -1,
                  "Cannot set a value that's not in the nt_object!");
    std::get<CIndex>(m_data).template set<CT>(index, val);

    set<CT1, CARGS...>(index, val1, params...);
  }

  template <typename CT>
  typename internal::nt_traits<CT>::type get(size_t index) const {
    const static int CIndex =
        get_index_of_type_in_collect_typelist<CT,
                                              util::type_list<ARGS...>>::value;
    static_assert(CIndex != -1,
                  "Cannot get a value that's not in the nt_object!");
    return std::get<CIndex>(m_data).template get<CT>(index);
  }

  size_t size() const { return std::get<0>(m_data).size(); }

protected:
  typedef type_list<ARGS...> collect_list;

  typedef typename convert_type_list_to_tuple<
      typename map_collect_list_to_storage_list<
          util::type_list<ARGS...>>::type>::type content_type;

  content_type m_data;
};

template <typename Layout> struct get_layout_storage_type {};
template <typename... ARGS> struct get_layout_storage_type<nt_layout<ARGS...>> {
  typedef nt_layout_storage<ARGS...> type;
};

template <typename NTObjType> struct ntobj_to_ntcollect {};
template <typename... ARGS> struct ntobj_to_ntcollect<ntobject<ARGS...>> {
  typedef nt_collect<ARGS...> type;
};

} // namespace internal

template <typename NTObjType,
          typename Layout =
              nt_layout<typename internal::ntobj_to_ntcollect<NTObjType>::type>>
class ntcompact_array {
public:
  typedef typename internal::get_layout_storage_type<Layout>::type storage_type;
  typedef ntcompact_array<NTObjType, Layout> self_type;

  template <typename... ARGS> class ntobject_in_array_impl {
  public:
    ntobject_in_array_impl(size_t index, self_type *s)
        : m_owner(s), m_index(index) {}

    template <typename CT, typename... CARGS, typename... PARGS>
    void set(const typename internal::nt_traits<CT>::type &val,
             PARGS... params) {
      m_owner->m_storage.template set<CT, CARGS...>(m_index, val, params...);
    }


    template <typename CT> typename internal::nt_traits<CT>::type get() const {
      return m_owner->m_storage.template get<CT>(m_index);
    }

  private:
    self_type *m_owner;
    size_t m_index;
  };

  template <typename NT> struct ntobject_in_array_type_helper {};
  template <typename... ARGS>
  struct ntobject_in_array_type_helper<ntobject<ARGS...>> {
    typedef ntobject_in_array_impl<ARGS...> type;
  };
  typedef typename ntobject_in_array_type_helper<NTObjType>::type
      ntobject_in_array_t;

  ntobject_in_array_t operator[](size_t i) {
    return ntobject_in_array_t(i, this);
  }

  size_t size() const { return m_storage.size(); }

protected:
  template <typename CT>
  void set(int index, const typename internal::nt_traits<CT>::type &val) {
    m_storage.template set<CT>(index, val);
  }

protected:
  storage_type m_storage;
};

} // namespace util
} // namespace ff
