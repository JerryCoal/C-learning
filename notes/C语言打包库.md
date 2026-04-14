# C语言打包库

## 概述
    打包自己的库，使自己的项目更加舒服

## 创建库方法
### 一、准备工作
1.**新建一个mylib.c**
```c
// mylib.c
#include <stdio.h>
#include "mylib.h" // 引用自己的头文件

// 定义一个公开的加法函数
int my_add(int a, int b) {
    return a + b;
}

// 定义一个公开的打印函数
void my_hello(const char *name) {
    printf("Hello, %s! From mylib.\n", name);
}
```
2.**新建一个mylib.h**(头文件)
```c
// mylib.h
#ifndef MYLIB_H
#define MYLIB_H

// 函数声明，告诉编译器有这些函数
int my_add(int a, int b);
void my_hello(const char *name);

#endif
```

### 二、编译
1.**编译生成目标文件**
    在你的终端（或 CMD/PowerShell），进入你的代码目录，执行：
```bash
# gcc -c 只编译不链接 -o 指定输出文件
gcc -c mylib.c -o mylib.o
```
2.**打包成静态库.a**
```bash
# ar rcs 是创建静态库的标准命令
ar rcs libmylib.a mylib.o
```
    * r：替换库中的旧文件。
      c：创建一个新的库。
      s：生成索引，加快链接速度

### 三、使用你打包的库
1.**创建自己的main.c**
```c
// main.c
#include "mylib.h" // 包含你的库头文件

int main() {
    // 调用库中的函数
    my_hello("C Developer");
    int result = my_add(10, 20);
    printf("10 + 20 = %d\n", result);
    return 0;
}
```
2.**编译并连接自己的库**
```bash
# gcc main.c -o main -L. -lmylib
```
即打开自己项目文件里的./vscode/tasks.json,然后改成
```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "type": "cppbuild",
            "label": "C/C++: gcc 生成活动文件",
            "command": "gcc",
            "args": [
                "-fdiagnostics-color=always",
                "-g",
                "${file}",
                "-o",
                "${fileDirname}/${fileBasenameNoExtension}",
                "-L.",        // 让编译器在当前目录找库
                "-lmylib"     // 链接你的库 libmylib.a
            ],
            "options": {
                "cwd": "${fileDirname}"
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "detail": "调试器生成的任务。"
        }
    ]
}
```

## 注意文件储存格式
三、必须满足的文件结构（非常重要）
**你的文件夹必须这样放：**

```plaintext
你的项目文件夹/
├─ .vscode/
│  └─ tasks.json  (你刚改的)
├─ mylib.h        头文件
├─ mylib.c        库源码
├─ libmylib.a     你打包好的库
└─ main.c         你的测试代码
```