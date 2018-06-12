#include "HoneyBadgerApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

template <>
InputParameters
validParams<HoneyBadgerApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

HoneyBadgerApp::HoneyBadgerApp(InputParameters parameters) : MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  HoneyBadgerApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  HoneyBadgerApp::associateSyntax(_syntax, _action_factory);

  Moose::registerExecFlags(_factory);
  ModulesApp::registerExecFlags(_factory);
  HoneyBadgerApp::registerExecFlags(_factory);
}

HoneyBadgerApp::~HoneyBadgerApp() {}

void
HoneyBadgerApp::registerApps()
{
  registerApp(HoneyBadgerApp);
}

void
HoneyBadgerApp::registerObjects(Factory & factory)
{
    Registry::registerObjectsTo(factory, {"HoneyBadgerApp"});
}

void
HoneyBadgerApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & action_factory)
{
  Registry::registerActionsTo(action_factory, {"HoneyBadgerApp"});

  /* Uncomment Syntax parameter and register your new production objects here! */
}

void
HoneyBadgerApp::registerObjectDepends(Factory & /*factory*/)
{
}

void
HoneyBadgerApp::associateSyntaxDepends(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}

void
HoneyBadgerApp::registerExecFlags(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new execution flags here! */
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
HoneyBadgerApp__registerApps()
{
  HoneyBadgerApp::registerApps();
}

extern "C" void
HoneyBadgerApp__registerObjects(Factory & factory)
{
  HoneyBadgerApp::registerObjects(factory);
}

extern "C" void
HoneyBadgerApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  HoneyBadgerApp::associateSyntax(syntax, action_factory);
}

extern "C" void
HoneyBadgerApp__registerExecFlags(Factory & factory)
{
  HoneyBadgerApp::registerExecFlags(factory);
}
