#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "product.h"

// Класс для отчетов о продажах
class SalesReport {
private:
    std::map<std::string, std::map<std::string, int>> salesByCategoryAndPeriod;
    std::map<std::string, std::map<std::string, double>> profitByCategoryAndPeriod;

public:
    // Функция для добавления данных о продажах из Product
    void addProductSales(const Product& product) {
        salesByCategoryAndPeriod[product.getCategory()]["день"] += product.getDailySales();
        salesByCategoryAndPeriod[product.getCategory()]["неделю"] += product.getWeeklySales();
        salesByCategoryAndPeriod[product.getCategory()]["месяц"] += product.getMonthlySales();

        profitByCategoryAndPeriod[product.getCategory()]["день"] += product.getDailySales() * product.getProfit();
        profitByCategoryAndPeriod[product.getCategory()]["неделю"] += product.getWeeklySales() * product.getProfit();
        profitByCategoryAndPeriod[product.getCategory()]["месяц"] += product.getMonthlySales() * product.getProfit();
    }

    // Функция для вывода отчета о продажах по категориям и периодам
    void printSalesReport() const {
        for (const auto& category : salesByCategoryAndPeriod) {
            std::cout << "Категория: " << category.first << std::endl;
            for (const auto& period : category.second) {
                std::cout << "За " << period.first << ": " << std::endl;
                std::cout << "Продано товаров: " << period.second << std::endl;
                std::cout << "Прибыль: " << profitByCategoryAndPeriod.at(category.first).at(period.first) << std::endl;
            }
            std::cout << "-----------------------------------" << std::endl;
        }
    }

    // Функция для сброса данных о продажах
    void clearSalesData() {
        salesByCategoryAndPeriod.clear();
        profitByCategoryAndPeriod.clear();
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    InventoryManagement inventory;
    SalesReport report;
    std::string filename;

    std::cout << "Введите имя файла с данными о товарах (или оставьте пустым для создания нового): ";
    std::getline(std::cin, filename);

    if (!filename.empty()) {
        std::ifstream testFile(filename);
        if (!testFile) {
            std::cout << "Файл не найден. Будет создан новый файл.\n";
        }
        else {
            inventory.loadFromFile(filename);
        }
    }
    else {
        filename = "new_inventory.txt"; // Имя нового файла по умолчанию
        std::cout << "Создан новый файл: " << filename << std::endl;
    }

    int choice = 0;
    do {
        std::cout << "Выберите действие:\n";
        std::cout << "1. Добавить товар\n";
        std::cout << "2. Удалить товар\n";
        std::cout << "3. Изменить цену закупки товара\n";
        std::cout << "4. Изменить цену продажи товара\n";
        std::cout << "5. Изменить количество товара\n";
        std::cout << "6. Изменить данные о продажах товара по периодам\n";
        std::cout << "7. Сохранить инвентарь в файл\n";
        std::cout << "8. Загрузить инвентарь из файла\n";
        std::cout << "9. Вывести отчет о продажах\n";
        std::cout << "10. Печать списка товаров\n";
        std::cout << "0. Выход\n";
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            int quant;
            std::string prdName, catg;
            double pri, sPri;
            std::cout << "Введите имя, цену покупки, цену продажи, количество на складе и категорию товара:\n";
            std::cin.ignore(); // Игнорируем символ новой строки оставшийся в потоке
            std::getline(std::cin, prdName);
            std::cin >> pri >> sPri >> quant;
            std::cin.ignore(); // Игнорируем символ новой строки оставшийся в потоке
            std::getline(std::cin, catg);
            if (pri < 0 || sPri < 0 || quant < 0) {
                std::cout << "Ошибка. Введено отрицательное число!\n";
            } else {
                inventory.addProduct({ prdName, pri, sPri, quant, catg, 0, 0, 0 });
            }
            break;
        }
        case 2: {
            std::string prod_del;
            std::cout << "Введите название удаляемого товара:\n";
            std::cin.ignore();
            std::getline(std::cin, prod_del);
            inventory.removeProduct(prod_del);
            break;
        }
        case 3: {
            std::string nameForNewPrice;
            double changedprice;
            std::cout << "Введите имя товара и новую цену закупки через пробел:\n";
            std::cin.ignore();
            std::getline(std::cin, nameForNewPrice);
            std::cin >> changedprice;
            if (changedprice < 0) {
                std::cout << "Ошибка. Введено отрицательное число!\n";
            } else {
                inventory.changeProductPrice(nameForNewPrice, changedprice);
            }
            break;
        }
        case 4: {
            std::string nameForNewSalePrice;
            double changedsaleprice;
            std::cout << "Введите имя товара и новую цену продажи через пробел:\n";
            std::cin.ignore();
            std::getline(std::cin, nameForNewSalePrice);
            std::cin >> changedsaleprice;
            if (changedsaleprice < 0) {
                std::cout << "Ошибка. Введено отрицательное число!\n";
            } else {
                inventory.changeProductSalePrice(nameForNewSalePrice, changedsaleprice);
            }
            break;
        }
        case 5: {
            std::string nameForNewQuant;
            int changedquant;
            std::cout << "Введите имя товара и новое количество через пробел:\n";
            std::cin.ignore();
            std::getline(std::cin, nameForNewQuant);
            std::cin >> changedquant;
            if (changedquant < 0) {
                std::cout << "Ошибка. Введено отрицательное число!\n";
            } else {
                inventory.changeProductQuantity(nameForNewQuant, changedquant);
            }
            break;
        }
        case 6: {
            std::string nameForNewSales;
            int sds, sws, sms;
            std::cout << "Введите имя товара и продажи за день, неделю и месяц через пробел:\n";
            std::cin.ignore();
            std::getline(std::cin, nameForNewSales);
            std::cin >> sds;
            std::cin >> sws;
            std::cin >> sms;
            if (sds < 0 || sws < 0 || sms < 0) {
                std::cout << "Ошибка. Введено отрицательное число!\n";
            } else {
                inventory.changeProductDailySales(nameForNewSales, sds);
                inventory.changeProductWeeklySales(nameForNewSales, sws);
                inventory.changeProductMonthlySales(nameForNewSales, sms);
            }
            break;
        }
        case 7: {
            inventory.saveToFile(filename);
            break;
        }
        case 8: {
            inventory.loadFromFile(filename);
            break;
        }
        case 9: {
            report.clearSalesData();
            for (const auto& product : inventory.products) {
                report.addProductSales(product);
            }
            report.printSalesReport();
            report.clearSalesData();
            break;
        }
        case 10: {
            inventory.printAllProducts();
            break;
        }
        case 0: {
            std::cout << "Выход из программы...\n";
            break;
        }
        default: {
            std::cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
        }
        }
    } while (choice != 0);

    return 0;
}
