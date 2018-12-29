/***********************************************
  The MIT License (MIT)

  Copyright (c) 2012 Athrun Arthur <athrunarthur@gmail.com>

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
#include "ff/net/middleware/ntpackage.h"
#include <iostream>
#include <vector>

define_nt(email, std::string, "email");
define_nt(uid, uint64_t, "uid");
define_nt(_name, std::string, "name");
define_nt(ns, std::vector<std::string>, "ns");

typedef ff::net::ntpackage<112, email, uid, _name, ns> mypackage;

int main(int, char *[]) {
  mypackage p1;
  std::vector<std::string> nss;
  nss.push_back("n1");
  nss.push_back("n2");
  nss.push_back("n3");
  p1.set<email, uid, _name>("xuepeng", 123, "xuepeng@email.com");
  p1.set<ns>(nss);

  ff::net::marshaler c(ff::net::marshaler::length_retriver);
  p1.arch(c);
  size_t l = c.get_length();
  std::cout << "length: " << l << std::endl;
  char *buf = new char[l];
  ff::net::marshaler sc(buf, l, ff::net::marshaler::seralizer);
  p1.arch(sc);

  mypackage p2;
  ff::net::marshaler dc(buf, l, ff::net::marshaler::deseralizer);
  p2.arch(dc);

  std::cout << "email: " << p2.get<email>() << std::endl;
  std::cout << "uid: " << p2.get<uid>() << std::endl;
  std::cout << "_name: " << p2.get<_name>() << std::endl;
  auto tss = p2.get<ns>();
  for (size_t i = 0; i < tss.size(); ++i) {
    std::cout << "\tns: " << tss[i] << std::endl;
  }

  return 0;
}
