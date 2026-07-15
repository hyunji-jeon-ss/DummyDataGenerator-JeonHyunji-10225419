#include "generator/DummyItemGenerator.h"
#include "repository/JsonItemRepository.h"

#define NOMINMAX
#include <windows.h>

#include <iostream>
#include <stdexcept>
#include <string>

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    JsonItemRepository repository("items.json");

    std::cout << "생성할 더미 데이터 개수 > ";
    std::string count_text;
    std::getline(std::cin, count_text);

    int count = 0;
    try
    {
        count = std::stoi(count_text);
    }
    catch (const std::exception&)
    {
        std::cout << "숫자를 입력해주세요." << std::endl;
        return 1;
    }

    DummyItemGenerator generator(repository);
    const int generated_count = generator.generate(count);

    std::cout << generated_count << "건 생성 완료." << std::endl;
    std::cout << "현재 저장된 전체 항목 수: " << repository.findAll().size() << std::endl;

    return 0;
}
