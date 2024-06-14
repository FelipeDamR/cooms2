// =========================================================
// File: operator.h
// Author: Felipe de Jesus Damian Rodrigue
// Date: 14/06/2024
// Description: Esta clase es una clase abstracta que representa a un operador
// de telecomunicaciones. Esta define los metodos virtuales que deberan ser
//implementados en las clases derivadas.
// =========================================================
#ifndef OPERATOR_H
#define OPERATOR_H

#include <string>

enum OperatorType { VOX, INTERNET };

class Operator {
protected:
    int id;
    double talkingCharge;
    double messageCost;
    double networkCharge;
    int discountRate;
    int totalSpentTalkingTime;
    int totalMessageSent;
    double totalInternetUsage;
    OperatorType type;

public:
    Operator(int id, double talkingCharge, double messageCost, double networkCharge, int discountRate, OperatorType type)
        : id(id), talkingCharge(talkingCharge), messageCost(messageCost), networkCharge(networkCharge),
          discountRate(discountRate), totalSpentTalkingTime(0), totalMessageSent(0), totalInternetUsage(0), type(type) {}

    virtual ~Operator() {}

    virtual double calculateTalkingCost(int minutes, int age) const = 0;
    virtual double calculateMessageCost(int quantity, int thisOpId, int otherOpId) const = 0;
    virtual double calculateNetworkCost(double amount) const = 0;

    int getId() const { return id; }
    double getTalkingChage() const { return talkingCharge; } // Cambiado aquí
    double getMessageCost() const { return messageCost; }
    double getNetworkCharge() const { return networkCharge; }
    int getDiscountRate() const { return discountRate; }
    int getTotalSpentTalkingTime() const { return totalSpentTalkingTime; }
    int getTotalMessageSent() const { return totalMessageSent; }
    double getTotalInternetUsage() const { return totalInternetUsage; }
    OperatorType getType() const { return type; }

    void addTalkingTime(int minutes) {
        if (minutes > 0) {
            totalSpentTalkingTime += minutes;
        }
    }

    void addTotalMessageSent(int messages) {
        if (messages > 0) {
            totalMessageSent += messages;
        }
    }

    void addTotalInternetUsage(double amount) {
        if (amount > 0) {
            totalInternetUsage += amount;
        }
    }

    virtual std::string toString() const = 0;
};

#endif
