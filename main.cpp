// =========================================================
// File: main.cpp
// Author: Felipe de Jesus Damian Rodriguez
// Date: 14/06/2024
// Description: Archivo main
// =========================================================


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include "customer.h"
#include "operator.h"
#include "vox.h"
#include "internet.h"
#include "bill.h"

using namespace std;

void processInputFile(const string &inputFileName, const string &outputFileName) {
    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);

    if (!inputFile) {
        cerr << "Error opening input file." << endl;
        return;
    }

    int C, O, N;
    inputFile >> C >> O >> N;

    vector<Customer*> customers;
    vector<Operator*> operators;

    for (int i = 0; i < N; ++i) {
        int operation;
        inputFile >> operation;

        switch (operation) {
            case 1: { // Creando un nuevo cliente
                string name;
                int age, operatorId;
                double limitAmount;
                inputFile >> name >> age >> operatorId >> limitAmount;
                customers.push_back(new Customer(customers.size(), name, age, operators[operatorId], limitAmount));
                break;
            }
            case 2: { // Creando un nuevo operador
                int opType;
                double talkingCharge, messageCost, networkCharge;
                int discountRate;
                inputFile >> opType >> talkingCharge >> messageCost >> networkCharge >> discountRate;
                if (opType == 1) {
                    operators.push_back(new VoxOperator(operators.size(), talkingCharge, messageCost, networkCharge, discountRate, VOX));
                } else if (opType == 2) {
                    operators.push_back(new InternetOperator(operators.size(), talkingCharge, messageCost, networkCharge, discountRate, INTERNET));
                }
                break;
            }
            case 3: { // Un cliente puede hablar con otro cliente
                int idCustomer1, idCustomer2, time;
                inputFile >> idCustomer1 >> idCustomer2 >> time;
                customers[idCustomer1]->talk(time, *customers[idCustomer2]);
                break;
            }
            case 4: { // Un cliente envía un mensaje a otro cliente
                int idCustomer1, idCustomer2, quantity;
                inputFile >> idCustomer1 >> idCustomer2 >> quantity;
                customers[idCustomer1]->message(quantity, *customers[idCustomer2]);
                break;
            }
            case 5: { // Un cliente se conecta a Internet
                int idCustomer;
                double amount;
                inputFile >> idCustomer >> amount;
                customers[idCustomer]->connection(amount);
                break;
            }
            case 6: { // Un cliente paga sus facturas
                int idCustomer;
                double amount;
                inputFile >> idCustomer >> amount;
                customers[idCustomer]->pay(amount);
                break;
            }
            case 7: { // Un cliente cambia de operador
                int idCustomer, idOperator;
                inputFile >> idCustomer >> idOperator;
                customers[idCustomer]->setOperator(operators[idOperator]);
                break;
            }
            case 8: { // Un cliente cambia su límite de factura
                int idCustomer;
                double amount;
                inputFile >> idCustomer >> amount;
                customers[idCustomer]->getBill()->changeTheLimit(amount);
                break;
            }
        }
    }

    // Generar la salida
    for (const auto& op : operators) {
        outputFile << op->toString() << endl;
    }

    for (const auto& customer : customers) {
        outputFile << customer->toString() << endl;
    }

    // Encontrar el cliente que más habla
    int maxTalkingId = 0;
    for (size_t i = 1; i < customers.size(); ++i) {
        if (customers[i]->getTotalSpentTalkingTime() > customers[maxTalkingId]->getTotalSpentTalkingTime()) {
            maxTalkingId = i;
        }
    }
    outputFile << customers[maxTalkingId]->getName() << ": " << customers[maxTalkingId]->getTotalSpentTalkingTime() << endl;

    // Encontrar el cliente que más mensajes envía
    int maxMessageId = 0;
    for (size_t i = 1; i < customers.size(); ++i) {
        if (customers[i]->getTotalMessageSent() > customers[maxMessageId]->getTotalMessageSent()) {
            maxMessageId = i;
        }
    }
    outputFile << customers[maxMessageId]->getName() << ": " << customers[maxMessageId]->getTotalMessageSent() << endl;

    // Encontrar el cliente que más se conecta a Internet
    int maxInternetId = 0;
    for (size_t i = 1; i < customers.size(); ++i) {
        if (customers[i]->getTotalInternetUsage() > customers[maxInternetId]->getTotalInternetUsage()) {
            maxInternetId = i;
        }
    }
    outputFile << customers[maxInternetId]->getName() << ": " << customers[maxInternetId]->getTotalInternetUsage() << endl;

    // Liberar memoria
    for (auto& customer : customers) {
        delete customer;
    }
    for (auto& op : operators) {
        delete op;
    }

    inputFile.close();
    outputFile.close();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }

    string inputFileName = argv[1];
    string outputFileName = argv[2];

    processInputFile(inputFileName, outputFileName);

    return 0;
}
