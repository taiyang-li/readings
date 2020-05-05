## 大型重构

### Tease Apart Inheritance 梳理并分解继承体系
某个继承体系同时承担两项责任

建立两个继承体系，并通过委托关系让其中一个可以调用另一个


### convert procedural desion to objects 将过程化设计转化为对象设计

你手上有一些传统过程化风格的代码

将数据记录变成对象，将大块的行为分成小块，并将行为移入到相关对象当中。


### separate domain from presentation 将领域和表述/显示分离
某些gui类中包含了领域逻辑

将领域逻辑分离出来，为他们建立独立的领域类

### extract hierarchy 提炼继承体系
你有某个类做了太多工作，其中一部分工作是以大量条件表达式完成的

建立继承体系，以一个子类表示一种特殊情况