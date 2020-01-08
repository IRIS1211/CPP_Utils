# CPP utils

包含自己常用的 CPP 处理函数
以及部分 opencv 和 QT 的处理部分, 
尽量做到通用

其中 test_* 开头的文件 是 doctest 的测试样例, 写的不是很好, 仅供参考

## 库 基本结构

使用类似 QT 库的方式, 全部使用 静态函数, 使用的时候 使用 `Utils::TestFunc()` 这样来调用函数

```cpp
class Utils
{
public:
    static int TestFunc(void);
};
```

## 细分内容

不同的模块放在不同的文件内, 作为基本的处理模块

- Utils_String  字符串处理相关函数
- Utils_Files   处理文件操作以及文件系统的库
- Utils_Time    CPP 的计时函数以及日期函数相关
- Utils_CV      通用的 opencv 相关的函数
- Utils_QT      通用的 QT 相关的函数
- Utils_Data    数据处理的相关内容
- Utils_Logger  封装的 spdlog的相关函数, 方便使用
- Utils_Exception   自定义异常信息, 继承自标准异常, 用于细分不同种类的异常, // 不算通用


