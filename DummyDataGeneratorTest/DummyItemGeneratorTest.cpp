#include "generator/DummyItemGenerator.h"
#include "repository/IItemRepository.h"

#include "gmock/gmock.h"

#include <vector>

using namespace testing;

class MockItemRepository : public IItemRepository
{
    public:
        MOCK_METHOD(Item, save, (const Item& item), (override));
        MOCK_METHOD(std::vector<Item>, findAll, (), (override));
};

TEST(DummyItemGeneratorTest, GenerateCallsSaveExactlyCountTimes)
{
    MockItemRepository repository;
    DummyItemGenerator generator(repository);

    EXPECT_CALL(repository, save(_))
        .Times(5)
        .WillRepeatedly(ReturnArg<0>());

    EXPECT_EQ(generator.generate(5), 5);
}

TEST(DummyItemGeneratorTest, GenerateZeroDoesNotCallSave)
{
    MockItemRepository repository;
    DummyItemGenerator generator(repository);

    EXPECT_CALL(repository, save(_)).Times(0);

    EXPECT_EQ(generator.generate(0), 0);
}

TEST(DummyItemGeneratorTest, GeneratedItemsHaveNonEmptyNames)
{
    MockItemRepository repository;
    DummyItemGenerator generator(repository);

    std::vector<Item> saved_items;
    EXPECT_CALL(repository, save(_))
        .Times(3)
        .WillRepeatedly(Invoke([&saved_items](const Item& item)
        {
            saved_items.push_back(item);
            return item;
        }));

    generator.generate(3);

    ASSERT_EQ(saved_items.size(), 3u);
    for (const Item& item : saved_items)
    {
        EXPECT_FALSE(item.name.empty());
    }
}

TEST(DummyItemGeneratorTest, SameSeedProducesSameNameSequence)
{
    MockItemRepository first_repository;
    MockItemRepository second_repository;

    std::vector<Item> first_names;
    std::vector<Item> second_names;

    EXPECT_CALL(first_repository, save(_))
        .Times(4)
        .WillRepeatedly(Invoke([&first_names](const Item& item)
        {
            first_names.push_back(item);
            return item;
        }));

    EXPECT_CALL(second_repository, save(_))
        .Times(4)
        .WillRepeatedly(Invoke([&second_names](const Item& item)
        {
            second_names.push_back(item);
            return item;
        }));

    DummyItemGenerator(first_repository, 42).generate(4);
    DummyItemGenerator(second_repository, 42).generate(4);

    ASSERT_EQ(first_names.size(), second_names.size());
    for (size_t i = 0; i < first_names.size(); i++)
    {
        EXPECT_EQ(first_names[i].name, second_names[i].name);
    }
}

int main(int argc, char** argv)
{
    InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
