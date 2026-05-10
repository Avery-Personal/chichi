#if (defined(CHICHI_IMPLEMENTATION) && !defined(CHICHI_NET_IMPLEMENTATION)) || (defined(CC_IMPLEMENTATION) && !defined(CHICHI_NET_IMPLEMENTATION))
    #define CHICHI_NET_IMPLEMENTATION
#endif

#ifndef CHICHI_NET_IMPLEMENTATION
#define CHICHI_NET_IMPLEMENTATION

    #ifdef CHICHI_BASE_H
        #define CC_NET_HAS_BASE 1
    #else
        #define CC_NET_HAS_BASE 0
    #endif

    #if !CC_NET_HAS_BASE
        #ifdef __cplusplus
            #define CC_EXTERN_C_BEGIN extern "C" {
            #define CC_EXTERN_C_END }
        #else
            #define CC_EXTERN_C_BEGIN
            #define CC_EXTERN_C_END
        #endif

        #if defined(_WIN32)
            #if defined(CC_NET_BUILD_DLL)
                #define CC_NET_API __declspec(dllexport)
            #elif defined(CC_NET_USE_DLL)
                #define CC_NET_API __declspec(dllimport)
            #else
                #define CC_NET_API
            #endif
        #else
            #define CC_NET_API
        #endif

        #ifndef CC_TRUE
            #define CC_TRUE 1
        #endif

        #ifndef CC_FALSE
            #define CC_FALSE 0
        #endif

        typedef unsigned char CCBool;
        typedef unsigned int CCu32;
    #else
        #define CC_NET_API CC_API
    #endif

    CC_EXTERN_C_BEGIN

    #ifndef _WIN32
        #include <unistd.h>
        #include <arpa/inet.h>
        #include <sys/socket.h>
    #else
        #include <winsock2.h>
    #endif

    #ifndef CC_NET_MAX_PACKET
        #define CC_NET_MAX_PACKET 2048
    #endif

    typedef struct {
        int Sock;
    } CCNetSocket;

    typedef struct {
        struct sockaddr_in Address;
        
        socklen_t Length;
    } CCNetPeer;

    typedef struct {
        CCNetSocket Socket;

        CCBool IsServer;
    } CCNetHost;

    CC_NET_API int CCNetInitialize(void);
    CC_NET_API void CCNetCleanup(void);

    CC_NET_API int CCNetSocketCreate(void);

    CC_NET_API CCBool CCNetHostCreate(CCNetHost *Host, const char *IP, int Port, CCBool IsServer);

    #ifdef CHICHI_NET_IMPLEMENTATION
        #include <stdio.h>
        #include <string.h>

        int CCNetInitialize(void) {
            #ifdef _WIN32
                WSADATA WSAData;

                return WSAStartup(MAKEWORD(2, 2), &WSAData);
            #else
                return 0;
            #endif
        }
        
        void CCNetCleanup(void) {
            #ifdef _WIN32
                WSACleanup();
            #endif
        }

        int CCNetSocketCreate(void) {
            int Socket = socket(AF_INET, SOCK_DGRAM, 0);
            if (Socket < 0)
                perror("Socket");

            return Socket;
        }

        CCBool CCNetHostCreate(CCNetHost *Host, const char *IP, int Port, CCBool IsServer) {
            Host -> Socket.Sock = CCNetSocketCreate();
            Host -> IsServer = IsServer;

            if (Host -> Socket.Sock < 0)
                return CC_FALSE;

            struct sockaddr_in Address;

            memset(&Address, 0, sizeof(Address));

            Address.sin_family = AF_INET;
            Address.sin_port = htons(Port);

            if (IsServer) {
                Address.sin_addr.s_addr = INADDR_ANY;

                if (bind(Host -> Socket.Sock, (struct sockaddr *) &Address, sizeof(Address)) < 0) {
                    perror("Bind");

                    return CC_FALSE;
                }
            } else {
                Address.sin_addr.s_addr = inet_addr(IP);
            }

            return CC_TRUE;
        }
    #endif

    CC_EXTERN_C_END

#endif
