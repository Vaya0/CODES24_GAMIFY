#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <fstream>
#include <string>
#pragma comment(lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#define PORT 8080
#define SERVER_IP L("127.0.0.1") 
#include <Windows.h>
#include <conio.h> 
char map[25][80] = {
    {'W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W'},
    {'W','S','S','-','-','D','D','D','D','D','-','-','-','-','W','-','-','-','-','-','-','-','W','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','W','-','-','-','-','-','-','-','W','-','-','-','-','D','D','D','D','D','-','-','S','S','W'},
    {'W','S','S','-','-','D','D','D','D','D','-','-','-','-','W','-','-','-','-','-','-','-','W','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','W','-','-','-','-','-','-','-','W','-','-','-','-','D','D','D','D','D','-','-','S','S','W'},
    {'W','S','S','-','-','-','-','-','-','-','-','-','-','-','W','-','-','-','-','-','-','-','W','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','W','-','-','-','-','-','-','-','W','-','-','-','-','-','-','-','-','-','-','-','S','S','W'},
    {'W','L','L','-','-','-','-','-','-','-','-','-','-','-','W','-','-','-','-','-','-','-','W','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','W','-','-','-','-','-','-','-','W','-','-','-','-','-','-','-','-','-','-','-','L','L','W'},
    {'W','L','L','-','-','-','-','-','-','-','-','-','-','-','W','-','-','-','-','-','-','-','W','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','W','-','-','-','-','-','-','-','W','-','-','-','-','-','-','-','-','-','-','-','L','L','W'},
    {'W','L','L','-','-','-','-','-','-','-','-','-','-','-','W','-','-','-','-','-','-','-','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','-','-','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','-','-','-','-','-','-','-','W','-','-','-','-','-','-','-','-','-','-','-','L','L','W'},
    {'W','L','L','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','L','L','W'},
    {'W','L','L','L','L','L','L','L','L','L','L','L','L','L','W','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','W','L','L','L','L','L','L','L','L','L','L','L','L','L','W'},
    {'W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W'},
    {'W','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','W'},
    {'W','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','W'},
    {'W','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','W'},
    {'W','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','W'},
    {'W','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','W'},
    {'W','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','W'},
    {'W','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','W'},
    {'W','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','W'},
    {'W','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','W'},
    {'W','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','W'},
    {'W','W','W','W','W','W','W','W','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','W'},
    {'W','-','-','-','-','-','-','W','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','W'},
    {'W','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','W'},
    {'W','-','-','-','-','-','-','W','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','W'},
    {'W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W'},
};
void displayMap()
{
    for (size_t i = 0; i < 25; i++)
    {
        for (size_t j = 0; j < 80; j++)
        {
            if (map[i][j] == '-') std::cout << ' ';
            else
            std::cout << map[i][j];
        }
        std::cout << std::endl;
    }
}
enum class Room
{
    Office1,
    Office2,
    Archive,
    ChatRoom,
    Toilet
};

struct position
{
    unsigned int x;
    unsigned int y;
};

class Player
{
    char name[64];
    position pos;
    char direction;
    Room currentRoom;
public:
    Player();
    ~Player();
    void move(const char m);
    Room getRoom() const;
    void updateRoom();
    char getDirection();
    char lookingAt();
};
Player::Player()
{
    name[0] = '1';
    currentRoom = Room::ChatRoom;
    pos.x = 14;
    pos.y = 40;
    if (::map[pos.x][pos.y] == '@')
    {
        pos.x++;
    }
    ::map[pos.x][pos.y] = '@';
    direction = 's';

}

Player::~Player()
{

}

char Player::getDirection()
{
    return direction;
}

char Player::lookingAt()
{
    switch (direction)
    {
    case 'w':
    {
        return map[pos.x][pos.y - 1];
        break;
    }
    case 'a':
    {
        return map[pos.x - 1][pos.y];
        break;
    }
    case 's':
    {
        return map[pos.x][pos.y + 1];
        break;
    }
    case 'd':
    {
        return map[pos.x + 1][pos.y];
        break;
    }
    }
}

void Player::move(const char m)
{
    if (m != 'w' && m != 'a' && m != 's' && m != 'd') return;
    this->direction = m;
    switch (m)
    {
    case 'a':
    {
        if (map[pos.x][pos.y - 1] == '-')
        {
            ::map[pos.x][pos.y] = '-';
            pos.y--;
        }
        break;
    }
    case 'w':
    {
        if (map[pos.x - 1][pos.y] == '-')
        {
            ::map[pos.x][pos.y] = '-';
            pos.x--;
        }
        break;
    }
    case 'd':
    {
        if (map[pos.x][pos.y + 1] == '-')
        {
            ::map[pos.x][pos.y] = '-';
            pos.y++;
        }
        break;
    }
    case 's':
    {
        if (map[pos.x + 1][pos.y] == '-')
        {
            ::map[pos.x][pos.y] = '-';
            pos.x++;
        }
        break;
    }
    }
    ::map[pos.x][pos.y] = '@';
}

