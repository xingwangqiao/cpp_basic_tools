# cpp_basic_tools
c++ 常用基础构件
## basic::Any
现代 c++ 中，为有效管理内存使用，智能指针被广泛使用，这导致在代码中频繁的出现各种类型的 std::shared_ptr ，这降低了代码的整洁性、可读性。
basic::Any 抽象统一代码中各种类型的 std::shared_ptr ，用以提升代码整洁程度。