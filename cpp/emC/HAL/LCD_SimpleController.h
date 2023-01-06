#ifndef HGUARD_LCD_SimpleController
#define HGUARD_LCD_SimpleController
/**This file defines the interface to a LCD display in a well usable form.
 * A LCD display is familiar for simple controller, connected either with special hardware or often via a SPI driver.
 * The implementation should be done for any necessary controller in the proper way.
 */


/**Initialize the display. */
extern void initLCD_SimpleController_HALemC();

/**Set one character on the given position. */
extern void setCharLCD_SimpleController_HALemC(int pos, char ccharacter);

/**Output a text as soon as possible. */
void setTextLCD_SimpleController_HALemC(char const* text);

#endif //HGUARD_LCD_SimpleController
