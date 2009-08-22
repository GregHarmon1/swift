#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

#include "Swiften/Parser/PayloadParsers/SecurityLabelParser.h"
#include "Swiften/Parser/PayloadParsers/UnitTest/PayloadParserTester.h"

using namespace Swift;

class SecurityLabelParserTest : public CppUnit::TestFixture
{
		CPPUNIT_TEST_SUITE(SecurityLabelParserTest);
		CPPUNIT_TEST(testParse);
		CPPUNIT_TEST_SUITE_END();

	public:
		SecurityLabelParserTest() {}

		void testParse() {
			SecurityLabelParser testling;
			PayloadParserTester parser(&testling);

			CPPUNIT_ASSERT(parser.parse(
				"<securitylabel xmlns=\"urn:xmpp:sec-label:0\">"
					"<displaymarking fgcolor=\"black\" bgcolor=\"red\">SECRET</displaymarking>"
					"<label>"
						"<esssecuritylabel xmlns=\"urn:xmpp:sec-label:ess:0\">MQYCAQQGASk=</esssecuritylabel>"
					"</label>"
					"<equivalentlabel>"
						"<icismlabel xmlns=\"http://example.gov/IC-ISM/0\" classification=\"S\" ownerProducer=\"USA\" disseminationControls=\"FOUO\"/>"
					"</equivalentlabel>"
					"<equivalentlabel>"
						"<esssecuritylabel xmlns=\"urn:xmpp:sec-label:ess:0\">MRUCAgD9DA9BcXVhIChvYnNvbGV0ZSk=</esssecuritylabel>"
					"</equivalentlabel>"
				"</securitylabel>"));

			SecurityLabel* payload = dynamic_cast<SecurityLabel*>(testling.getPayload().get());
			CPPUNIT_ASSERT_EQUAL(String("SECRET"), payload->getDisplayMarking());
			CPPUNIT_ASSERT_EQUAL(String("black"), payload->getForegroundColor());
			CPPUNIT_ASSERT_EQUAL(String("red"), payload->getBackgroundColor());
			CPPUNIT_ASSERT_EQUAL(String("<esssecuritylabel xmlns=\"urn:xmpp:sec-label:ess:0\">MQYCAQQGASk=</esssecuritylabel>"), payload->getLabel());	
			CPPUNIT_ASSERT_EQUAL(String("<icismlabel classification=\"S\" disseminationControls=\"FOUO\" ownerProducer=\"USA\" xmlns=\"http://example.gov/IC-ISM/0\"/>"), payload->getEquivalentLabels()[0]);	
			CPPUNIT_ASSERT_EQUAL(String("<esssecuritylabel xmlns=\"urn:xmpp:sec-label:ess:0\">MRUCAgD9DA9BcXVhIChvYnNvbGV0ZSk=</esssecuritylabel>"), payload->getEquivalentLabels()[1]);	
		}
};

CPPUNIT_TEST_SUITE_REGISTRATION(SecurityLabelParserTest);
