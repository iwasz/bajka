/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_SHELL_H_
#define BAJKA_SHELL_H_

class Impl;

class Shell {
public:

        Shell ();
        ~Shell ();

        int run (const char *file);

private:

        void init ();
        void loop ();
        void destroy ();

private:

        Impl *impl;

};

#endif /* SHELL_H_ */
