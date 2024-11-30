#include "uuid.h"
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
	#include <rpc.h>  // For Windows UUID generation
#endif

// Function to generate a UUID and return it as a byte array
uint8_t* generate_uuid() {
    uint8_t* uuid_bytes = (uint8_t*)malloc(16);  // Allocate 16 bytes for UUID
    if (uuid_bytes) {
#ifdef _WIN32
        // Windows-specific UUID generation
        UUID uuid;
        UuidCreate(&uuid);
        memcpy(uuid_bytes, &uuid.Data1, 4);        // Data1: 4 bytes
        memcpy(uuid_bytes + 4, &uuid.Data2, 2);    // Data2: 2 bytes
        memcpy(uuid_bytes + 6, &uuid.Data3, 2);    // Data3: 2 bytes
        memcpy(uuid_bytes + 8, &uuid.Data4, 8);    // Data4: 8 bytes
#else
        // POSIX (Linux/macOS) UUID generation
        uuid_t uuid;
        uuid_generate(uuid);
        memcpy(uuid_bytes, uuid, 16);  // Copy raw UUID bytes into the array
#endif
    }
    return uuid_bytes;
}

// Function to convert UUID from byte array to string (format: "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx")
char* uuid_to_string(uint8_t* uuid) {
    char* uuid_str = (char*)malloc(37);  // 36 characters + null terminator
    if (uuid_str) {
        snprintf(uuid_str, 37, "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
                 uuid[0], uuid[1], uuid[2], uuid[3],
                 uuid[4], uuid[5], uuid[6], uuid[7],
                 uuid[8], uuid[9], uuid[10], uuid[11],
                 uuid[12], uuid[13], uuid[14], uuid[15]);
    }
    return uuid_str;
}

// Function to convert a string to UUID (expects format: "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx")
int string_to_uuid(const char* str, uint8_t* uuid) {
    return sscanf(str, "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
                   &uuid[0], &uuid[1], &uuid[2], &uuid[3],
                   &uuid[4], &uuid[5], &uuid[6], &uuid[7],
                   &uuid[8], &uuid[9], &uuid[10], &uuid[11],
                   &uuid[12], &uuid[13], &uuid[14], &uuid[15]);
}

// Function to free memory allocated for UUID
void free_uuid(uint8_t* uuid) {
    free(uuid);
}
