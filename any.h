/**
 * @brief 使用统一的类型用于管理频繁出现的 std::shared_ptr
 * 
 */
#include <memory>

namespace basic {
class Any {
public:
    Any() = default;
    ~Any() = default;

    Any(std::nullptr_t) : Any() {}

    Any(const Any& rhs) : m_ptr_(rhs.m_ptr_) { }
    Any(Any &&rhs) : m_ptr_(std::move(rhs.m_ptr_)) { }

    template <typename T>
    Any(std::shared_ptr<T> rhs) :m_ptr_(std::static_pointer_cast<void>(rhs)) { }

    template <typename T>
    Any(T* ptr) : m_ptr_(std::shared_ptr<void>((void*)ptr)){ }

    Any& operator= (const Any& rhs) {
        if(&rhs == this)
            return *this;
        this->m_ptr_ = rhs.m_ptr_;
        return *this;
    } 
    Any& operator= (Any&& rhs) {
        this->m_ptr_ = std::move(rhs.m_ptr_);
        return *this;
    }

    bool operator== (const Any& rhs) {
        return this->m_ptr_ == rhs.m_ptr_;
    }
    bool operator!= (const Any& rhs) {
        return !(*this == rhs);
    }

    template <typename T>
    bool operator== (std::shared_ptr<T> rhs) {
        return this->m_ptr_ == std::static_pointer_cast<void>(rhs);
    }
    template <typename T>
    bool operator!= (std::shared_ptr<T> rhs) {
        return !(*this == rhs);
    }
    
    template <typename T>
    bool operator== (T* rhs) {
        return this->m_ptr_.get() == (void*)(rhs);
    }
    template <typename T>
    bool operator!= (T* rhs) {
        return !(*this == rhs);
    }

    operator bool () {
        return m_ptr_ != nullptr;
    }

    template <typename T>
    std::shared_ptr<T> get() {
        return std::static_pointer_cast<T>(m_ptr_);
    }

    void reset() {
        m_ptr_.reset();
    }

protected:
    std::shared_ptr<void> m_ptr_;
};
}