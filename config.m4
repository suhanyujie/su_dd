dnl 新加内容，用于将该插件的头文件放入 php/include/ext/ 对应的目录中
PHP_INSTALL_HEADERS(ext/su_dd, [php_su_dd.h])

dnl $Id$
dnl config.m4 for extension su_dd

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(su_dd, for su_dd support,
dnl Make sure that the comment is aligned:
dnl [  --with-su_dd             Include su_dd support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(su_dd, whether to enable su_dd support,
dnl Make sure that the comment is aligned:
dnl [  --enable-su_dd           Enable su_dd support])

PHP_ARG_ENABLE(su_dd, whether to enable su_dd support,
[  --enable-su_dd           Enable su_dd support])


if test "$PHP_SU_DD" != "no"; then
  dnl Write more examples of tests here...

  dnl # get library FOO build options from pkg-config output
  dnl AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
  dnl AC_MSG_CHECKING(for libfoo)
  dnl if test -x "$PKG_CONFIG" && $PKG_CONFIG --exists foo; then
  dnl   if $PKG_CONFIG foo --atleast-version 1.2.3; then
  dnl     LIBFOO_CFLAGS=`$PKG_CONFIG foo --cflags`
  dnl     LIBFOO_LIBDIR=`$PKG_CONFIG foo --libs`
  dnl     LIBFOO_VERSON=`$PKG_CONFIG foo --modversion`
  dnl     AC_MSG_RESULT(from pkgconfig: version $LIBFOO_VERSON)
  dnl   else
  dnl     AC_MSG_ERROR(system libfoo is too old: version 1.2.3 required)
  dnl   fi
  dnl else
  dnl   AC_MSG_ERROR(pkg-config not found)
  dnl fi
  dnl PHP_EVAL_LIBLINE($LIBFOO_LIBDIR, SU_DD_SHARED_LIBADD)
  dnl PHP_EVAL_INCLINE($LIBFOO_CFLAGS)

  dnl # --with-su_dd -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/su_dd.h"  # you most likely want to change this
  dnl if test -r $PHP_SU_DD/$SEARCH_FOR; then # path given as parameter
  dnl   SU_DD_DIR=$PHP_SU_DD
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for su_dd files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       SU_DD_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$SU_DD_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the su_dd distribution])
  dnl fi

  dnl # --with-su_dd -> add include path
  dnl PHP_ADD_INCLUDE($SU_DD_DIR/include)

  dnl # --with-su_dd -> check for lib and symbol presence
  dnl LIBNAME=su_dd # you may want to change this
  dnl LIBSYMBOL=su_dd # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $SU_DD_DIR/$PHP_LIBDIR, SU_DD_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_SU_DDLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong su_dd lib version or lib not found])
  dnl ],[
  dnl   -L$SU_DD_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(SU_DD_SHARED_LIBADD)

  PHP_NEW_EXTENSION(su_dd, su_dd.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
