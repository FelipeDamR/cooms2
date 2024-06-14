// =========================================================
// File: bill.h
// Author: Felipe de Jesus Damian Rodrigue
// Date: 14/06/2024
// Description: La clase Bill sirve para la gestión de las facturas de los clientes. 
// Esta tiene un registro de la deuda acutal, el dinero gastado por los clientes y el limite de credito.
// =========================================================
#ifndef BILL_H
#define BILL_H

class Bill {
private:
    double limitAmount;
    double currentDebt;
    double totalMoneySpent;

public:
    Bill() : limitAmount(0.0), currentDebt(0.0), totalMoneySpent(0.0) {}

    Bill(double amount) {
        if (amount < 0) amount = 0.0;
        limitAmount = amount;
        currentDebt = 0.0;
        totalMoneySpent = 0.0;
    }

    Bill(const Bill& other) {
        limitAmount = other.limitAmount;
        currentDebt = other.currentDebt;
        totalMoneySpent = other.totalMoneySpent;
    }

    double getLimitAmount() const { return limitAmount; }
    double getCurrentDebt() const { return currentDebt; }
    double getTotalMoneySpent() const { return totalMoneySpent; }

    bool check(double amount) const { return (amount <= limitAmount - currentDebt); }

    void add(double amount) {
        if (amount > 0) {
            currentDebt += amount;
        }
    }

    void pay(double amount) {
        if (amount > 0) {
            // Calculate the actual amount to be paid
            double actualPaid = (amount > currentDebt) ? currentDebt : amount;
            currentDebt -= actualPaid;
            totalMoneySpent += actualPaid;
        }
    }

    void changeTheLimit(double newLimit) {
        if (newLimit >= 0) limitAmount = newLimit;
    }
};

#endif 
