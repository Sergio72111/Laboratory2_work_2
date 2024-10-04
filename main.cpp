#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <cstdint>
#include <tuple> // Добавлено

using namespace std;

// Структура для хранения IP-адреса
struct IPAddress {
uint8_t n1, n2, n3, n4;

// Конструктор для удобного заполнения из строки
IPAddress(const string& ipString) {
stringstream ss(ipString);
char dot;
ss >> n1 >> dot >> n2 >> dot >> n3 >> dot >> n4;
}
};

// Сравнение IP-адресов в обратном лексикографическом порядке
auto compareIP = [](const IPAddress& lhs, const IPAddress& rhs) {
return make_tuple(lhs.n1, lhs.n2, lhs.n3, lhs.n4) > make_tuple(rhs.n1, rhs.n2, rhs.n3, rhs.n4);
};

int main() {
vector<IPAddress> ipAddresses;

// Чтение IP-адресов из файла ip_filter.tsv
ifstream file("ip_filter.tsv");
if (!file.is_open()) {
cerr << "Ошибка открытия файла ip_filter.tsv" << endl;
return 1;
}

string line;
while (getline(file, line)) {
// Разделение строки на части
stringstream ss(line);
string ipString;
getline(ss, ipString, '\t'); // Чтение IP-адресаф
ipAddresses.push_back(IPAddress(ipString));
}

file.close();

// Сортировка в обратном лексикографическом порядке
sort(ipAddresses.begin(), ipAddresses.end(), compareIP);

// Вывод всех IP-адресов
for (const auto& ip : ipAddresses) {
cout << static_cast<int>(ip.n1) << "."
<< static_cast<int>(ip.n2) << "."
<< static_cast<int>(ip.n3) << "."
<< static_cast<int>(ip.n4) << endl;
}

// Вывод IP-адресов с первым байтом 1
for (const auto& ip : ipAddresses) {
if (ip.n1 == 1) {
cout << static_cast<int>(ip.n1) << "."
<< static_cast<int>(ip.n2) << "."
<< static_cast<int>(ip.n3) << "."
<< static_cast<int>(ip.n4) << endl;
}
}
// Вывод IP-адресов с первым байтом 46 и вторым байтом 70
for (const auto& ip : ipAddresses) {
if (ip.n1 == 46 && ip.n2 == 70) {
cout << static_cast<int>(ip.n1) << "."
<< static_cast<int>(ip.n2) << "."
<< static_cast<int>(ip.n3) << "."
<< static_cast<int>(ip.n4) << endl;
}
}
// Вывод IP-адресов с байтом 46
for (const auto& ip : ipAddresses) {
if (ip.n1 == 46 || ip.n2 == 46 || ip.n3 == 46 || ip.n4 == 46) {
cout << static_cast<int>(ip.n1) << "."
<< static_cast<int>(ip.n2) << "."
<< static_cast<int>(ip.n3) << "."
<< static_cast<int>(ip.n4) << endl;
}
}

return 0;
}