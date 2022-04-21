#include <iostream>
#pragma comment(lib, "ws2_32.lib") // ��� ������� � ��������
#include <winsock2.h> // ���������� ��� ������ � �����
#include "../Packet.h"

using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    WSADATA wsaData; // �������������� DLL; ������� �����
    WSAStartup(MAKEWORD(2, 2), &wsaData); // ���������� ������ � �������

    int nSize;
    // ��������� ������, ������������ ��������
    char menu;
    bool running = true;
    char data[252] = {0};
    while (running)
    {
        char szBuffer[260] = { 0 };
        SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        sockaddr_in sockAddr;
        memset(&sockAddr, 0, sizeof(sockAddr)); // ��������� ����� ������
        sockAddr.sin_family = PF_INET;
        sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        sockAddr.sin_port = htons(1234);
        connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
        system("cls");
        cout << "[1] Ping" << endl
             << "[2] Greeting" << endl
             << "[3] Shutdown" << endl
             << "[4] Exit"<< endl
             << "������� ����� �������: ";
        cin >> menu;
        switch (menu)
        {
            case '1':
            {
                char fc = 65;
                Packet pack(fc, data);
                send(sock, pack.Serialize(), 260, NULL);
                system("cls");
                cout << "��������� �����:\n" << endl;
                pack.Print();
                system("pause");
                system("cls");
                recv(sock, szBuffer, 260, NULL);
                pack.Deserialize(szBuffer);
                char str[252]={0};
                strcpy(str, pack.Data);
                cout << "��������� �� �������: ";
                if (strlen(str))
                    cout << str;
                else
                    cout << "������ �� ��������.\n";
                system("pause");
                break;
            }
            case '2':
            {
                char fc = 66;
                Packet pack(fc, data);
                send(sock, pack.Serialize(), 260, NULL);
                system("cls");
                cout << "��������� �����:\n" << endl;
                pack.Print();
                system("pause");
                system("cls");
                recv(sock, szBuffer, 260, NULL);
                pack.Deserialize(szBuffer);
                cout << pack.Data <<endl;
                char name[30];
                cin >> name;
                strcpy(pack.Data, name);
                send(sock, pack.Serialize(), 260, NULL);
                recv(sock, szBuffer, 260, NULL);
                pack.Deserialize(szBuffer);
                cout << pack.Data << endl;
                system("pause");
                break;
            }
            case '3':
            {
                char fc = 67;
                Packet pack(fc, data);
                send(sock, pack.Serialize(), 260, NULL);
                system("cls");
                cout << "��������� �����:\n" << endl;
                pack.Print();
                system("pause");
                system("cls");
                recv(sock, szBuffer, 260, NULL);
                pack.Deserialize(szBuffer);
                cout << pack.Data;
                break;
            }
            case'4':
                running = false;
                closesocket(sock);
                break;
        }
    }

    WSACleanup(); // ��������� �����; ���������� ������������� DLL

    system("pause");
    return 0;
}
