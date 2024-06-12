#include "Client.h"

void Client::free() {
	delete[] accounts;
	delete[] messages;
}

void Client::copyFrom(const Client& other) {

}