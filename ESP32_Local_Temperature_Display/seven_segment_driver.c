#include "seven_segment_driver.h"
#ifndef INPUT
  #define INPUT 0x0
#endif

#ifndef OUTPUT
  #define OUTPUT 0x1
#endif

/*******************************************************************************
* Function Name: turn_digit_on
********************************************************************************
*
* Summary:
*  This routine provides power to a single digit in a 7-segment display
*
* Parameters:
*  int digit number: (1 - 5)
*
* Return:
*  None
*
*******************************************************************************/
void turn_digit_on(int digit) {
  if (digit <= 0) return;
  if (digit > 2) return;
  switch (digit) {
    case 1:
      digitalWrite(SEVEN_SEG_DIGIT_1, LED_OFF);
      break;
    case 2:
      digitalWrite(SEVEN_SEG_DIGIT_2, LED_OFF);
      break;
  }
}

/*******************************************************************************
* Function Name: turn_digit_off
********************************************************************************
*
* Summary:
*  This routine removes power from a single digit in a 7-segment display
*
* Parameters:
*  int digit number: (1 - 5)
*
* Return:
*  None
*
*******************************************************************************/
void turn_digit_off(int digit) {
  if (digit <= 0) return;
  if (digit > 2) return;
  switch (digit) {
    case 1:
      digitalWrite(SEVEN_SEG_DIGIT_1, LED_ON);
      break;
    case 2:
      digitalWrite(SEVEN_SEG_DIGIT_2, LED_ON);
      break;
  }
}

/*******************************************************************************
* Function Name: seven_segment_display_digit
********************************************************************************
*
* Summary:
*  This routine displays a number (digit) on a 7-segment display
*
* Parameters:
*  int digit: number (0 - 9)
*
* Return:
*  None
*
*******************************************************************************/
void seven_segment_display_digit(int digit) {
  switch (digit) {
    case 0:
      digitalWrite(SEVEN_SEG_A, LED_ON);
      digitalWrite(SEVEN_SEG_B, LED_ON);
      digitalWrite(SEVEN_SEG_C, LED_ON);
      digitalWrite(SEVEN_SEG_D, LED_ON);
      digitalWrite(SEVEN_SEG_E, LED_ON);
      digitalWrite(SEVEN_SEG_F, LED_ON);
      digitalWrite(SEVEN_SEG_G, LED_OFF);
      break;
    case 1:
      digitalWrite(SEVEN_SEG_A, LED_OFF);
      digitalWrite(SEVEN_SEG_B, LED_ON);
      digitalWrite(SEVEN_SEG_C, LED_ON);
      digitalWrite(SEVEN_SEG_E, LED_OFF);
      digitalWrite(SEVEN_SEG_D, LED_OFF);
      digitalWrite(SEVEN_SEG_F, LED_OFF);
      digitalWrite(SEVEN_SEG_G, LED_OFF);
      break;
    case 2:
      digitalWrite(SEVEN_SEG_A, LED_ON);
      digitalWrite(SEVEN_SEG_B, LED_ON);
      digitalWrite(SEVEN_SEG_C, LED_OFF);
      digitalWrite(SEVEN_SEG_D, LED_ON);
      digitalWrite(SEVEN_SEG_E, LED_ON);
      digitalWrite(SEVEN_SEG_F, LED_OFF);
      digitalWrite(SEVEN_SEG_G, LED_ON);
      break;
    case 3:
      digitalWrite(SEVEN_SEG_A, LED_ON);
      digitalWrite(SEVEN_SEG_B, LED_ON);
      digitalWrite(SEVEN_SEG_C, LED_ON);
      digitalWrite(SEVEN_SEG_D, LED_ON);
      digitalWrite(SEVEN_SEG_E, LED_OFF);
      digitalWrite(SEVEN_SEG_F, LED_OFF);
      digitalWrite(SEVEN_SEG_G, LED_ON);
      break;
    case 4:
      digitalWrite(SEVEN_SEG_A, LED_OFF);
      digitalWrite(SEVEN_SEG_B, LED_ON);
      digitalWrite(SEVEN_SEG_C, LED_ON);
      digitalWrite(SEVEN_SEG_D, LED_OFF);
      digitalWrite(SEVEN_SEG_E, LED_OFF);
      digitalWrite(SEVEN_SEG_F, LED_ON);
      digitalWrite(SEVEN_SEG_G, LED_ON);
      break;
    case 5:
      digitalWrite(SEVEN_SEG_A, LED_ON);
      digitalWrite(SEVEN_SEG_B, LED_OFF);
      digitalWrite(SEVEN_SEG_C, LED_ON);
      digitalWrite(SEVEN_SEG_D, LED_ON);
      digitalWrite(SEVEN_SEG_E, LED_OFF);
      digitalWrite(SEVEN_SEG_F, LED_ON);
      digitalWrite(SEVEN_SEG_G, LED_ON);
      break;
    case 6:
      digitalWrite(SEVEN_SEG_A, LED_ON);
      digitalWrite(SEVEN_SEG_B, LED_OFF);
      digitalWrite(SEVEN_SEG_C, LED_ON);
      digitalWrite(SEVEN_SEG_D, LED_ON);
      digitalWrite(SEVEN_SEG_E, LED_ON);
      digitalWrite(SEVEN_SEG_F, LED_ON);
      digitalWrite(SEVEN_SEG_G, LED_ON);
      break;
    case 7:
      digitalWrite(SEVEN_SEG_A, LED_ON);
      digitalWrite(SEVEN_SEG_B, LED_ON);
      digitalWrite(SEVEN_SEG_C, LED_ON);
      digitalWrite(SEVEN_SEG_D, LED_OFF);
      digitalWrite(SEVEN_SEG_E, LED_OFF);
      digitalWrite(SEVEN_SEG_F, LED_OFF);
      digitalWrite(SEVEN_SEG_G, LED_OFF);
      break;
    case 8:
      digitalWrite(SEVEN_SEG_A, LED_ON);
      digitalWrite(SEVEN_SEG_B, LED_ON);
      digitalWrite(SEVEN_SEG_C, LED_ON);
      digitalWrite(SEVEN_SEG_D, LED_ON);
      digitalWrite(SEVEN_SEG_E, LED_ON);
      digitalWrite(SEVEN_SEG_F, LED_ON);
      digitalWrite(SEVEN_SEG_G, LED_ON);
      break;
    case 9:
      digitalWrite(SEVEN_SEG_A, LED_ON);
      digitalWrite(SEVEN_SEG_B, LED_ON);
      digitalWrite(SEVEN_SEG_C, LED_ON);
      digitalWrite(SEVEN_SEG_D, LED_OFF);
      digitalWrite(SEVEN_SEG_E, LED_OFF);
      digitalWrite(SEVEN_SEG_F, LED_ON);
      digitalWrite(SEVEN_SEG_G, LED_ON);
      break;
  }
}

