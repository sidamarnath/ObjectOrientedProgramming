/**
 * @file CityView.cpp
 * @author Charles B. Owen
 */
#include "pch.h"

#include <sstream>
#include <wx/stdpaths.h>
#include <wx/dcbuffer.h>

#include "ids.h"
#include "CityView.h"

#include "TileLandscape.h"
#include "TileGarden.h"
#include "TileBuilding.h"
#include "TileHive.h"
#include "TileWater.h"
#include "BuildingCounter.h"
#include "HiveVisitor.h"
#include "ResetTileVisitor.h"

#include "CityReport.h"
#include "MemberReport.h"

using namespace std;

/// Initial tile X location
const int InitialX = City::GridSpacing * 5;

/// Initial tile Y location
const int InitialY = City::GridSpacing * 3;

/// Frame duration in milliseconds
const int FrameDuration = 30;

/// Margin of trashcan from side and bottom in pixels
const int TrashcanMargin = 10;

/**
 * Constructor
 * @param mainFrame Pointer to wxFrame object, the main frame for the application
 */
void CityView::Initialize(wxFrame* mainFrame)
{
    Create(mainFrame, wxID_ANY);

    // Determine where the images are stored
    //auto standardPaths = wxStandardPaths::Get();
    wxStandardPaths& standardPaths = wxStandardPaths::Get();
    std::wstring resourcesDir = standardPaths.GetResourcesDir().ToStdWstring();
    mCity.SetImagesDirectory(resourcesDir);

    mTrashcan = make_unique<wxBitmap>(mCity.GetImagesDirectory() + L"/trashcan.png", wxBITMAP_TYPE_ANY);

    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &CityView::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &CityView::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &CityView::OnLeftUp, this);
    Bind(wxEVT_LEFT_DCLICK, &CityView::OnLeftDoubleClick, this);
    Bind(wxEVT_MOTION, &CityView::OnMouseMove, this);
    Bind(wxEVT_TIMER, &CityView::OnTimer, this);


    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);
    mStopWatch.Start();
}


/**
 * Add menus specific to the view
 * @param mainFrame The main frame that owns the menu bar
 * @param menuBar The menu bar to add menus to
 * @param fileMenu The file menu, so we can add to it if we wish
 * @param viewMenu The view menu, so we can add to it if we wish
 */
