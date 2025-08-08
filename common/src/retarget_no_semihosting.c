/**
  * @file retarget_no_semihosting.c
  * @brief No semihosting retarget i/o routines
  * @author Leon Lee (leonlee.scut@gmail.com)
  * @version 0.1
  * @date 2024/07/16
  * 
  * @copyright Copyright (c) 2024 South China University of Technology.
  * All rights reserved.
  * 
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  * 
  * @par History:
  * 	Date		Version		Author			Description
  * 	2024/07/16	0.1			Leon Lee		Preliminary version.
  */


#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
__asm (".global __use_no_semihosting\n\t");
#elif defined(__CC_ARM)
#pragma import(__use_no_semihosting)
#elif defined(__GNUC__)
__attribute__((__section__(".no_semihosting"), __used__))
#elif defined(__ICCARM__)
#pragma import(no_semihosting)
#endif

extern int stdout_putchar (int ch);

/**
 * @brief Weak implementation of _ttywrch to redirect output to stdout_putchar.
 *
 * This function is called by the C library when a character is written to the
 * console through the _ttywrch function. It redirects the output to
 * stdout_putchar.
 *
 * @param ch The character to be written to the console.
 *
 * @note This function is declared as weak, which means that it can be
 *       overridden by other definitions in the application code.
 */
__attribute__((weak))
void _ttywrch (int ch) {
    // Redirect the output to stdout_putchar
    // The original implementation is commented out below
//   (void)ch;
//   __asm("BKPT 0");
    stdout_putchar (ch);
}


/**
 * @brief Weak implementation of _sys_exit to handle system exit with specified return code.
 *
 * This function is called when the system exits with a specified return code. 
 * It contains an endless loop to halt the system.
 *
 * @param return_code The return code of the system exit.
 */
__attribute__((weak))
void _sys_exit(int return_code)
{
    for (;;);    /* endless loop */
}

/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
