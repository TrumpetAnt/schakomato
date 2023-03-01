#pragma once
#include <memory>
#include <stdexcept>
#include <format>
#include "ListNode.h"

template <typename T>
class List
{
public:
	int Count();
	void Append(T val);
	T RemoveEnd();
	T Get(int n);
private:
	std::unique_ptr<ListNode<T>> first;
	int count;
};

template<typename T> std::unique_ptr<ListNode<T>>* GetIndex(std::unique_ptr<ListNode<T>>* node, int n) {
	return n < 1
		? node
		: GetIndex(&(node->get()->next), n - 1);
}

template<typename T> T ResetAndGetNextNode(std::unique_ptr<ListNode<T>>* node) {
	auto ret_val = *(*node)->next->val;
	(*node)->next->val.reset();
	(*node)->next.reset();
	return ret_val;
}

template<typename T> int List<T>::Count() {
	return count;
}

template<typename T> void List<T>::Append(T val) {
	std::unique_ptr<ListNode<T>>* last = GetIndex(&first, count);
	*last = std::make_unique<ListNode<T>>(ListNode<T>{nullptr, std::make_unique<T>(val)});
	count += 1;
}

template<typename T> T List<T>::RemoveEnd() {
	if (count == 0) {
		throw new std::invalid_argument("Unable to remove from empty list.");
	}

	T ret_val;
	if (count == 1) {
		ret_val = *first->val;
		first->val.reset();
		first.reset();
	}
	else {
		std::unique_ptr<ListNode<T>>* second_to_last = GetIndex(&first, count - 2);
		ret_val = ResetAndGetNextNode(second_to_last);
	}

	count -= 1;
	return ret_val;
}

template<typename T> T List<T>::Get(int n) {
	if (n >= count || n < 0) {
		throw new std::invalid_argument("Index out of range.");
	}
	return *(GetIndex(&first, n)->get()->val);
}
