/**
 * @file DrawableTest.cpp
 * @author Sid Amarnath
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Drawable.h>
#include <DrawableMock.h>


TEST(DrawableTest, Constructor)
{
    DrawableMock drawable(L"Harold");
    ASSERT_EQ(std::wstring(L"Harold"), drawable.GetName());

}

TEST(DrawableTest, Position)
{
    DrawableMock drawable(L"Harold");
    auto pos = drawable.GetPosition();
    ASSERT_EQ(wxPoint(pos), pos);
    auto newPos = wxPoint();
    drawable.SetPosition(newPos);
    ASSERT_EQ(drawable.GetPosition(), newPos);

}

TEST(DrawableTest, Rotation)
{
    DrawableMock drawable(L"Harold");
    double r = drawable.GetRotation();
    ASSERT_NEAR(0, r, 0.00001);
    double newR = 1.5;
    drawable.SetRotation(newR);
    ASSERT_NEAR(drawable.GetRotation(), newR, 0.00001);

}

TEST(DrawableTest, Association)
{
    DrawableMock body(L"Body");
    auto arm = std::make_shared<DrawableMock>(L"Arm");
    auto leg = std::make_shared<DrawableMock>(L"Leg");

    ASSERT_EQ(nullptr, arm->GetParent());
    ASSERT_EQ(nullptr, leg->GetParent());

    body.AddChild(arm);
    body.AddChild(leg);

    ASSERT_EQ(&body, arm->GetParent());
    ASSERT_EQ(&body, leg->GetParent());
}