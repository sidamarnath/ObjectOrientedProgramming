 /**
 * @file SpartyGnomeTest.cpp
 * @author Omay Dogan
 */
 
#include <pch.h>
#include "gtest/gtest.h"
#include <SpartyGnome.h>
#include <Game.h>

/**
 * Test the constructor
 */
TEST(SpartyGnomeTest, Construct){
    Game game;
    SpartyGnome spartyGnome(&game);
}