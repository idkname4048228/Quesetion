#ifndef TOOL_H
#define TOOL_H

#include <string>

class Tool
{
public:
    Tool();
    Tool(int, const std::string, int, float);

    void setRecode(int);
    int getRecode() const;

    void setName(std::string);
    std::string getName() const;

    void setQuqntity(int);
    int getQuantity() const;

    void setPrice(float);
    float getPrice() const;

private:
    int recode;
    char name[30];
    int quantity;
    float price;
};
#endif