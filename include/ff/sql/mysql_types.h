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
 ************************************************/
#pragma once
#include "ff/sql/table_create.h"
#include <cppconn/sqlstring.h>
#include "ff/sql/mysql_types_char_varchar_text.h"
#include "ff/sql/mysql_types_bin_varbin_blob.h"
#include <iostream>


// template<class T> class max{
//   public : 
//     T a;
//     // void abc(){std::cout << "this is spada";}
// };
// 
// template<> class max<int>{
//   int a;    
// };



// template<class T> T ma(T a){
//   return a;
// }
// 
// template<> int ma(int a){
//   return 0;
// }



// template<class T> void zi(T t){
//   cout << "this is zi";
// }
// 
// template<> void zi<int>(int t){
//   cout << "this is t";
// }
// 


// template<class B, class C> struct bd{
//   B a;
//   B abc(){return a;}
// };

// template<class A> struct bd<A, int>{
//   float a;
//   A abc(int c){cout << "this is piantehua" << endl;}
// };


// template<class T, class B> void k(){}
// template<class A> void k(){
//   A abc;
//   cout << abc;}

// template<>