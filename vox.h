// =========================================================
// File: vox_operator.h
// Author: Felipe de Jesus Damian Rodrigue
// Date: 12/06/2024
// Description: Esta clase representa a un operador de voz, esta se encarga de 
// calcular y manejar costos que esten asociados con las llamadas de voz, el uso
// de datos para la red y el envío de mensajes.
// =========================================================
#ifndef VOX_H
#define VOX_H

#include "operator.h"
#include <string>
#include <sstream>

class VoxOperator : public Operator {
public:
    VoxOperator(int id, double talkingCharge, double messageCost, double networkCharge, int discountRate, OperatorType type)
        : Operator(id, talkingCharge, messageCost, networkCharge, discountRate, type) {}

    double calculateTalkingCost(int minutes, int age) const override {
        if (minutes < 0 || age < 0) return 0;
        double cost = talkingCharge * minutes;
        if (age < 18) {
            cost *= (1 - discountRate / 100.0);
        }
        return cost;
    }

    double calculateMessageCost(int quantity, int thisOpId, int otherOpId) const override {
        if (quantity < 0) return 0;
        return (thisOpId == otherOpId) ? messageCost * quantity * (1 - discountRate / 100.0) : messageCost * quantity;
    }

    double calculateNetworkCost(double amount) const override {
        if (amount < 0) return 0;
        return networkCharge * amount;
    }

    std::string toString() const override {
        std::stringstream ss;
        ss << "Operator " << id << ": " << totalSpentTalkingTime << " " << totalMessageSent << " " << totalInternetUsage;
        return ss.str();
    }
};

#endif
