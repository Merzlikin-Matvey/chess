#include <iostream>
#include <nlohmann/json.hpp>

int main() {
    // Создаем объект JSON
    nlohmann::json json_data;

    // Добавляем данные в объект JSON
    json_data["name"] = "John";
    json_data["age"] = 25;
    json_data["city"] = "New York";

    // Выводим JSON в консоль
    std::cout << json_data.dump(4) << std::endl;

    return 0;
}
