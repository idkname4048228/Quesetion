#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include "Tool.h"

using namespace std;

enum class Choice
{
    LIST = 1,
    UPDATE,
    INSERT,
    DELETE,
    QUIT
};

void initial(fstream &file);
Choice selectChoice();
void listAllData(fstream &file);
void updataData(fstream &file);
void insertData(fstream &file);
void deleteData(fstream &file);
void print(const Tool &data);
void printTitle();

int main()
{
    char answer;
    cout << "Should the file be initialized (Y or N)\t";
    cin >> answer;
    fstream inOutFile;
    if (answer == 'y' || answer == 'Y')
    {
        inOutFile.open("shop_list.dat", ios::trunc | ios::in | ios::out | ios::binary);
        initial(inOutFile);
    }
    else
    {
        inOutFile.open("shop_list.dat", ios::in | ios::out | ios::binary);
    }

    if (!inOutFile)
    {
        cerr << "File could not be opened." << endl;
        exit(EXIT_FAILURE);
    }

    Choice choice;

    while ((choice = selectChoice()) != Choice::QUIT)
    {
        switch (choice)
        {
        case Choice::LIST:
            listAllData(inOutFile);
            break;
        case Choice::UPDATE:
            updataData(inOutFile);
            break;
        case Choice::INSERT:
            insertData(inOutFile);
            break;
        case Choice::DELETE:
            deleteData(inOutFile);
            break;
        default:
            cerr << "Incorrect choice" << endl;
            break;
        }

        inOutFile.clear();
    }
}

Choice selectChoice()
{
    cout << "Enter a choice:" << endl
         << "1  List all tools." << endl
         << "2  UPdata record." << endl
         << "3  Insert record." << endl
         << "4  Delete record." << endl
         << "5  End program." << endl
         << "? ";
    int choice{0};
    cin >> choice;
    return static_cast<Choice>(choice);
}

void initial(fstream &file)
{
    for (int i = 0; i < 100; i++)
    {
        Tool data{i, "", 0, 0};
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

        cout
            << "Enter the part number (0 - 99, -1 to the end input): ";
        cin >> place;
    }
}

void listAllData(fstream &file)
{
    printTitle();
    file.seekg(0);

    while (!file.eof())
    {
        Tool data;
        file.read(
            reinterpret_cast<char *>(&data), sizeof(Tool));
        if (data.getName() != "")
        {
            print(data);
        }
    }
}

void printTitle()
{
    cout << left << setw(11) << "Record#" << setw(30) << "Tool Name" << setw(13) << "Quantity" << setprecision(2)
         << showpoint << "Cost" << endl;
}

void print(const Tool &data)
{

    cout << left << setw(11) << data.getRecode() << setw(30) << data.getName() << setw(13) << data.getQuantity() << fixed << setprecision(2)
         << showpoint << data.getPrice() << endl;
}

void updataData(fstream &file)
{
    listAllData(file);//下面要 clear
    int place{0}, quantity{0};
    float price{0};
    cout << "Select one tool to update :";
    cin >> place;
    cout << "Input quantity and price :";
    cin >> quantity >> price;

    Tool dataInFile;
    file.clear();//這裡
    file.seekg(place * sizeof(Tool));
    file.read(
        reinterpret_cast<char *>(&dataInFile), sizeof(Tool));
    print(dataInFile);

    string name = dataInFile.getName();
    Tool updateData{place, name, quantity, price};
    file.seekp(place * sizeof(Tool));
    file.write(
        reinterpret_cast<const char *>(&updateData), sizeof(Tool));
    print(updateData);
}

void insertData(fstream &file)
{
    int place{0}, quantity{0};
    float price{0};
    string name;
    cout << "Enter the part number (0 - 99, -1 to the end input): ";
    cin >> place;
    cout << "Enter the tool name: ";
    getchar();
    getline(cin, name);
    cout << "Enter quantity and price: ";
    cin >> quantity >> price;

    Tool insertData{place, name, quantity, price};
    file.seekp(place * sizeof(Tool));
    file.write(
        reinterpret_cast<const char *>(&insertData), sizeof(Tool));
}

void deleteData(fstream &file)
{
    int place{0};
    cout << "Input prat to delete";
    cin >> place;
    Tool data{place, "", 0, 0};
    file.seekp(place * sizeof(Tool));
    file.write(
        reinterpret_cast<const char *>(&data), sizeof(Tool));
}
