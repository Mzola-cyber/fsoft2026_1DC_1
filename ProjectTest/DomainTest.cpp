//
// Created by masem on 14/06/2026.
//
#include <gtest/gtest.h>
#include "domain/headers/Veiculo.h"
#include "domain/headers/Cliente.h"

// CONSTRUTOR
TEST(DomainTest, CriarVeiculo) {
    Veiculo v(1, "AA-00-BB", 500);

    EXPECT_EQ(v.getId(), 1);
}

