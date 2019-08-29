/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2018 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_SU_DD_H
#define PHP_SU_DD_H

extern zend_module_entry su_dd_module_entry;
#define phpext_su_dd_ptr &su_dd_module_entry

#define PHP_SU_DD_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_SU_DD_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_SU_DD_API __attribute__ ((visibility("default")))
#else
#	define PHP_SU_DD_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

/*
// 被依赖的扩展的头文件中定义的类型可以被扩展 a 所调用
// 类型定义
*/
typedef struct Student {
  int age;
  char* name;
} Stu;

double php_su_test(double f);

PHP_FUNCTION(su_test);

/*
  	Declare any global variables you may need between the BEGIN
	and END macros here:

ZEND_BEGIN_MODULE_GLOBALS(su_dd)
	zend_long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(su_dd)
*/

/* Always refer to the globals in your function as SU_DD_G(variable).
   You are encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/
#define SU_DD_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(su_dd, v)

#if defined(ZTS) && defined(COMPILE_DL_SU_DD)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

PHP_FUNCTION(confirm_su_dd_compiled);

#endif	/* PHP_SU_DD_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
