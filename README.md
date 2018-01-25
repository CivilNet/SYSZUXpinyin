# SYSZUXpinyin
SYSZUXpinyin是一款基于Qt for Embedded linux的拼音输入法，可以输入字母、汉字、符号。目前支持Qt4.6以上的版本。旧的版本尚未测试，Qt5以上也未测试。其使用了嵌入式Qt提供的输入法接口QWSInputMethod。

# 如何使用SYSZUXpinyin?
 - 下载源码，交叉编译出libsyszuxpinyin.so库
 - 对于本地，将syszuxim.h和syszuxpinyin.h头文件和syszuxpinyin.ui面板放置到你Qt程序的源代码路径下。将libsyszuxpinyin.so这4个库放置到你的系统路径下，确保交叉编译工具的ld能能够找到。将你的Qt程序的.pro文件中添加 QMAKE_LIBS += -lsyszuxpinyin；
 - 对于目标机器，将libsyszuxpinyin.so这4个库文件放到合适的路径下（比如linux下LD_LIBRARY_PATH指定的路径），确保程序可以被正确加载。

# demo图片
 ![image](https://github.com/CivilNet/syszuxpinyin/blob/master/images/1.jpg)
 ![image](https://github.com/CivilNet/syszuxpinyin/blob/master/images/2.jpg)
 ![image](https://github.com/CivilNet/syszuxpinyin/blob/master/images/3.jpg)
 ![image](https://github.com/CivilNet/syszuxpinyin/blob/master/images/4.jpg)

# 为什么从CivilNet.CN迁移至GitHub？
SYSZUXpinyin 1.0 于2010年发布并托管在[CivilNet.CN](http://civilnet.cn)上，但是在2017年，[CivilNet.CN](http://civilnet.cn)停止对外提供服务。因此，代码现托管在GitHub上。