Room Player::getRoom() const
{
    if (pos.x > 1111 && pos.x < 1111 && pos.y > 1111 && pos.y < 1111)
    {
        return Room::Office1;
    }
    if (pos.x > 1111 && pos.x < 1111 && pos.y > 1111 && pos.y < 1111)
    {
        return Room::Office2;
    }
    if (pos.x > 1111 && pos.x < 1111 && pos.y > 1111 && pos.y < 1111)
    {
        return Room::Archive;
    }
    if (pos.x > 1111 && pos.x < 1111 && pos.y > 1111 && pos.y < 1111)
    {
        return Room::ChatRoom;
    }
    if (pos.x > 1111 && pos.x < 1111 && pos.y > 1111 && pos.y < 1111)
    {
        return Room::Toilet;
    }
}

void Player::updateRoom()
{
    currentRoom = getRoom();
}


class Server
{
    WSADATA wsaData;
    SOCKET serverSocket;
    SOCKET clientSocket;
public:
    //Server();
    ~Server();
    void open();
    void sendData(char m);//оverloard za movementData,PlayerData,Files etc;
    char recieveMData();// analogichni overloadove
    bool dataRecieved();
};

void Server::open()
{
    //WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed.\n";
        return;
    }

    //SOCKET 
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed.\n";
        WSACleanup();
        return;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, reinterpret_cast<SOCKADDR*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed with error.\n";
        closesocket(serverSocket);
        WSACleanup();
        return;
    }

    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed with error.\n";
        closesocket(serverSocket);
        WSACleanup();
        return;
    }

    std::cout << "Server listening on port " << PORT << std::endl;

    //SOCKET
    clientSocket = accept(serverSocket, NULL, NULL);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Accept failed with error.\n";
        closesocket(serverSocket);
        WSACleanup();
        return;
    }
}

Server::~Server()
{
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
}
void Server::sendData(char m)
{
    send(clientSocket, &m, sizeof(m), 0);
}
char Server::recieveMData()
{
    int bytesRecieved;
    char m;
    bytesRecieved = recv(clientSocket, &m, sizeof(m), 0);
    if (bytesRecieved == SOCKET_ERROR)
    {
        std::cout << "Error on Recieving";
    }
    else
    {
        return m;
    }
}
bool Server::dataRecieved()
{
    char buff[10];
    int bytesReceived = recv(serverSocket, buff, sizeof(buff), 0);
    if (bytesReceived > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}


class Client
{
    WSADATA wsaData;
    SOCKET clientSocket;
public:
    void open();
    ~Client();
    void sendData(char m);
    char recieveMData();
    bool dataRecieved();
};
void Client::open()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed.\n";
        return;
    }

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed.\n";
        WSACleanup();
        return;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    wchar_t ipAddress[] = L"127.0.0.1";
    if (InetPton(serverAddr.sin_family, ipAddress, &serverAddr.sin_addr) != 1) {

        std::cerr << "Invalid address.\n";
        closesocket(clientSocket);
        WSACleanup();
        return;
    }
    if (connect(clientSocket, reinterpret_cast<SOCKADDR*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Connection failed.\n";
        closesocket(clientSocket);
        WSACleanup();
        return;
    }

    std::cout << "Connected to server.\n";
}
Client::~Client()
{
    closesocket(clientSocket);
    WSACleanup();
}
void Client::sendData(char m)
{
    send(clientSocket, &m, sizeof(m), 0);
}
char Client::recieveMData()
{
    int bytesReceived;
    char m;
    bytesReceived = recv(clientSocket, &m, sizeof(m), 0);
    if (bytesReceived == SOCKET_ERROR) {
        std::cerr << "Receive failed.\n";
    }
    else
    {
        return m;
    }
}
bool Client::dataRecieved()
{
    char buff[10];
    int bytesReceived = recv(clientSocket, buff, sizeof(buff), 0);
    if (bytesReceived > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}


int main()
{
    std::cout << "Press 1 to host \nPress 2 to connect";
    int select;
    std::cin >> select;
    Server server;
    Client client;
    if (select == 1)
    {
        server.open();
    }
    if (select == 2)
    {
        client.open();
    }
    Player player1;
    Player player2;
    char key;

    while (true)
    {
        if (_kbhit())
        {
            key = _getch();
            player1.move(key);
            if (key == 27)
                break;
            if (select == 1)
            {
                server.sendData(key);
            }
            if (select == 2)
            {
                client.sendData(key);
            }
            system("cls");
            displayMap();
        }
        if (select == 1)
        {
            if (server.dataRecieved())
            {
                char rec = server.recieveMData();
                player2.move(rec);
                system("cls");
                displayMap();
            }
        }
        if (select == 2)
        {
            if (server.dataRecieved())
            {
                char rec = client.recieveMData();
                player2.move(rec);
                system("cls");
                displayMap();
            }
        }
    }
}
