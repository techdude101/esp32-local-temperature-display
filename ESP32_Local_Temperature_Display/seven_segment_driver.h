#ifndef _SEVEN_SEGMENT_DRIVER
  #define _SEVEN_SEGMENT_DRIVER
#endif

#ifdef __cplusplus
 extern "C" {
#endif

/* SEVEN-segment Pins
YZ50282IJ1S LED SEVEN-segment display from DVD player (green)

Common Anode (digit pins)

13   12  11  10  9   8  7   6   5     4     3     2   1
g   f   e   d   c   b   a   digit5  digit4  digit3  digit2  digit1  decimal separator


left most separator = 9 & 1
right most separator = 8 & 1
*/

/* Change depending on whether common anode or common cathode */
#define LED_ON 0
#define LED_OFF 1

const int SEVEN_SEG_DIGIT_1 = 21;
const int SEVEN_SEG_DIGIT_2 = 22;

const int SEVEN_SEG_A = 19;
const int SEVEN_SEG_B = 18;
const int SEVEN_SEG_C = 17;
const int SEVEN_SEG_D = 16;
const int SEVEN_SEG_E = 15;
const int SEVEN_SEG_F = 14;
const int SEVEN_SEG_G = 13;

/* Function definitions */
void turn_digit_on(int digit);
void turn_digit_off(int digit);

void seven_segment_display_digit(int digit);
void seven_segment_display_dash();
void seven_segment_turn_display_off();

void seven_segment_display_two_numbers(int tens, int units, int delayInMs);
void seven_segment_display_degree_symbol();
void seven_segment_display_letter(char letter);
void seven_segment_display_two_letters(char letter_1, char letter_2, int delay_in_ms);

#ifdef __cplusplus
}
#endif