#include "repository/JsonItemRepository.h"

#include <nlohmann/json.hpp>

#include <fstream>

using nlohmann::json;

namespace
{
    Item fromJson(const json& element)
    {
        return Item{ element.at("id").get<int>(), element.at("name").get<std::string>() };
    }

    json toJson(const Item& item)
    {
        return json{ {"id", item.id}, {"name", item.name} };
    }
}

JsonItemRepository::JsonItemRepository(const std::string& file_path)
    : file_path(file_path)
{
    for (const Item& item : findAll())
    {
        if (item.id >= next_id) next_id = item.id + 1;
    }
}

Item JsonItemRepository::save(const Item& item)
{
    std::vector<Item> items = findAll();

    Item saved_item = item;
    saved_item.id = next_id;
    next_id++;
    items.push_back(saved_item);

    json root = json::array();
    for (const Item& stored_item : items)
    {
        root.push_back(toJson(stored_item));
    }

    std::ofstream output(file_path);
    output << root.dump(4);

    return saved_item;
}

std::vector<Item> JsonItemRepository::findAll()
{
    std::ifstream input(file_path);
    if (!input.is_open()) return {};

    input.seekg(0, std::ios::end);
    if (input.tellg() == 0) return {};
    input.seekg(0, std::ios::beg);

    json root;
    input >> root;

    std::vector<Item> items;
    items.reserve(root.size());
    for (const json& element : root)
    {
        items.push_back(fromJson(element));
    }
    return items;
}
