#ifndef DIRECCIONESIP_H
#define DIRECCIONESIP_H

class IPAddresses {
    struct addrinfo* addresses;
public:
    IPAddresses(const char* domain, const char* port, struct addrinfo* hints);

    struct addrinfo* firstAddress() const;

    ~IPAddresses();
};

#endif
