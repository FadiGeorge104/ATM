#include "../include/card.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

EN_cardError_t getCardHolderName(ST_cardData_t *cardData) {
  printf("Please enter your name:\n");
  fgets((char *)cardData->cardHolderName, 26, stdin);
  int8_t len = strlen((char *)cardData->cardHolderName);
  if (len == 0) {
    return WRONG_NAME;
  }

  if (len < 20 || len > 24) {
    return WRONG_NAME;
  }
  return OK;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData) {
  // Read Card Expiry Date
  time_t t = time(NULL);
  struct tm *tm = localtime(&t);

  printf("Enter You expiry Data in form of  \"02/24\":\n");
  fgets((char *)cardData->cardExpirationDate, 7, stdin);
  size_t len = strlen((char *)cardData->cardExpirationDate) - 1;
  // Error Handling
  if (len != 5 || (char)cardData->cardExpirationDate[2] != '/') {
    return WRONG_EXP_DATE;
  }

  if ((char)cardData->cardExpirationDate[0] > '1' ||
      (((char)cardData->cardExpirationDate[0] == '1') &&
       ((char)cardData->cardExpirationDate[1] > '2')))
    return WRONG_EXP_DATE;

  int16_t yearAsInt = ((int)(cardData->cardExpirationDate[3] - '0') * 10 +
                       (int)(cardData->cardExpirationDate[4] - '0')) +
                      2000;
  int16_t monAsInt = (int)(cardData->cardExpirationDate[0] - '0') * 10 +
                     (int)(cardData->cardExpirationDate[1] - '0');

  if (yearAsInt < (tm->tm_year + 1900))
    return WRONG_EXP_DATE;
  if (monAsInt < (tm->tm_mon + 1) && yearAsInt <= (tm->tm_year + 1900))
    return WRONG_EXP_DATE;
  return OK;

}

EN_cardError_t getCardPAN(ST_cardData_t *cardData) {
  printf("\nPlease,Enter your Card PAN:\n");
  fgets((char *)cardData->primaryAccountNumber, 21, stdin);
  cardData->primaryAccountNumber[strcspn((char *)cardData->primaryAccountNumber, "\n")] =
      '\0';
  int8_t cardlenth = strlen((char *)cardData->primaryAccountNumber);
  int16_t char_count = 0;
  int16_t digit_count = 0;
  if (cardlenth == 0 || cardlenth > 20)
    return WRONG_PAN;
  for (int i = 0; (char)cardData->primaryAccountNumber[i] != '\0'; i++) {
    if (((char)cardData->primaryAccountNumber[i] >= 'a' &&
         (char)cardData->primaryAccountNumber[i] <= 'z') ||
        ((char)cardData->primaryAccountNumber[i] >= 'A' &&
         (char)cardData->primaryAccountNumber[i] <= 'Z')) {
      char_count++;
    } else if ((char)cardData->primaryAccountNumber[i] >= '0' &&
               (char)cardData->primaryAccountNumber[i] <= '9') {
      digit_count++;
    }
  }
  if (char_count < 16 || char_count > 19)
    return WRONG_PAN;
  return OK;
}