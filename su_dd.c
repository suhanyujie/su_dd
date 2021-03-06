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

#include "zend.h"

/* If you declare any globals in php_su_dd.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(su_dd)
*/
#define TEMP_CONVERTER_TO_FAHRENHEIT 2
#define TEMP_CONVERTER_TO_CELSIUS 1

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

ZEND_BEGIN_ARG_INFO_EX(arginfo_su_test_reverse, 0, 0, 1)
ZEND_ARG_INFO(0, param1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_temperature_converter, 0, 0, 1)
ZEND_ARG_INFO(0, t)
ZEND_ARG_INFO(0, mode)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_su_getType, 0, 0, 1)
ZEND_ARG_INFO(0, param1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_dd_count_object, 0, 0, 1)
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
	php_printf("The extension %s is loaded and working!\r\n", strg->val);

	RETURN_STR(strg);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/
double php_su_test(double f)
{
	return f + 1.01;
}

static double php_su_test_reverse(double c)
{
	return c * ((double)9 / 5) + 32;
}

// 统计对象的计数
static void php_dd_count_object()
{
}

PHP_FUNCTION(dd_count_object)
{
	zval *obj1;
	HashTable *properties;
	zend_string *key;
	zend_object *zobj;
	zend_ulong num_key;
	zval *value;
	// 声明一个字符指针
	// char s1[6] = {'h','e','l','l','o','\0'};
	char s1[] = "hello";
	// 声明一个字符串指针
	zend_string *str1;
	// 参数解析
	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_STR(str1);
	ZEND_PARSE_PARAMETERS_END();
	// strcat(str1->val, s1);
	// 将字符数组初始化为一个 zend_string
	// str1 = zend_string_init(s1, 5, 0);
	// 返回zend_string
	// RETURN_STR(str1);
	RETURN_STRINGL(str1, str1->len);
	return;
}

PHP_FUNCTION(temperature_converter)
{
	double t;
	zend_long mode = TEMP_CONVERTER_TO_CELSIUS;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d|l", &t, &mode) == FAILURE)
	{
		return;
	}
}

static void func_array_init()
{
	php_printf("debug-func_array_init\n");
}

//c实现函数 su_test
PHP_FUNCTION(su_test)
{
	zend_string *str, *delim;
	zend_long limit = ZEND_LONG_MAX; /* No limit */
	zval tmp;

	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_STR(delim)
		Z_PARAM_STR(str)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(limit)
	ZEND_PARSE_PARAMETERS_END();

	if (ZSTR_LEN(delim) == 0) {
		php_error_docref(NULL, E_WARNING, "Empty delimiter");
		RETURN_FALSE;
	}

	func_array_init();
	array_init(return_value);

	if (ZSTR_LEN(str) == 0) {
	  	if (limit >= 0) {
			ZVAL_EMPTY_STRING(&tmp);
			zend_hash_index_add_new(Z_ARRVAL_P(return_value), 0, &tmp);
		}
		return;
	}

	if (limit > 1) {
		php_explode(delim, str, return_value, limit);
	} else if (limit < 0) {
		php_explode_negative_limit(delim, str, return_value, limit);
	} else {
		ZVAL_STR_COPY(&tmp, str);
		zend_hash_index_add_new(Z_ARRVAL_P(return_value), 0, &tmp);
	}
}

PHP_FUNCTION(su_test_reverse)
{
	double c;
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "d", &c) == FAILURE)
	{
		return;
	}
	RETURN_DOUBLE(php_su_test_reverse(c));
}

PHP_FUNCTION(su_getType)
{
	zval *param1;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &param1) == FAILURE)
	{
		return;
	}
	//php_printf("type is :%d\n", Z_TYPE_P(param1));
	switch (Z_TYPE_P(param1))
	{
	case IS_NULL:
		php_printf("null\n");
		break;
	case IS_TRUE: //布尔值的判断需要分为IS_TRUE 和IS_FALSE
		php_printf("bool:%s\n", Z_LVAL_P(param1) ? "true" : "false");
		break;
	case IS_FALSE:
		php_printf("bool:%s\n", Z_LVAL_P(param1) ? "true" : "false");
		break;
	case IS_LONG:
		php_printf("long is:%d\n", Z_LVAL_P(param1));
		break;
	case IS_DOUBLE:
		php_printf("double is :%.2f...\n", Z_LVAL_P(param1));
		break;
	case IS_STRING:
		php_printf("string is :");
		php_write(Z_STRVAL_P(param1), Z_STRLEN_P(param1));
		php_printf("\n");
		break;
	case IS_RESOURCE:
		php_printf("resource...\n");
		break;
	case IS_ARRAY:
		php_printf("array...\n");
		break;
	case IS_OBJECT:
		php_printf("object...\n");
		break;
	default:
		php_printf("unknow...\n");
		break;
	}
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

	REGISTER_LONG_CONSTANT("TEMP_CONVERTER_TO_CELSIUS", TEMP_CONVERTER_TO_CELSIUS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("TEMP_CONVERTER_TO_FAHRENHEIT", TEMP_CONVERTER_TO_FAHRENHEIT, CONST_CS | CONST_PERSISTENT);

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

/* {{{ su_dd_functions[]
 *
 * Every user visible function must have an entry in su_dd_functions[].
 */
const zend_function_entry su_dd_functions[] = {
		PHP_FE(confirm_su_dd_compiled, NULL)												 /* For testing, remove later. */
		PHP_FE(su_test, arginfo_su_test)														 /* */
		PHP_FE(su_test_reverse, arginfo_su_test_reverse)						 /* */
		PHP_FE(temperature_converter, arginfo_temperature_converter) /* */
		PHP_FE(su_getType, arginfo_su_getType)											 /* */
		PHP_FE(dd_count_object, arginfo_dd_count_object)
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
		PHP_RINIT(su_dd),			/* Replace with NULL if there's nothing to do at request start */
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
