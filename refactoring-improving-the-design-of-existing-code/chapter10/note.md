## 简化函数调用

### rename method
函数的名称未能解释函数的用途
修改函数名称

### add parameter 
某个函数需要从调用端得到更多信息
为此函数添加一个对象参数，让该对象带进函数所需信息

### remove parameter
函数本体不在需要某个参数
将本参数取出

### separate query from modifier
某个函数即返回对象状态值，又修改对象状态
建立两个不同的函数，其中一个负责查询，另一个负责修改

### parameterize method
若干函数做了类似的工作，但是函数本体中却包含了不同的值
建立单一函数，以参数表达哪些不同的值

### replace parameter with explicit methods
你有一个函数，其中完全取决于参数值而采取不同的行动
针对该函数的每一个可能值，建立一个独立函数

### preserve whole object
你从对象中取出若干值，将他们作为某一次函数调用的参数
改成传递整个对象

### replace parameter with methods
对象调用某个函数，并将所得结果作为参数，传递给另一个函数，而接受该参数的函数本身也能够调用前一个函数
让参数接受者取出该项参数，并直接调用前一个函数

### introduce parameter object
某些参数总是很自然的同时出现，以一个对象取代这些参数

### remove setting method
类中某个字段应该在对象创建时被设值，然后不再改变
去掉该字段的所有设置函数

### hide method
有个函数，从来没有被其他类用过
将这个函数修改为private

### replace contructor with factory method
你希望在创建对象时不仅仅是做简单的构建动作
将构造函数替换为工厂函数

### encapsulate downcast 
某个函数返回的对象，需要由函数调用者执行向下转型
将向下转型动作移动到函数中

### replace error code with exception
某个函数返回一个特定的代码，用以表示某种错误情况
改成异常

### replace exception with test
面对一个调用者可以预先检查的条件，你抛出了一个异常
修改调用者，使它在调用函数之前先做检查






