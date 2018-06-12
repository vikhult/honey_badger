//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "LaplaceYoung.h"

registerMooseObject("MooseApp", LaplaceYoung);

template <>
InputParameters
validParams<LaplaceYoung>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<Real>("kappa","Parameter controlling the diffusion");
  params.addClassDescription("The Laplacian operator ($-\\nabla \\cdot \\nabla u$), with the weak "
                             "form of $(\\nabla \\phi_i, \\nabla u_h)$.");
  return params;
}

LaplaceYoung::LaplaceYoung(const InputParameters & parameters) : Kernel(parameters)
{
  _kappa = getParam<Real>("kappa");
}

Real
LaplaceYoung::computeK()
{
  return 1. /std::sqrt(1. + _grad_u[_qp] * _grad_u[_qp]);
}

Real
LaplaceYoung::computeQpResidual()
{
  // _some_variable_name denotes that the variable is a member of a class
  Real k = computeK();
  return k * _grad_u[_qp] * _grad_test[_i][_qp] + _kappa * _u[_qp] * _test[_i][_qp];
}

Real
LaplaceYoung::computeQpJacobian()
{
  Real k = computeK();
  return k * _grad_phi[_j][_qp] * _grad_test[_i][_qp] + _kappa * _phi[_j][_qp] * _test[_i][_qp];
}
