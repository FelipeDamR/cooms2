// =========================================================
// File: customer.h
// Author: Felipe de Jesus Damian Rodrigue
// Date: 14/06/2024
// Description: Esta clase reprenta a un cliente. Gestiona basicamenta la información
// el ID, la edad, nombre, el operador asignado y la facturacion.
// =========================================================
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <sstream>
#include <iomanip>
#include "bill.h"
#include "operator.h"

class Customer {
private:
    int id;
    std::string name;
    int age;
    Operator* op;
    Bill* bill;
    int totalSpentTalkingTime;
    int totalMessageSent;
    double totalInternetUsage;

public:
    Customer(int id, std::string name, int age, Operator* op, double limitAmount);
    Customer(const Customer& other);
    ~Customer();

    int getId() const;
    std::string getName() const;
    int getAge() const;
    int getTotalSpentTalkingTime() const;
    int getTotalMessageSent() const;
    double getTotalInternetUsage() const;
    Operator* getOperator() const;
    Bill* getBill() const;

    void setOperator(Operator* newOp);

    std::string toString() const;

    void talk(int minutes, Customer& other);
    void message(int quantity, const Customer& other);
    void connection(double amount);
    void pay(double amount);
};

Customer::Customer(int idr, std::string nombre, int edad, Operator* operador, double limite)
    : id(idr), name(nombre), age(edad), op(operador), bill(new Bill(limite)),
      totalSpentTalkingTime(0), totalMessageSent(0), totalInternetUsage(0.0) {}

Customer::Customer(const Customer& otro)
    : id(otro.id), name(otro.name), age(otro.age), op(otro.op),
      bill(new Bill(*otro.bill)), totalSpentTalkingTime(otro.totalSpentTalkingTime),
      totalMessageSent(otro.totalMessageSent), totalInternetUsage(otro.totalInternetUsage) {}

Customer::~Customer() {
    delete bill;
}

int Customer::getId() const { return id; }
std::string Customer::getName() const { return name; }
int Customer::getAge() const { return age; }
int Customer::getTotalSpentTalkingTime() const { return totalSpentTalkingTime; }
int Customer::getTotalMessageSent() const { return totalMessageSent; }
double Customer::getTotalInternetUsage() const { return totalInternetUsage; }
Operator* Customer::getOperator() const { return op; }
Bill* Customer::getBill() const { return bill; }

void Customer::setOperator(Operator* newOp) { op = newOp; }

std::string Customer::toString() const {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2);
    ss << "Customer " << id << ": " << bill->getTotalMoneySpent() << " " << bill->getCurrentDebt();
    return ss.str();
}

void Customer::talk(int cantidad, Customer& otro) {
    if (cantidad > 0 && otro.id != id) {
        double cost = op->calculateTalkingCost(cantidad, age);
        if (bill->check(cost)) {
            bill->add(cost);
            op->addTalkingTime(cantidad);
            totalSpentTalkingTime += cantidad;
            if (op != otro.op) {
                otro.op->addTalkingTime(cantidad);
            }
        }
    }
}

void Customer::message(int cantidad, const Customer& otro) {
    if (cantidad > 0 && otro.id != id) {
        double cost = op->calculateMessageCost(cantidad, op->getId(), otro.op->getId());
        if (bill->check(cost)) {
            bill->add(cost);
            op->addTotalMessageSent(cantidad);
            totalMessageSent += cantidad;
        }
    }
}

void Customer::connection(double cantidad) {
    if (cantidad > 0) {
        double cost = op->calculateNetworkCost(cantidad);
        if (bill->check(cost)) {
            bill->add(cost);
            op->addTotalInternetUsage(cantidad);
            totalInternetUsage += cantidad;
        }
    }
}

// Método pay
void Customer::pay(double amount) {
    bill->pay(amount);
}

#endif
