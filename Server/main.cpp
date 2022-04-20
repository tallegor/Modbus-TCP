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

    SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);

    bind(sListen, (SOCKADDR*)&addr, sizeof(addr)); // привязка адреса сокета

    listen(sListen, SOMAXCONN); // прослушивание порта в ожидании соединения со стороны клиента

    SOCKET newConnection; // сокет для удержания соединения с клиентом
    newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

    // если клиент не смог подключиться к серверу
    if (newConnection == 0) {
        cout << "Ошибка подключения к серверу." << endl;
    } else {
        cout << "Клиент соединился." << endl;
        char msg[256] = "Привет. Это моя первая сетевая программа.";
        send(newConnection, msg, sizeof(msg), NULL);
    }

    system("pause");
    return 0;
}
