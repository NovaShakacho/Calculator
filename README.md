
### 简介:
- ##### 概述:
    一个使用cpp开发的简单计算器。<br>
    核心代码位于"Calculator.h"，用于***计算字符串形式的中缀表达式***。<br>
    "Source.h"可以对指定格式的文件进行操作，但是这不重要。
- ##### 适用范围:
   - 可行：小数, 负号, 操作符"+ - * / ( )"
   - 不可行：***正号***
- ##### 开发环境：
  - Windows 11
  - Visual Studio 2022 Community
***
### 实现逻辑:
> ##### 注意:
> ***"中缀表达式转换后缀表达式" 和 "计算后缀表达式" 具有通用性， 
> 需求变更只需更新 "字符串解析为中缀表达式"***
- ##### 数据类型描述:
  程序必须使用一种数据结构来存储操作数和操作符。
```cpp
struct data_type
{
	data_type(double _number);
	data_type(char _char);
	bool is_symbol;
	double number;
	char symbol;
};
```
- ##### 字符串解析为中缀表达式：
    1. '(' 加入中缀表达式，辅助计算后缀表达式。
    2. 遍历字符串：
        - 提取操作数加入中缀表达式，只提取正数。
        - 提取操作符加入中缀表达式。
        - ***处理负号***：
            - 识别：考虑仅出现在'('右侧和字符串开头的负号。
            - 处理：0先加入中缀表达式，减号后加入中缀表达式。
    3. ')' 加入中缀表达式，与 '(' 配对。
- ##### 中缀表达式转换后缀表达式：
    1. 后缀表达式和中缀表达式都存储在队列中。
    2. 创建一个栈来临时存储操作数。
    3. 遍历中缀表达式的队列：
        - 如果是操作数，则添加到后缀表达式中。
        - 如果是操作符(OP)，比较OP和栈顶操作符的优先级:
          - 如果 OP 的优先级更高，则 OP 压栈。
          - 否则，不断弹出栈中的操作符到后缀表达式中，直到 OP 的优先级高于栈顶的操作符。
        - 括号的处理方式:
          - 将左括号的优先级设置为最低，但是直接添加到后缀表达式中。
          - 如果遇到右括号，那么从操作符栈中不断弹出操作符到后缀表达式中，直到遇到左括号。
    4. 如果栈不为空，则依次将元素弹出到后缀表达式中。
- ##### 计算后缀表达式：
    1. 创建一个临时栈用于计算。
    2. 遍历后缀表达式队列：
        - 如果是操作数，则将其压入栈。
        - 否则，删除栈的顶部两个元素并执行指定的计算。
    3. 弹出栈中最后一个元素得到结果。
***

### 参考:
- ##### [PTA-7-20 表达式转换（中缀转后缀，带括号，负数，小数转换）](https://blog.csdn.net/weixin_41012699/article/details/105279523)
- ##### [C++实现计算器，运用栈，输出后缀表达式，有负数、小数处理](https://www.whcsrl.com/blog/1029875)
