#pragma once

#include "repository/IItemRepository.h"

class DummyItemGenerator
{
    public:
        explicit DummyItemGenerator(IItemRepository& repository, unsigned int seed = 1);

        int generate(int count);

    private:
        IItemRepository& repository;
        unsigned int seed;
};
