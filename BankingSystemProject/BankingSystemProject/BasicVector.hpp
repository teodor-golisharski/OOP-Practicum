#pragma once
#include <iostream>

#pragma optimize("", off)
template<typename T>
class BasicVector {

private:
	T* data;
	int capacity;
	int current;

	void moveFrom(BasicVector&& other);
	void copyFrom(const BasicVector& other);
	void free();

public:
	BasicVector();
	~BasicVector();
	
	BasicVector(const BasicVector& other);
	BasicVector(BasicVector&& other) noexcept;

	BasicVector& operator=(const BasicVector& other);
	BasicVector& operator=(BasicVector&& other) noexcept;

	void push(T other);
	void insert(T other, unsigned index);

	T& get(unsigned index) const;
	void pop();
	void delete_at(unsigned index);
	int size() const;
	int get_capacity() const;
	void clear();

	T& operator[](unsigned index);
	T& operator[](unsigned index) const;
};

template<class T>
void BasicVector<T>::moveFrom(BasicVector&& other) {
	data = other.data;
	capacity = other.capacity;
	current = other.current;

	other.data = nullptr;
	other.capacity = 0;
	other.current = 0;
}

template<class T>
void BasicVector<T>::free() {
	if (data != nullptr) {
		if constexpr (std::is_pointer_v<T>) {
			for (size_t i = 0; i < current; i++) {
				delete data[i];
			}
		}
		delete[] data;
		data = nullptr;
	}
	current = 0;
	capacity = 0;
}

template<class T>
void BasicVector<T>::clear() {
	free();
	data = new T[1];
	capacity = 1;
	current = 0;
}

template<class T>
BasicVector<T>::BasicVector() {
	data = new T[1];
	capacity = 1;
	current = 0;
}

template<class T>
BasicVector<T>::~BasicVector() {
	free();
}

template<class T>
BasicVector<T>::BasicVector(const BasicVector& other) {
	copyFrom(other);
}

template<class T>
BasicVector<T>::BasicVector(BasicVector&& other) noexcept{
	moveFrom(std::move(other));
}

template<class T>
void BasicVector<T>::copyFrom(const BasicVector& other) {

	data = new T[other.capacity];
	for (int i = 0; i < other.current; i++) {
		data[i] = other.data[i];
	}
	capacity = other.capacity;
	current = other.current;
}

template<class T>
void BasicVector<T>::delete_at(unsigned index) {
	if (index >= current) {
		throw std::out_of_range("Index out of range!");
	}

	for (unsigned i = index; i < current - 1; ++i) {
		data[i] = std::move(data[i + 1]);
	}

	--current;

	if (current < capacity / 4) {
		capacity /= 2;
		T* newData = new T[capacity];
		
		for (unsigned i = 0; i < current; ++i) {
			newData[i] = std::move(data[i]);
		}

		delete[] data;
		data = newData;
	}
}

template<class T>
void BasicVector<T>::push(T other) {
	if (current == capacity) {
		T* temp = new T[2 * capacity];

		for (int i = 0; i < capacity; i++) {
			temp[i] = data[i];
		}

		delete[] data;
		capacity *= 2;
		data = temp;
	}

	data[current] = other;
	current++;
}

template<class T>
void BasicVector<T>::insert(T other, unsigned index) {
	if (index == capacity) {
		push(other);
	}
	data[index] = other;
}

template<class T>
T& BasicVector<T>::get(unsigned index) const {
	if (index < current) {
		return data[index];
	}

	return -1;
}

template<class T>
void BasicVector<T>::pop()
{
	if (current > 0) {
		current--;
	}
}

template<class T>
int BasicVector<T>::size() const {
	return current;
}

template<class T>
int BasicVector<T>::get_capacity() const {
	return capacity;
}

template<class T>
T& BasicVector<T>::operator[](unsigned index) {
	if (index >= current) {
		throw std::out_of_range("Index out of range!");
	}
	return data[index];
}

template<class T>
T& BasicVector<T>::operator[](unsigned index) const {
	if (index >= current) {
		throw std::out_of_range("Index out of range!");
	}
	return data[index];
}

template<class T>
BasicVector<T>& BasicVector<T>::operator=(const BasicVector& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

template<class T>
BasicVector<T>& BasicVector<T>::operator=(BasicVector&& other) noexcept{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

#pragma optimize("", on)


