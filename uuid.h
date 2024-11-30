#ifndef UUID_GENERATOR_H
#define UUID_GENERATOR_H

#include <stdint.h>  // For uint8_t
#include <stdlib.h>  // For malloc/free

#ifdef __cplusplus
extern "C" {
#endif

// Function to generate a UUID and return it as a byte array
uint8_t* generate_uuid();

// Function to convert a UUID from byte array to string (format: "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx")
char* uuid_to_string(uint8_t* uuid);

// Function to convert a string to UUID (expects string format "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx")
int string_to_uuid(const char* str, uint8_t* uuid);

// Function to free the memory allocated for UUID
void free_uuid(uint8_t* uuid);

#ifdef __cplusplus
}
#endif

#endif // UUID_GENERATOR_H