void CityView::AddMenus(wxFrame* mainFrame, wxMenuBar *menuBar, wxMenu* fileMenu, wxMenu* viewMenu)
{
    // The file and view menus are defined by MainFrame. You can
    // add things to them here.
    //  fileMenu->Append(...)

    //  viewMenu->Append(...)

    auto landscapingMenu = new wxMenu();
    auto buildingsMenu = new wxMenu();
    auto businessesMenu = new wxMenu();

    // Options added to the view menu
    viewMenu->Append(IDM_VIEW_OUTLINES, L"&Outlines", L"Enable to disable drawing outlines", wxITEM_CHECK);
    viewMenu->Append(IDM_VIEW_CITYREPORT, L"&City Report", L"Enable or disable city report", wxITEM_CHECK);
    viewMenu->Append(IDM_VIEW_POPULATION, L"&Population", L"Enable or disable population display", wxITEM_CHECK);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &CityView::OnViewOutlines, this, IDM_VIEW_OUTLINES);
    mainFrame->Bind(wxEVT_UPDATE_UI, &CityView::OnUpdateViewOutlines, this, IDM_VIEW_OUTLINES);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &CityView::OnViewCityReport, this, IDM_VIEW_CITYREPORT);
    mainFrame->Bind(wxEVT_UPDATE_UI, &CityView::OnUpdateViewCityReport, this, IDM_VIEW_CITYREPORT);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &CityView::OnViewPopulation, this, IDM_VIEW_POPULATION);
    mainFrame->Bind(wxEVT_UPDATE_UI, &CityView::OnUpdateViewPopulation, this, IDM_VIEW_POPULATION);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &CityView::OnReset, this, IDM_RESET);


    //
    // Landscaping menu options
    //
    AddTileMenuOption(mainFrame, landscapingMenu, IDM_LANDSCAPING_GRASS, L"&Grass", L"Add a Grass Tile");
    AddTileMenuOption(mainFrame, landscapingMenu, IDM_LANDSCAPING_TALLGRASS, L"&Tall Grass", L"Add a Tall Grass Tile");
    AddTileMenuOption(mainFrame, landscapingMenu, IDM_LANDSCAPING_SPARTYSTATUE, L"&Sparty Statue", L"Add a Sparty Status Tile");
    AddTileMenuOption(mainFrame, landscapingMenu, IDM_LANDSCAPING_TREE, L"Tr&ee", L"Add a Tree Tile");
    AddTileMenuOption(mainFrame, landscapingMenu, IDM_LANDSCAPING_TREES, L"Tree&s", L"Add a Trees Tile");
    AddTileMenuOption(mainFrame, landscapingMenu, IDM_LANDSCAPING_BIGTREES, L"&Big Trees", L"Add a Big Trees Tile");
    AddTileMenuOption(mainFrame, landscapingMenu, IDM_LANDSCAPING_GARDEN, L"G&arden", L"Add a Garden Tile");
    AddTileMenuOption(mainFrame, landscapingMenu, IDM_LANDSCAPING_WATER, L"&Water", L"Add a Water Tile");

    //
    // Buildings menu options
    //
    AddTileMenuOption(mainFrame, buildingsMenu, IDM_BUILDINGS_FARMHOUSE, L"&Farm House", L"Add a Farm House Tile");
    AddTileMenuOption(mainFrame, buildingsMenu, IDM_BUILDINGS_BLACKSMITHSHOP, L"&Blacksmith Shop", L"Add a Blacksmith Shop Tile");
    AddTileMenuOption(mainFrame, buildingsMenu, IDM_BUILDINGS_BROWNHOUSE, L"B&rown House", L"Add a Brown House Tile");
    AddTileMenuOption(mainFrame, buildingsMenu, IDM_BUILDINGS_YELLOWHOUSE, L"&Yellow House", L"Add a Yellow House Tile");
    AddTileMenuOption(mainFrame, buildingsMenu, IDM_BUILDINGS_FIRESTATION, L"F&ire Station", L"Add a Fire Station Tile");
    AddTileMenuOption(mainFrame, buildingsMenu, IDM_BUILDINGS_HOSPITAL, L"&Hospital", L"Add a Hospital Tile");
    AddTileMenuOption(mainFrame, buildingsMenu, IDM_BUILDINGS_MARKET, L"M&arket", L"Add a Market Tile");
    AddTileMenuOption(mainFrame, buildingsMenu, IDM_BUILDINGS_CONDOS, L"&Condos", L"Add a Condos Tile");
    buildingsMenu->AppendSeparator();
    buildingsMenu->Append(IDM_BUILDINGS_COUNT, L"&Count", L"Count the buildings");
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &CityView::OnBuildingsCount, this, IDM_BUILDINGS_COUNT);

    //
    // Businesses menu options
    //
    AddTileMenuOption(mainFrame, businessesMenu, IDM_BUSINESS_HIVE, L"&Hive", L"Add Umbrella Corporation Hive Tile");

    //
    // Append the menus to the menubar
    //
    menuBar->Append(landscapingMenu, L"&Landscaping" );
    menuBar->Append(buildingsMenu, L"&Buildings");
    menuBar->Append(businessesMenu, L"B&usinesses");
}

/**
 * Save the city to a file
 * @param filename
 */
void CityView::Save(wxString filename)
{
    mCity.Save(filename);
}

/**
 * Load the city from a file
 * @param filename
 */
void CityView::Load(wxString filename)
{
    mCity.Load(filename);
    Refresh();
}

/**
 * Append an option to a menu and bind it to the function CityView::OnAddTileMenuOption
 *
 * All of the menu options to add a tile use the same menu handler, which uses
 * a switch based on the ID to determine which option to make. This code cuts the
 * number of lines of code in CityView::AddMenus by about half.
 *
 * @param mainFrame The MainFrame object that owns the menu
 * @param menu The Menu we are adding the option to
 * @param id The Menu option ID
 * @param text Text for the menu option
 * @param help Help for the menu option
 */
