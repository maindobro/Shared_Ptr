#include <iostream>


template <typename T, class ...Args>
auto make_shared( Args && ...args ) -> shared_ptr<T>
{
    return shared_ptr<T>( new T( std::forward<Args>(args)... ) );
}


template <typename T>
class shared_ptr
{
public:
	shared_ptr(); /*noexcept*/
	shared_ptr(T* ptr); /*strong*/
	shared_ptr(shared_ptr const&); /*noexcept*/
	shared_ptr(shared_ptr&&); /*noexcept*/
	~shared_ptr(); /*noexcept*/
	auto operator = (shared_ptr const&)->shared_ptr&; /*noexcept*/
	auto operator = (shared_ptr&&)->shared_ptr&; /*noexcept*/
	auto swap(shared_ptr&) -> void; /*noexcept*/
	auto reset() -> void; /*noexcept*/
	auto get() const->T*; /*noexcept*/
	auto operator ->() const->T*; /*strong*/
	auto operator *() const->T&; /*strong*/
	auto countref() const->size_t; /*noexcept*/
private:
	T *ptr_;
	size_t *counter_;
};


template <typename T>
shared_ptr<T>::shared_ptr() : ptr_(nullptr), counter_(nullptr) {}

template <typename T>
shared_ptr<T>::shared_ptr(T* ptr) : ptr_(ptr), counter_(new size_t(1)) {}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr const& x) : ptr_(x.ptr_), counter_(x.counter_) 
{
	if(counter_ != nullptr) ++(*counter_);
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr&& x) : ptr_(x.ptr_), counter_(x.counter_)
{
	x.ptr_ = nullptr;
	x.counter_ = nullptr;
}

template <typename T>
shared_ptr<T>::~shared_ptr()
{
	if (ptr_ != nullptr && counter_ != nullptr && --(*counter_) == 0)
	{
		delete ptr_;
		delete counter_;
	}
}
