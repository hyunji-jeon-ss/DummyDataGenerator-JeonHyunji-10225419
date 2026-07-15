#pragma once

#include "repository/IItemRepository.h"

#include <string>

class JsonItemRepository : public IItemRepository
{
    public:
        explicit JsonItemRepository(const std::string& file_path);

        Item save(const Item& item) override;
        std::vector<Item> findAll() override;

    private:
        std::string file_path;
        int next_id = 1;
};