/*******************************************************************************
* Function Name: seven_segment_display_dash
********************************************************************************
*
* Summary:
*  This routine displays a dash '-' on a 7-segment display
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void seven_segment_display_dash() {
    digitalWrite(SEVEN_SEG_A, LED_OFF);
    digitalWrite(SEVEN_SEG_B, LED_OFF);
    digitalWrite(SEVEN_SEG_C, LED_OFF);
    digitalWrite(SEVEN_SEG_D, LED_OFF);
    digitalWrite(SEVEN_SEG_E, LED_OFF);
    digitalWrite(SEVEN_SEG_F, LED_OFF);
    digitalWrite(SEVEN_SEG_G, LED_ON);
}

/*******************************************************************************
* Function Name: seven_segment_display_degree_symbol
********************************************************************************
*
* Summary:
*  This routine displays a degree symbol on a 7-segment display
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void seven_segment_display_degree_symbol() {
    digitalWrite(SEVEN_SEG_A, LED_ON);
    digitalWrite(SEVEN_SEG_B, LED_ON);
    digitalWrite(SEVEN_SEG_C, LED_OFF);
    digitalWrite(SEVEN_SEG_D, LED_OFF);
    digitalWrite(SEVEN_SEG_E, LED_OFF);
    digitalWrite(SEVEN_SEG_F, LED_ON);
    digitalWrite(SEVEN_SEG_G, LED_ON);
}

/*******************************************************************************
* Function Name: seven_segment_display_letter
********************************************************************************
*
* Summary:
*  This routine displays a letter on a 7-segment display
*
* Parameters:
*  int letter: A, b, C, d, E, F, g, H, i, L, O, p, S, U
*
* Return:
*  None
*
*******************************************************************************/
void seven_segment_display_letter(char letter) {
  switch (letter) {
    case 'A':
      digitalWrite(SEVEN_SEG_A, LED_ON);
      digitalWrite(SEVEN_SEG_B, LED_ON);
      digitalWrite(SEVEN_SEG_C, LED_ON);
      digitalWrite(SEVEN_SEG_D, LED_OFF);
      digitalWrite(SEVEN_SEG_E, LED_ON);
      digitalWrite(SEVEN_SEG_F, LED_ON);
      digitalWrite(SEVEN_SEG_G, LED_ON);
      break;
    case 'b':
      digitalWrite(SEVEN_SEG_A, LED_OFF);
      digitalWrite(SEVEN_SEG_B, LED_OFF);
      digitalWrite(SEVEN_SEG_C, LED_ON);
      digitalWrite(SEVEN_SEG_D, LED_ON);
      digitalWrite(SEVEN_SEG_E, LED_ON);
      digitalWrite(SEVEN_SEG_F, LED_ON);
      digitalWrite(SEVEN_SEG_G, LED_ON);
      break;
    case 'C':
      // Fall through
    case 'c':
      digitalWrite(SEVEN_SEG_A, LED_ON);
      digitalWrite(SEVEN_SEG_B, LED_OFF);
      digitalWrite(SEVEN_SEG_C, LED_OFF);
      digitalWrite(SEVEN_SEG_D, LED_ON);
      digitalWrite(SEVEN_SEG_E, LED_ON);
      digitalWrite(SEVEN_SEG_F, LED_ON);
      digitalWrite(SEVEN_SEG_G, LED_OFF);
      break;
    case 'd':
      digitalWrite(SEVEN_SEG_A, LED_OFF);
      digitalWrite(SEVEN_SEG_B, LED_ON);
      digitalWrite(SEVEN_SEG_C, LED_ON);
      digitalWrite(SEVEN_SEG_D, LED_ON);
      digitalWrite(SEVEN_SEG_E, LED_ON);
      digitalWrite(SEVEN_SEG_F, LED_OFF);
      digitalWrite(SEVEN_SEG_G, LED_ON);
      break;
    case 'E':
      digitalWrite(SEVEN_SEG_A, LED_ON);
      digitalWrite(SEVEN_SEG_B, LED_OFF);
      digitalWrite(SEVEN_SEG_C, LED_OFF);
      digitalWrite(SEVEN_SEG_D, LED_ON);
      digitalWrite(SEVEN_SEG_E, LED_ON);
      digitalWrite(SEVEN_SEG_F, LED_ON);
      digitalWrite(SEVEN_SEG_G, LED_ON);
      break;
    case 'F':
      digitalWrite(SEVEN_SEG_A, LED_ON);
      digitalWrite(SEVEN_SEG_B, LED_OFF);
      digitalWrite(SEVEN_SEG_C, LED_OFF);
      digitalWrite(SEVEN_SEG_D, LED_OFF);
      digitalWrite(SEVEN_SEG_E, LED_ON);
      digitalWrite(SEVEN_SEG_F, LED_ON);
      digitalWrite(SEVEN_SEG_G, LED_ON);
      break;
    case 'g':
      digitalWrite(SEVEN_SEG_A, LED_ON);
      digitalWrite(SEVEN_SEG_B, LED_ON);
      digitalWrite(SEVEN_SEG_C, LED_ON);
      digitalWrite(SEVEN_SEG_D, LED_ON);
      digitalWrite(SEVEN_SEG_E, LED_OFF);
      digitalWrite(SEVEN_SEG_F, LED_ON);
      digitalWrite(SEVEN_SEG_G, LED_ON);
      break;
    case 'H':
      digitalWrite(SEVEN_SEG_A, LED_OFF);
      digitalWrite(SEVEN_SEG_B, LED_ON);
      digitalWrite(SEVEN_SEG_C, LED_ON);
      digitalWrite(SEVEN_SEG_D, LED_OFF);
      digitalWrite(SEVEN_SEG_E, LED_ON);
      digitalWrite(SEVEN_SEG_F, LED_ON);
      digitalWrite(SEVEN_SEG_G, LED_ON);
      break;
    case 'i':
      digitalWrite(SEVEN_SEG_A, LED_OFF);
      digitalWrite(SEVEN_SEG_B, LED_ON);
      digitalWrite(SEVEN_SEG_C, LED_ON);
      digitalWrite(SEVEN_SEG_D, LED_OFF);
      digitalWrite(SEVEN_SEG_E, LED_OFF);
      digitalWrite(SEVEN_SEG_F, LED_OFF);
      digitalWrite(SEVEN_SEG_G, LED_OFF);
      break;
    case 'L':
      digitalWrite(SEVEN_SEG_A, LED_OFF);
      digitalWrite(SEVEN_SEG_B, LED_OFF);
      digitalWrite(SEVEN_SEG_C, LED_OFF);
      digitalWrite(SEVEN_SEG_D, LED_ON);
      digitalWrite(SEVEN_SEG_E, LED_ON);
      digitalWrite(SEVEN_SEG_F, LED_ON);
      digitalWrite(SEVEN_SEG_G, LED_OFF);
      break;
    case 'o':
      // Fall through
    case 'O':
      digitalWrite(SEVEN_SEG_A, LED_ON);
      digitalWrite(SEVEN_SEG_B, LED_ON);
      digitalWrite(SEVEN_SEG_C, LED_ON);
      digitalWrite(SEVEN_SEG_D, LED_ON);
      digitalWrite(SEVEN_SEG_E, LED_ON);
      digitalWrite(SEVEN_SEG_F, LED_ON);
      digitalWrite(SEVEN_SEG_G, LED_OFF);
      break;
    case 'p':
      digitalWrite(SEVEN_SEG_A, LED_ON);
      digitalWrite(SEVEN_SEG_B, LED_ON);
      digitalWrite(SEVEN_SEG_C, LED_OFF);
      digitalWrite(SEVEN_SEG_D, LED_OFF);
      digitalWrite(SEVEN_SEG_E, LED_ON);
      digitalWrite(SEVEN_SEG_F, LED_ON);
      digitalWrite(SEVEN_SEG_G, LED_ON);
      break;
    case 's':
      // Fall through
    case 'S':
      digitalWrite(SEVEN_SEG_A, LED_ON);
      digitalWrite(SEVEN_SEG_B, LED_OFF);
      digitalWrite(SEVEN_SEG_C, LED_ON);
      digitalWrite(SEVEN_SEG_D, LED_ON);
      digitalWrite(SEVEN_SEG_E, LED_OFF);
      digitalWrite(SEVEN_SEG_F, LED_ON);
      digitalWrite(SEVEN_SEG_G, LED_ON);
      break;

    case 'u':
      // Fall through
    case 'U':
      digitalWrite(SEVEN_SEG_A, LED_OFF);
      digitalWrite(SEVEN_SEG_B, LED_ON);
      digitalWrite(SEVEN_SEG_C, LED_ON);
      digitalWrite(SEVEN_SEG_D, LED_ON);
      digitalWrite(SEVEN_SEG_E, LED_ON);
      digitalWrite(SEVEN_SEG_F, LED_ON);
      digitalWrite(SEVEN_SEG_G, LED_OFF);
      break;
  }
}

