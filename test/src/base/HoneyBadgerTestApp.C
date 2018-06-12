//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "HoneyBadgerTestApp.h"
#include "HoneyBadgerApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "ModulesApp.h"

template <>
InputParameters
validParams<HoneyBadgerTestApp>()
{
  InputParameters params = validParams<HoneyBadgerApp>();
  return params;
}

HoneyBadgerTestApp::HoneyBadgerTestApp(InputParameters parameters) : MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  HoneyBadgerApp::registerObjectDepends(_factory);
  HoneyBadgerApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  HoneyBadgerApp::associateSyntaxDepends(_syntax, _action_factory);
  HoneyBadgerApp::associateSyntax(_syntax, _action_factory);

  Moose::registerExecFlags(_factory);
  ModulesApp::registerExecFlags(_factory);
  HoneyBadgerApp::registerExecFlags(_factory);

  bool use_test_objs = getParam<bool>("allow_test_objects");
  if (use_test_objs)
  {
    HoneyBadgerTestApp::registerObjects(_factory);
    HoneyBadgerTestApp::associateSyntax(_syntax, _action_factory);
    HoneyBadgerTestApp::registerExecFlags(_factory);
  }
}

HoneyBadgerTestApp::~HoneyBadgerTestApp() {}

void
HoneyBadgerTestApp::registerApps()
{
  registerApp(HoneyBadgerApp);
  registerApp(HoneyBadgerTestApp);
}

void
HoneyBadgerTestApp::registerObjects(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new test objects here! */
}

void
HoneyBadgerTestApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
  /* Uncomment Syntax and ActionFactory parameters and register your new test objects here! */
}

void
HoneyBadgerTestApp::registerExecFlags(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new execute flags here! */
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
HoneyBadgerTestApp__registerApps()
{
  HoneyBadgerTestApp::registerApps();
}

// External entry point for dynamic object registration
extern "C" void
HoneyBadgerTestApp__registerObjects(Factory & factory)
{
  HoneyBadgerTestApp::registerObjects(factory);
}

// External entry point for dynamic syntax association
extern "C" void
HoneyBadgerTestApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  HoneyBadgerTestApp::associateSyntax(syntax, action_factory);
}

// External entry point for dynamic execute flag loading
extern "C" void
HoneyBadgerTestApp__registerExecFlags(Factory & factory)
{
  HoneyBadgerTestApp::registerExecFlags(factory);
}