void CityView::AddTileMenuOption(wxFrame *mainFrame, wxMenu *menu, int id, std::wstring text, std::wstring help)
{
    menu->Append(id, text, help);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &CityView::OnAddTileMenuOption, this, id);
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void CityView::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxBLACK);
    dc.SetBackground(background);
    dc.Clear();

    // Compute the time that has elapsed
    // since the last call to OnPaint.
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;

    /*
     * Draw the trash can
     */

    auto rect = GetClientRect();

    // Bottom minus image size minus margin is top of the image
    mTrashcanTop = rect.GetHeight() - mTrashcan->GetHeight() - TrashcanMargin;
    mTrashcanRight = TrashcanMargin + mTrashcan->GetWidth();

    dc.DrawBitmap(*mTrashcan, TrashcanMargin, mTrashcanTop);

    mCity.Update(elapsed);
    mCity.OnDraw(&dc);

    if(mOutlines)
    {
        // Draw outlines around each of the on-screen tiles

        //
        // Commented out until the iterator is available
        //

        for (auto tile : mCity)
        {
            wxPen pen(wxColour(0, 255, 0), 2);
            dc.SetPen(pen);
            tile->DrawBorder(&dc);
        }
    }

    if (mReport)
    {
        auto report = mCity.GenerateCityReport();

        float x = 10;
        float y = 10;
        const float dy = 15;

        // Creates a font
        wxFont font(wxSize(0, 14),
                    wxFONTFAMILY_SWISS,
                    wxFONTSTYLE_NORMAL,
                    wxFONTWEIGHT_NORMAL);
        dc.SetFont(font);
        dc.SetTextForeground(*wxCYAN);

        dc.DrawText(L"City Report",  // Text to draw
                    x,     // x coordinate for the left size of the text
                    y);    // y coordinate for the top of the text

        y += dy;

        //
        // Commented out until the iterator is available
        //

        for (auto memberReport : *report)
        {
            dc.DrawText(memberReport->Report().c_str(),
                        x,     // x coordinate for the left size of the text
                        y);    // y coordinate for the top of the text

            y += dy;
        }

    }
}

/**
 * Handle the left mouse button down event
 * @param event
 */
void CityView::OnLeftDown(wxMouseEvent &event)
{
    mGrabbedItem = mCity.HitTest(event.GetX(), event.GetY());
    if (mGrabbedItem != nullptr)
    {
        // We grabbed something
        // Move it to the front
        mCity.MoveToFront(mGrabbedItem);

        Refresh();
    }
}

/**
* Handle the left mouse button down event
* @param event
*/
void CityView::OnLeftUp(wxMouseEvent &event)
{
    OnMouseMove(event);
}

/**
* Handle the mouse move event
* @param event
*/
void CityView::OnMouseMove(wxMouseEvent &event)
{
    // See if an item is currently being moved by the mouse
    if (mGrabbedItem != nullptr)
    {
        // If an item is being moved, we only continue to
        // move it while the left button is down.
        if (event.LeftIsDown())
        {
            mGrabbedItem->SetLocation(event.GetX(), event.GetY());
        }
        else
        {
            // When the left button is released we release
            // the item. If we release it on the trashcan,
            // delete it.
            if (event.GetX() < mTrashcanRight && event.GetY() > mTrashcanTop)
            {
                // We have clicked on the trash can
                mCity.DeleteItem(mGrabbedItem);
            }
            else
            {
                mGrabbedItem->QuantizeLocation();
            }

            mCity.SortTiles();
            mGrabbedItem = nullptr;
        }

        // Force the screen to redraw
        Refresh();
    }
}

/**
 * Handle the left mouse button double-click event
 * @param event
 */
void CityView::OnLeftDoubleClick(wxMouseEvent &event)
{
    // The city has been double-clicked on.
    // The double-click location is in (event.GetX(), event.GetY())
    mGrabbedItem = mCity.HitTest(event.GetX(), event.GetY());
    if (mGrabbedItem != nullptr)
    {
        // Instantiate the visitor
        HiveVisitor visitor;

        // Send to JUST this one tile
        mGrabbedItem->Accept(&visitor);

        // Clear this since we don't want to then drag
        mGrabbedItem = nullptr;
    }

}



/**
 * Menu event handler for all known types of tiles
 * @param event Menu event
 */
