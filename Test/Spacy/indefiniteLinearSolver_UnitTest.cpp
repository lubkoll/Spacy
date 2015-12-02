// Copyright (C) 2015 by Lars Lubkoll. All rights reserved.
// Released under the terms of the GNU General Public License version 3 or later.

#include <gtest/gtest.h>

#include "Spacy/linearSolver.hh"
#include "Spacy/Spaces/RealSpace/real.hh"
#include "Test/Mock/linearSolver.hh"
#include "Test/Mock/vector.hh"

using namespace Spacy;

TEST(IndefiniteLinearSolver,Construction)
{
  auto solver = Mock::IndefiniteLinearSolver{};
  IndefiniteLinearSolver typeErasedSolver( solver );
  ASSERT_FALSE( !typeErasedSolver );
}

TEST(IndefiniteLinearSolver,Assignment)
{
  auto solver = Mock::IndefiniteLinearSolver{};
  IndefiniteLinearSolver typeErasedSolver;
  ASSERT_TRUE( !typeErasedSolver );
  typeErasedSolver = solver;
  ASSERT_FALSE( !typeErasedSolver );
}

TEST(IndefiniteLinearSolver,Apply)
{
  auto solver = Mock::IndefiniteLinearSolver{};
  IndefiniteLinearSolver typeErasedSolver( solver );
  Mock::Vector vector;
  ASSERT_NO_THROW( typeErasedSolver(vector) );
}

TEST(IndefiniteLinearSolver,IsPositiveDefinite)
{
  auto solver = Mock::IndefiniteLinearSolver{};
  IndefiniteLinearSolver typeErasedSolver( solver );
  ASSERT_NO_THROW( typeErasedSolver.isPositiveDefinite() );
  ASSERT_TRUE( typeErasedSolver.isPositiveDefinite() );
}