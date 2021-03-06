#ifndef CPPUNIT_PLUGIN_TESTPLUGINADAPTER
#define CPPUNIT_PLUGIN_TESTPLUGINADAPTER

#include <cppunit/Portability.h>

#if !defined(CPPUNIT_NO_TESTPLUGIN)

#include <cppunit/plugin/TestPlugIn.h>

#if CPPUNIT_NEED_DLL_DECL
#pragma warning( push )
#pragma warning( disable: 4251 4660 )  // X needs to have dll-interface to be used by clients of class Z
#endif

CPPUNIT_NS_BEGIN


class TestSuite;


/*! \brief Default implementation of test plug-in interface.
 * \ingroup WritingTestPlugIn
 *
 * Override getSuiteName() to specify the suite name. Default is "All Tests".
 *
 * CppUnitTestPlugIn::getTestSuite() returns a suite that contains
 * all the test registered to the default test factory registry 
 * ( TestFactoryRegistry::getRegistry() ).
 *
 */
class CPPUNIT_API TestPlugInDefaultImpl : public CppUnitTestPlugIn
{
public:
  TestPlugInDefaultImpl();

  virtual ~TestPlugInDefaultImpl() override;

  void initialize( TestFactoryRegistry *registry,
                   const PlugInParameters &parameters ) override;

  void addListener( TestResult *eventManager ) override;

  void removeListener( TestResult *eventManager ) override;

  void addXmlOutputterHooks( XmlOutputter *outputter ) override;

  void removeXmlOutputterHooks() override;

  void uninitialize( TestFactoryRegistry *registry ) override;
};


CPPUNIT_NS_END

#if CPPUNIT_NEED_DLL_DECL
#pragma warning( pop )
#endif

#endif // !defined(CPPUNIT_NO_TESTPLUGIN)

#endif // CPPUNIT_PLUGIN_TESTPLUGINADAPTER
