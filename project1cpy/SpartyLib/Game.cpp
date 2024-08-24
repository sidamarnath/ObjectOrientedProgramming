/**
 * @file Game.cpp
 * @author Sid Amarnath
 */


#include "pch.h"
#include "Game.h"
#include "SpartyGnome.h"
#include "Item.h"
#include "Platform.h"
#include "Villain.h"
#include "Money.h"
#include "TuitionUp.h"
#include "Door.h"
#include <cmath>
#include "cctype"
#include "Collision.h"
#include "Covid.h"
#include "Wall.h"
#include <wx/graphics.h>


using namespace std;

/// Game area height in virtual pixels
const static int Height = 1024;

/// Integer representing alternate key code for spacebar due to an issue with the remote desktop.
const static int AlternateJumpKeyCode = 0; // For some reason, pressing the spacebar gives a keycode of 0, not WXK_SPACE.

/// X position of level 0 start
const int levelZeroStartX = 468;
/// Y position of level 0 start
const int levelZeroStartY = 572;

/// X position of level 1 start
const int levelOneStartX = 852;
/// Y position of level 1 start
const int levelOneStartY = 540;

/// X position of level 2 start
const int levelTwoStartX = 788;
/// Y position of level 2 start
const int levelTwoStartY = 769;

/// X position of level 3 start
const int levelThreeStartX = 788;
/// Y position of level 3 start
const int levelThreeStartY = 796;

/// Integer to represent level 0
const int levelZero = 0;
/// Integer to represent level 1
const int levelOne = 1;
/// Integer to represent level 2
const int levelTwo = 2;
/// Integer to represent level 3
const int levelThree = 3;

///Seconds for which gnome freezes upon contact with COVID
const int gnomeFreeze = 1;


/**
 * Draw the game
 * @param graphics The device context to draw on
 * @param width The width
 * @param height The height
 */
