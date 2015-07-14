// Pool.h
// Chris Bowers

/**
 *	This defines and implements the Pool container class.
 *	The pool emulates the functionality of an std::vector, but uses the pool allocation strategy - see PoolAllocator.h
 *	Functionality should be the same as std::vector<T, PoolAllocator<T>>, except this does not implement iterator range based insertion or construction.
 */

#ifndef __POOL_H__
#define __POOL_H__

#include "PoolAllocator.h"
#include <initializer_list>
#include <iterator>
#include <stdexcept>

template<typename T>
struct Pool{
	typedef T* iterator;
	typedef const T* const_iterator;

	Pool();
	Pool(size_t n);
	Pool(size_t n, const T& val);
	Pool(const Pool& other);
	Pool(Pool&& other);
	Pool(std::initializer_list<T> il);
	Pool& operator=(const Pool& other);
	Pool& operator=(Pool&& other);
	Pool& operator=(std::initializer_list<T> il);
	~Pool();

	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;
	const_iterator cbegin() const;
	const_iterator cend() const;

	size_t size() const;
	size_t max_size() const;
	void resize(size_t n);
	void resize(size_t n, const T& val);
	size_t capacity() const;
	bool empty() const;
	void reserve(size_t n);
	void shrink_to_fit();

	T& operator[](size_t n);
	const T& operator[](size_t n) const;
	T& at(size_t n);
	const T& at(size_t) const;
	T& front();
	const T& front() const;
	T& back();
	const T& back() const;
	T* data();
	const T* data() const;
	
	void assign(size_t n, const T& val);
	void assign(std::initializer_list<T> il);
	void push_back(const T& val);
	void push_back(T&& val);
	void pop_back();
	iterator insert(const_iterator position, const T& val);
	iterator insert(const_iterator position, size_t n, const T& val);
	iterator insert(const_iterator position, T&& val);
	iterator insert(const_iterator position, std::initializer_list<T> il);
	iterator erase(const_iterator position);
	iterator erase(const_iterator first, const_iterator last);
	void swap(Pool& other);
	void clear();
	template<class... Args>
	iterator emplace(const_iterator position, Args&&... args);
	template<class... Args>
	void emplace_back(Args&&... args);

	PoolAllocator<T> get_allocator() const;

private:
	T* m_array;
	size_t m_size;
	size_t m_capacity;
	PoolAllocator<T> allocator;
};

template<typename T>
void swap(Pool<T>& x, Pool<T>& y);

template<typename T>
bool operator==(const Pool<T>& lhs, const Pool<T>& rhs);

template<typename T>
bool operator!=(const Pool<T>& lhs, const Pool<T>& rhs);

template<typename T>
bool operator<(const Pool<T>& lhs, const Pool<T>& rhs);

template<typename T>
bool operator<=(const Pool<T>& lhs, const Pool<T>& rhs);

template<typename T>
bool operator>(const Pool<T>& lhs, const Pool<T>& rhs);

template<typename T>
bool operator>=(const Pool<T>& lhs, const Pool<T>& rhs);

// IMPLEMENTATION BEGINS HERE

template<typename T>
Pool<T>::Pool() : Pool{ DEFAULT_CHUNK_SIZE } {}

template<typename T>
Pool<T>::Pool(size_t n) : m_size{ 0 }, m_capacity{ n }, m_array{ allocator.allocate(n) } {}

template<typename T>
Pool<T>::Pool(size_t n, const T& val) : Pool{ n }, m_size{ n } {
	for (size_t i = 0; i < m_size; i++){
		allocator.construct(m_array + i, val);
	}
}

template<typename T>
Pool<T>::Pool(const Pool& other) : Pool{ other.m_capacity }, m_size{ other.m_size } {
	for (size_t i = 0; i < m_size; i++){
		allocator.construct(m_array + i, other[i]);
	}
}

template<typename T>
Pool<T>::Pool(Pool&& other) : m_size{ other.m_size }, m_capacity{ other.m_capacity }, m_array{ other.m_array } {
	other.m_size = 0;
	other.m_capacity = 0;
	other.m_array = nullptr;
}

template<typename T>
Pool<T>::Pool(std::initializer_list<T> il) : Pool{ il.size() }, m_size{ il.size() } {
	auto it = il.begin();
	for (size_t i = 0; i < m_size; i++, it++){
		allocator.construct(m_array + i, *it);
	}
}

template<typename T>
Pool<T>::~Pool() { allocator.deallocate_chunk(m_array); }

template<typename T>
Pool<T>& Pool<T>::operator=(const Pool& other){
	allocator.deallocate_chunk(m_array);
	m_array = allocator.allocate(other.m_capacity);
	m_size = other.m_size;
	m_capacity = other.m_capacity;
	for (size_t i = 0; i < m_size; i++){
		allocator.construct(m_array + i, other[i]);
	}
	return *this;
}

