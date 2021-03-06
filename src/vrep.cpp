/* vrep.cpp -- convenience code to interface with V-REP
 * Copyright (C) 2013  Galois, Inc.
 *
 * This library is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 * To contact Galois, complete the Web form at <http://corp.galois.com/contact/>
 * or write to Galois, Inc., 421 Southwest 6th Avenue, Suite 300, Portland,
 * Oregon, 97204-1622. */

#ifdef HAVE_CONFIG_H
#   include <config.h>
#endif

#include <stdexcept>
#include <string>

#include <v_repLib.h>

#include "vrep.h"

namespace vrep {

    InterfaceLockGuard::~InterfaceLockGuard() noexcept {
        if (isLocked) {
            /* Throwing an exception from a destructor is a bad, bad idea.  See
             * /More Effective C++/ #14. */
            try {
                unlock();
            } catch (const Error& error) {
                /* Unlocking failed, so we're kind of screwed at this point.  We
                 * can't even display a dialog to the user noting the failure,
                 * because the interface is locked! *sigh*  Just give up and do
                 * nothing. */
            }
        }
    }

    void InterfaceLockGuard::copyState(const InterfaceLockGuard &other) {
        if (isLocked) {
            unlock();
        }
        if (other.isLocked) {
            lock();
        } else {
            isLocked = false;
        }
    }

    void InterfaceLockGuard::moveState(InterfaceLockGuard &other) {
        if (isLocked) {
            unlock();
        }
        if (other.isLocked) {
            lock();
            other.unlock();
        } else {
            isLocked = false;
        }
    }

}
