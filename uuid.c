#include "uuid.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>  // For malloc/free
#include <rpc.h>  // For Windows UUID generation
#include <uuid/uuid.h>  // For POSIX UUID generation (Linux, macOS)

// Function to generate a UUID and return it as a byte array
uint8_t* generate_uuid() {
	uint8_t* uuid_bytes = (uint8_t*)malloc(16);  // Allocate 16 bytes for the UUID
	if (uuid_bytes == NULL) {
		return NULL;  // If memory allocation fails, return NULL
	}

#ifdef _WIN32
	// Windows-specific UUID generation using rpc.h
	UUID uuid;
	UuidCreate(&uuid);
	memcpy(uuid_bytes, &uuid.Data1, 4);        // Copy Data1: 4 bytes
	memcpy(uuid_bytes + 4, &uuid.Data2, 2);    // Copy Data2: 2 bytes
	memcpy(uuid_bytes + 6, &uuid.Data3, 2);    // Copy Data3: 2 bytes
	memcpy(uuid_bytes + 8, &uuid.Data4, 8);    // Copy Data4: 8 bytes
#else
	// POSIX (Linux/macOS) UUID generation using uuid/uuid.h
    uuid_t uuid;
    uuid_generate(uuid);  // Generate UUID
    memcpy(uuid_bytes, uuid, 16);  // Copy raw UUID bytes into the array
#endif

	return uuid_bytes;
}

// Function to convert a UUID (byte array) to a string in the format "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"
char* uuid_to_string(uint8_t* uuid) {
	if (uuid == NULL) {
		return NULL;  // If UUID is NULL, return NULL
	}

	// Allocate memory for the string representation of UUID
	char* uuid_str = (char*)malloc(37);  // UUID string length is always 36 characters + 1 for the null terminator
	if (uuid_str == NULL) {
		return NULL;  // If memory allocation fails, return NULL
	}

	// Format UUID as string
	snprintf(uuid_str, 37,
	         "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
	         uuid[0], uuid[1], uuid[2], uuid[3],
	         uuid[4], uuid[5], uuid[6], uuid[7],
	         uuid[8], uuid[9], uuid[10], uuid[11],
	         uuid[12], uuid[13], uuid[14], uuid[15]);

	return uuid_str;
}

// Function to convert a string (format: "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx") to UUID (byte array)
int string_to_uuid(const char* str, uint8_t* uuid) {
	if (str == NULL || uuid == NULL) {
		return -1;  // Invalid input
	}

	// Parse the string representation of UUID into a byte array
	int result = sscanf(str,
	                    "%2hhx%2hhx%2hhx%2hhx-%2hhx%2hhx-%2hhx%2hhx-%2hhx%2hhx-%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx",
	                    &uuid[0], &uuid[1], &uuid[2], &uuid[3],
	                    &uuid[4], &uuid[5], &uuid[6], &uuid[7],
	                    &uuid[8], &uuid[9], &uuid[10], &uuid[11],
	                    &uuid[12], &uuid[13], &uuid[14], &uuid[15]);

	return (result == 16) ? 0 : -1;  // Return 0 if successful, -1 if parsing fails
}

// Function to free the memory allocated for the UUID
void free_uuid(uint8_t* uuid) {
	free(uuid);  // Free the memory
}
