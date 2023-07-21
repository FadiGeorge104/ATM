#include "../include/app.h"


void appStart()
{
  ST_cardData_t card;
  EN_cardError_t holderName = getCardHolderName(&card);
  if (holderName == OK) 
    printf("Welcome: %s\n", card.cardHolderName);
  else 
    return exit(WRONG_NAME);
    
  EN_cardError_t expiryData = getCardExpiryDate(&card);
  if (expiryData != OK)
    return exit(WRONG_EXP_DATE);

  EN_cardError_t cardPAN = getCardPAN(&card);
  if (cardPAN != OK)
    return exit(WRONG_PAN);

  ST_terminalData_t term;
  EN_terminalError_t termData = getTransactionDate(&term);
  if (termData != TERMINAL_OK) 
    return exit(WRONG_EXP_DATE);
  

  EN_terminalError_t checkExpiredData = isCardExpired(&term);
  if (checkExpiredData != TERMINAL_OK) 
    return exit(EXPIRED_CARD);
  

  EN_terminalError_t tranAmount = getTransactionAmount(&term);
  if (tranAmount != TERMINAL_OK)
    return exit(INVALID_AMOUNT);

  EN_terminalError_t setMaxamount = setMaxAmount(&term);
  if(setMaxamount != TERMINAL_OK)
     return exit(INVALID_AMOUNT);

  EN_terminalError_t maxAmount = isBelowMaxAmount(&term);
  if (maxAmount != TERMINAL_OK)
    return exit(EXCEED_MAX_AMOUNT);



  ST_transaction_t trans;

    trans.cardHolderData = card;
    trans.terminalData = term;
  EN_transState_t dataError = recieveTransactionData(&trans);
  if (dataError != APPROVED)
    return exit(INTERNAL_SERVER_ERROR);

  EN_serverError_t accountAvilable = isValidAccount(&card);
  if(accountAvilable != SERVER_OK)
    return exit(INTERNAL_SERVER_ERROR);

  EN_serverError_t checkBalance = isAmountAvailable(&term);
  if(checkBalance != SERVER_OK)
    return exit(LOW_BALANCE);

  EN_serverError_t saveTrans = saveTransaction(&trans);
  if(saveTrans == SERVER_OK)
    printf("Proccess succeded\n");
  else
    return exit(SAVING_FAILED);
}