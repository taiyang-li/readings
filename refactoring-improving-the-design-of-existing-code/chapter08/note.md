## 重新组织数据

### self encapsulate field
直接访问字段使得与字段之间的耦合关系逐渐变得笨拙
为这个字段建立set/get函数，并且只以这些函数来访问字段


### replace data value with object
你有一个数据项，需要与其他数据和行为一起使用才有意义。
将数据项变成对象

### change value to reference 
从一个类衍生出许多彼此相等的实例，希望他们替换为同一个对象
将这个值对象变成引用对象

### change reference to value
你有一个引用对象，很小且不可变，而且不易管理
将他变成一个值对象

### replace array with object
你有一个数组，其中不同元素代表不同的东西
以对象替换数组，对于数组中的每个元素，以一个字段来表示

### duplicate observed data 
你有一些领域数据置身于gui控件中，而领域函数需要访问这些数据。
将该数据复制到一个领域对象中，建立一个observer模式，用以同步领域对象和gui对象内的重复数据

### change unidirectional association to bidirectional 
两个类都需要使用对方特性，但其间只有一条单项连接
添加一个反向指针，并使修改函数能够同时更新两条连接


### change bidirectional association to unidirectional 
两个类之间有双向关联，但是其中一个类如今不再需要另一个类的特性。

### replace magic number with symbolic constant
以字面常量取代魔法数
你有一个字面数值，带有特别含义
创造一个常量，根据其意义为它命名，并将上述的字面数值替换为这个常量


### encapsulate field
你的类中存在一个public字段，将他声明为private, 并提供相应的访问函数

### encapsulate collection
有个函数返回一个集合，让这个函数返回集合的一个只读副本，并在这个类中提供添加/移除集合元素的函数


### replace record with data class 
当你需要面对传统编程环境中的记录结构，为该记录创建一个哑数据对象 

### replace type code with class
类之中有一个数值类型码，但是不影响类的行为
以一个新的类替换该数值类型码

### replace type code with subclass
你有一个不可变的类型码，他会影响类的行为。以子类取代这个类型码

### replace type code with state/strategy
你有一个类型码，他会影响类的行为，但你无法通过继承手法消除它，以状态对象取代类型码

### replace subclass with fields
你的各个子类的唯一差别只在返回常量数据的函数上。
修改这些函数，使他们返回超类中某个新增字段，然后销毁子类。