void Game::OnDraw(shared_ptr<wxGraphicsContext> graphics, int width, int height)
{

    //
    // Automatic Scaling
    //
    mScale = double(height) / double(Height);
    graphics->Scale(mScale, mScale);
    auto virtualWidth = (double)width/mScale;

    //Instantiating default background
    // Note: Currently this stretches the image.
    auto bgScaleFactor = mBackground->GetHeight() / Height;
    for (int i = 0; i < ceil(bgScaleFactor * virtualWidth / Height); i++)
    {
        graphics->DrawBitmap(*mBackground,i * mBackground->GetWidth() * bgScaleFactor,0,mBackground->GetWidth() * bgScaleFactor,Height);
    }

    auto gnomeBitmap = mGnome->GetBitmap();

    // Compute the amount to scroll in the X dimension
    auto xOffset = (double)-mGnome->GetX() + virtualWidth / 2.0f; // This is commented out since mGnome is not yet defined

    graphics->PushState();
    graphics->Translate(xOffset, 0);

    // This is where the scrolling draw functions go


    // Draw Items
    if (mCurrentLevel == 0)
    {
        for (auto item : mLevelZeroItems)
        {
            item->Draw(graphics, mScale);
        }
    }
    else if (mCurrentLevel == 1)
    {
        for (auto item : mLevelOneItems)
        {
            item->Draw(graphics, mScale);
        }
    }
    else if (mCurrentLevel == 2)
    {
        for (auto item : mLevelTwoItems)
        {
            item->Draw(graphics, mScale);
        }
    }
    else
    {
        for (auto item : mLevelThreeItems)
        {
            item->Draw(graphics, mScale);
        }
    }

    mGnome->Draw(graphics, mScale);

    graphics->PopState();
    graphics->Translate(0, 0);

    //graphics->DrawBitmap(gnomeBitmap, (virtualWidth- (gnomeBitmap.GetHeight() * mScale)) / 2, mGnome->GetY() - ((gnomeBitmap.GetHeight() * mScale) / 2), gnomeBitmap.GetWidth() * mScale, gnomeBitmap.GetHeight() * mScale);

    wxFont font(wxSize(0, (Height * mScale) / 16), wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    graphics->SetFont(font, wxColour(62, 205, 207));
    graphics->DrawText(L"$" + to_string(mScore), (Height * mScale) / 16, (Height * mScale) / 32);
    graphics->DrawText(TimeDisplay(mSecondsPassed), (width / mScale) - (Height * mScale * 5) / 16, (Height * mScale) / 32);

    wxFont font1(wxSize(100, (Height * mScale) / 8), wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MEDIUM);
    graphics->SetFont(font1, wxColour(0, 0, 255));
    if (mSecondsPassed <= 1)
    {
        graphics->DrawText(L"Level " + to_string(mCurrentLevel) + " Begin", height / 2, Height / 2);
    }

    if (mDeathPauseTimer > 0)
    {
        graphics->DrawText(L"You Lose!", height / 2, Height / 2);
    }

    if (mLevelCompletePauseTimer > 0)
    {

        graphics->DrawText(L"Level Complete!", height / 2, (Height * mScale) / 2);
    }

    if(mLevelEnded)
    {
        graphics->DrawText(L"Level " + to_string(mCurrentLevel) + " Begin", height / 2, Height / 2);
        OnLevelStart(graphics, Height);
    }

}

/**
 * Game Constructor
 * Create Game object, Gnome object, and load the backgrounds
 */
Game::Game()
{
    mOneBackground = make_shared<wxBitmap>(L"../images/backgroundForest.png", wxBITMAP_TYPE_ANY);
    mTwoBackground = make_shared<wxBitmap>(L"../images/backgroundColorGrass.png", wxBITMAP_TYPE_ANY);
    mThreeBackground = make_shared<wxBitmap>(L"../images/backgroundColorDesert.png", wxBITMAP_TYPE_ANY);
    mGnome = make_unique<SpartyGnome>(this); // This is commented because no constructor for SpartyGnome or Item exists yet.
    mGnome->SetLocation(50, 50); // Initial location, should be overwritten to middle of screen, height later
}

// BELOW ARE FUNCTIONS FOR LOADING -> COMMENTED OUT UNTIL ITEMS NECESSARY ARE CREATED

/**
 * Load the game
 * @param filename a level file to load items from
 */
void Game::Load(const wxString &filename)
{
    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load Game file");
        return;
    }
    // Get the XML document root node
    auto root = xmlDoc.GetRoot();

    mGnomeStartX = wxAtoi(root->GetAttribute(L"start-x", L"32"));
    mGnomeStartY = wxAtoi(root->GetAttribute(L"start-y", L"32"));
    mGnome->SetLocation(mGnomeStartX, mGnomeStartY);

    //
    // Traverse the children of the root
    // node of the XML document in memory!!!!
    //
    auto child = root->GetChildren();
    for( ; child; child=child->GetNext())
    {
        auto name = child->GetName();
        if(name == L"items")
        {
            XmlItem(child);
        }
        else
        {
            XmlDeclaration(child);
        }
    }
}

/**
 * Load the nodes contained in the declarations portion of the level xml files
 * @param node
 */
void Game::XmlDeclaration(wxXmlNode *node)
{
    auto name = node->GetName();

    auto child = node->GetChildren();
    for( ; child; child=child->GetNext())
    {
        // A pointer for the item we are loading
        shared_ptr<Item> item;

        // We have an item. What type?
        auto type = child->GetName();

        if (type == L"background")
        {
            wstring imgPath = L"../images/";
            imgPath += node->GetAttribute(L"image", L"backgroundForest.png");
            auto background = make_unique<wxBitmap>(imgPath, wxBITMAP_TYPE_ANY);
            //item = make_shared<Background>(this);
        }
        else if(type == L"platform")
        {
            wstring id;
            id += child->GetAttribute(L"id", L"i012");
            wstring idA = id + L"a";
            wstring idB = id + L"b";
            wstring idC = id + L"c";
            wstring leftImgPath =  L"../images/";
            leftImgPath += child->GetAttribute(L"left-image", L"UofM.png");
            wstring centerImgPath =  L"../images/";
            centerImgPath += child->GetAttribute(L"mid-image", L"UofM.png");
            wstring rightImgPath =  L"../images/";
            rightImgPath += child->GetAttribute(L"right-image", L"UofM.png");

            mIdToImage[idA] = leftImgPath;
            mIdToImage[idB] = centerImgPath;
            mIdToImage[idC] = rightImgPath;
        }
        else if(type == L"money")
        {
            wstring id;
            id += child->GetAttribute(L"id", L"i012");
            wstring imgPath =  L"../images/";
            imgPath += child->GetAttribute(L"image", L"UofM.png");
            int amount = wxAtoi(child->GetAttribute(L"value", L"100"));

            mIdToImage[id] = imgPath;
            mMoneyValue[id] = amount;
        }
        else if(type == L"wall")
        {
            wstring id;
            id += child->GetAttribute(L"id", L"i006");
            wstring imgPath =  L"../images/";
            imgPath += child->GetAttribute(L"image", L"wall1.png");

            mIdToImage[id] = imgPath;
        }
        else
        {
            wstring id;
            id += child->GetAttribute(L"id", L"i012");
            wstring imgPath =  L"../images/";
            imgPath += child->GetAttribute(L"image", L"UofM.png");

            mIdToImage[id] = imgPath;


        }
    }
}

