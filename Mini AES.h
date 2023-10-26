#ifndef _MINI_AES_H_
#define _MINI_AES_H_

//inclusion des settings
#include"settings.h"

#endif

/// @brief 
typedef unsigned char byte;

/// @brief 
typedef struct Message_s
{
    /// @brief 
    unsigned int size;

    /// @brief 
    byte *tab;
} Message;

/// @brief 
/// @param message 
void subBytes(Message *message);

/// @brief 
/// @param message 
void shiftRows(Message *message);

/// @brief 
/// @param message 
void mixColumns(Message *message);

/// @brief 
/// @param message 
/// @param roundKey 
void addRoundKey(Message *message, Message *roundKey);

/// @brief 
/// @param message 
/// @param roundKey 
/// @param round 
void encrypt(Message *message, Message *roundKey, int round);