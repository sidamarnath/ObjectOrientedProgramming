/**
 * @file ActorTest.cpp
 * @author Sid Amarnath
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Actor.h>

TEST(ActorTest, Constructor)
{
    Actor actor(L"Harold");
    ASSERT_EQ(std::wstring(L"Harold"), actor.GetName());
}

TEST(ActorTest, Enabled)
{
    Actor actor(L"Harold");
    ASSERT_TRUE(actor.IsEnabled());
    bool enabled = false;
    actor.SetEnabled(enabled);
    ASSERT_FALSE(actor.IsEnabled());

}

TEST(ActorTest, Clickable)
{
    Actor actor(L"Harold");
    ASSERT_TRUE(actor.IsClickable());
    bool clickable = false;
    actor.SetClickable(clickable);
    ASSERT_FALSE(actor.IsClickable());
}

TEST(ActorTest, Position)
{
    Actor actor(L"Harold");
    auto pos = actor.GetPosition();
    ASSERT_EQ(wxPoint(pos), pos);
    auto newPos = wxPoint();
    actor.SetPosition(newPos);
    ASSERT_EQ(actor.GetPosition(), newPos);
}