/**
 * Load the nodes contained in the items portion of the level xml files and add them to the correct vectors
 * @param node
 */
void Game::XmlItem(wxXmlNode *node)
{
    auto child = node->GetChildren();
    for( ; child; child=child->GetNext())
    {
        // A pointer for the item we are loading
        shared_ptr<Item> item;

        // We have an item. What type?
        auto type = child->GetName();

        if (type == L"background")
        {
            wstring imgPath = L"../images/";
            imgPath += node->GetAttribute(L"image", L"backgroundForest.png");
            mBackground = make_unique<wxBitmap>(imgPath, wxBITMAP_TYPE_ANY);
            //item = make_shared<Background>(this);
        }
        if (type == L"platform")
        {
            int platformWidth = wxAtoi(child->GetAttribute(L"width", L"128"));
            int platformHeight = wxAtoi(child->GetAttribute(L"height", L"32"));
            int itemX = wxAtoi(child->GetAttribute(L"x", L"128"));
            int itemY = wxAtoi(child->GetAttribute(L"y", L"512"));
            wstring id =L"";
            id += child->GetAttribute(L"id", L"i012");
            item = make_shared<Platform>(this, platformWidth, platformHeight, mIdToImage[id + L"a"], mIdToImage[id + L"b"], mIdToImage[id + L"c"]);
            item->SetLocation(itemX, itemY);
        }
        if (type == L"money")
        {
            wstring id =L"";
            id += child->GetAttribute(L"id", L"i012");
            item = make_shared<Money>(this, mIdToImage[id], mMoneyValue[id]);
        }
        if (type == L"wall")
        {
            int wallWidth = wxAtoi(child->GetAttribute(L"width", L"128"));
            int wallHeight = wxAtoi(child->GetAttribute(L"height", L"32"));
            int itemX = wxAtoi(child->GetAttribute(L"x", L"128"));
            int itemY = wxAtoi(child->GetAttribute(L"y", L"512"));
            wstring id =L"";
            id += child->GetAttribute(L"id", L"i012");
            item = make_shared<Wall>(this, wallWidth, wallHeight, mIdToImage[id]);
            item->SetLocation(itemX, itemY);
            //item = make_shared<Wall>(this);
        }
        if (type == L"tuition-up")
        {
            wstring id =L"";
            id += child->GetAttribute(L"id", L"i012");
            item = make_shared<TuitionUp>(this, mIdToImage[id]);
        }
        if (type == L"villain")
        {
            wstring id =L"";
            id += child->GetAttribute(L"id", L"i012");
            item = make_shared<Villain>(this, mIdToImage[id]);
        }
        if (type == L"covid")
        {
            wstring id =L"";
            id += child->GetAttribute(L"id", L"i014");
            item = make_shared<Covid>(this, mIdToImage[id]);
        }

        if (type == L"door")
        {
            item = make_shared<Door>(this);
        }


        if (item != nullptr)
        {
            Add(item);
            item->XmlLoad(child);

        }
    }

}


/**
 *  Handle updates for animation
 * @param elapsed elapsed time since last frame
 */
void Game::Update(double elapsed)
{
    if(mSecondsPassed <= 1 || mDeathPauseTimer > 0 || mLevelCompletePauseTimer > 0)
    {
        return;
    }
    if (mCurrentLevel == 0)
    {
        for (auto item : mLevelZeroItems)
        {
            item->Update(elapsed);
        }
    }
    else if (mCurrentLevel == 1)
    {
        for (auto item : mLevelOneItems)
        {
            item->Update(elapsed);
        }
    }
    else if (mCurrentLevel == 2)
    {
        for (auto item : mLevelTwoItems)
        {
            item->Update(elapsed);
        }
    }
    else
    {
        for (auto item : mLevelThreeItems)
        {
            item->Update(elapsed);
        }
    }

    mGnome->Update(elapsed);

}

