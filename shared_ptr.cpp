#include <iostream>
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
