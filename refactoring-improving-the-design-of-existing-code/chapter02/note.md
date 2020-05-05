## 重构原则
###  什么是重构(what)
- 名词：对软件结构的调整，提高可理解性，降低修改成本
- 动词：使用一系列重构手法, 在不改变软件行为的情况下，调整结构

### 为什么重构(why)
- 重构改进软件设计
- 重构使软件更容易理解
- 重构帮助找到bug
- 重构提高编程速度

### 何时重构(when)
- 三次法则(事不过三，三则重构)
- 添加功能时重构
- 修补错误时重构
- 复审代码时重构

### 怎么对经理说
- 经理懂技术：直言不讳
- 经理只关心进度：不要告诉他

### 重构难题
- 数据库(应用和数据库结构紧密耦合, 数据迁移造成了数据库相关代码的重构很困难)
- 修改接口(接口是对外的契约，不要朝令夕改)
- 难以通过重构守法完成的设计改动

### 何时不该重构
- 现有代码根本无法正常工作时，重写比重构来的快
- 靠近deadline, 赶进度要紧，不建议在分心于重构

### 重构与设计
有了重构之后，仍然需要做预先设计，但是不一定找出正确的解决方案，只需要确保方案合理即可。不断的重构将使方案逼近理想状态。

### 重构与性能
- 编写代码时不对性能投以特别关注，直到进入性能优化阶段。
- 在性能优化阶段，应当使用profile工具找到性能瓶颈，发现热点并去除热点