/**
 * Handle the case when user presses a key
 * @param event
 */
void Game::OnKeyDown(wxKeyEvent& event)
{
    wxString uc(event.GetUnicodeKey());
    string input = uc.ToStdString();
    input = tolower(event.GetUnicodeKey());

    if(event.GetKeyCode() == WXK_LEFT || input == "A" || input == "a")
    {
        mGnome->MoveLeftDown();
    }

    else if(event.GetKeyCode() == WXK_RIGHT || input == "D" || input == "d")
    {
        mGnome->MoveRightDown();
    }



}

/**
 * Handle the event when user releases a key
 * @param event
 */
void Game::OnKeyUp(wxKeyEvent& event)
{
    wxString uc(event.GetUnicodeKey());
    string input = uc.ToStdString();
    input = tolower(event.GetUnicodeKey());

    // Left arrow or A key
    if(event.GetKeyCode() == WXK_LEFT || input == "A" || input == "a")
    {
        mGnome->MoveLeftUp();
    }

    else if(event.GetKeyCode() == WXK_RIGHT || input == "D" || input == "d")
    {
        mGnome->MoveRightUp();
    }

    if(event.GetKeyCode() == WXK_SPACE || event.GetKeyCode() == AlternateJumpKeyCode)
    {
        mGnome->Jump();
    }
}

/**
 * TimeDisplay
 * @param time The number of seconds
 * @return A string with the number of seconds displayed as time
 */
string Game::TimeDisplay(int time)
{
    string timeString = "";
    if (time / 3600 != 0) timeString += (to_string(time / 3600) + ":");
    timeString += to_string(time / 60) + ":";
    if (time % 60 < 10)
    {
        timeString += ("0" + to_string(time % 60));
    }
    else
    {
        timeString += to_string(time % 60);
    }
    return timeString;
}

/**
 * Update the time whenever the timer reaches 1 second
 */
void Game::TimerRefresh()
{
    if (mSecondsPassed > mGnomeUnfreezeTime) mGnome->SetAcceptingInput(true);

    if (mSecondsPassed < 0.1)
    {
        ReturnGnomeToStart();
        mGnome->Reset();
    }

    if(mDeathPauseTimer > 0)
    {
        mDeathPauseTimer--;
        if(mDeathPauseTimer == 0)
        {
            UpdateLevel(mCurrentLevel);
            mGnome->Reset();
            ReturnGnomeToStart();
        }
    }

    if(mLevelCompletePauseTimer > 0)
    {
        mLevelCompletePauseTimer--;
        if(mLevelCompletePauseTimer <= 0)
        {
            mLevelCompletePauseTimer = 0;
            UpdateLevel(mCurrentLevel + 1);
            mGnome->Reset();
            ReturnGnomeToStart();
        }
    }

    mSecondsPassed++;
}

/**
 * Adds the item to the mItems vector for each level.
 * @param item A pointer to the item to be added.
 */
void Game::Add(std::shared_ptr<Item> item)
{
    if (mCurrentLevel == 0)
    {
        mLevelZeroItems.push_back(item);
    }
    else if (mCurrentLevel == 1)
    {
        mLevelOneItems.push_back(item);
    }
    else if (mCurrentLevel == 2)
    {
        mLevelTwoItems.push_back(item);
    }
    else
    {
        mLevelThreeItems.push_back(item);
    }
}

/**
 * Tests to see if item is colliding with anything else in mItems.
 * @param item We are testing collision with this item
 * @return A Vector with X and Y components. If a component is 0, no collision occurred. Otherwise, component is +- 1, with sign determining direction of collision, or 2 to indicate a collision in both directions.
 */
