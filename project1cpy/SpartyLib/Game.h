/**
 * @file Game.h
 * @author Sid Amarnath
 *
 *
 */

#ifndef PROJECT1_GAME_H
#define PROJECT1_GAME_H

#include "SpartyGnome.h"
#include "Item.h"
#include "Vector.h"
#include <string>
#include <map>


class Collision;

/**
 * Game class
 */
class Game {
private:
    /// Background image currently being drawn on the frame
    std::shared_ptr<wxBitmap> mBackground;
    /// Background image for level 1 (Also used by level 0)
    std::shared_ptr<wxBitmap> mOneBackground;
    /// Background image for level 2
    std::shared_ptr<wxBitmap> mTwoBackground;
    /// Background image for level 3
    std::shared_ptr<wxBitmap> mThreeBackground;

    /// Scale used for drawing the window
    double mScale = 0;
    /// Height of the window
    const static int Height = 1024;

    /// current level the game is playing
    int mCurrentLevel = 0;

    /// seconds since the level started
    int mSecondsPassed = 0;
    /// timer to pause the game until it hits zero when player dies
    int mDeathPauseTimer = 0;
    /// timer to pause the until it hits zero when level is completed
    int mLevelCompletePauseTimer = 0;

    /// player score for the current level
    int mScore = 0;

    /// All of the items in level Zero
    std::vector<std::shared_ptr<Item>> mLevelZeroItems;
    /// All of the items in level One
    std::vector<std::shared_ptr<Item>> mLevelOneItems;
    /// All of the items in level Two
    std::vector<std::shared_ptr<Item>> mLevelTwoItems;
    /// All of the items in level Three
    std::vector<std::shared_ptr<Item>> mLevelThreeItems;

    ///The Gnome object controlled by the player
    std::unique_ptr<SpartyGnome> mGnome;

    /// Container that associates item id's and their image names
    std::map<std::wstring , std::wstring> mIdToImage;

    /// Container that associates money id and its value
    std::map<std::wstring , int> mMoneyValue;

    /// Starting X coordinate of SpartyGnome
    int mGnomeStartX = 0;

    /// Starting Y coordinate of SpartyGnome
    int mGnomeStartY = 0;

    /// Multiplier for tuition
    float mTuitionMultiplier = 1;

    ///boolean for if level ended
    bool mLevelEnded;

    ///freezing level integer
    int mGnomeUnfreezeTime = 0;
public:
    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);

    /**
    * Game Constructor
    */
    Game();

    /// Copy constructor (disabled)
    Game(const Game &) = delete;

    /// Assignment operator
    void operator=(const Game &) = delete;

    void Load(const wxString &filename);

    void XmlDeclaration(wxXmlNode *node);

    void XmlItem(wxXmlNode* node);

    std::string TimeDisplay(int time);

    void TimerRefresh();

    void Update(double elapsed);

    void OnKeyDown(wxKeyEvent& event);
    void OnKeyUp(wxKeyEvent& event);

    void Add(std::shared_ptr<Item> item);

    std::shared_ptr<Collision> CollisionTest(Item *item);

    void UpdateLevel(const int newLevel);

    void ReturnGnomeToStart();

    void CollectedMoney(int amount);

    void TuitionIncrease(float multiplier);

    void OnLevelCompleted();

    void OnLevelStart(std::shared_ptr<wxGraphicsContext> graphics, int height);

    void GnomeDeath();
    void GnomeFreeze();

    /**
     * Game object tuition multiplier
     * @return mTuitionMultiplier float
     */
    float GetTuitionMultiplier() {return mTuitionMultiplier;}
};

#endif //PROJECT1_GAME_H