/*******************************************************************************
* Function Name: seven_segment_turn_display_off
********************************************************************************
*
* Summary:
*  This routine turns all segments off in a 7-segment display 
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void seven_segment_turn_display_off() {
  digitalWrite(SEVEN_SEG_A, LED_OFF);
  digitalWrite(SEVEN_SEG_B, LED_OFF);
  digitalWrite(SEVEN_SEG_C, LED_OFF);
  digitalWrite(SEVEN_SEG_D, LED_OFF);
  digitalWrite(SEVEN_SEG_E, LED_OFF);
  digitalWrite(SEVEN_SEG_F, LED_OFF);
  digitalWrite(SEVEN_SEG_G, LED_OFF);
}

/*******************************************************************************
* Function Name: seven_segment_display_two_numbers
********************************************************************************
*
* Summary:
*  This routine displays two numbers on a 7-segment display with a delay of <delay_in_ms> between updates
*  example: 
*    seven_segment_display_two_numbers(1, 9, 10)
*    Displays 19 on the 7-segment display
*     - display 1 for 10 milliseconds on digit 2
*     - display 9 for 10 milliseconds on digit 1
* Parameters:
*  int tens: Tens
*  int units: Units
*  int delay_in_ms: Delay in milliseconds
*
* Return:
*  None
*
*******************************************************************************/
void seven_segment_display_two_numbers(int tens, int units, int delay_in_ms) {
  // Display tens
  seven_segment_display_digit(tens);
  turn_digit_on(2);
  delay(delay_in_ms);
  turn_digit_off(2);
  
  // Display units
  seven_segment_display_digit(units);
  turn_digit_on(1);
  delay(delay_in_ms);
  turn_digit_off(1);
}

/*******************************************************************************
* Function Name: seven_segment_display_two_letters
********************************************************************************
*
* Summary:
*  This routine displays two letters on a 7-segment display with a delay of <delay_in_ms> between updates
*  example: 
*    seven_segment_display_two_letters('A', 'b', 10)
*    Displays Ab on the 7-segment display
*     - display A for 10 milliseconds on letter 1
*     - display b for 10 milliseconds on letter 2
* Parameters:
*  char letter_1: Left most letter
*  char letter_2: Right most letter
*  int delay_in_ms: Delay in milliseconds
*
* Return:
*  None
*
*******************************************************************************/
void seven_segment_display_two_letters(char letter_1, char letter_2, int delay_in_ms) {
  // Display left most letter
  seven_segment_display_letter(letter_1);
  turn_digit_on(2);
  delay(delay_in_ms);
  turn_digit_off(2);
  
  // Display right most
  seven_segment_display_letter(letter_2);
  turn_digit_on(1);
  delay(delay_in_ms);
  turn_digit_off(1);
}