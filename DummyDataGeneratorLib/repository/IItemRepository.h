#pragma once

#include "model/Item.h"

#include <vector>

class IItemRepository
{
    public:
        virtual ~IItemRepository() = default;

        virtual Item save(const Item& item) = 0;
        virtual std::vector<Item> findAll() = 0;
};
