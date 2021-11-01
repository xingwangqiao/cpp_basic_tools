# cpp_basic_tools
c++ 常用基础构件
## basic::Any
现代 c++ 中，为有效管理内存使用，智能指针被广泛使用，这导致在代码中频繁的出现各种类型的 std::shared_ptr ，这降低了代码的整洁性、可读性。
basic::Any 抽象统一代码中各种类型的 std::shared_ptr ，用以提升代码整洁程度。

## basic::InstancesResourceManager/InstanceResources
c++ 中，系统的运行依赖一个个被创建的实例。对外提供接口的实例可以叫做引擎，而类似这种的实例通常需要在其内部管理一系列的资源（内部产生的/外部传递进来的）。
basic::InstanceResources 利用 std::shard_ptr 自动管理内存的优势，抽象一组接口统一管理单一实例中的所有资源。
basic::InstancesResourceManager 则维护系统中一组实例及其管理的资源。

## basic::Logger
代码开发过程中，日志是必不可少的工具集之一，通过在代码的关键节点中放置适当的日志可以起到监控代码运行流、统计运行数据、问题分析等功能。Logger 设计并提供风格统一，使用简单的日志标记接口，并将日志内容通过唯一的回调接口暴露，实现本地日志收集和处理的分离。使用时只需要关注日志标注，以及如何处理收集的日志即可 (通常是通过实现对外暴露的回调)。