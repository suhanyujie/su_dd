## 准备 prepare
* 下载PHP7的源码 http://php.net/downloads.php
* 解压 `tar xvf phpxxxx.tar.gz`
* 进入主目录 `cd php7.xx`
* 随后进入扩展相关目录：`cd ext`
* 此时目录下有个可执行文件：`./ext_skel.php ` ，它是一个开发PHP扩展的脚手架，这个脚手架可以帮助你生成写扩展的一些文件以及目录
* 命令行下运行 `./ext_skel.php --ext su_dd`，会提示创建成功之类的一段英文文字。此时在当前目录下生成了一个 su_dd 的目录
* `cd su_dd`
* 查看其中的 config.m4 文件，根据实际需要取消对应的注释。如果没有需求，则可以不做修改。
* 在用脚手架生成这个扩展模板的时候。它同时也给我们生成了两个测试的扩展函数：su_dd_test1，su_dd_test1
* 因此，我们可以直接对其进行编译然后调用。编译过程大概如下：

```bash
phpize
./configure
make && make install // 如果是 Ubuntu 系统，需要使用 sudo：sudo make && sudo make install
```

* 使用 `php --ini` 查看 ini 文件的路径，我们在编译玩完扩展后，需要引入到 PHP 中。

```bash
vi /path/to/php.ini
// 将 extension=su_dd.so 追加载 ini 文件的结尾。
```

* 此时运行 `php -m`，可以看到 su_dd 已经位于已安装扩展列表中。
* 至此，准备工作算是做完了。