template<typename T>
Pool<T>& Pool<T>::operator=(Pool&& other){
	allocator.deallocate_chunk(m_array);
	m_array = other.m_array;
	m_size = other.m_size;
	m_capacity = other.m_capacity;
	other.m_size = 0;
	other.m_capacity = 0;
	other.m_array = nullptr;
	return *this;
}

template<typename T>
Pool<T>& Pool<T>::operator=(std::initializer_list<T> il){
	allocator.deallocate_chunk(m_array);
	m_array = allocator.allocate(il.size());
	m_size = il.size();
	m_capacity = il.size();
	auto it = il.begin();
	for (size_t i = 0; i < m_size; i++, it++){
		allocator.construct(m_array + i, *it);
	}
	return *this;
}

template<typename T>
typename Pool<T>::iterator Pool<T>::begin() { return m_array; }

template<typename T>
typename Pool<T>::const_iterator Pool<T>::begin() const { return m_array; }

template<typename T>
typename Pool<T>::iterator Pool<T>::end() { return m_array + m_size; }

template<typename T>
typename Pool<T>::const_iterator Pool<T>::end() const { return m_array + m_size; }

template<typename T>
typename Pool<T>::const_iterator Pool<T>::cbegin() const { return m_array; }

template<typename T>
typename Pool<T>::const_iterator Pool<T>::cend() const { return m_array + m_size; }

template<typename T>
size_t Pool<T>::size() const { return m_size; }

template<typename T>
size_t Pool<T>::max_size() const { return allocator.max_size(); }

template<typename T>
void Pool<T>::resize(size_t n){
	if (n <= m_size){
		for (size_t i = n; i < m_size; i++){
			allocator.destroy(m_array + i);
		}
	}
	else{
		if (n > m_capacity) reserve(n);
		for (size_t i = m_size; i < n; i++){
			allocator.construct(m_array + i);
		}
	}
	m_size = n;
}

template<typename T>
void Pool<T>::resize(size_t n, const T& val){
	if (n <= m_size){
		for (size_t i = n; i < m_size; i++){
			allocator.destroy(m_array + i);
		}
	}
	else{
		if (n > m_capacity) reserve(n);
		for (size_t i = m_size; i < n; i++){
			allocator.construct(m_array + i, val);
		}
	}
	m_size = n;
}

template<typename T>
size_t Pool<T>::capacity() const { return m_capacity; }

template<typename T>
bool Pool<T>::empty() const { return m_size == 0; }

template<typename T>
void Pool<T>::reserve(size_t n){
	if (n <= m_capacity) return;
	T* old = m_array;
	m_array = allocator.allocate(n);
	for (size_t i = 0; i < m_size; i++){
		allocator.construct(m_array + i, old[i]);
	}
	allocator.deallocate_chunk(old);
	m_capacity = n;
}

template<typename T>
void Pool<T>::shrink_to_fit() {}

template<typename T>
T& Pool<T>::operator[](size_t n) { return m_array[n]; }

template<typename T>
const T& Pool<T>::operator[](size_t n) const { return m_array[n]; }

template<typename T>
T& Pool<T>::at(size_t n){
	if (n >= m_size) throw std::out_of_range("Pool::at index out of range");
	return m_array[n];
}

template<typename T>
const T& Pool<T>::at(size_t n) const{
	if (n >= m_size) throw std::out_of_range("Pool::at index out of range");
	return m_array[n];
}

template<typename T>
T& Pool<T>::front() { return m_array[0]; }

template<typename T>
const T& Pool<T>::front() const { return m_array[0]; }

template<typename T>
T& Pool<T>::back() { return m_array[m_size - 1]; }

template<typename T>
const T& Pool<T>::back() const { return m_array[m_size - 1]; }

template<typename T>
T* Pool<T>::data() { return m_array; }

template<typename T>
const T* Pool<T>::data() const { return m_array; }

template<typename T>
void Pool<T>::assign(size_t n, const T& val) {
	clear();
	reserve(n);
	m_size = n;
	for (size_t i = 0; i < m_size; i++){
		allocator.construct(m_array + i, val);
	}
}

template<typename T>
void Pool<T>::assign(std::initializer_list<T> il){
	clear();
	reserve(il.size());
	m_size = il.size();
	auto it = il.begin();
	for (size_t i = 0; i < m_size; i++, it++){
		allocator.construct(m_array + i, *it);
	}
}

template<typename T>
void Pool<T>::push_back(const T& val){
	if (m_size == m_capacity) reserve(m_capacity * 1.5);
	allocator.construct(m_array + m_size++, val);
}

template<typename T>
void Pool<T>::push_back(T&& val){
	if (m_size == m_capacity) reserve(m_capacity * 1.5);
	allocator.construct(m_array + m_size++, std::forward<T>(val));
}

template<typename T>
void Pool<T>::pop_back() { allocator.destroy(m_array + --m_size); }

template<typename T>
typename Pool<T>::iterator Pool<T>::insert(const_iterator position, const T& val){
	ptrdiff_t diff = position - m_array;
	if (m_size == m_capacity) reserve(m_capacity * 1.5);
	iterator it;
	for (it = end(); it > m_array + diff; it--){
		*it = *(it - 1);
	}
	*it = val;
	m_size++;
	return it;
}

