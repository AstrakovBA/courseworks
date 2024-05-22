#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

class Product {
private:
    std::string name; // Название товара
    double price; // Цена закупки
    double salePrice; // Цена продажи
    int dailySales; // Продано за день
    int weeklySales; // Продано за неделю
    int monthlySales; // Продано за месяц
    int quantity; // Количество товара на складе
    std::string category; // Категория товара

public:
    // Конструктор
    Product(std::string name, double price, double salePrice, int quantity, std::string category, int dailySales, int weeklySales, int monthlySales)
        : name(name), price(price), salePrice(salePrice), quantity(quantity), category(category), dailySales(dailySales), weeklySales(weeklySales), monthlySales(monthlySales) {}

    // Функции доступа
    std::string getName() const { return name; }
    double getPrice() const { return price; }
    double getSalePrice() const { return salePrice; }
    double getProfit() const { return salePrice - price; } // Вычисляемая прибыль
    int getQuantity() const { return quantity; }
    std::string getCategory() const { return category; }
    int getDailySales() const { return dailySales; }
    int getWeeklySales() const { return weeklySales; }
    int getMonthlySales() const { return monthlySales; }

    // Функции модификации
    void setPrice(double newPrice) { price = newPrice; }
    void setSalePrice(double newSalePrice) { salePrice = newSalePrice; }
    void setQuantity(int newQuantity) { quantity = newQuantity; }
    void setDailySales(int newDailySales) { dailySales = newDailySales; }
    void setWeeklySales(int newWeeklySales) { weeklySales = newWeeklySales; }
    void setMonthlySales(int newMonthlySales) { monthlySales = newMonthlySales; }
};

// Класс для работы с товарами
class InventoryManagement {
public:
    std::vector<Product> products; // Список товаров
    // Функция вывода всех товаров
    void printAllProducts() {
    if (products.empty()) {
        std::cout << "Инвентарь пуст." << std::endl;
    } else {
        std::cout << "Список всех товаров:" << std::endl;
        for (const auto& product : products) {
            std::cout << "Название: " << product.getName()
                      << ", Категория: " << product.getCategory()
                      << ", Цена закупки: " << product.getPrice()
                      << "руб, Цена продажи:" << product.getSalePrice()
                      << "руб, Количество: " << product.getQuantity()
                      << ", Продано за день: " << product.getDailySales()
                      << ", Продано за неделю: " << product.getWeeklySales()
                      << ", Продано за месяц: " << product.getMonthlySales() << std::endl;
        }
    }
}

    // Функция для добавления товара
    void addProduct(const Product& product) {
        products.push_back(product);
    }

    // Функция для удаления товара
    void removeProduct(const std::string& productName) {
        products.erase(
            std::remove_if(
                products.begin(),
                products.end(),
                [&productName](const Product& product) {
                    return product.getName() == productName;
                }
            ),
            products.end()
        );
    }

    // Функция для изменения цены закупки товара
    void changeProductPrice(const std::string& productName, double newPrice) {
        for (auto& product : products) {
            if (product.getName() == productName) {
                product.setPrice(newPrice);
                break;
            }
        }
    }

    // Функция для изменения цены продажи товара
    void changeProductSalePrice(const std::string& productName, double newSalePrice) {
        for (auto& product : products) {
            if (product.getName() == productName) {
                product.setSalePrice(newSalePrice);
                break;
            }
        }
    }

    // Функция для изменения количества товара
    void changeProductQuantity(const std::string& productName, int newQuantity) {
        for (auto& product : products) {
            if (product.getName() == productName) {
                product.setQuantity(newQuantity);
                break;
            }
        }
    }

    // Функция для изменения количества продаж за день
    void changeProductDailySales(const std::string& productName, int newDailySales) {
        for (auto& product : products) {
            if (product.getName() == productName) {
                product.setDailySales(newDailySales);
                break;
            }
        }
    }

    // Функция для изменения количества продаж за неделю
    void changeProductWeeklySales(const std::string& productName, int newWeeklySales) {
        for (auto& product : products) {
            if (product.getName() == productName) {
                product.setWeeklySales(newWeeklySales);
                break;
            }
        }
    }

    // Функция для изменения количества продаж за месяц
    void changeProductMonthlySales(const std::string& productName, int newMonthlySales) {
        for (auto& product : products) {
            if (product.getName() == productName) {
                product.setMonthlySales(newMonthlySales);
                break;
            }
        }
    }

    // Метод для сохранения инвентаря в файл
    void saveToFile(const std::string& filename) {
        std::ofstream fileOut(filename);
        if (fileOut.is_open()) {
            for (const auto& product : products) {
                fileOut << product.getName() << ","
                        << product.getPrice() << ","
                        << product.getSalePrice() << ","
                        << product.getQuantity() << ","
                        << product.getCategory() << ","
                        << product.getDailySales() << ","
                        << product.getWeeklySales() << ","
                        << product.getMonthlySales() << std::endl;
            }
            fileOut.close();
        } else {
            std::cerr << "Не удалось открыть файл для записи." << std::endl;
        }
    }

    // Метод для загрузки инвентаря из файла
    void loadFromFile(const std::string& filename) {
        std::ifstream fileIn(filename);
        if (fileIn.is_open()) {
            std::string line;
            while (std::getline(fileIn, line)) {
                std::stringstream ss(line);
                std::string name, category;
                double price, salePrice;
                int quantity, dailySales, weeklySales, monthlySales;

                std::getline(ss, name, ',');
                ss >> price;
                ss.ignore(); // Пропускаем запятую
                ss >> salePrice;
                ss.ignore();
                ss >> quantity;
                ss.ignore();
                std::getline(ss, category, ',');
                ss >> dailySales;
                ss.ignore();
                ss >> weeklySales;
                ss.ignore();
                ss >> monthlySales;

                products.push_back(Product(name, price, salePrice, quantity, category, dailySales, weeklySales, monthlySales));
            }
            fileIn.close();
        } else {
            std::cerr << "Не удалось открыть файл для чтения." << std::endl;
        }
    }
};

#endif