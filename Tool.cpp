#include "Tool.h"
#include <string>

Tool::Tool()
{
    setRecode(0);
    setName("");
    setQuqntity(0);
    setPrice(0);
}
Tool::Tool(int recode, const std::string name, int quantity, float price)
    : recode(recode), quantity(quantity), price(price)
{
    setName(name);
}

void Tool::setRecode(int recode)
{
    this->recode = recode;
}
int Tool::getRecode() const
{
    return recode;
}

void Tool::setName(std::string name)
{
    int i;
    for (i = 0; i != name.length() and i != 29; i++)
    {
        this->name[i] = name[i];
    }
    this->name[i] = '\0';
}

std::string Tool::getName() const
{
    std::string name;
    for (int i = 0; this->name[i] != '\0'; i++)
    {
        name += this->name[i];
    }
    return name;
}

void Tool::setQuqntity(int quantity)
{
    this->quantity = quantity;
}
int Tool::getQuantity() const
{
    return quantity;
}

void Tool::setPrice(float price)
{
    this->price = price;
}
float Tool::getPrice() const
{
    return price;
}