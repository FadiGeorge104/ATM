#include "../include/server.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
ST_accountsDB_t accounts[255] = 
{
    {.balance = 1000.0, .primaryAccountNumber = "asdasdasdasdasdasd12" , .active = 1},
    {.balance = 2000.0, .primaryAccountNumber = "asdasdasdasdasdasd13" , .active = 0},
    {.balance = 3000, .primaryAccountNumber = "asdasdasdasdasdasd14" , .active = 1}
};

EN_transState_t recieveTransactionData(ST_transaction_t *transData) {
  //Check trans Time
  time_t t = time(NULL);
  struct tm *tm = localtime(&t);
  char* currentTime = malloc(100);
  sprintf(currentTime, "%02d/%02d/%04d", tm->tm_mday,
          tm->tm_mon + 1, tm->tm_year + 1900);
  if(strcmp(currentTime,(char*)transData->terminalData.transactionDate) != 0)
  {
    return INTERNAL_SERVER_ERROR;
  }
  //Check if the account exist
  int8_t checkAccountAvilabilty = 0;
  for (int i = 0; i < 255; i++) {
    if ((strcmp((char *)transData->cardHolderData.primaryAccountNumber,
                (char *)accounts[i].primaryAccountNumber)) == 0) {
      if (accounts[i].active != 0) {
        checkAccountAvilabilty = 1;
        break;
      }
    }
  }
  if (checkAccountAvilabilty != 1)
    return INTERNAL_SERVER_ERROR;
  return APPROVED;
}

uint8_t accountNumber ;
EN_serverError_t isValidAccount(ST_cardData_t *cardData) {
  // check accout number
  int8_t check = 0;
  for (int i = 0; i < 255; i++) {
    if ((strcmp((char *)cardData->primaryAccountNumber,
                (char *)accounts[i].primaryAccountNumber)) == 0) {
      check = 1;
      accountNumber = i;
      return SERVER_OK;
    }
  }
  if (check != 1)
    return ACCOUNT_NOT_FOUND;
  return SERVER_OK;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData) {

  if(termData->transAmount > accounts[accountNumber].balance)
  {
    printf("Transaction declined: **Low Balance**\n");
    return LOW_BALANCE;
  }
  printf("Your New Balance is: %0.02f\n", accounts[accountNumber].balance -= termData->transAmount);
  return SERVER_OK; 
}
EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
  time_t t = time(NULL);
  struct tm *tm = localtime(&t);
  FILE *fp =fopen("data.txt", "a");
  if(fp == NULL)
  { 
    printf("Faild to open the file \n"); 
    fprintf(fp,"\n");
  }
  fprintf(fp, "%d.%d.%d %s\n",tm->tm_hour-12,tm->tm_min,tm->tm_sec, transData->terminalData.transactionDate);
  return SERVER_OK;
}
// EN_serverError_t getTransaction(uint32_t transactionSequenceNumber);