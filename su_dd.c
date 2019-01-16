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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_su_dd.h"

/* If you declare any globals in php_su_dd.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(su_dd)
*/

/* True global resources - no need for thread safety here */
static int le_su_dd;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("su_dd.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_su_dd_globals, su_dd_globals)
    STD_PHP_INI_ENTRY("su_dd.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_su_dd_globals, su_dd_globals)
PHP_INI_END()
*/
/* }}} */
//传入参数的注册/声明
ZEND_BEGIN_ARG_INFO_EX(arginfo_su_test, 0, 0, 1)
ZEND_ARG_INFO(0, param1)
ZEND_END_ARG_INFO()

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_su_dd_compiled(string arg)
   Return a string to confirm that the module is compiled in */
//c实现函数 confirm_su_dd_compiled
PHP_FUNCTION(confirm_su_dd_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE)
	{
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "su_dd", arg);

	RETURN_STR(strg);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/
static double php_su_test(double f)
{
	return ((double)5/9)*(double)(f-32);
}

//c实现函数 su_test
PHP_FUNCTION(su_test)
{
	double f;
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "d", &f) == FAILURE)
	{
		return;
	}
	RETURN_DOUBLE(php_su_test(f));
}

/* {{{ php_su_dd_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_su_dd_init_globals(zend_su_dd_globals *su_dd_globals)
{
	su_dd_globals->global_value = 0;
	su_dd_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(su_dd)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(su_dd)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(su_dd)
{
#if defined(COMPILE_DL_SU_DD) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(su_dd)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(su_dd)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "su_dd support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

void zif_su_test(zend_execute_data *execute_data, zval *return_value)
{
}

/* {{{ su_dd_functions[]
 *
 * Every user visible function must have an entry in su_dd_functions[].
 */
const zend_function_entry su_dd_functions[] = {
	PHP_FE(su_test, arginfo_su_test)
	//PHP_FE(confirm_su_dd_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE_END /* Must be the last line in su_dd_functions[] */
};
/* }}} */

/* {{{ su_dd_module_entry
 */
zend_module_entry su_dd_module_entry = {
	STANDARD_MODULE_HEADER,
	"su_dd",
	su_dd_functions,
	PHP_MINIT(su_dd),
	PHP_MSHUTDOWN(su_dd),
	PHP_RINIT(su_dd),	 /* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(su_dd), /* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(su_dd),
	PHP_SU_DD_VERSION,
	STANDARD_MODULE_PROPERTIES};
/* }}} */

#ifdef COMPILE_DL_SU_DD
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(su_dd)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
