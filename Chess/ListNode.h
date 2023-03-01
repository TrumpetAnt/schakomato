#pragma once
#include <memory>

template <typename T>
struct ListNode {
	std::unique_ptr<ListNode> next;
	std::unique_ptr<T> val;
};