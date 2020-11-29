//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//					 Kratos default license: kratos/license.txt
//
//  Main authors:    Arash Partow (This an adaptation of http://www.partow.net/programming/exprtk/index.html )
//                   Vicente Mataix Ferrandiz
//
//

/*
 **************************************************************
 *         C++ Mathematical Expression Toolkit Library        *
 *                                                            *
 * Examples and Unit-Tests                                    *
 * Author: Arash Partow (1999-2020)                           *
 * URL: http://www.partow.net/programming/exprtk/index.html   *
 *                                                            *
 * Copyright notice:                                          *
 * Free use of the Mathematical Expression Toolkit Library is *
 * permitted under the guidelines and in accordance with the  *
 * most current version of the MIT License.                   *
 * http://www.opensource.org/licenses/MIT                     *
 *                                                            *
 **************************************************************
*/


// System includes
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <deque>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

// External includes
#include "exprtk/exprtk.hpp"

// Project includes
#include "testing/testing.h"

namespace Kratos {

namespace Testing {

#ifdef exprtk_test_float32_type
typedef float numeric_type;
#else
typedef double numeric_type;
#endif

typedef std::pair<std::string,numeric_type> test_t;

static const test_t global_test_list[] =
                  {
                    // Note: Each of following tests must compile down
                    // to a single literal node.
                    test_t("0",0.0),
                    test_t("1",1.0),
                    test_t("2",2.0),
                    test_t("3",3.0),
                    test_t("4",4.0),
                    test_t("5",5.0),
                    test_t("6",6.0),
                    test_t("7",7.0),
                    test_t("8",8.0),
                    test_t("9",9.0),
                    test_t("12.12",12.12),
                    test_t("123.123",123.123),
                    test_t("1234.1234",1234.1234),
                    test_t("12345.12345",12345.12345),
                    test_t("123456.123456",123456.123456),
                    test_t("0.0",0.0),
                    test_t("1.0",1.0),
                    test_t("2.0",2.0),
                    test_t("3.0",3.0),
                    test_t("4.0",4.0),
                    test_t("5.0",5.0),
                    test_t("6.0",6.0),
                    test_t("7.0",7.0),
                    test_t("8.0",8.0),
                    test_t("9.0",9.0),
                    test_t("0.0",0.0),
                    test_t("1.1",1.1),
                    test_t("2.2",2.2),
                    test_t("3.3",3.3),
                    test_t("4.4",4.4),
                    test_t("5.5",5.5),
                    test_t("6.6",6.6),
                    test_t("7.7",7.7),
                    test_t("8.8",8.8),
                    test_t("9.9",9.9),
                    test_t("+0",0.0),
                    test_t("+1",1.0),
                    test_t("+2",2.0),
                    test_t("+3",3.0),
                    test_t("+4",4.0),
                    test_t("+5",5.0),
                    test_t("+6",6.0),
                    test_t("+7",7.0),
                    test_t("+8",8.0),
                    test_t("+9",9.0),
                    test_t("+0.0",0.0),
                    test_t("+1.0",1.0),
                    test_t("+2.0",2.0),
                    test_t("+3.0",3.0),
                    test_t("+4.0",4.0),
                    test_t("+5.0",5.0),
                    test_t("+6.0",6.0),
                    test_t("+7.0",7.0),
                    test_t("+8.0",8.0),
                    test_t("+9.0",9.0),
                    test_t("+0.0",0.0),
                    test_t("+1.1",1.1),
                    test_t("+2.2",2.2),
                    test_t("+3.3",3.3),
                    test_t("+4.4",4.4),
                    test_t("+5.5",5.5),
                    test_t("+6.6",6.6),
                    test_t("+7.7",7.7),
                    test_t("+8.8",8.8),
                    test_t("+9.9",9.9),
                    test_t("-0",-0.0),
                    test_t("-1",-1.0),
                    test_t("-2",-2.0),
                    test_t("-3",-3.0),
                    test_t("-4",-4.0),
                    test_t("-5",-5.0),
                    test_t("-6",-6.0),
                    test_t("-7",-7.0),
                    test_t("-8",-8.0),
                    test_t("-9",-9.0),
                    test_t("-0.0",-0.0),
                    test_t("-1.0",-1.0),
                    test_t("-2.0",-2.0),
                    test_t("-3.0",-3.0),
                    test_t("-4.0",-4.0),
                    test_t("-5.0",-5.0),
                    test_t("-6.0",-6.0),
                    test_t("-7.0",-7.0),
                    test_t("-8.0",-8.0),
                    test_t("-9.0",-9.0),
                    test_t("-0.0",-0.0),
                    test_t("-1.1",-1.1),
                    test_t("-2.2",-2.2),
                    test_t("-3.3",-3.3),
                    test_t("-4.4",-4.4),
                    test_t("-5.5",-5.5),
                    test_t("-6.6",-6.6),
                    test_t("-7.7",-7.7),
                    test_t("-8.8",-8.8),
                    test_t("-9.9",-9.9),
                    test_t("0.0e+0" ,+0.0e+0),
                    test_t("1.1e+1" ,+1.1e+1),
                    test_t("2.2e+2" ,+2.2e+2),
                    test_t("3.3e+3" ,+3.3e+3),
                    test_t("4.4e+4" ,+4.4e+4),
                    test_t("5.5e+5" ,+5.5e+5),
                    test_t("6.6e+6" ,+6.6e+6),
                    test_t("7.7e+7" ,+7.7e+7),
                    test_t("8.8e+8" ,+8.8e+8),
                    test_t("9.9e+9" ,+9.9e+9),
                    test_t("-0.0e+0",-0.0e+0),
                    test_t("-1.1e+1",-1.1e+1),
                    test_t("-2.2e+2",-2.2e+2),
                    test_t("-3.3e+3",-3.3e+3),
                    test_t("-4.4e+4",-4.4e+4),
                    test_t("-5.5e+5",-5.5e+5),
                    test_t("-6.6e+6",-6.6e+6),
                    test_t("-7.7e+7",-7.7e+7),
                    test_t("-8.8e+8",-8.8e+8),
                    test_t("-9.9e+9",-9.9e+9),
                    test_t("0.0E+0" ,+0.0E+0),
                    test_t("1.1E+1" ,+1.1E+1),
                    test_t("2.2E+2" ,+2.2E+2),
                    test_t("3.3E+3" ,+3.3E+3),
                    test_t("4.4E+4" ,+4.4E+4),
                    test_t("5.5E+5" ,+5.5E+5),
                    test_t("6.6E+6" ,+6.6E+6),
                    test_t("7.7E+7" ,+7.7E+7),
                    test_t("8.8E+8" ,+8.8E+8),
                    test_t("9.9E+9" ,+9.9E+9),
                    test_t("-0.0E+0",-0.0E+0),
                    test_t("-1.1E+1",-1.1E+1),
                    test_t("-2.2E+2",-2.2E+2),
                    test_t("-3.3E+3",-3.3E+3),
                    test_t("-4.4E+4",-4.4E+4),
                    test_t("-5.5E+5",-5.5E+5),
                    test_t("-6.6E+6",-6.6E+6),
                    test_t("-7.7E+7",-7.7E+7),
                    test_t("-8.8E+8",-8.8E+8),
                    test_t("-9.9E+9",-9.9E+9),
                    test_t("(0)",0.0),
                    test_t("(1)",1.0),
                    test_t("(2)",2.0),
                    test_t("(3)",3.0),
                    test_t("(4)",4.0),
                    test_t("(5)",5.0),
                    test_t("(6)",6.0),
                    test_t("(7)",7.0),
                    test_t("(8)",8.0),
                    test_t("(9)",9.0),
                    test_t("(0.0)",0.0),
                    test_t("(1.0)",1.0),
                    test_t("(2.0)",2.0),
                    test_t("(3.0)",3.0),
                    test_t("(4.0)",4.0),
                    test_t("(5.0)",5.0),
                    test_t("(6.0)",6.0),
                    test_t("(7.0)",7.0),
                    test_t("(8.0)",8.0),
                    test_t("(9.0)",9.0),
                    test_t("(0.0)",0.0),
                    test_t("(1.1)",1.1),
                    test_t("(2.2)",2.2),
                    test_t("(3.3)",3.3),
                    test_t("(4.4)",4.4),
                    test_t("(5.5)",5.5),
                    test_t("(6.6)",6.6),
                    test_t("(7.7)",7.7),
                    test_t("(8.8)",8.8),
                    test_t("(9.9)",9.9),
                    test_t("(+0)" ,0.0),
                    test_t("(+1)" ,1.0),
                    test_t("(+2)" ,2.0),
                    test_t("(+3)" ,3.0),
                    test_t("(+4)" ,4.0),
                    test_t("(+5)" ,5.0),
                    test_t("(+6)" ,6.0),
                    test_t("(+7)" ,7.0),
                    test_t("(+8)" ,8.0),
                    test_t("(+9)" ,9.0),
                    test_t("(+0.0)",0.0),
                    test_t("(+1.0)",1.0),
                    test_t("(+2.0)",2.0),
                    test_t("(+3.0)",3.0),
                    test_t("(+4.0)",4.0),
                    test_t("(+5.0)",5.0),
                    test_t("(+6.0)",6.0),
                    test_t("(+7.0)",7.0),
                    test_t("(+8.0)",8.0),
                    test_t("(+9.0)",9.0),
                    test_t("(+0.0)",0.0),
                    test_t("(+1.1)",1.1),
                    test_t("(+2.2)",2.2),
                    test_t("(+3.3)",3.3),
                    test_t("(+4.4)",4.4),
                    test_t("(+5.5)",5.5),
                    test_t("(+6.6)",6.6),
                    test_t("(+7.7)",7.7),
                    test_t("(+8.8)",8.8),
                    test_t("(+9.9)",9.9),
                    test_t("(-0)" ,-0.0),
                    test_t("(-1)" ,-1.0),
                    test_t("(-2)" ,-2.0),
                    test_t("(-3)" ,-3.0),
                    test_t("(-4)" ,-4.0),
                    test_t("(-5)" ,-5.0),
                    test_t("(-6)" ,-6.0),
                    test_t("(-7)" ,-7.0),
                    test_t("(-8)" ,-8.0),
                    test_t("(-9)" ,-9.0),
                    test_t("(-0.0)",-0.0),
                    test_t("(-1.0)",-1.0),
                    test_t("(-2.0)",-2.0),
                    test_t("(-3.0)",-3.0),
                    test_t("(-4.0)",-4.0),
                    test_t("(-5.0)",-5.0),
                    test_t("(-6.0)",-6.0),
                    test_t("(-7.0)",-7.0),
                    test_t("(-8.0)",-8.0),
                    test_t("(-9.0)",-9.0),
                    test_t("(-0.0)",-0.0),
                    test_t("(-1.1)",-1.1),
                    test_t("(-2.2)",-2.2),
                    test_t("(-3.3)",-3.3),
                    test_t("(-4.4)",-4.4),
                    test_t("(-5.5)",-5.5),
                    test_t("(-6.6)",-6.6),
                    test_t("(-7.7)",-7.7),
                    test_t("(-8.8)",-8.8),
                    test_t("(-9.9)",-9.9),
                    test_t("-(1.1)",-1.1),
                    test_t("-(1.1+2.2)",-3.3),
                    test_t("1234567890",1234567890),
                    test_t("123456789.0",123456789.0),
                    test_t("+1234567890",1234567890),
                    test_t("+123456789.0",123456789.0),
                    test_t("-1234567890",-1234567890),
                    test_t("-123456789.0",-123456789.0),
                    test_t("1234.567890",1234.567890),
                    test_t("-1234.567890",-1234.567890),
                    test_t("0+9",9.0),
                    test_t("1+8",9.0),
                    test_t("2+7",9.0),
                    test_t("3+6",9.0),
                    test_t("4+5",9.0),
                    test_t("5+4",9.0),
                    test_t("6+3",9.0),
                    test_t("7+2",9.0),
                    test_t("8+1",9.0),
                    test_t("9+0",9.0),
                    test_t(" 0 + 9 ",9.0),
                    test_t(" 1 + 8 ",9.0),
                    test_t(" 2 + 7 ",9.0),
                    test_t(" 3 + 6 ",9.0),
                    test_t(" 4 + 5 ",9.0),
                    test_t(" 5 + 4 ",9.0),
                    test_t(" 6 + 3 ",9.0),
                    test_t(" 7 + 2 ",9.0),
                    test_t(" 8 + 1 ",9.0),
                    test_t(" 9 + 0 ",9.0),
                    test_t("( 0 + 9 )",9.0),
                    test_t("( 1 + 8 )",9.0),
                    test_t("( 2 + 7 )",9.0),
                    test_t("( 3 + 6 )",9.0),
                    test_t("( 4 + 5 )",9.0),
                    test_t("( 5 + 4 )",9.0),
                    test_t("( 6 + 3 )",9.0),
                    test_t("( 7 + 2 )",9.0),
                    test_t("( 8 + 1 )",9.0),
                    test_t("( 9 + 0 )",9.0),
                    test_t("1E1+1",11.0),
                    test_t("1e1+1",11.0),
                    test_t("1E1-1", 9.0),
                    test_t("1e1-1", 9.0),
                    test_t("1E01+1",11.0),
                    test_t("1e01+1",11.0),
                    test_t("1E01-1", 9.0),
                    test_t("1e01-1", 9.0),
                    test_t("1+2",+3.0),
                    test_t("1-2",-1.0),
                    test_t("1*2",+2.0),
                    test_t("1/2",+0.5),
                    test_t("1.1+2.2", +3.3),
                    test_t("1.1-2.2", -1.1),
                    test_t("1.1*2.2",+2.42),
                    test_t("1.1/2.2", +0.5),
                    test_t("0-9",-9.0),
                    test_t("1-8",-7.0),
                    test_t("2-7",-5.0),
                    test_t("3-6",-3.0),
                    test_t("4-5",-1.0),
                    test_t("5-4",+1.0),
                    test_t("6-3",+3.0),
                    test_t("7-2",+5.0),
                    test_t("8-1",+7.0),
                    test_t("9-0",+9.0),
                    test_t("2.*3",+6.0),
                    test_t("2.*3.",+6.0),
                    test_t("2.+3",+5.0),
                    test_t("2.+3.",+5.0),
                    test_t("123.*456.",+56088.0),
                    test_t(" 0 - 9 ",-9.0),
                    test_t(" 1 - 8 ",-7.0),
                    test_t(" 2 - 7 ",-5.0),
                    test_t(" 3 - 6 ",-3.0),
                    test_t(" 4 - 5 ",-1.0),
                    test_t(" 5 - 4 ",+1.0),
                    test_t(" 6 - 3 ",+3.0),
                    test_t(" 7 - 2 ",+5.0),
                    test_t(" 8 - 1 ",+7.0),
                    test_t(" 9 - 0 ",+9.0),
                    test_t("( 0 - 9 )",-9.0),
                    test_t("( 1 - 8 )",-7.0),
                    test_t("( 2 - 7 )",-5.0),
                    test_t("( 3 - 6 )",-3.0),
                    test_t("( 4 - 5 )",-1.0),
                    test_t("( 5 - 4 )",+1.0),
                    test_t("( 6 - 3 )",+3.0),
                    test_t("( 7 - 2 )",+5.0),
                    test_t("( 8 - 1 )",+7.0),
                    test_t("( 9 - 0 )",+9.0),
                    test_t("-(1+2)",-3.0),
                    test_t("+(1+2)",+3.0),
                    test_t("+(1-2)",-1.0),
                    test_t("-(1-2)",+1.0),
                    test_t("(-3*-6)",+18.0),
                    test_t("(-6*-3)",+18.0),
                    test_t("-(-3*-6)",-18.0),
                    test_t("-(-6*-3)",-18.0),
                    test_t("1.1+2.2+3.3",+6.6),
                    test_t("+1.1+2.2+3.3",+6.6),
                    test_t("-1.1-2.2-3.3",-6.6),
                    test_t("1.1*2.2*3.3",+7.986),
                    test_t("+1.1*2.2*3.3",+7.986),
                    test_t("-1.1*-2.2*-3.3",-7.986),
                    test_t("1 + 1/2",+1.5),
                    test_t("1 + (1/2)",+1.5),
                    test_t("1.1 + 1.1/2.2",+1.6),
                    test_t("1.1 + (1.1/2.2)",+1.6),
                    test_t("2 * 1/2",+1.0),
                    test_t("2 * (1/2)",+1.0),
                    test_t("2.2 * 1.1/2.2",+1.1),
                    test_t("2.2 * (1.1/2.2)",+1.1),
                    test_t("1^2",1.0),
                    test_t("2^1",2.0),
                    test_t("2^3",8.0),
                    test_t("-2^3",-8.0),
                    test_t("-2^4",-16.0),
                    test_t("(-2)^3",-8.0),
                    test_t("(-2)^4",+16.0),
                    test_t("3^2^4",43046721.0),
                    test_t("1.1^2.2",1.23328630055466251099),
                    test_t("2.2^1.1",2.3804822576003541627),
                    test_t("2.2^3.3",13.48946876053338489127),
                    test_t("3.3^2.2^1.1",17.15193942371376191362),
                    test_t("+3.3^2.2^1.1",17.15193942371376191362),
                    test_t("3.3^+2.2^1.1",17.15193942371376191362),
                    test_t("3.3^2.2^+1.1",17.15193942371376191362),
                    test_t("3.3^2.2^-1.1",1.65127293793867959137),
                    test_t("+3.3^+2.2^-1.1",1.65127293793867959137),
                    test_t("1.1^(1.1 * 2.2)",1.25941916576299080582),
                    test_t("2.2^(1.1 * 3.3)",17.49823848953534759743),
                    test_t("3.3^(1.1 * 2.2)",17.98058156638874965269),
                    test_t("1.1^-2.2/1.1",0.73712884727743375853),
                    test_t("1.1^+2.2/1.1",1.121169364140602282717273261774),
                    test_t("1.1^2.2/+1.1",1.121169364140602282717273261774),
                    test_t("1.1^+2.2/+1.1",1.121169364140602282717273261774),
                    test_t("1.1^+2.2/-1.1",-1.121169364140602282717273261774),
                    test_t("1.1^2.2/-1.1",-1.121169364140602282717273261774),
                    test_t("1.1^+2.2/-1.1",-1.121169364140602282717273261774),
                    test_t("+1.1^-2.2/1.1",0.73712884727743375853),
                    test_t("+1.1^+2.2/1.1",1.121169364140602282717273261774),
                    test_t("+1.1^2.2/+1.1",1.121169364140602282717273261774),
                    test_t("+1.1^+2.2/+1.1",1.121169364140602282717273261774),
                    test_t("+1.1^+2.2/-1.1",-1.121169364140602282717273261774),
                    test_t("+1.1^2.2/-1.1",-1.121169364140602282717273261774),
                    test_t("+1.1^+2.2/-1.1",-1.121169364140602282717273261774),
                    test_t("equal(1.23^3,(1.23 * 1.23 * 1.23))",1.0),
                    test_t("equal(1.23^-3,1/(1.23 * 1.23 * 1.23))",1.0),
                    test_t("equal((2.1 + 1.23^3),(2.1 + [1.23 * 1.23 * 1.23]))",1.0),
                    test_t("equal((2.1 - 1.23^3),(2.1 - [1.23 * 1.23 * 1.23]))",1.0),
                    test_t("equal((2.1 * 1.23^3),(2.1 * [1.23 * 1.23 * 1.23]))",1.0),
                    test_t("equal((2.1 / 1.23^3),(2.1 / [1.23 * 1.23 * 1.23]))",1.0),
                    test_t("equal((1.23^3 + 2.1),({1.23 * 1.23 * 1.23} + 2.1))",1.0),
                    test_t("equal((1.23^3 - 2.1),({1.23 * 1.23 * 1.23} - 2.1))",1.0),
                    test_t("equal((1.23^3 * 2.1),({1.23 * 1.23 * 1.23} * 2.1))",1.0),
                    test_t("equal((1.23^3 / 2.1),({1.23 * 1.23 * 1.23} / 2.1))",1.0),
                    test_t("equal(1.0^(1.0/2.0),sqrt(1.0))",1.0),
                    test_t("equal(1.0^(1.0/2.0),root(1.0,2.0))",1.0),
                    test_t("equal(1.0^(1.0/3.0),root(1.0,3.0))",1.0),
                    test_t("equal(1.0^(1.0/4.0),root(1.0,4.0))",1.0),
                    test_t("equal(1.0^(1.0/5.0),root(1.0,5.0))",1.0),
                    test_t("equal(1.0^(1.0/6.0),root(1.0,6.0))",1.0),
                    test_t("equal(1.0^(1.0/7.0),root(1.0,7.0))",1.0),
                    test_t("equal(1.0^(1.0/8.0),root(1.0,8.0))",1.0),
                    test_t("equal(1.0^(1.0/9.0),root(1.0,9.0))",1.0),
                    test_t("equal(2.0^(1.0/2.0),sqrt(2.0))",1.0),
                    test_t("equal(2.0^(1.0/2.0),root(2.0,2.0))",1.0),
                    test_t("equal(3.0^(1.0/3.0),root(3.0,3.0))",1.0),
                    test_t("equal(4.0^(1.0/4.0),root(4.0,4.0))",1.0),
                    test_t("equal(5.0^(1.0/5.0),root(5.0,5.0))",1.0),
                    test_t("equal(6.0^(1.0/6.0),root(6.0,6.0))",1.0),
                    test_t("equal(7.0^(1.0/7.0),root(7.0,7.0))",1.0),
                    test_t("equal(8.0^(1.0/8.0),root(8.0,8.0))",1.0),
                    test_t("equal(9.0^(1.0/9.0),root(9.0,9.0))",1.0),
                    test_t("1 <  2", 1.0),
                    test_t("1 <= 2", 1.0),
                    test_t("1.1 <= 2.2", 1.0),
                    test_t("(1.0 + 0.1) <= (2.0 + 0.2)", 1.0),
                    test_t("1 >  2", 0.0),
                    test_t("1 >= 2", 0.0),
                    test_t("1.1 >= 2.2", 0.0),
                    test_t("(1.0 + 0.1) >= (2.0 + 0.2)", 0.0),
                    test_t("1 <> 2", 1.0),
                    test_t("1 != 2", 1.0),
                    test_t("1.1 <> 2.2", 1.0),
                    test_t("1.1 != 2.2", 1.0),
                    test_t("(1.0 + 0.1) <> (2.0 + 0.2)", 1.0),
                    test_t("(1.0 + 0.1) != (2.0 + 0.2)", 1.0),
                    test_t("1 == 1", 1.0),
                    test_t("1.1 == 1.1", 1.0),
                    test_t("1 = 1", 1.0),
                    test_t("1.1 = 1.1", 1.0),
                    test_t("1 <> 1", 0.0),
                    test_t("1 != 1", 0.0),
                    test_t("1.1 <> 1.1", 0.0),
                    test_t("1.1 != 1.1", 0.0),
                    test_t("(1.0 + 0.1) <> (1.0 + 0.1)", 0.0),
                    test_t("(1.0 + 0.1) != (1.0 + 0.1)", 0.0),
                    test_t("equal(1.1,1.1)",1.0),
                    test_t("equal(1.1,2.2)",0.0),
                    test_t("not_equal(1.1,1.1)",0.0),
                    test_t("not_equal(1.1,2.2)",1.0),
                    test_t("1 and 1",1.0),
                    test_t("1 and 0",0.0),
                    test_t("0 and 1",0.0),
                    test_t("0 and 0",0.0),
                    test_t("1.0 and 1.0",1.0),
                    test_t("1.0 and 0.0",0.0),
                    test_t("0.0 and 1.0",0.0),
                    test_t("0.0 and 0.0",0.0),
                    test_t("(1 and 1)",1.0),
                    test_t("(1 and 0)",0.0),
                    test_t("(0 and 1)",0.0),
                    test_t("(0 and 0)",0.0),
                    test_t("(1.0 and 1.0)",1.0),
                    test_t("(1.0 and 0.0)",0.0),
                    test_t("(0.0 and 1.0)",0.0),
                    test_t("(0.0 and 0.0)",0.0),
                    test_t("1 or 1",1.0),
                    test_t("1 or 0",1.0),
                    test_t("0 or 1",1.0),
                    test_t("0 or 0",0.0),
                    test_t("1.0 or 1.0",1.0),
                    test_t("1.0 or 0.0",1.0),
                    test_t("0.0 or 1.0",1.0),
                    test_t("0.0 or 0.0",0.0),
                    test_t("(1 or 1)",1.0),
                    test_t("(1 or 0)",1.0),
                    test_t("(0 or 1)",1.0),
                    test_t("(0 or 0)",0.0),
                    test_t("(1.0 or 1.0)",1.0),
                    test_t("(1.0 or 0.0)",1.0),
                    test_t("(0.0 or 1.0)",1.0),
                    test_t("(0.0 or 0.0)",0.0),
                    test_t("1 nand 1",0.0),
                    test_t("1 nand 0",1.0),
                    test_t("0 nand 1",1.0),
                    test_t("0 nand 0",1.0),
                    test_t("1.0 nand 1.0",0.0),
                    test_t("1.0 nand 0.0",1.0),
                    test_t("0.0 nand 1.0",1.0),
                    test_t("0.0 nand 0.0",1.0),
                    test_t("(1 nand 1)",0.0),
                    test_t("(1 nand 0)",1.0),
                    test_t("(0 nand 1)",1.0),
                    test_t("(0 nand 0)",1.0),
                    test_t("(1.0 nand 1.0)",0.0),
                    test_t("(1.0 nand 0.0)",1.0),
                    test_t("(0.0 nand 1.0)",1.0),
                    test_t("(0.0 nand 0.0)",1.0),
                    test_t("1 nor 1",0.0),
                    test_t("1 nor 0",0.0),
                    test_t("0 nor 1",0.0),
                    test_t("0 nor 0",1.0),
                    test_t("1.0 nor 1.0",0.0),
                    test_t("1.0 nor 0.0",0.0),
                    test_t("0.0 nor 1.0",0.0),
                    test_t("0.0 nor 0.0",1.0),
                    test_t("(1 nor 1)",0.0),
                    test_t("(1 nor 0)",0.0),
                    test_t("(0 nor 1)",0.0),
                    test_t("(0 nor 0)",1.0),
                    test_t("(1.0 nor 1.0)",0.0),
                    test_t("(1.0 nor 0.0)",0.0),
                    test_t("(0.0 nor 1.0)",0.0),
                    test_t("(0.0 nor 0.0)",1.0),
                    test_t("0 xor 0",0.0),
                    test_t("0 xor 1",1.0),
                    test_t("1 xor 0",1.0),
                    test_t("1 xor 1",0.0),
                    test_t("0.0 xor 0.0",0.0),
                    test_t("0.0 xor 1.0",1.0),
                    test_t("1.0 xor 0.0",1.0),
                    test_t("1.0 xor 1.0",0.0),
                    test_t("(0 xor 0)",0.0),
                    test_t("(0 xor 1)",1.0),
                    test_t("(1 xor 0)",1.0),
                    test_t("(1 xor 1)",0.0),
                    test_t("(0.0 xor 0.0)",0.0),
                    test_t("(0.0 xor 1.0)",1.0),
                    test_t("(1.0 xor 0.0)",1.0),
                    test_t("(1.0 xor 1.0)",0.0),
                    test_t("1 & 1",1.0),
                    test_t("1 & 0",0.0),
                    test_t("0 & 1",0.0),
                    test_t("0 & 0",0.0),
                    test_t("1.0 & 1.0",1.0),
                    test_t("1.0 & 0.0",0.0),
                    test_t("0.0 & 1.0",0.0),
                    test_t("0.0 & 0.0",0.0),
                    test_t("(1 & 1)",1.0),
                    test_t("(1 & 0)",0.0),
                    test_t("(0 & 1)",0.0),
                    test_t("(0 & 0)",0.0),
                    test_t("(1.0 & 1.0)",1.0),
                    test_t("(1.0 & 0.0)",0.0),
                    test_t("(0.0 & 1.0)",0.0),
                    test_t("(0.0 & 0.0)",0.0),
                    test_t("1 | 1",1.0),
                    test_t("1 | 0",1.0),
                    test_t("0 | 1",1.0),
                    test_t("0 | 0",0.0),
                    test_t("1.0 | 1.0",1.0),
                    test_t("1.0 | 0.0",1.0),
                    test_t("0.0 | 1.0",1.0),
                    test_t("0.0 | 0.0",0.0),
                    test_t("(1 | 1)",1.0),
                    test_t("(1 | 0)",1.0),
                    test_t("(0 | 1)",1.0),
                    test_t("(0 | 0)",0.0),
                    test_t("(1.0 | 1.0)",1.0),
                    test_t("(1.0 | 0.0)",1.0),
                    test_t("(0.0 | 1.0)",1.0),
                    test_t("(0.0 | 0.0)",0.0),
                    test_t("(1 nand 1) == not(1 and 1)",1.0),
                    test_t("(1 nand 0) == not(1 and 0)",1.0),
                    test_t("(0 nand 1) == not(0 and 1)",1.0),
                    test_t("(0 nand 0) == not(0 and 0)",1.0),
                    test_t("(1 nor 1) == not(1 or 1)",1.0),
                    test_t("(1 nor 0) == not(1 or 0)",1.0),
                    test_t("(0 nor 1) == not(0 or 1)",1.0),
                    test_t("(0 nor 0) == not(0 or 0)",1.0),
                    test_t("(1.0 nand 1.0) == not(1.0 and 1.0)",1.0),
                    test_t("(1.0 nand 0.0) == not(1.0 and 0.0)",1.0),
                    test_t("(0.0 nand 1.0) == not(0.0 and 1.0)",1.0),
                    test_t("(0.0 nand 0.0) == not(0.0 and 0.0)",1.0),
                    test_t("(1.0 nor 1.0) == not(1.0 or 1.0)",1.0),
                    test_t("(1.0 nor 0.0) == not(1.0 or 0.0)",1.0),
                    test_t("(0.0 nor 1.0) == not(0.0 or 1.0)",1.0),
                    test_t("(0.0 nor 0.0) == not(0.0 or 0.0)",1.0),
                    test_t("(1 nand 1) == not(1 & 1)",1.0),
                    test_t("(1 nand 0) == not(1 & 0)",1.0),
                    test_t("(0 nand 1) == not(0 & 1)",1.0),
                    test_t("(0 nand 0) == not(0 & 0)",1.0),
                    test_t("(1 nor 1) == not(1 | 1)",1.0),
                    test_t("(1 nor 0) == not(1 | 0)",1.0),
                    test_t("(0 nor 1) == not(0 | 1)",1.0),
                    test_t("(0 nor 0) == not(0 | 0)",1.0),
                    test_t("(1.0 nand 1.0) == not(1.0 & 1.0)",1.0),
                    test_t("(1.0 nand 0.0) == not(1.0 & 0.0)",1.0),
                    test_t("(0.0 nand 1.0) == not(0.0 & 1.0)",1.0),
                    test_t("(0.0 nand 0.0) == not(0.0 & 0.0)",1.0),
                    test_t("(1.0 nor 1.0) == not(1.0 | 1.0)",1.0),
                    test_t("(1.0 nor 0.0) == not(1.0 | 0.0)",1.0),
                    test_t("(0.0 nor 1.0) == not(0.0 | 1.0)",1.0),
                    test_t("(0.0 nor 0.0) == not(0.0 | 0.0)",1.0),
                    test_t("mand(1,1)",1.0),
                    test_t("mand(1,0)",0.0),
                    test_t("mand(0,1)",0.0),
                    test_t("mand(0,0)",0.0),
                    test_t("mand(1.0,1.0)",1.0),
                    test_t("mand(1.0,0.0)",0.0),
                    test_t("mand(0.0,1.0)",0.0),
                    test_t("mand(0.0,0.0)",0.0),
                    test_t("mor(1,1)",1.0),
                    test_t("mor(1,0)",1.0),
                    test_t("mor(0,1)",1.0),
                    test_t("mor(0,0)",0.0),
                    test_t("mor(1.0,1.0)",1.0),
                    test_t("mor(1.0,0.0)",1.0),
                    test_t("mor(0.0,1.0)",1.0),
                    test_t("mor(0.0,0.0)",0.0),
                    test_t("(1 nand 1) == not(mand(1,1))",1.0),
                    test_t("(1 nand 0) == not(mand(1,0))",1.0),
                    test_t("(0 nand 1) == not(mand(0,1))",1.0),
                    test_t("(0 nand 0) == not(mand(0,0))",1.0),
                    test_t("(1 nor 1) == not(mor(1,1))",1.0),
                    test_t("(1 nor 0) == not(mor(1,0))",1.0),
                    test_t("(0 nor 1) == not(mor(0,1))",1.0),
                    test_t("(0 nor 0) == not(mor(0,0))",1.0),
                    test_t("(1.0 nand 1.0) == not(mand(1.0,1.0))",1.0),
                    test_t("(1.0 nand 0.0) == not(mand(1.0,0.0))",1.0),
                    test_t("(0.0 nand 1.0) == not(mand(0.0,1.0))",1.0),
                    test_t("(0.0 nand 0.0) == not(mand(0.0,0.0))",1.0),
                    test_t("(1.0 nor 1.0) == not(mor(1.0,1.0))",1.0),
                    test_t("(1.0 nor 0.0) == not(mor(1.0,0.0))",1.0),
                    test_t("(0.0 nor 1.0) == not(mor(0.0,1.0))",1.0),
                    test_t("(0.0 nor 0.0) == not(mor(0.0,0.0))",1.0),
                    test_t("abs(1)",1.0),
                    test_t("abs(-1)",1.0),
                    test_t("abs(1.0)",1.0),
                    test_t("abs(-1.0)",1.0),
                    test_t("min(1,2)",1.0),
                    test_t("min(1,2,3)",1.0),
                    test_t("min(1,2,3,4)",1.0),
                    test_t("min(1,2,3,4,5)",1.0),
                    test_t("min(1,2,3,4,5,6)",1.0),
                    test_t("min(1.1,2.2)",1.1),
                    test_t("min(1.1,2.2,3.3)",1.1),
                    test_t("min(1.1,2.2,3.3,4.4)",1.1),
                    test_t("min(1.1,2.2,3.3,4.4,5.5)",1.1),
                    test_t("min(1.1,2.2,3.3,4.4,5.5,6.6)",1.1),
                    test_t("min(min(1,2),min(3,4))",1.0),
                    test_t("max(1,2)",2.0),
                    test_t("max(1,2,3)",3.0),
                    test_t("max(1,2,3,4)",4.0),
                    test_t("max(1,2,3,4,5)",5.0),
                    test_t("max(1,2,3,4,5,6)",6.0),
                    test_t("max(1.1,2.2)",2.2),
                    test_t("max(1.1,2.2,3.3)",3.3),
                    test_t("max(1.1,2.2,3.3,4.4)",4.4),
                    test_t("max(1.1,2.2,3.3,4.4,5.5)",5.5),
                    test_t("max(1.1,2.2,3.3,4.4,5.5,6.6)",6.6),
                    test_t("max(max(1,2),max(3,4))",4.0),
                    test_t("avg(1,2)",1.5),
                    test_t("avg(1,2,3)",2.0),
                    test_t("avg(1,2,3,4)",2.5),
                    test_t("avg(1,2,3,4,5)",3.0),
                    test_t("avg(1.1,2.2)",1.65),
                    test_t("avg(1.1,2.2,3.3)",2.2),
                    test_t("avg(1.1,2.2,3.3,4.4)",2.75),
                    test_t("avg(1.1,2.2,3.3,4.4,5.5)",3.3),
                    test_t("avg(1.1,2.2,3.3,4.4,5.5,6.6)",3.85),
                    test_t("sum(1,2)",3.0),
                    test_t("sum(1,2,3)",6.0),
                    test_t("sum(1,2,3,4)",10),
                    test_t("sum(1,2,3,4,5)",15.0),
                    test_t("sum(1,2,3,4,5,6)",21),
                    test_t("sum(1.1,2.2)",3.3),
                    test_t("sum(1.1,2.2,3.3)",6.6),
                    test_t("sum(1.1,2.2,3.3,4.4)",11.0),
                    test_t("sum(1.1,2.2,3.3,4.4,5.5)",16.5),
                    test_t("sum(1.1,2.2,3.3,4.4,5.5,6.6)",23.1),
                    test_t("mul(1,2)",2.0),
                    test_t("mul(1,2,3)",6.0),
                    test_t("mul(1,2,3,4)",24.0),
                    test_t("mul(1,2,3,4,5)",120.0),
                    test_t("mul(1,2,3,4,5,6)",720.0),
                    test_t("mul(1.1,2.2)",2.42),
                    test_t("mul(1.1,2.2,3.3)",7.986),
                    test_t("mul(1.1,2.2,3.3,4.4)",35.1384),
                    test_t("mul(1.1,2.2,3.3,4.4,5.5)",193.2612),
                    test_t("mul(1.1,2.2,3.3,4.4,5.5,6.6)",1275.52392),
                    test_t("equal(sum(1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9),(1.1+2.2+3.3+4.4+5.5+6.6+7.7+8.8+9.9))",1.0),
                    test_t("equal(mul(1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9),(1.1*2.2*3.3*4.4*5.5*6.6*7.7*8.8*9.9))",1.0),
                    test_t("equal(min(1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9),1.1)",1.0),
                    test_t("equal(max(1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9),9.9)",1.0),
                    test_t("equal(avg(1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9),5.5)",1.0),
                    test_t("floor(1.0)",1.0),
                    test_t("floor(1.1)",1.0),
                    test_t("floor(-1.0)",-1.0),
                    test_t("floor(-1.1)",-2.0),
                    test_t("ceil(1.0)",1.0),
                    test_t("ceil(1.1)",2.0),
                    test_t("ceil(-1.0)",-1.0),
                    test_t("ceil(-1.1)",-1.0),
                    test_t("round(1.1)",1.0),
                    test_t("round(1.49)",1.0),
                    test_t("round(1.5)",2.0),
                    test_t("round(1.9)",2.0),
                    test_t("roundn(1/3,2)",0.33),
                    test_t("roundn(1/3,5)",0.33333),
                    test_t("roundn(2/3,2)",0.67),
                    test_t("roundn(2/3,5)",0.66667),
                    test_t("roundn(1.0/3.0,2.0)",0.33),
                    test_t("roundn(1.0/3.0,5.0)",0.33333),
                    test_t("roundn(2.0/3.0,2.0)",0.67),
                    test_t("roundn(2.0/3.0,5.0)",0.66667),
                    test_t("cos(0.0)",1.0),
                    test_t("sin(0.0)",0.0),
                    test_t("equal(sin(pi/4.0),cos(pi/4.0))",1.0),
                    test_t("equal(sin(pi/6.0),cos(pi/3.0))",1.0),
                    test_t("(sin(pi/4.0) - cos(pi/4.0)) <= epsilon",1.0),
                    test_t("(cos(pi/3.0) - sin(pi/6.0)) <= epsilon",1.0),
                    test_t("sin(deg2rad(30))",0.5),
                    test_t("cos(deg2rad(60))",0.5),
                    test_t("sin(deg2rad(30)) + cos(deg2rad(60))",1.0),
                    test_t("equal(sin(deg2rad(30))/cos(deg2rad(30)),tan(deg2rad(30)))",1.0),
                    test_t("equal(sinh(pi),11.5487393572577483779773343153884) ",1.0),
                    test_t("equal(asinh(11.5487393572577483779773343153884),pi)",1.0),
                    test_t("equal(cosh(pi),11.5919532755215206277517520525601) ",1.0),
                    test_t("equal(acosh(11.5919532755215206277517520525601),pi)",1.0),
                    test_t("equal(tanh(pi),0.99627207622074994426469058001253) ",1.0),
                    test_t("equal(atanh(0.99627207622074994426469058001253),pi)",1.0),
                    test_t("exp(1.0)",2.71828182845904523536028747135266249775724),
                    test_t("exp(0.0)",1.0),
                    test_t("log(2.7182818284590451)",1.0),
                    test_t("log10(10.0)",1.0),
                    test_t("frac(12.34) + trunc(12.34)",12.34),
                    test_t("hypot(3.0,4.0)",5.0),
                    test_t("hypot(1.0,sqrt(3.0))",2.0),
                    test_t("if(1 < 2, 3, 4)",3.0),
                    test_t("if(1.1 < 2.2, 3.3, 4.4)",3.3),
                    test_t("if((1.0+1.1) < (2.0+1.2), 3.3, 4.4)",3.3),
                    test_t("if(1 = 2, 3, 4)",4.0),
                    test_t("if(1.1 = 2.2, 3.3, 4.4)",4.4),
                    test_t("if((1.0+1.1) = (2.0+1.2), 3.3, 4.4)",4.4),
                    test_t("if(1 == 2, 3, 4)",4.0),
                    test_t("if(1.1 == 2.2, 3.3, 4.4)",4.4),
                    test_t("if((1.0+1.1) == (2.0+1.2), 3.3, 4.4)",4.4),
                    test_t("if(1 >= 2, 3, 4)",4.0),
                    test_t("if(1.1 >= 2.2, 3.3, 4.4)",4.4),
                    test_t("if((1.0+1.1) >= (2.0+1.2), 3.3, 4.4)",4.4),
                    test_t("if(((1.0 + 2.0) == 3.0) and ((4.0 + 5.0) < 9.0),1,2)",2.0),
                    test_t("(3.0 - 1.0 - 2.0) == ((3.0 - 1.0) - 2.0)",1.0),
                    test_t("true == true",1.0),
                    test_t("false == false",1.0),
                    test_t("true != false",1.0),
                    test_t("false != true",1.0),
                    test_t("(1 < 2) == true",1.0),
                    test_t("(1 > 2) == false",1.0),
                    test_t("true == (1 < 2)",1.0),
                    test_t("false == (1 > 2)",1.0),
                    test_t("(1 > 2) != true",1.0),
                    test_t("(1 < 2) != false",1.0),
                    test_t("true != (1 > 2)",1.0),
                    test_t("false != (1 < 2)",1.0),
                    test_t("(true and true) == true",1.0),
                    test_t("(false and false) == false",1.0),
                    test_t("(true or true) == true",1.0),
                    test_t("(false or false) == false",1.0),
                    test_t("(true and false) == false",1.0),
                    test_t("(false and true) == false",1.0),
                    test_t("(true or false) == true",1.0),
                    test_t("(false or true) == true",1.0),
                    test_t("(true & true) == true",1.0),
                    test_t("(false & false) == false",1.0),
                    test_t("(true | true) == true",1.0),
                    test_t("(false | false) == false",1.0),
                    test_t("(true & false) == false",1.0),
                    test_t("(false & true) == false",1.0),
                    test_t("(true | false) == true",1.0),
                    test_t("(false | true) == true",1.0),
                    test_t("clamp(-1,1,+1)",1.0),
                    test_t("clamp(-1,-1.5,+1.0)",-1.0),
                    test_t("clamp(-1,+1.5,+1.0)",+1.0),
                    test_t("clamp(-1,-1.5,+1.0) + clamp(-1,+1.5,+1.0)",0.0),
                    test_t("inrange(-2,1,+2) == ((-2 <= 1) and (1 <= +2))",1.0),
                    test_t("inrange(-2,1,+2) == if(({-2 <= 1} and [1 <= +2]),1.0,0.0)",1.0),
                    test_t("sgn( 0)", 0.0),
                    test_t("sgn(+3)",+1.0),
                    test_t("sgn(-3)",-1.0),
                    test_t("equal($f00(1.1,2.2,3.3),(1.1+2.2)/3.3)",1.0),
                    test_t("equal($f01(1.1,2.2,3.3),(1.1+2.2)*3.3)",1.0),
                    test_t("equal($f02(1.1,2.2,3.3),(1.1+2.2)-3.3)",1.0),
                    test_t("equal($f03(1.1,2.2,3.3),(1.1+2.2)+3.3)",1.0),
                    test_t("equal($f04(1.1,2.2,3.3),(1.1-2.2)+3.3)",1.0),
                    test_t("equal($f05(1.1,2.2,3.3),(1.1-2.2)/3.3)",1.0),
                    test_t("equal($f06(1.1,2.2,3.3),(1.1-2.2)*3.3)",1.0),
                    test_t("equal($f07(1.1,2.2,3.3),(1.1*2.2)+3.3)",1.0),
                    test_t("equal($f08(1.1,2.2,3.3),(1.1*2.2)-3.3)",1.0),
                    test_t("equal($f09(1.1,2.2,3.3),(1.1*2.2)/3.3)",1.0),
                    test_t("equal($f10(1.1,2.2,3.3),(1.1*2.2)*3.3)",1.0),
                    test_t("equal($f11(1.1,2.2,3.3),(1.1/2.2)+3.3)",1.0),
                    test_t("equal($f12(1.1,2.2,3.3),(1.1/2.2)-3.3)",1.0),
                    test_t("equal($f13(1.1,2.2,3.3),(1.1/2.2)/3.3)",1.0),
                    test_t("equal($f14(1.1,2.2,3.3),(1.1/2.2)*3.3)",1.0),
                    test_t("equal($f15(1.1,2.2,3.3),1.1/(2.2+3.3))",1.0),
                    test_t("equal($f16(1.1,2.2,3.3),1.1/(2.2-3.3))",1.0),
                    test_t("equal($f17(1.1,2.2,3.3),1.1/(2.2*3.3))",1.0),
                    test_t("equal($f18(1.1,2.2,3.3),1.1/(2.2/3.3))",1.0),
                    test_t("equal($f19(1.1,2.2,3.3),1.1*(2.2+3.3))",1.0),
                    test_t("equal($f20(1.1,2.2,3.3),1.1*(2.2-3.3))",1.0),
                    test_t("equal($f21(1.1,2.2,3.3),1.1*(2.2*3.3))",1.0),
                    test_t("equal($f22(1.1,2.2,3.3),1.1*(2.2/3.3))",1.0),
                    test_t("equal($f23(1.1,2.2,3.3),1.1-(2.2+3.3))",1.0),
                    test_t("equal($f24(1.1,2.2,3.3),1.1-(2.2-3.3))",1.0),
                    test_t("equal($f25(1.1,2.2,3.3),1.1-(2.2/3.3))",1.0),
                    test_t("equal($f26(1.1,2.2,3.3),1.1-(2.2*3.3))",1.0),
                    test_t("equal($f27(1.1,2.2,3.3),1.1+(2.2*3.3))",1.0),
                    test_t("equal($f28(1.1,2.2,3.3),1.1+(2.2/3.3))",1.0),
                    test_t("equal($f29(1.1,2.2,3.3),1.1+(2.2+3.3))",1.0),
                    test_t("equal($f30(1.1,2.2,3.3),1.1+(2.2-3.3))",1.0),
                    test_t("equal($f31(1.1,2.2,3.3),1.1*2.2^2+3.3)",1.0),
                    test_t("equal($f32(1.1,2.2,3.3),1.1*2.2^3+3.3)",1.0),
                    test_t("equal($f33(1.1,2.2,3.3),1.1*2.2^4+3.3)",1.0),
                    test_t("equal($f34(1.1,2.2,3.3),1.1*2.2^5+3.3)",1.0),
                    test_t("equal($f35(1.1,2.2,3.3),1.1*2.2^6+3.3)",1.0),
                    test_t("equal($f36(1.1,2.2,3.3),1.1*2.2^7+3.3)",1.0),
                    test_t("equal($f37(1.1,2.2,3.3),1.1*2.2^8+3.3)",1.0),
                    test_t("equal($f38(1.1,2.2,3.3),1.1*2.2^9+3.3)",1.0),
                    test_t("equal($f39(1.1,2.2,3.3),1.1*log(2.2)+3.3)",1.0),
                    test_t("equal($f40(1.1,2.2,3.3),1.1*log(2.2)-3.3)",1.0),
                    test_t("equal($f41(1.1,2.2,3.3),1.1*log10(2.2)+3.3)",1.0),
                    test_t("equal($f42(1.1,2.2,3.3),1.1*log10(2.2)-3.3)",1.0),
                    test_t("equal($f43(1.1,2.2,3.3),1.1*sin(2.2)+3.3)",1.0),
                    test_t("equal($f44(1.1,2.2,3.3),1.1*sin(2.2)-3.3)",1.0),
                    test_t("equal($f45(1.1,2.2,3.3),1.1*cos(2.2)+3.3)",1.0),
                    test_t("equal($f46(1.1,2.2,3.3),1.1*cos(2.2)-3.3)",1.0),
                    test_t("equal($f47(1.1,2.2,3.3),if(0!=1.1,2.2,3.3))",1.0),
                    test_t("equal($f48(1.1,2.2,3.3,4.4),1.1+((2.2+3.3)/4.4))",1.0),
                    test_t("equal($f49(1.1,2.2,3.3,4.4),1.1+((2.2+3.3)*4.4))",1.0),
                    test_t("equal($f50(1.1,2.2,3.3,4.4),1.1+((2.2-3.3)/4.4))",1.0),
                    test_t("equal($f51(1.1,2.2,3.3,4.4),1.1+((2.2-3.3)*4.4))",1.0),
                    test_t("equal($f52(1.1,2.2,3.3,4.4),1.1+((2.2*3.3)/4.4))",1.0),
                    test_t("equal($f53(1.1,2.2,3.3,4.4),1.1+((2.2*3.3)*4.4))",1.0),
                    test_t("equal($f54(1.1,2.2,3.3,4.4),1.1+((2.2/3.3)+4.4))",1.0),
                    test_t("equal($f55(1.1,2.2,3.3,4.4),1.1+((2.2/3.3)/4.4))",1.0),
                    test_t("equal($f56(1.1,2.2,3.3,4.4),1.1+((2.2/3.3)*4.4))",1.0),
                    test_t("equal($f57(1.1,2.2,3.3,4.4),1.1-((2.2+3.3)/4.4))",1.0),
                    test_t("equal($f58(1.1,2.2,3.3,4.4),1.1-((2.2+3.3)*4.4))",1.0),
                    test_t("equal($f59(1.1,2.2,3.3,4.4),1.1-((2.2-3.3)/4.4))",1.0),
                    test_t("equal($f60(1.1,2.2,3.3,4.4),1.1-((2.2-3.3)*4.4))",1.0),
                    test_t("equal($f61(1.1,2.2,3.3,4.4),1.1-((2.2*3.3)/4.4))",1.0),
                    test_t("equal($f62(1.1,2.2,3.3,4.4),1.1-((2.2*3.3)*4.4))",1.0),
                    test_t("equal($f63(1.1,2.2,3.3,4.4),1.1-((2.2/3.3)/4.4))",1.0),
                    test_t("equal($f64(1.1,2.2,3.3,4.4),1.1-((2.2/3.3)*4.4))",1.0),
                    test_t("equal($f65(1.1,2.2,3.3,4.4),((1.1+2.2)*3.3)-4.4)",1.0),
                    test_t("equal($f66(1.1,2.2,3.3,4.4),((1.1-2.2)*3.3)-4.4)",1.0),
                    test_t("equal($f67(1.1,2.2,3.3,4.4),((1.1*2.2)*3.3)-4.4)",1.0),
                    test_t("equal($f68(1.1,2.2,3.3,4.4),((1.1/2.2)*3.3)-4.4)",1.0),
                    test_t("equal($f69(1.1,2.2,3.3,4.4),((1.1+2.2)/3.3)-4.4)",1.0),
                    test_t("equal($f70(1.1,2.2,3.3,4.4),((1.1-2.2)/3.3)-4.4)",1.0),
                    test_t("equal($f71(1.1,2.2,3.3,4.4),((1.1*2.2)/3.3)-4.4)",1.0),
                    test_t("equal($f72(1.1,2.2,3.3,4.4),((1.1/2.2)/3.3)-4.4)",1.0),
                    test_t("equal($f73(1.1,2.2,3.3,4.4),(1.1*2.2)+(3.3*4.4))",1.0),
                    test_t("equal($f74(1.1,2.2,3.3,4.4),(1.1*2.2)-(3.3*4.4))",1.0),
                    test_t("equal($f75(1.1,2.2,3.3,4.4),(1.1*2.2)+(3.3/4.4))",1.0),
                    test_t("equal($f76(1.1,2.2,3.3,4.4),(1.1*2.2)-(3.3/4.4))",1.0),
                    test_t("equal($f77(1.1,2.2,3.3,4.4),(1.1/2.2)+(3.3/4.4))",1.0),
                    test_t("equal($f78(1.1,2.2,3.3,4.4),(1.1/2.2)-(3.3/4.4))",1.0),
                    test_t("equal($f79(1.1,2.2,3.3,4.4),(1.1/2.2)-(3.3*4.4))",1.0),
                    test_t("equal($f80(1.1,2.2,3.3,4.4),1.1/(2.2+(3.3*4.4)))",1.0),
                    test_t("equal($f81(1.1,2.2,3.3,4.4),1.1/(2.2-(3.3*4.4)))",1.0),
                    test_t("equal($f82(1.1,2.2,3.3,4.4),1.1*(2.2+(3.3*4.4)))",1.0),
                    test_t("equal($f83(1.1,2.2,3.3,4.4),1.1*(2.2-(3.3*4.4)))",1.0),
                    test_t("equal($f84(1.1,2.2,3.3,4.4),1.1*2.2^2+3.3*4.4^2)",1.0),
                    test_t("equal($f85(1.1,2.2,3.3,4.4),1.1*2.2^3+3.3*4.4^3)",1.0),
                    test_t("equal($f86(1.1,2.2,3.3,4.4),1.1*2.2^4+3.3*4.4^4)",1.0),
                    test_t("equal($f87(1.1,2.2,3.3,4.4),1.1*2.2^5+3.3*4.4^5)",1.0),
                    test_t("equal($f88(1.1,2.2,3.3,4.4),1.1*2.2^6+3.3*4.4^6)",1.0),
                    test_t("equal($f89(1.1,2.2,3.3,4.4),1.1*2.2^7+3.3*4.4^7)",1.0),
                    test_t("equal($f90(1.1,2.2,3.3,4.4),1.1*2.2^8+3.3*4.4^8)",1.0),
                    test_t("equal($f91(1.1,2.2,3.3,4.4),1.1*2.2^9+3.3*4.4^9)",1.0),
                    test_t("equal($f92(1.1,2.2,3.3,4.4),if(1.1 and 2.2,3.3,4.4))",1.0),
                    test_t("equal($f93(1.1,2.2,3.3,4.4),if(1.1 or 2.2,3.3,4.4))",1.0),
                    test_t("equal($f94(1.1,2.2,3.3,4.4),if(1.1 < 2.2,3.3,4.4))",1.0),
                    test_t("equal($f95(1.1,2.2,3.3,4.4),if(1.1 <= 2.2,3.3,4.4))",1.0),
                    test_t("equal($f96(1.1,2.2,3.3,4.4),if(1.1 > 2.2,3.3,4.4))",1.0),
                    test_t("equal($f97(1.1,2.2,3.3,4.4),if(1.1 >= 2.2,3.3,4.4))",1.0),
                    test_t("equal($f98(1.1,2.2,3.3,4.4),if(equal(1.1,2.2),3.3,4.4))",1.0),
                    test_t("equal($f99(1.1,2.2,3.3,4.4),1.1*sin(2.2)+3.3*cos(4.4))",1.0),
                    test_t("equal((48.0/2.0*(9.0+3.0)),288.0)",1.0),
                    test_t("equal((48.0/2.0(9.0+3.0)),288.0)",1.0),
                    test_t("equal((6.0/2.0(1.0+2.0)),9.0)",1.0),
                    test_t("1+2+3+4+5+6+7+8+9+0",45.0),
                    test_t("1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 0",45.0),
                    test_t("1.0 + 2.0 + 3.0 + 4.0 + 5.0 + 6.0 + 7.0 + 8.0 + 9.0 + 0.0",45.0),
                    test_t("(1+2)+(3+4)+(5+6)+(7+8)+(9+0)",45.0),
                    test_t("(1-2)+(3-4)+(5-6)+(7-8)+(9-0)",+5.0),
                    test_t("(1+2)-(3+4)-(5+6)-(7+8)-(9+0)",-39.0),
                    test_t("(1.0+2.0)+(3.0+4.0)+(5.0+6.0)+(7.0+8.0)+(9.0+0.0)",45.0),
                    test_t("(1.0-2.0)+(3.0-4.0)+(5.0-6.0)+(7.0-8.0)+(9.0-0.0)",+5.0),
                    test_t("(1.0+2.0)-(3.0+4.0)-(5.0+6.0)-(7.0+8.0)-(9.0+0.0)",-39.0),
                    test_t("[(1.0+2.0)+[3.0+4.0]+(5.0+6.0)]+([7.0+8.0]+(9.0+0.0))",45.0),
                    test_t("([1.0-2.0]+(3.0-4.0)+[5.0-6.0])+[(7.0-8.0)+[9.0-0.0]]",+5.0),
                    test_t("((1.0+2.0))-[(3.0+4.0)]-((5.0+6.0))-[(7.0+8.0)]-((9.0+0.0))",-39.0),
                    test_t("{[(1.0+2.0)+[3.0+4.0]+({5.0+6.0})]}+({[7.0+8.0]+(9.0+0.0)})",45.0),
                    test_t("{([1.0-2.0]+(3.0-4.0)+[5.0-6.0])}+[({+7.0}-{+8.0})+[{+9.0-0.0}]]",+5.0),
                    test_t("((+1.0+2.0))-[({+3.0+4.0})]-(({+5.0+6.0}))-[({+7.0}+8.0)]-(({+9.0}+{0.0}))",-39.0),
                    test_t("1+2-3*4/5+6-7*8/9+0",0.37777777777777777778),
                    test_t("1.1+2.2-3.3*4.4/5.5+6.6-7.7*8.8/9.9+0.0",0.41555555555555555556),
                    test_t("(1+2)-(3*4)/(5+6)-(7*8)/(9+0)",-4.31313131313131313131),
                    test_t("1/1+1/2+1/3+1/4+1/5+1/6+1/7+1/8+1/9",2.82896825396825396825),
                    test_t("(1/1)+(1/2)+(1/3)+(1/4)+(1/5)+(1/6)+(1/7)+(1/8)+(1/9)",2.82896825396825396825),
                    test_t("1.0/1.0+1.0/2.0+1.0/3.0+1.0/4.0+1.0/5.0+1.0/6.0+1.0/7.0+1.0/8.0+1.0/9",2.82896825396825396825),
                    test_t("(1.0/1.0)+(1.0/2.0)+(1.0/3.0)+(1.0/4.0)+(1.0/5.0)+(1.0/6.0)+(1.0/7.0)+(1.0/8.0)+(1.0/9)",2.82896825396825396825),
                    test_t("1/1*1/2*1/3*1/4*1/5*1/6*1/7*1/8*1/9",0.00000275573192239859),
                    test_t("(1/1)*(1/2)*(1/3)*(1/4)*(1/5)*(1/6)*(1/7)*(1/8)*(1/9)",0.00000275573192239859),
                    test_t("1.0/1.0*1.0/2.0*1.0/3.0*1.0/4.0*1.0/5.0*1.0/6.0*1.0/7.0*1.0/8.0*1.0/9",0.00000275573192239859),
                    test_t("(1.0/1.0)*(1.0/2.0)*(1.0/3.0)*(1.0/4.0)*(1.0/5.0)*(1.0/6.0)*(1.0/7.0)*(1.0/8.0)*(1.0/9)",0.00000275573192239859),
                    test_t("equal(poly01(1.2345,2.2,1.1),(2.2*1.2345^1+1.1))",1.0),
                    test_t("equal(poly02(1.2345,3.3,2.2,1.1),(3.3*1.2345^2+2.2*1.2345^1+1.1))",1.0),
                    test_t("equal(poly03(1.2345,4.4,3.3,2.2,1.1),(4.4*1.2345^3+3.3*1.2345^2+2.2*1.2345^1+1.1))",1.0),
                    test_t("equal(poly04(1.2345,5.5,4.4,3.3,2.2,1.1),(5.5*1.2345^4+4.4*1.2345^3+3.3*1.2345^2+2.2*1.2345^1+1.1))",1.0),
                    test_t("equal(poly05(1.2345,6.6,5.5,4.4,3.3,2.2,1.1),(6.6*1.2345^5+5.5*1.2345^4+4.4*1.2345^3+3.3*1.2345^2+2.2*1.2345^1+1.1))",1.0),
                    test_t("equal(poly06(1.2345,7.7,6.6,5.5,4.4,3.3,2.2,1.1),(7.7*1.2345^6+6.6*1.2345^5+5.5*1.2345^4+4.4*1.2345^3+3.3*1.2345^2+2.2*1.2345^1+1.1))",1.0),
                    test_t("equal(poly07(1.2345,8.8,7.7,6.6,5.5,4.4,3.3,2.2,1.1),(8.8*1.2345^7+7.7*1.2345^6+6.6*1.2345^5+5.5*1.2345^4+4.4*1.2345^3+3.3*1.2345^2+2.2*1.2345^1+1.1))",1.0),
                    test_t("equal(poly08(1.2345,9.9,8.8,7.7,6.6,5.5,4.4,3.3,2.2,1.1),(9.9*1.2345^8+8.8*1.2345^7+7.7*1.2345^6+6.6*1.2345^5+5.5*1.2345^4+4.4*1.2345^3+3.3*1.2345^2+2.2*1.2345^1+1.1))",1.0),
                    test_t("equal(poly09(1.2345,1.1,9.9,8.8,7.7,6.6,5.5,4.4,3.3,2.2,1.1),(1.1*1.2345^9+9.9*1.2345^8+8.8*1.2345^7+7.7*1.2345^6+6.6*1.2345^5+5.5*1.2345^4+4.4*1.2345^3+3.3*1.2345^2+2.2*1.2345^1+1.1))",1.0),
                    test_t("equal(poly10(1.37,2.2,1.1,9.9,8.8,7.7,6.6,5.5,4.4,3.3,2.2,1.1),(2.2*1.37^10+1.1*1.37^9+9.9*1.37^8+8.8*1.37^7+7.7*1.37^6+6.6*1.37^5+5.5*1.37^4+4.4*1.37^3+3.3*1.37^2+2.2*1.37^1+1.1))",1.0),
                    test_t("equal(poly11(1.37,3.3,2.2,1.1,9.9,8.8,7.7,6.6,5.5,4.4,3.3,2.2,1.1),(3.3*1.37^11+2.2*1.37^10+1.1*1.37^9+9.9*1.37^8+8.8*1.37^7+7.7*1.37^6+6.6*1.37^5+5.5*1.37^4+4.4*1.37^3+3.3*1.37^2+2.2*1.37^1+1.1))",1.0),
                    test_t("equal(poly12(1.37,4.4,3.3,2.2,1.1,9.9,8.8,7.7,6.6,5.5,4.4,3.3,2.2,1.1),(4.4*1.37^12+3.3*1.37^11+2.2*1.37^10+1.1*1.37^9+9.9*1.37^8+8.8*1.37^7+7.7*1.37^6+6.6*1.37^5+5.5*1.37^4+4.4*1.37^3+3.3*1.37^2+2.2*1.37^1+1.1))",1.0),
                    test_t("equal(\t \n(\n \r1.1\t\t - \n\n 2.2\n\n/\r3.3\t),(1.1-2.2/3.3))",1.0),
                    test_t("equal((pi^2^3),(pi^8))",1.0),
                    test_t("equal((pi^(2^3)),(pi^8))",1.0),
                    test_t("equal(pi^2^3-pi^8,0)",1.0),
                    test_t("equal((2*pi^2^3),2*(pi^8))",1.0),
                    test_t("equal((pi^2^3*2),2*(pi^8))",1.0),
                    test_t("equal((pi^2^3/2),(pi^8)/2)",1.0),
                    test_t("equal((pi^2.2^3.3),(pi^13.4894687605338489))",1.0),
                    test_t("equal((pi^(2.2^3.3)),(pi^13.4894687605338489))",1.0),
                    test_t("equal((2.2*pi^2.2^3.3),2.2*(pi^13.4894687605338489))",1.0),
                    test_t("equal((pi^2.2^3.3*2),2*(pi^13.4894687605338489))",1.0),
                    test_t("equal((pi^2.2^3.3/2.2),(pi^13.4894687605338489)/2.2)",1.0),
                    test_t("equal((pi^-2^3),1/(pi^8))",1.0),
                    test_t("equal((pi^(-2^3)),1/(pi^8))",1.0),
                    test_t("equal((pi^2^-3),(pi^(1/8)))",1.0),
                    test_t("equal((pi^(2^-3)),(pi^(1/8)))",1.0),
                    test_t("equal((pi^-2^-3),1/(pi^(1/8)))",1.0),
                    test_t("equal((pi^(-2^-3)),1/(pi^(1/8)))",1.0),
                    test_t("equal((-pi^2^3),(-pi^8))",1.0),
                    test_t("equal((-pi^(2^3)),(-pi^8))",1.0),
                    test_t("equal(-pi^2^3--pi^8,0)",1.0),
                    test_t("equal((2*-pi^2^3),2*(-pi^8))",1.0),
                    test_t("equal((-pi^2^3*2),2*(-pi^8))",1.0),
                    test_t("equal((-pi^2^3/2),(-pi^8)/2)",1.0),
                    test_t("equal((-pi^2.2^3.3),(-pi^13.4894687605338489))",1.0),
                    test_t("equal((-pi^(2.2^3.3)),(-pi^13.4894687605338489))",1.0),
                    test_t("equal((2.2*-pi^2.2^3.3),2.2*(-pi^13.4894687605338489))",1.0),
                    test_t("equal((-pi^2.2^3.3*2),2*(-pi^13.4894687605338489))",1.0),
                    test_t("equal((-pi^2.2^3.3/2.2),(-pi^13.4894687605338489)/2.2)",1.0),
                    test_t("equal((-pi^-2^3),1/(-pi^8))",1.0),
                    test_t("equal((-pi^(-2^3)),1/(-pi^8))",1.0),
                    test_t("equal((-pi^2^-3),(-pi^(1/8)))",1.0),
                    test_t("equal((-pi^(2^-3)),(-pi^(1/8)))",1.0),
                    test_t("equal((-pi^-2^-3),1/(-pi^(1/8)))",1.0),
                    test_t("equal((-pi^(-2^-3)),1/(-pi^(1/8)))",1.0),
                    test_t("equal((+pi^+2^+3),(+pi^+8))",1.0),
                    test_t("equal((+pi^(2^3)),(+pi^+8))",1.0),
                    test_t("equal(+pi^+2^+3-+pi^+8,0)",1.0),
                    test_t("equal((+2*+pi^+2^+3),+2*(+pi^+8))",1.0),
                    test_t("equal((+pi^+2^+3*+2),+2*(+pi^+8))",1.0),
                    test_t("equal((+pi^+2^+3/+2),(+pi^+8)/+2)",1.0),
                    test_t("equal((+pi^+2.2^+3.3),(+pi^+13.4894687605338489))",1.0),
                    test_t("equal((+pi^(+2.2^+3.3)),(+pi^+13.4894687605338489))",1.0),
                    test_t("equal((+2.2*+pi^+2.2^+3.3),+2.2*(+pi^+13.4894687605338489))",1.0),
                    test_t("equal((+pi^+2.2^+3.3*+2),+2*(+pi^+13.4894687605338489))",1.0),
                    test_t("equal((+pi^+2.2^+3.3/+2.2),(+pi^+13.4894687605338489)/+2.2)",1.0),
                    test_t("equal((+pi^-2^3),1/(+pi^+8))",1.0),
                    test_t("equal((+pi^(-2^3)),1/(+pi^+8))",1.0),
                    test_t("equal((+pi^2^-3),(+pi^(+1/+8)))",1.0),
                    test_t("equal((+pi^(2^-3)),(+pi^(+1/+8)))",1.0),
                    test_t("equal((+pi^-2^-3),1/(+pi^(+1/+8)))",1.0),
                    test_t("equal((+pi^(-2^-3)),1/(+pi^(+1/+8)))",1.0),
                    test_t("equal((-pi^+2^+3),(-pi^+8))",1.0),
                    test_t("equal((-pi^(2^3)),(-pi^+8))",1.0),
                    test_t("equal(-pi^+2^+3--pi^+8,0)",1.0),
                    test_t("equal((+2*-pi^+2^+3),2*(-pi^+8))",1.0),
                    test_t("equal((-pi^+2^+3*2),2*(-pi^+8))",1.0),
                    test_t("equal((-pi^+2^+3/+2),(-pi^+8)/+2)",1.0),
                    test_t("equal((-pi^+2.2^+3.3),(-pi^+13.4894687605338489))",1.0),
                    test_t("equal((-pi^(2.2^3.3)),(-pi^+13.4894687605338489))",1.0),
                    test_t("equal((+2.2*-pi^+2.2^+3.3),2.2*(-pi^+13.4894687605338489))",1.0),
                    test_t("equal((-pi^+2.2^+3.3*2),2*(-pi^+13.4894687605338489))",1.0),
                    test_t("equal((-pi^+2.2^+3.3/+2.2),(-pi^+13.4894687605338489)/+2.2)",1.0),
                    test_t("equal((-pi^-2^3),1/(-pi^+8))",1.0),
                    test_t("equal((-pi^(-2^3)),1/(-pi^+8))",1.0),
                    test_t("equal((-pi^2^-3),(-pi^(+1/+8)))",1.0),
                    test_t("equal((-pi^(2^-3)),(-pi^(+1/+8)))",1.0),
                    test_t("equal((-pi^-2^-3),1/(-pi^(+1/+8)))",1.0),
                    test_t("equal((-pi^(-2^-3)),1/(-pi^(+1/+8)))",1.0),
                    test_t("switch { case (1 <= 2) : 1; default: 1.12345; }",1.0),
                    test_t("switch { case (1 >  2) : 0; case (1 <= 2) : 1; default: 1.12345; }",1.0),
                    test_t("switch { case (1 <= 2) : switch { case (1 <= 2) : 1; default: 1.12345; }; default: 1.12345; }",1.0),
                    test_t("switch { case [1 <= 2] : 1; default: 1.12345; }",1.0),
                    test_t("switch { case [1 >  2] : 0; case [1 <= 2] : 1; default: 1.12345; }",1.0),
                    test_t("switch { case [1 <= 2] : switch { case [1 <= 2] : 1; default: 1.12345; }; default: 1.12345; }",1.0),
                    test_t("switch { case {1 <= 2} : 1; default: 1.12345; }",1.0),
                    test_t("switch { case {1 >  2} : 0; case {1 <= 2} : 1; default: 1.12345; }",1.0),
                    test_t("switch { case {1 <= 2} : switch { case {1 <= 2} : 1; default: 1.12345; }; default: 1.12345; }",1.0),
                    test_t("switch { case [(1 <= 2)] : {1}; default: 1.12345; }",1.0),
                    test_t("switch { case ([1 >  2]) : [0]; case ([1 <= 2]) : 1; default: 1.12345; }",1.0),
                    test_t("switch { case {(1 <= 2)} : switch { case ({1 <= 2}) : 1; default: 1.12345; }; default: 1.12345; }",1.0),
                    test_t("switch { case 1 > 1 : 1; case 2 > 2 : 2; case 3 = 3 : 3; case 4 > 4 : 4; default : 5; }",3.0),
                    test_t("repeat 1.1 + 2.2 until (1 < 2)",3.3),
                    test_t("repeat (1.1 + 2.2) until (1 < 2)",3.3),
                    test_t("repeat 1.1 + 2.2; until (1 < 2)",3.3),
                    test_t("repeat (1.1 + 2.2); until (1 < 2)",3.3),
                    test_t("repeat 1.1234; 1 < 2; 1.1 + 2.2 until (1 < 2)",3.3),
                    test_t("repeat 1.1234; 1 < 2; (1.1 + 2.2) until (1 < 2)",3.3),
                    test_t("repeat 1.1234; 1 < 2; 1.1 + 2.2; until (1 < 2)",3.3),
                    test_t("repeat 1.1234; 1 < 2; (1.1 + 2.2); until (1 < 2)",3.3),
                    test_t("[*] { case 1 < 2 : 1 / 2; case (1 < 3) : 2 / 2; case 1 < 4 : 3 / 2; case (1 < 5) : 4 / 2; }",2.0),
                    test_t(" 0 ? 1 : 2",2.0),
                    test_t(" 1 ? 3 : 4",3.0),
                    test_t("(0 ? 1 : 2) == 2",1.0),
                    test_t("(1 ? 3 : 4) == 3",1.0),
                    test_t("[(0)] ? [(1)] : [(2)]",2.0),
                    test_t("([(0)] ? [(1)] : [(2)]) == 2",1.0),
                    test_t("([(1)] ? [(3)] : [(4)]) == 3",1.0),
                    test_t("(1 < 2 ? 3 : 4) == 3",1.0),
                    test_t("(1 > 2 ? 3 : 4) == 4",1.0),
                    test_t("(1 < 2 ? 3 + 5 : 4) == 8",1.0),
                    test_t("(1 > 2 ? 3 : 4 + 5) == 9",1.0),
                    test_t("(2 < 3 + 3 ? 7 : 9) == 7",1.0),
                    test_t("(1 + 1 < 3 ? 7 : 9) == 7",1.0),
                    test_t("(1 + 1 < 3 + 3 ? 7 : 9) == 7",1.0),
                    test_t("(2 > 3 + 3 ? 7 : 9) == 9",1.0),
                    test_t("(1 + 1 > 3 ? 7 : 9) == 9",1.0),
                    test_t("(1 + 1 > 3 + 3 ? 7 : 9) == 9",1.0),
                    test_t("(2 < (3 + 3) ? 7 : 9) == 7",1.0),
                    test_t("((1 + 1) < 3 ? 7 : 9) == 7",1.0),
                    test_t("((1 + 1) < (3 + 3) ? 7 : 9) == 7",1.0),
                    test_t("(min(1,2) ? 1 + 3 : 1 + 4) == 4",1.0),
                    test_t("(min(0,1) ? 1 + 3 : 1 + 4) == 5",1.0),
                    test_t("if (1 < 2) 3; == 3",1.0),
                    test_t("if (1 > 2) 3; == null",1.0),
                    test_t("if (1 < 2) 3; else 4; == 3",1.0),
                    test_t("if (1 > 2) 3; else 4; == 4",1.0),
                    test_t("if (1 < 2) 3; else {1+2; 4;} == 3",1.0),
                    test_t("if (1 > 2) 3; else {1+2; 4;} == 4",1.0),
                    test_t("if (1 < 2) 3; else if (1 < 2) 4; == 3",1.0),
                    test_t("if (1 > 2) 3; else if (1 < 2) 4; == 4",1.0),
                    test_t("if (1 > 2) 3; else if (1 > 2) 4; == null",1.0),
                    test_t("if (1 < 2) 3; else if (1 < 2) {1+2; 4;} == 3",1.0),
                    test_t("if (1 > 2) 3; else if (1 < 2) {1+2; 4;} == 4",1.0),
                    test_t("if (1 > 2) 3; else if (1 > 2) {1+2; 4;} == null",1.0),
                    test_t("if (1 < 2) { 1+2; 3;} == 3",1.0),
                    test_t("if (1 > 2) { 1+2; 3;} == null",1.0),
                    test_t("if (1 < 2) { 1+2; 3;} else 4; == 3",1.0),
                    test_t("if (1 > 2) { 1+2; 3;} else 4; == 4",1.0),
                    test_t("if (1 < 2) { 1+2; 3;} else {1+2; 4;} == 3",1.0),
                    test_t("if (1 > 2) { 1+2; 3;} else {1+2; 4;} == 4",1.0),
                    test_t("if (1 < 2) { 1+2; 3;} else if (1 < 2) 4; == 3",1.0),
                    test_t("if (1 > 2) { 1+2; 3;} else if (1 < 2) 4; == 4",1.0),
                    test_t("if (1 > 2) { 1+2; 3;} else if (1 > 2) 4; == null",1.0),
                    test_t("if (1 < 2) { 1+2; 3;} else if (1 < 2) {1+2; 4;} == 3",1.0),
                    test_t("if (1 > 2) { 1+2; 3;} else if (1 < 2) {1+2; 4;} == 4",1.0),
                    test_t("if (1 > 2) { 1+2; 3;} else if (1 > 2) {1+2; 4;} == null",1.0)
                  };

static const std::size_t global_test_list_size = sizeof(global_test_list) / sizeof(test_t);

template <typename T>
inline bool not_equal_impl(const T& t1,
                           const T& t2,
                           const T& epsilon = 0.0000000001/*std::numeric_limits<T>::epsilon()*/)
{
   if (t1 != t1) return true;
   if (t2 != t2) return true;
   T diff = std::abs(t1 - t2);
   T eps_norm = (std::max(T(1),std::max(std::abs(t1),std::abs(t2))) * epsilon);
   return diff > eps_norm;
}

template <typename T>
inline bool not_equal(const T& t0, const T& t1,
                      const T& epsilon = T(0.0000000001))
{
   return not_equal_impl(t0,t1,epsilon);
}

inline bool not_equal(const float& t0, const float& t1, const float& epsilon = 0.000001f)
{
   return not_equal_impl(t0,t1,epsilon);
}

template <typename T>
inline bool test_expression(const std::string& expression_string, const T& expected_result)
{
   exprtk::symbol_table<T> symbol_table;
   symbol_table.add_constants();

   exprtk::polynomial<T, 1> poly01;
   exprtk::polynomial<T, 2> poly02;
   exprtk::polynomial<T, 3> poly03;
   exprtk::polynomial<T, 4> poly04;
   exprtk::polynomial<T, 5> poly05;
   exprtk::polynomial<T, 6> poly06;
   exprtk::polynomial<T, 7> poly07;
   exprtk::polynomial<T, 8> poly08;
   exprtk::polynomial<T, 9> poly09;
   exprtk::polynomial<T,10> poly10;
   exprtk::polynomial<T,11> poly11;
   exprtk::polynomial<T,12> poly12;

   symbol_table.add_function("poly01", poly01);
   symbol_table.add_function("poly02", poly02);
   symbol_table.add_function("poly03", poly03);
   symbol_table.add_function("poly04", poly04);
   symbol_table.add_function("poly05", poly05);
   symbol_table.add_function("poly06", poly06);
   symbol_table.add_function("poly07", poly07);
   symbol_table.add_function("poly08", poly08);
   symbol_table.add_function("poly09", poly09);
   symbol_table.add_function("poly10", poly10);
   symbol_table.add_function("poly11", poly11);
   symbol_table.add_function("poly12", poly12);

   exprtk::expression<T> expression;
   expression.register_symbol_table(symbol_table);

   {
      exprtk::parser<T> parser;

      if (!parser.compile(expression_string,expression))
      {
         printf("test_expression() - Error: %s   Expression: %s\n",
                parser.error().c_str(),
                expression_string.c_str());

         return false;
      }
   }

   if (!exprtk::expression_helper<T>::is_constant(expression))
   {
      printf("test_expression() - Error: Expression did not compile to a constant!   Expression: %s\n",
             expression_string.c_str());

      return false;
   }

   T result = expression.value();

   if (not_equal(result,expected_result))
   {
      printf("test_expression() - Computation Error:  Expression: [%s]\tExpected: %19.15f\tResult: %19.15f\n",
             expression_string.c_str(),
             (double)expected_result,
             (double)result);

      return false;
   }

   return true;
}

template <typename T>
inline bool run_test00()
{
   const std::size_t rounds = 10;
   for (std::size_t r = 0; r < rounds; ++r)
   {
      bool result = true;
      for (std::size_t i = 0; i < global_test_list_size; ++i)
      {
         if (!test_expression<T>(global_test_list[i].first,T(global_test_list[i].second)))
         {
            result = false;
         }
      }

      if (!result)
      {
         return false;
      }
   }

   return true;
}

template <typename T>
struct test_xy
{
   test_xy(const std::string& e, const T& v0, const T& v1, const T& r)
   : expr(e),
     x(v0),
     y(v1),
     result(r)
   {}

   std::string expr;
   T x;
   T y;
   T result;
};

template <typename T>
struct test_xyzw
{
   test_xyzw(const std::string& e, const T& v0, const T& v1, const T& v2, const T& v3, const T& r)
   : expr(e),
     x(v0),
     y(v1),
     z(v2),
     w(v3),
     result(r)
   {}

   std::string expr;
   T x;
   T y;
   T z;
   T w;
   T result;
};

template <typename T>
inline bool run_test01()
{
   {
      static const test_xy<T> test_list[] =
                              {
                                test_xy<T>("x + y"             ,T(2.2),T(3.3),T(5.5  )),
                                test_xy<T>("x - y"             ,T(3.3),T(2.2),T(1.1  )),
                                test_xy<T>("x * y"             ,T(3.3),T(2.2),T(7.26 )),
                                test_xy<T>("x / y"             ,T(3.3),T(2.2),T(1.5  )),
                                test_xy<T>("(x + y) * (x + y)" ,T(2.2),T(3.3),T(30.25)),
                                test_xy<T>("(x + y) / (x + y)" ,T(2.2),T(3.3),T(1.0  )),
                                test_xy<T>("x + y > x and  x + y > y" ,T(2.2),T(3.3),T(1.0)),
                                test_xy<T>("1 + (x + y)"       ,T(2.2),T(3.3),T(6.5  )),
                                test_xy<T>("(x + y) - 1"       ,T(2.2),T(3.3),T(4.5  )),
                                test_xy<T>("1 + (x + y) * 2"   ,T(2.2),T(3.3),T(12.0  )),
                                test_xy<T>("2 * (x + y) - 1"   ,T(2.2),T(3.3),T(10.0  )),
                                test_xy<T>("y + (x + 1)"       ,T(2.2),T(3.3),T(6.5  )),
                                test_xy<T>("(x + 1) + y"       ,T(2.2),T(3.3),T(6.5  )),
                                test_xy<T>("2 * x"  ,T(2.2),T(0.0),T(4.4)),
                                test_xy<T>("x * 2"  ,T(2.2),T(0.0),T(4.4)),
                                test_xy<T>("1.1 + x",T(2.2),T(0.0),T(3.3)),
                                test_xy<T>("x + 1.1",T(2.2),T(0.0),T(3.3)),
                                test_xy<T>("x * 1 == x"    ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("1 * x == x"    ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("y * 1 == y"    ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("1 * y == y"    ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("x * 0 == 0"    ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("0 * x == 0"    ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("y * 0 == 0"    ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("0 * y == 0"    ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("x + 1 == 1 + x",T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("y + 1 == 1 + y",T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("x + y == y + x",T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("x * y == y * x",T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("x < y"         ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("y > x"         ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("x <= y"        ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("y >= x"        ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("x + y > y"     ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("x + y > x"     ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("x * y > y"     ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("x * y > x"     ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("(x + y) > y"   ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("(x + y) > x"   ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("(x * y) > y"   ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("(x * y) > x"   ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("(2x + 3y)  == (2*x + 3*y)" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("2(x +  y)  == (2*x + 2*y)" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>(" (x +  y)3 == (3*x + 3*y)" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("2x + 3y    ==   2*x + 3*y" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("2(x +  y)  ==   2*x + 2*y" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>(" (x +  y)3 ==   3*x + 3*y" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>(" (x)y    == (x*y)" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>(" x(y)    == (x*y)" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>(" (x) y   == (x*y)" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>(" x (y)   == (x*y)" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>(" ((x) y) == (x*y)" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>(" (x (y)) == (x*y)" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>(" (x)3    == (x*3)" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>(" x(3)    == (x*3)" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>(" (x) 3   == (x*3)" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>(" x (3)   == (x*3)" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>(" ((x) 3) == (x*3)" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>(" (x (3)) == (x*3)" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>(" (2)y    == (2*y)" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>(" 2(y)    == (2*y)" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>(" (2) y   == (2*y)" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>(" 2 (y)   == (2*y)" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>(" ((2) y) == (2*y)" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>(" (2 (y)) == (2*y)" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("var a := 2; (a)(3) == 6" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("var a := 2; (A){3} == 6" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("var a := 2; (a)[3] == 6" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("var a := 2; {a}(3) == 6" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("var a := 2; {a}{3} == 6" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("var a := 2; {a}[3] == 6" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("var a := 2; var b := 3; (a)(b) == 6" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("var a := 2; var b := 3; (a){B} == 6" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("var a := 2; var b := 3; (a)[b] == 6" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("var a := 2; var b := 3; {a}(b) == 6" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("var a := 2; var b := 3; {a}{b} == 6" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("var a := 2; var b := 3; {a}[b] == 6" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("var a := 2; (a)(a+1) == 6" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("var a := 2; (a){a+1} == 6" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("var a := 2; (a)[a+1] == 6" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("var a := 2; {a}(a+1) == 6" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("var a := 2; {a}{a+1} == 6" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("var a := 2; {a}[a+1] == 6" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("var a := 2; var b := 3; (b-1)(b) == 6" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("var a := 2; var b := 3; (b-1){b} == 6" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("var a := 2; var b := 3; (b-1)[b] == 6" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("var a := 2; var b := 3; {b-1}(b) == 6" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("var a := 2; var b := 3; {b-1}{b} == 6" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("var a := 2; var b := 3; {b-1}[b] == 6" ,T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("equal(x^2.2^1.1,17.15193942371376191362)" ,T(3.3),T(0.0),T(1.0)),
                                test_xy<T>("equal(3.3^x^1.1,17.15193942371376191362)" ,T(2.2),T(0.0),T(1.0)),
                                test_xy<T>("equal(3.3^2.2^x,17.15193942371376191362)" ,T(1.1),T(0.0),T(1.0)),
                                test_xy<T>("equal(x^2.2^y,17.15193942371376191362)" ,T(3.3),T(1.1),T(1.0)),
                                test_xy<T>("equal(x^y^1.1,17.15193942371376191362)" ,T(3.3),T(2.2),T(1.0)),
                                test_xy<T>("equal(3.3^x^y,17.15193942371376191362)" ,T(2.2),T(1.1),T(1.0)),
                                test_xy<T>("equal(x+y^3/7,x+(y*y*y)/7)",T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("equal(1-x^3+y^2*7,1-(x*x*x)+(y*y)*7)",T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("equal( x^0,1)",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal( x^1,x)",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal( x^2,x*x)",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal( x^3,x*x*x)",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal( x^4,x*x*x*x)",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal( x^5,x*x*x*x*x)",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal( x^6,x*x*x*x*x*x)",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal( x^7,x*x*x*x*x*x*x)",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal( x^8,x*x*x*x*x*x*x*x)",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal( x^9,x*x*x*x*x*x*x*x*x)",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal(x^10,x*x*x*x*x*x*x*x*x*x)",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal(x^11,x*x*x*x*x*x*x*x*x*x*x)",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal(x^12,x*x*x*x*x*x*x*x*x*x*x*x)",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal(x^13,x*x*x*x*x*x*x*x*x*x*x*x*x)",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal(x^14,x*x*x*x*x*x*x*x*x*x*x*x*x*x)",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal(x^15,x*x*x*x*x*x*x*x*x*x*x*x*x*x*x)",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal(x^16,x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x)",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal(x^17,x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x)",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal(x^18,x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x)",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal(x^19,x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x)",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal(x^20,x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x)",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal(x^21,x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x)",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal(x^22,x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x)",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal(x^23,x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x)",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal(x^24,x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x)",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal(x^25,x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x)",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal( y^0,1)",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal( y^1,y)",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal( y^2,y*y)",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal( y^3,y*y*y)",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal( y^4,y*y*y*y)",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal( y^5,y*y*y*y*y)",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal( y^6,y*y*y*y*y*y)",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal( y^7,y*y*y*y*y*y*y)",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal( y^8,y*y*y*y*y*y*y*y)",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal( y^9,y*y*y*y*y*y*y*y*y)",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal(y^10,y*y*y*y*y*y*y*y*y*y)",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal(y^11,y*y*y*y*y*y*y*y*y*y*y)",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal(y^12,y*y*y*y*y*y*y*y*y*y*y*y)",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal(y^13,y*y*y*y*y*y*y*y*y*y*y*y*y)",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal(y^14,y*y*y*y*y*y*y*y*y*y*y*y*y*y)",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal(y^15,y*y*y*y*y*y*y*y*y*y*y*y*y*y*y)",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal(y^16,y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y)",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal(y^17,y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y)",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal(y^18,y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y)",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal(y^19,y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y)",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal(y^20,y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y)",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal(y^21,y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y)",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal(y^22,y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y)",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal(y^23,y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y)",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal(y^24,y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y)",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal(y^25,y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y)",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal( x^-0,1/1)",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal( x^-1,1/(x))",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal( x^-2,1/(x*x))",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal( x^-3,1/(x*x*x))",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal( x^-4,1/(x*x*x*x))",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal( x^-5,1/(x*x*x*x*x))",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal( x^-6,1/(x*x*x*x*x*x))",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal( x^-7,1/(x*x*x*x*x*x*x))",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal( x^-8,1/(x*x*x*x*x*x*x*x))",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal( x^-9,1/(x*x*x*x*x*x*x*x*x))",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal(x^-10,1/(x*x*x*x*x*x*x*x*x*x))",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal(x^-11,1/(x*x*x*x*x*x*x*x*x*x*x))",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal(x^-12,1/(x*x*x*x*x*x*x*x*x*x*x*x))",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal(x^-13,1/(x*x*x*x*x*x*x*x*x*x*x*x*x))",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal(x^-14,1/(x*x*x*x*x*x*x*x*x*x*x*x*x*x))",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal(x^-15,1/(x*x*x*x*x*x*x*x*x*x*x*x*x*x*x))",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal(x^-16,1/(x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x))",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal(x^-17,1/(x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x))",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal(x^-18,1/(x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x))",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal(x^-19,1/(x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x))",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal(x^-20,1/(x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x))",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal(x^-21,1/(x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x))",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal(x^-22,1/(x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x))",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal(x^-23,1/(x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x))",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal(x^-24,1/(x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x))",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal(x^-25,1/(x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x))",T(12.34),T(0.0),T(1.0)),
                                test_xy<T>("equal( y^-0,1/1)",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal( y^-1,1/(y))",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal( y^-2,1/(y*y))",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal( y^-3,1/(y*y*y))",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal( y^-4,1/(y*y*y*y))",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal( y^-5,1/(y*y*y*y*y))",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal( y^-6,1/(y*y*y*y*y*y))",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal( y^-7,1/(y*y*y*y*y*y*y))",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal( y^-8,1/(y*y*y*y*y*y*y*y))",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal( y^-9,1/(y*y*y*y*y*y*y*y*y))",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal(y^-10,1/(y*y*y*y*y*y*y*y*y*y))",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal(y^-11,1/(y*y*y*y*y*y*y*y*y*y*y))",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal(y^-12,1/(y*y*y*y*y*y*y*y*y*y*y*y))",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal(y^-13,1/(y*y*y*y*y*y*y*y*y*y*y*y*y))",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal(y^-14,1/(y*y*y*y*y*y*y*y*y*y*y*y*y*y))",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal(y^-15,1/(y*y*y*y*y*y*y*y*y*y*y*y*y*y*y))",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal(y^-16,1/(y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y))",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal(y^-17,1/(y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y))",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal(y^-18,1/(y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y))",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal(y^-19,1/(y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y))",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal(y^-20,1/(y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y))",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal(y^-21,1/(y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y))",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal(y^-22,1/(y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y))",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal(y^-23,1/(y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y))",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal(y^-24,1/(y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y))",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("equal(y^-25,1/(y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y*y))",T(0.0),T(12.34),T(1.0)),
                                test_xy<T>("(2 + x) + 7",T(3.0),T(0.0),T((2.0 + 3.0) + 7.0)),
                                test_xy<T>("(2 + x) - 7",T(3.0),T(0.0),T((2.0 + 3.0) - 7.0)),
                                test_xy<T>("(2 - x) + 7",T(3.0),T(0.0),T((2.0 - 3.0) + 7.0)),
                                test_xy<T>("(2 - x) - 7",T(3.0),T(0.0),T((2.0 - 3.0) - 7.0)),
                                test_xy<T>("(2 * x) * 7",T(3.0),T(0.0),T((2.0 * 3.0) * 7.0)),
                                test_xy<T>("(2 * x) / 7",T(3.0),T(0.0),T((2.0 * 3.0) / 7.0)),
                                test_xy<T>("(2 / x) * 7",T(3.0),T(0.0),T((2.0 / 3.0) * 7.0)),
                                test_xy<T>("(2 / x) / 7",T(3.0),T(0.0),T((2.0 / 3.0) / 7.0)),
                                test_xy<T>("2 + (x + 7)",T(3.0),T(0.0),T(2.0 + (3.0 + 7.0))),
                                test_xy<T>("2 + (x - 7)",T(3.0),T(0.0),T(2.0 + (3.0 - 7.0))),
                                test_xy<T>("2 - (x + 7)",T(3.0),T(0.0),T(2.0 - (3.0 + 7.0))),
                                test_xy<T>("2 - (x - 7)",T(3.0),T(0.0),T(2.0 - (3.0 - 7.0))),
                                test_xy<T>("2 * (x * 7)",T(3.0),T(0.0),T(2.0 * (3.0 * 7.0))),
                                test_xy<T>("2 * (x / 7)",T(3.0),T(0.0),T(2.0 * (3.0 / 7.0))),
                                test_xy<T>("2 / (x * 7)",T(3.0),T(0.0),T(2.0 / (3.0 * 7.0))),
                                test_xy<T>("2 / (x / 7)",T(3.0),T(0.0),T(2.0 / (3.0 / 7.0))),
                                test_xy<T>("2 + (7 + x)",T(3.0),T(0.0),T(2.0 + (7.0 + 3.0))),
                                test_xy<T>("2 + (7 - x)",T(3.0),T(0.0),T(2.0 + (7.0 - 3.0))),
                                test_xy<T>("2 - (7 + x)",T(3.0),T(0.0),T(2.0 - (7.0 + 3.0))),
                                test_xy<T>("2 - (7 - x)",T(3.0),T(0.0),T(2.0 - (7.0 - 3.0))),
                                test_xy<T>("2 * (7 * x)",T(3.0),T(0.0),T(2.0 * (7.0 * 3.0))),
                                test_xy<T>("2 * (7 / x)",T(3.0),T(0.0),T(2.0 * (7.0 / 3.0))),
                                test_xy<T>("2 / (7 * x)",T(3.0),T(0.0),T(2.0 / (7.0 * 3.0))),
                                test_xy<T>("2 / (7 / x)",T(3.0),T(0.0),T(2.0 / (7.0 / 3.0))),
                                test_xy<T>("(x + 2) + 7",T(3.0),T(0.0),T((3.0 + 2.0) + 7.0)),
                                test_xy<T>("(x + 2) - 7",T(3.0),T(0.0),T((3.0 + 2.0) - 7.0)),
                                test_xy<T>("(x - 2) + 7",T(3.0),T(0.0),T((3.0 - 2.0) + 7.0)),
                                test_xy<T>("(x - 2) - 7",T(3.0),T(0.0),T((3.0 - 2.0) - 7.0)),
                                test_xy<T>("(x * 2) * 7",T(3.0),T(0.0),T((3.0 * 2.0) * 7.0)),
                                test_xy<T>("(x * 2) / 7",T(3.0),T(0.0),T((3.0 * 2.0) / 7.0)),
                                test_xy<T>("(x / 2) * 7",T(3.0),T(0.0),T((3.0 / 2.0) * 7.0)),
                                test_xy<T>("(x / 2) / 7",T(3.0),T(0.0),T((3.0 / 2.0) / 7.0)),
                                test_xy<T>("((2 + x) + (3 + y))",T(7.0),T(9.0),T(((2.0 + 7.0) + (3.0 + 9.0)))),
                                test_xy<T>("((2 + x) - (3 + y))",T(7.0),T(9.0),T(((2.0 + 7.0) - (3.0 + 9.0)))),
                                test_xy<T>("((2 - x) - (3 - y))",T(7.0),T(9.0),T(((2.0 - 7.0) - (3.0 - 9.0)))),
                                test_xy<T>("((2 * x) * (3 * y))",T(7.0),T(9.0),T(((2.0 * 7.0) * (3.0 * 9.0)))),
                                test_xy<T>("((x + 2) + (y + 3))",T(7.0),T(9.0),T(((7.0 + 2.0) + (9.0 + 3.0)))),
                                test_xy<T>("((x + 2) - (y + 3))",T(7.0),T(9.0),T(((7.0 + 2.0) - (9.0 + 3.0)))),
                                test_xy<T>("((x - 2) - (y - 3))",T(7.0),T(9.0),T(((7.0 - 2.0) - (9.0 - 3.0)))),
                                test_xy<T>("((2 * x) * (3 * y))",T(7.0),T(9.0),T(((2.0 * 7.0) * (3.0 * 9.0)))),
                                test_xy<T>("((2 + x) + (y + 3))",T(7.0),T(9.0),T(((2.0 + 7.0) + (9.0 + 3.0)))),
                                test_xy<T>("((2 + x) - (y + 3))",T(7.0),T(9.0),T(((2.0 + 7.0) - (9.0 + 3.0)))),
                                test_xy<T>("((2 - x) - (y - 3))",T(7.0),T(9.0),T(((2.0 - 7.0) - (9.0 - 3.0)))),
                                test_xy<T>("((2 * x) * (3 * y))",T(7.0),T(9.0),T(((2.0 * 7.0) * (3.0 * 9.0)))),
                                test_xy<T>("((x + 2) + (3 + y))",T(7.0),T(9.0),T(((7.0 + 2.0) + (3.0 + 9.0)))),
                                test_xy<T>("((x + 2) - (3 + y))",T(7.0),T(9.0),T(((7.0 + 2.0) - (3.0 + 9.0)))),
                                test_xy<T>("((x - 2) - (3 - y))",T(7.0),T(9.0),T(((7.0 - 2.0) - (3.0 - 9.0)))),
                                test_xy<T>("((2 * x) * (3 * y))",T(7.0),T(9.0),T(((2.0 * 7.0) * (3.0 * 9.0)))),
                                test_xy<T>("((2 * x) / (3 * y))",T(7.0),T(9.0),T(((2.0 * 7.0) / (3.0 * 9.0)))),
                                test_xy<T>("((2 / x) * (3 / y))",T(7.0),T(9.0),T(((2.0 / 7.0) * (3.0 / 9.0)))),
                                test_xy<T>("((2 * x) / (3 / y))",T(7.0),T(9.0),T(((2.0 * 7.0) / (3.0 / 9.0)))),
                                test_xy<T>("((2 / x) / (3 * y))",T(7.0),T(9.0),T(((2.0 / 7.0) / (3.0 * 9.0)))),
                                test_xy<T>("((x * 2) / (y * 3))",T(7.0),T(9.0),T(((7.0 * 2.0) / (9.0 * 3.0)))),
                                test_xy<T>("((x / 2) * (y / 3))",T(7.0),T(9.0),T(((7.0 / 2.0) * (9.0 / 3.0)))),
                                test_xy<T>("((x * 2) / (y / 3))",T(7.0),T(9.0),T(((7.0 * 2.0) / (9.0 / 3.0)))),
                                test_xy<T>("((x / 2) / (y * 3))",T(7.0),T(9.0),T(((7.0 / 2.0) / (9.0 * 3.0)))),
                                test_xy<T>("((2 * x) / (y * 3))",T(7.0),T(9.0),T(((2.0 * 7.0) / (9.0 * 3.0)))),
                                test_xy<T>("((2 / x) * (y / 3))",T(7.0),T(9.0),T(((2.0 / 7.0) * (9.0 / 3.0)))),
                                test_xy<T>("((2 * x) / (y / 3))",T(7.0),T(9.0),T(((2.0 * 7.0) / (9.0 / 3.0)))),
                                test_xy<T>("((2 / x) / (y * 3))",T(7.0),T(9.0),T(((2.0 / 7.0) / (9.0 * 3.0)))),
                                test_xy<T>("((x * 2) / (3 * y))",T(7.0),T(9.0),T(((7.0 * 2.0) / (3.0 * 9.0)))),
                                test_xy<T>("((x / 2) * (3 / y))",T(7.0),T(9.0),T(((7.0 / 2.0) * (3.0 / 9.0)))),
                                test_xy<T>("((x * 2) / (3 / y))",T(7.0),T(9.0),T(((7.0 * 2.0) / (3.0 / 9.0)))),
                                test_xy<T>("((x / 2) / (3 * y))",T(7.0),T(9.0),T(((7.0 / 2.0) / (3.0 * 9.0)))),
                                test_xy<T>("([(min(x,8) + y) + 3] - 4)",T(7.0),T(9.0),T((((std::min(7.0,8.0) + 9.0) + 3.0) - 4.0))),
                                test_xy<T>("([(min(x,8) + y) + 3] + 4)",T(7.0),T(9.0),T((((std::min(7.0,8.0) + 9.0) + 3.0) + 4.0))),
                                test_xy<T>("([(min(x,8) + y) + 3] * 4)",T(7.0),T(9.0),T((((std::min(7.0,8.0) + 9.0) + 3.0) * 4.0))),
                                test_xy<T>("([(min(x,8) + y) + 3] / 4)",T(7.0),T(9.0),T((((std::min(7.0,8.0) + 9.0) + 3.0) / 4.0))),
                                test_xy<T>("([(min(x,8) + y) - 3] - 4)",T(7.0),T(9.0),T((((std::min(7.0,8.0) + 9.0) - 3.0) - 4.0))),
                                test_xy<T>("([(min(x,8) + y) - 3] + 4)",T(7.0),T(9.0),T((((std::min(7.0,8.0) + 9.0) - 3.0) + 4.0))),
                                test_xy<T>("([(min(x,8) + y) - 3] * 4)",T(7.0),T(9.0),T((((std::min(7.0,8.0) + 9.0) - 3.0) * 4.0))),
                                test_xy<T>("([(min(x,8) + y) - 3] / 4)",T(7.0),T(9.0),T((((std::min(7.0,8.0) + 9.0) - 3.0) / 4.0))),
                                test_xy<T>("([(min(x,8) + y) * 3] - 4)",T(7.0),T(9.0),T((((std::min(7.0,8.0) + 9.0) * 3.0) - 4.0))),
                                test_xy<T>("([(min(x,8) + y) * 3] + 4)",T(7.0),T(9.0),T((((std::min(7.0,8.0) + 9.0) * 3.0) + 4.0))),
                                test_xy<T>("([(min(x,8) + y) * 3] * 4)",T(7.0),T(9.0),T((((std::min(7.0,8.0) + 9.0) * 3.0) * 4.0))),
                                test_xy<T>("([(min(x,8) + y) * 3] / 4)",T(7.0),T(9.0),T((((std::min(7.0,8.0) + 9.0) * 3.0) / 4.0))),
                                test_xy<T>("([(min(x,8) + y) / 3] - 4)",T(7.0),T(9.0),T((((std::min(7.0,8.0) + 9.0) / 3.0) - 4.0))),
                                test_xy<T>("([(min(x,8) + y) / 3] + 4)",T(7.0),T(9.0),T((((std::min(7.0,8.0) + 9.0) / 3.0) + 4.0))),
                                test_xy<T>("([(min(x,8) + y) / 3] * 4)",T(7.0),T(9.0),T((((std::min(7.0,8.0) + 9.0) / 3.0) * 4.0))),
                                test_xy<T>("([(min(x,8) + y) / 3] / 4)",T(7.0),T(9.0),T((((std::min(7.0,8.0) + 9.0) / 3.0) / 4.0))),
                                test_xy<T>("(4 - [3 + (min(x,8) + y)])",T(7.0),T(9.0),T((4.0 - (3.0 + (std::min(7.0,8.0) + 9.0))))),
                                test_xy<T>("(4 + [3 + (min(x,8) + y)])",T(7.0),T(9.0),T((4.0 + (3.0 + (std::min(7.0,8.0) + 9.0))))),
                                test_xy<T>("(4 * [3 + (min(x,8) + y)])",T(7.0),T(9.0),T((4.0 * (3.0 + (std::min(7.0,8.0) + 9.0))))),
                                test_xy<T>("(4 / [3 + (min(x,8) + y)])",T(7.0),T(9.0),T((4.0 / (3.0 + (std::min(7.0,8.0) + 9.0))))),
                                test_xy<T>("(4 - [3 - (min(x,8) + y)])",T(7.0),T(9.0),T((4.0 - (3.0 - (std::min(7.0,8.0) + 9.0))))),
                                test_xy<T>("(4 + [3 - (min(x,8) + y)])",T(7.0),T(9.0),T((4.0 + (3.0 - (std::min(7.0,8.0) + 9.0))))),
                                test_xy<T>("(4 * [3 - (min(x,8) + y)])",T(7.0),T(9.0),T((4.0 * (3.0 - (std::min(7.0,8.0) + 9.0))))),
                                test_xy<T>("(4 / [3 - (min(x,8) + y)])",T(7.0),T(9.0),T((4.0 / (3.0 - (std::min(7.0,8.0) + 9.0))))),
                                test_xy<T>("(4 - [3 * (min(x,8) + y)])",T(7.0),T(9.0),T((4.0 - (3.0 * (std::min(7.0,8.0) + 9.0))))),
                                test_xy<T>("(4 + [3 * (min(x,8) + y)])",T(7.0),T(9.0),T((4.0 + (3.0 * (std::min(7.0,8.0) + 9.0))))),
                                test_xy<T>("(4 * [3 * (min(x,8) + y)])",T(7.0),T(9.0),T((4.0 * (3.0 * (std::min(7.0,8.0) + 9.0))))),
                                test_xy<T>("(4 / [3 * (min(x,8) + y)])",T(7.0),T(9.0),T((4.0 / (3.0 * (std::min(7.0,8.0) + 9.0))))),
                                test_xy<T>("(4 - [3 / (min(x,8) + y)])",T(7.0),T(9.0),T((4.0 - (3.0 / (std::min(7.0,8.0) + 9.0))))),
                                test_xy<T>("(4 + [3 / (min(x,8) + y)])",T(7.0),T(9.0),T((4.0 + (3.0 / (std::min(7.0,8.0) + 9.0))))),
                                test_xy<T>("(4 * [3 / (min(x,8) + y)])",T(7.0),T(9.0),T((4.0 * (3.0 / (std::min(7.0,8.0) + 9.0))))),
                                test_xy<T>("(4 / [3 / (min(x,8) + y)])",T(7.0),T(9.0),T((4.0 / (3.0 / (std::min(7.0,8.0) + 9.0))))),
                                test_xy<T>("((2 * x) + (2 * y))",T(7.0),T(9.0),T(((2.0 * 7.0) + (2.0 * 9.0)))),
                                test_xy<T>("((2 * x) - (2 * y))",T(7.0),T(9.0),T(((2.0 * 7.0) - (2.0 * 9.0)))),
                                test_xy<T>("((2 * x) + (y * 2))",T(7.0),T(9.0),T(((2.0 * 7.0) + (9.0 * 2.0)))),
                                test_xy<T>("((x * 2) - (y * 2))",T(7.0),T(9.0),T(((7.0 * 2.0) - (9.0 * 2.0)))),
                                test_xy<T>("0 * (abs  (x) + acos (y) + asin (x) + atan (y))",T(1.0),T(1.0),T(0.0)),
                                test_xy<T>("0 * (ceil (x) + cos  (y) + cosh (x) + exp  (y))",T(1.0),T(1.0),T(0.0)),
                                test_xy<T>("0 * (floor(x) + log  (y) + log10(x) + round(y))",T(1.0),T(1.0),T(0.0)),
                                test_xy<T>("0 * (sin  (x) + sinh (y) + sqrt (x) + tan  (y))",T(1.0),T(1.0),T(0.0)),
                                test_xy<T>("0 * (sec  (x) + csc  (y) + tanh (x) + cot  (y))",T(1.0),T(1.0),T(0.0)),
                                test_xy<T>("0 * (erf  (x) + erfc (y) + sgn  (y) + frac (y))",T(1.0),T(1.0),T(0.0)),
                                test_xy<T>("0 * (log1p(x) + expm1(y) + acosh(x) + asinh(y))",T(1.0),T(1.0),T(0.0)),
                                test_xy<T>("0 * (deg2grad(x) + grad2deg(y) + rad2deg(x) + deg2rad(y))",T(1.0),T(1.0),T(0.0)),
                                test_xy<T>("switch { case (x <= y) : (y - x); default: 1.12345; }",T(1.0),T(2.0),T(1.0)),
                                test_xy<T>("switch { case (x >  y) : 0; case (x <= y) : (y - x); default: 1.12345; }",T(1.0),T(2.0),T(1.0)),
                                test_xy<T>("switch { case (x <= y) : switch { case (x <= y) : (y - x); default: 1.12345; }; default: 1.12345; }",T(1.0),T(2.0),T(1.0)),
                                test_xy<T>("switch { case [x <= y] : [y - x]; default: 1.12345; }",T(1.0),T(2.0),T(1.0)),
                                test_xy<T>("switch { case [x >  y] : 0; case [x <= y] : [y - x]; default: 1.12345; }",T(1.0),T(2.0),T(1.0)),
                                test_xy<T>("switch { case [x <= y] : switch { case [x <= y] : {y - x}; default: 1.12345; }; default: 1.12345; }",T(1.0),T(2.0),T(1.0)),
                                test_xy<T>("switch { case {x <= y} : x; default: 1.12345; }",T(1.0),T(2.0),T(1.0)),
                                test_xy<T>("switch { case {x >  y} : 0; case {x <= y} : {y - x}; default: 1.12345; }",T(1.0),T(2.0),T(1.0)),
                                test_xy<T>("switch { case {x <= y} : switch { case {x <= y} : x; default: 1.12345; }; default: 1.12345; }",T(1.0),T(2.0),T(1.0)),
                                test_xy<T>("switch { case [(x <= y)] : {y - x}; default: 1.12345; }",T(1.0),T(2.0),T(1.0)),
                                test_xy<T>("switch { case ([x >  y]) : [0]; case ([x <= y]) : [y - x]; default: 1.12345; }",T(1.0),T(2.0),T(1.0)),
                                test_xy<T>("switch { case {(x <= y)} : switch { case ({x <= y}) : x; default: 1.12345; }; default: 1.12345; }",T(1.0),T(2.0),T(1.0)),
                                test_xy<T>("[*]{ case x < y : x + y; case y < x : y - x; }",T(2.0),T(3.0),T(5.0)),
                                test_xy<T>("[*]{ case x > y : x + y; case y > x : y - x; }",T(2.0),T(3.0),T(1.0)),
                                test_xy<T>("[*]{ case x > y : x - y; case y < x : y + x; }",T(2.0),T(3.0),T(0.0)),
                                test_xy<T>("0 ? x : y"                       ,T(1.0),T(2.0),T( 2.0)),
                                test_xy<T>("1 ? x : y"                       ,T(1.0),T(2.0),T( 1.0)),
                                test_xy<T>("x ? x : y"                       ,T(1.0),T(2.0),T( 1.0)),
                                test_xy<T>("x ? x : y"                       ,T(0.0),T(2.0),T( 2.0)),
                                test_xy<T>("(x + y < 4) ? 1 : 2"             ,T(1.0),T(2.0),T( 1.0)),
                                test_xy<T>("(x + y > 4) ? 1 : 2"             ,T(1.0),T(2.0),T( 2.0)),
                                test_xy<T>("x < y ? x + y : x - y"           ,T(1.0),T(2.0),T( 3.0)),
                                test_xy<T>("x > y ? x + y : x - y"           ,T(1.0),T(2.0),T(-1.0)),
                                test_xy<T>("(x + x < y ? 7 : 9) == 7"        ,T(1.0),T(3.0),T( 1.0)),
                                test_xy<T>("(x + x < y + y ? 7 : 9) == 7"    ,T(1.0),T(3.0),T( 1.0)),
                                test_xy<T>("(x > y + y ? 7 : 9) == 9"        ,T(1.0),T(3.0),T( 1.0)),
                                test_xy<T>("(x + x > y ? 7 : 9) == 9"        ,T(1.0),T(3.0),T( 1.0)),
                                test_xy<T>("(x + x > y + 3 ? 7 : 9) == 9"    ,T(1.0),T(3.0),T( 1.0)),
                                test_xy<T>("(x < (y + y) ? 7 : 9) == 7"      ,T(1.0),T(3.0),T( 1.0)),
                                test_xy<T>("((x + x) < y ? 7 : 9) == 7"      ,T(1.0),T(3.0),T( 1.0)),
                                test_xy<T>("((x + x) < (y + y) ? 7 : 9) == 7",T(1.0),T(3.0),T( 1.0)),
                                test_xy<T>("(x += 2 ) ==    3 "              ,T(1),T(3),T(1)),
                                test_xy<T>("(x += 2y) ==    7 "              ,T(1),T(3),T(1)),
                                test_xy<T>("(x -= 2 ) ==   -1 "              ,T(1),T(3),T(1)),
                                test_xy<T>("(x -= 2y) ==   -5 "              ,T(1),T(3),T(1)),
                                test_xy<T>("(x *= 2 ) ==    2 "              ,T(1),T(3),T(1)),
                                test_xy<T>("(x *= 2y) ==    6 "              ,T(1),T(3),T(1)),
                                test_xy<T>("(x /= 2 ) == (1/2)"              ,T(1),T(3),T(1)),
                                test_xy<T>("(x /= 2y) == (1/6)"              ,T(1),T(3),T(1)),
                                test_xy<T>("for(var i := 0; (i < 10);) { i += 1; }; x;"                   ,T(1),T(20),T( 1)),
                                test_xy<T>("for(var i := 0; (i < 10) and (i != y); i+=2) { x += i; }; x;" ,T(1),T(20),T(21)),
                                test_xy<T>("for(var i := 0; (i < 10) and (i != y);) { x += i; i+=2; }; x;",T(1),T(20),T(21)),
                                test_xy<T>("for(var i := 0; (i < y); i += 1) { if (i <= (y / 2)) x += i; else break; }; x;" ,T(0),T(10),T(15)),
                                test_xy<T>("for(var i := 0; (i < y); i += 1) { if (i <= (y / 2)) continue; else x += i; }; x;" ,T(0),T(10),T(30)),
                                test_xy<T>("var a := 2; (0 * a) == 0",T(0),T(0),T(1)),
                                test_xy<T>("var a := 2; (0 / a) == 0",T(0),T(0),T(1)),
                                test_xy<T>("var a := 2; (a * 0) == 0",T(0),T(0),T(1)),
                                test_xy<T>("var a := 2; (a / 1) == a",T(0),T(0),T(1)),
                                test_xy<T>("var a := 2; (0 + a) == a",T(0),T(0),T(1)),
                                test_xy<T>("var a := 2; (a + 0) == a",T(0),T(0),T(1)),
                                test_xy<T>("var a := 2; (1 * a) == a",T(0),T(0),T(1)),
                                test_xy<T>("var a.b     := 3; (2 * a.b    ) == 6",T(0),T(0),T(1)),
                                test_xy<T>("var aa.bb   := 3; (2 * aa.bb  ) == 6",T(0),T(0),T(1)),
                                test_xy<T>("var aaa.bbb := 3; (2 * aAa.BbB) == 6",T(0),T(0),T(1)),
                                test_xy<T>("var a1.b2   := 3; (2 * a1.b2  ) == 6",T(0),T(0),T(1))
                              };

      static const std::size_t test_list_size = sizeof(test_list) / sizeof(test_xy<T>);

      const std::size_t rounds = 60;

      for (std::size_t r = 0; r < rounds; ++r)
      {
         bool loop_result = true;

         for (std::size_t i = 0; i < test_list_size; ++i)
         {
            test_xy<T>& test = const_cast<test_xy<T>&>(test_list[i]);

            T x = test.x;
            T y = test.y;

            exprtk::symbol_table<T> symbol_table;
            symbol_table.add_variable("x",x);
            symbol_table.add_variable("y",y);

            exprtk::expression<T> expression;
            expression.register_symbol_table(symbol_table);

            {
               exprtk::parser<T> parser;

               if (!parser.compile(test.expr,expression))
               {
                  printf("run_test01() - Error: %s   Expression: %s\n",
                         parser.error().c_str(),
                         test.expr.c_str());

                  loop_result = false;

                  continue;
               }
            }

            T result = expression.value();

            if (not_equal(result,test.result))
            {
               printf("run_test01() - Computation Error:  Expression: [%s]\tExpected: %19.15f\tResult: %19.15f\n",
                      test.expr.c_str(),
                      (double)test.result,
                      (double)result);

               loop_result = false;
            }
         }

         if (!loop_result)
         {
            return false;
         }
      }
   }

   {
      static const test_xyzw<T> test_list[] =
                              {
                                test_xyzw<T>("((x /  y) / z )",T(7.0),T(9.0),T(3.0),T(0.0),T(((7.0 /  9.0) / 3.0 ))),
                                test_xyzw<T>("((x /  y) / 2 )",T(7.0),T(9.0),T(3.0),T(0.0),T(((7.0 /  9.0) / 2.0 ))),
                                test_xyzw<T>("((x /  2) / y )",T(7.0),T(9.0),T(3.0),T(0.0),T(((7.0 /  2.0) / 9.0 ))),
                                test_xyzw<T>("((2 /  x) / y )",T(7.0),T(9.0),T(3.0),T(0.0),T(((2.0 /  7.0) / 9.0 ))),
                                test_xyzw<T>("( x / (y /  z))",T(7.0),T(9.0),T(3.0),T(0.0),T(( 7.0 / (9.0  / 3.0)))),
                                test_xyzw<T>("( x / (y /  2))",T(7.0),T(9.0),T(3.0),T(0.0),T(( 7.0 / (9.0  / 2.0)))),
                                test_xyzw<T>("( x / (2  / y))",T(7.0),T(9.0),T(3.0),T(0.0),T(( 7.0 / (2.0  / 9.0)))),
                                test_xyzw<T>("( 2 / (x /  y))",T(7.0),T(9.0),T(3.0),T(0.0),T(( 2.0 / (7.0  / 9.0)))),
                                test_xyzw<T>("([(min(x,y) + z) + 3] - 4)",T(5.0),T(7.0),T(9.0),T(0.0),T((((std::min(5.0,7.0) + 9.0) + 3.0) - 4.0))),
                                test_xyzw<T>("([(min(x,y) + z) + 3] + 4)",T(5.0),T(7.0),T(9.0),T(0.0),T((((std::min(5.0,7.0) + 9.0) + 3.0) + 4.0))),
                                test_xyzw<T>("([(min(x,y) + z) + 3] * 4)",T(5.0),T(7.0),T(9.0),T(0.0),T((((std::min(5.0,7.0) + 9.0) + 3.0) * 4.0))),
                                test_xyzw<T>("([(min(x,y) + z) + 3] / 4)",T(5.0),T(7.0),T(9.0),T(0.0),T((((std::min(5.0,7.0) + 9.0) + 3.0) / 4.0))),
                                test_xyzw<T>("([(min(x,y) + z) - 3] - 4)",T(5.0),T(7.0),T(9.0),T(0.0),T((((std::min(5.0,7.0) + 9.0) - 3.0) - 4.0))),
                                test_xyzw<T>("([(min(x,y) + z) - 3] + 4)",T(5.0),T(7.0),T(9.0),T(0.0),T((((std::min(5.0,7.0) + 9.0) - 3.0) + 4.0))),
                                test_xyzw<T>("([(min(x,y) + z) - 3] * 4)",T(5.0),T(7.0),T(9.0),T(0.0),T((((std::min(5.0,7.0) + 9.0) - 3.0) * 4.0))),
                                test_xyzw<T>("([(min(x,y) + z) - 3] / 4)",T(5.0),T(7.0),T(9.0),T(0.0),T((((std::min(5.0,7.0) + 9.0) - 3.0) / 4.0))),
                                test_xyzw<T>("([(min(x,y) + z) * 3] - 4)",T(5.0),T(7.0),T(9.0),T(0.0),T((((std::min(5.0,7.0) + 9.0) * 3.0) - 4.0))),
                                test_xyzw<T>("([(min(x,y) + z) * 3] + 4)",T(5.0),T(7.0),T(9.0),T(0.0),T((((std::min(5.0,7.0) + 9.0) * 3.0) + 4.0))),
                                test_xyzw<T>("([(min(x,y) + z) * 3] * 4)",T(5.0),T(7.0),T(9.0),T(0.0),T((((std::min(5.0,7.0) + 9.0) * 3.0) * 4.0))),
                                test_xyzw<T>("([(min(x,y) + z) * 3] / 4)",T(5.0),T(7.0),T(9.0),T(0.0),T((((std::min(5.0,7.0) + 9.0) * 3.0) / 4.0))),
                                test_xyzw<T>("([(min(x,y) + z) / 3] - 4)",T(5.0),T(7.0),T(9.0),T(0.0),T((((std::min(5.0,7.0) + 9.0) / 3.0) - 4.0))),
                                test_xyzw<T>("([(min(x,y) + z) / 3] + 4)",T(5.0),T(7.0),T(9.0),T(0.0),T((((std::min(5.0,7.0) + 9.0) / 3.0) + 4.0))),
                                test_xyzw<T>("([(min(x,y) + z) / 3] * 4)",T(5.0),T(7.0),T(9.0),T(0.0),T((((std::min(5.0,7.0) + 9.0) / 3.0) * 4.0))),
                                test_xyzw<T>("([(min(x,y) + z) / 3] / 4)",T(5.0),T(7.0),T(9.0),T(0.0),T((((std::min(5.0,7.0) + 9.0) / 3.0) / 4.0))),
                                test_xyzw<T>("(4 - [3 + (min(x,y) + z)])",T(5.0),T(7.0),T(9.0),T(0.0),T((4.0 - (3.0 + (std::min(5.0,7.0) + 9.0))))),
                                test_xyzw<T>("(4 + [3 + (min(x,y) + z)])",T(5.0),T(7.0),T(9.0),T(0.0),T((4.0 + (3.0 + (std::min(5.0,7.0) + 9.0))))),
                                test_xyzw<T>("(4 * [3 + (min(x,y) + z)])",T(5.0),T(7.0),T(9.0),T(0.0),T((4.0 * (3.0 + (std::min(5.0,7.0) + 9.0))))),
                                test_xyzw<T>("(4 / [3 + (min(x,y) + z)])",T(5.0),T(7.0),T(9.0),T(0.0),T((4.0 / (3.0 + (std::min(5.0,7.0) + 9.0))))),
                                test_xyzw<T>("(4 - [3 - (min(x,y) + z)])",T(5.0),T(7.0),T(9.0),T(0.0),T((4.0 - (3.0 - (std::min(5.0,7.0) + 9.0))))),
                                test_xyzw<T>("(4 + [3 - (min(x,y) + z)])",T(5.0),T(7.0),T(9.0),T(0.0),T((4.0 + (3.0 - (std::min(5.0,7.0) + 9.0))))),
                                test_xyzw<T>("(4 * [3 - (min(x,y) + z)])",T(5.0),T(7.0),T(9.0),T(0.0),T((4.0 * (3.0 - (std::min(5.0,7.0) + 9.0))))),
                                test_xyzw<T>("(4 / [3 - (min(x,y) + z)])",T(5.0),T(7.0),T(9.0),T(0.0),T((4.0 / (3.0 - (std::min(5.0,7.0) + 9.0))))),
                                test_xyzw<T>("(4 - [3 * (min(x,y) + z)])",T(5.0),T(7.0),T(9.0),T(0.0),T((4.0 - (3.0 * (std::min(5.0,7.0) + 9.0))))),
                                test_xyzw<T>("(4 + [3 * (min(x,y) + z)])",T(5.0),T(7.0),T(9.0),T(0.0),T((4.0 + (3.0 * (std::min(5.0,7.0) + 9.0))))),
                                test_xyzw<T>("(4 * [3 * (min(x,y) + z)])",T(5.0),T(7.0),T(9.0),T(0.0),T((4.0 * (3.0 * (std::min(5.0,7.0) + 9.0))))),
                                test_xyzw<T>("(4 / [3 * (min(x,y) + z)])",T(5.0),T(7.0),T(9.0),T(0.0),T((4.0 / (3.0 * (std::min(5.0,7.0) + 9.0))))),
                                test_xyzw<T>("(4 - [3 / (min(x,y) + z)])",T(5.0),T(7.0),T(9.0),T(0.0),T((4.0 - (3.0 / (std::min(5.0,7.0) + 9.0))))),
                                test_xyzw<T>("(4 + [3 / (min(x,y) + z)])",T(5.0),T(7.0),T(9.0),T(0.0),T((4.0 + (3.0 / (std::min(5.0,7.0) + 9.0))))),
                                test_xyzw<T>("(4 * [3 / (min(x,y) + z)])",T(5.0),T(7.0),T(9.0),T(0.0),T((4.0 * (3.0 / (std::min(5.0,7.0) + 9.0))))),
                                test_xyzw<T>("(4 / [3 / (min(x,y) + z)])",T(5.0),T(7.0),T(9.0),T(0.0),T((4.0 / (3.0 / (std::min(5.0,7.0) + 9.0))))),
                                test_xyzw<T>("if (x < y) { z+2; z;} == z"                             ,T(1.0),T(2.0),T(3.0),T(4.0),T(1.0)),
                                test_xyzw<T>("if (x > y) { z+2; z;} == null"                          ,T(1.0),T(2.0),T(3.0),T(4.0),T(1.0)),
                                test_xyzw<T>("if (x < y) { z+2; z;} else w; == z"                     ,T(1.0),T(2.0),T(3.0),T(4.0),T(1.0)),
                                test_xyzw<T>("if (x > y) { z+2; z;} else 1 + w; == (w + 1)"           ,T(1.0),T(2.0),T(3.0),T(4.0),T(1.0)),
                                test_xyzw<T>("if (x < y) { z+2; z;} else {1+2; w;} == z"              ,T(1.0),T(2.0),T(3.0),T(4.0),T(1.0)),
                                test_xyzw<T>("if (x > y) { z+2; z;} else {1+2; w;} == w"              ,T(1.0),T(2.0),T(3.0),T(4.0),T(1.0)),
                                test_xyzw<T>("if (x < y) { z+2; z;} else if (x < y) w; == z"          ,T(1.0),T(2.0),T(3.0),T(4.0),T(1.0)),
                                test_xyzw<T>("if (x > y) { z+2; z;} else if (x < y) 1 + w; == w + 1"  ,T(1.0),T(2.0),T(3.0),T(4.0),T(1.0)),
                                test_xyzw<T>("if (x > y) { z+2; z;} else if (x > y) w; == null"       ,T(1.0),T(2.0),T(3.0),T(4.0),T(1.0)),
                                test_xyzw<T>("if (x < y) { z+2; z;} else if (x < y) {w+2; w;} == z"   ,T(1.0),T(2.0),T(3.0),T(4.0),T(1.0)),
                                test_xyzw<T>("if (x > y) { z+2; z;} else if (x < y) {w+2; w;} == w"   ,T(1.0),T(2.0),T(3.0),T(4.0),T(1.0)),
                                test_xyzw<T>("if (x > y) { z+2; z;} else if (x > y) {w+2; w;} == null",T(1.0),T(2.0),T(3.0),T(4.0),T(1.0))
                              };

      static const std::size_t test_list_size = sizeof(test_list) / sizeof(test_xyzw<T>);

      const std::size_t rounds = 60;

      for (std::size_t r = 0; r < rounds; ++r)
      {
         bool loop_result = true;
         for (std::size_t i = 0; i < test_list_size; ++i)
         {
            test_xyzw<T>& test = const_cast<test_xyzw<T>&>(test_list[i]);

            exprtk::symbol_table<T> symbol_table;
            symbol_table.add_variable("x",test.x);
            symbol_table.add_variable("y",test.y);
            symbol_table.add_variable("z",test.z);
            symbol_table.add_variable("w",test.w);

            exprtk::expression<T> expression;
            expression.register_symbol_table(symbol_table);

            {
               exprtk::parser<T> parser;

               if (!parser.compile(test.expr,expression))
               {
                  printf("run_test01() - Error: %s   Expression: %s\n",
                         parser.error().c_str(),
                         test.expr.c_str());

                  loop_result = false;

                  continue;
               }
            }

            T result = expression.value();

            if (not_equal(result,test.result))
            {
               printf("run_test01() - Computation Error:  Expression: [%s]\tExpected: %19.15f\tResult: %19.15f\n",
                      test.expr.c_str(),
                      (double)test.result,
                      (double)result);

               loop_result = false;
            }
         }

         if (!loop_result)
         {
            return false;
         }
      }
   }

   {
      const std::string expr_list[] =
                          {
                            "((v[1] + x) == (x + v[1]))",
                            "((v[0] += x) == x)",
                            "((v[0] += x + y) == (x + y))",
                            "((v[0] -= x) == -x)",
                            "((v[0] -= (x + y)) == -(x + y))",
                            "((v[1] + v[2]) == (v[3 - 1] + v[2 * 1/2]))",
                            "(v[v[1]] == v[1])",
                            "(v[1] += v[1]) == v[1 + 1]",
                            "((v[i[1]] + x) == (x + v[i[1]]))",
                            "((v[i[0]] += x) == x)",
                            "((v[i[0]] += x + y) == (x + y))",
                            "((v[i[0]] -= x) == -x)",
                            "((v[i[0]] -= (x + y)) == -(x + y))",
                            "((v[i[1]] + v[2]) == (v[i[3] - i[1]] + v[i[2] * 1/2]))",
                            "(v[v[i[1]]] == v[i[1]])",
                            "(v[i[1]] += v[i[1]]) == v[i[1] + 1]"
                          };

      const std::size_t expr_list_size = sizeof(expr_list) / sizeof(std::string);

      const std::size_t rounds = 60;

      for (std::size_t r = 0; r < rounds; ++r)
      {
         bool loop_result = true;

         for (std::size_t i = 0; i < expr_list_size; ++i)
         {
            T v[]     = { T(0.0), T(1.1), T(2.2), T(3.3), T(4.4), T(5.5) };
            T index[] = { T(0)  , T(1)  , T(2)  , T(3)  , T(4)  , T(5)   };

            T x = T(6.6);
            T y = T(7.7);
            T z = T(8.8);

            exprtk::symbol_table<T> symbol_table;
            symbol_table.add_variable("x",x);
            symbol_table.add_variable("y",y);
            symbol_table.add_variable("z",z);
            symbol_table.add_vector  ("v",v);
            symbol_table.add_vector  ("i",index);

            exprtk::expression<T> expression;
            expression.register_symbol_table(symbol_table);

            {
               exprtk::parser<T> parser;

               if (!parser.compile(expr_list[i],expression))
               {
                  printf("run_test01() - Error: %s   Expression: %s\n",
                         parser.error().c_str(),
                         expr_list[i].c_str());

                  loop_result = false;

                  continue;
               }
            }

            T result = expression.value();

            if (not_equal(result,T(1)))
            {
               printf("run_test01() - Computation Error:  Expression: [%s]\tExpected: %19.15f\tResult: %19.15f\n",
                      expr_list[i].c_str(),
                      (double)1.0,
                      (double)result);

               loop_result = false;
            }
         }

         if (!loop_result)
         {
            return false;
         }
      }

      for (std::size_t r = 0; r < rounds; ++r)
      {
         bool loop_result = true;

         for (std::size_t i = 0; i < expr_list_size; ++i)
         {
            T v_[]     = { T(0.0), T(1.1), T(2.2), T(3.3), T(4.4), T(5.5) };
            T index_[] = { T(0)  , T(1)  , T(2)  , T(3)  , T(4)  , T(5)   };

            T x = T(6.6);
            T y = T(7.7);
            T z = T(8.8);

            exprtk::vector_view<T> v     = exprtk::make_vector_view(v_    ,6);
            exprtk::vector_view<T> index = exprtk::make_vector_view(index_,6);

            exprtk::symbol_table<T> symbol_table;
            symbol_table.add_variable("x",x);
            symbol_table.add_variable("y",y);
            symbol_table.add_variable("z",z);
            symbol_table.add_vector  ("v",v);
            symbol_table.add_vector  ("i",index);

            exprtk::expression<T> expression;
            expression.register_symbol_table(symbol_table);

            {
               exprtk::parser<T> parser;

               if (!parser.compile(expr_list[i],expression))
               {
                  printf("run_test01() - Error: %s   Expression: %s\n",
                         parser.error().c_str(),
                         expr_list[i].c_str());

                  loop_result = false;

                  continue;
               }
            }

            T result = expression.value();

            if (not_equal(result,T(1)))
            {
               printf("run_test01() - Computation Error:  Expression: [%s]\tExpected: %19.15f\tResult: %19.15f\n",
                      expr_list[i].c_str(),
                      (double)1.0,
                      (double)result);
               loop_result = false;
            }
         }

         if (!loop_result)
         {
            return false;
         }
      }
   }

   return true;
}

template <typename T>
struct test_ab
{
   test_ab(const std::string& e, const std::string& v0, const std::string& v1, const T& r)
   : expr(e),
     a(v0),
     b(v1),
     c("ccc"),
     result(r)
   {}

   std::string expr;
   std::string a;
   std::string b;
   std::string c;
   T result;
};

template <typename T>
inline bool run_test02()
{
   static const test_ab<T> test_list[] =
                           {
                             test_ab<T>("'aaa' == 'aaa'"              ,"","",T(1.0)),
                             test_ab<T>("'aaa'  < 'bbb'"              ,"","",T(1.0)),
                             test_ab<T>("'aaa' <= 'bbb'"              ,"","",T(1.0)),
                             test_ab<T>("'bbb' >  'aaa'"              ,"","",T(1.0)),
                             test_ab<T>("'bbb' >= 'aaa'"              ,"","",T(1.0)),
                             test_ab<T>("'aaa' != 'aaa'"              ,"","",T(0.0)),
                             test_ab<T>("'aaa' != 'bbb'"              ,"","",T(1.0)),
                             test_ab<T>("'aaa' + '123' == 'aaa123'"   ,"","",T(1.0)),
                             test_ab<T>("'aaa123' == 'aaa' + '123'"   ,"","",T(1.0)),
                             test_ab<T>("('aaa' + '123') == 'aaa123'" ,"","",T(1.0)),
                             test_ab<T>("'aaa123' == ('aaa' + '123')" ,"","",T(1.0)),
                             test_ab<T>("'aaa' in 'aaa123'"           ,"","",T(1.0)),
                             test_ab<T>("'123' in 'aaa123'"           ,"","",T(1.0)),
                             test_ab<T>("'a123b' like '*123*'"        ,"","",T(1.0)),
                             test_ab<T>("'a123b' like '*123?'"        ,"","",T(1.0)),
                             test_ab<T>("'1XYZ2' ilike '*xyz*'"       ,"","",T(1.0)),
                             test_ab<T>("'1XYZ2' ilike '*xyz?'"       ,"","",T(1.0)),
                             test_ab<T>("inrange('aaa','bbb','ccc')"  ,"","",T(1.0)),
                             test_ab<T>("a == b"                      ,"aaa","aaa",T(1.0)),
                             test_ab<T>("a != b"                      ,"aaa","bbb",T(1.0)),
                             test_ab<T>("a <  b"                      ,"aaa","bbb",T(1.0)),
                             test_ab<T>("a <= b"                      ,"aaa","bbb",T(1.0)),
                             test_ab<T>("b >  a"                      ,"aaa","bbb",T(1.0)),
                             test_ab<T>("b >= a"                      ,"aaa","bbb",T(1.0)),
                             test_ab<T>("a in b"                      ,"aaa","aaa123",T(1.0)),
                             test_ab<T>("a in b"                      ,"123","aaa123",T(1.0)),
                             test_ab<T>("a == 'aaa'"                  ,"aaa","aaa",T(1.0)),
                             test_ab<T>("'aaa' == a"                  ,"aaa","aaa",T(1.0)),
                             test_ab<T>("a != 'bbb'"                  ,"aaa","bbb",T(1.0)),
                             test_ab<T>("'bbb' != a"                  ,"aaa","bbb",T(1.0)),
                             test_ab<T>("a <  'bbb'"                  ,"aaa","bbb",T(1.0)),
                             test_ab<T>("a <= 'bbb'"                  ,"aaa","bbb",T(1.0)),
                             test_ab<T>("'bbb' >  a"                  ,"aaa","bbb",T(1.0)),
                             test_ab<T>("'bbb' >= a"                  ,"aaa","bbb",T(1.0)),
                             test_ab<T>("a in 'aaa123'"               ,"aaa","aaa123",T(1.0)),
                             test_ab<T>("a in 'aaa123'"               ,"123","aaa123",T(1.0)),
                             test_ab<T>("'aaa' in b"                  ,"aaa","aaa123",T(1.0)),
                             test_ab<T>("'123' in b"                  ,"aaa","aaa123",T(1.0)),
                             test_ab<T>("(a < b) or (a == b)"         ,"aaa","bbb",T(1.0)),
                             test_ab<T>("(a == b) or (a < b)"         ,"aaa","bbb",T(1.0)),
                             test_ab<T>("(b > a) or (b == a)"         ,"aaa","bbb",T(1.0)),
                             test_ab<T>("(b == a) or (b > a)"         ,"aaa","bbb",T(1.0)),
                             test_ab<T>("(a < b) and (b > a)"         ,"aaa","bbb",T(1.0)),
                             test_ab<T>("a like '*123*'"              ,"a123b","",T(1.0)),
                             test_ab<T>("a like '*123?'"              ,"a123b","",T(1.0)),
                             test_ab<T>("'a123b' like b"              ,"a123b","*123*",T(1.0)),
                             test_ab<T>("'a123b' like b"              ,"a123b","*123?",T(1.0)),
                             test_ab<T>("a ilike '*xyz*'"             ,"1XYZ2","",T(1.0)),
                             test_ab<T>("a ilike '*xyz?'"             ,"1XYZ2","",T(1.0)),
                             test_ab<T>("'1XYZ2' ilike b"             ,"","*xyz*",T(1.0)),
                             test_ab<T>("'1XYZ2' ilike b"             ,"","*xyz?",T(1.0)),
                             test_ab<T>("inrange(a,'bbb',c)"          ,"aaa","bbb",T(1.0)),
                             test_ab<T>("inrange('aaa',b,'ccc')"      ,"aaa","bbb",T(1.0)),
                             test_ab<T>("inrange(a,b,c)"              ,"aaa","bbb",T(1.0)),
                             test_ab<T>("inrange(a,b,'ccc')"          ,"aaa","bbb",T(1.0)),
                             test_ab<T>("inrange('aaa',b,c)"          ,"aaa","bbb",T(1.0)),
                             test_ab<T>("inrange('aaa',b,c)"          ,"aaa","bbb",T(1.0)),
                             test_ab<T>("(a < b ? a : b) == a"           ,"aaa","bbb",T(1.0)),
                             test_ab<T>("(a > b ? a : b) == b"           ,"aaa","bbb",T(1.0)),
                             test_ab<T>("(a == (a + '1') ? a : b) == b"  ,"aaa","bbb",T(1.0)),
                             test_ab<T>("((a + '2') != a ? a : b) == a"  ,"aaa","bbb",T(1.0)),
                             test_ab<T>("(a < b ? a + '1' : b) == 'aaa1'","aaa","bbb",T(1.0)),
                             test_ab<T>("(a > b ? a : b + '2') == 'bbb2'","aaa","bbb",T(1.0)),
                             test_ab<T>("b == (a == (a + '1') ? a : b)"  ,"aaa","bbb",T(1.0)),
                             test_ab<T>("a == (a != (a + '2') ? a : b)"  ,"aaa","bbb",T(1.0)),
                             test_ab<T>("'aaa1' == (a < b ? a + '1' : b)","aaa","bbb",T(1.0)),
                             test_ab<T>("'bbb2' == (a > b ? a : b + '2')","aaa","bbb",T(1.0)),
                             test_ab<T>("(a < b ? a[1:2] : b) == '23'"   ,"1234","67890",T(1.0)),
                             test_ab<T>("(a > b ? a : b[0:3]) == '6789'" ,"1234","67890",T(1.0)),
                             test_ab<T>("~{var x := 'xxx'; var y := 'yyy';~{(x < y ? x : y) == x           }}","","",T(1.0)),
                             test_ab<T>("~{var x := 'xxx'; var y := 'yyy';~{(x > y ? x : y) == y           }}","","",T(1.0)),
                             test_ab<T>("~{var x := 'xxx'; var y := 'yyy';~{(x == (x + '1') ? x : y) == y  }}","","",T(1.0)),
                             test_ab<T>("~{var x := 'xxx'; var y := 'yyy';~{((x + '2') != x ? x : y) == x  }}","","",T(1.0)),
                             test_ab<T>("~{var x := 'xxx'; var y := 'yyy';~{(x < y ? x + '1' : y) == 'xxx1'}}","","",T(1.0)),
                             test_ab<T>("~{var x := 'xxx'; var y := 'yyy';~{(x > y ? x : y + '2') == 'yyy2'}}","","",T(1.0)),
                             test_ab<T>("~{var x := 'xxx'; var y := 'yyy';~{y == (x == (x + '1') ? x : y)  }}","","",T(1.0)),
                             test_ab<T>("~{var x := 'xxx'; var y := 'yyy';~{x == (x != (x + '2') ? x : y)  }}","","",T(1.0)),
                             test_ab<T>("~{var x := 'xxx'; var y := 'yyy';~{'xxx1' == (x < y ? x + '1' : y)}}","","",T(1.0)),
                             test_ab<T>("~{var x := 'xxx'; var y := 'yyy';~{'yyy2' == (x > y ? x : y + '2')}}","","",T(1.0)),
                             test_ab<T>("'01234567890123456789'[0:9] == '0123456789'    ","","",T(1.0)),
                             test_ab<T>("'01234567890123456789'[0:9] == '0123456789'[:] ","","",T(1.0)),
                             test_ab<T>("'01234567890123456789'[0:9] == '0123456789'[0:]","","",T(1.0)),
                             test_ab<T>("'01234567890123456789'[0:9] == '0123456789'[:9]","","",T(1.0)),
                             test_ab<T>("'01234567890123456789'[:9]  == '0123456789'[:9]","","",T(1.0)),
                             test_ab<T>("'01234567890123456789'[10:] == '0123456789'[:] ","","",T(1.0)),
                             test_ab<T>("'01234567890123456789'[0:9] != '123456789'     ","","",T(1.0)),
                             test_ab<T>("'01234567890123456789'[0:9] != '123456789'[:]  ","","",T(1.0)),
                             test_ab<T>("'01234567890123456789'[0:9] != '123456789'[0:] ","","",T(1.0)),
                             test_ab<T>("'01234567890123456789'[0:9] != '123456789'[:8] ","","",T(1.0)),
                             test_ab<T>("'01234567890123456789'[:9]  != '123456789'[:8] ","","",T(1.0)),
                             test_ab<T>("'01234567890123456789'[10:] != '123456789'[:]  ","","",T(1.0)),
                             test_ab<T>("'01234567890123456789'[2*6:10+6] == '23456'    ","","",T(1.0)),
                             test_ab<T>("'0123456789'     == '01234567890123456789'[0:9]","","",T(1.0)),
                             test_ab<T>("'0123456789'[:]  == '01234567890123456789'[0:9]","","",T(1.0)),
                             test_ab<T>("'0123456789'[0:] == '01234567890123456789'[0:9]","","",T(1.0)),
                             test_ab<T>("'0123456789'[:9] == '01234567890123456789'[0:9]","","",T(1.0)),
                             test_ab<T>("'0123456789'[:9] == '01234567890123456789'[:9] ","","",T(1.0)),
                             test_ab<T>("'0123456789'[:]  == '01234567890123456789'[10:]","","",T(1.0)),
                             test_ab<T>("'0123456789'[3:3] == '3'[:]                    ","","",T(1.0)),
                             test_ab<T>("'0123456789'[3:3] == '3'[0:0]                  ","","",T(1.0)),
                             test_ab<T>("'123456789'      != '01234567890123456789'[0:9]","","",T(1.0)),
                             test_ab<T>("'123456789'[:]   != '01234567890123456789'[0:9]","","",T(1.0)),
                             test_ab<T>("'123456789'[0:]  != '01234567890123456789'[0:9]","","",T(1.0)),
                             test_ab<T>("'123456789'[:8]  != '01234567890123456789'[0:9]","","",T(1.0)),
                             test_ab<T>("'123456789'[:8]  != '01234567890123456789'[:9] ","","",T(1.0)),
                             test_ab<T>("'123456789'[:]   != '01234567890123456789'[10:]","","",T(1.0)),
                             test_ab<T>("'23456' == '01234567890123456789'[2*6:10+6]    ","","",T(1.0)),
                             test_ab<T>("'01234567890123456789'[r0: 6]   == '23456'              ","","",T(1.0)),
                             test_ab<T>("'01234567890123456789'[2: r1]   == '23456'              ","","",T(1.0)),
                             test_ab<T>("'01234567890123456789'[r0:3*2]  == '23456'              ","","",T(1.0)),
                             test_ab<T>("'01234567890123456789'[1+1:r1]  == '23456'              ","","",T(1.0)),
                             test_ab<T>("'01234567890123456789'[r0:  ]   == '234567890123456789' ","","",T(1.0)),
                             test_ab<T>("'01234567890123456789'[:  r1]   == '0123456'            ","","",T(1.0)),
                             test_ab<T>("'01234567890123456789'[r0:r1]   == '23456'              ","","",T(1.0)),
                             test_ab<T>("'01234567890123456789'[r0:r1+2] == '2345678'            ","","",T(1.0)),
                             test_ab<T>("'01234567890123456789'[r0+2:r1] == '456'                ","","",T(1.0)),
                             test_ab<T>("'01234567890123456789'[r1-r0:]  == '4567890123456789'   ","","",T(1.0)),
                             test_ab<T>("'01234567890123456789'[:r1-r0]  == '01234'              ","","",T(1.0)),
                             test_ab<T>("'23456'              == '01234567890123456789'[r0: 6]   ","","",T(1.0)),
                             test_ab<T>("'23456'              == '01234567890123456789'[2: r1]   ","","",T(1.0)),
                             test_ab<T>("'23456'              == '01234567890123456789'[r0:3*2]  ","","",T(1.0)),
                             test_ab<T>("'23456'              == '01234567890123456789'[1+1:r1]  ","","",T(1.0)),
                             test_ab<T>("'234567890123456789' == '01234567890123456789'[r0:  ]   ","","",T(1.0)),
                             test_ab<T>("'0123456'            == '01234567890123456789'[:  r1]   ","","",T(1.0)),
                             test_ab<T>("'23456'              == '01234567890123456789'[r0:r1]   ","","",T(1.0)),
                             test_ab<T>("'2345678'            == '01234567890123456789'[r0:r1+2] ","","",T(1.0)),
                             test_ab<T>("'456'                == '01234567890123456789'[r0+2:r1] ","","",T(1.0)),
                             test_ab<T>("'4567890123456789'   == '01234567890123456789'[r1-r0:]  ","","",T(1.0)),
                             test_ab<T>("'01234'              == '01234567890123456789'[:r1-r0]  ","","",T(1.0)),
                             test_ab<T>("a[r0: 6]   == '23456'              ","01234567890123456789","",T(1.0)),
                             test_ab<T>("a[2: r1]   == '23456'              ","01234567890123456789","",T(1.0)),
                             test_ab<T>("a[r0:3*2]  == '23456'              ","01234567890123456789","",T(1.0)),
                             test_ab<T>("a[1+1:r1]  == '23456'              ","01234567890123456789","",T(1.0)),
                             test_ab<T>("a[r0:  ]   == '234567890123456789' ","01234567890123456789","",T(1.0)),
                             test_ab<T>("a[:  r1]   == '0123456'            ","01234567890123456789","",T(1.0)),
                             test_ab<T>("a[r0:r1]   == '23456'              ","01234567890123456789","",T(1.0)),
                             test_ab<T>("a[r0:r1+2] == '2345678'            ","01234567890123456789","",T(1.0)),
                             test_ab<T>("a[r0+2:r1] == '456'                ","01234567890123456789","",T(1.0)),
                             test_ab<T>("a[r1-r0:]  == '4567890123456789'   ","01234567890123456789","",T(1.0)),
                             test_ab<T>("a[:r1-r0]  == '01234'              ","01234567890123456789","",T(1.0)),
                             test_ab<T>("'23456'              == a[r0: 6]   ","01234567890123456789","",T(1.0)),
                             test_ab<T>("'23456'              == a[2: r1]   ","01234567890123456789","",T(1.0)),
                             test_ab<T>("'23456'              == a[r0:3*2]  ","01234567890123456789","",T(1.0)),
                             test_ab<T>("'23456'              == a[1+1:r1]  ","01234567890123456789","",T(1.0)),
                             test_ab<T>("'234567890123456789' == a[r0:  ]   ","01234567890123456789","",T(1.0)),
                             test_ab<T>("'0123456'            == a[:  r1]   ","01234567890123456789","",T(1.0)),
                             test_ab<T>("'23456'              == a[r0:r1]   ","01234567890123456789","",T(1.0)),
                             test_ab<T>("'2345678'            == a[r0:r1+2] ","01234567890123456789","",T(1.0)),
                             test_ab<T>("'456'                == a[r0+2:r1] ","01234567890123456789","",T(1.0)),
                             test_ab<T>("'4567890123456789'   == a[r1-r0:]  ","01234567890123456789","",T(1.0)),
                             test_ab<T>("'01234'              == a[:r1-r0]  ","01234567890123456789","",T(1.0)),
                             test_ab<T>("a[r0: 6]   == b                    ","01234567890123456789","23456",T(1.0)),
                             test_ab<T>("a[2: r1]   == b                    ","01234567890123456789","23456",T(1.0)),
                             test_ab<T>("a[r0:3*2]  == b                    ","01234567890123456789","23456",T(1.0)),
                             test_ab<T>("a[1+1:r1]  == b                    ","01234567890123456789","23456",T(1.0)),
                             test_ab<T>("a[r0:  ]   == b                    ","01234567890123456789","234567890123456789",T(1.0)),
                             test_ab<T>("a[:  r1]   == b                    ","01234567890123456789","0123456",T(1.0)),
                             test_ab<T>("a[r0:r1]   == b                    ","01234567890123456789","23456",T(1.0)),
                             test_ab<T>("a[r0:r1+2] == b                    ","01234567890123456789","2345678",T(1.0)),
                             test_ab<T>("a[r0+2:r1] == b                    ","01234567890123456789","456",T(1.0)),
                             test_ab<T>("a[r1-r0:]  == b                    ","01234567890123456789","4567890123456789",T(1.0)),
                             test_ab<T>("a[:r1-r0]  == b                    ","01234567890123456789","01234",T(1.0)),
                             test_ab<T>("b == a[r0: 6]                      ","01234567890123456789","23456",T(1.0)),
                             test_ab<T>("b == a[2: r1]                      ","01234567890123456789","23456",T(1.0)),
                             test_ab<T>("b == a[r0:3*2]                     ","01234567890123456789","23456",T(1.0)),
                             test_ab<T>("b == a[1+1:r1]                     ","01234567890123456789","23456",T(1.0)),
                             test_ab<T>("b == a[r0:  ]                      ","01234567890123456789","234567890123456789",T(1.0)),
                             test_ab<T>("b == a[:  r1]                      ","01234567890123456789","0123456",T(1.0)),
                             test_ab<T>("b == a[r0:r1]                      ","01234567890123456789","23456",T(1.0)),
                             test_ab<T>("b == a[r0:r1+2]                    ","01234567890123456789","2345678",T(1.0)),
                             test_ab<T>("b == a[r0+2:r1]                    ","01234567890123456789","456",T(1.0)),
                             test_ab<T>("b == a[r1-r0:]                     ","01234567890123456789","4567890123456789",T(1.0)),
                             test_ab<T>("b == a[:r1-r0]                     ","01234567890123456789","01234",T(1.0)),
                             test_ab<T>("'01234567890123456789'[0:9] == a     ","0123456789","",T(1.0)),
                             test_ab<T>("'01234567890123456789'[0:9] == a[:]  ","0123456789","",T(1.0)),
                             test_ab<T>("'01234567890123456789'[0:9] == a[0:] ","0123456789","",T(1.0)),
                             test_ab<T>("'01234567890123456789'[0:9] == a[:9] ","0123456789","",T(1.0)),
                             test_ab<T>("'01234567890123456789'[:9]  == a[:9] ","0123456789","",T(1.0)),
                             test_ab<T>("'01234567890123456789'[10:] == a[:]  ","0123456789","",T(1.0)),
                             test_ab<T>("'01234567890123456789'[0:9] != a     ","123456789" ,"",T(1.0)),
                             test_ab<T>("'01234567890123456789'[0:9] != a[:]  ","123456789" ,"",T(1.0)),
                             test_ab<T>("'01234567890123456789'[0:9] != a[0:] ","123456789" ,"",T(1.0)),
                             test_ab<T>("'01234567890123456789'[0:9] != a[:8] ","123456789" ,"",T(1.0)),
                             test_ab<T>("'01234567890123456789'[:9]  != a[:8] ","123456789" ,"",T(1.0)),
                             test_ab<T>("'01234567890123456789'[10:] != a[:]  ","123456789" ,"",T(1.0)),
                             test_ab<T>("'01234567890123456789'[2*6:10+6] == a","23456"     ,"",T(1.0)),
                             test_ab<T>("'23456' == a[:]                      ","23456"     ,"",T(1.0)),
                             test_ab<T>("a     == '01234567890123456789'[0:9] ","0123456789","",T(1.0)),
                             test_ab<T>("a[:]  == '01234567890123456789'[0:9] ","0123456789","",T(1.0)),
                             test_ab<T>("a[0:] == '01234567890123456789'[0:9] ","0123456789","",T(1.0)),
                             test_ab<T>("a[:9] == '01234567890123456789'[0:9] ","0123456789","",T(1.0)),
                             test_ab<T>("a[:9] == '01234567890123456789'[:9]  ","0123456789","",T(1.0)),
                             test_ab<T>("a[:]  == '01234567890123456789'[10:] ","0123456789","",T(1.0)),
                             test_ab<T>("a     != '01234567890123456789'[0:9] ","123456789" ,"",T(1.0)),
                             test_ab<T>("a[:]  != '01234567890123456789'[0:9] ","123456789" ,"",T(1.0)),
                             test_ab<T>("a[0:] != '01234567890123456789'[0:9] ","123456789" ,"",T(1.0)),
                             test_ab<T>("a[:8] != '01234567890123456789'[0:9] ","123456789" ,"",T(1.0)),
                             test_ab<T>("a[:8] != '01234567890123456789'[:9]  ","123456789" ,"",T(1.0)),
                             test_ab<T>("a[:]  != '01234567890123456789'[10:] ","123456789" ,"",T(1.0)),
                             test_ab<T>("a == '01234567890123456789'[2*6:10+6]","23456"     ,"",T(1.0)),
                             test_ab<T>("a[:] == '23456'                      ","23456"     ,"",T(1.0)),
                             test_ab<T>("a[0:9] == b      ","01234567890123456789","0123456789",T(1.0)),
                             test_ab<T>("a[0:9] == b[:]   ","01234567890123456789","0123456789",T(1.0)),
                             test_ab<T>("a[0:9] == b[0:]  ","01234567890123456789","0123456789",T(1.0)),
                             test_ab<T>("a[0:9] == b[:9]  ","01234567890123456789","0123456789",T(1.0)),
                             test_ab<T>("a[:9]  == b[:9]  ","01234567890123456789","0123456789",T(1.0)),
                             test_ab<T>("a[10:] == b[:]   ","01234567890123456789","0123456789",T(1.0)),
                             test_ab<T>("a[0:9] != b      ","01234567890123456789","123456789" ,T(1.0)),
                             test_ab<T>("a[0:9] != b[:]   ","01234567890123456789","123456789" ,T(1.0)),
                             test_ab<T>("a[0:9] != b[0:]  ","01234567890123456789","123456789" ,T(1.0)),
                             test_ab<T>("a[0:9] != b[:8]  ","01234567890123456789","123456789" ,T(1.0)),
                             test_ab<T>("a[:9]  != b[:8]  ","01234567890123456789","123456789" ,T(1.0)),
                             test_ab<T>("a[10:] != b[:]   ","01234567890123456789","123456789" ,T(1.0)),
                             test_ab<T>("a[2*6:10+6] == b ","01234567890123456789","23456"     ,T(1.0)),
                             test_ab<T>("b     == a[0:9]  ","01234567890123456789","0123456789",T(1.0)),
                             test_ab<T>("b[:]  == a[0:9]  ","01234567890123456789","0123456789",T(1.0)),
                             test_ab<T>("b[0:] == a[0:9]  ","01234567890123456789","0123456789",T(1.0)),
                             test_ab<T>("b[:9] == a[0:9]  ","01234567890123456789","0123456789",T(1.0)),
                             test_ab<T>("b[:9] == a[:9]   ","01234567890123456789","0123456789",T(1.0)),
                             test_ab<T>("b[:]  == a[10:]  ","01234567890123456789","0123456789",T(1.0)),
                             test_ab<T>("b     != a[0:9]  ","01234567890123456789","123456789" ,T(1.0)),
                             test_ab<T>("b[:]  != a[0:9]  ","01234567890123456789","123456789" ,T(1.0)),
                             test_ab<T>("b[0:] != a[0:9]  ","01234567890123456789","123456789" ,T(1.0)),
                             test_ab<T>("b[:8] != a[0:9]  ","01234567890123456789","123456789" ,T(1.0)),
                             test_ab<T>("b[:8] != a[:9]   ","01234567890123456789","123456789" ,T(1.0)),
                             test_ab<T>("b[:]  != a[10:]  ","01234567890123456789","123456789" ,T(1.0)),
                             test_ab<T>("b == a[2*6:10+6] ","01234567890123456789","23456"     ,T(1.0)),
                             test_ab<T>("a[2:6] == b"         ,"0123456789","23456"  ,T(1.0)),
                             test_ab<T>("a == b[2:6]"         ,"23456","0123456789"  ,T(1.0)),
                             test_ab<T>("a[1+1:2*3] == b"     ,"0123456789","23456"  ,T(1.0)),
                             test_ab<T>("a == b[4/2:sqrt(36)]","23456","0123456789"  ,T(1.0)),
                             test_ab<T>("a[0:6] == b"         ,"0123456789","0123456",T(1.0)),
                             test_ab<T>("a[:6] == b"          ,"0123456789","0123456",T(1.0)),
                             test_ab<T>("a[4/2-2:2+4] == b"   ,"0123456789","0123456",T(1.0)),
                             test_ab<T>("a[:12/2] == b"       ,"0123456789","0123456",T(1.0)),
                             test_ab<T>("a[0:] == b"          ,"0123456","0123456"   ,T(1.0)),
                             test_ab<T>("a[:] == b"           ,"0123456","0123456"   ,T(1.0)),
                             test_ab<T>("a == b[0:6]"         ,"0123456","0123456789",T(1.0)),
                             test_ab<T>("a == b[:6]"          ,"0123456","0123456789",T(1.0)),
                             test_ab<T>("a == b[4/2-2:2+4]"   ,"0123456","0123456789",T(1.0)),
                             test_ab<T>("a == b[:12/2]"       ,"0123456","0123456789",T(1.0)),
                             test_ab<T>("a == b[0:]"          ,"0123456","0123456"   ,T(1.0)),
                             test_ab<T>("a == b[:]"           ,"0123456","0123456"   ,T(1.0)),
                             test_ab<T>("a[:9] == b[0:9]"     ,"0123456789","01234567890123456789",T(1.0)),
                             test_ab<T>("a[0:9] == b[0:9]"    ,"0123456789","01234567890123456789",T(1.0)),
                             test_ab<T>("a[0:] == b[0:9]"     ,"0123456789","01234567890123456789",T(1.0)),
                             test_ab<T>("a[:] == b[0:9]"      ,"0123456789","01234567890123456789",T(1.0)),
                             test_ab<T>("a[:] == b[10:]"      ,"0123456789","01234567890123456789",T(1.0)),
                             test_ab<T>("'!@#$%^&*([{}])-=' != ')]}{[(*&^%$#@!'","","",T(1.0)),
                             test_ab<T>("('!@#$%^&*([{}])-=') != (')]}{[(*&^%$#@!')","","",T(1.0)),
                             test_ab<T>("{[('a')]} == [{('a')}]","","",T(1.0)),
                             test_ab<T>("{[('!@#$%^&*([{}])-=')]} != [{(')]}{[(*&^%$#@!')}]","","",T(1.0)),
                             test_ab<T>("'!@#$%^&*([{}])-=' == '!@#$%^&*([{}])-='","","",T(1.0)),
                             test_ab<T>("('!@#$%^&*([{}])-=') == ('!@#$%^&*([{}])-=')","","",T(1.0)),
                             test_ab<T>("{[('!@#$%^&*([{}])-=')]} == [{('!@#$%^&*([{}])-=')}]","","",T(1.0)),
                             test_ab<T>("'1234\\\\abc\nxyz\r890\tqaz\\'567' == a","1234\\abc\nxyz\r890\tqaz'567","",T(1.0)),
                             test_ab<T>("a == '1234\\\\abc\nxyz\r890\tqaz\\'567'","1234\\abc\nxyz\r890\tqaz'567","",T(1.0)),
                             test_ab<T>("'123'[] == 3"                       ,"",""               ,T(1.0)),
                             test_ab<T>("3 == '123'[]"                       ,"",""               ,T(1.0)),
                             test_ab<T>("'123'[] + '1234'[] == 7"            ,"",""               ,T(1.0)),
                             test_ab<T>("abs('123'[] - '1234'[]) == 1"       ,"",""               ,T(1.0)),
                             test_ab<T>("'1234'[] == a[]"                    ,"1234",""           ,T(1.0)),
                             test_ab<T>("'123'[] + a[] == 7"                 ,"1234",""           ,T(1.0)),
                             test_ab<T>("abs(a[] - '12345'[]) == 1"          ,"1234",""           ,T(1.0)),
                             test_ab<T>("'1234'[] + '12345'[] == a[] + b[]"  ,"1234","12345"      ,T(1.0)),
                             test_ab<T>("abs('123'[] -'1234'[]) == abs(a[] - b[])" ,"1234","12345",T(1.0)),
                             test_ab<T>("(a + b)      == 'abc123'            ","abc","123"        ,T(1.0)),
                             test_ab<T>("(a + '123')  == 'abc123'            ","abc","123"        ,T(1.0)),
                             test_ab<T>("('abc' + b)  == 'abc123'            ","abc","123"        ,T(1.0)),
                             test_ab<T>("(a + '1')    == 'abc1'              ","abc","123"        ,T(1.0)),
                             test_ab<T>("('a' + b)    == 'a123'              ","abc","123"        ,T(1.0)),
                             test_ab<T>("(a[2:7] + b) == 'cdefgh0123'        ","abcdefghij","0123",T(1.0)),
                             test_ab<T>("(a + b[2:7]) == 'abc234567'         ","abc","0123456789" ,T(1.0)),
                             test_ab<T>("(a[2:7] + '0123') == 'cdefgh0123'   ","abcdefghij","0123",T(1.0)),
                             test_ab<T>("('abc' + b[2:7])  == 'abc234567'    ","abc","0123456789" ,T(1.0)),
                             test_ab<T>("(a[2:2] + b[3:3]) == 'c3'           ","abc","0123456789" ,T(1.0)),
                             test_ab<T>("(a[3:] + b) == 'defghij0123'        ","abcdefghij","0123",T(1.0)),
                             test_ab<T>("('abc' + b[:7])   == 'abc01234567'  ","abc","0123456789" ,T(1.0)),
                             test_ab<T>("a + '123'  == 'abc'+ b              ","abc"   , "123"   , T(1.0)),
                             test_ab<T>("a[0:2] + '123' == 'abc' + b[0:2]    ","abcXYZ", "123XYZ", T(1.0)),
                             test_ab<T>("a[ :2] + '123' == 'abc' + b[ :2]    ","abcXYZ", "123XYZ", T(1.0)),
                             test_ab<T>("a[3:       ] + '123' == 'abc' + b[3:       ]","XYZabc", "XYZ123", T(1.0)),
                             test_ab<T>("a[3:a[] - 1] + '123' == 'abc' + b[3:b[] - 1]","XYZabc", "XYZ123", T(1.0)),
                             test_ab<T>("(a[r0:r2] + b) == 'cdefgh0123'      ","abcdefghij","0123",T(1.0)),
                             test_ab<T>("(a + b[r0:r2]) == 'abc234567'       ","abc","0123456789" ,T(1.0)),
                             test_ab<T>("(a[r0:r2] + '0123') == 'cdefgh0123' ","abcdefghij","0123",T(1.0)),
                             test_ab<T>("('abc' + b[r0:r2])  == 'abc234567'  ","abc","0123456789" ,T(1.0)),
                             test_ab<T>("(a[r0:r0] + b[r3:r3]) == 'c3'       ","abc","0123456789" ,T(1.0)),
                             test_ab<T>("(a[r3:] + b) == 'defghij0123'       ","abcdefghij","0123",T(1.0)),
                             test_ab<T>("('abc' + b[:r2]) == 'abc01234567'   ","abc","0123456789" ,T(1.0)),
                             test_ab<T>("a[0:r0] + '123' == 'abc' + b[0:r0]  ","abcXYZ", "123XYZ", T(1.0)),
                             test_ab<T>("a[ :r0] + '123' == 'abc' + b[ :r0]  ","abcXYZ", "123XYZ", T(1.0)),
                             test_ab<T>("a[r3:       ] + '123' == 'abc' + b[r3:       ]","XYZabc", "XYZ123", T(1.0)),
                             test_ab<T>("a[r3:a[] - 1] + '123' == 'abc' + b[r3:b[] - 1]","XYZabc", "XYZ123", T(1.0)),
                             test_ab<T>("(a[r0:r0] + b[r3:r0+1]) == 'c3'     ","abc","0123456789" ,T(1.0)),
                             test_ab<T>("(a[r0+1:] + b) == 'defghij0123'     ","abcdefghij","0123",T(1.0)),
                             test_ab<T>("a[r0+1:       ] + '123' == 'abc' + b[r0+1:       ]","XYZabc", "XYZ123", T(1.0)),
                             test_ab<T>("a[r0+1:a[] - 1] + '123' == 'abc' + b[r0+1:b[] - 1]","XYZabc", "XYZ123", T(1.0)),
                             test_ab<T>("(a + b)[  :13] == 'abcdefghij0123'             ", "abcdefghij", "0123456789" ,T(1.0)),
                             test_ab<T>("(a + b)[ 6:  ] == 'ghij0123456789'             ", "abcdefghij", "0123456789" ,T(1.0)),
                             test_ab<T>("(a + b)[ 2:3r1-1] == 'cdefghij01234567'        ", "abcdefghij", "0123456789" ,T(1.0)),
                             test_ab<T>("(a[2:7] + b[2:7])      == 'cdefgh234567'       ", "abcdefghij", "0123456789" ,T(1.0)),
                             test_ab<T>("(a[2:7] + b[2:7])[3:8] == 'fgh234'             ", "abcdefghij", "0123456789" ,T(1.0)),
                             test_ab<T>("(a + b)[r0 - 2: r1 + r2] == 'abcdefghij0123'   ", "abcdefghij", "0123456789" ,T(1.0)),
                             test_ab<T>("(a + b)[r0*r3:] == 'ghij0123456789'            ", "abcdefghij", "0123456789" ,T(1.0)),
                             test_ab<T>("(a + b)[3r0:  ] == 'ghij0123456789'            ", "abcdefghij", "0123456789" ,T(1.0)),
                             test_ab<T>("(a + b)[2r3:  ] == 'ghij0123456789'            ", "abcdefghij", "0123456789" ,T(1.0)),
                             test_ab<T>("(a + b)[2:3r1 - 1]  == 'cdefghij01234567'      ", "abcdefghij", "0123456789" ,T(1.0)),
                             test_ab<T>("(a[r0:7] + b[r0:r2])== 'cdefgh234567'          ", "abcdefghij", "0123456789" ,T(1.0)),
                             test_ab<T>("(a[r1 / r3:7] + b[r0:r2])[3:r2 + 1] == 'fgh234'", "abcdefghij", "0123456789" ,T(1.0)),
                             test_ab<T>("(a += b)      == 'abc123'                      ", "abc","123"       ,T(1.0)),
                             test_ab<T>("(a += '123')  == 'abc123'                      ", "abc","123"       ,T(1.0)),
                             test_ab<T>("(a += b[3:5]) == 'abc123'                      ", "abc","XXX123XXX" ,T(1.0)),
                             test_ab<T>("(a += 'XXX123XXX'[3:5]) == 'abc123'            ", "abc","123"       ,T(1.0)),
                             test_ab<T>("(a += b)[:]      == 'abc123'                   ", "abc","123"       ,T(1.0)),
                             test_ab<T>("(a += '123')[:]  == 'abc123'                   ", "abc","123"       ,T(1.0)),
                             test_ab<T>("(a += b[3:5])[:] == 'abc123'                   ", "abc","XXX123XXX" ,T(1.0)),
                             test_ab<T>("(a += 'XXX123XXX'[3:5])[:] == 'abc123'         ", "abc","123"       ,T(1.0)),
                             test_ab<T>("(a += b[r1/2:r1-1]) == 'abc123'                ", "abc","XXX123XXX" ,T(1.0)),
                             test_ab<T>("(a += 'XXX123XXX'[r0+1:r1-1]) == 'abc123'      ", "abc","123"       ,T(1.0)),
                             test_ab<T>("(a += b)[]      == 6                           ", "abc","123"       ,T(1.0)),
                             test_ab<T>("(a += '123')[]  == 6                           ", "abc","123"       ,T(1.0)),
                             test_ab<T>("(a += b[3:5])[] == 6                           ", "abc","XXX123XXX" ,T(1.0)),
                             test_ab<T>("(a += b[r0+1:r1-1])[] == 6                     ", "abc","XXX123XXX" ,T(1.0)),
                             test_ab<T>("(a + b)[:][]                  == 6             ","abc","123"        ,T(1.0)),
                             test_ab<T>("(a + b)[:][:][]               == 6             ","abc","123"        ,T(1.0)),
                             test_ab<T>("(a + b)[:][:][:][]            == 6             ","abc","123"        ,T(1.0)),
                             test_ab<T>("(a + b)[:][:][:][:][]         == 6             ","abc","123"        ,T(1.0)),
                             test_ab<T>("(a + b)[:][:][:][:][:][]      == 6             ","abc","123"        ,T(1.0)),
                             test_ab<T>("(a + b)[:][:][:][:][:][:][]   == 6             ","abc","123"        ,T(1.0)),
                             test_ab<T>("(a + b)[:][:][:][:][:][:][:][]== 6             ","abc","123"        ,T(1.0)),
                             test_ab<T>("(a + b)[0:5]                  == 'abc123'      ","abc","123"        ,T(1.0)),
                             test_ab<T>("(a + b)[0:5][1:4]             == 'bc12'        ","abc","123"        ,T(1.0)),
                             test_ab<T>("(a + b)[0:5][1:4][1:2]        == 'c1'          ","abc","123"        ,T(1.0)),
                             test_ab<T>("(a + b)[0:5][1:4][1:2][0:0]   == 'c'           ","abc","123"        ,T(1.0)),
                             test_ab<T>("(a + b)[0:5][]                == 6             ","abc","123"        ,T(1.0)),
                             test_ab<T>("(a + b)[0:5][1:4][]           == 4             ","abc","123"        ,T(1.0)),
                             test_ab<T>("(a + b)[0:5][1:4][1:2][]      == 2             ","abc","123"        ,T(1.0)),
                             test_ab<T>("(a + b)[0:5][1:4][1:2][0:0][] == 1             ","abc","123"        ,T(1.0)),
                             test_ab<T>("(a[ : ] := b); (a == 'ABCDEFGHIJ');", "0123456789","ABCDEFGHIJ"     ,T(1.0)),
                             test_ab<T>("(a[0: ] := b); (a == 'ABCDEFGHIJ');", "0123456789","ABCDEFGHIJ"     ,T(1.0)),
                             test_ab<T>("(a[ :9] := b); (a == 'ABCDEFGHIJ');", "0123456789","ABCDEFGHIJ"     ,T(1.0)),
                             test_ab<T>("(a[3:7] := b); (a == '012ABCDE89');", "0123456789","ABCDEFGHIJ"     ,T(1.0)),
                             test_ab<T>("(a[2:8] := b); (a == '01ABCDEFG9');", "0123456789","ABCDEFGHIJ"     ,T(1.0)),
                             test_ab<T>("(a[1:9] := b); (a == '0ABCDEFGHI');", "0123456789","ABCDEFGHIJ"     ,T(1.0)),
                             test_ab<T>("(a[0:0] := b); (a == 'A123456789');", "0123456789","ABCDEFGHIJ"     ,T(1.0)),
                             test_ab<T>("(a[1:1] := b); (a == '0A23456789');", "0123456789","ABCDEFGHIJ"     ,T(1.0)),
                             test_ab<T>("(a[2:2] := b); (a == '01A3456789');", "0123456789","ABCDEFGHIJ"     ,T(1.0)),
                             test_ab<T>("(a[3:3] := b); (a == '012A456789');", "0123456789","ABCDEFGHIJ"     ,T(1.0)),
                             test_ab<T>("(a[4:4] := b); (a == '0123A56789');", "0123456789","ABCDEFGHIJ"     ,T(1.0)),
                             test_ab<T>("(a[5:5] := b); (a == '01234A6789');", "0123456789","ABCDEFGHIJ"     ,T(1.0)),
                             test_ab<T>("(a[6:6] := b); (a == '012345A789');", "0123456789","ABCDEFGHIJ"     ,T(1.0)),
                             test_ab<T>("(a[7:7] := b); (a == '0123456A89');", "0123456789","ABCDEFGHIJ"     ,T(1.0)),
                             test_ab<T>("(a[8:8] := b); (a == '01234567A9');", "0123456789","ABCDEFGHIJ"     ,T(1.0)),
                             test_ab<T>("(a[9:9] := b); (a == '012345678A');", "0123456789","ABCDEFGHIJ"     ,T(1.0)),
                             test_ab<T>("(a[0:1] := b); (a == 'AB23456789');", "0123456789","ABCDEFGHIJ"     ,T(1.0)),
                             test_ab<T>("(a[1:2] := b); (a == '0AB3456789');", "0123456789","ABCDEFGHIJ"     ,T(1.0)),
                             test_ab<T>("(a[2:3] := b); (a == '01AB456789');", "0123456789","ABCDEFGHIJ"     ,T(1.0)),
                             test_ab<T>("(a[3:4] := b); (a == '012AB56789');", "0123456789","ABCDEFGHIJ"     ,T(1.0)),
                             test_ab<T>("(a[4:5] := b); (a == '0123AB6789');", "0123456789","ABCDEFGHIJ"     ,T(1.0)),
                             test_ab<T>("(a[5:6] := b); (a == '01234AB789');", "0123456789","ABCDEFGHIJ"     ,T(1.0)),
                             test_ab<T>("(a[6:7] := b); (a == '012345AB89');", "0123456789","ABCDEFGHIJ"     ,T(1.0)),
                             test_ab<T>("(a[7:8] := b); (a == '0123456AB9');", "0123456789","ABCDEFGHIJ"     ,T(1.0)),
                             test_ab<T>("(a[8:9] := b); (a == '01234567AB');", "0123456789","ABCDEFGHIJ"     ,T(1.0)),
                             test_ab<T>("(a[ : ] := b[3:b[] - 3]); (a == 'ABCDEFGHIJ');", "0123456789","xyzABCDEFGHIJxyz",T(1.0)),
                             test_ab<T>("(a[0: ] := b[3:b[] - 3]); (a == 'ABCDEFGHIJ');", "0123456789","xyzABCDEFGHIJxyz",T(1.0)),
                             test_ab<T>("(a[ :9] := b[3:b[] - 3]); (a == 'ABCDEFGHIJ');", "0123456789","xyzABCDEFGHIJxyz",T(1.0)),
                             test_ab<T>("(a[3:7] := b[3:b[] - 3]); (a == '012ABCDE89');", "0123456789","xyzABCDEFGHIJxyz",T(1.0)),
                             test_ab<T>("(a[2:8] := b[3:b[] - 3]); (a == '01ABCDEFG9');", "0123456789","xyzABCDEFGHIJxyz",T(1.0)),
                             test_ab<T>("(a[1:9] := b[3:b[] - 3]); (a == '0ABCDEFGHI');", "0123456789","xyzABCDEFGHIJxyz",T(1.0)),
                             test_ab<T>("(a[0:0] := b[3:b[] - 3]); (a == 'A123456789');", "0123456789","xyzABCDEFGHIJxyz",T(1.0)),
                             test_ab<T>("(a[1:1] := b[3:b[] - 3]); (a == '0A23456789');", "0123456789","xyzABCDEFGHIJxyz",T(1.0)),
                             test_ab<T>("(a[2:2] := b[3:b[] - 3]); (a == '01A3456789');", "0123456789","xyzABCDEFGHIJxyz",T(1.0)),
                             test_ab<T>("(a[3:3] := b[3:b[] - 3]); (a == '012A456789');", "0123456789","xyzABCDEFGHIJxyz",T(1.0)),
                             test_ab<T>("(a[4:4] := b[3:b[] - 3]); (a == '0123A56789');", "0123456789","xyzABCDEFGHIJxyz",T(1.0)),
                             test_ab<T>("(a[5:5] := b[3:b[] - 3]); (a == '01234A6789');", "0123456789","xyzABCDEFGHIJxyz",T(1.0)),
                             test_ab<T>("(a[6:6] := b[3:b[] - 3]); (a == '012345A789');", "0123456789","xyzABCDEFGHIJxyz",T(1.0)),
                             test_ab<T>("(a[7:7] := b[3:b[] - 3]); (a == '0123456A89');", "0123456789","xyzABCDEFGHIJxyz",T(1.0)),
                             test_ab<T>("(a[8:8] := b[3:b[] - 3]); (a == '01234567A9');", "0123456789","xyzABCDEFGHIJxyz",T(1.0)),
                             test_ab<T>("(a[9:9] := b[3:b[] - 3]); (a == '012345678A');", "0123456789","xyzABCDEFGHIJxyz",T(1.0)),
                             test_ab<T>("(a[0:1] := b[3:b[] - 3]); (a == 'AB23456789');", "0123456789","xyzABCDEFGHIJxyz",T(1.0)),
                             test_ab<T>("(a[1:2] := b[3:b[] - 3]); (a == '0AB3456789');", "0123456789","xyzABCDEFGHIJxyz",T(1.0)),
                             test_ab<T>("(a[2:3] := b[3:b[] - 3]); (a == '01AB456789');", "0123456789","xyzABCDEFGHIJxyz",T(1.0)),
                             test_ab<T>("(a[3:4] := b[3:b[] - 3]); (a == '012AB56789');", "0123456789","xyzABCDEFGHIJxyz",T(1.0)),
                             test_ab<T>("(a[4:5] := b[3:b[] - 3]); (a == '0123AB6789');", "0123456789","xyzABCDEFGHIJxyz",T(1.0)),
                             test_ab<T>("(a[5:6] := b[3:b[] - 3]); (a == '01234AB789');", "0123456789","xyzABCDEFGHIJxyz",T(1.0)),
                             test_ab<T>("(a[6:7] := b[3:b[] - 3]); (a == '012345AB89');", "0123456789","xyzABCDEFGHIJxyz",T(1.0)),
                             test_ab<T>("(a[7:8] := b[3:b[] - 3]); (a == '0123456AB9');", "0123456789","xyzABCDEFGHIJxyz",T(1.0)),
                             test_ab<T>("(a[8:9] := b[3:b[] - 3]); (a == '01234567AB');", "0123456789","xyzABCDEFGHIJxyz",T(1.0)),
                             test_ab<T>("(a[0:9] := b); (a == 'A123456789');", "0123456789","A"         ,T(1.0)),
                             test_ab<T>("(a[0:9] := b); (a == 'AB23456789');", "0123456789","AB"        ,T(1.0)),
                             test_ab<T>("(a[0:9] := b); (a == 'ABC3456789');", "0123456789","ABC"       ,T(1.0)),
                             test_ab<T>("(a[0:9] := b); (a == 'ABCD456789');", "0123456789","ABCD"      ,T(1.0)),
                             test_ab<T>("(a[0:9] := b); (a == 'ABCDE56789');", "0123456789","ABCDE"     ,T(1.0)),
                             test_ab<T>("(a[0:9] := b); (a == 'ABCDEF6789');", "0123456789","ABCDEF"    ,T(1.0)),
                             test_ab<T>("(a[0:9] := b); (a == 'ABCDEFG789');", "0123456789","ABCDEFG"   ,T(1.0)),
                             test_ab<T>("(a[0:9] := b); (a == 'ABCDEFGH89');", "0123456789","ABCDEFGH"  ,T(1.0)),
                             test_ab<T>("(a[0:9] := b); (a == 'ABCDEFGHI9');", "0123456789","ABCDEFGHI" ,T(1.0)),
                             test_ab<T>("(a[3:9] := b); (a == '012A456789');", "0123456789","A"         ,T(1.0)),
                             test_ab<T>("(a[3:9] := b); (a == '012AB56789');", "0123456789","AB"        ,T(1.0)),
                             test_ab<T>("(a[3:9] := b); (a == '012ABC6789');", "0123456789","ABC"       ,T(1.0)),
                             test_ab<T>("(a[3:9] := b); (a == '012ABCD789');", "0123456789","ABCD"      ,T(1.0)),
                             test_ab<T>("(a[3:9] := b); (a == '012ABCDE89');", "0123456789","ABCDE"     ,T(1.0)),
                             test_ab<T>("(a[3:9] := b); (a == '012ABCDEF9');", "0123456789","ABCDEF"    ,T(1.0)),
                             test_ab<T>("(a[r1 / r0:r2] := b[3:b[] - r3]);  (a == '012ABCDE89');", "0123456789","xyzABCDEFGHIJxyz",T(1.0)),
                             test_ab<T>("(a[r0:r2 + 1]  := b[r3:b[] - r3]); (a == '01ABCDEFG9');", "0123456789","xyzABCDEFGHIJxyz",T(1.0)),
                             test_ab<T>("'\\0x30\\0x31\\0x32\\0x33\\0x34\\0x35\\0x36\\0x37\\0x38\\0x39' == '0123456789'","","",T(1.0)),
                             test_ab<T>("'abc\\0x30\\0x31\\0x32\\0x33xyz' == 'abc0123xyz'"       ,"","",T(1.0)),
                             test_ab<T>("'\\0x30\\n\\0x31\\n\\0x32\\n\\0x33' == '0\\n1\\n2\\n3'" ,"","",T(1.0)),
                             test_ab<T>("('\\0x30' + '') == '0'"                                 ,"","",T(1.0)),
                             test_ab<T>("('\\0x30' + '\\0x31\\0x32') == '012'"                   ,"","",T(1.0)),
                             test_ab<T>("('\\0x30' + '\\0x31\\0x32' + '\\0x33\\0x34\\0x35') == '012345'" ,"","",T(1.0)),
                             test_ab<T>("'a\\'\\\\b' == a" ,"a'\\b","",T(1.0)),
                             test_ab<T>("'a\\\\\\'b' == a" ,"a\\'b","",T(1.0)),
                             test_ab<T>("'a\\'\\\\\\\\b' == a" ,"a'\\\\b","",T(1.0)),
                             test_ab<T>("'a\\0x30\\'\\0x31\\\\\\0x32b' == a" ,"a0'1\\2b","",T(1.0)),

                             test_ab<T>("var x := 3; x > 2 and 'abc' like  '*bc'"   ,"","",T(1.0)),
                             test_ab<T>("var x := 3; x > 2 and 'abc' ilike '*Bc'"   ,"","",T(1.0)),
                             test_ab<T>("var x := 3; x > 2 and 'abc' in '123abc123'","","",T(1.0)),

                             test_ab<T>("var x := 3; var s := 'abc'; x > 2 and s like  '*bc'"   ,"","",T(1.0)),
                             test_ab<T>("var x := 3; var s := 'abc'; x > 2 and s ilike '*Bc'"   ,"","",T(1.0)),
                             test_ab<T>("var x := 3; var s := 'abc'; x > 2 and s in '123abc123'","","",T(1.0)),

                             test_ab<T>("var x := 3; var s := 'abc'; var t := '*bc'; x > 2 and s like  t"   ,"","",T(1.0)),
                             test_ab<T>("var x := 3; var s := 'abc'; var t := '*Bc'; x > 2 and s ilike t"   ,"","",T(1.0)),
                             test_ab<T>("var x := 3; var s := 'abc'; var t := '123abc123'; x > 2 and s in t","","",T(1.0)),

                             test_ab<T>("var x := 3; x > 2 and a like  '*bc'"   ,"abc","",T(1.0)),
                             test_ab<T>("var x := 3; x > 2 and a ilike '*Bc'"   ,"abc","",T(1.0)),
                             test_ab<T>("var x := 3; x > 2 and a in '123abc123'","abc","",T(1.0)),

                             test_ab<T>("var x := 3; x > 2 and a like b ","abc","*bc",T(1.0)),
                             test_ab<T>("var x := 3; x > 2 and a ilike b","abc","*Bc",T(1.0)),
                             test_ab<T>("var x := 3; x > 2 and a in b   ","abc","123abc123",T(1.0)),

                             test_ab<T>("a[] > 2 and a like  '*bc'"   ,"abc","",T(1.0)),
                             test_ab<T>("a[] > 2 and a ilike '*Bc'"   ,"abc","",T(1.0)),
                             test_ab<T>("a[] > 2 and a in '123abc123'","abc","",T(1.0)),

                             test_ab<T>("a[] > 2 and a like b ","abc","*bc",T(1.0)),
                             test_ab<T>("a[] > 2 and a ilike b","abc","*Bc",T(1.0)),
                             test_ab<T>("a[] > 2 and a in b   ","abc","123abc123",T(1.0)),

                             test_ab<T>("a[0:0] := b[ :]; a == '0XXXX'", "XXXXX","01234567890",T(1.0)),
                             test_ab<T>("a[0:1] := b[ :]; a == '01XXX'", "XXXXX","01234567890",T(1.0)),
                             test_ab<T>("a[0:2] := b[ :]; a == '012XX'", "XXXXX","01234567890",T(1.0)),
                             test_ab<T>("a[0:3] := b[ :]; a == '0123X'", "XXXXX","01234567890",T(1.0)),
                             test_ab<T>("a[0:4] := b[ :]; a == '01234'", "XXXXX","01234567890",T(1.0)),
                             test_ab<T>("a[0:0] := b[6:]; a == '6XXXX'", "XXXXX","01234567890",T(1.0)),
                             test_ab<T>("a[0:1] := b[6:]; a == '67XXX'", "XXXXX","01234567890",T(1.0)),
                             test_ab<T>("a[0:2] := b[6:]; a == '678XX'", "XXXXX","01234567890",T(1.0)),
                             test_ab<T>("a[0:3] := b[6:]; a == '6789X'", "XXXXX","01234567890",T(1.0)),
                             test_ab<T>("a[0:4] := b[6:]; a == '67890'", "XXXXX","01234567890",T(1.0)),
                             test_ab<T>("a[0:0] <=> b[ :]; (a == '0XXXX') and (b == 'X1234567890')", "XXXXX","01234567890",T(1.0)),
                             test_ab<T>("a[0:1] <=> b[ :]; (a == '01XXX') and (b == 'XX234567890')", "XXXXX","01234567890",T(1.0)),
                             test_ab<T>("a[0:2] <=> b[ :]; (a == '012XX') and (b == 'XXX34567890')", "XXXXX","01234567890",T(1.0)),
                             test_ab<T>("a[0:3] <=> b[ :]; (a == '0123X') and (b == 'XXXX4567890')", "XXXXX","01234567890",T(1.0)),
                             test_ab<T>("a[0:4] <=> b[ :]; (a == '01234') and (b == 'XXXXX567890')", "XXXXX","01234567890",T(1.0)),
                             test_ab<T>("a[0:0] <=> b[6:]; (a == '6XXXX') and (b == '012345X7890')", "XXXXX","01234567890",T(1.0)),
                             test_ab<T>("a[0:1] <=> b[6:]; (a == '67XXX') and (b == '012345XX890')", "XXXXX","01234567890",T(1.0)),
                             test_ab<T>("a[0:2] <=> b[6:]; (a == '678XX') and (b == '012345XXX90')", "XXXXX","01234567890",T(1.0)),
                             test_ab<T>("a[0:3] <=> b[6:]; (a == '6789X') and (b == '012345XXXX0')", "XXXXX","01234567890",T(1.0)),
                             test_ab<T>("a[0:4] <=> b[6:]; (a == '67890') and (b == '012345XXXXX')", "XXXXX","01234567890",T(1.0)),
                             test_ab<T>("var i := 0; a[0:i+0] :=  b[:]; a == '0XXXX'", "XXXXX","01234567890",T(1.0)),
                             test_ab<T>("var i := 0; a[0:i+1] :=  b[:]; a == '01XXX'", "XXXXX","01234567890",T(1.0)),
                             test_ab<T>("var i := 0; a[0:i+2] :=  b[:]; a == '012XX'", "XXXXX","01234567890",T(1.0)),
                             test_ab<T>("var i := 0; a[0:i+3] :=  b[:]; a == '0123X'", "XXXXX","01234567890",T(1.0)),
                             test_ab<T>("var i := 0; a[0:i+4] :=  b[:]; a == '01234'", "XXXXX","01234567890",T(1.0)),
                             test_ab<T>("var i := 0; a[0:i+0] <=> b[:]; (a == '0XXXX') and (b == 'X1234567890')", "XXXXX","01234567890",T(1.0)),
                             test_ab<T>("var i := 0; a[0:i+1] <=> b[:]; (a == '01XXX') and (b == 'XX234567890')", "XXXXX","01234567890",T(1.0)),
                             test_ab<T>("var i := 0; a[0:i+2] <=> b[:]; (a == '012XX') and (b == 'XXX34567890')", "XXXXX","01234567890",T(1.0)),
                             test_ab<T>("var i := 0; a[0:i+3] <=> b[:]; (a == '0123X') and (b == 'XXXX4567890')", "XXXXX","01234567890",T(1.0)),
                             test_ab<T>("var i := 0; a[0:i+4] <=> b[:]; (a == '01234') and (b == 'XXXXX567890')", "XXXXX","01234567890",T(1.0)),

                             test_ab<T>("var x := 'XXXXX'; var y := '01234567890'; x[0:0] := y[:]; x == '0XXXX'", "","",T(1.0)),
                             test_ab<T>("var x := 'XXXXX'; var y := '01234567890'; x[0:1] := y[:]; x == '01XXX'", "","",T(1.0)),
                             test_ab<T>("var x := 'XXXXX'; var y := '01234567890'; x[0:2] := y[:]; x == '012XX'", "","",T(1.0)),
                             test_ab<T>("var x := 'XXXXX'; var y := '01234567890'; x[0:3] := y[:]; x == '0123X'", "","",T(1.0)),
                             test_ab<T>("var x := 'XXXXX'; var y := '01234567890'; x[0:4] := y[:]; x == '01234'", "","",T(1.0)),
                             test_ab<T>("var x := 'XXXXX'; var y := '01234567890'; x[0:0] := y[6:]; x == '6XXXX'", "","",T(1.0)),
                             test_ab<T>("var x := 'XXXXX'; var y := '01234567890'; x[0:1] := y[6:]; x == '67XXX'", "","",T(1.0)),
                             test_ab<T>("var x := 'XXXXX'; var y := '01234567890'; x[0:2] := y[6:]; x == '678XX'", "","",T(1.0)),
                             test_ab<T>("var x := 'XXXXX'; var y := '01234567890'; x[0:3] := y[6:]; x == '6789X'", "","",T(1.0)),
                             test_ab<T>("var x := 'XXXXX'; var y := '01234567890'; x[0:4] := y[6:]; x == '67890'", "","",T(1.0)),
                             test_ab<T>("var x := 'XXXXX'; var y := '01234567890'; x[0:0] <=> y[:]; (x == '0XXXX') and (y == 'X1234567890')", "","",T(1.0)),
                             test_ab<T>("var x := 'XXXXX'; var y := '01234567890'; x[0:1] <=> y[:]; (x == '01XXX') and (y == 'XX234567890')", "","",T(1.0)),
                             test_ab<T>("var x := 'XXXXX'; var y := '01234567890'; x[0:2] <=> y[:]; (x == '012XX') and (y == 'XXX34567890')", "","",T(1.0)),
                             test_ab<T>("var x := 'XXXXX'; var y := '01234567890'; x[0:3] <=> y[:]; (x == '0123X') and (y == 'XXXX4567890')", "","",T(1.0)),
                             test_ab<T>("var x := 'XXXXX'; var y := '01234567890'; x[0:4] <=> y[:]; (x == '01234') and (y == 'XXXXX567890')", "","",T(1.0)),
                             test_ab<T>("var x := 'XXXXX'; var y := '01234567890'; x[0:0] <=> y[6:]; (x == '6XXXX') and (y == '012345X7890')", "","",T(1.0)),
                             test_ab<T>("var x := 'XXXXX'; var y := '01234567890'; x[0:1] <=> y[6:]; (x == '67XXX') and (y == '012345XX890')", "","",T(1.0)),
                             test_ab<T>("var x := 'XXXXX'; var y := '01234567890'; x[0:2] <=> y[6:]; (x == '678XX') and (y == '012345XXX90')", "","",T(1.0)),
                             test_ab<T>("var x := 'XXXXX'; var y := '01234567890'; x[0:3] <=> y[6:]; (x == '6789X') and (y == '012345XXXX0')", "","",T(1.0)),
                             test_ab<T>("var x := 'XXXXX'; var y := '01234567890'; x[0:4] <=> y[6:]; (x == '67890') and (y == '012345XXXXX')", "","",T(1.0)),
                             test_ab<T>("var x := 'XXXXX'; var y := '01234567890'; var i := 0; x[0:i+0] := y[:]; x == '0XXXX'", "","",T(1.0)),
                             test_ab<T>("var x := 'XXXXX'; var y := '01234567890'; var i := 0; x[0:i+1] := y[:]; x == '01XXX'", "","",T(1.0)),
                             test_ab<T>("var x := 'XXXXX'; var y := '01234567890'; var i := 0; x[0:i+2] := y[:]; x == '012XX'", "","",T(1.0)),
                             test_ab<T>("var x := 'XXXXX'; var y := '01234567890'; var i := 0; x[0:i+3] := y[:]; x == '0123X'", "","",T(1.0)),
                             test_ab<T>("var x := 'XXXXX'; var y := '01234567890'; var i := 0; x[0:i+4] := y[:]; x == '01234'", "","",T(1.0)),
                             test_ab<T>("var x := 'XXXXX'; var y := '01234567890'; var i := 0; x[0:i+0] <=> y[:]; (x == '0XXXX') and (y == 'X1234567890')", "","",T(1.0)),
                             test_ab<T>("var x := 'XXXXX'; var y := '01234567890'; var i := 0; x[0:i+1] <=> y[:]; (x == '01XXX') and (y == 'XX234567890')", "","",T(1.0)),
                             test_ab<T>("var x := 'XXXXX'; var y := '01234567890'; var i := 0; x[0:i+2] <=> y[:]; (x == '012XX') and (y == 'XXX34567890')", "","",T(1.0)),
                             test_ab<T>("var x := 'XXXXX'; var y := '01234567890'; var i := 0; x[0:i+3] <=> y[:]; (x == '0123X') and (y == 'XXXX4567890')", "","",T(1.0)),
                             test_ab<T>("var x := 'XXXXX'; var y := '01234567890'; var i := 0; x[0:i+4] <=> y[:]; (x == '01234') and (y == 'XXXXX567890')", "","",T(1.0)),

                             test_ab<T>("var v[4] := {1,2,3,4}; for (var i := 0; i < v[]; i += 1) { v[i] += 10; v[i] == 0 }; sum(v) == (1 + 2 + 3 + 4) + (v[] * 10)", "","",T(1.0)),
                             test_ab<T>("var v[4] := {1,2,3,4}; for (var i := 0; i < v[]; i += 1) { v[i] -= 10; v[i] == 0 }; sum(v) == (1 + 2 + 3 + 4) - (v[] * 10)", "","",T(1.0)),
                             test_ab<T>("var v[4] := {1,2,3,4}; for (var i := 0; i < v[]; i += 1) { v[i] *= 10; v[i] == 0 }; sum(v) == (1 + 2 + 3 + 4) * 10", "","",T(1.0)),
                             test_ab<T>("var v[4] := {1,2,3,4}; for (var i := 0; i < v[]; i += 1) { v[i] /= 10; v[i] == 0 }; sum(v) == (1 + 2 + 3 + 4) / 10", "","",T(1.0)),

                             test_ab<T>("a like b", "abcd", "abcd*", T(1.0)),
                             test_ab<T>("a like b", "abcd", "abcd" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "abc*" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "*bcd" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "abc?" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "?bcd" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "ab?d" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "ab*d" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "a?cd" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "a*cd" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "a??d" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "a*?d" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "*bc*" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "?bc?" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "????" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "a???" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "ab??" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "abc?" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "???d" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "??cd" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "?bcd" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "?b?d" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "a?c?" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "a??d" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "?bc?" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "ab**" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "ab*?" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "a***" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "**cd" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "*?cd" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "***d" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "*bc*" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "*bc?" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "*b??" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "?bc*" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "??c*" , T(1.0)),
                             test_ab<T>("a like b", "abcd", "*b?*" , T(1.0)),
                             test_ab<T>("a like b", "ab"  , "a*"   , T(1.0)),
                             test_ab<T>("a like b", "ab"  , "a?"   , T(1.0)),

                             test_ab<T>("a ilike b", "aBcD", "abcd*", T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "abcd" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "abc*" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "*bcd" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "abc?" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "?bcd" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "ab?d" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "ab*d" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "a?cd" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "a*cd" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "a??d" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "a*?d" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "*bc*" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "?bc?" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "????" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "a???" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "ab??" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "abc?" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "???d" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "??cd" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "?bcd" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "?b?d" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "a?c?" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "a??d" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "?bc?" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "ab**" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "ab*?" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "a***" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "**cd" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "*?cd" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "***d" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "*bc*" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "*bc?" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "*b??" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "?bc*" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "??c*" , T(1.0)),
                             test_ab<T>("a ilike b", "aBcD", "*b?*" , T(1.0)),
                             test_ab<T>("a ilike b", "aB"  , "a*"   , T(1.0)),
                             test_ab<T>("a ilike b", "aB"  , "a?"   , T(1.0))
                           };

   static const std::size_t test_list_size = sizeof(test_list) / sizeof(test_ab<T>);

   {
      const std::size_t rounds = 50;

      for (std::size_t r = 0; r < rounds; ++r)
      {
         bool result = true;

         for (std::size_t i = 0; i < test_list_size; ++i)
         {
            test_ab<T>& test = const_cast<test_ab<T>&>(test_list[i]);

            std::string str_a;
            std::string str_b;
            std::string str_c;

            T r0 = T(2);
            T r1 = T(6);
            T r2 = T(7);
            T r3 = T(3);

            exprtk::symbol_table<T> symbol_table;
            symbol_table.add_stringvar("a", str_a);
            symbol_table.add_stringvar("b", str_b);
            symbol_table.add_stringvar("c", str_c);
            symbol_table.add_variable("r0", r0);
            symbol_table.add_variable("r1", r1);
            symbol_table.add_variable("r2", r2);
            symbol_table.add_variable("r3", r3);

            exprtk::expression<T> expression;
            expression.register_symbol_table(symbol_table);

            {
               exprtk::parser<T> parser;

               if (!parser.compile(test.expr, expression))
               {
                  printf("run_test02() - Error: %s   Expression: %s\n",
                         parser.error().c_str(),
                         test.expr.c_str());

                  result = false;
                  continue;
               }
            }

            str_a = test.a;
            str_b = test.b;
            str_c = test.c;

            T expr_result = expression.value();

            if (not_equal(expr_result, test.result))
            {
               printf("run_test02() - Computation Error:  Expression: [%s]\tExpected: %19.15f\tResult: %19.15f\t"
                      "a='%s'\tb='%s'\tc='%s'\n",
                      test.expr.c_str(),
                      (double)test.result,
                      (double)expr_result,
                      str_a.c_str(),
                      str_b.c_str(),
                      str_c.c_str());

               result = false;
               continue;
            }
         }

         if (!result)
         {
            return false;
         }
      }
   }

   {
      std::string s0;
      std::string s1;

      const std::string expression_str =
                          " s0 := 'abc';                     "
                          " s0 := (s1 := '0123456789'[2:7]); "
                          " s1 := 'xyz';                     "
                          " s0 < s1;                         ";

      exprtk::symbol_table<T> symbol_table;
      symbol_table.add_stringvar("s0" ,s0);
      symbol_table.add_stringvar("s1" ,s1);

      exprtk::expression<T> expression;
      expression.register_symbol_table(symbol_table);

      {
         exprtk::parser<T> parser;

         if (!parser.compile(expression_str,expression))
         {
            printf("run_test02() - [2] Error: %s   Expression: %s\n",
                   parser.error().c_str(),
                   expression_str.c_str());

            return false;
         }
      }

      if (T(0) == expression.value())
      {
         printf("run_test02() - Evaluation Error [2]:  Expression: [%s]\tExpected: True\n",
                expression_str.c_str());

         return false;
      }
      else if ("234567" != s0)
      {
         printf("run_test02() - Evaluation Error [2]:  Expression: [%s]\tInvalid value for s0\n",
                expression_str.c_str());

         return false;
      }
      else if ("xyz" != s1)
      {
         printf("run_test02() - Evaluation Error [2]:  Expression: [%s]\tInvalid value for s1\n",
                expression_str.c_str());

         return false;
      }
   }

   return true;
}

template <typename T>
inline bool run_test03()
{
   typedef exprtk::symbol_table<T> symbol_table_t;
   typedef exprtk::expression<T>     expression_t;
   typedef exprtk::parser<T>             parser_t;

   std::string expression_string = "A+A0+aA+Aa0+b+B1+Bb+bB1+A+A0+AA+AA0+B+B1+BB+BB1+a+a0+aa+aa0+b+b1+bb+bb1+"
                                   "c+C2+Cc+Cc2+D+D3+dD+dD3+C+C2+CC+CC2+D+D3+DD+DD3+c+c2+cc+cc2+d+d3+dd+dd3+"
                                   "E+E4+eE+Ee4+f+F5+Ff+fF5+E+E4+EE+EE4+F+F5+FF+FF5+e+e4+ee+ee4+f+f5+ff+ff5+"
                                   "g+G6+Gg+Gg6+H+H7+hH+hH7+G+G6+GG+GG6+H+H7+HH+HH7+g+g6+gg+gg6+h+h7+hh+hh7+"
                                   "I+I8+iI+Ii8+j+J9+Jj+jJ9+I+I8+II+II8+J+J9+JJ+JJ9+i+i8+ii+ii8+j+j9+jj+jj9+"
                                   "k+K0+Kk+Kk0+L+L1+lL+lL1+K+K0+KK+KK0+L+L1+LL+LL1+k+k0+kk+kk0+l+l1+ll+ll1+"
                                   "M+M2+mM+Mm2+n+N3+Nn+nN3+M+M2+MM+MM2+N+N3+NN+NN3+m+m2+mm+mm2+n+n3+nn+nn3+"
                                   "o+O4+Oo+Oo4+P+P5+pP+pP5+O+O4+OO+OO4+P+P5+PP+PP5+o+o4+oo+oo4+p+p5+pp+pp5+"
                                   "Q+Q6+qQ+Qq6+r+R7+Rr+rR7+Q+Q6+QQ+QQ6+R+R7+RR+RR7+q+q6+qq+qq6+r+r7+rr+rr7+"
                                   "s+S8+Ss+Ss8+T+T9+tT+tT9+S+S8+SS+SS8+T+T9+TT+TT9+s+s8+ss+ss8+t+t9+tt+tt9+"
                                   "U+U0+uU+Uu0+v+V1+Vv+vV1+U+U0+UU+UU0+V+V1+VV+VV1+u+u0+uu+uu0+v+v1+vv+vv1+"
                                   "w+W2+Ww+Ww2+X+X3+xX+xX3+W+W2+WW+WW2+X+X3+XX+XX3+w+w2+ww+ww2+x+x3+xx+xx3+"
                                   "Y+Y4+yY+Yy4+z+Z5+Zz+zZ5+Y+Y4+YY+YY4+Z+Z5+ZZ+ZZ5+y+y4+yy+yy4+z+z5+zz+zz5 ";

   static const std::string variable_list[] =
                               {
                                 "A", "A0", "aA", "Aa0", "b", "B1", "Bb", "bB1",
                                 "c", "C2", "Cc", "Cc2", "D", "D3", "dD", "dD3",
                                 "E", "E4", "eE", "Ee4", "f", "F5", "Ff", "fF5",
                                 "g", "G6", "Gg", "Gg6", "H", "H7", "hH", "hH7",
                                 "I", "I8", "iI", "Ii8", "j", "J9", "Jj", "jJ9",
                                 "k", "K0", "Kk", "Kk0", "L", "L1", "lL", "lL1",
                                 "M", "M2", "mM", "Mm2", "n", "N3", "Nn", "nN3",
                                 "o", "O4", "Oo", "Oo4", "P", "P5", "pP", "pP5",
                                 "Q", "Q6", "qQ", "Qq6", "r", "R7", "Rr", "rR7",
                                 "s", "S8", "Ss", "Ss8", "T", "T9", "tT", "tT9",
                                 "U", "U0", "uU", "Uu0", "v", "V1", "Vv", "vV1",
                                 "w", "W2", "Ww", "Ww2", "X", "X3", "xX", "xX3",
                                 "Y", "Y4", "yY", "Yy4", "z", "Z5", "Zz", "zZ5"
                               };

   static const std::size_t variable_list_size = sizeof(variable_list) / sizeof(std::string);

   static const std::size_t rounds = 300;

   for (std::size_t r = 0; r < rounds; ++r)
   {
      symbol_table_t symbol_table_0;
      symbol_table_t symbol_table_1;
      expression_t   expression;

      std::vector<T> v;
      v.resize(variable_list_size);

      for (std::size_t i = 0; i < variable_list_size; ++i)
      {
         v[i] = T(i);
         if (i & 1)
            symbol_table_0.add_variable(variable_list[i],v[i]);
         else
            symbol_table_1.add_variable(variable_list[i],v[i]);
      }

      std::size_t total_symbol_count = symbol_table_0.variable_count() +
                                       symbol_table_1.variable_count();

      if (variable_list_size != total_symbol_count)
      {
         printf("run_test03() - Error - Invalid number of variables in symbol_table!  Expected: %d  got: %d\n",
                static_cast<unsigned int>(variable_list_size),
                static_cast<unsigned int>(total_symbol_count));

         return false;
      }

      symbol_table_0.add_constants();

      expression.register_symbol_table(symbol_table_0);
      expression.register_symbol_table(symbol_table_1);

      {
         exprtk::parser<T> parser;

         if (!parser.compile(expression_string,expression))
         {
            printf("run_test03() - Error: %s   Expression: %s\n",
                   parser.error().c_str(),
                   expression_string.c_str());

            return false;
         }
      }

      expression.value();
   }

   {
      static const std::string invalid_expr[] =
                                 {
                                   "x y",
                                   "x y z",
                                   "x y z w",
                                   "x 1",
                                   "x 1 2",
                                   "x 1 2 3",
                                   "x 'abc'",
                                   "x 1 'abc'",
                                   "x 'abc' 1",
                                   "1 2",
                                   "1 2 3",
                                   "1 2 3 4",
                                   "'abc' 'xyz'",
                                   "'abc' 1",
                                   "1 'abc'",
                                   "x sin(1)",
                                   "s 'abc'",
                                   "s x",
                                   "s y",
                                   "s 1",
                                   "s 1 x",
                                   "s 1 y",
                                   "s x 1",
                                   "s y 1",
                                   "x s ",
                                   "y s ",
                                   "1 s ",
                                   "1 s x",
                                   "1 s y",
                                   "x s 1",
                                   "y s 1",
                                   "v 'abc'",
                                   "v x  ",
                                   "v y  ",
                                   "v s  ",
                                   "v 1  ",
                                   "v 1 x",
                                   "v 1 y",
                                   "v 1 s",
                                   "v x 1",
                                   "v y 1",
                                   "v s 1",
                                   "x v  ",
                                   "y v  ",
                                   "1 v  ",
                                   "1 v x",
                                   "1 v y",
                                   "x v 1",
                                   "y v 1",

                                   "(x == 'a string'                    )",
                                   "(x == 'a string'[1:2]               )",
                                   "(x == 'a string' + 'b string'       )",
                                   "(x == ('a string' + 'b string')[3:5])",
                                   "('a string' == x                    )",
                                   "('a string'[1:2] == x               )",
                                   "('a string' + 'b string' == x       )",
                                   "(('a string' + 'b string')[3:5] == x)",

                                   "var a; var b; 3in(a)+sin(b)               ",
                                   "var a; var b; sin(a)+3in(b)               ",
                                   "var a; var b; sqrt(a)<3in(8)              ",
                                   "var a; var b; (1.99-3in((b-b)))           ",
                                   "var a; var b; ((3in(sin((b+b)))/1.06)-a)  ",
                                   "var a; var b; ((sin(3in((b+b)))/1.06)-a)  ",
                                   "var a; var b; (3in(x*(y+z))+cos(x*(y-z))) ",
                                   "var a; var b; (cos(x*(y+z))+3in(x*(y-z))) ",

                                   "1++++",
                                   "1+-+-+",
                                   "1===",
                                   "1====",
                                   "[*][*][*][*][*]",

                                   "var v[1] := {}; var s0appe0 := false; repeat s0appe0 false for(){(){}}",
                                   "var v[2] := {}; repeat var s0appe0 := false; s0appe0 false for(){(){}}",
                                   "var v[3] := {}; repeat var s0appe0 := false; for(){(){}} s0appe0 false",
                                   "var v[4] := {}; repeat var s0appe0 := false; s0appe0 for(){(){}} false",
                                   "var v[5] := {}; repeat for(){(){}} var s0appe0 := false; s0appe0 false",
                                   "var v{};v ;v  60;v 60;v o5"
                                 };

      const std::size_t invalid_expr_size = sizeof(invalid_expr) / sizeof(std::string);

      {
         for (std::size_t i = 0; i < invalid_expr_size; ++i)
         {
            symbol_table_t symbol_table;
            expression_t   expression;
            parser_t       parser;

            T x = T(0);
            std::string s;
            std::vector<T> v(10, T(1.234));

            symbol_table.add_variable ("x",x);
            symbol_table.add_stringvar("s",s);
            symbol_table.add_vector   ("v",v);

            if (parser.compile(invalid_expr[i],expression))
            {
               printf("run_test03() - Error: [1] Invalid expression compiled successfuly.   Expression: %s\n",
                      invalid_expr[i].c_str());

               return false;
            }
         }
      }

      {
         T x = T(0);
         std::string s;
         std::vector<T> v(10, T(1.234));

         symbol_table_t symbol_table;
         parser_t parser;

         symbol_table.add_variable ("x",x);
         symbol_table.add_stringvar("s",s);
         symbol_table.add_vector   ("v",v);

         for (std::size_t i = 0; i < invalid_expr_size; ++i)
         {
            exprtk::expression<T> expression;

            if (parser.compile(invalid_expr[i],expression))
            {
               printf("run_test03() - Error: [2] Invalid expression compiled successfuly.   Expression: %s\n",
                      invalid_expr[i].c_str());

               return false;
            }
         }
      }

      {
         const std::string base_expression =
                              "1+(2+2(3+3(4+4cos(((((a+((x*(e-tan((cos((((((b/(tan(((1.60*a)-0.34))-0.76))-x)+y)-3.27)+a))/pi))))^a))+y)*b)-e))+e)/z)+w)+"
                              "(((b+(a/((((tan((b*((((((a-(cos((cos(tan(((a+a)*3.33)))-b))/2.52))*x)/b)+3.07)^0.86)+b)))*3.95)/0.39)*y)+a)))*a)*z)";

         const std::string mod =
                              "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789^+-/*,;:<>=%?[]{}() #&'\"\\\t\r\n";

         symbol_table_t symbol_table;
         expression_t   expression;
         parser_t       parser;

         T a = T(1.1     );
         T b = T(2.2     );
         T c = T(3.3     );
         T d = T(4.5     );
         T e = T(4.5     );
         T x = T(2.123456);
         T y = T(3.123456);
         T z = T(4.123456);
         T w = T(5.123456);

         symbol_table.add_variable("a", a);
         symbol_table.add_variable("b", b);
         symbol_table.add_variable("c", c);
         symbol_table.add_variable("d", d);
         symbol_table.add_variable("e", e);

         symbol_table.add_variable("x", x);
         symbol_table.add_variable("y", y);
         symbol_table.add_variable("z", z);
         symbol_table.add_variable("w", w);

         expression.register_symbol_table(symbol_table);

         T total = T(0);

         for (std::size_t j = 0; j < base_expression.size(); ++j)
         {
            std::string expression_str = base_expression;
            const char old_c = base_expression[j];

            for (std::size_t i = 0; i < mod.size(); ++i)
            {
               expression_str[j] = mod[i];

               if (parser.compile(expression_str, expression))
               {
                  total += expression.value();
               }
            }

            expression_str[j] = old_c;
         }

         if (total == T(12345.6789)) { printf(" "); }
      }
   }

   return true;
}

template <typename T>
inline T clamp(const T& l, const T& v, const T& u)
{
   return (v < l) ? l : ((v > u) ? u : v);
}

template <typename T>
inline bool run_test04()
{
   std::string expression_string = "clamp(-1.0,sin(2 * pi * x) + cos(y / 2 * pi),+1.0)";

   exprtk::symbol_table<T> symbol_table;
   exprtk::expression<T> expression;

   T x = T(-1000);
   T y = T(-1000);

   symbol_table.add_variable("x",x);
   symbol_table.add_variable("y",y);
   symbol_table.add_constants();

   expression.register_symbol_table(symbol_table);

   {
      exprtk::parser<T> parser;

      if (!parser.compile(expression_string,expression))
      {
         printf("run_test04() - Error: %s   Expression: %s\n",
                parser.error().c_str(),
                expression_string.c_str());

         return false;
      }
   }

   const T pi = T(3.141592653589793238462643383279502);
   const T increment = T(0.0001);

   while ((x <= T(+1000)) && (y <= T(+1000)))
   {
      T result1 = expression.value();
      T result2 = clamp<T>(-1.0,std::sin(2 * pi * x) + std::cos(y / 2 * pi),+1.0);

      if (not_equal(result1,result2))
      {
         printf("run_test04() - Computation Error:  Expression: [%s]\tExpected: %19.15f\tResult: %19.15f x:%19.15f\ty:%19.15f\n",
                expression_string.c_str(),
                (double)result1,
                (double)result2,
                (double)x,
                (double)y);

         return false;
      }

      x += increment;
      y += increment;
   }

   return true;
}

template <typename T>
inline bool run_test05()
{
   typedef exprtk::expression<T> expression_t;
   std::string expression_string = "clamp(-1.0,sin(2 * pi * x_var123) + cos(y_var123 / 2 * pi),+1.0)";

   exprtk::symbol_table<T> symbol_table;
   std::deque<expression_t> expression_list;

   T x = T(-1000);
   T y = T(-1000);

   symbol_table.add_variable("x_var123",x);
   symbol_table.add_variable("y_var123",y);
   symbol_table.add_constants();

   const std::size_t expression_count = 10;
   for (std::size_t i = 0; i < expression_count; ++i)
   {
      expression_t e;
      e.register_symbol_table(symbol_table);

      {
         exprtk::parser<T> parser;

         if (!parser.compile(expression_string,e))
         {
            printf("run_test05() - Error: %s   Expression: %s\n",
                   parser.error().c_str(),
                   expression_string.c_str());

            return false;
         }
      }

      expression_list.push_back(e);
   }

   const T pi = T(3.141592653589793238462643383279502);
   const T increment = T(0.001);

   while ((x <= T(+1000)) && (y <= T(+1000)))
   {
      T real_result = clamp<T>(-1.0,std::sin(2 * pi * x) + std::cos(y / 2 * pi),+1.0);

      for (std::size_t i = 0; i < expression_list.size(); ++i)
      {
         expression_t& expr = expression_list[i];

         T result = expr.value();

         if (not_equal(result,real_result))
         {
            printf("run_test05() - Computation Error:  Expression: [%s]\tExpected: %19.15f\tResult: %19.15f x:%19.15f\ty:%19.15f\tIndex:%d\n",
                   expression_string.c_str(),
                   (double)real_result,
                   (double)result,
                   (double)x,
                   (double)y,
                   static_cast<unsigned int>(i));

            return false;
         }
      }

      x += increment;
      y += increment;
   }

   return true;
}

template <typename T>
inline bool run_test06()
{
   typedef exprtk::expression<T> expression_t;
   std::string expression_string = "sqrt(1 - (x^2))";

   T x = T(0);

   exprtk::symbol_table<T> symbol_table;
   symbol_table.add_variable("x",x);

   expression_t expression;
   expression.register_symbol_table(symbol_table);

   {
      exprtk::parser<T> parser;

      if (!parser.compile(expression_string,expression))
      {
         printf("run_test06() - Error: %s   Expression: %s\n",
                parser.error().c_str(),
                expression_string.c_str());

         return false;
      }
   }

   T total_area1 = exprtk::integrate(expression,x,T(-1),T(1));
   T total_area2 = exprtk::integrate(expression,"x",T(-1),T(1));
   const T pi = T(3.141592653589793238462643383279502);

   if (not_equal(total_area1,total_area2,T(0.000001)))
   {
      printf("run_test06() - Integration Error:  area1 != area2\n");
      return false;
   }

   if (not_equal(total_area1,T(pi) / T(2),T(0.000001)))
   {
      printf("run_test06() - Integration Error:  Expected: %19.15f\tResult: %19.15f\n",
             (double)(pi / T(2)),
             (double)total_area1);

      return false;
   }

   return true;
}

template <typename T>
inline bool run_test07()
{
   typedef exprtk::expression<T> expression_t;
   std::string expression_string = "sin(2x + 1 / 3)";

   T x = T(0);

   exprtk::symbol_table<T> symbol_table;
   symbol_table.add_variable("x",x);

   expression_t expression;
   expression.register_symbol_table(symbol_table);

   {
      exprtk::parser<T> parser;

      if (!parser.compile(expression_string,expression))
      {
         printf("run_test07() - Error: %s   Expression: %s\n",
                parser.error().c_str(),
                expression_string.c_str());

         return false;
      }
   }

   for (x = T(-200); x < T(200); x += T(0.0001))
   {
      {
         T deriv1_real_result = T(2) * std::cos(T(2) * x + T(1.0 / 3.0));
         T deriv1_result1 = exprtk::derivative(expression,x);
         T deriv1_result2 = exprtk::derivative(expression,"x");

         if (not_equal(deriv1_result1,deriv1_result2,T(0.00001)))
         {
            printf("run_test07() - 1st Derivative Error:  result1 != result2\n");
            return false;
         }

         if (not_equal(deriv1_result1,deriv1_real_result,T(0.00001)))
         {
            printf("run_test07() - 1st Derivative Error:  x: %19.15f\tExpected: %19.15f\tResult: %19.15f\n",
                   (double)x,
                   (double)deriv1_real_result,
                   (double)deriv1_result1);

            return false;
         }
      }

      {
         T deriv2_real_result = T(-4) * std::sin(T(2) * x + T(1.0 / 3.0));
         T deriv2_result1 = exprtk::second_derivative(expression,x);
         T deriv2_result2 = exprtk::second_derivative(expression,"x");

         if (not_equal(deriv2_result1,deriv2_result2,T(0.0000001)))
         {
            printf("run_test07() - 2nd Derivative Error:  result1 != result2\n");
            return false;
         }

         if (not_equal(deriv2_result1,deriv2_real_result,T(0.01)))
         {
            printf("run_test07() - 2nd Derivative Error:  x: %19.15f\tExpected: %19.15f\tResult: %19.15f\n",
                   (double)x,
                   (double)deriv2_real_result,
                   (double)deriv2_result1);

            return false;
         }
      }

      {
         T deriv3_real_result = T(-8) * std::cos(T(2) * x + T(1.0 / 3.0));
         T deriv3_result1 = exprtk::third_derivative(expression,x);
         T deriv3_result2 = exprtk::third_derivative(expression,"x");

         if (not_equal(deriv3_result1,deriv3_result2,T(0.0000001)))
         {
            printf("run_test07() - 3rd Derivative Error:  result1 != result2\n");
            return false;
         }

         if (not_equal(deriv3_result1,deriv3_real_result,T(0.01)))
         {
            printf("run_test07() - 3rd Derivative Error:  x: %19.15f\tExpected: %19.15f\tResult: %19.15f\n",
                   (double)x,
                   (double)deriv3_real_result,
                   (double)deriv3_result1);

            return false;
         }
      }
   }

   return true;
}

template <typename T>
inline bool run_test08()
{

   static const std::string expr_str[] =
                              {
                                "x", "y", "z", "w", "u",
                                "x + y + z + w + u",
                                "x + y / z * w ^ u",
                                "x:=1.1", "y:=2.2", "z:=3.3", "w:=4.4", "u:=5.5",
                                "x:=x+1.1", "y:=y+2.2", "z:=z+3.3", "w:=w+4.4", "u:=u+5.5",
                                "x:=1.1+x", "y:=2.2+y", "z:=3.3+z", "w:=4.4+w", "u:=5.5+u",
                                "x:=(x <= 1.1)",
                                "y:=(2.2 >= y)",
                                "z:=(3.3 and z)",
                                "w:=(4.4 or w)",
                                "u:=(u xor 5.5)",
                                "min(x,y) + min(x,y,z) + min(x,y,z,w) + min(x,y,z,w,y)",
                                "max(x,y) + max(x,y,z) + max(x,y,z,w) + max(x,y,z,w,y)",
                                "avg(x,y)",
                                "avg(x,y,z)",
                                "avg(x,y,z,w)",
                                "avg(x,y,z,w,u)",
                                "(u := u := min(x:=1,y:=2,z:=3)) == 1",
                                "(2x+3y+4z+5w)==(2*x+3*y+4*z+5*w)",
                                "(3(x+y)/2+1)==(3*(x+y)/2+1)",
                                "((x+y)3+1/4)==((x+y)*3+1/4)",
                                "((x+y)z+1/2)==((x+y)*z+1/2)",
                                "(x+y^3/z) == (x+(y*y*y)/z)",
                                "(z-x^3+y^2*7) == (z-(x*x*x)+(y*y)*7)",
                                "(3min(x,y))==(3*min(x,y))",
                                "(sin(x)y)==(sin(x)*y)",
                                "(sin(x)cos(y)+1)==(sin(x)*cos(y)+1)",
                                "(sgn(sin(x))cos(sgn(y))+1)==(sgn(sin(x))*cos(sgn(y))+1)",
                                "equal($f00(x,y,z),(x+y)/z)",
                                "equal($f01(x,y,z),(x+y)*z)",
                                "equal($f02(x,y,z),(x+y)-z)",
                                "equal($f03(x,y,z),(x+y)+z)",
                                "equal($f04(x,y,z),(x-y)+z)",
                                "equal($f05(x,y,z),(x-y)/z)",
                                "equal($f06(x,y,z),(x-y)*z)",
                                "equal($f07(x,y,z),(x*y)+z)",
                                "equal($f08(x,y,z),(x*y)-z)",
                                "equal($f09(x,y,z),(x*y)/z)",
                                "equal($f10(x,y,z),(x*y)*z)",
                                "equal($f11(x,y,z),(x/y)+z)",
                                "equal($f12(x,y,z),(x/y)-z)",
                                "equal($f13(x,y,z),(x/y)/z)",
                                "equal($f14(x,y,z),(x/y)*z)",
                                "equal($f15(x,y,z),x/(y+z))",
                                "equal($f16(x,y,z),x/(y-z))",
                                "equal($f17(x,y,z),x/(y*z))",
                                "equal($f18(x,y,z),x/(y/z))",
                                "equal($f19(x,y,z),x*(y+z))",
                                "equal($f20(x,y,z),x*(y-z))",
                                "equal($f21(x,y,z),x*(y*z))",
                                "equal($f22(x,y,z),x*(y/z))",
                                "equal($f23(x,y,z),x-(y+z))",
                                "equal($f24(x,y,z),x-(y-z))",
                                "equal($f25(x,y,z),x-(y/z))",
                                "equal($f26(x,y,z),x-(y*z))",
                                "equal($f27(x,y,z),x+(y*z))",
                                "equal($f28(x,y,z),x+(y/z))",
                                "equal($f29(x,y,z),x+(y+z))",
                                "equal($f30(x,y,z),x+(y-z))",
                                "equal($f31(x,y,z),x*y^2+z)",
                                "equal($f32(x,y,z),x*y^3+z)",
                                "equal($f33(x,y,z),x*y^4+z)",
                                "equal($f34(x,y,z),x*y^5+z)",
                                "equal($f35(x,y,z),x*y^6+z)",
                                "equal($f36(x,y,z),x*y^7+z)",
                                "equal($f37(x,y,z),x*y^8+z)",
                                "equal($f38(x,y,z),x*y^9+z)",
                                "equal($f39(x,y,z),x*log(y)+z)",
                                "equal($f40(x,y,z),x*log(y)-z)",
                                "equal($f41(x,y,z),x*log10(y)+z)",
                                "equal($f42(x,y,z),x*log10(y)-z)",
                                "equal($f43(x,y,z),x*sin(y)+z)",
                                "equal($f44(x,y,z),x*sin(y)-z)",
                                "equal($f45(x,y,z),x*cos(y)+z)",
                                "equal($f46(x,y,z),x*cos(y)-z)",
                                "equal($f47(x,y,z),if(0!=x,y,z))",
                                "equal($f48(x,y,z,w),x+((y+z)/w))",
                                "equal($f49(x,y,z,w),x+((y+z)*w))",
                                "equal($f50(x,y,z,w),x+((y-z)/w))",
                                "equal($f51(x,y,z,w),x+((y-z)*w))",
                                "equal($f52(x,y,z,w),x+((y*z)/w))",
                                "equal($f53(x,y,z,w),x+((y*z)*w))",
                                "equal($f54(x,y,z,w),x+((y/z)+w))",
                                "equal($f55(x,y,z,w),x+((y/z)/w))",
                                "equal($f56(x,y,z,w),x+((y/z)*w))",
                                "equal($f57(x,y,z,w),x-((y+z)/w))",
                                "equal($f58(x,y,z,w),x-((y+z)*w))",
                                "equal($f59(x,y,z,w),x-((y-z)/w))",
                                "equal($f60(x,y,z,w),x-((y-z)*w))",
                                "equal($f61(x,y,z,w),x-((y*z)/w))",
                                "equal($f62(x,y,z,w),x-((y*z)*w))",
                                "equal($f63(x,y,z,w),x-((y/z)/w))",
                                "equal($f64(x,y,z,w),x-((y/z)*w))",
                                "equal($f65(x,y,z,w),((x+y)*z)-w)",
                                "equal($f66(x,y,z,w),((x-y)*z)-w)",
                                "equal($f67(x,y,z,w),((x*y)*z)-w)",
                                "equal($f68(x,y,z,w),((x/y)*z)-w)",
                                "equal($f69(x,y,z,w),((x+y)/z)-w)",
                                "equal($f70(x,y,z,w),((x-y)/z)-w)",
                                "equal($f71(x,y,z,w),((x*y)/z)-w)",
                                "equal($f72(x,y,z,w),((x/y)/z)-w)",
                                "equal($f73(x,y,z,w),(x*y)+(z*w))",
                                "equal($f74(x,y,z,w),(x*y)-(z*w))",
                                "equal($f75(x,y,z,w),(x*y)+(z/w))",
                                "equal($f76(x,y,z,w),(x*y)-(z/w))",
                                "equal($f77(x,y,z,w),(x/y)+(z/w))",
                                "equal($f78(x,y,z,w),(x/y)-(z/w))",
                                "equal($f79(x,y,z,w),(x/y)-(z*w))",
                                "equal($f80(x,y,z,w),x/(y+(z*w)))",
                                "equal($f81(x,y,z,w),x/(y-(z*w)))",
                                "equal($f82(x,y,z,w),x*(y+(z*w)))",
                                "equal($f83(x,y,z,w),x*(y-(z*w)))",
                                "equal($f84(x,y,z,w),x*y^2+z*w^2)",
                                "equal($f85(x,y,z,w),x*y^3+z*w^3)",
                                "equal($f86(x,y,z,w),x*y^4+z*w^4)",
                                "equal($f87(x,y,z,w),x*y^5+z*w^5)",
                                "equal($f88(x,y,z,w),x*y^6+z*w^6)",
                                "equal($f89(x,y,z,w),x*y^7+z*w^7)",
                                "equal($f90(x,y,z,w),x*y^8+z*w^8)",
                                "equal($f91(x,y,z,w),x*y^9+z*w^9)",
                                "equal($f92(x,y,z,w),if(x and y,z,w))",
                                "equal($f93(x,y,z,w),if(x or y,z,w))",
                                "equal($f94(x,y,z,w),if(x < y,z,w))",
                                "equal($f95(x,y,z,w),if(x <= y,z,w))",
                                "equal($f96(x,y,z,w),if(x > y,z,w))",
                                "equal($f97(x,y,z,w),if(x >= y,z,w))",
                                "equal($f98(x,y,z,w),if(equal(x,y),z,w))",
                                "equal($f92(x,y,z,w),x and y ? z : w)",
                                "equal($f93(x,y,z,w),x or y ? z : w)",
                                "equal($f94(x,y,z,w),x < y ? z : w)",
                                "equal($f95(x,y,z,w),x <= y ? z : w)",
                                "equal($f96(x,y,z,w),x > y ? z : w)",
                                "equal($f97(x,y,z,w),x >= y ? z : w)",
                                "equal($f98(x,y,z,w),equal(x,y) ? z : w)",
                                "equal($f99(x,y,z,w),x*sin(y)+z*cos(w))"
                              };
   static const std::size_t expr_str_size = sizeof(expr_str) / sizeof(std::string);

   static const std::size_t rounds = 25;

   for (std::size_t i = 0; i < rounds; ++i)
   {
      for (std::size_t j = 0; j < expr_str_size; ++j)
      {
         typedef exprtk::expression<T> expression_t;

         T x = T(1.12345);
         T y = T(2.12345);
         T z = T(3.12345);
         T w = T(4.12345);
         T u = T(5.12345);

         exprtk::symbol_table<T> symbol_table;
         symbol_table.add_variable("x",x);
         symbol_table.add_variable("y",y);
         symbol_table.add_variable("z",z);
         symbol_table.add_variable("w",w);
         symbol_table.add_variable("u",u);

         expression_t expression;
         expression.register_symbol_table(symbol_table);

         {
            exprtk::parser<T> parser;

            if (!parser.compile(expr_str[j],expression))
            {
               printf("run_test08() - Error: %s   Expression: %s\n",
                      parser.error().c_str(),
                      expr_str[j].c_str());

               return false;
            }
         }

         expression.value();
      }
   }

   return true;
}

template <typename T>
struct myfunc : public exprtk::ifunction<T>
{
   using exprtk::ifunction<T>::operator();

   myfunc() : exprtk::ifunction<T>(2) {}

   inline T operator()(const T& v1, const T& v2) override
   {
      return T(1) + (v1 * v2) / T(3);
   }
};

#define define_free_functions(N,Type)                                                                   \
Type N##1(Type v0) { return v0; }                                                                       \
Type N##2(Type v0, Type v1) { return v0 + v1; }                                                         \
Type N##3(Type v0, Type v1, Type v2) { return v0 + v1 + v2; }                                           \
Type N##4(Type v0, Type v1, Type v2, Type v3) { return v0 + v1 + v2 + v3; }                             \
Type N##5(Type v0, Type v1, Type v2, Type v3, Type v4) { return v0 + v1 + v2 + v3 + v4; }               \
Type N##6(Type v0, Type v1, Type v2, Type v3, Type v4, Type v5) { return v0 + v1 + v2 + v3 + v4 + v5; } \

define_free_functions(foo,numeric_type)
#undef define_free_functions

template <typename T>
inline bool run_test09()
{
   {
      static const std::size_t rounds = 1000;
      for (std::size_t i = 0; i < rounds; ++i)
      {
         typedef exprtk::expression<T> expression_t;
         std::string expression_string = "myfunc0(sin(x * pi),y / 2) + myfunc1(sin(x * pi),y / 2)+"
                                         "myfunc2(sin(x * pi),y / 2) + myfunc3(sin(x * pi),y / 2)+"
                                         "myfunc4(sin(x * pi),y / 2) + myfunc5(sin(x * pi),y / 2)+"
                                         "myfunc6(sin(x * pi),y / 2) + myfunc7(sin(x * pi),y / 2)+"
                                         "myfunc8(sin(x * pi),y / 2) + myfunc9(sin(x * pi),y / 2)+"
                                         "myfunc0(sin(x * pi),y / 2) + myfunc1(sin(x * pi),y / 2)+"
                                         "myfunc2(sin(x * pi),y / 2) + myfunc3(sin(x * pi),y / 2)+"
                                         "myfunc4(sin(x * pi),y / 2) + myfunc5(sin(x * pi),y / 2)+"
                                         "myfunc6(sin(x * pi),y / 2) + myfunc7(sin(x * pi),y / 2)+"
                                         "myfunc8(sin(x * pi),y / 2) + myfunc9(sin(x * pi),y / 2)+"
                                         "myfunc0(sin(x * pi),y / 2) + myfunc1(sin(x * pi),y / 2)+"
                                         "myfunc2(sin(x * pi),y / 2) + myfunc3(sin(x * pi),y / 2)+"
                                         "myfunc4(sin(x * pi),y / 2) + myfunc5(sin(x * pi),y / 2)+"
                                         "myfunc6(sin(x * pi),y / 2) + myfunc7(sin(x * pi),y / 2)+"
                                         "myfunc8(sin(x * pi),y / 2) + myfunc9(sin(x * pi),y / 2)+"
                                         "myfunc0(sin(x * pi),y / 2) + myfunc1(sin(x * pi),y / 2)+"
                                         "myfunc2(sin(x * pi),y / 2) + myfunc3(sin(x * pi),y / 2)+"
                                         "myfunc4(sin(x * pi),y / 2) + myfunc5(sin(x * pi),y / 2)+"
                                         "myfunc6(sin(x * pi),y / 2) + myfunc7(sin(x * pi),y / 2)+"
                                         "myfunc8(sin(x * pi),y / 2) + myfunc9(sin(x * pi),y / 2)";

         T x = T(1) + (i / T(10000));
         T y = T(2) + (i / T(10000));
         myfunc<T> mf;

         exprtk::symbol_table<T> symbol_table;
         symbol_table.add_variable("x",x);
         symbol_table.add_variable("y",y);
         symbol_table.add_function("myfunc0",mf);
         symbol_table.add_function("myfunc1",mf);
         symbol_table.add_function("myfunc2",mf);
         symbol_table.add_function("myfunc3",mf);
         symbol_table.add_function("myfunc4",mf);
         symbol_table.add_function("myfunc5",mf);
         symbol_table.add_function("myfunc6",mf);
         symbol_table.add_function("myfunc7",mf);
         symbol_table.add_function("myfunc8",mf);
         symbol_table.add_function("myfunc9",mf);
         symbol_table.add_constants();

         expression_t expression;
         expression.register_symbol_table(symbol_table);

         {
            exprtk::parser<T> parser;

            if (!parser.compile(expression_string,expression))
            {
               printf("run_test09() - Error: %s   Expression: %s\n",
                      parser.error().c_str(),
                      expression_string.c_str());

               return false;
            }
         }

         const T pi = T(3.141592653589793238462643383279502);

         T result = expression.value();

         T expected = T(4) *
                      (
                         mf(sin(x*pi),y / T(2)) +
                         mf(sin(x*pi),y / T(2)) +
                         mf(sin(x*pi),y / T(2)) +
                         mf(sin(x*pi),y / T(2)) +
                         mf(sin(x*pi),y / T(2)) +
                         mf(sin(x*pi),y / T(2)) +
                         mf(sin(x*pi),y / T(2)) +
                         mf(sin(x*pi),y / T(2)) +
                         mf(sin(x*pi),y / T(2)) +
                         mf(sin(x*pi),y / T(2))
                      );

         if (not_equal(result,expected,T(0.0000001)))
         {
            printf("run_test09() - Error Expected: %19.15f\tResult: %19.15f\n",
                   (double)expected,
                   (double)result);

            return false;
         }
      }
   }

   {
      typedef exprtk::expression<T>   expression_t;
      typedef exprtk::symbol_table<T> symbol_table_t;

      bool result = true;

      const std::string expression_list[] =
                           {
                             "foo1(1)           == 1",
                             "foo2(1,2)         == (1 + 2)",
                             "foo3(1,2,3)       == (1 + 2 + 3)",
                             "foo4(1,2,3,4)     == (1 + 2 + 3 + 4)",
                             "foo5(1,2,3,4,5)   == (1 + 2 + 3 + 4 + 5)",
                             "foo6(1,2,3,4,5,6) == (1 + 2 + 3 + 4 + 5 + 6)"
                           };

      const std::size_t expression_list_size = sizeof(expression_list) / sizeof(std::string);

      symbol_table_t symbol_table;

      symbol_table.add_function("foo1",foo1);
      symbol_table.add_function("foo2",foo2);
      symbol_table.add_function("foo3",foo3);
      symbol_table.add_function("foo4",foo4);
      symbol_table.add_function("foo5",foo5);
      symbol_table.add_function("foo6",foo6);

      for (std::size_t i = 0; i < expression_list_size; ++i)
      {
         expression_t expression;
         expression.register_symbol_table(symbol_table);

         exprtk::parser<T> parser;

         if (!parser.compile(expression_list[i],expression))
         {
            printf("run_test09() - Error: %s   Expression: %s\n",
                   parser.error().c_str(),
                   expression_list[i].c_str());

            result = false;
         }
      }

      if (!result)
         return false;
   }

   return true;
}

template <typename T>
inline bool run_test10()
{
   typedef exprtk::expression<T> expression_t;

   T  x = T(1.1);
   T  y = T(2.2);
   T xx = T(3.3);
   T yy = T(4.4);

   std::string i_s  = "A String";
   std::string j_s  = "Another String";
   std::string ii_s = "A String";
   std::string jj_s = "Another String";

   struct test
   {
      static inline bool variable(exprtk::symbol_table<T>& symbol_table, const std::string& variable_name, const T& value)
      {
         exprtk::details::variable_node<T>* var = symbol_table.get_variable(variable_name);

         if (var)
            return (!not_equal(var->ref(),value));
         else
            return false;
      }

      static inline bool string(exprtk::symbol_table<T>& symbol_table, const std::string& string_name, const std::string& str)
      {
         exprtk::details::stringvar_node<T>* str_node = symbol_table.get_stringvar(string_name);

         if (str_node)
            return (str_node->ref() == str);
         else
            return false;
      }
   };

   {
      static const std::size_t rounds = 10;

      exprtk::symbol_table<T> symbol_table;

      for (std::size_t r = 0; r < rounds; ++r)
      {
         symbol_table.add_variable("x", x);
         symbol_table.add_variable("y", y);
         symbol_table.add_variable("xx", xx);
         symbol_table.add_variable("yy", yy);

         if (!symbol_table.symbol_exists("x"))
         {
            printf("run_test10() - Symbol 'x' does not exist!\n");
            return false;
         }
         else if (!symbol_table.symbol_exists("y"))
         {
            printf("run_test10() - Symbol 'y' does not exist!\n");
            return false;
         }
         else if (!symbol_table.symbol_exists("xx"))
         {
            printf("run_test10() - Symbol 'xx' does not exist!\n");
            return false;
         }
         else if (!symbol_table.symbol_exists("yy"))
         {
            printf("run_test10() - Symbol 'yy' does not exist!\n");
            return false;
         }
         else if (!test::variable(symbol_table, "x", x))
         {
            printf("run_test10() - Symbol 'x' value failure!\n");
            return false;
         }
         else if (!test::variable(symbol_table, "y", y))
         {
            printf("run_test10() - Symbol 'y' value failure!\n");
            return false;
         }
         else if (!test::variable(symbol_table, "xx", xx))
         {
            printf("run_test10() - Symbol 'xx' value failure!\n");
            return false;
         }
         else if (!test::variable(symbol_table, "yy", yy))
         {
            printf("run_test10() - Symbol 'yy' value failure!\n");
            return false;
         }

         if (!symbol_table.remove_variable("x"))
         {
            printf("run_test10() - Failed to remove symbol 'x'!\n");
            return false;
         }
         else if (!symbol_table.remove_variable("y"))
         {
            printf("run_test10() - Failed to remove symbol 'y'!\n");
            return false;
         }
         else if (!symbol_table.remove_variable("xx"))
         {
            printf("run_test10() - Failed to remove symbol 'xx'!\n");
            return false;
         }
         else if (!symbol_table.remove_variable("yy"))
         {
            printf("run_test10() - Failed to remove symbol 'yy'!\n");
            return false;
         }
      }

      for (std::size_t r = 0; r < rounds; ++r)
      {
         myfunc<T> mf;

         symbol_table.add_function("f", mf);
         symbol_table.add_function("f1", mf);

         if (!symbol_table.symbol_exists("f"))
         {
            printf("run_test10() - function 'f' does not exist!\n");
            return false;
         }
         else if (!symbol_table.symbol_exists("f1"))
         {
            printf("run_test10() - function 'f1' does not exist!\n");
            return false;
         }

         if (!symbol_table.remove_function("f"))
         {
            printf("run_test10() - Failed to remove function 'f'!\n");
            return false;
         }
         else if (!symbol_table.remove_function("f1"))
         {
            printf("run_test10() - Failed to remove function 'f1'!\n");
            return false;
         }
      }

      for (std::size_t r = 0; r < rounds; ++r)
      {
         symbol_table.add_stringvar("i", i_s);
         symbol_table.add_stringvar("j", j_s);

         symbol_table.add_stringvar("ii", ii_s);
         symbol_table.add_stringvar("jj", jj_s);

         if (!symbol_table.symbol_exists("i"))
         {
            printf("run_test10() - String 'i' does not exist!\n");
            return false;
         }
         else if (!symbol_table.symbol_exists("j"))
         {
            printf("run_test10() - String 'j' does not exist!\n");
            return false;
         }
         else if (!symbol_table.symbol_exists("ii"))
         {
            printf("run_test10() - String 'ii' does not exist!\n");
            return false;
         }
         else if (!symbol_table.symbol_exists("jj"))
         {
            printf("run_test10() - String 'jj' does not exist!\n");
            return false;
         }
         else if (!test::string(symbol_table, "i", i_s))
         {
            printf("run_test10() - String 'i' value failure!\n");
            return false;
         }
         else if (!test::string(symbol_table, "j", j_s))
         {
            printf("run_test10() - String 'j' value failure!\n");
            return false;
         }
         else if (!test::string(symbol_table, "ii", ii_s))
         {
            printf("run_test10() - String 'ii' value failure!\n");
            return false;
         }
         else if (!test::string(symbol_table, "jj", jj_s))
         {
            printf("run_test10() - String 'jj' value failure!\n");
            return false;
         }
         else if (!symbol_table.remove_stringvar("i"))
         {
            printf("run_test10() - Failed to remove String 'i'!\n");
            return false;
         }
         else if (!symbol_table.remove_stringvar("j"))
         {
            printf("run_test10() - Failed to remove String 'j'!\n");
            return false;
         }
         else if (!symbol_table.remove_stringvar("ii"))
         {
            printf("run_test10() - Failed to remove String 'ii'!\n");
            return false;
         }
         else if (!symbol_table.remove_stringvar("jj"))
         {
            printf("run_test10() - Failed to remove String 'jj'!\n");
            return false;
         }
      }

      for (std::size_t r = 0; r < rounds; ++r)
      {
         symbol_table.add_variable("x", x);
         symbol_table.add_variable("y", y);
         symbol_table.add_variable("xx", xx);
         symbol_table.add_variable("yy", yy);

         std::vector<std::string> expected_var_list;

         expected_var_list.push_back("x");
         expected_var_list.push_back("y");
         expected_var_list.push_back("xx");
         expected_var_list.push_back("yy");

         std::deque<std::pair<std::string, T> > variable_list;

         symbol_table.get_variable_list(variable_list);

         if (variable_list.size() != expected_var_list.size())
         {
            printf("run_test10() - Failed to get variable list (1)\n");
            return false;
         }

         std::size_t found_count = 0;

         for (std::size_t i = 0; i < variable_list.size(); ++i)
         {
            for (std::size_t j = 0; j < expected_var_list.size(); ++j)
            {
               if (variable_list[i].first == expected_var_list[j])
               {
                  ++found_count;
                  break;
               }
            }
         }

         if (found_count != expected_var_list.size())
         {
            printf("run_test10() - Failed to get variable list (2)\n");
            return false;
         }
      }

      for (std::size_t r = 0; r < rounds; ++r)
      {
         symbol_table.add_variable("x", x);
         symbol_table.add_variable("y", y);
         symbol_table.add_variable("xx", xx);
         symbol_table.add_variable("yy", yy);

         std::vector<std::string> expected_var_list;

         expected_var_list.push_back("x");
         expected_var_list.push_back("y");
         expected_var_list.push_back("xx");
         expected_var_list.push_back("yy");

         std::deque<std::string> variable_list;

         symbol_table.get_variable_list(variable_list);

         if (variable_list.size() != expected_var_list.size())
         {
            printf("run_test10() - Failed to get variable list (3)\n");
            return false;
         }

         std::size_t found_count = 0;

         for (std::size_t i = 0; i < variable_list.size(); ++i)
         {
            for (std::size_t j = 0; j < expected_var_list.size(); ++j)
            {
               if (variable_list[i] == expected_var_list[j])
               {
                  ++found_count;
                  break;
               }
            }
         }

         if (found_count != expected_var_list.size())
         {
            printf("run_test10() - Failed to get variable list (4)\n");
            return false;
         }
      }

      for (std::size_t r = 0; r < rounds; ++r)
      {
         symbol_table.add_stringvar("i", i_s);
         symbol_table.add_stringvar("j", j_s);
         symbol_table.add_stringvar("ii", ii_s);
         symbol_table.add_stringvar("jj", jj_s);

         std::vector<std::string> expected_var_list;

         expected_var_list.push_back("i");
         expected_var_list.push_back("j");
         expected_var_list.push_back("ii");
         expected_var_list.push_back("jj");

         std::deque<std::pair<std::string, std::string> > stringvar_list;

         symbol_table.get_stringvar_list(stringvar_list);

         if (stringvar_list.size() != expected_var_list.size())
         {
            printf("run_test10() - Failed to get stringvar list (1)\n");
            return false;
         }

         std::size_t found_count = 0;

         for (std::size_t i = 0; i < stringvar_list.size(); ++i)
         {
            for (std::size_t j = 0; j < expected_var_list.size(); ++j)
            {
               if (stringvar_list[i].first == expected_var_list[j])
               {
                  ++found_count;
                  break;
               }
            }
         }

         if (found_count != expected_var_list.size())
         {
            printf("run_test10() - Failed to get stringvar list (2)\n");
            return false;
         }
      }

      for (std::size_t r = 0; r < rounds; ++r)
      {
         symbol_table.add_stringvar("i", i_s);
         symbol_table.add_stringvar("j", j_s);
         symbol_table.add_stringvar("ii", ii_s);
         symbol_table.add_stringvar("jj", jj_s);

         std::vector<std::string> expected_var_list;

         expected_var_list.push_back("i");
         expected_var_list.push_back("j");
         expected_var_list.push_back("ii");
         expected_var_list.push_back("jj");

         std::deque<std::string> stringvar_list;

         symbol_table.get_stringvar_list(stringvar_list);

         if (stringvar_list.size() != expected_var_list.size())
         {
            printf("run_test10() - Failed to get stringvar list (3.0)\n");
            return false;
         }

         if (symbol_table.stringvar_count() != expected_var_list.size())
         {
            printf("run_test10() - Failed to get stringvar list (3.1)\n");
            return false;
         }

         std::size_t found_count = 0;

         for (std::size_t i = 0; i < stringvar_list.size(); ++i)
         {
            for (std::size_t j = 0; j < expected_var_list.size(); ++j)
            {
               if (stringvar_list[i] == expected_var_list[j])
               {
                  ++found_count;
                  break;
               }
            }
         }

         if (found_count != expected_var_list.size())
         {
            printf("run_test10() - Failed to get stringvar list (4)\n");
            return false;
         }
      }
   }

   {
      T x0 = T(0);
      T y0 = T(0);
      T z0 = T(0);

      std::string expression_string = "(x0 + y0) / z0";

      static const std::size_t rounds = 100;

      for (std::size_t i = 0; i < rounds; ++i)
      {
         expression_t expression0;

         x0 = T(i + 1.11);
         y0 = T(i + 2.22);
         z0 = T(i + 3.33);

         exprtk::symbol_table<T> st0;

         st0.add_variable("x0",x0);
         st0.add_variable("y0",y0);
         st0.add_variable("z0",z0);

         expression0.register_symbol_table(st0);

         {
            exprtk::parser<T> parser;

            if (!parser.compile(expression_string,expression0))
            {
               printf("run_test10() - Error: %s   Expression: %s\n",
                      parser.error().c_str(),
                      expression_string.c_str());

               return false;
            }
         }

         {
            expression_t expression1;
            exprtk::symbol_table<T> st1 = st0;
            expression1.register_symbol_table(st1);

            {
               exprtk::parser<T> parser;

               if (!parser.compile(expression_string,expression1))
               {
                  printf("run_test10() - Error: %s   Expression: %s\n",
                         parser.error().c_str(),
                         expression_string.c_str());

                  return false;
               }
            }

            st1.remove_variable("x0");
            st1.remove_variable("y0");
            st1.remove_variable("z0");
         }
      }
   }

   {
      T a = T(1);
      T b = T(2);
      T c = T(3);
      T d = T(4);

      std::string e = "string";

      exprtk::symbol_table<T> symbol_table;

      symbol_table.add_variable ("a",a);
      symbol_table.add_variable ("b",b);
      symbol_table.add_variable ("c",c);
      symbol_table.add_variable ("d",d);
      symbol_table.add_stringvar("e",e);

      expression_t expression;
      expression.register_symbol_table(symbol_table);

      std::string expression_string = "(E == '1234') and (sin(a) + C) / b";

      typedef exprtk::parser<T> parser_t;
      typedef typename parser_t::dependent_entity_collector::symbol_t symbol_t;

      std::deque<symbol_t> symbol_list;

      {
         parser_t parser;

         parser.dec().collect_variables() = true;
         parser.dec().collect_functions() = true;

         if (!parser.compile(expression_string,expression))
         {
            printf("run_test10() - Error: %s   Expression: %s\n",
                   parser.error().c_str(),
                   expression_string.c_str());

            return false;
         }

         parser.dec().symbols(symbol_list);
      }

      std::deque<symbol_t> expected_symbol_list;

      expected_symbol_list.push_back(symbol_t("a"  ,parser_t::e_st_variable));
      expected_symbol_list.push_back(symbol_t("b"  ,parser_t::e_st_variable));
      expected_symbol_list.push_back(symbol_t("c"  ,parser_t::e_st_variable));
      expected_symbol_list.push_back(symbol_t("e"  ,parser_t::e_st_string  ));
      expected_symbol_list.push_back(symbol_t("sin",parser_t::e_st_function));

      bool result = (symbol_list.size() == expected_symbol_list.size()) &&
                     std::equal(symbol_list.begin(),
                                symbol_list.end(),
                                expected_symbol_list.begin());
      if (!result)
      {
         printf("run_test10() - Failed variable list comparison.(5)\n");
         return false;
      }
   }

   {
      T a = T(1);
      T b = T(2);
      T c = T(3);
      T d = T(4);

      std::string e = "string";

      exprtk::symbol_table<T> symbol_table;

      symbol_table.add_variable ("a",a);
      symbol_table.add_variable ("b",b);
      symbol_table.add_variable ("c",c);
      symbol_table.add_variable ("d",d);
      symbol_table.add_stringvar("e",e);

      expression_t expression;
      expression.register_symbol_table(symbol_table);

      std::string expression_string = "a := b + c;     "
                                      "b := c + d;     "
                                      "c := d + 1;     "
                                      "e := e + 'abc'; ";

      typedef exprtk::parser<T> parser_t;
      typedef typename parser_t::dependent_entity_collector::symbol_t symbol_t;

      std::deque<symbol_t> variable_list;

      {
         parser_t parser;

         parser.dec().collect_assignments() = true;

         if (!parser.compile(expression_string,expression))
         {
            printf("run_test10() - Error: %s   Expression: %s\n",
                   parser.error().c_str(),
                   expression_string.c_str());

            return false;
         }

         parser.dec().assignment_symbols(variable_list);
      }

      std::deque<symbol_t> expected_assignment_list;

      expected_assignment_list.push_back(symbol_t("a",parser_t::e_st_variable));
      expected_assignment_list.push_back(symbol_t("b",parser_t::e_st_variable));
      expected_assignment_list.push_back(symbol_t("c",parser_t::e_st_variable));
      expected_assignment_list.push_back(symbol_t("e",parser_t::e_st_string  ));

      bool result = (variable_list.size() == expected_assignment_list.size()) &&
                     std::equal(variable_list.begin(),
                                variable_list.end(),
                                expected_assignment_list.begin());
      if (!result)
      {
         printf("run_test10() - Failed variable list comparison.(6)\n");
         return false;
      }
   }

   {
      exprtk::symbol_table<T> symbol_table0;
      exprtk::symbol_table<T> symbol_table1;

      if (symbol_table0 == symbol_table1)
      {
         printf("run_test10() - Error symbol_table0 and symbol_table1 are equal\n");
         return false;
      }

      symbol_table0 = symbol_table1;
      symbol_table1 = symbol_table0;

      if (!(symbol_table0 == symbol_table1))
      {
         printf("run_test10() - Error symbol_table0 and symbol_table1 are not equal\n");
         return false;
      }
   }

   {
      T a = T(1);
      T b = T(2);
      T c = T(3);
      T d = T(4);

      std::string e = "a string";

      exprtk::symbol_table<T> symbol_table0;
      exprtk::symbol_table<T> symbol_table1;
      expression_t expression;

      for (std::size_t i = 0; i < 10000; ++i)
      {
         symbol_table0.clear();
         symbol_table1.clear();

         symbol_table0.add_variable ("a",a);
         symbol_table0.add_variable ("b",b);
         symbol_table0.add_variable ("c",c);
         symbol_table0.add_variable ("d",d);
         symbol_table0.add_stringvar("e",e);
         symbol_table0.add_constants(     );

         symbol_table1.add_variable ("a",a);
         symbol_table1.add_variable ("b",b);
         symbol_table1.add_variable ("c",c);
         symbol_table1.add_variable ("d",d);
         symbol_table1.add_stringvar("e",e);
         symbol_table1.add_constants(     );

         expression.register_symbol_table(symbol_table0);
         expression.register_symbol_table(symbol_table1);
      }
   }

   {
      const std::string expression =
                           "for (var i := 0; i < min(x[],y[],z[]); i += 1)"
                           "{ z[i] := 3sin(x[i]) + 2log(y[i]); }";

      std::vector<std::string> var_symbol_list;
      std::vector<std::string> func_symbol_list;

      if (!exprtk::collect_variables(expression, var_symbol_list))
      {
         printf("run_test10() - Failed to collect variables.\n");
         return false;
      }

      if (!exprtk::collect_functions(expression, func_symbol_list))
      {
         printf("run_test10() - Failed to collect functions.\n");
         return false;
      }

      std::sort(var_symbol_list .begin(), var_symbol_list .end());
      std::sort(func_symbol_list.begin(), func_symbol_list.end());

      std::vector<std::string> expected_var_symbol_list;
      std::vector<std::string> expected_func_symbol_list;

      expected_var_symbol_list.push_back("i");
      expected_var_symbol_list.push_back("x");
      expected_var_symbol_list.push_back("y");
      expected_var_symbol_list.push_back("z");

      expected_func_symbol_list.push_back("log");
      expected_func_symbol_list.push_back("min");
      expected_func_symbol_list.push_back("sin");

      const bool var_result = (var_symbol_list.size() == expected_var_symbol_list.size()) &&
                               std::equal(var_symbol_list.begin(),
                                          var_symbol_list.end(),
                                          expected_var_symbol_list.begin());
      if (!var_result)
      {
         printf("run_test10() - Failed collected variable comparison between recieved and expected variables\n");
         return false;
      }

      const bool func_result = (func_symbol_list.size() == expected_func_symbol_list.size()) &&
                               std::equal(func_symbol_list.begin(),
                                          func_symbol_list.end(),
                                          expected_func_symbol_list.begin());
      if (!func_result)
      {
         printf("run_test10() - Failed collected fuctions comparison between recieved and expected functions\n");
         return false;
      }
   }

   {
      std::string expression_list[] =
      {
        "var x; 1",
        "var x := 1; x",
        "var x := 1; var y := 2; 1",
        "var x := 1; var y := 2; x",
        "var x:=6; var y:=4; x + -3  ==   3",
        "var x:=6; var y:=4; x - -3  ==   9",
        "var x:=6; var y:=4; x * -3  == -18",
        "var x:=6; var y:=4; x / -3  ==  -2",
        "var x:=6; var y:=4; -x + -3 ==  -9",
        "var x:=6; var y:=4; -x - -3 ==  -3",
        "var x:=6; var y:=4; -x * -3 ==  18",
        "var x:=6; var y:=4; -x / -3 ==   2",
        "var x:=6; var y:=4; -3 + -x ==   -9",
        "var x:=6; var y:=4; -3 - -x ==    3",
        "var x:=6; var y:=4; -3 * -x ==   18",
        "var x:=6; var y:=4; -3 / -x ==  0.5",
        "var x:=6; var y:=4;  3 + -x ==   -3",
        "var x:=6; var y:=4;  3 - -x ==    9",
        "var x:=6; var y:=4;  3 * -x ==  -18",
        "var x:=6; var y:=4;  3 / -x == -0.5",
        "var x := 3; var y := 6;  x + -y == -3",
        "var x := 3; var y := 6;  x - -y ==  9",
        "var x := 3; var y := 6; -x + -y == -9",
        "var x := 3; var y := 6; -x - -y ==  3",
        "var x := 3; var y := 6; -x * -y == 18",
        "var x := 6; var y := 3; -x / -y ==  2",
        "var x := 3; var y := 6; -(-x * -y) == -18",
        "var x := 6; var y := 3; -(-x / -y) ==  -2",
        "var x:=1;  2+(3+abs(x)) == 6    ",
        "var x:=1;  (3+abs(x))+2 == 6    ",
        "var x:=1;  2+(abs(x)+3) == 6    ",
        "var x:=1;  (abs(x)+3)+2 == 6    ",
        "var x:=1;  2+(3-abs(x)) == 4    ",
        "var x:=1;  (3-abs(x))+2 == 4    ",
        "var x:=1;  2+(abs(x)-3) == 0    ",
        "var x:=1;  (abs(x)-3)+2 == 0    ",
        "var x:=1;  2-(3+abs(x)) == -2   ",
        "var x:=1;  (3+abs(x))-2 ==  2   ",
        "var x:=1;  2-(abs(x)+3) == -2   ",
        "var x:=1;  (abs(x)+3)-2 ==  2   ",
        "var x:=1;  2*(3*abs(x)) == 6    ",
        "var x:=1;  (3*abs(x))*2 == 6    ",
        "var x:=1;  2*(abs(x)*3) == 6    ",
        "var x:=1;  (abs(x)*3)*2 == 6    ",
        "var x:=1;  2*(3/abs(x)) == 6    ",
        "var x:=1;  (3/abs(x))*2 == 6    ",
        "var x:=1;  2*(abs(x)/3) == (2/3)",
        "var x:=1;  (abs(x)/3)*2 == (2/3)",
        "var x:=1;  2/(3*abs(x)) == (2/3)",
        "var x:=1;  (3*abs(x))/2 == (3/2)",
        "var x:=1;  2/(abs(x)*3) == (2/3)",
        "var x:=1;  (abs(x)*3)/2 == (3/2)",
        "var x:=1;  2/(3/abs(x)) == (2/3)",
        "var x:=1;  (3/abs(x))/2 == (3/2)",
        "var x:=1;  2/(abs(x)/3) == 6    ",
        "var x:=1;  (abs(x)/3)/2 == (1/6)",
        "var x:=3; var y:=6; -(-x)*-(-y)               ==  18",
        "var x:=3; var y:=6; -(-x)*-(-(-y))            == -18",
        "var x:=3; var y:=6; -(-(-x))*-(-y)            == -18",
        "var x:=3; var y:=6; -(-(-x))*-(-(-y))         ==  18",
        "var x:=3; var y:=6; -(-(x+y))*-(-(y+x))       ==  81",
        "var x:=3; var y:=6; -(-(-(x+y)))*-(-(y+x))    == -81",
        "var x:=3; var y:=6; -(-(x+y))*-(-(-(y+x)))    == -81",
        "var x:=3; var y:=6; -(-(-(x+y)))*-(-(-(y+x))) ==  81",
        "var x:= 2; var y := 3; (-abs(x)+-abs(y)) == -5     ",
        "var x:= 2; var y := 3; (-abs(x)--abs(y)) ==  1     ",
        "var x:= 2; var y := 3; (-abs(x)*-abs(y)) ==  6     ",
        "var x:= 2; var y := 3; (-abs(x)/-abs(y)) ==  (2/3) ",
        "var x:= 2; var y := 3; (-abs(x)+abs(y))  ==  1     ",
        "var x:= 2; var y := 3; (-abs(x)-abs(y))  == -5     ",
        "var x:= 2; var y := 3; (-abs(x)*abs(y))  == -6     ",
        "var x:= 2; var y := 3; (-abs(x)/abs(y))  == -(2/3) ",
        "var x:= 2; var y := 3; (abs(x)+-abs(y))  == -1     ",
        "var x:= 2; var y := 3; (abs(x)--abs(y))  ==  5     ",
        "var x:= 2; var y := 3; (abs(x)*-abs(y))  == -6     ",
        "var x:= 2; var y := 3; (abs(x)/-abs(y))  == -(2/3) ",
        "var x:= 2; var y := 3; (-abs(x + 0)+-abs(y - 0)) == -5     ",
        "var x:= 2; var y := 3; (-abs(x + 0)--abs(y - 0)) ==  1     ",
        "var x:= 2; var y := 3; (-abs(x + 0)*-abs(y - 0)) ==  6     ",
        "var x:= 2; var y := 3; (-abs(x + 0)/-abs(y - 0)) ==  (2/3) ",
        "var x:= 2; var y := 3; (-abs(x + 0)+abs(y - 0))  ==  1     ",
        "var x:= 2; var y := 3; (-abs(x + 0)-abs(y - 0))  == -5     ",
        "var x:= 2; var y := 3; (-abs(x + 0)*abs(y - 0))  == -6     ",
        "var x:= 2; var y := 3; (-abs(x + 0)/abs(y - 0))  == -(2/3) ",
        "var x:= 2; var y := 3; (abs(x + 0)+-abs(y - 0))  == -1     ",
        "var x:= 2; var y := 3; (abs(x + 0)--abs(y - 0))  ==  5     ",
        "var x:= 2; var y := 3; (abs(x + 0)*-abs(y - 0))  == -6     ",
        "var x:= 2; var y := 3; (abs(x + 0)/-abs(y - 0))  == -(2/3) ",
        "var x := 1; var y := 2; swap(x,y); (x == 2) and (y == 1)",
        "var x := 1; var y := 2; x <=> y     ; (x    == 2) and (y    == 1)",
        "var x := 'abc'; x == 'abc'                        ",
        "var x := 'abc'; var y := '123'; x != y            ",
        "var x := 'abc'; var y := x + '123'; y == 'abc123' ",
        "var x := 'abc'; var y := '123' + x; y == '123abc' ",
        "~{var x := '123'; x[]} + ~{var x := '1234'; x[]}    == 7",
        "~{var x := '123'; x[]} + ~{~{var x := '1234'; x[]}} == 7",
        "~{~{var x := '123'; x[]}} + ~{var x := '1234'; x[]} == 7",
        "~{var x := '123'; x[]} + ~{var x := 4}              == 7",
        "~{var x := 3} + ~{var x := '1234'; x[]}             == 7",
        "~{var x := '123'; x[]} + ~{~{var x := 4}}           == 7",
        "~{~{var x := 3}} + ~{var x := '1234'; x[]}          == 7",
        "var v[2] := {1,2}; swap(v[0],v[1]); (v[0] == 2) and (v[1] == 1)",
        "var v[2] := {1,2}; v[0] <=> v[1]  ; (v[0] == 2) and (v[1] == 1)",
        "var x := 1; var y := 2; ~(swap(x,y),(x == 2) and (y == 1))",
        "var x := 1; var y := 2; ~(x <=> y     , (x    == 2) and (y    == 1))",
        "var v[2] := {1,2}; ~(swap(v[0],v[1]), (v[0] == 2) and (v[1] == 1))",
        "var v[2] := {1,2}; ~(v[0] <=> v[1]  , (v[0] == 2) and (v[1] == 1))",
        "var v[2] := {1,2}; swap(v[zero],v[one]); (v[zero] == 2) and (v[one] == 1)",
        "var v[2] := {1,2}; v[zero] <=> v[one]  ; (v[zero] == 2) and (v[one] == 1)",
        "var v[2] := {1,2}; ~(swap(v[zero],v[one]), (v[zero] == 2) and (v[one] == 1))",
        "var v[2] := {1,2}; ~(v[zero] <=> v[one]  , (v[zero] == 2) and (v[one] == 1))",
        "var v[2] := {1,2}; swap(v[2 * zero],v[(2 * one) / (1 + 1)]); (v[2 * zero] == 2) and (v[(2 * one) / (1 + 1)] == 1)",
        "var v[2] := {1,2}; v[2 * zero] <=> v[(2*one)/(1+1)]  ; (v[2 * zero] == 2) and (v[(2 * one) / (1 + 1)] == 1)",
        "var v[2] := {1,2}; ~(swap(v[2 * zero],v[(2 * one) / (1 + 1)]), (v[2 * zero] == 2) and (v[(2 * one) / (1 + 1)] == 1))",
        "var v[2] := {1,2}; ~(v[2 * zero] <=> v[(2 * one) / (1 + 1)]  , (v[2 * zero] == 2) and (v[(2 * one) / (1 + 1)] == 1))",
        "var x := 1; var y := 2; var v[2] := {3,4}; swap(x,v[0]); swap(v[1],y); (x == 3) and (y == 4)",
        "var x := 1; var y := 2; var v[2] := {3,4}; x <=> v[0]; v[1] <=> y; (x == 3) and (y == 4)",
        "var x := 1; var y := 2; var v[2] := {3,4}; swap(x,v[zero]); swap(v[one],y); (x == 3) and (y == 4)",
        "var x := 1; var y := 2; var v[2] := {3,4}; x <=> v[zero]; v[one] <=> y; (x == 3) and (y == 4)",
        "var x := 1; var y := 2; var v[2] := {3,4}; swap(x,v[2 * zero]); swap(v[(2 * one) / (1 + 1)],y); (x == 3) and (y == 4)",
        "var x := 1; var y := 2; var v[2] := {3,4}; x <=> v[zero / 3]; v[(2 * one)/(1 + 1)] <=> y; (x == 3) and (y == 4)",
        "~{ var x := 1 } + ~{ var x := 2 } == 3",
        "(~{ var x := 1 } + ~{ var x := 2 }) == (~{ var x := 2 } + ~{ var x := 1 })",
        "(~{ var x := 1 } + ~{ var x := 2 } + ~{~{ var x := 1 } + ~{ var x := 2 }}) == 6",
        "(~{ var x[1] := [1] } + ~{ var x[1] := [2] } + ~{~{ var x[1] := [1] } + ~{ var x[1] := [2] }}) == 6",
        "(~{ var x    := [1] } + ~{ var x[1] := [2] } + ~{~{ var x[1] := [1] } + ~{ var x[1] := [2] }}) == 6",
        "(~{ var x[1] := [1] } + ~{ var x    := [2] } + ~{~{ var x[1] := [1] } + ~{ var x[1] := [2] }}) == 6",
        "(~{ var x[1] := [1] } + ~{ var x[1] := [2] } + ~{~{ var x    := [1] } + ~{ var x[1] := [2] }}) == 6",
        "(~{ var x[1] := [1] } + ~{ var x[1] := [2] } + ~{~{ var x[1] := [1] } + ~{ var x    := [2] }}) == 6",
        "(~{~{ var x[1] := [1] } + ~{ var x[1] := [2] }} + ~{ var x[1] := [1] } + ~{ var x[1] := [2] }) == 6",
        "(~{~{ var x    := [1] } + ~{ var x[1] := [2] }} + ~{ var x[1] := [1] } + ~{ var x[1] := [2] }) == 6",
        "(~{~{ var x[1] := [1] } + ~{ var x    := [2] }} + ~{ var x[1] := [1] } + ~{ var x[1] := [2] }) == 6",
        "(~{~{ var x[1] := [1] } + ~{ var x[1] := [2] }} + ~{ var x    := [1] } + ~{ var x[1] := [2] }) == 6",
        "(~{~{ var x[1] := [1] } + ~{ var x[1] := [2] }} + ~{ var x[1] := [1] } + ~{ var x    := [2] }) == 6",
        "(~{~{ var x[1] := [1] }} + ~{ var x[1] := [1] } + ~{ var x[1] := [2] } + ~{{ var x[1] := [2] }}) == 6",
        "(~{~{ var x    := [1] }} + ~{ var x[1] := [1] } + ~{ var x[1] := [2] } + ~{{ var x[1] := [2] }}) == 6",
        "(~{~{ var x[1] := [1] }} + ~{ var x    := [1] } + ~{ var x[1] := [2] } + ~{{ var x[1] := [2] }}) == 6",
        "(~{~{ var x[1] := [1] }} + ~{ var x[1] := [1] } + ~{ var x    := [2] } + ~{{ var x[1] := [2] }}) == 6",
        "(~{~{ var x[1] := [1] }} + ~{ var x[1] := [1] } + ~{ var x[1] := [2] } + ~{{ var x    := [2] }}) == 6",
        "(~{~{~{var x[1] := [1]}}} + ~{~{var x[1] := [2]}} + ~{var x[1] := [3]}) == 6",
        "(~{var x[1] := [1]} + ~{~{var x[1] := [2]}} + ~{~{~{var x[1] := [3]}}}) == 6",
        "(~{ var x[3] := [1] } + ~{ var x[6] := {6,5,4,3,2,1}}) == 7",
        "(~{ var x[6] := {6,5,4,3,2,1} } + ~{ var x := 1 }) == 7",
        "(~{ var x := 1 } + ~{ var x[6] := {6,5,4,3,2,1} }) == 7",
        "var x[3] := {};      (x[0] == 0) and (x[1] == 0) and (x[2] == 0)",
        "var x[3] := {1,2};   (x[0] == 1) and (x[1] == 2) and (x[2] == 0)",
        "var x[3] := {1,2,3}; (x[0] == 1) and (x[1] == 2) and (x[2] == 3)",
        "var x[3] := [1];     (x[0] == 1) and (x[1] == 1) and (x[2] == 1)",
        "var v[3] := [1]; v += 1; (v[0] == v[1]) and (v[0] == v[2]) and (v[0] == 2)",
        "var v[3] := [1]; v -= 1; (v[0] == v[1]) and (v[0] == v[2]) and (v[0] == 0)",
        "var v[3] := [1]; v *= 2; (v[0] == v[1]) and (v[0] == v[2]) and (v[0] == 2)",
        "var v[3] := [3]; v /= 3; (v[0] == v[1]) and (v[0] == v[2]) and (v[0] == 1)",
        "var v[3] := {1,2, 3}; v += 1; (v[0] == 2) and (v[1] == 3) and (v[2] == 4)",
        "var v[3] := {1,2, 3}; v -= 1; (v[0] == 0) and (v[1] == 1) and (v[2] == 2)",
        "var v[3] := {1,2, 3}; v *= 2; (v[0] == 2) and (v[1] == 4) and (v[2] == 6)",
        "var v[3] := {3,9,15}; v /= 3; (v[0] == 1) and (v[1] == 3) and (v[2] == 5)",
        "var v0[3] := [1]; var v1[3] := [1]; v0 += v1; (v0[0] == v0[1]) and (v0[0] == v0[2]) and (v0[0] == 2)",
        "var v0[3] := [1]; var v1[3] := [1]; v0 -= v1; (v0[0] == v0[1]) and (v0[0] == v0[2]) and (v0[0] == 0)",
        "var v0[3] := [1]; var v1[3] := [2]; v0 *= v1; (v0[0] == v0[1]) and (v0[0] == v0[2]) and (v0[0] == 2)",
        "var v0[3] := [3]; var v1[3] := [3]; v0 /= v1; (v0[0] == v0[1]) and (v0[0] == v0[2]) and (v0[0] == 1)",
        "var v0[3] := {1,2, 3}; var v1[3] := {1,1,1}; v0 += v1; (v0[0] == 2) and (v0[1] == 3) and (v0[2] == 4)",
        "var v0[3] := {1,2, 3}; var v1[3] := {1,1,1}; v0 -= v1; (v0[0] == 0) and (v0[1] == 1) and (v0[2] == 2)",
        "var v0[3] := {1,2, 3}; var v1[3] := {2,2,2}; v0 *= v1; (v0[0] == 2) and (v0[1] == 4) and (v0[2] == 6)",
        "var v0[3] := {3,9,15}; var v1[3] := {3,3,3}; v0 /= v1; (v0[0] == 1) and (v0[1] == 3) and (v0[2] == 5)",
        "var x[3] := {};  var y[4] := {1,2,3,4}; x := y; (x[0] == y[0]) and (x[1] == y[1]) and (x[2] == y[2])",
        "var x[3] := {};  var y[3] := {1,2,3};   x := y; (x[0] == y[0]) and (x[1] == y[1]) and (x[2] == y[2])",
        "var x[3] := {};  var y[2] := {1,2};     x := y; (x[0] == y[0]) and (x[1] == y[1]) and (x[2] ==    0)",
        "var x[3] := {};  var y[1] := {1};       x := y; (x[0] == y[0]) and (x[1] ==    0) and (x[2] ==    0)",
        "var x[3] := {};  var y[4] := {1,2,3,4}; x := (y+=1); (x[0] == y[0]) and (x[1] == y[1]) and (x[2] == y[2])",
        "var x[3] := {};  var y[3] := {1,2,3};   x := (y+=1); (x[0] == y[0]) and (x[1] == y[1]) and (x[2] == y[2])",
        "var x[3] := {};  var y[2] := {1,2};     x := (y+=1); (x[0] == y[0]) and (x[1] == y[1]) and (x[2] ==    0)",
        "var x[3] := {};  var y[1] := {1};       x := (y+=1); (x[0] == y[0]) and (x[1] ==    0) and (x[2] ==    0)",
        "var x[3] := {};  var y[4] := {1,2,3,4}; x += (y+=1); (x[0] == y[0]) and (x[1] == y[1]) and (x[2] == y[2])",
        "var x[3] := {};  var y[3] := {1,2,3};   x += (y+=1); (x[0] == y[0]) and (x[1] == y[1]) and (x[2] == y[2])",
        "var x[3] := {};  var y[2] := {1,2};     x += (y+=1); (x[0] == y[0]) and (x[1] == y[1]) and (x[2] ==    0)",
        "var x[3] := {};  var y[1] := {1};       x += (y+=1); (x[0] == y[0]) and (x[1] ==    0) and (x[2] ==    0)",
        "var x[3] := [9]; var y[4] := {1,2,3,4}; x <=> y; (x[0] == 1) and (x[1] == 2) and (x[2] == 3)",
        "var x[3] := [9]; var y[3] := {1,2,3};   x <=> y; (x[0] == 1) and (x[1] == 2) and (x[2] == 3)",
        "var x[3] := [9]; var y[2] := {1,2};     x <=> y; (x[0] == 1) and (x[1] == 2) and (x[2] == 9)",
        "var x[3] := [9]; var y[1] := {1};       x <=> y; (x[0] == 1) and (x[1] == 9) and (x[2] == 9)",
        "var x[3] := [9]; var y[4] := {1,2,3,4}; x <=> (y += 1); (x[0] == 2) and (x[1] == 3) and (x[2] == 4)",
        "var x[3] := [9]; var y[3] := {1,2,3};   x <=> (y += 1); (x[0] == 2) and (x[1] == 3) and (x[2] == 4)",
        "var x[3] := [9]; var y[2] := {1,2};     x <=> (y += 1); (x[0] == 2) and (x[1] == 3) and (x[2] == 9)",
        "var x[3] := [9]; var y[1] := {1};       x <=> (y += 1); (x[0] == 2) and (x[1] == 9) and (x[2] == 9)",
        "var x[3] := [8]; var y[4] := {1,2,3,4}; (x += 1) <=> y; (x[0] == 1) and (x[1] == 2) and (x[2] == 3)",
        "var x[3] := [8]; var y[3] := {1,2,3};   (x += 1) <=> y; (x[0] == 1) and (x[1] == 2) and (x[2] == 3)",
        "var x[3] := [8]; var y[2] := {1,2};     (x += 1) <=> y; (x[0] == 1) and (x[1] == 2) and (x[2] == 9)",
        "var x[3] := [8]; var y[1] := {1};       (x += 1) <=> y; (x[0] == 1) and (x[1] == 9) and (x[2] == 9)",
        "var x[3] := [8]; var y[4] := {1,2,3,4}; (x += 1) <=> (y += 1); (x[0] == 2) and (x[1] == 3) and (x[2] == 4)",
        "var x[3] := [8]; var y[3] := {1,2,3};   (x += 1) <=> (y += 1); (x[0] == 2) and (x[1] == 3) and (x[2] == 4)",
        "var x[3] := [8]; var y[2] := {1,2};     (x += 1) <=> (y += 1); (x[0] == 2) and (x[1] == 3) and (x[2] == 9)",
        "var x[3] := [8]; var y[1] := {1};       (x += 1) <=> (y += 1); (x[0] == 2) and (x[1] == 9) and (x[2] == 9)",
        "var x[3] := [0]; var y[4] := {1,2,3,4}; X <  y",
        "var x[3] := [0]; var y[3] := {1,2,3};   x <  Y",
        "var x[3] := [0]; var y[2] := {1,2};     X <  y",
        "var x[3] := [0]; var y[1] := {1};       x <  Y",
        "var x[3] := [0]; var y[4] := {1,2,3,4}; x <= y",
        "var x[3] := [0]; var y[3] := {1,2,3};   x <= y",
        "var x[3] := [0]; var y[2] := {1,2};     x <= y",
        "var x[3] := [0]; var y[1] := {1};       x <= y",
        "var x[3] := [5]; var y[4] := {1,2,3,4}; x >  y",
        "var x[3] := [5]; var y[3] := {1,2,3};   x >  y",
        "var x[3] := [5]; var y[2] := {1,2};     x >  y",
        "var x[3] := [5]; var y[1] := {1};       x >  y",
        "var x[3] := [5]; var y[4] := {1,2,3,4}; x >= y",
        "var x[3] := [5]; var y[3] := {1,2,3};   x >= y",
        "var x[3] := [5]; var y[2] := {1,2};     x >= y",
        "var x[3] := [5]; var y[1] := {1};       x >= y",
        "var x[3] := [1]; var y[4] := [1];       x == y",
        "var x[3] := [1]; var y[3] := [1];       x == y",
        "var x[3] := [1]; var y[2] := [1];       x == y",
        "var x[3] := [1]; var y[1] := [1];       x == y",
        "var x[3] := [1]; var y[4] := [2];       x != y",
        "var x[3] := [1]; var y[3] := [2];       x != y",
        "var x[3] := [1]; var y[2] := [2];       x != y",
        "var x[3] := [1]; var y[1] := [2];       x != y",
        "var x[3] := [0]; var y[4] := {5,6,7,8}; (x += 1) < y",
        "var x[3] := [0]; var y[3] := {5,6,7};   (x += 1) < y",
        "var x[3] := [0]; var y[2] := {5,6};     (x += 1) < y",
        "var x[3] := [0]; var y[1] := {5};       (x += 1) < y",
        "var x[3] := [0]; var y[4] := {1,2,3,4}; x < (y += 1)",
        "var x[3] := [0]; var y[3] := {1,2,3};   x < (y += 1)",
        "var x[3] := [0]; var y[2] := {1,2};     x < (y += 1)",
        "var x[3] := [0]; var y[1] := {1};       x < (y += 1)",
        "var x[3] := [0]; var y[4] := {5,6,7,8}; (x += 1) < (y += 1)",
        "var x[3] := [0]; var y[3] := {5,6,7};   (x += 1) < (y += 1)",
        "var x[3] := [0]; var y[2] := {5,6};     (x += 1) < (y += 1)",
        "var x[3] := [0]; var y[1] := {5};       (x += 1) < (y += 1)",
        "var x[3] := {1,2,3};  var y := 5; x < y     ",
        "var x[3] := {1,2,3};  var y := 3; x < y + 1 ",
        "var x[3] := {1,2,3};  var y := 5; x <= y    ",
        "var x[3] := {1,2,3};  var y := 3; x <= y + 1",
        "var x[3] := {1,1,1};  var y := 1; x == y    ",
        "var x[3] := {1,1,1};  var y := 2; x == y - 1",
        "var x[3] := {1,2,3};  var y := 5; y > x     ",
        "var x[3] := {1,2,3};  var y := 3; y >= x    ",
        "var x[3] := {1,2,3};  var y := 5; y + 1 > x ",
        "var x[3] := {1,1,1};  var y := 1; y == x    ",
        "var x[3] := {1,1,1};  var y := 2; y - 1 == x",
        "var x[3] := {1,2,3};  var y := 5; equal(true,(x += 1) < y)    ",
        "var x[3] := {1,2,3};  var y := 3; equal(true,(x -= 1) < y + 1)",
        "var x[3] := {1,2,3};  var y := 5; equal(true,(x -= 1) <= y)   ",
        "var x[3] := {2,2,2};  var y := 1; (x -= 1) == y    ",
        "var x[3] := {1,2,3};  var y := 5; y > (x += 1)     ",
        "var x[3] := {1,2,3};  var y := 5; y + 1 > (x += 1) ",
        "var x[3] := {2,2,2};  var y := 1; y == (x -= 1)    ",
        "var x[3] := {2,2,2};  var y := 0; y + 1 == (x -= 1)",
        "var x[3] := [1]; var y[4] := {1,2,3,4}; var z[3] := [1]; z := (x + y); z == (x + y)",
        "var x[3] := [1]; var y[3] := {1,2,3};   var z[3] := [1]; z := (x - y); z == (x - y)",
        "var x[3] := [1]; var y[2] := {1,2};     var z[3] := [1]; z := (x / y); z == (x / y)",
        "var x[3] := [1]; var y[1] := {1};       var z[3] := [1]; z := (x * y); z == (x * y)",
        "var x[3] := [1]; var y[4] := {1,2,3,4}; var z[3] := [1]; z := 2(x + y); z == (x + y)2",
        "var x[3] := [1]; var y[3] := {1,2,3};   var z[3] := [1]; z := 2(x - y); z == (x - y)2",
        "var x[3] := [1]; var y[2] := {1,2};     var z[3] := [1]; z := 2(x / y); z == (x / y)2",
        "var x[3] := [1]; var y[1] := {1};       var z[3] := [1]; z := 2(x * y); z == (x * y)2",
        "var x[3] := [1]; var y[4] := {1,2,3,4}; var z[3] := [1]; z := 2(x + y)/3; z == 2(x + y)/3",
        "var x[3] := [1]; var y[3] := {1,2,3};   var z[3] := [1]; z := 2(x - y)/3; z == 2(x - y)/3",
        "var x[3] := [1]; var y[2] := {1,2};     var z[3] := [1]; z := 2(x / y)/3; z == 2(x / y)/3",
        "var x[3] := [1]; var y[1] := {1};       var z[3] := [1]; z := 2(x * y)/3; z == 2(x * y)/3",
        "var x[6] := {1,2,3,4,5,6}; equal(sqrt(sum([x - avg(x)]^2) / x[]),1.7078251277)",
        "var x[3] := {-1,-2,-3};    sum(abs(x)  ) == 6",
        "var x[3] := {0.1,0.2,0.3}; sum(trunc(x)) == 0",

        "var x[10^6]:=[2];var y[10^6]:=[3]; var s:=0;equal(for(var i:=0; i<10;i+=1){s+= sum(5 *(2x-y/3)) + i;},150000045.0)",

        "var x := 2; (~{ for (var i := 0; i < 10; i += 1) { for (var j := 0; j <= i;  "
        "j += 1) { var y := 3; if ((i + j + y + x) < 6) { y += x; continue; } else    "
        "break[i + j]; } } } + ~{ for (var i := 0; i < 10; i += 1) { for (var j := 0; "
        "j <= i; j += 1) { var y := 3; if ((i + j + y + x) < 6) { y += x; continue; } "
        " else break[i + j]; } } }) == 18                                             ",

        "var x := 2; var v0[3] := {1,2,3}; ( ~{ for (var i := 0; i < 10; i += 1) { "
        "for (var j := 0; j <= i; j += 1) { var y := 3; var v2[3] := {1,2,3}; if ( "
        "(i + j + y + x + abs(v0[i % v0[]] - v2[j % v2[]])) < 6) { var v3[3] :=    "
        "{1,2,3}; y += x / v3[j % v3[]]; continue; } else break[i + j]; } } }      "
        "+ ~{ for (var i := 0; i < 10; i += 1) { for (var j := 0; j <= i; j += 1)  "
        " { var y := 3; var v2[3] := {1,2,3}; if ((i + j + y + x + abs(v0[i % v0[]] - "
        "v2[j % v2[]])) < 6) { var v3[3] := {1,2,3}; y += x / v3[j % v3[]];        "
        "continue; } else break[i + j]; } } } ) == 18                              ",

        "12 == (if (1 > 2) { var x:= 2; } else { var x[3] := {7,2,3}; sum(x); })",
        "12 == (if (1 < 2) { var x[3] := {7,2,3}; sum(x); } else { var x:= 2; })",
        "12 == (if (1 > 2) { var x:= 2; } else { var x[3] := {7,2,3}; sum(x); })",
        "12 == (if (1 < 2) { var x[3] := {7,2,3}; sum(x); } else { var x:= 2; })",

        "21 == (for (var i := 0; i < 10; i += 1) { if (i > 2) { break [i * 7]; i += 1;"
        "i += 2; i += 3; }; })",

        "21 == (for (var i := 0; i < 10; i += 1) { if (i > 2) { break [i * 7]; return "
        "[i * 8]; i += 1; i += 2; i += 3; }; })",

        "2 == for (var i := 0; i < 10; i += 1) { if (i > 2) { continue; i += 1; i += 2;"
        "i += 3; } else i; }",

        "2 == for (var i := 0; i < 10; i += 1) { if (i > 2) { continue; return [i * 8];"
        "i += 1; i += 2; i += 3; } else i; }",

        "var x[10] := [-1]; var y[10] := [-1]; for (var i := 0; i < 10; i += 1) { x[i] := i; "
        "y[i] := 2 * x[i]; }; (sum(x) == 45) and (sum(y) == (2 * sum(x)));"

        "7 == (for (var i := 0; i < 10; i += 1) { ~{break[7]; continue; i += i} })",
        "0 == (for (var i := 0; i < 10; i += 1) { ~{break[i]; continue; i += i} })",
        "0 == (for (var i := 0; i < 10; i += 1) { ~{continue; break[7]; i += i} })",
        "1 == (for (var i := 0; i < 10; i += 1) { ~{break[i += 1]; continue; i += i} })",

        "var s := 'abc';  s == ~{'abc'     } ",
        "var s := 'abc';  s == ~{s         } ",
        "var s := 'abc';  s == ~{'ab' + 'c'} ",
        "var s := 'abc';  ~{'abc'     } == s ",
        "var s := 'abc';  ~{s         } == s ",
        "var s := 'abc';  ~{'ab' + 'c'} == s ",
        "var s := 'abc';  ~{1 + 2; 'abc' + s; s} == s ",
        "var s := 'abc';  ~{1 + 2; var x := 'ab'; x + 'c'} == s ",

        "var x[10^6] := null; var y[10^7] := null; 0 * (min(x) + min(y)) + x[] + y[] == 10^7 + 10^6"
      };

      const std::size_t expression_list_size = sizeof(expression_list) / sizeof(std::string);

      static const std::size_t rounds = 20;

      exprtk::symbol_table<T> symbol_table;

      T zero = T(0);
      T one  = T(1);

      symbol_table.add_variable("zero",zero);
      symbol_table.add_variable("one" , one);
      symbol_table.add_pi();

      bool failed = false;

      for (std::size_t r = 0; r < rounds; ++r)
      {
         for (std::size_t i = 0; i < expression_list_size; ++i)
         {
            expression_t expression;
            expression.register_symbol_table(symbol_table);

            {
               exprtk::parser<T> parser;

               if (!parser.compile(expression_list[i],expression))
               {
                  printf("run_test10() -  swaps[1]  Error: %s   Expression: %s\n",
                         parser.error().c_str(),
                         expression_list[i].c_str());

                  failed = true;
                  continue;
               }
            }

            T result = expression.value();

            if (T(1) != result)
            {
               printf("run_test10() -  swaps[1] evaluation error Expression: %s\n",
                      expression_list[i].c_str());

               failed = true;
            }
         }

         if (failed)
         {
            return false;
         }
      }

      // reuse parser
      for (std::size_t r = 0; r < rounds; ++r)
      {
         exprtk::parser<T> parser;

         for (std::size_t i = 0; i < expression_list_size; ++i)
         {
            expression_t expression;
            expression.register_symbol_table(symbol_table);

            if (!parser.compile(expression_list[i],expression))
            {
               printf("run_test10() -  swaps[2]  Error: %s   Expression: %s\n",
                      parser.error().c_str(),
                      expression_list[i].c_str());

               failed = true;
               continue;
            }

            T result = expression.value();

            if (T(1) != result)
            {
               printf("run_test10() -  swaps[2] evaluation error Expression: %s\n",
                      expression_list[i].c_str());

               failed = true;
            }
         }

         if (failed)
         {
            return false;
         }
      }
   }

   return true;
}

template <typename T>
inline bool run_test11()
{
   typedef exprtk::expression<T> expression_t;
   std::string expression_string = "(x + y) / 3";

   T x = T(1.0);
   T y = T(2.0);

   exprtk::symbol_table<T> symbol_table;
   symbol_table.add_variable("x",x);
   symbol_table.add_variable("y",y);

   expression_t expression;
   expression.register_symbol_table(symbol_table);

   static const std::size_t rounds = 500;

   for (std::size_t i = 0; i < rounds; ++i)
   {
      {
         exprtk::parser<T> parser;

         if (!parser.compile(expression_string,expression))
         {
            printf("run_test11() - Error: %s   Expression: %s\n",
                   parser.error().c_str(),
                   expression_string.c_str());

            return false;
         }
      }

      if (not_equal(expression.value(),(x + y) / T(3),T(0.000001)))
      {
         printf("run_test11() - Error in evaluation!(1)\n");
         return false;
      }

      expression.release();

      if (false == (!expression))
      {
         printf("run_test11() - Error in evaluation!(2)\n");
         return false;
      }

      {
         exprtk::parser<T> parser;

         if (!parser.compile(expression_string,expression))
         {
            printf("run_test11() - Error: %s   Expression: %s\n",
                   parser.error().c_str(),
                   expression_string.c_str());

            return false;
         }
      }

      expression.value();

      if (not_equal(expression.value(),(x + y) / T(3),T(0.000001)))
      {
         printf("run_test11() - Error in evaluation!(3)\n");
         return false;
      }
   }

   if (!exprtk::pgo_primer<T>())
   {
      printf("run_test11() - Failed PGO primer\n");
      return false;
   }

   return true;
}

template <typename T>
inline bool run_test12()
{
   typedef exprtk::expression<T> expression_t;
   static const std::string expression_string[] =
                            {
                              "equal(poly01(x,2.2,1.1),(2.2x^1+1.1))",
                              "equal(poly02(x,3.3,2.2,1.1),(3.3x^2+2.2x^1+1.1))",
                              "equal(poly03(x,4.4,3.3,2.2,1.1),(4.4x^3+3.3x^2+2.2x^1+1.1))",
                              "equal(poly04(x,5.5,4.4,3.3,2.2,1.1),(5.5x^4+4.4x^3+3.3x^2+2.2x^1+1.1))",
                              "equal(poly05(x,6.6,5.5,4.4,3.3,2.2,1.1),(6.6x^5+5.5x^4+4.4x^3+3.3x^2+2.2x^1+1.1))",
                              "equal(poly06(x,7.7,6.6,5.5,4.4,3.3,2.2,1.1),(7.7x^6+6.6x^5+5.5x^4+4.4x^3+3.3x^2+2.2x^1+1.1))",
                              "equal(poly07(x,8.8,7.7,6.6,5.5,4.4,3.3,2.2,1.1),(8.8x^7+7.7x^6+6.6x^5+5.5x^4+4.4x^3+3.3x^2+2.2x^1+1.1))",
                              "equal(poly08(x,9.9,8.8,7.7,6.6,5.5,4.4,3.3,2.2,1.1),(9.9x^8+8.8x^7+7.7x^6+6.6x^5+5.5x^4+4.4x^3+3.3x^2+2.2x^1+1.1))",
                              "equal(poly09(x,1.1,9.9,8.8,7.7,6.6,5.5,4.4,3.3,2.2,1.1),(1.1x^9+9.9x^8+8.8x^7+7.7x^6+6.6x^5+5.5x^4+4.4x^3+3.3x^2+2.2x^1+1.1))",
                              "equal(poly10(x,2.2,1.1,9.9,8.8,7.7,6.6,5.5,4.4,3.3,2.2,1.1),(2.2x^10+1.1x^9+9.9x^8+8.8x^7+7.7x^6+6.6x^5+5.5x^4+4.4x^3+3.3x^2+2.2x^1+1.1))",
                              "equal(poly11(x,3.3,2.2,1.1,9.9,8.8,7.7,6.6,5.5,4.4,3.3,2.2,1.1),(3.3x^11+2.2x^10+1.1x^9+9.9x^8+8.8x^7+7.7x^6+6.6x^5+5.5x^4+4.4x^3+3.3x^2+2.2x^1+1.1))",
                              "equal(poly12(x,4.4,3.3,2.2,1.1,9.9,8.8,7.7,6.6,5.5,4.4,3.3,2.2,1.1),(4.4x^12+3.3x^11+2.2x^10+1.1x^9+9.9x^8+8.8x^7+7.7x^6+6.6x^5+5.5x^4+4.4x^3+3.3x^2+2.2x^1+1.1))",
                              "EquaL(Poly01(x,2.2,1.1),(2.2x^1+1.1))",
                              "eQuAl(pOly02(x,3.3,2.2,1.1),(3.3x^2+2.2x^1+1.1))",
                              "eqUal(poLy03(x,4.4,3.3,2.2,1.1),(4.4x^3+3.3x^2+2.2x^1+1.1))",
                              "eQuAl(polY04(x,5.5,4.4,3.3,2.2,1.1),(5.5x^4+4.4x^3+3.3x^2+2.2x^1+1.1))",
                              "EquAl(pOLy05(x,6.6,5.5,4.4,3.3,2.2,1.1),(6.6x^5+5.5x^4+4.4x^3+3.3x^2+2.2x^1+1.1))",
                              "EqUaL(pOly06(x,7.7,6.6,5.5,4.4,3.3,2.2,1.1),(7.7x^6+6.6x^5+5.5x^4+4.4x^3+3.3x^2+2.2x^1+1.1))",
                              "Equal(Poly07(x,8.8,7.7,6.6,5.5,4.4,3.3,2.2,1.1),(8.8x^7+7.7x^6+6.6x^5+5.5x^4+4.4x^3+3.3x^2+2.2x^1+1.1))",
                              "eQual(PoLy08(x,9.9,8.8,7.7,6.6,5.5,4.4,3.3,2.2,1.1),(9.9x^8+8.8x^7+7.7x^6+6.6x^5+5.5x^4+4.4x^3+3.3x^2+2.2x^1+1.1))",
                              "eqUal(pOlY09(x,1.1,9.9,8.8,7.7,6.6,5.5,4.4,3.3,2.2,1.1),(1.1x^9+9.9x^8+8.8x^7+7.7x^6+6.6x^5+5.5x^4+4.4x^3+3.3x^2+2.2x^1+1.1))",
                              "equAl(POLY10(x,2.2,1.1,9.9,8.8,7.7,6.6,5.5,4.4,3.3,2.2,1.1),(2.2x^10+1.1x^9+9.9x^8+8.8x^7+7.7x^6+6.6x^5+5.5x^4+4.4x^3+3.3x^2+2.2x^1+1.1))",
                              "equaL(PolY11(x,3.3,2.2,1.1,9.9,8.8,7.7,6.6,5.5,4.4,3.3,2.2,1.1),(3.3x^11+2.2x^10+1.1x^9+9.9x^8+8.8x^7+7.7x^6+6.6x^5+5.5x^4+4.4x^3+3.3x^2+2.2x^1+1.1))",
                              "EQUAL(pOLy12(x,4.4,3.3,2.2,1.1,9.9,8.8,7.7,6.6,5.5,4.4,3.3,2.2,1.1),(4.4x^12+3.3x^11+2.2x^10+1.1x^9+9.9x^8+8.8x^7+7.7x^6+6.6x^5+5.5x^4+4.4x^3+3.3x^2+2.2x^1+1.1))"
                            };
   static const std::size_t expression_string_size = sizeof(expression_string) / sizeof(std::string);

   T x = T(1.23456);

   exprtk::polynomial<T, 1> poly01;
   exprtk::polynomial<T, 2> poly02;
   exprtk::polynomial<T, 3> poly03;
   exprtk::polynomial<T, 4> poly04;
   exprtk::polynomial<T, 5> poly05;
   exprtk::polynomial<T, 6> poly06;
   exprtk::polynomial<T, 7> poly07;
   exprtk::polynomial<T, 8> poly08;
   exprtk::polynomial<T, 9> poly09;
   exprtk::polynomial<T,10> poly10;
   exprtk::polynomial<T,11> poly11;
   exprtk::polynomial<T,12> poly12;

   exprtk::symbol_table<T> symbol_table;

   symbol_table.add_variable("x",x);
   symbol_table.add_function("poly01", poly01);
   symbol_table.add_function("poly02", poly02);
   symbol_table.add_function("poly03", poly03);
   symbol_table.add_function("poly04", poly04);
   symbol_table.add_function("poly05", poly05);
   symbol_table.add_function("poly06", poly06);
   symbol_table.add_function("poly07", poly07);
   symbol_table.add_function("poly08", poly08);
   symbol_table.add_function("poly09", poly09);
   symbol_table.add_function("poly10", poly10);
   symbol_table.add_function("poly11", poly11);
   symbol_table.add_function("poly12", poly12);

   expression_t expression;
   expression.register_symbol_table(symbol_table);

   static const std::size_t rounds = 500;

   for (std::size_t i = 0; i < rounds; ++i)
   {
      for (std::size_t j = 0; j < expression_string_size; ++j)
      {
         const std::string& expr_str = expression_string[j];

         {
            exprtk::parser<T> parser;

            if (!parser.compile(expr_str,expression))
            {
               printf("run_test12() - Error: %s   Expression: %s\n",
                      parser.error().c_str(),
                      expr_str.c_str());

               return false;
            }
         }

         if (T(1) != expression.value())
         {
            printf("run_test12() - Error in evaluation! Expression: %s\n",expr_str.c_str());
            return false;
         }
      }
   }

   return true;
}

template <typename T>
struct sine_deg : public exprtk::ifunction<T>
{
   using exprtk::ifunction<T>::operator();

   sine_deg() : exprtk::ifunction<T>(1) {}

   inline T operator()(const T& v) override
   {
      return std::sin((v * T(exprtk::details::numeric::constant::pi)) / T(180));
   }
};

template <typename T>
struct cosine_deg : public exprtk::ifunction<T>
{
   using exprtk::ifunction<T>::operator();

   cosine_deg() : exprtk::ifunction<T>(1) {}

   inline T operator()(const T& v) override
   {
      return std::cos((v * T(exprtk::details::numeric::constant::pi)) / T(180));
   }
};

template <typename T>
inline bool run_test13()
{
   typedef exprtk::symbol_table<T> symbol_table_t;
   typedef exprtk::expression<T>     expression_t;
   typedef exprtk::parser<T>             parser_t;

   static const std::string expression_string[] =
                            {
                              "equal(sin(30),0.5)                    ",
                              "equal(cos(60),0.5)                    ",
                              "equal(sin(60),sqrt(3)/2)              ",
                              "equal(cos(30),sqrt(3)/2)              ",
                              "equal(sin(x_deg),0.5)                 ",
                              "equal(cos(y_deg),0.5)                 ",
                              "equal(sin(y_deg),sqrt(3)/2)           ",
                              "equal(cos(x_deg),sqrt(3)/2)           ",
                              "equal(sin(30) + sin(30),1.0)          ",
                              "equal(cos(60) + cos(60),1.0)          ",
                              "equal(sin(60) + sin(60),sqrt(3))      ",
                              "equal(cos(30) + cos(30),sqrt(3))      ",
                              "equal(sin(x_deg) + sin(x_deg),1.0)    ",
                              "equal(cos(y_deg) + cos(y_deg),1.0)    ",
                              "equal(sin(y_deg) + sin(y_deg),sqrt(3))",
                              "equal(cos(x_deg) + cos(x_deg),sqrt(3))"
                            };

   static const std::size_t expression_string_size = sizeof(expression_string) / sizeof(std::string);

   {
      T x_deg = T(30);
      T y_deg = T(60);

      sine_deg  <T>   sine;
      cosine_deg<T> cosine;

      symbol_table_t symbol_table_0;
      symbol_table_t symbol_table_1;

      symbol_table_0.add_variable("x_deg",x_deg);
      symbol_table_1.add_variable("y_deg",y_deg);

      symbol_table_0.add_function(  "sine_deg",   sine);
      symbol_table_1.add_function("cosine_deg", cosine);

      expression_t expression;

      expression.register_symbol_table(symbol_table_0);
      expression.register_symbol_table(symbol_table_1);

      static const std::size_t rounds = 100;

      for (std::size_t i = 0; i < rounds; ++i)
      {
         for (std::size_t j = 0; j < expression_string_size; ++j)
         {
            const std::string& expr_str = expression_string[j];

            {
               parser_t parser;

               parser.replace_symbol("sin",   "sine_deg");
               parser.replace_symbol("cos", "cosine_deg");

               if (!parser.compile(expr_str,expression))
               {
                  printf("run_test13() - Error: %s   Expression: %s  [1]\n",
                         parser.error().c_str(),
                         expr_str.c_str());

                  return false;
               }
            }

            if (T(1) != expression.value())
            {
               printf("run_test13() - Error in evaluation! Expression: %s  [1]\n",expr_str.c_str());
               return false;
            }
         }
      }
   }

   {
      T x_deg = T(30);
      T y_deg = T(60);

      sine_deg  <T>   sine;
      cosine_deg<T> cosine;

      symbol_table_t symbol_table_0;
      symbol_table_t symbol_table_1;

      symbol_table_0.add_variable("x_deg",x_deg);
      symbol_table_1.add_variable("y_deg",y_deg);

      symbol_table_0.add_reserved_function("sin",  sine);
      symbol_table_1.add_reserved_function("cos",cosine);

      expression_t expression;

      expression.register_symbol_table(symbol_table_0);
      expression.register_symbol_table(symbol_table_1);

      static const std::size_t rounds = 100;

      for (std::size_t i = 0; i < rounds; ++i)
      {
         for (std::size_t j = 0; j < expression_string_size; ++j)
         {
            const std::string& expr_str = expression_string[j];

            {
               typedef typename parser_t::settings_store settings_t;

               parser_t parser;

               parser.settings()
                  .disable_base_function(settings_t::e_bf_sin)
                  .disable_base_function(settings_t::e_bf_cos);

               if (!parser.compile(expr_str,expression))
               {
                  printf("run_test13() - Error: %s   Expression: %s  [2]\n",
                         parser.error().c_str(),
                         expr_str.c_str());

                  return false;
               }
            }

            if (T(1) != expression.value())
            {
               printf("run_test13() - Error in evaluation! Expression: %s  [2]\n",expr_str.c_str());
               return false;
            }
         }
      }
   }

   return true;
}

template <typename Allocator,
          template <typename,typename> class Sequence>
inline std::size_t load_expressions(const std::string& file_name,
                                    Sequence<std::string,Allocator>& sequence)
{
   std::ifstream stream(file_name.c_str());

   if (!stream) return 0;

   std::string buffer;
   buffer.reserve(1024);

   std::size_t line_count = 0;

   while (std::getline(stream,(buffer)))
   {
      if (buffer.empty())
         continue;
      else if ('#' == buffer[0])
         continue;

      ++line_count;
      sequence.push_back(buffer);
   }

   return line_count;
}

template <typename T>
inline bool run_test14()
{
   typedef exprtk::expression<T> expression_t;

   T x = T(0);
   T y = T(0);
   T z = T(0);
   T w = T(0);

   exprtk::polynomial<T, 1> poly01;
   exprtk::polynomial<T, 2> poly02;
   exprtk::polynomial<T, 3> poly03;
   exprtk::polynomial<T, 4> poly04;
   exprtk::polynomial<T, 5> poly05;
   exprtk::polynomial<T, 6> poly06;
   exprtk::polynomial<T, 7> poly07;
   exprtk::polynomial<T, 8> poly08;
   exprtk::polynomial<T, 9> poly09;
   exprtk::polynomial<T,10> poly10;
   exprtk::polynomial<T,11> poly11;
   exprtk::polynomial<T,12> poly12;

   exprtk::symbol_table<T> symbol_table;
   symbol_table.add_constants();
   symbol_table.add_variable("x",x);
   symbol_table.add_variable("y",y);
   symbol_table.add_variable("z",z);
   symbol_table.add_variable("w",w);
   symbol_table.add_function("poly01", poly01);
   symbol_table.add_function("poly02", poly02);
   symbol_table.add_function("poly03", poly03);
   symbol_table.add_function("poly04", poly04);
   symbol_table.add_function("poly05", poly05);
   symbol_table.add_function("poly06", poly06);
   symbol_table.add_function("poly07", poly07);
   symbol_table.add_function("poly08", poly08);
   symbol_table.add_function("poly09", poly09);
   symbol_table.add_function("poly10", poly10);
   symbol_table.add_function("poly11", poly11);
   symbol_table.add_function("poly12", poly12);

   expression_t expression;
   expression.register_symbol_table(symbol_table);

   exprtk::parser<T> parser;

   std::deque<std::string> expr_str_list;

   load_expressions("exprtk_functional_test.txt"    ,expr_str_list);
   load_expressions("exprtk_functional_ext_test.txt",expr_str_list);

   if (expr_str_list.empty())
   {
      return true;
   }

   std::deque<exprtk::expression<T> > expression_list;
   bool failure = false;
   static const std::size_t rounds = 5;

   for (std::size_t r = 0; r < rounds; ++r)
   {
      for (std::size_t i = 0; i < expr_str_list.size(); ++i)
      {
         exprtk::expression<T> current_expression;

         current_expression.register_symbol_table(symbol_table);

         if (!parser.compile(expr_str_list[i],current_expression))
         {
            printf("run_test14() - Error: %s   Expression: %s\n",
                   parser.error().c_str(),
                   expr_str_list[i].c_str());

            failure = true;
         }
         else
            expression_list.push_back(current_expression);
      }

      if (failure)
         break;

      for (std::size_t i = 0; i < expression_list.size(); ++i)
      {
         T result = expression_list[i].value();

         if (result != T(1))
         {
            failure = true;

            printf("run_test14() - Error with evaluation of expression: %s\n",
                   expr_str_list[i].c_str());
         }
      }

      expression_list.clear();

      if (failure)
         break;
   }

   return !failure;
}

template <typename T>
inline bool run_test15()
{
   typedef exprtk::expression<T> expression_t;

   T x = T(1.1);
   T y = T(2.2);
   T z = T(3.3);

   exprtk::symbol_table<T> symbol_table;
   symbol_table.add_constants();
   symbol_table.add_variable("x",x);
   symbol_table.add_variable("y",y);
   symbol_table.add_variable("z",z);

   static const std::string expr_str_list[] =
                               {
                                 "2 - (x + y) / z//Comment 01   ",
                                 "2 - (x + y) / z#Comment 02    ",
                                 "2 - (x + y) / z //Comment 03  ",
                                 "2 - (x + y) / z #Comment 04   ",
                                 "2 - (x + y) / z//Comment 05 \n",
                                 "2 - (x + y) / z#Comment 06  \n",
                                 "2 - (x + y) / z //Comment 07\n",
                                 "2 - (x + y) / z #Comment 08 \n",
                                 "/* Comment 09*/2 - (x + y) / z",
                                 "/* Comment 10*/2 - (x + y) / z\n",
                                 "/* Comment 11*/2 - (x + y) / z/* Comment 12*/",
                                 "/* Comment 13*/2 - (x + y) / z/* Comment 14*/\n",
                                 "2 - /* Comment 15 */(x + y) / z",
                                 "2 - /* Comment 16 */(x + y) /* Comment 17 *// z \n",
                                 "2 - /* Comment 18 */(x + y) /* Comment 19 */ / z //Comment 20\n",
                                 "2 - /* Comment 21 */(x + y) /* Comment 22 */ / z #Comment 23\n",
                                 "2 - /* Comment 24 */(x + y) /* Comment 25 */ / z //Comment 26",
                                 "2 - /* Comment 27 */(x + y) /* Comment 28 */ / z #Comment 29"
                               };
   static const std::size_t expr_str_list_size = sizeof(expr_str_list) / sizeof(std::string);

   std::deque<expression_t> expression_list;

   for (std::size_t i = 0; i < expr_str_list_size; ++i)
   {
      expression_t expression;
      expression.register_symbol_table(symbol_table);

      exprtk::parser<T> parser;

      if (!parser.compile(expr_str_list[i],expression))
      {
         printf("run_test15() - Error: %s   Expression: %s\n",
                parser.error().c_str(),
                expr_str_list[i].c_str());

         return false;
      }
      else
         expression_list.push_back(expression);
   }

   expression_t base_expression;
   const std::string base_expr_str = "2 - (x + y) / z";

   {
      base_expression.register_symbol_table(symbol_table);

      exprtk::parser<T> parser;

      if (!parser.compile(base_expr_str,base_expression))
      {
         printf("run_test15() - Error: %s   Expression: %s\n",
                parser.error().c_str(),
                base_expr_str.c_str());

         return false;
      }
   }

   bool failure = false;

   for (std::size_t i = 0; i < expression_list.size(); ++i)
   {
      T base_result = base_expression.value();
      T result      = expression_list[i].value();

      if (not_equal(base_result,result))
      {
         printf("run_test15() - Error in evaluation! (1)  Base: %20.10f\tResult: %20.10f\tExpression: %s\n",
                (double)base_result,
                (double)result,
                expr_str_list[i].c_str());

         failure = true;
      }
   }

   return !failure;
}

template <typename T>
struct base_func : public exprtk::ifunction<T>
{
   using exprtk::ifunction<T>::operator();

   typedef const T& type;
   base_func(const std::size_t& n) : exprtk::ifunction<T>(n) {}
   inline T operator()(type v0, type v1, type v2, type v3, type v4) override { return (v0 + v1 + v2 + v3 + v4); }
   inline T operator()(type v0, type v1, type v2, type v3) override { return (v0 + v1 + v2 + v3); }
   inline T operator()(type v0, type v1, type v2) override { return (v0 + v1 + v2); }
   inline T operator()(type v0, type v1) override { return (v0 + v1); }
   inline T operator()(type v0) override { return v0; }
   inline T operator()() override { return T(1.1234); }
};

template <typename T> struct test_func5 : public base_func<T> { test_func5() : base_func<T>(5){} };
template <typename T> struct test_func4 : public base_func<T> { test_func4() : base_func<T>(4){} };
template <typename T> struct test_func3 : public base_func<T> { test_func3() : base_func<T>(3){} };
template <typename T> struct test_func2 : public base_func<T> { test_func2() : base_func<T>(2){} };
template <typename T> struct test_func1 : public base_func<T> { test_func1() : base_func<T>(1){} };
template <typename T> struct test_func0 : public base_func<T> { test_func0() : base_func<T>(0){} };

template <typename T>
inline bool run_test16()
{
   typedef exprtk::expression<T> expression_t;

   T x = T(1.1);
   T y = T(2.2);
   T z = T(3.3);
   T w = T(4.4);
   T u = T(5.5);

   test_func0<T> test_func00;
   test_func1<T> test_func01;
   test_func2<T> test_func02;
   test_func3<T> test_func03;
   test_func4<T> test_func04;
   test_func5<T> test_func05;

   exprtk::symbol_table<T> symbol_table;
   symbol_table.add_constants();
   symbol_table.add_variable("x",x);
   symbol_table.add_variable("y",y);
   symbol_table.add_variable("z",z);
   symbol_table.add_variable("w",w);
   symbol_table.add_variable("u",u);

   symbol_table.add_function("test_func0",test_func00);
   symbol_table.add_function("test_func1",test_func01);
   symbol_table.add_function("test_func2",test_func02);
   symbol_table.add_function("test_func3",test_func03);
   symbol_table.add_function("test_func4",test_func04);
   symbol_table.add_function("test_func5",test_func05);

   static const std::string expr_str_list[] =
                               {
                                 "test_func0 = test_func0()",
                                 "test_func0 == test_func0()",
                                 "equal(1.1 + test_func0,test_func0() + 1.1)",
                                 "equal(test_func0 + 1.1,1.1 + test_func0())",
                                 "equal((1.1 + test_func0),(test_func0() + 1.1))",
                                 "equal((test_func0 + 1.1),(1.1 + test_func0()))",
                                 "equal(test_func0,test_func0())",
                                 "equal(test_func0,1.1234)",
                                 "equal(test_func0(),1.1234)",
                                 "equal(test_func0 + test_func0(),2 * 1.1234)",
                                 "equal((test_func0 + test_func0()),2 * 1.1234)",
                                 "equal((test_func0) + (test_func0()),2 * 1.1234)",
                                 "equal(test_func1(x),(x))",
                                 "equal(test_func2(x,y),(x + y))",
                                 "equal(test_func3(x,y,z),(x + y + z))",
                                 "equal(test_func4(x,y,z,w),(x + y + z + w))",
                                 "equal(test_func5(x,y,z,w,u),(x + y + z + w + u))",
                                 "equal(1.1 + test_func0,1.1234 + 1.1)",
                                 "equal(1.1 + test_func0(),1.1234 + 1.1)",
                                 "equal(1.1 + test_func1(x),(x + 1.1))",
                                 "equal(1.1 + test_func2(x,y),(x + y + 1.1))",
                                 "equal(1.1 + test_func3(x,y,z),(x + y + z + 1.1))",
                                 "equal(1.1 + test_func4(x,y,z,w),(x + y + z + w + 1.1))",
                                 "equal(1.1 + test_func5(x,y,z,w,u),(x + y + z + w + u + 1.1))",
                                 "equal(test_func0 + 2.2,1.1234 + 2.2)",
                                 "equal(test_func0() + 2.2,1.1234 + 2.2)",
                                 "equal(test_func1(x) + 2.2,(x + 2.2))",
                                 "equal(test_func2(x,y) + 2.2,(x + y + 2.2))",
                                 "equal(test_func3(x,y,z) + 2.2,(x + y + z + 2.2))",
                                 "equal(test_func4(x,y,z,w) + 2.2,(x + y + z + w + 2.2))",
                                 "equal(test_func5(x,y,z,w,u) + 2.2,(x + y + z + w + u + 2.2))",
                                 "equal({[test_func1(x)]},{[(x)]})",
                                 "equal({[test_func2(x,y)]},{[(x + y)]})",
                                 "equal({[test_func3(x,y,z)]},{[(x + y + z)]})",
                                 "equal({[test_func4(x,y,z,w)]},{[(x + y + z + w)]})",
                                 "equal({[test_func5(x,y,z,w,u)]},{[(x + y + z + w + u)]})",
                                 "equal(test_func1(2.12),(2.12))",
                                 "equal(test_func2(2.12,3.12),(2.12 + 3.12))",
                                 "equal(test_func3(2.12,3.12,4.12),(2.12 + 3.12 + 4.12))",
                                 "equal(test_func4(2.12,3.12,4.12,5.12),(2.12 + 3.12 + 4.12 + 5.12))",
                                 "equal(test_func5(2.12,3.12,4.12,5.12,6.12),(2.12 + 3.12 + 4.12 + 5.12 + 6.12))",
                                 "equal(1.1 + test_func1(2.12),(2.12 + 1.1))",
                                 "equal(1.1 + test_func2(2.12,3.12),(2.12 + 3.12 + 1.1))",
                                 "equal(1.1 + test_func3(2.12,3.12,4.12),(2.12 + 3.12 + 4.12 + 1.1))",
                                 "equal(1.1 + test_func4(2.12,3.12,4.12,5.12),(2.12 + 3.12 + 4.12 + 5.12 + 1.1))",
                                 "equal(1.1 + test_func5(2.12,3.12,4.12,5.12,6.12),(2.12 + 3.12 + 4.12 + 5.12 + 6.12 + 1.1))",
                                 "equal(test_func1(2.12) + 2.2,(2.12 + 2.2))",
                                 "equal(test_func2(2.12,3.12) + 2.2,(2.12 + 3.12 + 2.2))",
                                 "equal(test_func3(2.12,3.12,4.12) + 2.2,(2.12 + 3.12 + 4.12 + 2.2))",
                                 "equal(test_func4(2.12,3.12,4.12,5.12) + 2.2,(2.12 + 3.12 + 4.12 + 5.12 + 2.2))",
                                 "equal(test_func5(2.12,3.12,4.12,5.12,6.12) + 2.2,(2.12 + 3.12 + 4.12 + 5.12 + 6.12 + 2.2))",
                                 "equal({[test_func1(2.12)]},{[(2.12)]})",
                                 "equal({[test_func2(2.12,3.12)]},{[(2.12 + 3.12)]})",
                                 "equal({[test_func3(2.12,3.12,4.12)]},{[(2.12 + 3.12 + 4.12)]})",
                                 "equal({[test_func4(2.12,3.12,4.12,5.12)]},{[(2.12 + 3.12 + 4.12 + 5.12)]})",
                                 "equal({[test_func5(2.12,3.12,4.12,5.12,6.12)]},{[(2.12 + 3.12 + 4.12 + 5.12 + 6.12)]})",
                                 "TeSt_FuNc0 = tEsT_fUnC0()",
                                 "TEst_fuNC0 == tESt_fUNc0()",
                                 "EquaL(tEsT_FuNC1(x),(x))",
                                 "eQuAl(teSt_fUnc2(x,y),(x + y))",
                                 "EqUaL(tEsT_fUNc3(x,y,z),(x + y + z))",
                                 "EQUal(TEst_FunC4(x,y,z,w),(x + y + z + w))",
                                 "eqUAL(tEsT_FuNc5(x,y,z,w,u),(x + y + z + w + u))"
                               };
   static const std::size_t expr_str_list_size = sizeof(expr_str_list) / sizeof(std::string);

   std::deque<expression_t> expression_list;

   for (std::size_t i = 0; i < expr_str_list_size; ++i)
   {
      expression_t expression;
      expression.register_symbol_table(symbol_table);

      exprtk::parser<T> parser;

      if (!parser.compile(expr_str_list[i],expression))
      {
         printf("run_test16() - Error: %s   Expression: %s\n",
                parser.error().c_str(),
                expr_str_list[i].c_str());

         return false;
      }
      else
         expression_list.push_back(expression);
   }

   bool failure = false;

   for (std::size_t i = 0; i < expression_list.size(); ++i)
   {
      if (T(1) != expression_list[i].value())
      {
         printf("run_test16() - Error in evaluation! (1) Expression: %s\n",
                expr_str_list[i].c_str());

         failure = true;
      }
   }

   return !failure;
}

template <typename T>
inline bool run_test17()
{
   typedef exprtk::expression<T> expression_t;

   T x = T(1.1);
   T y = T(2.2);
   T z = T(3.3);
   T w = T(4.4);
   T u = T(5.5);
   T v = T(6.6);
   T t = T(7.7);

   T one  = T(1);
   T zero = T(0);

   exprtk::symbol_table<T> symbol_table;
   symbol_table.add_constants();
   symbol_table.add_variable("x",x);
   symbol_table.add_variable("y",y);
   symbol_table.add_variable("z",z);
   symbol_table.add_variable("w",w);
   symbol_table.add_variable("u",u);
   symbol_table.add_variable("v",v);
   symbol_table.add_variable("t",t);

   symbol_table.add_variable("one",one);
   symbol_table.add_variable("zero",zero);

   static const std::string expr_str_list[] =
                               {
                                 "equal(mand(one,one),1.0)",
                                 "equal(mand(one,zero),0.0)",
                                 "equal(mand(zero,one),0.0)",
                                 "equal(mand(zero,zero),0.0)",
                                 "equal(mand(one,one),1.0)",
                                 "equal(mand(one,one,one),1.0)",
                                 "equal(mand(one,one,one,one),1.0)",
                                 "equal(mand(one,one,one,one,one),1.0)",
                                 "equal(mand(one,one,zero),0.0)",
                                 "equal(mand(one,one,one,zero),0.0)",
                                 "equal(mand(one,one,one,one,zero),0.0)",
                                 "equal(mand(one,one,one,one,one,zero),0.0)",
                                 "equal(mor(one,one),1.0)",
                                 "equal(mor(one,zero),1.0)",
                                 "equal(mor(zero,one),1.0)",
                                 "equal(mor(zero,zero),0.0)",
                                 "equal(mor(one,one),1.0)",
                                 "equal(mor(one,one,zero),1.0)",
                                 "equal(mor(one,zero,one),1.0)",
                                 "equal(mor(one,zero,one,zero),1.0)",
                                 "equal(mor(zero,one),1.0)",
                                 "equal(mor(zero,zero,one),1.0)",
                                 "equal(mor(zero,zero,zero,zero,one),1.0)",
                                 "equal(mor(zero,zero,zero,zero,zero,one),1.0)",
                                 "equal(mor(zero,zero,zero,zero,zero,zero,zero,zero),0.0)",
                                 "equal((one nand one),not(mand(one,one)))",
                                 "equal((one nand zero),not(mand(one,zero)))",
                                 "equal((zero nand one),not(mand(zero,one)))",
                                 "equal((zero nand zero),not(mand(zero,zero)))",
                                 "equal((one nor one),not(mor(one,one)))",
                                 "equal((one nor zero),not(mor(one,zero)))",
                                 "equal((zero nor one),not(mor(zero,one)))",
                                 "equal((zero nor zero),not(mor(zero,zero)))",
                                 "equal(sum(x,y,z,w,u,v,t),(x+y+z+w+u+v+t))",
                                 "equal(sum(x+t,y+v,z+u,w+w,u+z,v+y,t+x),2*(x+y+z+w+u+v+t))",
                                 "equal(mul(x,y,z,w,u,v,t),(x*y*z*w*u*v*t))",
                                 "equal(mul(x*t,y*v,z*u,w*w,u*z,v*y,t*x),(x*y*z*w*u*v*t)^2)",
                                 "equal(sum(x,1.0,y,2.0,z,3.0,w,4.0,u,5.0,v,6.0,t),(x+y+z+w+u+v+t+21.0))",
                                 "equal(sum(x+1.0,y+2.0,z+3.0,w+4.0,u+5.0,v+6.0,t),(x+y+z+w+u+v+t+21.0))",
                                 "equal(mul(x,1.0,y,2.0,z,3.0,w,4.0,u,5.0,v,6.0,t),(x*y*z*w*u*v*t*720.0))",
                                 "equal(mul(x*1.0,y*2.0,z*3.0,w*4.0,u*5.0,v*6.0,t),(x*y*z*w*u*v*t*720.0))",
                                 "equal(min(x,y,z,w,u,v,t,zero),zero)",
                                 "equal(min(x+y,z+w,u+v,t,zero),zero)",
                                 "equal(max(one,x,y,z,w,u,v,t),t)",
                                 "equal(max(x+y,z+w,u+v,t,one),u+v)",
                                 "equal(avg(x,y,z,w,u,v,t),(x+y+z+w+u+v+t)/7.0)",
                                 "equal(avg(x+t,y+v,z+u,w+w,u+z,v+y,t+x),2/7*(x+y+z+w+u+v+t))"
                               };
   static const std::size_t expr_str_list_size = sizeof(expr_str_list) / sizeof(std::string);

   std::deque<expression_t> expression_list;

   for (std::size_t i = 0; i < expr_str_list_size; ++i)
   {
      expression_t expression;
      expression.register_symbol_table(symbol_table);

      exprtk::parser<T> parser;

      if (!parser.compile(expr_str_list[i],expression))
      {
         printf("run_test17() - Error: %s   Expression: %s\n",
                parser.error().c_str(),
                expr_str_list[i].c_str());

         return false;
      }
      else
         expression_list.push_back(expression);
   }

   bool failure = false;

   for (std::size_t i = 0; i < expression_list.size(); ++i)
   {
      if (T(1) != expression_list[i].value())
      {
         printf("run_test17() - Error in evaluation! (1) Expression: %s\n",
                expr_str_list[i].c_str());

         failure = true;
      }
   }

   return !failure;
}

template <typename T>
struct va_func : public exprtk::ivararg_function<T>
{
   va_func()
   {
      exprtk::enable_zero_parameters(*this);
      exprtk::set_min_num_args(*this,  0);
      exprtk::set_max_num_args(*this, 20);
   }

   inline T operator()(const std::vector<T>& arglist) override
   {
      T result = T(0);

      for (std::size_t i = 0; i < arglist.size(); ++i)
      {
         result += arglist[i];
      }

      return result;
   }
};

template <typename T>
struct gen_func : public exprtk::igeneric_function<T>
{
   typedef typename exprtk::igeneric_function<T>::generic_type generic_type;
   typedef typename exprtk::igeneric_function<T>::parameter_list_t parameter_list_t;

   typedef typename generic_type::scalar_view scalar_t;
   typedef typename generic_type::vector_view vector_t;
   typedef typename generic_type::string_view string_t;

   using exprtk::igeneric_function<T>::operator();

   gen_func()
   : scalar_count(0),
     vector_count(0),
     string_count(0)
   {}

   inline T operator()(parameter_list_t params) override
   {
      for (std::size_t i = 0; i < params.size(); ++i)
      {
         generic_type& gt = params[i];

         switch (gt.type)
         {
            case generic_type::e_scalar : scalar_count++;
                                          break;

            case generic_type::e_vector : vector_count++;
                                          break;

            case generic_type::e_string : {
                                             if (
                                                  ("CdEf"   != exprtk::to_str(string_t(gt))) &&
                                                  ("abc123" != exprtk::to_str(string_t(gt)))
                                                )
                                             {
                                                return std::numeric_limits<T>::quiet_NaN();
                                             }
                                             else
                                                string_count++;
                                          }
                                          break;

            default : return std::numeric_limits<T>::quiet_NaN();
         }
      }

      return T(0);
   }

   std::size_t scalar_count;
   std::size_t vector_count;
   std::size_t string_count;
};

template <typename T>
struct gen_func2 : public exprtk::igeneric_function<T>
{
   typedef typename exprtk::igeneric_function<T>::parameter_list_t parameter_list_t;

   using exprtk::igeneric_function<T>::operator();

   gen_func2()
   {}

   inline T operator()(parameter_list_t) override
   {
      return T(0);
   }

   inline T operator()(const std::size_t&, parameter_list_t params) override
   {
      return this->operator()(params);
   }
};

template <typename T>
struct inc_func : public exprtk::igeneric_function<T>
{
   typedef typename exprtk::igeneric_function<T>::generic_type generic_type;
   typedef typename exprtk::igeneric_function<T>::parameter_list_t parameter_list_t;

   typedef typename generic_type::scalar_view scalar_t;
   typedef typename generic_type::vector_view vector_t;
   typedef typename generic_type::string_view string_t;

   using exprtk::igeneric_function<T>::operator();

   inc_func()
   {}

   inline T operator()(parameter_list_t params) override
   {
      for (std::size_t i = 0; i < params.size(); ++i)
      {
         generic_type& gt = params[i];

         switch (gt.type)
         {
            case generic_type::e_scalar : {
                                             scalar_t scalar(gt);
                                             scalar() += T(1);
                                          }
                                          break;

            case generic_type::e_vector : {
                                             vector_t vector(gt);

                                             for (std::size_t x = 0; x < vector.size(); ++x)
                                             {
                                                vector[x] += T(1);
                                             }
                                          }
                                          break;

            case generic_type::e_string : {
                                             string_t string(gt);

                                             for (std::size_t x = 0; x < string.size(); ++x)
                                             {
                                                string[x] += static_cast<typename string_t::value_t>(1);
                                             }
                                          }
                                          break;

            default : return std::numeric_limits<T>::quiet_NaN();
         }
      }

      return T(0);
   }

   inline T operator()(const std::size_t&, parameter_list_t params) override
   {
      return this->operator()(params);
   }
};

template <typename T>
struct rem_space_and_uppercase : public exprtk::igeneric_function<T>
{
   typedef typename exprtk::igeneric_function<T> igenfunc_t;
   typedef typename igenfunc_t::generic_type     generic_type;
   typedef typename igenfunc_t::parameter_list_t parameter_list_t;
   typedef typename generic_type::string_view    string_t;

   using exprtk::igeneric_function<T>::operator();

   rem_space_and_uppercase()
   : igenfunc_t("S",igenfunc_t::e_rtrn_string)
   {}

   inline T operator()(std::string& result, parameter_list_t params) override
   {
      string_t string(params[0]);

      result.reserve(string.size());
      result.clear();

      char c;

      for (std::size_t i = 0; i < string.size(); ++i)
      {
         if (' ' != (c = string[i]))
            result += static_cast<char>(std::toupper(c));
      }

      return T(0);
   }

   inline T operator()(const std::size_t& param_seq_index, std::string& result, parameter_list_t params) override
   {
      if (1 == param_seq_index)
         return this->operator()(result,params);
      else
         return T(0);
   }
};

template <typename T>
struct vararg_func : public exprtk::igeneric_function<T>
{
   typedef typename exprtk::igeneric_function<T>::parameter_list_t
                                                  parameter_list_t;

   typedef typename exprtk::igeneric_function<T>::generic_type
                                                  generic_type;

   typedef typename generic_type::scalar_view scalar_t;
   typedef typename generic_type::vector_view vector_t;

   using exprtk::igeneric_function<T>::operator();

   vararg_func()
   : exprtk::igeneric_function<T>("Z|T*|V")
   {}

   inline T operator()(const std::size_t& ps_index, parameter_list_t /*arglist*/) override
   {
      switch (ps_index)
      {                         // Overload resolution:
         case 0  : return T(0); // Z  - Zero arguments
         case 1  : return T(1); // T* - One or more scalars
         case 2  : return T(2); // V  - One vector
         default : return std::numeric_limits<T>::quiet_NaN();
      }
   }
};

template <typename T>
struct vecrebase_func : public exprtk::igeneric_function<T>
{
   typedef typename exprtk::igeneric_function<T>::parameter_list_t
                                                  parameter_list_t;

   typedef typename exprtk::igeneric_function<T>::generic_type
                                                  generic_type;

   typedef typename generic_type::vector_view vector_t;

   using exprtk::igeneric_function<T>::operator();

   vecrebase_func()
   : exprtk::igeneric_function<T>("V")
   {}

   inline T operator()(parameter_list_t params) override
   {
      vector_t v(params[0]);
      return std::accumulate(v.begin(), v.end(), T(0));
   }
};

template <typename T>
struct overload_func : exprtk::igeneric_function<T>
{
   typedef typename exprtk::igeneric_function<T> igfun_t;
   typedef typename igfun_t::parameter_list_t    parameter_list_t;
   typedef typename igfun_t::generic_type        generic_type;
   typedef typename generic_type::vector_view    vector_t;

   using exprtk::igeneric_function<T>::operator();

   overload_func(const std::string& param_seq_list)
   : exprtk::igeneric_function<T>(param_seq_list, igfun_t::e_rtrn_overload),
     current_ps_index(std::numeric_limits<std::size_t>::max())
   {
      clear();
   }

   void clear()
   {
      current_ps_index  = std::numeric_limits<std::size_t>::max();
      current_param_seq = "";
   }

   inline T operator()(const std::size_t& ps_index,
                       parameter_list_t parameters) override
   {
      current_ps_index = ps_index;
      determine_param_seq(parameters);
      return T(1);
   }

   inline T operator()(const std::size_t& ps_index,
                       std::string& result,
                       parameter_list_t parameters) override
   {
      current_ps_index = ps_index;
      determine_param_seq(parameters);
      result = "string result";
      return T(1);
   }

   void determine_param_seq(parameter_list_t parameters)
   {
      current_param_seq = "";

      for (std::size_t i = 0; i < parameters.size(); ++i)
      {
         generic_type& gt = parameters[i];

         switch (gt.type)
         {
            case generic_type::e_scalar : current_param_seq += "T";
                                          break;

            case generic_type::e_vector : current_param_seq += "V";
                                          break;

            case generic_type::e_string : current_param_seq += "S";
                                          break;

            default                     : continue;
         }
      }
   }

   std::size_t current_ps_index;
   std::string current_param_seq;

   struct test_result_t
   {
      test_result_t(const std::size_t psi, const std::string& ps)
      : ps_index(psi),
        param_seq(ps)
      {}

      std::size_t ps_index;
      std::string param_seq;
   };
};

template <typename T>
inline bool run_test18()
{
   {
      typedef exprtk::expression<T> expression_t;

      T x = T(1.1);
      T y = T(2.2);
      T z = T(3.3);
      T w = T(4.4);
      T u = T(5.5);
      T v = T(6.6);
      T t = T(7.7);

      va_func<T> vaf;

      exprtk::symbol_table<T> symbol_table;
      symbol_table.add_constants();
      symbol_table.add_variable("x",x);
      symbol_table.add_variable("y",y);
      symbol_table.add_variable("z",z);
      symbol_table.add_variable("w",w);
      symbol_table.add_variable("u",u);
      symbol_table.add_variable("v",v);
      symbol_table.add_variable("t",t);
      symbol_table.add_function("va_func",vaf);

      static const std::string expr_str_list[] =
                                  {
                                    "equal(va_func,(0))",
                                    "equal(va_func(),(0))",
                                    "equal(va_func(1,2,3,4,5,6,7,8,9),(1+2+3+4+5+6+7+8+9))",
                                    "equal(va_func(1,x,3,y,5,z,7,w,9),(1+x+3+y+5+z+7+w+9))",
                                    "equal(va_func(x,2,y,4,z,6,w,8,u),(x+2+y+4+z+6+w+8+u))",
                                    "equal(va_func(x,y,z,w,u,v,t,1,2,3),(x+y+z+w+u+v+t+1+2+3))",
                                    "equal(va_func(x,y,z,w,u,v,t),(x+y+z+w+u+v+t))",
                                    "equal(va_func(x+t,y+v,z+u,w+w,u+z,v+y,t+x),2*(x+y+z+w+u+v+t))",
                                    "equal(1+va_func(1,x,3,y,5,z,7,w,9),(1+x+3+y+5+z+7+w+9)+1)",
                                    "equal(va_func(va_func(x,y,z,w,u,v,t),va_func(x,y,z,w,u,v,t)),2*(x+y+z+w+u+v+t))",
                                    "equal(va_func(va_func(x),va_func(y),va_func(z)),va_func(x,y,z))",
                                    "equal(va_func(va_func(va_func(va_func(va_func(va_func(va_func(va_func(x)))))))),x)",
                                    "equal(va_func(va_func(va_func(va_func(va_func(va_func(va_func(va_func(123.456)))))))),123.456)",
                                    "equal(va_func(va_func(va_func(va_func(va_func(va_func(va_func(va_func(x+1)))))))),x+1)",
                                    "equal(va_func(va_func(va_func(va_func(va_func(va_func(va_func(va_func(x+y)))))))),x+y)"
                                  };
      static const std::size_t expr_str_list_size = sizeof(expr_str_list) / sizeof(std::string);

      std::deque<expression_t> expression_list;

      for (std::size_t i = 0; i < expr_str_list_size; ++i)
      {
         expression_t expression;
         expression.register_symbol_table(symbol_table);

         exprtk::parser<T> parser;

         if (!parser.compile(expr_str_list[i],expression))
         {
            printf("run_test18() - VarArg Error: %s   Expression: %s\n",
                   parser.error().c_str(),
                   expr_str_list[i].c_str());

            return false;
         }
         else
            expression_list.push_back(expression);
      }

      bool failure = false;

      for (std::size_t i = 0; i < expression_list.size(); ++i)
      {
         if (T(1) != expression_list[i].value())
         {
            printf("run_test18() - Error in evaluation! (1) Expression: %s\n",
                   expr_str_list[i].c_str());

            failure = true;
         }
      }

      if (failure)
         return false;
   }

   {
      typedef exprtk::symbol_table<T> symbol_table_t;
      typedef exprtk::expression<T>     expression_t;
      typedef exprtk::parser<T>             parser_t;

      T x = T(33);
      T y = T(77);

      T v0[] = { T(1), T(1), T(1), T(1) };
      T v1[] = { T(1), T(2), T(3), T(4) };

      std::vector<T> v2;

      v2.push_back(T(5));
      v2.push_back(T(6));
      v2.push_back(T(7));
      v2.push_back(T(8));

      std::string s0 = "AbCdEfGhIj";

      gen_func<T> f;

      symbol_table_t symbol_table;

      symbol_table.add_constants();

      symbol_table.add_variable ("x"  , x);
      symbol_table.add_variable ("y"  , y);
      symbol_table.add_vector   ("v0" ,v0);
      symbol_table.add_vector   ("v1" ,v1);
      symbol_table.add_vector   ("v2" ,v2);
      symbol_table.add_stringvar("s0", s0);
      symbol_table.add_function ("gen_func", f);

      std::string expression_list[] =
                  {
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; gen_func(v0,v1 + v2, v0[2], x, 2x + y, z, 2w / 3, 'abc123',s0[2:5]);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; gen_func(v0,v1 + v2, v0[2], x, 2x + y, z, 2w / 3, 'abc123',s0[2:5]);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; gen_func(v1 + v2, v0[2], x, 2x + y, z, 2w / 3, 'abc123',s0[2:5],v0);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; gen_func(v0[2], x, 2x + y, z, 2w / 3, 'abc123',s0[2:5],v0, v1 + v2);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; gen_func(x, 2x + y, z, 2w / 3, 'abc123',s0[2:5],v0, v1 + v2, v0[2]);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; gen_func(2x + y, z, 2w / 3, 'abc123',s0[2:5],v0, v1 + v2, v0[2], x);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; gen_func(z, 2w / 3, 'abc123',s0[2:5],v0, v1 + v2, v0[2], x, 2x + y);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; gen_func(2w / 3, 'abc123',s0[2:5],v0, v1 + v2, v0[2], x, 2x + y, z);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; gen_func('abc123', s0[2:5],v0, v1 + v2, v0[2], x, 2x + y, z,2w / 3);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; gen_func(s0[2:5],v0, v1 + v2, v0[2], x, 2x + y, z,2w / 3, 'abc123');"
                  };

      static const std::size_t expression_list_size = sizeof(expression_list) / sizeof(std::string);

      bool failure = false;

      for (std::size_t i = 0; i < expression_list_size; ++i)
      {
         expression_t expression;

         expression.register_symbol_table(symbol_table);

         parser_t parser;

         if (!parser.compile(expression_list[i],expression))
         {
            printf("run_test18() - GenFunc Error: %s   Expression: %s [2]\n",
                   parser.error().c_str(),
                   expression_list[i].c_str());

            failure = true;
            continue;
         }

         f.scalar_count = 0;
         f.vector_count = 0;
         f.string_count = 0;

         expression.value();

         if (
              (4 != f.scalar_count) ||
              (3 != f.vector_count) ||
              (2 != f.string_count)
            )
         {
            printf("run_test18() - Error in evaluation! (2) Expression: %s  "
                   "sc_count = %d  "
                   "vr_count = %d  "
                   "st_count = %d\n",
                   expression_list[i].c_str(),
                   static_cast<int>(f.scalar_count),
                   static_cast<int>(f.vector_count),
                   static_cast<int>(f.string_count));

            failure = true;
         }
      }

      if (failure)
         return false;
   }

   {
      typedef exprtk::symbol_table<T> symbol_table_t;
      typedef exprtk::expression<T>     expression_t;
      typedef exprtk::parser<T>             parser_t;

      T x = T(33);
      T y = T(77);

      T v0[] = { T(1), T(1), T(1), T(1) };
      T v1[] = { T(1), T(2), T(3), T(4) };
      T v2[] = { T(5), T(6), T(7), T(8) };

      std::string s0 = "AbCdEfGhIj";

      gen_func2<T> f;

      symbol_table_t symbol_table;

      symbol_table.add_constants();

      symbol_table.add_variable ("x"  , x);
      symbol_table.add_variable ("y"  , y);
      symbol_table.add_vector   ("v0" ,v0);
      symbol_table.add_vector   ("v1" ,v1);
      symbol_table.add_vector   ("v2" ,v2);
      symbol_table.add_stringvar("s0", s0);
      symbol_table.add_function ("foo", f);

      std::string expression_list[] =
                  {
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(v0,v1 + v2, v0[2], x, 2x + y, z, 2w / 3, 'abc123',s0[2:5]);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(v1 + v2, v0[2], x, 2x + y, z, 2w / 3, 'abc123',s0[2:5],v0);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(v0[2], x, 2x + y, z, 2w / 3, 'abc123',s0[2:5],v0, v1 + v2);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(x, 2x + y, z, 2w / 3, 'abc123',s0[2:5],v0, v1 + v2, v0[2]);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(2x + y, z, 2w / 3, 'abc123',s0[2:5],v0, v1 + v2, v0[2], x);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(z, 2w / 3, 'abc123',s0[2:5],v0, v1 + v2, v0[2], x, 2x + y);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(2w / 3, 'abc123',s0[2:5],v0, v1 + v2, v0[2], x, 2x + y, z);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo('abc123', s0[2:5],v0, v1 + v2, v0[2], x, 2x + y, z,2w / 3);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(s0[2:5],v0, v1 + v2, v0[2], x, 2x + y, z,2w / 3, 'abc123');",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(s0[2:3]+s0[4:5],v0, v1 + v2, v0[2], x, 2x + y, z,2w / 3, 'abc123');",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(v0,v1 + v2, v0[2], x, 2x + y, z, 2w / 3, 'abc123',s0[2:5]);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(v0,v1 + v2, v0[2], x, 2x + y, z, 2w / 3, 'abc123',s0[2:5]);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(v0,v1 + v2, v0[2], x, 2x + y, z, 2w / 3, 'abc123',s0[2:5]);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(v0,v1 + v2, v0[2], x, 2x + y, z, 2w / 3, 'abc123',s0[2:5]);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(x);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(x,x);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(x,x,x);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(x,x,x,x);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(s0);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(s0,s0);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(s0,s0,s0);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(s0,s0,s0,s0);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(v0);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(v0,v0);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(v0,v0,v0);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(v0,v0,v0,v0);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(x);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(x,x);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(x,x,x);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(x,x,x,x);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(s0);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(s0,s0);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(s0,s0,s0);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(s0,s0,s0,s0);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(v0);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(v0,v0);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(v0,v0,v0);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(v0,v0,v0,v0);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(v0,v1 + v2, v0[2], x, 2x + y, z, 2w / 3, 'abc123',s0[2:5]);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(v0,v1 + v2, v0[2], x, 2x + y, z, 2w / 3, 'abc123',s0[2:5]);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(v0,v1 + v2, v0[2], x, 2x + y, z, 2w / 3, 'abc123',s0[2:5]);",
                    "var z := 3; var w[3] := { 1/3, 1/5, 1/7 }; foo(v0,v1 + v2, v0[2], x, 2x + y, z, 2w / 3, 'abc123',s0[2:5]);"
                  };

      static const std::size_t expression_list_size = sizeof(expression_list) / sizeof(std::string);

      std::string parameter_type_list[] =
                  {
                    "VVTTTTVSS",
                    "VTTTTVSSV",
                    "TTTTVSSVV",
                    "TTTVSSVVT",
                    "TTVSSVVT*",
                    "TVSSVVT*" ,
                    "VSSVVT*"  ,
                    "SSVVTTTTV",
                    "SVVTTTTVS",
                    "SVVTTTTVS",
                    "V*T*VS*"  ,
                    "V*TTTTVSS",
                    "VVT*VSS"  ,
                    "VVTTTTVS*",
                    "T*",
                    "T*",
                    "T*",
                    "T*",
                    "S*",
                    "S*",
                    "S*",
                    "S*",
                    "V*",
                    "V*",
                    "V*",
                    "V*",
                    "T",
                    "TT",
                    "TTT",
                    "TTTT",
                    "S",
                    "SS",
                    "SSS",
                    "SSSS",
                    "V",
                    "VV",
                    "VVV",
                    "VVVV",
                    "TTTTTTT|STSTSTS|V*T*VS*"  ,
                    "TTTTTTT|STSTSTS|V*TTTTVSS",
                    "TTTTTTT|STSTSTS|VVT*VSS"  ,
                    "TTTTTTT|STSTSTS|VVTTTTVS*",
                  };

      bool failure = false;

      for (std::size_t i = 0; i < expression_list_size; ++i)
      {
         expression_t expression;

         expression.register_symbol_table(symbol_table);

         parser_t parser;

         f.parameter_sequence = parameter_type_list[i];

         if (!parser.compile(expression_list[i],expression))
         {
            printf("run_test18() - GenFunc2 Error: %s   Expression: %s  Parameter Sequence: %s [3]\n",
                   parser.error().c_str(),
                   expression_list[i].c_str(),
                   parameter_type_list[i].c_str());

            failure = true;
            continue;
         }

         expression.value();
      }

      if (failure)
         return false;
   }

   {
      bool failure = false;

      std::string expression_list[] =
                  {
                    "foo(v0,v1,v2,x,y,s0);",
                    "foo(v1,v2,x,y,s0,v0);",
                    "foo(v2,x,y,s0,v0,v1);",
                    "foo(x,y,s0,v0,v1,v2);",
                    "foo(y,s0,v0,v1,v2,x);",
                    "foo(s0,v0,v1,v2,x,y);"
                  };

      static const std::size_t expression_list_size = sizeof(expression_list) / sizeof(std::string);

      std::string parameter_type_list[] =
                  {
                    "VVVTTS",
                    "VVTTSV",
                    "VTTSVV",
                    "TTSVVV",
                    "TSVVVT",
                    "SVVVTT"
                  };

      for (std::size_t i = 0; i < expression_list_size; ++i)
      {
         typedef exprtk::symbol_table<T> symbol_table_t;
         typedef exprtk::expression<T>     expression_t;
         typedef exprtk::parser<T>             parser_t;

         T x = T(33);
         T y = T(77);

         T v0[] = { T(1), T(1), T(1), T(1) };
         T v1[] = { T(1), T(2), T(3), T(4) };
         T v2[] = { T(5), T(6), T(7), T(8) };

         std::string s0 = "AbCdEfGhIj";

         T x_inc = T(34);
         T y_inc = T(78);

         T v0_inc[] = { T(2), T(2), T(2), T(2) };
         T v1_inc[] = { T(2), T(3), T(4), T(5) };
         T v2_inc[] = { T(6), T(7), T(8), T(9) };

         std::size_t sizeof_vec = sizeof(v0) / sizeof(T);

         std::string s0_inc = "BcDeFgHiJk";

         inc_func<T> f;

         symbol_table_t symbol_table;

         symbol_table.add_constants();

         symbol_table.add_variable ("x"  , x);
         symbol_table.add_variable ("y"  , y);
         symbol_table.add_vector   ("v0" ,v0);
         symbol_table.add_vector   ("v1" ,v1);
         symbol_table.add_vector   ("v2" ,v2);
         symbol_table.add_stringvar("s0", s0);
         symbol_table.add_function ("foo", f);

         expression_t expression;

         expression.register_symbol_table(symbol_table);

         parser_t parser;

         f.parameter_sequence = parameter_type_list[i];

         if (!parser.compile(expression_list[i],expression))
         {
            printf("run_test18() - IncFunc Error: %s   Expression: %s  Parameter Sequence: %s [4]\n",
                   parser.error().c_str(),
                   expression_list[i].c_str(),
                   parameter_type_list[i].c_str());

            failure = true;
            continue;
         }

         expression.value();

         if (x != x_inc)
         {
            printf("run_test18() - Error in evaluation! (3) Expression: %s  Check: x\n",
                   expression_list[i].c_str());
            failure = true;
         }

         if (y != y_inc)
         {
            printf("run_test18() - Error in evaluation! (3) Expression: %s  Check: y\n",
                   expression_list[i].c_str());
            failure = true;
         }

         if (s0 != s0_inc)
         {
            printf("run_test18() - Error in evaluation! (3) Expression: %s  Check: y\n",
                   expression_list[i].c_str());
            failure = true;
         }

         if (!std::equal(v0,v0 + sizeof_vec,v0_inc))
         {
            printf("run_test18() - Error in evaluation! (3) Expression: %s  Check: v0\n",
                   expression_list[i].c_str());
            failure = true;
         }

         if (!std::equal(v1,v1 + sizeof_vec,v1_inc))
         {
            printf("run_test18() - Error in evaluation! (3) Expression: %s  Check: v1\n",
                   expression_list[i].c_str());
            failure = true;
         }

         if (!std::equal(v2,v2 + sizeof_vec,v2_inc))
         {
            printf("run_test18() - Error in evaluation! (3) Expression: %s  Check: v2\n",
                   expression_list[i].c_str());
            failure = true;
         }
      }

      if (failure)
         return false;
   }

   {
      bool failure = false;

      rem_space_and_uppercase<T> rsauc;

      std::string s0 = "XXXXXXXXXXXXXXX";
      std::string s1 = "XXXXXXXXXXXXXXX";
      std::string s2 = "XXXXXXXXXXXXXXX";
      std::string s3 = "XXXXXXXXXXXXXXX";
      std::string s4 = "XXXXXXXXXXXXXXX";

      typedef exprtk::symbol_table<T> symbol_table_t;
      typedef exprtk::expression<T>     expression_t;
      typedef exprtk::parser<T>             parser_t;

      symbol_table_t symbol_table;

      symbol_table.add_constants();

      symbol_table.add_stringvar("s0", s0);
      symbol_table.add_stringvar("s1", s1);
      symbol_table.add_stringvar("s2", s2);
      symbol_table.add_stringvar("s3", s3);
      symbol_table.add_stringvar("s4", s4);

      symbol_table.add_function("remspc_uc",rsauc);

      std::string program = " s0 := 'How now ';                                   "
                            " s1 := 'brown cow?';                                 "
                            " s2 := remspc_uc(s0 + s1);                           "
                            " s3 := remspc_uc(s0) + s1;                           "
                            " s4 := s0 + remspc_uc(s1);                           "
                            " remspc_uc(s0 + s1) == remspc_uc(s0) + remspc_uc(s1);";

      std::string parameter_type_list[] =
                  {
                    "VVVTTT|S",
                    "VVTTTV|S",
                    "VTTTVV|S",
                    "TTTVVV|S",
                    "TTVVVT|S",
                    "TVVVTT|S"
                  };

      std::size_t parameter_type_list_size = sizeof(parameter_type_list) / sizeof(std::string);

      for (std::size_t i = 0; i < parameter_type_list_size; ++i)
      {
         expression_t expression;

         expression.register_symbol_table(symbol_table);

         parser_t parser;

         rsauc.parameter_sequence = parameter_type_list[i];

         if (!parser.compile(program,expression))
         {
            printf("run_test18() - Error: %s\tExpression: %s\n",
                   parser.error().c_str(),
                   program.c_str());

            return false;
         }

         T result = expression.value();

         if (result != T(1))
         {
            printf("run_test18() - Error in evaluation! (4) Expression: %s  Result <> 1\n",
                   program.c_str());
            failure = true;
         }

         if (result != T(1))
         {
            printf("run_test18() - Error in evaluation! (4) Expression: %s  Check: s0\n",
                   program.c_str());
            failure = true;
         }

         if ("How now " != s0)
         {
            printf("run_test18() - Error in evaluation! (4) Expression: %s  Check: s0\n",
                   program.c_str());
            failure = true;
         }

         if ("brown cow?" != s1)
         {
            printf("run_test18() - Error in evaluation! (4) Expression: %s  Check: s1\n",
                   program.c_str());
            failure = true;
         }

         if ("HOWNOWBROWNCOW?" != s2)
         {
            printf("run_test18() - Error in evaluation! (4) Expression: %s  Check: s2\n",
                   program.c_str());
            failure = true;
         }

         if ("HOWNOWbrown cow?" != s3)
         {
            printf("run_test18() - Error in evaluation! (4) Expression: %s  Check: s3\n",
                   program.c_str());
            failure = true;
         }

         if ("How now BROWNCOW?" != s4)
         {
            printf("run_test18() - Error in evaluation! (4) Expression: %s  Check: s4\n",
                   program.c_str());
            failure = true;
         }
      }

      if (failure)
         return false;
   }

   {
      bool failure = false;

      typedef exprtk::symbol_table<T> symbol_table_t;
      typedef exprtk::expression<T>     expression_t;
      typedef exprtk::parser<T>             parser_t;

      symbol_table_t symbol_table;

      T v[4] = {T(5), T(6), T(7), T(8)};

      symbol_table.add_vector("v",v);

      vararg_func<T> vaf;
      symbol_table.add_function("vararg_func",vaf);

      expression_t expression;
      expression.register_symbol_table(symbol_table);

      parser_t parser;

      std::string programs[] =
                     {
                        "equal(0,vararg_func())",
                        "equal(1,vararg_func() + 1)",
                        "equal(1,1 + vararg_func())",
                        "equal(1,vararg_func + 1)",
                        "equal(1,1 + vararg_func)",
                        "equal(0,vararg_func() + vararg_func)",
                        "equal(0,vararg_func + vararg_func())",
                        "equal(1,vararg_func + vararg_func(1))",
                        "equal(1,vararg_func + vararg_func(1,2))",
                        "equal(2,vararg_func + vararg_func(v))",
                        "equal(1,vararg_func() + vararg_func(1))",
                        "equal(1,vararg_func() + vararg_func(1,2))",
                        "equal(2,vararg_func() + vararg_func(v))",
                        "equal(2,vararg_func(v))",
                        "equal(1,vararg_func(1))",
                        "equal(1,vararg_func(1,2,3))",
                        "equal(1,vararg_func(5,6,7,8))",
                        "equal(5,vararg_func(v) + 3)",
                        "equal(5,vararg_func(1) + 4)",
                        "equal(6,vararg_func(1,2,3) + 5)",
                        "equal(7,vararg_func(5,6,7,8) + 6)"
                     };

      static const std::size_t programs_size = sizeof(programs) / sizeof(std::string);

      for (std::size_t i = 0; i < programs_size; ++i)
      {
         if (!parser.compile(programs[i],expression))
         {
            printf("run_test18() - Error: %s\tExpression: %s\n",
                   parser.error().c_str(),
                   programs[i].c_str());

            failure = true;
         }
         else if (T(1) != expression.value())
         {
            printf("run_test18() - Error in evaluation! (5) Expression: %s\n",
                   programs[i].c_str());

            failure = true;
         }
      }

      if (failure)
         return false;
   }

   {
      bool failure = false;

      typedef exprtk::symbol_table<T> symbol_table_t;
      typedef exprtk::expression<T>     expression_t;
      typedef exprtk::parser<T>             parser_t;

      std::vector<T> v0;
      std::vector<T> v1;
      std::vector<T> v2;
      std::vector<T> v3;

      #define pb(v,N)    \
      v.push_back(T(N)); \

      pb(v0,0) pb(v0,0) pb(v0,0) pb(v0,0) pb(v0,0) pb(v0, 0) pb(v0, 0)
      pb(v1,0) pb(v1,2) pb(v1,4) pb(v1,6) pb(v1,8) pb(v1,10) pb(v1,12)
      pb(v2,1) pb(v2,3) pb(v2,5) pb(v2,7) pb(v2,9) pb(v2,11) pb(v2,13)
      pb(v3,0) pb(v3,1) pb(v3,2) pb(v3,3) pb(v3,4) pb(v3, 5) pb(v3, 6)
      #undef pb

      const std::string expr_string = "sum(v + 1)";

      exprtk::vector_view<T> v = exprtk::make_vector_view(v0,v0.size());

      symbol_table_t symbol_table;
      symbol_table.add_vector("v",v);

      expression_t expression;
      expression.register_symbol_table(symbol_table);

      parser_t parser;

      if (!parser.compile(expr_string,expression))
      {
         printf("run_test18() - Error: %s\tExpression: %s\n",
                parser.error().c_str(),
                expr_string.c_str());

         failure = true;
      }

      T sum = { T(0) };

      sum = expression.value();

      if (not_equal(sum,T(7)))
      {
         printf("run_test18() - Error in evaluation! (6) Expression: %s\n",
                expr_string.c_str());
         failure = true;
      }

      v.rebase(v1.data());
      sum = expression.value();

      if (not_equal(sum,T(49)))
      {
         printf("run_test18() - Error in evaluation! (7) Expression: %s\n",
                expr_string.c_str());
         failure = true;
      }

      v.rebase(v2.data());
      sum = expression.value();

      if (not_equal(sum,T(56)))
      {
         printf("run_test18() - Error in evaluation! (8) Expression: %s\n",
                expr_string.c_str());
         failure = true;
      }

      v.rebase(v3.data());
      sum = expression.value();

      if (not_equal(sum,T(28)))
      {
         printf("run_test18() - Error in evaluation! (9) Expression: %s\n",
                expr_string.c_str());
         failure = true;
      }

      if (failure)
         return false;
   }

   {
      bool failure = false;

      typedef exprtk::symbol_table<T> symbol_table_t;
      typedef exprtk::expression<T>     expression_t;
      typedef exprtk::parser<T>             parser_t;

      std::vector<T> v0;
      std::vector<T> s;

      #define pb(v,N)    \
      v.push_back(T(N)); \

      pb(v0,0) pb(v0,1) pb(v0,2) pb(v0,3) pb(v0,4)
      pb(v0,5) pb(v0,6) pb(v0,7) pb(v0,8) pb(v0,9)

      pb(s, 3) pb(s, 6) pb(s, 9) pb(s,12)
      pb(s,15) pb(s,18) pb(s,21)
      #undef pb

      const std::string expr_string = "v[0] + v[1] + v[2]";

      exprtk::vector_view<T> v = exprtk::make_vector_view(v0,4);

      symbol_table_t symbol_table;
      symbol_table.add_vector("v",v);

      expression_t expression;
      expression.register_symbol_table(symbol_table);

      parser_t parser;

      if (!parser.compile(expr_string,expression))
      {
         printf("run_test18() - Error: %s\tExpression: %s\n",
                parser.error().c_str(),
                expr_string.c_str());

         failure = true;
      }

      for (std::size_t i = 0; i < v0.size() - 4; ++i)
      {
         v.rebase(v0.data() + i);

         T sum = expression.value();

         if (not_equal(sum,s[i]))
         {
            printf("run_test18() - Error in evaluation! (7) Expression: %s  Expected: %5.3f  Computed: %5.3f\n",
                   expr_string.c_str(),
                   s[i],
                   sum);

            failure = true;
         }

      }

      if (failure)
         return false;
   }

   {
      bool failure = false;

      typedef exprtk::symbol_table<T> symbol_table_t;
      typedef exprtk::expression<T>     expression_t;
      typedef exprtk::parser<T>             parser_t;

      std::vector<T> v0;
      std::vector<T> s;

      #define pb(v,N)    \
      v.push_back(T(N)); \

      pb(v0,0) pb(v0,1) pb(v0,2) pb(v0,3) pb(v0,4)
      pb(v0,5) pb(v0,6) pb(v0,7) pb(v0,8) pb(v0,9)

      pb(s, 3) pb(s, 6) pb(s, 9) pb(s,12)
      pb(s,15) pb(s,18) pb(s,21)
      #undef pb

      const std::string expr_string = "var i := 0; var j := 1; var k := 2; v[i] + v[j] + v[k]";

      exprtk::vector_view<T> v = exprtk::make_vector_view(v0,4);

      symbol_table_t symbol_table;
      symbol_table.add_vector("v",v);

      expression_t expression;
      expression.register_symbol_table(symbol_table);

      parser_t parser;

      if (!parser.compile(expr_string,expression))
      {
         printf("run_test18() - Error: %s\tExpression: %s\n",
                parser.error().c_str(),
                expr_string.c_str());

         failure = true;
      }

      for (std::size_t i = 0; i < v0.size() - 4; ++i)
      {
         v.rebase(v0.data() + i);

         T sum = expression.value();

         if (not_equal(sum,s[i]))
         {
            printf("run_test18() - Error in evaluation! (8) Expression: %s  Expected: %5.3f  Computed: %5.3f\n",
                   expr_string.c_str(),
                   s[i],
                   sum);

            failure = true;
         }

      }

      if (failure)
         return false;
   }

   {
      bool failure = false;

      typedef exprtk::symbol_table<T> symbol_table_t;
      typedef exprtk::expression<T>     expression_t;
      typedef exprtk::parser<T>             parser_t;

      std::vector<T> v0;
      std::vector<T> s;

      #define pb(v,N)    \
      v.push_back(T(N)); \

      pb(v0,0) pb(v0,1) pb(v0,2) pb(v0,3) pb(v0,4)
      pb(v0,5) pb(v0,6) pb(v0,7) pb(v0,8) pb(v0,9)

      pb(s, 3) pb(s, 6) pb(s, 9) pb(s,12)
      pb(s,15) pb(s,18) pb(s,21)
      #undef pb

      const std::string expr_string = "var i := 0; v[i + 0] + v[i + 1] + v[i + 2]";

      exprtk::vector_view<T> v = exprtk::make_vector_view(v0,4);

      symbol_table_t symbol_table;
      symbol_table.add_vector("v",v);

      expression_t expression;
      expression.register_symbol_table(symbol_table);

      parser_t parser;

      if (!parser.compile(expr_string,expression))
      {
         printf("run_test18() - Error: %s\tExpression: %s\n",
                parser.error().c_str(),
                expr_string.c_str());

         failure = true;
      }

      for (std::size_t i = 0; i < v0.size() - 4; ++i)
      {
         v.rebase(v0.data() + i);

         T sum = expression.value();

         if (not_equal(sum,s[i]))
         {
            printf("run_test18() - Error in evaluation! (9) Expression: %s  Expected: %5.3f  Computed: %5.3f\n",
                   expr_string.c_str(),
                   s[i],
                   sum);

            failure = true;
         }

      }

      if (failure)
         return false;
   }

   {
      typedef exprtk::symbol_table<T> symbol_table_t;
      typedef exprtk::expression<T>     expression_t;
      typedef exprtk::parser<T>             parser_t;

      T v0[] = { T(0), T(1), T(2), T(3), T(4) };
      T v1[] = { T(5), T(6), T(7), T(8), T(9) };

      const std::size_t v0_size = sizeof(v0) / sizeof (T);
      const std::size_t v1_size = sizeof(v1) / sizeof (T);

      exprtk::vector_view<T> v = exprtk::make_vector_view(v0, v0_size);

      vecrebase_func<T> vec_sum;

      symbol_table_t symbol_table;
      symbol_table.add_vector("v",v);
      symbol_table.add_function("vec_sum",vec_sum);

      expression_t expression;
      expression.register_symbol_table(symbol_table);

      parser_t parser;

      const std::string expr_string = "vec_sum(v)";

      if (!parser.compile(expr_string,expression))
      {
         printf("run_test18() - Error: %s\tExpression: %s\n",
                parser.error().c_str(),
                expr_string.c_str());

         return false;
      }

      const T expected_result0 = std::accumulate(v0, v0 + v0_size,T(0));

      if (expression.value() != expected_result0)
      {
         printf("run_test18() - Error in evaluation! (10.1) Expression: %s  Expected: %5.3f  Computed: %5.3f\n",
                expr_string.c_str(),
                expected_result0,
                expression.value());

         return false;
      }

      v.rebase(v1);

      const T expected_result1 = std::accumulate(v1, v1 + v1_size,T(0));

      if (expression.value() != expected_result1)
      {
         printf("run_test18() - Error in evaluation! (10.2) Expression: %s  Expected: %5.3f  Computed: %5.3f\n",
                expr_string.c_str(),
                expected_result1,
                expression.value());

         return false;
      }
   }

   {
      bool failure = false;

      typedef exprtk::symbol_table<T> symbol_table_t;
      typedef exprtk::expression<T>     expression_t;
      typedef exprtk::parser<T>             parser_t;

      exprtk::rtl::vecops::package<T> vecops_pkg;

      symbol_table_t symbol_table;
      symbol_table.add_package(vecops_pkg);

      std::string expr_str_list[] =
                  {
                     "var v[9] := {1,2,3,4,5,6,7,8,9};  all_true(v) == true" ,
                     "var v[6] := {-1,-2,-3,-4,-5,-6};  all_true(v) == true" ,
                     "var v[8] := {1,2,3,0,0,0,0,0};    all_true(v) == false",
                     "var v[8] := {-1,-2,-3,0,0,0,0,0}; all_true(v) == false",
                     "var v[9] := {0,0,0,0,0,0,0,0,0};  all_true(v + 1) == true",

                     "var v[9] := {0,0,0,0,0,0,0,0,0};  all_false(v) == true"  ,
                     "var v[9] := {0,0,0,0,0,1,2,3,4};  all_false(v) == false" ,
                     "var v[8] := {0,0,0,0,0,-1,-2,-3}; all_false(v) == false" ,
                     "var v[9] := {1,1,1,1,1,1,1,1,1};  any_false(v - 1) == true",

                     "var v[9] := {0,0,0,0,0,0,0,0,1};  any_true(v) == true"  ,
                     "var v[9] := {0,0,0,0,1,0,0,0,0};  any_true(v) == true"  ,
                     "var v[9] := {0,0,0,0,0,0,0,0,0};  any_true(v) == false" ,
                     "var v[9] := {0,0,0,0,0,0,0,0,0};  any_true(v + 1) == true",

                     "var v[9] := {1,1,1,1,1,1,1,1,0};  any_false(v) == true"  ,
                     "var v[9] := {1,1,1,1,0,1,1,1,1};  any_false(v) == true"  ,
                     "var v[9] := {1,1,1,1,1,1,1,1,1};  any_false(v) == false" ,
                     "var v[9] := {1,1,1,1,1,1,1,1,1};  any_false(v - 1) == true",

                     "var v[9] := {0,0,0,0,0,0,0,0,0};  count(v) == 0"  ,
                     "var v[9] := {0,0,0,0,0,0,0,0,1};  count(v) == 1"  ,
                     "var v[9] := {0,0,0,0,0,0,0,2,1};  count(v) == 2"  ,
                     "var v[9] := {0,0,0,0,0,0,3,2,1};  count(v) == 3"  ,
                     "var v[9] := {0,0,0,0,0,0,0,0,0};  count(v + 1) == v[]",
                     "var v[9] := {1,1,1,1,1,1,1,1,1};  count(v - 1) == 0",

                     "var v[9] := {1,2,3,4,5,6,7,8,9};  var r[9] := [0]; copy(v,r); sum(v == r) == v[]",
                     "var v[9] := {1,2,3,4,5,6,7,8,9};  var r[9] := [0]; copy(v,0,8,r,0,8); sum(r) == 45",
                     "var v[9] := {1,2,3,4,5,6,7,8,9};  var r[9] := [0]; copy(v,1,7,r,1,7); sum(r) == 35",
                     "var v[9] := {1,2,3,4,5,6,7,8,9};  var r[5] := [0]; copy(v,0,4,r,0,4); sum(r) == 15",

                     "var v[5] := {1,2,3,4,5}; var r[5] := {4,5,1,2,3}; rol(v,3); sum(v == r) == v[]",
                     "var v[5] := {1,2,3,4,5}; var r[5] := {3,4,5,1,2}; ror(v,3); sum(v == r) == v[]",

                     "var v[5] := {1,2,3,4,5}; var r[5] := {3,4,5,1,2}; rol(v,2); sum(v == r) == v[]",
                     "var v[5] := {1,2,3,4,5}; var r[5] := {4,5,1,2,3}; ror(v,2); sum(v == r) == v[]",

                     "var v[5] := {1,2,3,4,5}; var r[5] := {1,3,4,2,5}; rol(v,1,1,3); sum(v == r) == v[]",
                     "var v[5] := {1,2,3,4,5}; var r[5] := {1,4,2,3,5}; ror(v,1,1,3); sum(v == r) == v[]",

                     "var v[5] := {1,2,3,4,5}; var r[5] := {3,4,5,0,0}; shftl(v,2); sum(v == r) == v[]",
                     "var v[5] := {1,2,3,4,5}; var r[5] := {5,0,0,0,0}; shftl(v,4); sum(v == r) == v[]",
                     "var v[5] := {1,2,3,4,5}; var r[5] := {0,0,0,0,0}; shftl(v,5); sum(v == r) == v[]",

                     "var v[5] := {1,2,3,4,5}; var r[5] := {0,0,1,2,3}; shftr(v,2); sum(v == r) == v[]",
                     "var v[5] := {1,2,3,4,5}; var r[5] := {0,0,0,0,1}; shftr(v,4); sum(v == r) == v[]",
                     "var v[5] := {1,2,3,4,5}; var r[5] := {0,0,0,0,0}; shftr(v,5); sum(v == r) == v[]",

                     "var v[5] := {1,2,3,4,5}; var r[5] := {1,3,4,0,5}; shftl(v,1,1,3); sum(v == r) == v[]",
                     "var v[5] := {1,2,3,4,5}; var r[5] := {1,0,2,3,5}; shftr(v,1,1,3); sum(v == r) == v[]",

                     "var v[5] := {1,3,5,2,4}; var r[5] := {1,2,3,4,5}; sort(v); sum(v == r) == v[]",
                     "var v[5] := {5,4,3,2,1}; var r[5] := {1,2,3,4,5}; sort(v); sum(v == r) == v[]",
                     "var v[5] := {1,4,2,3,5}; var r[5] := {1,2,3,4,5}; sort(v,1,3); sum(v == r) == v[]",
                     "var v[5] := {5,4,2,3,1}; var r[5] := {5,2,3,4,1}; sort(v,1,3); sum(v == r) == v[]",
                     "var v[5] := {3,1,2,4,5}; var r[5] := {1,2,3,4,5}; sort(v,0,2); sum(v == r) == v[]",
                     "var v[5] := {1,2,5,3,4}; var r[5] := {1,2,3,4,5}; sort(v,2,4); sum(v == r) == v[]",

                     "var v[5] := {1,3,5,2,4}; var r[5] := {1,2,3,4,5}; sort(v,'ascending'); sum(v == r) == v[]",
                     "var v[5] := {1,3,5,2,4}; var r[5] := {1,2,3,4,5}; sort(v,'aScEnDiNg'); sum(v == r) == v[]",
                     "var v[5] := {5,4,3,2,1}; var r[5] := {1,2,3,4,5}; sort(v,'ascending'); sum(v == r) == v[]",
                     "var v[5] := {1,4,2,3,5}; var r[5] := {1,2,3,4,5}; sort(v,'ascending',1,3); sum(v == r) == v[]",
                     "var v[5] := {3,1,2,4,5}; var r[5] := {1,2,3,4,5}; sort(v,'ascending',0,2); sum(v == r) == v[]",
                     "var v[5] := {1,2,5,3,4}; var r[5] := {1,2,3,4,5}; sort(v,'ascending',2,4); sum(v == r) == v[]",

                     "var v[5] := {1,3,5,2,4}; var r[5] := {5,4,3,2,1}; sort(v,'descending'); sum(v == r) == v[]",
                     "var v[5] := {1,3,5,2,4}; var r[5] := {5,4,3,2,1}; sort(v,'DeScEnDiNg'); sum(v == r) == v[]",
                     "var v[5] := {5,4,3,2,1}; var r[5] := {5,4,3,2,1}; sort(v,'descending'); sum(v == r) == v[]",
                     "var v[5] := {1,4,2,3,5}; var r[5] := {1,4,3,2,5}; sort(v,'descending',1,3); sum(v == r) == v[]",
                     "var v[5] := {3,1,2,4,5}; var r[5] := {3,2,1,4,5}; sort(v,'descending',0,2); sum(v == r) == v[]",
                     "var v[5] := {1,2,5,3,4}; var r[5] := {1,2,5,4,3}; sort(v,'descending',2,4); sum(v == r) == v[]",

                     "var v[9] := {7,8,9,1,2,3,4,5,6}; nth_element(v,trunc(v[] / 2)); v[v[] / 2] == 5",
                     "var v[9] := {7,8,9,1,2,3,4,5,6}; nth_element(v,trunc(v[] / 3)); v[v[] / 3] == 4",

                     "var v[9] := {7,8,9,1,2,3,4,5,6}; nth_element(v,trunc(v[] / 2)); sort(v,0,trunc(v[] / 2)); (v[v[] / 2] == 5) and (v[0] == 1)",
                     "var v[9] := {7,8,9,1,2,3,4,5,6}; nth_element(v,trunc(v[] / 3)); sort(v,0,trunc(v[] / 3)); (v[v[] / 3] == 4) and (v[0] == 1)",

                     "var v[5]; iota(v,2);      var r[5] := {0,2,4,6,8}; sum(v == r) == v[]",
                     "var v[5]; iota(v,2,1);    var r[5] := {1,3,5,7,9}; sum(v == r) == v[]",
                     "var v[5]; iota(v,1,1,3);  var r[5] := {0,0,1,2,0}; sum(v == r) == v[]",
                     "var v[5]; iota(v,2,2,1,3);var r[5] := {0,2,4,6,0}; sum(v == r) == v[]",
                     "var v[5]; iota(v,2,1,1,3);var r[5] := {0,1,3,5,0}; sum(v == r) == v[]",

                     " var a := 2; var x[3] := {1,2,3}; var y[3] := {1,2,3}; var r[3] := [0]; r := a * x + y; axpy(a,x,y); sum(y == r) == y[]",
                     " var a := 2; var b := 3; var x[3] := {1,2,3}; var y[3] := {1,2,3}; var r[3] := [0]; r := a * x + b * y; axpby(a,x,b,y); sum(y == r) == y[]",

                     " var a := 2; var x[3] := {1,2,3}; var y[3] := {1,2,3}; var z[3] := [0]; var r[3] := [0]; r := a * x + y; axpyz(a,x,y,z); sum(z == r) == z[]",
                     " var a := 2; var b := 3; var x[3] := {1,2,3}; var y[3] := {1,2,3}; var z[3] := [0]; var r[3] := [0]; r := a * x + b * y; axpbyz(a,x,b,y,z); sum(z == r) == z[]",
                     " var a := 2; var b := 3; var x[3] := {1,2,3}; var z[3] := [0]; var r[3] := [0]; r := a * x + b; axpbz(a,x,b,z); sum(z == r) == z[]",
                  };

      const std::size_t expr_str_list_size = sizeof(expr_str_list) / sizeof(std::string);

      parser_t parser;

      for (std::size_t i = 0; i < expr_str_list_size; ++i)
      {
         expression_t expression;
         expression.register_symbol_table(symbol_table);

         if (!parser.compile(expr_str_list[i], expression))
         {
            printf("run_test18() - Error: %s   Expression: %s\n",
                   parser.error().c_str(),
                   expr_str_list[i].c_str());

            failure = true;

            continue;
         }

         T result = expression.value();

         if (result != T(1))
         {
            printf("run_test18() - Error in evaluation! (11) Expression: %s\n",
                   expr_str_list[i].c_str());

            failure = true;
         }
      }

      if (failure)
         return false;
   }

   {
      typedef exprtk::expression<T> expression_t;

      std::string a = "a";
      std::string b = "b";
      std::string c = "c";
      std::string d = "d";

      T x = T(1.1);
      T y = T(2.2);
      T z = T(3.3);
      T w = T(4.4);

      overload_func<T> ovrld_func
                        (
                          "T:T|T:TT|T:TTT|T:TTTT|"
                          "T:S|T:SS|T:SSS|T:SSSS|"
                          "T:ST|T:STS|T:STST|"
                          "T:TS|T:TST|T:TSTS|"
                          "T:TTSS|T:SSTT|T:STTS|T:TSST"
                        );

      exprtk::symbol_table<T> symbol_table;

      symbol_table.add_constants();
      symbol_table.add_variable ("x",x);
      symbol_table.add_variable ("y",y);
      symbol_table.add_variable ("z",z);
      symbol_table.add_variable ("w",w);

      symbol_table.add_stringvar("a",a);
      symbol_table.add_stringvar("b",b);
      symbol_table.add_stringvar("c",c);
      symbol_table.add_stringvar("d",d);

      symbol_table.add_function("foo",ovrld_func);

      typedef typename overload_func<T>::test_result_t test_result_t;
      typedef std::pair<std::string, typename overload_func<T>::test_result_t> test_pack_t;

      static const test_pack_t test_pack_list[] =
                                  {
                                    test_pack_t("foo(x)"                          , test_result_t( 0, "T"   )),
                                    test_pack_t("foo(x, y)"                       , test_result_t( 1, "TT"  )),
                                    test_pack_t("foo(x, y, z)"                    , test_result_t( 2, "TTT" )),
                                    test_pack_t("foo(x, y, z, w)"                 , test_result_t( 3, "TTTT")),
                                    test_pack_t("foo(x + y)"                      , test_result_t( 0, "T"   )),
                                    test_pack_t("foo(x + y, y + z)"               , test_result_t( 1, "TT"  )),
                                    test_pack_t("foo(x + y, y + z, z + w)"        , test_result_t( 2, "TTT" )),
                                    test_pack_t("foo(x + y, y + z, z + w, w)"     , test_result_t( 3, "TTTT")),
                                    test_pack_t("foo(a)"                          , test_result_t( 4, "S"   )),
                                    test_pack_t("foo(a, b)"                       , test_result_t( 5, "SS"  )),
                                    test_pack_t("foo(a, b, c)"                    , test_result_t( 6, "SSS" )),
                                    test_pack_t("foo(a, b, c, d)"                 , test_result_t( 7, "SSSS")),
                                    test_pack_t("foo(a + b)"                      , test_result_t( 4, "S"   )),
                                    test_pack_t("foo(a + b, b + c)"               , test_result_t( 5, "SS"  )),
                                    test_pack_t("foo(a + b, b + c, c + d)"        , test_result_t( 6, "SSS" )),
                                    test_pack_t("foo(a + b, b + c, c + d, d)"     , test_result_t( 7, "SSSS")),
                                    test_pack_t("foo(a, x)"                       , test_result_t( 8, "ST"  )),
                                    test_pack_t("foo(a, x, b)"                    , test_result_t( 9, "STS" )),
                                    test_pack_t("foo(a, x, b, y)"                 , test_result_t(10, "STST")),
                                    test_pack_t("foo(a + b, x + y)"               , test_result_t( 8, "ST"  )),
                                    test_pack_t("foo(a + b, x + y, b + c)"        , test_result_t( 9, "STS" )),
                                    test_pack_t("foo(a + b, x + y, b + c, y + z)" , test_result_t(10, "STST")),
                                    test_pack_t("foo(x, a)"                       , test_result_t(11, "TS"  )),
                                    test_pack_t("foo(x, a, y)"                    , test_result_t(12, "TST" )),
                                    test_pack_t("foo(x, a, y, b)"                 , test_result_t(13, "TSTS")),
                                    test_pack_t("foo(x + y, a + b)"               , test_result_t(11, "TS"  )),
                                    test_pack_t("foo(x + y, a + b, y + z)"        , test_result_t(12, "TST" )),
                                    test_pack_t("foo(x + y, a + b, y + z, b + c)" , test_result_t(13, "TSTS")),
                                    test_pack_t("foo(x, y, a, b)"                 , test_result_t(14, "TTSS")),
                                    test_pack_t("foo(a, b, x, y)"                 , test_result_t(15, "SSTT")),
                                    test_pack_t("foo(a, x, y, b)"                 , test_result_t(16, "STTS")),
                                    test_pack_t("foo(x, a, b, y)"                 , test_result_t(17, "TSST")),
                                    test_pack_t("foo(x + y, y + z, a + b, b + c)" , test_result_t(14, "TTSS")),
                                    test_pack_t("foo(a + b, b + c, x + y, y + z)" , test_result_t(15, "SSTT")),
                                    test_pack_t("foo(a + b, x + y, y + z, b + c)" , test_result_t(16, "STTS")),
                                    test_pack_t("foo(x + y, a + b, b + c, y + z)" , test_result_t(17, "TSST"))
                                  };

      static const std::size_t test_pack_list_size = sizeof(test_pack_list) / sizeof(test_pack_t);

      std::deque<expression_t> expression_list;

      for (std::size_t i = 0; i < test_pack_list_size; ++i)
      {
         expression_t expression;
         expression.register_symbol_table(symbol_table);

         exprtk::parser<T> parser;

         if (!parser.compile(test_pack_list[i].first, expression))
         {
            printf("run_test18() - (12) Overload VarArg Error: %s   Expression: %s\n",
                   parser.error().c_str(),
                   test_pack_list[i].first.c_str());

            return false;
         }
         else
            expression_list.push_back(expression);
      }

      bool failure = false;

      for (std::size_t i = 0; i < expression_list.size(); ++i)
      {
         ovrld_func.clear();

         if (T(1) != expression_list[i].value())
         {
            printf("run_test18() - Error in evaluation! (12) Expression: %s\n",
                   test_pack_list[i].first.c_str());

            failure = true;
         }

         if (ovrld_func.current_ps_index != test_pack_list[i].second.ps_index)
         {
            printf("run_test18() - Error with ps_index (12) Expression: %s  Expected: %d  Got: %d\n",
                   test_pack_list[i].first.c_str(),
                   static_cast<int>(test_pack_list[i].second.ps_index),
                   static_cast<int>(ovrld_func.current_ps_index));

            failure = true;
         }

         if (ovrld_func.current_param_seq != test_pack_list[i].second.param_seq)
         {
            printf("run_test18() - Error with parameter seq (12) Expression: %s  Expected: %s  Got: %s\n",
                   test_pack_list[i].first.c_str(),
                   test_pack_list[i].second.param_seq.c_str(),
                   ovrld_func.current_param_seq.c_str());

            failure = true;
         }
         ::fflush(stdout);
      }

      if (failure)
         return false;
   }

   {
      typedef exprtk::expression<T> expression_t;

      std::string a = "a";
      std::string b = "b";
      std::string c = "c";
      std::string d = "d";
      std::string result = "";

      T x = T(1.1);
      T y = T(2.2);
      T z = T(3.3);
      T w = T(4.4);

      overload_func<T> ovrld_func
                        (
                          "S:T|S:TT|S:TTT|S:TTTT|"
                          "S:S|S:SS|S:SSS|S:SSSS|"
                          "S:ST|S:STS|S:STST|"
                          "S:TS|S:TST|S:TSTS|"
                          "S:TTSS|S:SSTT|S:STTS|S:TSST"
                        );

      exprtk::symbol_table<T> symbol_table;

      symbol_table.add_constants();
      symbol_table.add_variable ("x",x);
      symbol_table.add_variable ("y",y);
      symbol_table.add_variable ("z",z);
      symbol_table.add_variable ("w",w);

      symbol_table.add_stringvar("a",a);
      symbol_table.add_stringvar("b",b);
      symbol_table.add_stringvar("c",c);
      symbol_table.add_stringvar("d",d);
      symbol_table.add_stringvar("result",result);

      symbol_table.add_function("foo",ovrld_func);

      typedef typename overload_func<T>::test_result_t test_result_t;
      typedef std::pair<std::string, typename overload_func<T>::test_result_t> test_pack_t;

      static const test_pack_t test_pack_list[] =
                                  {
                                    test_pack_t("result := foo(x)"                          , test_result_t( 0, "T"   )),
                                    test_pack_t("result := foo(x, y)"                       , test_result_t( 1, "TT"  )),
                                    test_pack_t("result := foo(x, y, z)"                    , test_result_t( 2, "TTT" )),
                                    test_pack_t("result := foo(x, y, z, w)"                 , test_result_t( 3, "TTTT")),
                                    test_pack_t("result := foo(x + y)"                      , test_result_t( 0, "T"   )),
                                    test_pack_t("result := foo(x + y, y + z)"               , test_result_t( 1, "TT"  )),
                                    test_pack_t("result := foo(x + y, y + z, z + w)"        , test_result_t( 2, "TTT" )),
                                    test_pack_t("result := foo(x + y, y + z, z + w, w)"     , test_result_t( 3, "TTTT")),
                                    test_pack_t("result := foo(a)"                          , test_result_t( 4, "S"   )),
                                    test_pack_t("result := foo(a, b)"                       , test_result_t( 5, "SS"  )),
                                    test_pack_t("result := foo(a, b, c)"                    , test_result_t( 6, "SSS" )),
                                    test_pack_t("result := foo(a, b, c, d)"                 , test_result_t( 7, "SSSS")),
                                    test_pack_t("result := foo(a + b)"                      , test_result_t( 4, "S"   )),
                                    test_pack_t("result := foo(a + b, b + c)"               , test_result_t( 5, "SS"  )),
                                    test_pack_t("result := foo(a + b, b + c, c + d)"        , test_result_t( 6, "SSS" )),
                                    test_pack_t("result := foo(a + b, b + c, c + d, d)"     , test_result_t( 7, "SSSS")),
                                    test_pack_t("result := foo(a, x)"                       , test_result_t( 8, "ST"  )),
                                    test_pack_t("result := foo(a, x, b)"                    , test_result_t( 9, "STS" )),
                                    test_pack_t("result := foo(a, x, b, y)"                 , test_result_t(10, "STST")),
                                    test_pack_t("result := foo(a + b, x + y)"               , test_result_t( 8, "ST"  )),
                                    test_pack_t("result := foo(a + b, x + y, b + c)"        , test_result_t( 9, "STS" )),
                                    test_pack_t("result := foo(a + b, x + y, b + c, y + z)" , test_result_t(10, "STST")),
                                    test_pack_t("result := foo(x, a)"                       , test_result_t(11, "TS"  )),
                                    test_pack_t("result := foo(x, a, y)"                    , test_result_t(12, "TST" )),
                                    test_pack_t("result := foo(x, a, y, b)"                 , test_result_t(13, "TSTS")),
                                    test_pack_t("result := foo(x + y, a + b)"               , test_result_t(11, "TS"  )),
                                    test_pack_t("result := foo(x + y, a + b, y + z)"        , test_result_t(12, "TST" )),
                                    test_pack_t("result := foo(x + y, a + b, y + z, b + c)" , test_result_t(13, "TSTS")),
                                    test_pack_t("result := foo(x, y, a, b)"                 , test_result_t(14, "TTSS")),
                                    test_pack_t("result := foo(a, b, x, y)"                 , test_result_t(15, "SSTT")),
                                    test_pack_t("result := foo(a, x, y, b)"                 , test_result_t(16, "STTS")),
                                    test_pack_t("result := foo(x, a, b, y)"                 , test_result_t(17, "TSST")),
                                    test_pack_t("result := foo(x + y, y + z, a + b, b + c)" , test_result_t(14, "TTSS")),
                                    test_pack_t("result := foo(a + b, b + c, x + y, y + z)" , test_result_t(15, "SSTT")),
                                    test_pack_t("result := foo(a + b, x + y, y + z, b + c)" , test_result_t(16, "STTS")),
                                    test_pack_t("result := foo(x + y, a + b, b + c, y + z)" , test_result_t(17, "TSST"))
                                  };

      static const std::size_t test_pack_list_size = sizeof(test_pack_list) / sizeof(test_pack_t);

      std::deque<expression_t> expression_list;

      for (std::size_t i = 0; i < test_pack_list_size; ++i)
      {
         expression_t expression;
         expression.register_symbol_table(symbol_table);

         exprtk::parser<T> parser;

         if (!parser.compile(test_pack_list[i].first, expression))
         {
            printf("run_test18() - (13) Overload VarArg Error: %s   Expression: %s\n",
                   parser.error().c_str(),
                   test_pack_list[i].first.c_str());

            return false;
         }
         else
            expression_list.push_back(expression);
      }

      bool failure = false;

      for (std::size_t i = 0; i < expression_list.size(); ++i)
      {
         ovrld_func.clear();
         result = "";
         expression_list[i].value();

         if (result != "string result")
         {
            printf("run_test18() - Error in evaluation! (13) Expression: %s\n",
                   test_pack_list[i].first.c_str());

            failure = true;
         }

         if (ovrld_func.current_ps_index != test_pack_list[i].second.ps_index)
         {
            printf("run_test18() - Error with ps_index (13) Expression: %s  Expected: %d  Got: %d\n",
                   test_pack_list[i].first.c_str(),
                   static_cast<int>(test_pack_list[i].second.ps_index),
                   static_cast<int>(ovrld_func.current_ps_index));

            failure = true;
         }

         if (ovrld_func.current_param_seq != test_pack_list[i].second.param_seq)
         {
            printf("run_test18() - Error with parameter seq (13) Expression: %s  Expected: %s  Got: %s\n",
                   test_pack_list[i].first.c_str(),
                   test_pack_list[i].second.param_seq.c_str(),
                   ovrld_func.current_param_seq.c_str());

            failure = true;
         }
      }

      if (failure)
         return false;
   }

   return true;
}

template <typename T>
inline bool run_test19()
{
   typedef exprtk::symbol_table<T>      symbol_table_t;
   typedef exprtk::expression<T>          expression_t;
   typedef exprtk::parser<T>                  parser_t;
   typedef exprtk::function_compositor<T> compositor_t;
   typedef typename compositor_t::function  function_t;

   {
      T x = T(123.123);

      compositor_t compositor;

      // f(x) = x + 2
      compositor.add(function_t("f","x + 2","x"));

      // g(x) = x^2-3
      compositor.add(function_t("g","x^2 - 3","x"));

      // fof(x) = f(f(x))
      compositor.add(function_t("fof","f(f(x))","x"));

      // gog(x) = g(g(x))
      compositor.add(function_t("gog","g(g(x))","x"));

      // fog(x) = f(g(x))
      compositor.add(function_t("fog","f(g(x))","x"));

      // gof(x) = g(f(x))
      compositor.add(function_t("gof","g(f(x))","x"));

      // fogof(x) = f(g(f(x)))
      compositor.add(function_t("fogof","f(g(f(x)))","x"));

      // gofog(x) = g(f(g(x)))
      compositor.add(function_t("gofog","g(f(g(x)))","x"));

      symbol_table_t& symbol_table = compositor.symbol_table();
      symbol_table.add_constants();
      symbol_table.add_variable("x",x);

      static const std::string expr_str_list[] =
                                 {
                                   "equal(f(x),(x + 2))",
                                   "equal(g(x),(x^2 - 3))",
                                   "equal(fof(x),(x + 4))",
                                   "equal(gog(x),(x^4 - 6x^2 + 6))",
                                   "equal(fog(x),(x^2 - 1))",
                                   "equal(gof(x),(x^2 + 4x + 1))",
                                   "equal(fogof(x),(x^2 + 4x + 3))",
                                   "equal(gofog(x),(x^4 - 2x^2 - 2))"
                                 };
      static const std::size_t expr_str_list_size = sizeof(expr_str_list) / sizeof(std::string);

      std::deque<expression_t> expression_list;

      for (std::size_t i = 0; i < expr_str_list_size; ++i)
      {
         expression_t expression;
         expression.register_symbol_table(symbol_table);

         parser_t parser;

         if (!parser.compile(expr_str_list[i],expression))
         {
            printf("run_test19() - Error: %s   Expression: %s\n",
                   parser.error().c_str(),
                   expr_str_list[i].c_str());

            return false;
         }
         else
            expression_list.push_back(expression);
      }

      bool failure = false;

      for (std::size_t i = 0; i < expression_list.size(); ++i)
      {
         if (T(1) != expression_list[i].value())
         {
            printf("run_test19() - Error in evaluation! (1) Expression: %s\n",
                   expr_str_list[i].c_str());

            failure = true;
         }
      }

      if (failure)
         return false;
   }

   const std::size_t rounds = 100;

   for (std::size_t r = 0; r < rounds; ++r)
   {
      T x = T(1);
      T y = T(2);
      T z = T(3);
      T w = T(4);
      T u = T(5);
      T v = T(6);

      compositor_t compositor;

      // f0() = 6
      compositor
         .add(
            function_t("f0")
              .expression("3 * 2"));

      // f1(x) = 5 * (f0 + x)
      compositor
         .add(
            function_t("f1")
              .var("x")
              .expression("5 * (f0 + x)"));

      // f2(x,y) = 7 * (f1(x) + f1(y))
      compositor
         .add(
            function_t("f2")
              .var("x").var("y")
              .expression("7 * (f1(x) + f1(y))"));

      // f3(x,y,z) = 9 * (f2(x,y) + f2(y,z) + f2(x,z))
      compositor
         .add(
            function_t("f3")
              .var("x").var("y").var("z")
              .expression("9 * (f2(x,y) + f2(y,z) + f2(x,z))"));

      // f4(x,y,z,w) = 11 * (f3(x,y,z) + f3(y,z,w) + f3(z,w,z))
      compositor
         .add(
            function_t("f4")
              .var("x").var("y").var("z").var("w")
              .expression("11 * (f3(x,y,z) + f3(y,z,w) + f3(z,w,x))"));

      // f5(x,y,z,w,u) = 13 * (f4(x,y,z,w) + f4(y,z,w,u) + f4(z,w,u,x) + f4(w,u,x,y))
      compositor
         .add(
            function_t("f5")
              .var("x").var("y").var("z").var("w").var("u")
              .expression("13 * (f4(x,y,z,w) + f4(y,z,w,u) + f4(z,w,u,x) + f4(w,u,x,y))"));

      // f6(x,y,z,w,u,v) = 17 * (f5(x,y,z,w,u) + f5(y,z,w,u,v) + f5(z,w,u,v,x) + f5(w,u,v,x,y))
      compositor
         .add(
            function_t("f6")
              .var("x").var("y").var("z")
              .var("w").var("u").var("v")
              .expression("17 * (f5(x,y,z,w,u) + f5(y,z,w,u,v) + f5(z,w,u,v,x) + f5(w,u,v,x,y))"));

      symbol_table_t& symbol_table = compositor.symbol_table();
      symbol_table.add_constants();
      symbol_table.add_variable("x",x);
      symbol_table.add_variable("y",y);
      symbol_table.add_variable("z",z);
      symbol_table.add_variable("w",w);
      symbol_table.add_variable("u",u);
      symbol_table.add_variable("v",v);

      parser_t parser;

      const std::string expr_str_list[] =
                          {
                            "f0()",
                            "f1(x)",
                            "f2(x,x)",
                            "f3(x,x,x)",
                            "f4(x,x,x,x)",
                            "f5(x,x,x,x,x)",
                            "f6(x,x,x,x,x,x)",
                            "f2(x,y)",
                            "f3(x,y,z)",
                            "f4(x,y,z,w)",
                            "f5(x,y,z,w,u)",
                            "f6(x,y,z,w,u,v)"
                          };
      const std::size_t expr_str_list_size = sizeof(expr_str_list) / sizeof(std::string);

      const T result_list[] =
                {
                  T(6         ),
                  T(35        ),
                  T(490       ),
                  T(13230     ),
                  T(436590    ),
                  T(22702680  ),
                  T(1543782240),
                  T(525       ),
                  T(15120     ),
                  T(533610    ),
                  T(29459430  ),
                  T(2122700580)
                };

      bool failure = false;

      for (std::size_t i = 0; i < expr_str_list_size; ++i)
      {
         expression_t expression;
         expression.register_symbol_table(symbol_table);

         if (!parser.compile(expr_str_list[i],expression))
         {
            printf("run_test19() - Error: %s   Expression: %s\n",
                   parser.error().c_str(),
                   expr_str_list[i].c_str());

            failure = true;
            continue;
         }

         T result = expression.value();

         if (result_list[i] != result)
         {
            printf("run_test19() - Error in evaluation! (2) Expression: %s Expected: %10.1f\tResult: %10.1f\n",
                   expr_str_list[i].c_str(),
                   result_list[i],
                   result);

            failure = true;
            continue;
         }
      }

      if (failure)
         return false;
   }

   {
      T x = T(0);

      compositor_t compositor;

      compositor
         .add(
         function_t(
              "is_prime_impl1",
              "if (y == 1,true,                "
              "   if (0 == (x % y),false,      "
              "      is_prime_impl1(x,y - 1))) ",
              "x","y"));

      compositor
         .add(
         function_t(
              "is_prime1",
              "if (frac(x) != 0, false,                                "
              "   if (x <= 0, false,                                   "
              "      is_prime_impl1(x,min(x - 1,trunc(sqrt(x)) + 1)))) ",
              "x"));

      compositor
         .add(
         function_t(
              "is_prime_impl2",
              "switch                                        "
              "{                                             "
              "  case y == 1       : true;                   "
              "  case (x % y) == 0 : false;                  "
              "  default           : is_prime_impl2(x,y - 1);"
              "}                                             ",
              "x","y"));

      compositor
         .add(
         function_t(
              "is_prime2",
              "switch                                                                "
              "{                                                                     "
              "  case x <= 0       : false;                                          "
              "  case frac(x) != 0 : false;                                          "
              "  default           : is_prime_impl2(x,min(x - 1,trunc(sqrt(x)) + 1));"
              "}                                                                     ",
              "x"));

      compositor
         .add(
         function_t(
              "is_prime_impl3",
              "while (y > 0)                           "
              "{                                       "
              "  switch                                "
              "  {                                     "
              "    case y == 1       : ~(y := 0, true);"
              "    case (x % y) == 0 : ~(y := 0,false);"
              "    default           : y := y - 1;     "
              "  }                                     "
              "}                                       ",
              "x","y"));

      compositor
         .add(
         function_t(
              "is_prime3",
              "switch                                                                "
              "{                                                                     "
              "  case x <= 0       : false;                                          "
              "  case frac(x) != 0 : false;                                          "
              "  default           : is_prime_impl3(x,min(x - 1,trunc(sqrt(x)) + 1));"
              "}                                                                     ",
              "x"));

      compositor
         .add(
         function_t(
              "is_prime_impl4",
              "switch                              "
              "{                                   "
              "  case 1 == x     : false;          "
              "  case 2 == x     : true;           "
              "  case 3 == x     : true;           "
              "  case 5 == x     : true;           "
              "  case 7 == x     : true;           "
              "  case 0 == x % 2 : false;          "
              "  default         :                 "
              "  {                                 "
              "    for (var i := 3; i < y; i += 2) "
              "    {                               "
              "      if ((x % i) == 0)             "
              "        break[false];               "
              "      else                          "
              "        true;                       "
              "    }                               "
              "  };                                "
              "}                                   ",
              "x","y"));

      compositor
         .add(
         function_t(
              "is_prime4",
              "switch                                                                "
              "{                                                                     "
              "  case x <= 0       : false;                                          "
              "  case frac(x) != 0 : false;                                          "
              "  default           : is_prime_impl4(x,min(x - 1,trunc(sqrt(x)) + 1));"
              "}                                                                     ",
              "x"));

      symbol_table_t& symbol_table = compositor.symbol_table();
      symbol_table.add_constants();
      symbol_table.add_variable("x",x);

      const std::string expression_str[] = {
                                             "is_prime1(x)",
                                             "is_prime2(x)",
                                             "is_prime3(x)",
                                             "is_prime4(x)"
                                           };

      const std::size_t expression_count = sizeof(expression_str) / sizeof(std::string);

      std::vector<expression_t> expression_list;

      for (std::size_t i = 0; i < expression_count; ++i)
      {
         parser_t parser;

         expression_t expression;
         expression.register_symbol_table(symbol_table);

         if (!parser.compile(expression_str[i],expression))
         {
            printf("run_test19() - Error: %s   Expression%d: %s\n",
                   parser.error().c_str(),
                   static_cast<unsigned int>(i),
                   expression_str[i].c_str());

            return false;
         }
         else
            expression_list.push_back(expression);
      }

      bool failure = false;

      const std::size_t prime_list[] =
                           {
                                   2,       3,       5,       7,      11,      13,      17,      19,
                                 877,     947,    1087,    1153,    1229,    1297,    1381,    1453,
                                1523,    1597,    1663,    1741,    1823,    1901,    1993,    2063,
                                2131,    2221,    2293,    2371,    2437,    2539,    2621,    2689,
                                2749,    2833,    2909,    3001,    3083,    3187,    3259,    3343,
                                3433,    3517,    3581,    3659,    3733,    3823,    3911,    4001,
                                4073,    4153,    4241,    4327,    4421,    4507,    4591,    4663,
                                4759,    4861,    4943,    5009,    5099,    5189,    5281,    5393,
                                5449,    5527,    5641,    5701,    5801,    5861,    5953,    6067,
                                6143,    6229,    6311,    6373,    6481,    6577,    6679,    6763,
                                6841,    6947,    7001,    7109,    7211,    7307,    7417,    7507,
                              104309,  104311,  104323,  104327,  104347,  104369,  104381,  104383,
                              104393,  104399,  104417,  104459,  104471,  104473,  104479,  104491,
                              104513,  104527,  104537,  104543,  104549,  104551,  104561,  104579,
                              104593,  104597,  104623,  104639,  104651,  104659,  104677,  104681,
                              104683,  104693,  104701,  104707,  104711,  104717,  104723,  104729,
                             1000621, 1000639, 1000651, 1000667, 1000669, 1001023, 1001027, 1001041
                           };

      const std::size_t prime_list_size = sizeof(prime_list) / sizeof(std::size_t);

      for (std::size_t i = 0; (i < prime_list_size) && (!failure); ++i)
      {
         x = static_cast<T>(prime_list[i]);

         std::vector<T> result(expression_count,T(0));

         for (std::size_t j = 0; j < expression_list.size(); ++j)
         {
            result[j] = expression_list[j].value();
         }

         for (std::size_t j = 1; j < expression_list.size(); ++j)
         {
            if (result[j] != result[0])
            {
               failure = true;
               break;
            }
         }

         if (failure)
         {
            printf("run_test19() - Error in evaluation! (3)  Results don't match!  Prime: %d\n",
                   static_cast<unsigned int>(prime_list[i]));

            for (std::size_t j = 0; j < expression_list.size(); ++j)
            {
               printf("Expression[%02d]: %s = %d\n",
                      static_cast<unsigned int>(j),
                      expression_str[j].c_str(),
                      static_cast<unsigned int>(result[j]));
            }
         }
         else  if (T(1) != expression_list[0].value())
         {
            printf("run_test19() - Error in evaluation! (4)  Results don't match!  Prime: %d\n",
                   static_cast<unsigned int>(prime_list[i]));

            for (std::size_t j = 0; j < expression_list.size(); ++j)
            {
               printf("Expression[%02d]: %s = %d\n",
                      static_cast<unsigned int>(j),
                      expression_str[j].c_str(),
                      static_cast<unsigned int>(result[j]));
            }
         }
      }

      if (failure)
         return false;
   }

   {
      T x = T(0);

      compositor_t compositor;

      compositor
         .add(
         function_t(
              "fibonacci1",
              "if (x == 0,0,                                 "
              "    if (x == 1,1,                             "
              "       fibonacci1(x - 1) + fibonacci1(x - 2)))",
              "x"));

      compositor
         .add(
         function_t(
              "fibonacci2",
              "switch                                                "
              "{                                                     "
              "  case x == 0 : 0;                                    "
              "  case x == 1 : 1;                                    "
              "  default     : fibonacci2(x - 1) + fibonacci2(x - 2);"
              "}                                                     ",
              "x"));

      compositor
         .add(
         function_t(
              "fibonacci_impl3",
              "switch                         "
              "{                              "
              "  case x == 0 : 0;             "
              "  case x == 1 : 1;             "
              "  default :                    "
              "    while ((x := (x - 1)) > 0) "
              "    {                          "
              "      w := z;                  "
              "      z := z + y;              "
              "      y := w;                  "
              "      z                        "
              "    };                         "
              "}                              ",
              "x","y","z","w"));

      compositor
         .add(
         function_t(
              "fibonacci3",
              "fibonacci_impl3(x,0,1,0)",
              "x"));

      compositor
         .add(
         function_t(
              "fibonacci_impl4",
              "switch              "
              "{                   "
              "  case x == 0 : 0;  "
              "  case x == 1 : 1;  "
              "  default :         "
              "    repeat          "
              "      w := z;       "
              "      z := z + y;   "
              "      y := w;       "
              "      x := x - 1;   "
              "      z             "
              "    until (x <= 1); "
              "}                   ",
              "x","y","z","w"));

      compositor
         .add(
         function_t(
              "fibonacci4",
              "fibonacci_impl4(x,0,1,0)",
              "x"));

      compositor
         .add(
         function_t(
              "fibonacci5",
              "if ((x == 0) or (x == 1))                "
              "  x;                                     "
              "else                                     "
              "  fibonacci5(x - 1) + fibonacci5(x - 2); ",
              "x"));

      symbol_table_t& symbol_table = compositor.symbol_table();

      symbol_table.add_constants();
      symbol_table.add_variable("x",x);

      const std::string expression_str[] = {
                                             "fibonacci1(x)",
                                             "fibonacci2(x)",
                                             "fibonacci3(x)",
                                             "fibonacci4(x)",
                                             "fibonacci5(x)"
                                           };

      const std::size_t expression_count = sizeof(expression_str) / sizeof(std::string);

      std::vector<expression_t> expression_list;

      for (std::size_t i = 0; i < expression_count; ++i)
      {
         parser_t parser;

         expression_t expression;
         expression.register_symbol_table(symbol_table);

         if (!parser.compile(expression_str[i],expression))
         {
            printf("run_test19() - Error: %s   Expression[%02d]: %s\n",
                   parser.error().c_str(),
                   static_cast<unsigned int>(i),
                   expression_str[i].c_str());

            return false;
         }
         else
            expression_list.push_back(expression);
      }

      bool failure = false;

      const std::size_t fibonacci_list[] =
                           {
                                  0,       1,      1,       2,
                                  3,       5,      8,      13,
                                 21,      34,     55,      89,
                                144,     233,    377,     610,
                                987,    1597,   2584,    4181,
                               6765,   10946,  17711,   28657,
                              46368,   75025, 121393,  196418,
                             317811,  514229, 832040, 1346269
                           };

      const std::size_t fibonacci_list_size = sizeof(fibonacci_list) / sizeof(std::size_t);

      for (std::size_t i = 0; (i < fibonacci_list_size) && (!failure); ++i)
      {
         x = static_cast<T>(i);

         std::vector<T> result(expression_count,T(0));

         for (std::size_t j = 0; j < expression_list.size(); ++j)
         {
            result[j] = expression_list[j].value();
         }

         for (std::size_t j = 1; j < expression_list.size(); ++j)
         {
            if (result[j] != result[0])
            {
               failure = true;
               break;
            }
         }

         if (failure)
         {
            printf("run_test19() - Error in evaluation! (5)  Results don't match!  fibonacci(%d) = %d\n",
                   static_cast<unsigned int>(i),
                   static_cast<unsigned int>(fibonacci_list[i]));

            for (std::size_t j = 0; j < expression_list.size(); ++j)
            {
               printf("Expression[%02d]: %s = %d\n",
                      static_cast<unsigned int>(j),
                      expression_str[j].c_str(),
                      static_cast<unsigned int>(result[j]));
            }
         }
         else  if (fibonacci_list[i] != expression_list[0].value())
         {
            printf("run_test19() - Error in evaluation! (6)  Results don't match!  fibonacci(%d) = %d\n",
                   static_cast<unsigned int>(i),
                   static_cast<unsigned int>(fibonacci_list[i]));

            for (std::size_t j = 0; j < expression_list.size(); ++j)
            {
               printf("Expression[%02d]: %s = %d\n",
                      static_cast<unsigned int>(j),
                      expression_str[j].c_str(),
                      static_cast<unsigned int>(result[j]));
            }
         }
      }

      if (failure)
         return false;
   }

   {
      T x = T(0);

      symbol_table_t symbol_table;

      symbol_table.add_constants();
      symbol_table.add_variable("x",x);

      compositor_t compositor(symbol_table);

      compositor
         .add(
         function_t(
              "newton_sqrt_impl",
              "switch                               "
              "{                                    "
              "  case x < 0  : -inf;                "
              "  case x == 0 : 0;                   "
              "  case x == 1 : 1;                   "
              "  default:                           "
              "  ~{                                 "
              "     z := 100;                       "
              "     y := x / 2;                     "
              "     repeat                          "
              "       y := (1 / 2) * (y + (x / y)); "
              "       if (equal(y * y,x))           "
              "         break[y];                   "
              "     until ((z -= 1) <= 0);          "
              "   };                                "
              "}                                    ",
              "x","y","z"));

      compositor
         .add(
         function_t(
              "newton_sqrt",
              "newton_sqrt_impl(x,0,0)","x"));

      std::string expression_str = "newton_sqrt(x)";

      expression_t expression;

      expression.register_symbol_table(symbol_table);

      parser_t parser;

      if (!parser.compile(expression_str,expression))
      {
         printf("run_test19() - Error: %s   Expression: %s\n",
                parser.error().c_str(),
                expression_str.c_str());

         return false;
      }

      bool failure = false;

      for (std::size_t i = 0; i < 100; ++i)
      {
         x = static_cast<T>(i);

         T result = expression.value();

         if (not_equal(result,std::sqrt(x),T(0.0000001)))
         {
            printf("run_test19() - Computation Error  "
                   "Expression: [%s]\tExpected: %12.8f\tResult: %12.8f\n",
                   expression_str.c_str(),
                   (double)std::sqrt(x),
                   (double)result);

            failure = true;
         }
      }

      if (failure)
         return false;
   }

   {
      symbol_table_t symbol_table;

      symbol_table.add_constants();

      compositor_t compositor(symbol_table);

      compositor
         .add(
         function_t(
              "mandelbrot",
              " var width    := 118;                            "
              " var height   := 41;                             "
              " var imag_max := +1;                             "
              " var imag_min := -1;                             "
              " var real_max := +1;                             "
              " var real_min := -2.5;                           "
              " var x_step   := (real_max - real_min) / width;  "
              " var y_step   := (imag_max - imag_min) / height; "
              " for (var y := 0; y < height; y += 1)            "
              " {                                               "
              "   var imag := imag_min + (y_step * y);          "
              "   for (var x := 0; x < width; x += 1)           "
              "   {                                             "
              "     var real   := real_min + x_step * x;        "
              "     var z_real := real;                         "
              "     var z_imag := imag;                         "
              "     var plot_value;                             "
              "     for (var n := 0; n < 30; n += 1)            "
              "     {                                           "
              "       var a := z_real^2;                        "
              "       var b := z_imag^2;                        "
              "       plot_value := n;                          "
              "       if ((a + b) < 4)                          "
              "       {                                         "
              "         z_imag := 2 * z_real * z_imag + imag;   "
              "         z_real := a - b + real;                 "
              "       }                                         "
              "       else                                      "
              "         break;                                  "
              "     };                                          "
              "   };                                            "
              " }                                               "));

      std::string expression_str = "mandelbrot()";

      expression_t expression;

      expression.register_symbol_table(symbol_table);

      parser_t parser;

      if (!parser.compile(expression_str,expression))
      {
         printf("run_test19() - Error: %s   Expression: %s\n",
                parser.error().c_str(),
                expression_str.c_str());

         return false;
      }

      for (std::size_t i = 0; i < 100; ++i)
      {
         expression.value();
      }
   }

   {
      T x = T(0);

      symbol_table_t symbol_table;

      symbol_table.add_variable("x",x);

      compositor_t compositor(symbol_table);

      compositor
         .add(
         function_t(
              "fooboo",
              " var x := input;       "
              " if (x > 0)            "
              "   fooboo(x - 1) + x;  "
              " else                  "
              "   0;                  ",
              "input"));

      std::string expression_str = "fOoBoO(x)";

      expression_t expression;

      expression.register_symbol_table(symbol_table);

      parser_t parser;

      if (!parser.compile(expression_str,expression))
      {
         printf("run_test19() - Error: %s   Expression: %s\n",
                parser.error().c_str(),
                expression_str.c_str());

         return false;
      }

      T sum = T(0);

      for (std::size_t i = 0; i < 100; ++i)
      {
         x = T(i);

         sum += x;

         T result = expression.value();

         if (result != sum)
         {
            printf("run_test19() - FooBoo(%5.2f)  Expected: %5.2f\tResult: %5.2f\n",
                   x,
                   sum,
                   result);

            return false;
         }
      }

   }

   {
      symbol_table_t symbol_table;

      symbol_table.add_constants();

      std::string expression_str =
                     " var sieve[10^7] := [false];                     "
                     " var m := trunc(sqrt(sieve[]));                  "
                     "                                                 "
                     " sieve[0] := true;                               "
                     " sieve[1] := true;                               "
                     "                                                 "
                     " for (var i := 0; i <= m; i += 1)                "
                     " {                                               "
                     "   if (false == sieve[i])                        "
                     "   {                                             "
                     "     for (var j := (i * i); j < sieve[]; j += i) "
                     "     {                                           "
                     "       sieve[j] := true;                         "
                     "     }                                           "
                     "   }                                             "
                     " };                                              "
                     "                                                 "
                     " var prime_count := 0;                           "
                     " for (var i := 0; i < sieve[]; i += 1)           "
                     " {                                               "
                     "   if (false == sieve[i])                        "
                     "   {                                             "
                     "     prime_count += 1;                           "
                     "   };                                            "
                     " };                                              "
                     "                                                 "
                     " prime_count == 664579;                          ";

      expression_t expression;

      expression.register_symbol_table(symbol_table);

      parser_t parser;

      if (!parser.compile(expression_str,expression))
      {
         printf("run_test19() - Error: %s   Expression: %s\n",
                parser.error().c_str(),
                expression_str.c_str());

         return false;
      }

      if (T(1) != expression.value())
      {
         printf("run_test19() - Prime Sieve Computation Error");

         return false;
      }
   }

   {
      symbol_table_t symbol_table;

      symbol_table.add_constants();

      std::string expression_str[] =
                    {
                      "var delta := 10^-7; var total := 0; for (var i := 0; i <= 3; i += delta) { total +=   "
                      "erf(i) }; abs((delta * total) - (3 * erf(3) + (1 / exp(9) - 1) / sqrt(pi))) < 0.000001",

                      "var delta := 10^-7; var total := 0; for (var i := 0; i <= 3; i += delta) { total +=  "
                      "erfc(i) }; abs((delta * total) - (3 * erfc(3) + ((1 - 1 / exp(9)) / sqrt(pi)))) < 0.000001"
                    };

      expression_t e[2];

      parser_t parser;

      for (std::size_t i = 0; i < 2; ++i)
      {
         e[i].register_symbol_table(symbol_table);

         if (!parser.compile(expression_str[i],e[i]))
         {
            printf("run_test19() - Error: %s   Expression: %s\n",
                   parser.error().c_str(),
                   expression_str[i].c_str());

            return false;
         }

         if (T(1) != e[i].value())
         {
            printf("run_test19() - erf/erfc computation error %d",
                   static_cast<unsigned int>(i));

            return false;
         }
      }
   }

   return true;
}

template <typename T>
struct my_usr : public exprtk::parser<T>::unknown_symbol_resolver
{
   typedef typename exprtk::parser<T>::unknown_symbol_resolver usr_t;

   bool process(const std::string& unknown_symbol,
                typename usr_t::usr_symbol_type& st,
                T& default_value,
                std::string& error_message) override
   {
      if (unknown_symbol[0] == 'v')
      {
         st = usr_t::e_usr_variable_type;
         default_value = next_value();
         error_message.clear();

         return true;
      }
      else if (unknown_symbol[0] == 'c')
      {
         st = usr_t::e_usr_constant_type;
         default_value = next_value();
         error_message.clear();

         return true;
      }
      else
      {
         error_message = "Unknown symbol...";
         return false;
      }
   }

   T next_value(const bool reset = false)
   {
      static T value = 0;

      if (reset)
         return (value = 0);
      else
         return ++value;
   }
};

template <typename T>
struct my_usr_ext : public exprtk::parser<T>::unknown_symbol_resolver
{
   typedef exprtk::symbol_table<T> symbol_table_t;
   typedef typename exprtk::parser<T>::unknown_symbol_resolver usr_t;

   my_usr_ext()
   : usr_t(usr_t::e_usrmode_extended)
   {}

   bool process(const std::string& unknown_symbol,
                        symbol_table_t&      symbol_table,
                        std::string&        error_message) override
   {
      bool result = false;

      if (unknown_symbol[0] == 'v')
      {
         static T var_default_value = 1.0;

         if ((result = symbol_table.create_variable(unknown_symbol, var_default_value++)) == false)
         {
            error_message = "Failed to create variable(" + unknown_symbol + ") in primary symbol table";
         }
      }
      else if (unknown_symbol[0] == 'c')
      {
         static T cvar_default_value = 1.0;

         if ((result = symbol_table.add_constant(unknown_symbol, cvar_default_value++)) == false)
         {
            error_message = "Failed to create const variable(" + unknown_symbol + ") in primary symbol table";
         }
      }
      else if (0 == unknown_symbol.find("foo"))
      {
         //functions of form: fooXX
         if (4 >= unknown_symbol.size())
         {
            switch(unknown_symbol[3])
            {
               case '1' : result = symbol_table.add_function(unknown_symbol,foo1);
                          break;

               case '2' : result = symbol_table.add_function(unknown_symbol,foo2);
                          break;

               case '3' : result = symbol_table.add_function(unknown_symbol,foo3);
                          break;

               case '4' : result = symbol_table.add_function(unknown_symbol,foo4);
                          break;

               case '5' : result = symbol_table.add_function(unknown_symbol,foo5);
                          break;

               case '6' : result = symbol_table.add_function(unknown_symbol,foo6);
                          break;
            }
         }

         if (!result)
         {
            error_message = "Failed to add function(" + unknown_symbol + ") in primary symbol table";
         }
      }
      else
         error_message = "Indeterminable symbol type.";

      return result;
   }
};

template <typename T>
inline bool run_test20()
{
   typedef exprtk::expression<T> expression_t;

   {
      for (std::size_t i = 0; i < 100; ++i)
      {
         exprtk::symbol_table<T> symbol_table0; // primary symbol_table
         exprtk::symbol_table<T> symbol_table1;
         exprtk::symbol_table<T> symbol_table2;
         exprtk::symbol_table<T> symbol_table3;

         symbol_table0.add_constants();

         expression_t expression;
         expression.register_symbol_table(symbol_table0);
         expression.register_symbol_table(symbol_table1);
         expression.register_symbol_table(symbol_table2);
         expression.register_symbol_table(symbol_table3);

         exprtk::parser<T> parser;

         my_usr<T> musr;
         musr.next_value(true);
         parser.enable_unknown_symbol_resolver(&musr);

         std::string expr_str = "v01+c02+v03+c04+v05+c06+v07+c08+v09+c10+"
                                "v11+c12+v13+c14+v15+c16+v17+c18+v19+c20+"
                                "v21+c22+v23+c24+v25+c26+v27+c28+v29+c30 ";

         if (!parser.compile(expr_str,expression))
         {
            printf("run_test20() - [1] Error: %s   Expression: %s\n",
                   parser.error().c_str(),
                   expr_str.c_str());

            return false;
         }

         T sum_1_30 = T((1 + 30) * 15);
         T result   = expression.value();

         if (sum_1_30 != result)
         {
            printf("run_test20() - [1] Error in evaluation! (1) Expression: %s\n",
                   expr_str.c_str());

            return false;
         }
      }
   }

   {
      for (std::size_t i = 0; i < 100; ++i)
      {
         exprtk::symbol_table<T> symbol_table0; // primary symbol_table
         exprtk::symbol_table<T> symbol_table1;
         exprtk::symbol_table<T> symbol_table2;
         exprtk::symbol_table<T> symbol_table3;

         symbol_table0.add_constants();

         expression_t expression;
         expression.register_symbol_table(symbol_table0);
         expression.register_symbol_table(symbol_table1);
         expression.register_symbol_table(symbol_table2);
         expression.register_symbol_table(symbol_table3);

         exprtk::parser<T> parser;

         my_usr_ext<T> musr;
         parser.enable_unknown_symbol_resolver(&musr);

         std::string expr_str = "foo6(foo1(v0),foo2(c1,foo4(v2,c3,v4,c5)),foo3"
                                "(v6,c7,foo5(v8,c9,v10,c11,v12)),c13,v14,c15) ";

         if (!parser.compile(expr_str,expression))
         {
            printf("run_test20() - [2] Error: %s   Expression: %s\n",
                   parser.error().c_str(),
                   expr_str.c_str());

            return false;
         }
      }
   }

   {
      T              var;
      std::string    str;
      std::vector<T> vec(10,0.0);

      typedef exprtk::symbol_table<T> symbol_table_t;

      bool result = true;

      {
         symbol_table_t symbol_table;

         symbol_table.add_variable ("val",var);
         symbol_table.add_stringvar("str",str);
         symbol_table.add_vector   ("vec",vec);

         if (symbol_table.get_variable("val") == 0 || !symbol_table.symbol_exists("val"))
         {
            printf("run_test20() - [3] Failed to get 'val' from symbol_table\n");
            result = false;
         }

         if (symbol_table.get_stringvar("str") == 0 || !symbol_table.symbol_exists("str"))
         {
            printf("run_test20() - [3] Failed to get 'str' from symbol_table\n");
            result = false;
         }

         if (symbol_table.get_vector("vec") == 0 || !symbol_table.symbol_exists("vec"))
         {
            printf("run_test20() - [3] Failed to get 'vec' from symbol_table\n");
            result = false;
         }
      }

      if (!result)
         return result;

      {
         symbol_table_t symbol_table;

         symbol_table.add_variable("val",var);

         if (symbol_table.get_variable("val") == 0 || !symbol_table.symbol_exists("val"))
         {
            printf("run_test20() - [4] Failed to get 'val' from symbol_table\n");
            result = false;
         }

         if (symbol_table.get_stringvar("str") != 0 || symbol_table.symbol_exists("str"))
         {
            printf("run_test20() - [4] Failed to get 'str' from symbol_table\n");
            result = false;
         }

         if (symbol_table.get_vector("vec") != 0 || symbol_table.symbol_exists("vec"))
         {
            printf("run_test20() - [4] Failed to get 'vec' from symbol_table\n");
            result = false;
         }
      }

      if (!result)
         return result;

      {
         symbol_table_t symbol_table;

         symbol_table.add_stringvar("str",str);

         if (symbol_table.get_stringvar("str") == 0 || !symbol_table.symbol_exists("str"))
         {
            printf("run_test20() - [5] Failed to get 'str' from symbol_table\n");
            result = false;
         }

         if (symbol_table.get_variable("val") != 0 || symbol_table.symbol_exists("val"))
         {
            printf("run_test20() - [5] Failed to get 'val' from symbol_table\n");
            result = false;
         }

         if (symbol_table.get_vector("vec") != 0 || symbol_table.symbol_exists("vec"))
         {
            printf("run_test20() - [5] Failed to get 'vec' from symbol_table\n");
            result = false;
         }
      }

      if (!result)
         return result;

      {
         symbol_table_t symbol_table;

         symbol_table.add_vector("vec",vec);

         if (symbol_table.get_vector("vec") == 0 || !symbol_table.symbol_exists("vec"))
         {
            printf("run_test20() - [6] Failed to get 'vec' from symbol_table\n");
            result = false;
         }

         if (symbol_table.get_variable("val") != 0 || symbol_table.symbol_exists("val"))
         {
            printf("run_test20() - [6] Failed to get 'val' from symbol_table\n");
            result = false;
         }

         if (symbol_table.get_stringvar("str") != 0 || symbol_table.symbol_exists("str"))
         {
            printf("run_test20() - [6] Failed to get 'str' from symbol_table\n");
            result = false;
         }
      }

      if (!result)
         return result;
   }

   return true;
}

template <typename T>
inline std::string results_to_string(const exprtk::results_context<T>& results)
{
   typedef exprtk::results_context<T> results_context_t;
   typedef typename results_context_t::type_store_t type_t;

   std::string res_str;

   for (std::size_t i = 0; i < results.count(); ++i)
   {
      type_t t = results[i];

      switch (t.type)
      {
         case type_t::e_scalar : res_str += 'T';
                                 break;

         case type_t::e_vector : res_str += 'V';
                                 break;

         case type_t::e_string : res_str += 'S';
                                 break;

         default               : continue;
      }
   }

   return res_str;
}

template <typename T>
inline bool result_equal(const exprtk::results_context<T>& results, const T& value)
{
   typedef exprtk::results_context<T> results_context_t;
   typedef typename results_context_t::type_store_t type_t;
   typedef typename type_t::scalar_view scalar_t;

   if (1 != results.count())
      return false;
   else if (type_t::e_scalar != results[0].type)
      return false;
   else
      return (value == scalar_t(results[0])());
}

template <typename T>
inline bool run_test21()
{
   typedef exprtk::symbol_table<T> symbol_table_t;
   typedef exprtk::expression<T>     expression_t;
   typedef exprtk::parser<T>             parser_t;

   T x = T(1.1);
   T y = T(2.2);
   T z = T(3.3);

   symbol_table_t symbol_table;
   symbol_table.add_constants();
   symbol_table.add_variable("x",x);
   symbol_table.add_variable("y",y);
   symbol_table.add_variable("z",z);

   {
      static const std::string expression_list[] =
         {
           "return[]; x;",
           "return[x]; x;",
           "return[x,y]; x;",
           "return[x + y,y - x]; x;",
           "return[x + y,y - x,'abc']; x;",
           "if (x < y) return [1,'abc1']; else return [2,'abc2',x];"      ,
           "if (x > y) return [1,'abc1']; else return [2,'abc2',x];"      ,
           "if (x < y) { return [1,'abc1'];} else { return [2,'abc2',x];}",
           "if (x > y) { return [1,'abc1'];} else { return [2,'abc2',x];}",
           "for(var i := 0; i < 10; i += 1) { if (i == 5) return [1]; }        ",
           "for(var i := 0; i < 10; i += 1) { if (i == 5) return [1,'abc']; }  ",
           "for(var i := 0; i < 10; i += 1) { if (i == 5) return [1,'abc',x]; }",
           "for(var i := 0; i < 10; i += 1) { if (i == 5) return [1,'abc',x,y]; }",
           "for(var i := 0; i < 10; i += 1) { if (i == 5) return [1,'abc',x,y,z]; }",
           "for(var i := 0; i < 10; i += 1) { if (i == 5) return [2,'abc2',x]; else x += 1; }",
           "for(var i := 0; i < 10; i += 1) { if (i == 5) { return [1,'abc1'];} else x += 1; }"
         };

      static const std::string result_list[] =
         {
           ""     ,
           "T"    ,
           "TT"   ,
           "TT"   ,
           "TTS"  ,
           "TS"   ,
           "TST"  ,
           "TS"   ,
           "TST"  ,
           "T"    ,
           "TS"   ,
           "TST"  ,
           "TSTT" ,
           "TSTTT",
           "TST"  ,
           "TS"
         };

      static const std::size_t expression_list_size = sizeof(expression_list) / sizeof(std::string);

      bool failure = false;

      for (std::size_t i = 0; i < expression_list_size; ++i)
      {
         expression_t expression;
         expression.register_symbol_table(symbol_table);

         parser_t parser;

         if (!parser.compile(expression_list[i],expression))
         {
            printf("run_test21() - Error: %s   Expression: %s  [1]\n",
                   parser.error().c_str(),
                   expression_list[i].c_str());

            failure = true;
            continue;
         }
         else if (!parser.dec().return_present())
         {
            printf("run_test21() - Expected a return statement   Expression: %s  [1]\n",
                   expression_list[i].c_str());

            failure = true;
            continue;
         }

         expression.value();

         std::string pattern = results_to_string<T>(expression.results());

         if (!expression.return_invoked())
         {
            printf("run_test21() - Invalid return invoke state [1] Expression: %s\n",
                   expression_list[i].c_str());

            failure = true;
            continue;
         }
         else if (result_list[i] != pattern)
         {
            printf("run_test21() - Invalid return results [1] Expected %s  Got: %s  Expression: %s\n",
                   result_list[i].c_str(),
                   pattern.c_str(),
                   expression_list[i].c_str());

            failure = true;
            continue;
         }
      }

      if (failure)
         return false;
   }

   {
      static const std::string expression_list[] =
         {
           "x := 1; x + 1; x + 2; x + 3; x + 5; x + 7;  return [x + 1];  ",
           "x := 1; x + 1; x + 2; x + 3; x + 5; return [x + 1]; x := 7;  ",
           "x := 1; x + 1; x + 2; x + 3; return [x + 1]; x + 5; x := 7;  ",
           "x := 1; x + 1; x + 2; return [x + 1]; x + 3; x + 5; x := 7;  ",
           "x := 1; x + 1; return [x + 1]; x + 2; x + 3; x + 5; x := 7;  ",
           "x := 1; return [x + 1]; x + 1; x + 2; x + 3; x + 5; x := 7;  ",
           "return [x + 1]; x := 1; x + 1; x + 2; x + 3; x + 5; x := 7;  ",
           "~{x := 1; x + 1; x + 2; x + 3; x + 5; x + 7;  return [x + 1]}",
           "~{x := 1; x + 1; x + 2; x + 3; x + 5; return [x + 1]; x := 7}",
           "~{x := 1; x + 1; x + 2; x + 3; return [x + 1]; x + 5; x := 7}",
           "~{x := 1; x + 1; x + 2; return [x + 1]; x + 3; x + 5; x := 7}",
           "~{x := 1; x + 1; return [x + 1]; x + 2; x + 3; x + 5; x := 7}",
           "~{x := 1; return [x + 1]; x + 1; x + 2; x + 3; x + 5; x := 7}",
           "~{return [x + 1]; x := 1; x + 1; x + 2; x + 3; x + 5; x := 7}"
         };

      static const std::string result_list[] =
         {
           "T", "T", "T", "T", "T", "T", "T",
           "T", "T", "T", "T", "T", "T", "T",
         };

      static const std::size_t expression_list_size = sizeof(expression_list) / sizeof(std::string);

      bool failure = false;

      for (std::size_t i = 0; i < expression_list_size; ++i)
      {
         expression_t expression;
         expression.register_symbol_table(symbol_table);

         parser_t parser;

         if (!parser.compile(expression_list[i],expression))
         {
            printf("run_test21() - Error: %s   Expression: %s  [2]\n",
                   parser.error().c_str(),
                   expression_list[i].c_str());

            failure = true;
            continue;
         }
         else if (!parser.dec().return_present())
         {
            printf("run_test21() - Expected a return statement   Expression: %s  [2]\n",
                   expression_list[i].c_str());

            failure = true;
            continue;
         }

         expression.value();

         std::string pattern = results_to_string<T>(expression.results());

         if (!expression.return_invoked())
         {
            printf("run_test21() - Invalid return invoke state [2] Expression: %s\n",
                   expression_list[i].c_str());

            failure = true;
            continue;
         }
         else if (result_list[i] != pattern)
         {
            printf("run_test21() - Invalid return results [2] Expected %s  Got: %s  Expression: %s\n",
                   result_list[i].c_str(),
                   pattern.c_str(),
                   expression_list[i].c_str());

            failure = true;
            continue;
         }
         else if (!result_equal(expression.results(), x + T(1)))
         {
            printf("run_test21() - Invalid return results [2] Expected %s  Got: %s  Expression: %s\n",
                   result_list[i].c_str(),
                   pattern.c_str(),
                   expression_list[i].c_str());

            failure = true;
            continue;
         }
      }

      if (failure)
         return false;
   }

   return true;
}

template <typename T>
struct type_name { static inline std::string value() { return "unknown"; } };
template <> struct type_name<float>       { static inline std::string value() { return "float";       } };
template <> struct type_name<double>      { static inline std::string value() { return "double";      } };
template <> struct type_name<long double> { static inline std::string value() { return "long double"; } };

#define perform_test(Type,Number)                                                                                                                \
{                                                                                                                                                \
  bool check = true;                                                                                                                             \
  exprtk::timer timer;                                                                                                                           \
  timer.start();                                                                                                                                 \
  if (!run_test##Number<Type>()) {                                                                                                               \
      std::cout << "run_test#Number" << type_name<Type>::value().c_str() << "*** FAILED! ***" << std::endl;                                      \
      check = false;                                                                                                                             \
  } else  {                                                                                                                                      \
      timer.stop();                                                                                                                              \
      std::cout << "run_test#Number" << type_name<Type>::value().c_str() << "- Result: SUCCESS   Time: " << timer.time() << " sec" << std::endl; \
  }                                                                                                                                              \
  KRATOS_CHECK(check)                                                                                                                            \
}                                                                                                                                                \

/**
 * Checks that exprtk 00
 */
KRATOS_TEST_CASE_IN_SUITE(exprtkLLibrary00, KratosExternalLibrariesFastSuite)
{
    perform_test(numeric_type,00);
}

/**
 * Checks that exprtk 01
 */
KRATOS_TEST_CASE_IN_SUITE(exprtkLLibrary01, KratosExternalLibrariesFastSuite)
{
    perform_test(numeric_type,01);
}

/**
 * Checks that exprtk 02
 */
KRATOS_TEST_CASE_IN_SUITE(exprtkLLibrary02, KratosExternalLibrariesFastSuite)
{
    perform_test(numeric_type,02);
}

/**
 * Checks that exprtk 03
 */
KRATOS_TEST_CASE_IN_SUITE(exprtkLLibrary03, KratosExternalLibrariesFastSuite)
{
    perform_test(numeric_type,03);
}

/**
 * Checks that exprtk 04
 */
KRATOS_TEST_CASE_IN_SUITE(exprtkLLibrary04, KratosExternalLibrariesFastSuite)
{
    perform_test(numeric_type,04);
}

/**
 * Checks that exprtk 05
 */
KRATOS_TEST_CASE_IN_SUITE(exprtkLLibrary05, KratosExternalLibrariesFastSuite)
{
    perform_test(numeric_type,05);
}

/**
 * Checks that exprtk 06
 */
KRATOS_TEST_CASE_IN_SUITE(exprtkLLibrary06, KratosExternalLibrariesFastSuite)
{
    perform_test(numeric_type,06);
}

/**
 * Checks that exprtk 07
 */
KRATOS_TEST_CASE_IN_SUITE(exprtkLLibrary07, KratosExternalLibrariesFastSuite)
{
    perform_test(numeric_type,07);
}

/**
 * Checks that exprtk 08
 */
KRATOS_TEST_CASE_IN_SUITE(exprtkLLibrary08, KratosExternalLibrariesFastSuite)
{
    perform_test(numeric_type,08);
}

/**
 * Checks that exprtk 09
 */
KRATOS_TEST_CASE_IN_SUITE(exprtkLLibrary09, KratosExternalLibrariesFastSuite)
{
    perform_test(numeric_type,09);
}

/**
 * Checks that exprtk 10
 */
KRATOS_TEST_CASE_IN_SUITE(exprtkLLibrary10, KratosExternalLibrariesFastSuite)
{
    perform_test(numeric_type,10);
}

/**
 * Checks that exprtk 11
 */
KRATOS_TEST_CASE_IN_SUITE(exprtkLLibrary11, KratosExternalLibrariesFastSuite)
{
    perform_test(numeric_type,11);
}

/**
 * Checks that exprtk 12
 */
KRATOS_TEST_CASE_IN_SUITE(exprtkLLibrary12, KratosExternalLibrariesFastSuite)
{
    perform_test(numeric_type,12);
}

/**
 * Checks that exprtk 13
 */
KRATOS_TEST_CASE_IN_SUITE(exprtkLLibrary13, KratosExternalLibrariesFastSuite)
{
    perform_test(numeric_type,13);
}

/**
 * Checks that exprtk 14
 */
KRATOS_TEST_CASE_IN_SUITE(exprtkLLibrary14, KratosExternalLibrariesFastSuite)
{
    perform_test(numeric_type,14);
}

/**
 * Checks that exprtk 15
 */
KRATOS_TEST_CASE_IN_SUITE(exprtkLLibrary15, KratosExternalLibrariesFastSuite)
{
    perform_test(numeric_type,15);
}

/**
 * Checks that exprtk 16
 */
KRATOS_TEST_CASE_IN_SUITE(exprtkLLibrary16, KratosExternalLibrariesFastSuite)
{
    perform_test(numeric_type,16);
}

/**
 * Checks that exprtk 17
 */
KRATOS_TEST_CASE_IN_SUITE(exprtkLLibrary17, KratosExternalLibrariesFastSuite)
{
    perform_test(numeric_type,17);
}

/**
 * Checks that exprtk 18
 */
KRATOS_TEST_CASE_IN_SUITE(exprtkLLibrary18, KratosExternalLibrariesFastSuite)
{
    perform_test(numeric_type,18);
}

/**
 * Checks that exprtk 19
 */
KRATOS_TEST_CASE_IN_SUITE(exprtkLLibrary19, KratosExternalLibrariesFastSuite)
{
    perform_test(numeric_type,19);
}

/**
 * Checks that exprtk 20
 */
KRATOS_TEST_CASE_IN_SUITE(exprtkLLibrary20, KratosExternalLibrariesFastSuite)
{
    perform_test(numeric_type,20);
}

/**
 * Checks that exprtk 21
 */
KRATOS_TEST_CASE_IN_SUITE(exprtkLLibrary21, KratosExternalLibrariesFastSuite)
{
    perform_test(numeric_type,21);
}

#undef perform_test

} // namespace Testing.
} // namespace Kratos.
