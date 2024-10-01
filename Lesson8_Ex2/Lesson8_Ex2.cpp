#include <iostream>
#include <string>

class PhoneNumber {
public:
    std::string number;

    PhoneNumber() {
        number = "";
    }

    PhoneNumber(std::string num) {
        number = num;
    }

    bool isValid() {
        return number.size() == 12 && number.substr(0, 2) == "+7";
    }
};

class Contact {
public:
    std::string name;
    PhoneNumber phoneNumber;

    Contact() {
        name = "";
        phoneNumber = PhoneNumber();
    }

    Contact(std::string contactName, std::string contactNumber) : phoneNumber(contactNumber) {
        name = contactName;
    }
};

class MobilePhone {
private:
    Contact contacts[100];
    int contactCount;

public:
    MobilePhone() {
        contactCount = 0;
    }

    void addContact(std::string name, std::string number) {
        PhoneNumber phoneNumber(number);
        if (phoneNumber.isValid()) {
            contacts[contactCount] = Contact(name, number);
            contactCount++;
            std::cout << "Контакт \"" << name << "\" добавлен с номером " << number << std::endl;
        }
        else {
            std::cout << "Неправильный формат номера. Используйте формат +7XXXXXXXXXX." << std::endl;
        }
    }

    void call(std::string identifier) {
        std::string number = getPhoneNumber(identifier);
        if (number != "") {
            std::cout << "CALL " << number << std::endl;
        }
        else {
            std::cout << "Контакт или номер не найден." << std::endl;
        }
    }

    void sendSms(std::string identifier, std::string message) {
        std::string number = getPhoneNumber(identifier);
        if (number != "") {
            std::cout << "SMS на " << number << ": " << message << std::endl;
        }
        else {
            std::cout << "Контакт или номер не найден." << std::endl;
        }
    }

private:
    std::string getPhoneNumber(std::string identifier) {
        for (int i = 0; i < contactCount; i++) {
            if (contacts[i].name == identifier) {
                return contacts[i].phoneNumber.number;
            }
        }
        PhoneNumber phone(identifier);
        return phone.isValid() ? identifier : "";
    }
};

int main() {
    setlocale(LC_CTYPE, "rus");
    MobilePhone phone;
    std::string command;

    while (true) {
        std::cout << "Введите команду (add, call, sms, exit): ";
        std::cin >> command;

        if (command == "add") {
            std::string name, number;
            std::cout << "Введите имя контакта: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Введите номер телефона (формат +7XXXXXXXXXX): ";
            std::cin >> number;
            phone.addContact(name, number);
        }
        else if (command == "call") {
            std::string identifier;
            std::cout << "Введите имя контакта или номер телефона: ";
            std::cin.ignore();
            std::getline(std::cin, identifier);
            phone.call(identifier);
        }
        else if (command == "sms") {
            std::string identifier, message;
            std::cout << "Введите имя контакта или номер телефона: ";
            std::cin.ignore();
            std::getline(std::cin, identifier);
            std::cout << "Введите сообщение: ";
            std::getline(std::cin, message);
            phone.sendSms(identifier, message);
        }
        else if (command == "exit") {
            std::cout << "Выход из программы." << std::endl;
            break;
        }
        else {
            std::cout << "Неизвестная команда. Попробуйте снова." << std::endl;
        }
    }

    return 0;
}
