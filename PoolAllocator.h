// PoolAllocator.h
// Chris Bowers

/**
 *	This defines and implements a pool allocator. The pool allocator allocates space for multiple objects all at once.
 *	If a large number of small objects are needed, pool allocation is more efficient than standard heap allocation.
 *	Use should be restricted to objects with trivial destructors for maximum efficiency.
 */

#ifndef __POOLALLOCATOR_H__
#define __POOLALLOCATOR_H__

#include <memory>
#include <mutex>
#include <new>
#include <utility>
#include <unordered_set>

#define DEFAULT_CHUNK_SIZE 32U

template<size_t ELEM_SIZE>
union ChunkElem{
	ChunkElem* next;
	unsigned char padding[ELEM_SIZE];
};

template<size_t ELEM_SIZE>
struct PoolChunk{
	PoolChunk(size_t elem_count);
	~PoolChunk();
	bool in(void* p) const;
	bool empty() const;
	bool full() const;
	void* allocate();
	void deallocate(void* p);
	size_t size() const;

private:
	ChunkElem<ELEM_SIZE>* head;
	ChunkElem<ELEM_SIZE>* first_free;
	size_t num_allocs;
	size_t capacity;
};

template<typename T>
class PoolAllocator{
public:
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef T value_type;
	template<typename U>
	struct rebind{
		typedef PoolAllocator<U> other;
	};

	PoolAllocator();
	PoolAllocator(const PoolAllocator&);
	template<typename U>
	PoolAllocator(const PoolAllocator<U>&);
	~PoolAllocator();

	pointer address(reference x) const;
	const_pointer address(const_reference x) const;
	pointer allocate(size_type n, const void* hint = nullptr);
	void reserve_chunk(size_type n);
	void deallocate(pointer p, size_type n);
	void deallocate_chunk(pointer p);
	template<typename U, typename... Args>
	void construct(U* p, Args&&... args);
	template<typename U>
	void destroy(U* p);
	size_type max_size() const;

private:
	struct PoolSet{
		~PoolSet();
		std::unordered_set<PoolChunk<sizeof(T)>*> set;
		std::mutex access_mtx;
	};
	static PoolSet m_chunks;
};

// IMPLEMENTATION BEGINS HERE

template<size_t ELEM_SIZE>
PoolChunk<ELEM_SIZE>::PoolChunk(size_t elem_count) : num_allocs{ 0 }, capacity{ elem_count } {
	first_free = head = new ChunkElem<ELEM_SIZE>[capacity];
	ChunkElem<ELEM_SIZE>* curr = head;
	for (size_t i = 0; i < capacity - 1; i++, curr++){
		curr->next = curr + 1;
	}
	curr->next = nullptr;
}

template<size_t ELEM_SIZE>
PoolChunk<ELEM_SIZE>::~PoolChunk(){
	delete[] head;
	first_free = head = nullptr;
}

template<size_t ELEM_SIZE>
bool PoolChunk<ELEM_SIZE>::in(void* p) const { return p >= head && p < (head + capacity); }

template<size_t ELEM_SIZE>
bool PoolChunk<ELEM_SIZE>::empty() const { return num_allocs == 0; }

template<size_t ELEM_SIZE>
bool PoolChunk<ELEM_SIZE>::full() const { return num_allocs == capacity; }

template<size_t ELEM_SIZE>
void* PoolChunk<ELEM_SIZE>::allocate() {
	if (full()) return nullptr;
	void* old_first = first_free;
	first_free = first_free->next;
	num_allocs++;
	return old_first;
}

template<size_t ELEM_SIZE>
void PoolChunk<ELEM_SIZE>::deallocate(void* p){
	if (!in(p)) return;
	ChunkElem<ELEM_SIZE>* old_first = first_free;
	first_free = (ChunkElem<ELEM_SIZE>*)p;
	first_free->next = old_first;
	num_allocs--;
}

template<size_t ELEM_SIZE>
size_t PoolChunk<ELEM_SIZE>::size() const { return capacity; }

template<typename T>
PoolAllocator<T>::PoolAllocator() {}

template<typename T>
PoolAllocator<T>::PoolAllocator(const PoolAllocator&) {}

template<typename T> template<typename U>
PoolAllocator<T>::PoolAllocator(const PoolAllocator<U>&) {}

template<typename T>
PoolAllocator<T>::~PoolAllocator() {}

template<typename T>
typename PoolAllocator<T>::pointer PoolAllocator<T>::address(reference x) const { return &x; }

template<typename T>
typename PoolAllocator<T>::const_pointer PoolAllocator<T>::address(const_reference x) const { return &x; }

template<typename T>
typename PoolAllocator<T>::pointer PoolAllocator<T>::allocate(size_type n, const void* hint){
	std::lock_guard<std::mutex> lock{ m_chunks.access_mtx };
	switch (n){
	case 0:
		return nullptr;
		break;
	case 1:
		for (auto chunk : m_chunks.set){
			if (!chunk->full()) return (pointer)chunk->allocate();
		}
		break;
	default:
		break;
	}
	auto it = m_chunks.set.insert(m_chunks.set.cend(), ::new PoolChunk<sizeof(T)>(n == 1 ? DEFAULT_CHUNK_SIZE : n));
	return (pointer)((*it)->allocate());
}

template<typename T>
void PoolAllocator<T>::reserve_chunk(size_type n) { m_chunks.set.insert(::new PoolChunk<sizeof(T)>(n)); }

template<typename T>
void PoolAllocator<T>::deallocate(pointer p, size_type n){
	if (n == 0 || p == nullptr) return;
	std::lock_guard<std::mutex> lock{ m_chunks.access_mtx };
	for (auto chunk : m_chunks.set){
		if (chunk->in(p)){
			for (size_t i = n - 1; i >= 0; i--){
				chunk->deallocate(p + i);
			}
			return;
		}
	}
}

template<typename T>
void PoolAllocator<T>::deallocate_chunk(pointer p){
	if (p == nullptr) return;
	std::lock_guard<std::mutex> lock{ m_chunks.access_mtx };
	auto it = m_chunks.set.find((PoolChunk<sizeof(T)>*)p);
	if (it == m_chunks.set.end()) return;
	delete *it;
	m_chunks.set.erase(it);
}

template<typename T> template<typename U, typename... Args>
void PoolAllocator<T>::construct(U* p, Args&&... args) { ::new (p) U(std::forward<Args>(args)...); }

template<typename T> template<typename U>
void PoolAllocator<T>::destroy(U* p) { p->~U(); }

template<typename T>
typename PoolAllocator<T>::size_type PoolAllocator<T>::max_size() const { return std::allocator<T>().max_size(); }

template<typename T>
PoolAllocator<T>::PoolSet::~PoolSet() {
	for (auto chunk : set){
		delete chunk;
	}
}

template<typename T>
typename PoolAllocator<T>::PoolSet PoolAllocator<T>::m_chunks;

#endif // __POOLALLOCATOR_H__
