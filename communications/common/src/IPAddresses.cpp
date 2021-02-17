#include "../include/IPAddresses.h"
#include <netdb.h>
#include <string>
#include "../include/Exception.h"

IPAddresses::IPAddresses(const char* domain,
                         const char* port,
                         struct addrinfo* hints) {
    int getAddrInfoCode;
    addresses = nullptr;

    getAddrInfoCode = getaddrinfo(domain, port, hints, &addresses);

    if (getAddrInfoCode != 0) {
    	throw Exception("Domain/Port invalid: " + std::string(gai_strerror(getAddrInfoCode)));
    }
}

struct addrinfo* IPAddresses::firstAddress() const {
    return addresses;
}

IPAddresses::~IPAddresses() {
    freeaddrinfo(addresses);
}
