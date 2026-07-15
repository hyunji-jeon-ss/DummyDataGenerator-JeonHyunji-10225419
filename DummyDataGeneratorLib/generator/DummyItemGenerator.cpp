#include "generator/DummyItemGenerator.h"

#include <random>
#include <string>

namespace
{
    const std::string PREFIXES[] = { "실리콘 웨이퍼", "GaN 에피택셜", "SiC 파워기판", "포토레지스트", "산화막 웨이퍼" };
    constexpr size_t PREFIX_COUNT = sizeof(PREFIXES) / sizeof(PREFIXES[0]);
}

DummyItemGenerator::DummyItemGenerator(IItemRepository& repository, unsigned int seed)
    : repository(repository)
    , seed(seed)
{
}

int DummyItemGenerator::generate(int count)
{
    std::mt19937 random_engine(seed);
    std::uniform_int_distribution<size_t> prefix_distribution(0, PREFIX_COUNT - 1);

    int generated_count = 0;
    for (int i = 0; i < count; i++)
    {
        const std::string name = PREFIXES[prefix_distribution(random_engine)] + "-" + std::to_string(i + 1);
        repository.save(Item{ 0, name });
        generated_count++;
    }
    return generated_count;
}
