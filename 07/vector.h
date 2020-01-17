#pragma once
#include <iterator>
#include "Allocator.h"
#include "Iterator.h"

template <class T, class Alloc = Allocator<T>>
class Vector {

private:
	Alloc allocate_;
	T* data_;
	size_t size_;
	size_t capacity_ = 10;

public:
	using iterator = Iterator<T>;
	using reverse_iterator = std::reverse_iterator<Iterator<T>>;
	using value_type = T;
	using ptr_t = T*;
	using size_type = size_t;
	using ref_t = T&;

	explicit Vector(size_type n = 0) : size_(n)
	{
		if (n > 0) { s
			capacity_ = n;
		}
		data_ = allocate_.allocate(capacity_);
		for (size_type i = 0; i < size_; ++i) {
			allocate_.construct(data_ + i);
		}
	}

	bool empty() const
	{
		return (size_ == 0);
	}

	size_type size() const
	{
		return size_;
	}
	size_type capacity() const
	{
		return capacity_;
	}

	iterator begin() const 
	{
		return iterator(data_);
	}

	iterator end() const 
	{
		return iterator(data_ + size_);
	}

	reverse_iterator rbegin() const 
	{
		return reverse_iterator(end());
	}

	reverse_iterator rend() const 
	{
		return reverse_iterator(begin());
	}

	void clear() 
	{
		resize(0);
	}

	~Vector()
	{
		resize(0);
		allocate_.deallocate(data_);
	}

	ref_t operator[] (size_type n) {
		if (n >= size_)
			throw std::out_of_range("Out of range");
		return data_[n];
	}

	const ref_t operator[] (size_type n) const {
		if (n >= size_)
			throw std::out_of_range("Out of range");
		return data_[n];
	}


	void push_back(value_type&& value) {
		if (size_ == capacity_)
			reserve(capacity_ * 2);
		allocate_.construct(data_ + size_++, std::move(value));
	}


	void push_back(const value_type& value) {
		if (size_ == capacity_)
			reserve(capacity_ * 2);
		allocate_.construct(data_ + size_++, value);
	}



	void pop_back()
	{
		if (size_ > 0) {
			allocate_.destroy(data_ + size_--);
		}
	}



	void reserve(size_type n)
	{
		if (n < capacity_) {
			return;
		}
		ptr_t new_data = allocate_.allocate(n);
		for (size_type i = 0; i < size_; ++i) {
			allocate_.construct(new_data + i, *(data_ + i));
			allocate_.destroy(data_ + i);
		}
		allocate_.deallocate(data_);
		data_ = new_data;
		capacity_ = n;

	}



	void resize(size_type n)
	{
		if (capacity_ < n) {
			reserve(n);
		}
		for (size_type i = size_; i < n; i++) {
			allocate_.construct(data_ + i);
		}
		for (size_type i = n; i < size_; ++i) {
			allocate_.destroy(data_ + i);
		}
		size_ = n;
	}
};