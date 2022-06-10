#ifndef TOOL_H
#define TOOL_H

#include <string>

class Tool
{
public:
    Tool();
    Tool(int, const std::string, int, float);

    void setRecode(int);
    int getRecode();

    void setName(std::string);
    std::string getName();

    void setQuqntity(int);
    int getQuantity();

    void setPrice(float);
    float getPrice();

private:
    int recode;
    std::string name;
    int quantity;
    float price;
};
#endif