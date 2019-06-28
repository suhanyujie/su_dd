# 扩展依赖
* 关于开发 PHP 扩展时依赖于其他的 PHP 扩展的处理方法，在信海龙老师的博客文章“[ php7 扩展开发之依赖其他扩展](https://www.bo56.com/php7%e6%89%a9%e5%b1%95%e5%bc%80%e5%8f%91%e4%b9%8b%e4%be%9d%e8%b5%96%e5%85%b6%e4%bb%96%e6%89%a9%e5%b1%95/)”中已经讲的很清楚了，在这里做个实践，并整理一下。

## 误区
* 最近在看 PHP 的函数源码，看的同时也在做一些实践。在开发扩展 a （只是个代称）时，需要依赖扩展 mbstring 扩展中的一些东西
* 在没有看到海龙老师的博客文章之前，我想当然的以为只需要将扩展 mbstring 对应的源码文件引入就行，例如：

```c
#include "ext/mbstring/libmbfl/mbfl/mbfl_encoding.h"
#include "ext/mbstring/libmbfl/mbfl/mbfl_encoding.c"
```

* 这样引入，当你编译扩展 a 时，就会提示找不到 mbfl_encoding.c 文件。因此这种方法是不可取的。

## 正确地依赖
* 当一个扩展 a 需要使用扩展 b 中的一些函数，我们需要明确以下几点：
    * 扩展 b 的相关头文件需要被安装在 PHP 的安装目录的某个目录下，一般是 `/usr/local/php/include/php/ext`，根据实际的 PHP 安装目录而定。
    * 只有扩展 b 中头文件中声明了的函数才能够被扩展 a 所调用。

### 扩展头文件尚未被安装
* 根据海龙老师博客提到的，如果被依赖的扩展 b 的相关头文件尚未安装到对应目录下，那么需要你手动指定。这时候需要更改扩展 b 了
* 首先，在扩展 b 对应的 config.m4 文件的顶部新增：

```c
PHP_INSTALL_HEADERS(ext/su_dd, [php_su_dd.h])
```

* 其中，su_dd 是扩展的名称，`php_su_dd.h` 则是扩展的头文件，如果有**多个**，可以使用**空格**隔开。
* 此时重新编译扩展 b。编译的 make install 完成后，输出中会有一行提示：`Installing header files:          /usr/local/php/include/php/`
* 此时，你可以查看目录中是否存在对应头文件：`ll /usr/local/php/include/php/ext/su_dd`，原本 su_dd 目录是不存在的，而此时已经存在了。

### 依赖声明
* 此时意味着可以去依赖扩展 b 的条件了，但是我们需要让扩展 a 知道它依赖扩展 b，否则可能会出现当你编译扩展 a 时，扩展 b 尚未被编译的情况。这种情况我尝试了一下，依赖一个不存在的扩展，你的扩展 a 还是可以编译通过的，但是在你使用扩展的时候会报 `Segmentation fault (core dumped)` 错误。感觉这一点很坑，没有在编译的时候提示出来。
* 依赖声明就是在你的扩展源代码中，添加一些声明，调整一下 `zend_module_entry` 类型的变量值，源文件中你可以搜索关键词 `zend_module_entry`：

```c
// 点1.自己新增的静态常量
static const  zend_module_dep su_dd_deps[] = {
    ZEND_MOD_REQUIRED("su_dd") // su_dd 是被依赖的扩展名称
    ZEND_MOD_END
};
zend_module_entry s2_module_entry = {
	STANDARD_MODULE_HEADER_EX, NULL,// 点2.这一行本只有一段 `STANDARD_MODULE_HEADER`，依赖其他扩展时，要改为 `STANDARD_MODULE_HEADER_EX, NULL,`
	su_dd_deps,                     // 点3.将声明的常量 su_dd_deps 放在这个位置
	"s2",					/* Extension name */
	s2_functions,			/* zend_function_entry */
	// ...
};
```

* 以上代码段是修改后的，修改需要做到上面注释中提到的 3 点：
    * 点1.自己新增的静态常量
    * 点2.这一行本只有一段 `STANDARD_MODULE_HEADER`，依赖其他扩展时，要改为 `STANDARD_MODULE_HEADER_EX, NULL,`
    * 点3.将声明的常量 su_dd_deps 放在这个位置
* 然而，我在实际操作过程中，将依赖声明的修改部分恢复到修改前的状态，发现依赖还是有效的。我的意思是它看起来不是那么重要，没有它，依赖调用也能正常进行。
* 但为了让一切都正常，还是请按照争取的方式做吧！因为你偷懒省略了，也许会对之后的使用或者开发造成一些难以预料的后果，那就麻烦了。
* 我甚至还做了一次尝试，将依赖声明保留，但是我将依赖的扩展改为它本身：`ZEND_MOD_REQUIRED("s2")`(s2 是扩展 a 的扩展名)，也就是自己依赖自己，也是能正常工作的。但是如果你改为不存在的扩展名，就会在运行时报错。因此，我猜测，是编译时，只对扩展是否存在做了校验。

### 头文件引入
* 上面说到，没有依赖声明，也能运行，是因为有正确的头文件引入为前提的：

```c
#include "ext/su_dd/php_su_dd.h"
```

* `php_su_dd.h` 就是被依赖扩展 b 的头文件。引入它，你的扩展就能正常调用扩展 b 的函数了。

## 参考资料
* [php7 扩展开发之依赖其他扩展](https://www.bo56.com/php7%e6%89%a9%e5%b1%95%e5%bc%80%e5%8f%91%e4%b9%8b%e4%be%9d%e8%b5%96%e5%85%b6%e4%bb%96%e6%89%a9%e5%b1%95/
