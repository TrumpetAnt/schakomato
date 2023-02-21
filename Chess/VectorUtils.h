#pragma once

template <typename T>
T Find(std::Container<T>* container, bool(*evaluator)(T, T), T target) {

	for (T element : container) {
		if (evaluator(element)) {
			return element;
		}
	}
	return null;
};