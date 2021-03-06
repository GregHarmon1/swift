/*
 * Copyright (c) 2010-2016 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <Swiften/JID/JID.h>

#include <Swift/Controllers/UIEvents/UIEvent.h>

namespace Swift {
    class RequestChatUIEvent : public UIEvent {
        public:
            RequestChatUIEvent(const JID& contact) : contact_(contact) {}
            JID getContact() {return contact_;}
        private:
            JID contact_;
    };
}
