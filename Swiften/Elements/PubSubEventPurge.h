/*
 * Copyright (c) 2013 Remko Tronçon
 * Licensed under the GNU General Public License.
 * See the COPYING file for more information.
 */

#pragma once

#include <Swiften/Base/Override.h>
#include <Swiften/Base/API.h>
#include <Swiften/Elements/Payload.h>
#include <string>

#include <Swiften/Elements/PubSubEventPayload.h>

namespace Swift {
	class SWIFTEN_API PubSubEventPurge : public PubSubEventPayload {
		public:
			
			PubSubEventPurge();
			
			virtual ~PubSubEventPurge();

			const std::string& getNode() const {
				return node;
			}

			void setNode(const std::string& value) {
				this->node = value ;
			}


		private:
			std::string node;
	};
}