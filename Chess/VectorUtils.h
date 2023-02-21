#pragma once
#include <functional>

template <typename T>
T* Find(std::vector<T*>* vector, std::function<bool(T*)> evaluator) {
	for (T* element : *vector) {
		if (evaluator(element)) {
			return element;
		}
	}
	return NULL;
};