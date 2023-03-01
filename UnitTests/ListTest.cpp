#include "pch.h"
#include "List.h"
#include "Square.h"


TEST(ListTestInt, CreateAndDelete) {
	std::unique_ptr<List<int>> list = std::make_unique<List<int>>(List<int>());
	EXPECT_EQ(list->Count(), 0);
	list.reset();
	EXPECT_EQ(list.get(), nullptr);
}

TEST(ListTestInt, Append) {
	std::unique_ptr<List<int>> list = std::make_unique<List<int>>(List<int>());

	list->Append(1);

	EXPECT_EQ(list->Count(), 1);

	list->Append(2);

	EXPECT_EQ(list->Count(), 2);

	list->Append(2);
	list->Append(2);
	EXPECT_EQ(list->Count(), 4);

	list.reset();
	EXPECT_EQ(list.get(), nullptr);
}

TEST(ListTestInt, Get) {
	std::unique_ptr<List<int>> list = std::make_unique<List<int>>(List<int>());

	list->Append(1);
	list->Append(2);
	list->Append(3);

	EXPECT_EQ(list->Get(0), 1);
	EXPECT_EQ(list->Get(1), 2);
	EXPECT_EQ(list->Get(2), 3);

	list->Append(3);
	list->Append(2);
	list->Append(1);

	EXPECT_EQ(list->Get(3), 3);
	EXPECT_EQ(list->Get(4), 2);
	EXPECT_EQ(list->Get(5), 1);

	EXPECT_ANY_THROW(list->Get(-1));
	EXPECT_ANY_THROW(list->Get(6));
}

TEST(ListTestInt, RemoveEnd) {
	std::unique_ptr<List<int>> list = std::make_unique<List<int>>(List<int>());
	EXPECT_ANY_THROW(list->RemoveEnd());
	list->Append(1);
	list->Append(2);
	list->Append(3);

	EXPECT_EQ(list->Count(), 3);

	EXPECT_EQ(list->RemoveEnd(), 3);
	EXPECT_EQ(list->RemoveEnd(), 2);
	EXPECT_EQ(list->RemoveEnd(), 1);

	EXPECT_EQ(list->Count(), 0);

	EXPECT_ANY_THROW(list->RemoveEnd());
}

TEST(ListTestInt, MultipleActions) {
	std::unique_ptr<List<int>> list = std::make_unique<List<int>>(List<int>());
	list->Append(1);
	list->Append(2);
	list->Append(3);

	EXPECT_EQ(list->Count(), 3);

	EXPECT_EQ(list->RemoveEnd(), 3);
	EXPECT_EQ(list->RemoveEnd(), 2);
	EXPECT_EQ(list->RemoveEnd(), 1);

	EXPECT_EQ(list->Count(), 0);

	list->Append(1);
	list->Append(2);
	list->Append(3);

	EXPECT_EQ(list->RemoveEnd(), 3);

	list->Append(2);
	list->Append(2);

	EXPECT_EQ(list->Count(), 4);

	EXPECT_EQ(list->RemoveEnd(), 2);
	EXPECT_EQ(list->RemoveEnd(), 2);
	EXPECT_EQ(list->RemoveEnd(), 2);
	EXPECT_EQ(list->RemoveEnd(), 1);

	EXPECT_EQ(list->Count(), 0);

	for (int i = 1; i < 1001; i++) {
		list->Append(i);
		EXPECT_EQ(list->Count(), i);
	}

	for (int i = 1000; i > 0; i--) {
		EXPECT_EQ(list->RemoveEnd(), i);
	}

	EXPECT_EQ(list->Count(), 0);
}

TEST(ListTestSquare, CreateAndDelete) {
	std::unique_ptr<List<Square>> list = std::make_unique<List<Square>>(List<Square>());
	EXPECT_EQ(list->Count(), 0);
	list.reset();
	EXPECT_EQ(list.get(), nullptr);
}

TEST(ListTestSquare, Append) {
	std::unique_ptr<List<Square>> list = std::make_unique<List<Square>>(List<Square>());

	list->Append(Square{'A', 0});

	EXPECT_EQ(list->Count(), 1);

	list->Append(Square{ 'A', 1 });

	EXPECT_EQ(list->Count(), 2);

	list->Append(Square{ 'A', 2 });
	list->Append(Square{ 'A', 3 });
	EXPECT_EQ(list->Count(), 4);

	list.reset();
	EXPECT_EQ(list.get(), nullptr);
}

TEST(ListTestSquare, Get) {
	std::unique_ptr<List<Square*>> list = std::make_unique<List<Square*>>(List<Square*>());

	list->Append(new Square{'A', 0});
	list->Append(new Square{ 'B', 1 });
	list->Append(new Square{ 'C', 2 });

	Square x = *(list->Get(0));
	Square y = Square{ 'A', 0 };
	EXPECT_EQ(x, y);
	x = *(list->Get(1));
	y = Square{ 'B', 1 };
	EXPECT_EQ(x, y);
	x = *(list->Get(2));
	y = Square{ 'C', 2 };
	EXPECT_EQ(x, y);

	list->Append(new Square{ 'D', 5 });
	list->Append(new Square{ 'E', 6 });
	list->Append(new Square{ 'F', 7 });

	x = *(list->Get(3));
	y = Square{ 'D', 5 };
	EXPECT_EQ(x, y);
	x = *(list->Get(4));
	y = Square{ 'E', 6 };
	EXPECT_EQ(x, y);
	x = *(list->Get(5));
	y = Square{ 'F', 7 };
	EXPECT_EQ(x, y);

	EXPECT_ANY_THROW(list->Get(-1));
	EXPECT_ANY_THROW(list->Get(6));
}

TEST(ListTestSquare, RemoveEnd) {
	std::unique_ptr<List<Square*>> list = std::make_unique<List<Square*>>(List<Square*>());
	EXPECT_ANY_THROW(list->RemoveEnd());
	list->Append(new Square{ 'A', 0 });
	list->Append(new Square{ 'B', 1 });
	list->Append(new Square{ 'C', 2 });

	EXPECT_EQ(list->Count(), 3);

	Square x = *(list->RemoveEnd());
	Square y = Square{ 'C', 2 };
	EXPECT_EQ(x, y);
	x = *(list->RemoveEnd());
	y = Square{ 'B', 1 };
	EXPECT_EQ(x, y);
	x = *(list->RemoveEnd());
	y = Square{ 'A', 0 };
	EXPECT_EQ(x, y);

	EXPECT_EQ(list->Count(), 0);
	EXPECT_ANY_THROW(list->RemoveEnd());
}