shared_ptr<Collision> Game::CollisionTest(Item *item)
{

    double xLoc = 0;
    double yLoc = 0;
    double width = 0;
    double height = 0;
    bool collided = false;

    if (mCurrentLevel == 0)
    {
        for(auto items: mLevelZeroItems)
        {
            if(items->CollisionTest(item))
            {
                xLoc = items->GetX();
                yLoc = items->GetY();
                width = items->GetWidth();
                height = items->GetHeight();
                collided = true;
            }
        }
    }
    else if (mCurrentLevel == 1)
    {
        for(auto items: mLevelOneItems)
        {
            if(items->CollisionTest(item))
            {
                xLoc = items->GetX();
                yLoc = items->GetY();
                width = items->GetWidth();
                height = items->GetHeight();
                collided = true;
            }
        }
    }
    else if (mCurrentLevel == 2)
    {
        for(auto items: mLevelTwoItems)
        {
            if(items->CollisionTest(item))
            {
                xLoc = items->GetX();
                yLoc = items->GetY();
                width = items->GetWidth();
                height = items->GetHeight();
                collided = true;
            }
        }
    }
    else
    {
        for(auto items: mLevelThreeItems)
        {
            if(items->CollisionTest(item))
            {
                xLoc = items->GetX();
                yLoc = items->GetY();
                width = items->GetWidth();
                height = items->GetHeight();
                collided = true;
            }
        }
    }
    if(collided)
    {
        shared_ptr<Collision> col;
        col = make_shared<Collision>();
        col->SetLocation(xLoc, yLoc);
        col->SetWidth(width);
        col->SetHeight(height);

        return col;
    }

    return nullptr;

}

/**
 * Change the current level the game is on
 * @param newLevel
 */
void Game::UpdateLevel(const int newLevel)
{
    mCurrentLevel = newLevel;
    if (mCurrentLevel > levelThree)
    {
        mCurrentLevel = levelThree;
    }
    mScore = 0;
    mSecondsPassed = 0;
    mTuitionMultiplier = 1;
    if (newLevel == 0 || newLevel == 1)
    {
        mBackground = mOneBackground;
        for (auto item : mLevelOneItems)
        {
            item->Reset();
        }
    }
    if (newLevel == 2)
    {
        mBackground = mTwoBackground;
        for (auto item : mLevelTwoItems)
        {
            item->Reset();
        }
    }
    if (mCurrentLevel == 3)
    {
        mBackground = mThreeBackground;
        for (auto item : mLevelThreeItems)
        {
            item->Reset();
        }
    }
    mGnome->SetAcceptingInput(true);
}

/**
 * Function Returns Gnome to the Start position of the current level
 */
void Game::ReturnGnomeToStart()
{
    if (mCurrentLevel == levelZero)
    {
        mGnome->SetLocation(levelZeroStartX, levelZeroStartY);
    }
    if (mCurrentLevel == levelOne)
    {
        mGnome->SetLocation(levelOneStartX, levelOneStartY);
    }
    if (mCurrentLevel == levelTwo)
    {
        mGnome->SetLocation(levelTwoStartX, levelTwoStartY);
    }
    if (mCurrentLevel == levelThree)
    {
        mGnome->SetLocation(levelThreeStartX, levelThreeStartY);
    }
}

/**
 * Add money count to the score
 * @param amount dollar amount to be added to mScore
 */
void Game::CollectedMoney(int amount)
{
    mScore += amount * mTuitionMultiplier;
}

/**
* Increase tuition value by a specified value after Stanley collision
 * @param multiplier Value by which tuition is multiplied, is 1.1 from constant
*/
void Game::TuitionIncrease(float multiplier)
{
    mTuitionMultiplier *= multiplier;
}

/**
 * Handle a level ending
 */
void Game::OnLevelCompleted()
{
    mLevelCompletePauseTimer = 2;
}

/**
 * Start a level
 * @param graphics Graphics context upon which level is drawn
 * @param height of level in pixels
 */
void Game::OnLevelStart(shared_ptr<wxGraphicsContext> graphics, int height)
{
    UpdateLevel(mCurrentLevel + 1);
    ReturnGnomeToStart();
    mLevelEnded = false;

}

/**
 * Function that handles when the gnome dies
 */
void Game::GnomeDeath()
{
    mDeathPauseTimer = 2;
}

/**
* Function that freezes SpartyGnome for gnomeFreeze seconds
*/
void Game::GnomeFreeze()
{
    mGnome->SetAcceptingInput(false);

    mGnomeUnfreezeTime = mSecondsPassed + gnomeFreeze;
}