template<typename T>
typename Pool<T>::iterator Pool<T>::insert(const_iterator position, size_t n, const T& val){
	ptrdiff_t diff = position - m_array;
	if (m_size + n > m_capacity) reserve((m_capacity + n) * 1.5);
	iterator it;
	for (it = end() + n - 1; it > m_array + diff + n - 1; it--){
		*it = *(it - n);
	}
	for (it = m_array + diff; it < m_array + diff + n; it++){
		*it = val;
	}
	m_size += n;
	return m_array + diff;
}

template<typename T>
typename Pool<T>::iterator Pool<T>::insert(const_iterator position, T&& val){
	ptrdiff_t diff = position - m_array;
	if (m_size == m_capacity) reserve(m_capacity * 1.5);
	iterator it;
	for (it = end(); it > m_array + diff; it--){
		*it = *(it - 1);
	}
	*it = std::forward<T>(val);
	m_size++;
	return it;
}

template<typename T>
typename Pool<T>::iterator Pool<T>::insert(const_iterator position, std::initializer_list<T> il){
	ptrdiff_t diff = position - m_array;
	size_t n = il.size();
	if (m_size + n > m_capacity) reserve((m_capacity + n) * 1.5);
	iterator it;
	for (it = end() + n - 1; it > m_array + diff + n - 1; it--){
		*it = *(it - n);
	}
	auto val = il.begin();
	for (it = m_array + diff; it < m_array + diff + n; it++, val++){
		*it = *val;
	}
	m_size += n;
	return m_array + diff;
}

template<typename T>
typename Pool<T>::iterator Pool<T>::erase(const_iterator position){
	ptrdiff_t diff = position - m_array;
	iterator it = m_array + diff;
	allocator.destroy(it);
	for (; it < end() - 2; it++){
		*it = *(it + 1);
	}
	m_size--;
	return m_array + diff;
}

template<typename T>
typename Pool<T>::iterator Pool<T>::erase(const_iterator first, const_iterator last){
	ptrdiff_t fdiff = first - m_array;
	ptrdiff_t ldiff = last - m_array;
	ptrdiff_t range = last - first;
	iterator it;
	for (it = m_array + fdiff; it < m_array + ldiff; it++){
		allocator.destroy(it);
		if (it + range < end())
			*it = *(it + range);
	}
	for (; it < end() - (range + 1); it++){
		*it = *(it + range);
	}
	m_size -= range;
	return m_array + fdiff;
}

template<typename T>
void Pool<T>::swap(Pool& other){
	std::swap(m_array, other.m_array);
	std::swap(m_size, other.m_size);
	std::swap(m_capacity, other.m_capacity);
}

template<typename T>
void Pool<T>::clear(){
	for (iterator it = begin(); it < end(); it++){
		allocator.destroy(it);
	}
	m_size = 0;
}

template<typename T> template<class... Args>
typename Pool<T>::iterator Pool<T>::emplace(const_iterator position, Args&&... args){
	ptrdiff_t diff = position - m_array;
	if (m_size == m_capacity) reserve(m_capacity * 1.5);
	iterator it;
	for (it = end(); it > m_array + diff; it--){
		*it = *(it - 1);
	}
	allocator.construct(it, std::forward<Args>(args)...);
	m_size++;
	return it;
}

template<typename T> template<class... Args>
void Pool<T>::emplace_back(Args&&... args){
	if (m_size == m_capacity) reserve(m_capacity * 1.5);
	allocator.construct(m_array + m_size++, std::forward<Args>(args)...);
}

template<typename T>
PoolAllocator<T> Pool<T>::get_allocator() const { return allocator; }

template<typename T>
void swap(Pool<T>& x, Pool<T>& y) { x.swap(y); }

template<typename T>
bool operator==(const Pool<T>& lhs, const Pool<T>& rhs){
	if (!(lhs.size() == rhs.size())) return false;
	for (size_t i = 0; i < lhs.size(); i++){
		if (!(lhs[i] == rhs[i])) return false;
	}
	return true;
}

template<typename T>
bool operator!=(const Pool<T>& lhs, const Pool<T>& rhs) { return !(lhs == rhs); }

template<typename T>
bool operator<(const Pool<T>& lhs, const Pool<T>& rhs){
	auto lit = lhs.cbegin();
	auto rit = rhs.cbegin();
	while (lit != lhs.cend()){
		if (rit == rhs.cend() || *rit < *lit) return false;
		else if (*lit < *rit) return true;
		++lit;
		++rit;
	}
	return rit != rhs.cend();
}

template<typename T>
bool operator<=(const Pool<T>& lhs, const Pool<T>& rhs) { return !(rhs < lhs); }

template<typename T>
bool operator>(const Pool<T>& lhs, const Pool<T>& rhs) { return rhs < lhs; }

template<typename T>
bool operator>=(const Pool<T>& lhs, const Pool<T>& rhs) { return !(lhs < rhs); }

#endif // __POOL_H__