void CityView::OnAddTileMenuOption(wxCommandEvent& event)
{
    shared_ptr<Tile> tile;

    switch(event.GetId())
    {
        case IDM_LANDSCAPING_GRASS:
            tile = make_shared<TileLandscape>(&mCity);
            tile->SetImage(L"grass.png");
            break;

        case IDM_LANDSCAPING_TALLGRASS:
            tile = make_shared<TileLandscape>(&mCity);
            tile->SetImage(L"tallgrass.png");
            break;

        case IDM_LANDSCAPING_SPARTYSTATUE:
            tile = make_shared<TileLandscape>(&mCity);
            tile->SetImage(L"sparty.png");
            break;

        case IDM_LANDSCAPING_TREE:
            tile = make_shared<TileLandscape>(&mCity);
            tile->SetImage(L"tree.png");
            break;

        case IDM_LANDSCAPING_TREES:
            tile = make_shared<TileLandscape>(&mCity);
            tile->SetImage(L"tree2.png");
            break;

        case IDM_LANDSCAPING_BIGTREES:
            tile = make_shared<TileLandscape>(&mCity);
            tile->SetImage(L"tree3.png");
            break;

        case IDM_LANDSCAPING_GARDEN:
            tile = make_shared<TileGarden>(&mCity);
            break;

        case IDM_LANDSCAPING_WATER:
            tile = make_shared<TileWater>(&mCity);
            break;

        case IDM_BUILDINGS_FARMHOUSE:
            tile = make_shared<TileBuilding>(&mCity);
            tile->SetImage(L"farm0.png");
            break;

        case IDM_BUILDINGS_BLACKSMITHSHOP:
            tile = make_shared<TileBuilding>(&mCity);
            tile->SetImage(L"blacksmith.png");
            break;

        case IDM_BUILDINGS_BROWNHOUSE:
            tile = make_shared<TileBuilding>(&mCity);
            tile->SetImage(L"house.png");
            break;

        case IDM_BUILDINGS_YELLOWHOUSE:
            tile = make_shared<TileBuilding>(&mCity);
            tile->SetImage(L"yellowhouse.png");
            break;

        case IDM_BUILDINGS_FIRESTATION:
            tile = make_shared<TileBuilding>(&mCity, 20);
            tile->SetImage(L"firestation.png");
            break;

        case IDM_BUILDINGS_HOSPITAL:
            tile = make_shared<TileBuilding>(&mCity, 300);
            tile->SetImage(L"hospital.png");
            break;

        case IDM_BUILDINGS_MARKET:
            tile = make_shared<TileBuilding>(&mCity, 100);
            tile->SetImage(L"market.png");
            break;

        case IDM_BUILDINGS_CONDOS:
            tile = make_shared<TileBuilding>(&mCity, 100);
            tile->SetImage(L"condos.png");
            break;

        //case IDM_BUSINESS_HIVE:
            //tile = make_shared<TileHive>(&mCity);
            //break;
    }

    if(tile != nullptr)
    {
        tile->SetLocation(InitialX, InitialY);
        mCity.Add(tile);
        Refresh();
    }
}

/**
 * Menu event handler View>Outlines menu optino
 * @param event Menu event
 */
void CityView::OnViewOutlines(wxCommandEvent& event)
{
    mOutlines = !mOutlines;
}

/**
 * Update handler for View>Outlines menu option
 * @param event Update event
 */
void CityView::OnUpdateViewOutlines(wxUpdateUIEvent& event)
{
    event.Check(mOutlines);
}

/**
 * Menu event handler View>City Report menu optino
 * @param event Menu event
 */
void CityView::OnViewCityReport(wxCommandEvent& event)
{
    mReport = !mReport;
}

/**
 * Update handler for View>City Report menu option
 * @param event Update event
 */
void CityView::OnUpdateViewCityReport(wxUpdateUIEvent& event)
{
    event.Check(mReport);
}

/**
 * Menu event handler View>City Report menu optino
 * @param event Menu event
 */
void CityView::OnViewPopulation(wxCommandEvent& event)
{
    mCity.FlipViewPopulation();
    Refresh();
}

/**
 * Update handler for View>City Report menu option
 * @param event Update event
 */
void CityView::OnUpdateViewPopulation(wxUpdateUIEvent& event)
{
    event.Check(mCity.IsViewPopulation());
}

/**
 * Handle timer events
 * @param event timer event
 */
void CityView::OnTimer(wxTimerEvent& event)
{
    Refresh();
}

/**
 * Handle the Buildines>Count menu option
 * @param event Menu event
 */
void CityView::OnBuildingsCount(wxCommandEvent& event)
{
    BuildingCounter visitor;
    mCity.Accept(&visitor);
    int cnt = visitor.GetNumBuildings();
    wstringstream str;
    str << L"There are " << cnt << L" buildings.";
    wxMessageBox(str.str().c_str(), L"Building Counter");

}

/**
 * Handle the Menu>Reset menu option
 * @param event Menu event
 */
void CityView::OnReset(wxCommandEvent& event)
{
    ResetTileVisitor visitor;
    mCity.Accept(&visitor);

}




