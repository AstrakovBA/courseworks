#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "product.h"

// ����� ��� ������� � ��������
class SalesReport {
private:
    std::map<std::string, std::map<std::string, int>> salesByCategoryAndPeriod;
    std::map<std::string, std::map<std::string, double>> profitByCategoryAndPeriod;

public:
    // ������� ��� ���������� ������ � �������� �� Product
    void addProductSales(const Product& product) {
        salesByCategoryAndPeriod[product.getCategory()]["����"] += product.getDailySales();
        salesByCategoryAndPeriod[product.getCategory()]["������"] += product.getWeeklySales();
        salesByCategoryAndPeriod[product.getCategory()]["�����"] += product.getMonthlySales();

        profitByCategoryAndPeriod[product.getCategory()]["����"] += product.getDailySales() * product.getProfit();
        profitByCategoryAndPeriod[product.getCategory()]["������"] += product.getWeeklySales() * product.getProfit();
        profitByCategoryAndPeriod[product.getCategory()]["�����"] += product.getMonthlySales() * product.getProfit();
    }

    // ������� ��� ������ ������ � �������� �� ���������� � ��������
    void printSalesReport() const {
        for (const auto& category : salesByCategoryAndPeriod) {
            std::cout << "���������: " << category.first << std::endl;
            for (const auto& period : category.second) {
                std::cout << "�� " << period.first << ": " << std::endl;
                std::cout << "������� �������: " << period.second << std::endl;
                std::cout << "�������: " << profitByCategoryAndPeriod.at(category.first).at(period.first) << std::endl;
            }
            std::cout << "-----------------------------------" << std::endl;
        }
    }

    // ������� ��� ������ ������ � ��������
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

    std::cout << "������� ��� ����� � ������� � ������� (��� �������� ������ ��� �������� ������): ";
    std::getline(std::cin, filename);

    if (!filename.empty()) {
        std::ifstream testFile(filename);
        if (!testFile) {
            std::cout << "���� �� ������. ����� ������ ����� ����.\n";
        }
        else {
            inventory.loadFromFile(filename);
        }
    }
    else {
        filename = "new_inventory.txt"; // ��� ������ ����� �� ���������
        std::cout << "������ ����� ����: " << filename << std::endl;
    }

    int choice = 0;
    do {
        std::cout << "�������� ��������:\n";
        std::cout << "1. �������� �����\n";
        std::cout << "2. ������� �����\n";
        std::cout << "3. �������� ���� ������� ������\n";
        std::cout << "4. �������� ���� ������� ������\n";
        std::cout << "5. �������� ���������� ������\n";
        std::cout << "6. �������� ������ � �������� ������ �� ��������\n";
        std::cout << "7. ��������� ��������� � ����\n";
        std::cout << "8. ��������� ��������� �� �����\n";
        std::cout << "9. ������� ����� � ��������\n";
        std::cout << "10. ������ ������ �������\n";
        std::cout << "0. �����\n";
        std::cout << "��� �����: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            int quant;
            std::string prdName, catg;
            double pri, sPri;
            std::cout << "������� ���, ���� �������, ���� �������, ���������� �� ������ � ��������� ������:\n";
            std::cin.ignore(); // ���������� ������ ����� ������ ���������� � ������
            std::getline(std::cin, prdName);
            std::cin >> pri >> sPri >> quant;
            std::cin.ignore(); // ���������� ������ ����� ������ ���������� � ������
            std::getline(std::cin, catg);
            if (pri < 0 || sPri < 0 || quant < 0) {
                std::cout << "������. ������� ������������� �����!\n";
            } else {
                inventory.addProduct({ prdName, pri, sPri, quant, catg, 0, 0, 0 });
            }
            break;
        }
        case 2: {
            std::string prod_del;
            std::cout << "������� �������� ���������� ������:\n";
            std::cin.ignore();
            std::getline(std::cin, prod_del);
            inventory.removeProduct(prod_del);
            break;
        }
        case 3: {
            std::string nameForNewPrice;
            double changedprice;
            std::cout << "������� ��� ������ � ����� ���� ������� ����� ������:\n";
            std::cin.ignore();
            std::getline(std::cin, nameForNewPrice);
            std::cin >> changedprice;
            if (changedprice < 0) {
                std::cout << "������. ������� ������������� �����!\n";
            } else {
                inventory.changeProductPrice(nameForNewPrice, changedprice);
            }
            break;
        }
        case 4: {
            std::string nameForNewSalePrice;
            double changedsaleprice;
            std::cout << "������� ��� ������ � ����� ���� ������� ����� ������:\n";
            std::cin.ignore();
            std::getline(std::cin, nameForNewSalePrice);
            std::cin >> changedsaleprice;
            if (changedsaleprice < 0) {
                std::cout << "������. ������� ������������� �����!\n";
            } else {
                inventory.changeProductSalePrice(nameForNewSalePrice, changedsaleprice);
            }
            break;
        }
        case 5: {
            std::string nameForNewQuant;
            int changedquant;
            std::cout << "������� ��� ������ � ����� ���������� ����� ������:\n";
            std::cin.ignore();
            std::getline(std::cin, nameForNewQuant);
            std::cin >> changedquant;
            if (changedquant < 0) {
                std::cout << "������. ������� ������������� �����!\n";
            } else {
                inventory.changeProductQuantity(nameForNewQuant, changedquant);
            }
            break;
        }
        case 6: {
            std::string nameForNewSales;
            int sds, sws, sms;
            std::cout << "������� ��� ������ � ������� �� ����, ������ � ����� ����� ������:\n";
            std::cin.ignore();
            std::getline(std::cin, nameForNewSales);
            std::cin >> sds;
            std::cin >> sws;
            std::cin >> sms;
            if (sds < 0 || sws < 0 || sms < 0) {
                std::cout << "������. ������� ������������� �����!\n";
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
            std::cout << "����� �� ���������...\n";
            break;
        }
        default: {
            std::cout << "�������� �����. ����������, ���������� �����.\n";
        }
        }
    } while (choice != 0);

    return 0;
}
