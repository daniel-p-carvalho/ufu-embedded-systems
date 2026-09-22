/****************************************************************************
 * main.c
 *
 * Description:
 *
 * Authors: Daniel Pereira de Carvalho <daniel.carvalho@ufu.br>
 *
 *****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <stdlib.h>

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: main
 *
 * Description:
 *   Standard C entry point. In a bare-metal environment, this function
 *   should never return.
 *
 * Return:
 *   Although it never returns in a bare-metal environment, it returns
 *   EXIT_FAILURE as a safeguard against unexpected loop termination.
 ****************************************************************************/

int main(void)
{
  /* Main application loop. In a bare-metal environment, this loop should
   * run indefinitely, performing the necessary tasks of the application.
   */
  while (1);

  /* Should never be reached in an embedded system. */
  return EXIT_FAILURE;
}