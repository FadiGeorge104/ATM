#include "../include/terminal.h"
#include <stdio.h>

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData) {
  time_t t = time(NULL);
  struct tm *tm = localtime(&t);
  // DD/MM/yyyy
  sprintf((char *)termData->transactionDate, "%02d/%02d/%04d", tm->tm_mday,
          tm->tm_mon + 1, tm->tm_year + 1900);
  printf("\nTime: %s\n",termData->transactionDate);
  uint8_t len = strlen((char *)termData->transactionDate);
  if (len == 0 || len < 10) {
    return WRONG_DATE;
  }
  
  return TERMINAL_OK;
}

EN_terminalError_t isCardExpired(ST_terminalData_t *termData) {
  time_t t = time(NULL);
  struct tm *tm = localtime(&t);

  if ((termData->transactionDate[3] + termData->transactionDate[4]) <
      (tm->tm_year - 100)) {
    return EXPIRED_CARD;
  }
  return TERMINAL_OK;
}
EN_terminalError_t isValidCardPAN(ST_terminalData_t *termData);

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData) {
  printf("\nplease enter your transaction amount: \n");
  scanf("%f", &termData->transAmount);
  if (termData->transAmount <= 0)
    return INVALID_AMOUNT;
  return TERMINAL_OK;
}
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData) {
  // Set max amount
  termData->maxTransAmount = 2000;
  if (termData->maxTransAmount <= 0)
    return INVALID_MAX_AMOUNT;
  return TERMINAL_OK;
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData) {
  if (termData->maxTransAmount < termData->transAmount)
    {
      printf("Error ,max trans amount= %0.02f\n",termData->maxTransAmount);
    return EXCEED_MAX_AMOUNT;
    }
  else
    return TERMINAL_OK;
}
