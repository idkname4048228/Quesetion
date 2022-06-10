#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include "Tool.h"

using namespace std;

void initial(fstream &file);
void selectChoice();
void listAllData(fstream &file);
void updataData(fstream &file);
void insertData(fstream &file);
void deleteData(fstream &file);
void print(Tool &data);
void printTitle();

enum class Choise
{
    LIST = 1,
    UPDATE,
    INSERT,
    DELETE,
    QUIT
};

int main()
{
    char answer;
    cout << "Initial ?(y/n)'\t";
    cin >> answer;
    fstream inOutFile;
    if (answer == 'y')
    {
        fstream inOutFile{"shop_list.dat", ios::trunc | ios::in | ios::out | ios::binary};
    }
    else
    {
        fstream inOutFile{"shop_list.dat", ios::in | ios::out | ios::binary};
    }

    initial(inOutFile);
    listAllData(inOutFile);
    inOutFile.close();
}

void selectChoice()
{
    cout << "Enter a choice:" << endl
         << "1  List all tools." << endl
         << "2  UPdata recode." << endl
         << "3  Insert recode." << endl
         << "4  Delete recode." << endl
         << "5  End program." << endl
         << "? ";
    int choice{0};
    cin >> choice;
}

void initial(fstream &file)
{
    for (int i = 0; i < 100; i++)
    {
        Tool data{i, "", 0, 0};
        print(data);
        file.seekp(i * sizeof(Tool));
        file.write(
            reinterpret_cast<const char *>(&data), sizeof(Tool));
    }
    int place{0};
    cout << "Enter the part number (0 - 99, -1 to the end input): ";
    cin >> place;
    while (place != -1)
    {
        int quantity{0};
        float price{0};
        string name;

        cout << "Enter the tool name: ";
        getchar();
        getline(cin, name);
        cout << "Enter quantity and price: ";
        cin >> quantity >> price;

        Tool data{place, name, quantity, price};

        file.seekp(place * sizeof(Tool));
        file.write(
            reinterpret_cast<const char *>(&data), sizeof(Tool));

        cout << "Enter the part number (0 - 99, -1 to the end input): ";
        cin >> place;
    }
}

void listAllData(fstream &file)
{
    printTitle();
    for (int i = 0; i < 100; i++)
    {
        Tool data;
        file.seekg(i * sizeof(Tool));
        file.read(
            reinterpret_cast<char *>(&data), sizeof(Tool));
        print(data);
    }
}

void printTitle()
{
    cout << left << setw(11) << "Recode#" << setw(30) << "Tool Name" << setw(13) << "Quantity" << setprecision(2)
         << showpoint << "Cost" << endl;
}

void print(Tool &data)
{

    cout << left << setw(11) << data.getRecode() << setw(30) << data.getName() << setw(13) << data.getQuantity() << setprecision(3)
         << showpoint << data.getPrice() << endl;
}

void updataData(fstream &file)
{
    int place{0}, quantity{0};
    float price{0};
    cout << "Select one tool to update :";
    cin >> place;
    cout << "Input quantity and price :";
    cin >> quantity >> price;

    Tool dataInFile;
    file.seekg(place * sizeof(Tool));
    file.read(
        reinterpret_cast<char *>(&dataInFile), sizeof(Tool));

    Tool updateData{place, dataInFile.getName(), quantity, price};
    file.seekp(place * sizeof(Tool));
    file.write(
        reinterpret_cast<const char *>(&updateData), sizeof(Tool));
}

void insertData(fstream &file)
{
    int place{0}, quantity{0};
    float price{0};
    string name;
    cout << "Input recode, name, quantity and price of insert tool :";
    cin >> place >> name >> quantity >> price;

    Tool insertData{place, name, quantity, price};
    file.seekp(place * sizeof(Tool));
    file.write(
        reinterpret_cast<const char *>(&insertData), sizeof(Tool));
}

void deleteData(fstream &file)
{
    int place{0};
    cout << "Input place to delete";
    cin >> place;
    Tool data{place, "", 0, 0};
    file.seekp(place * sizeof(Tool));
    file.write(
        reinterpret_cast<const char *>(&data), sizeof(Tool));
}
