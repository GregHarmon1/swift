#include "Swiften/Network/PlatformDomainNameResolver.h"

// Putting this early on, because some system types conflict with thread
#include "Swiften/Network/PlatformDomainNameServiceQuery.h"

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <idna.h>
#include <algorithm>

#include "Swiften/Base/String.h"
#include "Swiften/Network/HostAddress.h"
#include "Swiften/EventLoop/MainEventLoop.h"
#include "Swiften/Network/HostAddressPort.h"
#include "Swiften/Network/DomainNameAddressQuery.h"

using namespace Swift;

namespace {
	struct AddressQuery : public DomainNameAddressQuery, public boost::enable_shared_from_this<AddressQuery>, public EventOwner {
		AddressQuery(const String& host) : hostname(host), thread(NULL), safeToJoin(false) {}

		~AddressQuery() {
			if (safeToJoin) {
				thread->join();
			}
			else {
				// FIXME: UGLYYYYY
			}
			delete thread;
		}

		void run() {
			safeToJoin = false;
			thread = new boost::thread(boost::bind(&AddressQuery::doRun, shared_from_this()));
		}
		
		void doRun() {
			boost::asio::ip::tcp::resolver resolver(ioService);
			boost::asio::ip::tcp::resolver::query query(hostname.getUTF8String(), "5222");
			try {
				boost::asio::ip::tcp::resolver::iterator endpointIterator = resolver.resolve(query);
				if (endpointIterator == boost::asio::ip::tcp::resolver::iterator()) {
					emitError();
				}
				else {
					boost::asio::ip::address address = (*endpointIterator).endpoint().address();
					HostAddress result = (address.is_v4() ? HostAddress(&address.to_v4().to_bytes()[0], 4) : HostAddress(&address.to_v6().to_bytes()[0], 16));
					MainEventLoop::postEvent(
							boost::bind(boost::ref(onResult), result, boost::optional<DomainNameResolveError>()), 
							shared_from_this());
				}
			}
			catch (...) {
				emitError();
			}
			safeToJoin = true;
		}

		void emitError() {
			MainEventLoop::postEvent(boost::bind(boost::ref(onResult), HostAddress(), boost::optional<DomainNameResolveError>(DomainNameResolveError())), shared_from_this());
		}

		boost::asio::io_service ioService;
		String hostname;
		boost::thread* thread;
		bool safeToJoin;
	};

	String getNormalized(const String& domain) {
		char* output;
		if (idna_to_ascii_8z(domain.getUTF8Data(), &output, 0) == IDNA_SUCCESS) {
			String result(output);
			free(output);
			return result;
		}
		else {
			return domain;
		}
	}
}

namespace Swift {

PlatformDomainNameResolver::PlatformDomainNameResolver() {
}

boost::shared_ptr<DomainNameServiceQuery> PlatformDomainNameResolver::createServiceQuery(const String& name) {
	return boost::shared_ptr<DomainNameServiceQuery>(new PlatformDomainNameServiceQuery(getNormalized(name)));
}

boost::shared_ptr<DomainNameAddressQuery> PlatformDomainNameResolver::createAddressQuery(const String& name) {
	return boost::shared_ptr<DomainNameAddressQuery>(new AddressQuery(getNormalized(name)));
}

}
