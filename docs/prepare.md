## 准备 prepare
* 下载PHP7的源码 http://php.net/downloads.php
* 解压 `tar xvf phpxxxx.tar.gz`
* 进入主目录 `cd php7.xx`
* 随后进入扩展相关目录：`cd ext`
* 此时运行 `./ext_skel` ，它是一个开发PHP扩展的脚手架，这个脚手架可以帮助你生成写扩展的一些文件以及目录
* `./ext_skel su_dd`，此时在当前目录下生成了一个 su_dd 的目录
* `cd su_dd`
* 查看其中的 config.m4 文件，将其中的一下内容复制一份，粘贴在其下方，作为备份，如下：

```
dnl PHP_ARG_ENABLE(su_dd, whether to enable su_dd support,
dnl Make sure that the comment is aligned:
dnl [  --enable-su_dd           Enable su_dd support])

dnl PHP_ARG_ENABLE(su_dd, whether to enable su_dd support,
dnl Make sure that the comment is aligned:
dnl [  --enable-su_dd           Enable su_dd support])
```

* 在这个文件中，以 `dnl` 为前缀的就表示是注释
* 将其中的一份，去掉其注释：

```
dnl PHP_ARG_ENABLE(su_dd, whether to enable su_dd support,
dnl Make sure that the comment is aligned:
dnl [  --enable-su_dd           Enable su_dd support])

PHP_ARG_ENABLE(su_dd, whether to enable su_dd support,
[  --enable-su_dd           Enable su_dd support])
```

* 至此，准备工作算是做完了。
