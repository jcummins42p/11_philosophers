/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splashscreen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:43:20 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/11 15:41:34 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	splash4(void)
{
	printf("                                :      :-..     ...     .+=:  @@@@@\
@@@@@@@@@@PHILOSOPHERSP@@@PPP P@@ PHILOSOPHERS P    \n");
	printf("                                :         ....    .:. - =-:  P@@@@\
@@  @@PP PHILOSOPHERS @P@@@@P P P PHILOSOPHERS       \n");
	printf("                                =   .           .  :  +=:. PPP@@@@\
@ :=P@PP PP@@@PP@@@@@@@P@@@@PP@P  PHILOSOPHERS       \n" KDEF);
	fflush(stdout);
}

void	splash3(void)
{
	printf("                                        |                          \
- @@::.:  :  PPPPPPPP P=P@ @P@@  PPPP @@P@@@@@@@\n");
	printf("                                     + -=+++              +        \
 :@@@P@@@@--.+      @@@@@@@P@@ @P    PPP PP@@@@@  \n");
	printf("                                     : =@ -::=            .  .:    \
  .-   P@@@@@P.==  PHILOSOPHERSP P             @    \n");
	printf("                                      +: -P@ --+          .      .\
   - + P@@.. . -P   .:=  :-@@@@@@PPP   P          @    \n");
	printf("                                     +-=++ @P+-:-         :  .::  \
  -         P@       =+. .:: @@@@@@P@@@PP      @@@@  \n");
	printf("                                     +.+=-  P -:.-           ..   \
: +@@ -:::::- @@.  -    P .-@P@@@@@@@@@PP@PP   @@@@  \n");
	printf("                                      +      +-:..-          .:-+  \
   :   PPPPPPP    =: +  - @:@@ PHILOSOPHERS PP PHIL   \n");
	printf("                                        +  +=-:..:::    +   ..    .\
: PP PP PPPPP      .+ +PP@@@   PHILOSOPHERSPHILOSOP \n");
	printf("                                            +-:.:::-:++   ::-.   +=\
-@@@PPPPPPP PPP P@@@+  P @P@@P       PHILOSOPHERS P \n");
	printf("                                          =--.:....   :+@@+.: -  @=\
 @@@@@P@PPPPPPPP@@@@@P @= @@@@@      P@@@@@@@@@@@P  \n");
	printf("                                   +=      .::-:....=   --  :-.+@@ \
 @PP@@@PP@@PPPP@@@@@@@P@@+P@@@@@  P PHILOSOPHERSP   \n");
	printf("                                 .   :.      ..:::.    .: .=:  @@@@\
 @@PP@@@@P@PHILOSOPHERS@@@PP@@@@@  PHILOSOPHERS     \n");
	splash4();
}

void	splash2(void)
{
	printf("                                                                - \
   \\/\\/\\/\\/  P@@                                    \n");
	printf("                                   STARTING                       -\
:-/\\/\\/\\/\\P @@@   @@@P    @P                      \n");
	printf("                                   PHILOSOPHERS                   +\
  -   =-=+=- P@@@@@@P@@@@@@P@@@@PPP                 \n");
	printf("                                     | | | |                       \
+ =:+:= :==  @@@@@ . @@:.+P@   := PP                \n");
	printf("                                     | | | |                      \
  =.=+--=::+@@@@  + @..+ @@-   :+PPPPP              \n");
	printf("                                     | | | |                       \
    +-.:== @@@  .=P+.:+@@+..   :=  @@@P             \n");
	printf("                                     | | | |                       \
        .- @@= -=  .+@@+ :=.   :=+PP@@PPP           \n");
	printf("                                     _______                       \
             .=+  + @@  --.  .@@@@@ @@@PP           \n");
	printf("                                        V                      =.  \
-=  -+@@  .=:. =@@@@P@@@@@@@PP          \n");
	printf("                                        |                    =     \
  .   +=:::-=  @ .     :PP   P@@@PP         \n");
	printf("                                        |                   -      \
   . -+ .-= -P@@  P -  - =P:-PP=  -+P@ PPP        \n");
	printf("                                        |                  +       \
   :+@@ P@ . PPPPPP@P  +-:P@PPP@PP@:-:-= P   @@@  \n");
	splash3();
}

void	splash(void)
{
	printf(KGRN "                                                              \
                                                    \n");
	printf("                                                                   \
                                                    \n");
	printf("                                                                   \
-     .:+                                        \n");
	printf("                                                                 + \
.:= PPPP@                                       \n");
	printf("                                                                :  \
 . P@@@P@@@P                                      \n");
	printf("                                                               .   \
   .:++  @@P@@@PP                                     \n");
	printf("                                                              : :+ \
  :++= @@PP@@@ PP                                   \n");
	printf("                                                               . + \
-+  - P@ + P@ P @                                   \n");
	printf("                                                              -===:\
.+P@.P@P+ PP@ @@P                                   \n");
	printf("                                                                -  \
👁️  ..  PP 👁️  P@@                                    \n");
	printf("                                                                =. \
.  -P+@@P     PP                                    \n");
	printf("                                                                = \
 .-+=+     P                                      \n");
	splash2();
}
