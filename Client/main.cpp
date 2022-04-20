#include <iostream>
#pragma comment(lib, "ws2_32.lib") // для доступа к функциям
#include <winsock2.h> // библиотека для работы с сетью

using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1); // запрашиваемая версия библиотеки WinSock; также необходима для загрузки библиотеки
    // загрузка библиотеки
    if (WSAStartup(DLLVersion, &wsaData) != 0) {
        cout << "Ошибка загрузки библиотеки." << endl;
        exit(1);
    }

    // проверка информации об адресе сокета
    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1111);
    addr.sin_family = AF_INET;

    SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL); // сокет для соединения с сервером
    if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) { // присоединение к серверу
        cout << "Ошибка подключения к серверу." << endl;
        return 1;
    }
    cout << "Подключение к серверу прошло успешно!" << endl;
    char msg[256];
    // принимаем и записываем отправленные сервером данные
    recv(Connection, msg, sizeof(msg), NULL);
    cout << msg << endl;

    system("pause");
    return 0;
}
