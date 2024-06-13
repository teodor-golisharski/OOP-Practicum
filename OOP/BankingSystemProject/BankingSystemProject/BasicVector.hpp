#pragma once
#include <iostream>

template<typename T>
class BasicVector {

private:
	T* data;
	int capacity;
	int current;

public:
	BasicVector();
	~BasicVector();

	void push(T other);
	void push(T other, unsigned index);

	T& get(unsigned index) const;
	void pop();
	int size() const;
	int get_capacity() const;

	T& operator[](unsigned index);
	T operator[](unsigned index) const;
};


template<class T>
BasicVector<T>::BasicVector() {
	data = new T[1];
	capacity = 1;
	current = 0;
}

template<class T>
BasicVector<T>::~BasicVector() {
	delete[] data;
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
void BasicVector<T>::push(T other, unsigned index) {
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
T BasicVector<T>::operator[](unsigned index) const {
	if (index >= current) {
		throw std::out_of_range("Index out of range!");
	}
	return data[index];
}





