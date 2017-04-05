#include <thread>
#include "Client.h"

void Draw();

int main()
{
	auto client = std::unique_ptr<Client>(new Client);
	client->ClientHandle();
	return 0;
}

void Draw()
{

}