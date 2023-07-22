#ifndef TERMINAL_H
#define TERMINAL_H
#include "util.h"
#include "card.h"

typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    uint8_t transactionDate[100];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
    TERMINAL_OK,WRONG_DATE,
    EXPIRED_CARD ,INVALID_CARD,
    INVALID_AMOUNT,EXCEED_MAX_AMOUNT
    ,INVALID_MAX_AMOUNT
}EN_terminalError_t;

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);
EN_terminalError_t isCardExpired(ST_terminalData_t *termData);
EN_terminalError_t isValidCardPAN(ST_terminalData_t *termData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData);

#endif // !CARD_H