// Copyright (C) 2015 by Lars Lubkoll. All rights reserved.
// Released under the terms of the GNU General Public License version 3 or later.

#include <gtest/gtest.h>

#include "Spacy/Algorithm/lipschitzConstant.hh"

TEST(LipschitzConstant,Assignment)
{
  auto L = Spacy::LipschitzConstant{5.};
  EXPECT_DOUBLE_EQ( L , 5. );

  L.setMinFactor(1e-3);
  L = -1e-3;
  EXPECT_DOUBLE_EQ( L , 5e-3 );

  L.setMaxFactor(1e6);
  L = 1e4;
  EXPECT_DOUBLE_EQ( L , 5e3 );

  auto eps = 1e-15;
  L.setEps(eps);
  L = 0.5*eps;
  EXPECT_DOUBLE_EQ( L , eps) ;
}

TEST(LipschitzConstant,Previous)
{
  auto L = Spacy::LipschitzConstant{2.2};

  L = 1.;
  EXPECT_DOUBLE_EQ( L.previous() , 2.2 );
}

