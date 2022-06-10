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
    : recode(recode), name(name), quantity(quantity), price(price)
{
}

void Tool::setRecode(int recode)
{
    this->recode = recode;
}
int Tool::getRecode()
{
    return recode;
}

void Tool::setName(std::string name)
{
    this->name = name;
}
std::string Tool::getName()
{
    return name;
}

void Tool::setQuqntity(int quantity)
{
    this->quantity = quantity;
}
int Tool::getQuantity()
{
    return quantity;
}

void Tool::setPrice(float price)
{
    this->price = price;
}
float Tool::getPrice()
{
    return price;
}