/*******************************************************************************************
*
*   ChibiManager v1.0.0 - Tool Description
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 raylib technologies. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/
#include <unistd.h>
#include <raylib.h>
#include <string.h>
#include "tinyfiledialogs/tinyfiledialogs.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui/src/raygui.h"

char *home;
const char *WindowBox000Text = "Spawn Chibi";
const char *CloseButtonText = "#05#Close";
const char *SpawnButtonText = "Spawn Chibi";
const char *Label004Text = "Image Path:";
const char *Label006Text = "x";
const char *Label008Text = "Dimensions:";
const char *Label011Text = "x";
const char *Label012Text = "Position:";
const char *HideOnHoverText = "";
const char *Label014Text = "Hide on Hover:";
const char *Label017Text = "CGID:";
const char *GroupBox018Text = "Shared Chibis (WIP)";
const char *Label019Text = "Server:";
const char *GetSizeFromImageText = "Get Size";

Vector2 anchor01 = {0, 0};
Vector2 anchor02 = {72, 216};

bool WindowBox000Active = true;
bool TextBox003EditMode = false;
char ChibiPath[4096] = "/path/to/file";
bool ChibiWidthEditMode = false;
int ChibiWidthValue = 0;
bool ChibiHeightEditMode = false;
int ChibiHeightValue = 0;
bool XPosEditMode = false;
int XPosValue = 0;
bool YPosEditMode = false;
int YPosValue = 0;
bool HideOnHoverChecked = false;
bool CGIDEditMode = false;
char CGIDText[128] = "123456789ABCDEFGHIJK";
bool ChibiIndexEditMode = false;
int ChibiIndexValue = 0;
bool ServerIPEditMode = false;
char ServerIPText[128] = "192.168.122.6/cgi-bin/cgi";
bool showMessageBox;
bool launch = false;
char buf[2048];
//----------------------------------------------------------------------------------
// Controls Functions Declaration
//----------------------------------------------------------------------------------
static void CloseButton();

static void SpawnButton();

static void GetSizeFromImage();

static void PickFile();

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main() {
#ifdef _WIN32
    home = getenv("LocalAppData");
#else
    home = getenv("HOME");
#endif

    // Initialization
    //---------------------------------------------------------------------------------------
    int screenWidth = 480;
    int screenHeight = 408;
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    InitWindow(screenWidth, screenHeight, "chibi_manager");

    // chibi_manager: controls initialization
    //----------------------------------------------------------------------------------

    //----------------------------------------------------------------------------------

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
    GuiLoadStyle("../raygui/styles/bluish/style_bluish.rgs");

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Implement required update logic
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        // raygui: controls drawing
        //----------------------------------------------------------------------------------
        if (WindowBox000Active) {
            WindowBox000Active = !GuiWindowBox((Rectangle){anchor01.x + 0, anchor01.y + 0, 480, 408}, WindowBox000Text);
            if (GuiButton((Rectangle){anchor01.x + 336, anchor01.y + 360, 120, 24}, CloseButtonText)) CloseButton();
            if (GuiButton((Rectangle){anchor01.x + 24, anchor01.y + 360, 120, 24}, SpawnButtonText)) SpawnButton();
            if (GuiTextBox((Rectangle){anchor01.x + 168, anchor01.y + 48, 232, 24}, ChibiPath, 4096,
                           TextBox003EditMode))
                TextBox003EditMode = !TextBox003EditMode;
            GuiLabel((Rectangle){anchor01.x + 72, anchor01.y + 48, 96, 24}, Label004Text);
            if (GuiValueBox((Rectangle){anchor01.x + 168, anchor01.y + 96, 72, 24}, nullptr, &ChibiWidthValue, 0, 9999,
                            ChibiWidthEditMode))
                ChibiWidthEditMode = !ChibiWidthEditMode;
            GuiLabel((Rectangle){anchor01.x + 240, anchor01.y + 96, 12, 24}, Label006Text);
            if (GuiValueBox((Rectangle){anchor01.x + 248, anchor01.y + 96, 72, 24}, nullptr, &ChibiHeightValue, 0, 9999,
                            ChibiHeightEditMode))
                ChibiHeightEditMode = !ChibiHeightEditMode;
            GuiLabel((Rectangle){anchor01.x + 72, anchor01.y + 96, 96, 24}, Label008Text);
            if (GuiValueBox((Rectangle){anchor01.x + 168, anchor01.y + 144, 72, 24}, nullptr, &XPosValue, 0, 9999,
                            XPosEditMode))
                XPosEditMode = !XPosEditMode;
            if (GuiValueBox((Rectangle){anchor01.x + 248, anchor01.y + 144, 72, 24}, nullptr, &YPosValue, 0, 9999,
                            YPosEditMode))
                YPosEditMode = !YPosEditMode;
            GuiLabel((Rectangle){anchor01.x + 240, anchor01.y + 144, 12, 24}, Label011Text);
            GuiLabel((Rectangle){anchor01.x + 72, anchor01.y + 144, 96, 24}, Label012Text);
            GuiCheckBox((Rectangle){anchor01.x + 168, anchor01.y + 192, 24, 24}, HideOnHoverText, &HideOnHoverChecked);
            GuiLabel((Rectangle){anchor01.x + 72, anchor01.y + 192, 96, 24}, Label014Text);
            if (GuiTextBox((Rectangle){anchor02.x + 96, anchor02.y + 72, 208, 24}, CGIDText, 128, CGIDEditMode))
                CGIDEditMode = !CGIDEditMode;
            if (GuiValueBox((Rectangle){anchor02.x + 312, anchor02.y + 72, 24, 24}, nullptr, &ChibiIndexValue, 0, 9999,
                            ChibiIndexEditMode))
                ChibiIndexEditMode = !ChibiIndexEditMode;
            GuiLabel((Rectangle){anchor02.x + 0, anchor02.y + 72, 48, 24}, Label017Text);
            GuiGroupBox((Rectangle){anchor02.x + -24, anchor02.y + 16, 384, 104}, GroupBox018Text);
            GuiLabel((Rectangle){anchor02.x + 0, anchor02.y + 24, 48, 24}, Label019Text);
            if (GuiTextBox((Rectangle){anchor02.x + 96, anchor02.y + 24, 240, 24}, ServerIPText, 128, ServerIPEditMode))
                ServerIPEditMode = !ServerIPEditMode;
            if (GuiButton((Rectangle){336, 96, 72, 24}, GetSizeFromImageText)) GetSizeFromImage();
            if (showMessageBox) {
                int result = GuiMessageBox((Rectangle){
                                               (float) screenWidth / 2 - 125, (float) screenHeight / 2 - 50, 250, 100
                                           },
                                           "Invalid Image!!", "Make sure that your path is correct or it's a valid Image !!", "Understood!");
                if (result >= 0) showMessageBox = false;
            }
            if (GuiButton((Rectangle){anchor01.x + 408, anchor01.y + 48, 24, 24}, "#05#")) PickFile();
        } else
            break;


        //----------------------------------------------------------------------------------

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    if (launch) {
        sprintf(buf, "chibi %s -f %s -p %dx%d -s %dx%d", (HideOnHoverChecked ? "-t" : ""), ChibiPath, XPosValue,
                YPosValue, ChibiWidthValue, ChibiHeightValue);
        TraceLog(LOG_INFO, buf);
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    if (launch) {
        if (fork() == 0) {
            char *array[] = {"/bin/sh", "-c", buf, nullptr};
            extern char **environ;
            execve("/bin/sh", array, environ);
        }
    }
    return 0;
}

//------------------------------------------------------------------------------------
// Controls Functions Definitions (local)
//------------------------------------------------------------------------------------
static void CloseButton() {
    WindowBox000Active = false;
}

static void SpawnButton() {
    if (ChibiPath[0] == '~') {
        strncpy(buf, home, 510);
        strncat(buf, ChibiPath + 1, 2048 - 510);
        strncpy(ChibiPath, buf, 2048);
    }
    Image tmp = LoadImage(ChibiPath);
    if (!IsImageValid(tmp))
        showMessageBox = true;
    else {
        TraceLog(LOG_INFO, "Spawning : %s at %dx%d size %dx%d. %s", ChibiPath, XPosValue, YPosValue, ChibiWidthValue,
                 ChibiHeightValue, HideOnHoverChecked ? "Hide on Hover" : "Do not Hide on Hover");
        UnloadImage(tmp);
        launch = true;
        WindowBox000Active = false;
    }
}

static void GetSizeFromImage() {
    if (ChibiPath[0] == '~') {
        strncpy(buf, home, 510);
        strncat(buf, ChibiPath + 1, 2048 - 510);
        strncpy(ChibiPath, buf, 2048);
    }
    Image tmp = LoadImage(ChibiPath);
    if (!IsImageValid(tmp))
        showMessageBox = true;
    else {
        ChibiWidthValue = tmp.width;
        ChibiHeightValue = tmp.height;
        UnloadImage(tmp);
    }
}

static void PickFile() {
    char *path = tinyfd_openFileDialog("Pick Chibi", "../", 0, nullptr, nullptr, 0);
    if (path != nullptr) {
        Image tmp = LoadImage(path);
        if (!IsImageValid(tmp))
            showMessageBox = true;
        else
            strncpy(ChibiPath,path,4095);
    }
}
