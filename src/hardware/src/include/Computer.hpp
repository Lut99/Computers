/* COMPUTER.hpp
 *   by Lut99
 *
 * Created:
 *   3/30/2020, 8:09:06 PM
 * Last edited:
 *   3/30/2020, 8:14:04 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   The computer class is the basis of any computer, as the name suggests.
 *   Mainly, it handles the most basic form of bootup and shutdown of the
 *   computer, and it handles the coorporation between threads that serve
 *   the various computer components. This is the classes' header file.
**/


#ifndef COMPUTER_HPP
#define COMPUTER_HPP

namespace Computer {
    class Computer {
        public:
            /* The Computer class houses all components that makes a computer and also provides access to a BIOS and allows the processor to communicate with other parts. */
            Computer();
    };
}

#endif