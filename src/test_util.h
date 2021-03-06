/*
 * s3fs - FUSE-based file system backed by Amazon S3
 *
 * Copyright(C) 2014 Andrew Gaul <andrew@gaul.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <cstdlib>
#include <iostream>
#include <stdio.h>

template <typename T> void assert_equals(const T &x, const T &y, const char *file, int line)
{
  if (x != y) {
    std::cerr << x << " != " << y << " at " << file << ":" << line << std::endl;
    std::cerr << std::endl;
    std::exit(1);
  }
}

template <> void assert_equals(const std::string &x, const std::string &y, const char *file, int line)
{
  if (x != y) {
    std::cerr << x << " != " << y << " at " << file << ":" << line << std::endl;
    for (unsigned i=0; i<x.length(); i++)
       fprintf(stderr, "%02x ", (unsigned char)x[i]);
    std::cerr << std::endl;
    for (unsigned i=0; i<y.length(); i++)
       fprintf(stderr, "%02x ", (unsigned char)y[i]);
    std::cerr << std::endl;
    std::exit(1);
  }
}


template <typename T> void assert_nequals(const T &x, const T &y, const char *file, int line)
{
  if (x == y) {
    std::cerr << x << " == " << y << " at " << file << ":" << line << std::endl;
    std::exit(1);
  }
}

template <> void assert_nequals(const std::string &x, const std::string &y, const char *file, int line)
{
  if (x == y) {
    std::cerr << x << " == " << y << " at " << file << ":" << line << std::endl;
    for (unsigned i=0; i<x.length(); i++)
       fprintf(stderr, "%02x ", (unsigned char)x[i]);
    std::cerr << std::endl;
    for (unsigned i=0; i<y.length(); i++)
       fprintf(stderr, "%02x ", (unsigned char)y[i]);
    std::cerr << std::endl;
    std::exit(1);
  }
}

void assert_strequals(const char *x, const char *y, const char *file, int line)
{
  if(x == NULL && y == NULL){
    return;
  // cppcheck-suppress nullPointerRedundantCheck
  } else if(x == NULL || y == NULL || strcmp(x, y) != 0){
    std::cerr << (x ? x : "null") << " != " << (y ? y : "null") << " at " << file << ":" << line << std::endl;
    std::exit(1);
  }
}

#define ASSERT_EQUALS(x, y) \
  assert_equals((x), (y), __FILE__, __LINE__)

#define ASSERT_NEQUALS(x, y) \
  assert_nequals((x), (y), __FILE__, __LINE__)

#define ASSERT_STREQUALS(x, y) \
  assert_strequals((x), (y), __FILE__, __LINE__)
