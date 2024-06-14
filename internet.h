// =========================================================
// File: internet_operator.h
// Author: Felipe de Jesus Damian Rodriguez
// Date: 14/06/2024
// Description: Esta es importante para gestionar los servicios de internet
// asegura que los calculos se hagan bien y que los totales sean actualizados correctamente
// Basicamente permite el manejo correcto y preciso de los servicios de 
// telecomunicaciones del internet
// =========================================================
#ifndef INTERNET_H
#define INTERNET_H

#include "operator.h"
#include <string>
#include <sstream>

class InternetOperator : public Operator {
public:
    InternetOperator(int id, double talkingCharge, double messageCost, double networkCharge, int discountRate, OperatorType type)
        : Operator(id, talkingCharge, messageCost, networkCharge, discountRate, type) {}

    double calculateTalkingCost(int minutes, int age) const override {
        if (minutes < 0) return 0;
        return (age < 18) ? talkingCharge * minutes * (1 - discountRate / 100.0) : talkingCharge * minutes;
    }

    double calculateMessageCost(int quantity, int thisOpId, int otherOpId) const override {
        if (quantity < 0) return 0;
        return (thisOpId == otherOpId) ? messageCost * quantity * (1 - discountRate / 100.0) : messageCost * quantity;
    }

    double calculateNetworkCost(double amount) const override {
        if (amount < 0) return 0;
        return networkCharge * amount * (1 - discountRate / 100.0);
    }

    std::string toString() const override {
        std::stringstream ss;
        ss << "Operator " << id << ": " << totalSpentTalkingTime << " " << totalMessageSent << " " << totalInternetUsage;
        return ss.str();
    }
};

#endif
