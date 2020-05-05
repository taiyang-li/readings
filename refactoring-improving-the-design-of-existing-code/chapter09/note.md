## 简化条件表达式

### decompose conditional
你有一个复杂的条件语句，从if then else三个段落中分别提炼出独立函数

### consolidate conditional expression 合并条件表达式
你有一系列条件测试都得到相同结果，
将这些测试合并成一个条件表达式，并将这个条件表达式提炼成一个独立函数

### consolidate duplicate conditional fragments 合并重复的条件片段
在条件表达式的每个分支上有着相同的一段代码
将这段重复代码搬移到条件表达式之外

### remove control flag
在一系列布尔表达式中，某个变量带有控制标记的作用，以break语句或return语句取代控制标记

### replace nested conditional with guard clauses
函数中的条件逻辑使人难以看清正确的执行路径，使用卫语句表现所有的特殊情况


### replace conditional with polymorphism
你手上有个条件表达式，它根据对象类型的不同而选择不同的行为
将这个条件表达式的每个分支放入子类的一个override函数中，然后将原始函数声明为抽象函数


### introduce null object
你需要再三检查某个对象是否为null
将null值替换成null对象


### introduce assertion 
某一段代码需要对程序状态做出某种假设
以断言明确表现这种假设