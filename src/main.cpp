// CMake-generated header containing timestamp of the build
#include "build_timestamp.h"

#include "imgui-extra/imgui_impl.h"
#include "imgui/imgui_internal.h"

#include "IconsFontAwesome5.h"
#include "IconsFontAwesome5Brands.h"

#define SDL_DISABLE_ARM_NEON_H 1
#include <SDL.h>
#include <SDL_opengl.h>

#include <array>
#include <cmath>
#include <fstream>
#include <functional>
#include <map>
#include <sstream>
#include <vector>
#include <memory>
#include <algorithm>
#include <chrono>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/bind.h>
#else
#define EMSCRIPTEN_KEEPALIVE
#endif

#include "imgui-helpers.h"

//
// Constants
//

using TColor = uint32_t;

const auto kTitle          = "УЪРДЪЛ";
const auto kTitleClipboard = "Уърдъл 🇧🇬";
const auto kURL            = "wordle-bg.ggerganov.com";
const auto kHashtag        = "#уърдъл";
const auto kFontScale      = 3.0f;

// animation time in seconds
const float kTimeFlip       = 0.35f; // cell flip on submit
const float kTimeFill       = 0.50f; // cell flip on submit
const float kTimeBump       = 0.10f; // cell bump on key press
const float kTimeShake      = 0.50f; // cell shake on incorrect input
const float kTimeShow       = 0.20f; // time to show popup window
const float kTimeGuessed    = 2.00f; // time to display text upon correct answer
const float kTimeClipboard  = 2.00f; // time to display text about result being copied to the clipboard
const float kTimeIncorrect  = 1.00f; // time to display text about incorrect input
const float kTimeInitialize = 2.00f; // time to initialize the UI

// timestamp of the first puzzle
// 15 Jan 2022 00:00:00
const int64_t kTimestamp0 = 1642197600;

// available color themes
enum class EColorTheme {
    Light,
    Dark,
};

// colors
enum class EColor {
    Title,
    Text,
    TextSubmitted,
    Background,
    EmptyBorder,
    EmptyFill,
    PendingBorder,
    PendingFill,
    AbsentBorder,
    AbsentFill,
    PresentBorder,
    PresentFill,
    CorrectBorder,
    CorrectFill,
    KeyboardUnused,
};

using TColorTheme = std::map<EColor, TColor>;

const std::map<EColorTheme, TColorTheme> kColorThemes = {
    {
        EColorTheme::Light, {
            { EColor::Title,          ImGui::ColorConvertFloat4ToU32({ float(0x1A)/256.0f, float(0x1A)/256.0f, float(0x1B)/256.0f, 1.00f }), },
            { EColor::Text,           ImGui::ColorConvertFloat4ToU32({ float(0x1A)/256.0f, float(0x1A)/256.0f, float(0x1B)/256.0f, 1.00f }), },
            { EColor::TextSubmitted,  ImGui::ColorConvertFloat4ToU32({ float(0xFF)/256.0f, float(0xFF)/256.0f, float(0xFF)/256.0f, 1.00f }), },
            { EColor::Background,     ImGui::ColorConvertFloat4ToU32({ float(0xFF)/256.0f, float(0xFF)/256.0f, float(0xFF)/256.0f, 1.00f }), },
            { EColor::PendingBorder,  ImGui::ColorConvertFloat4ToU32({ float(0x56)/256.0f, float(0x57)/256.0f, float(0x58)/256.0f, 1.00f }), },
            { EColor::PendingFill,    ImGui::ColorConvertFloat4ToU32({ float(0x56)/256.0f, float(0x57)/256.0f, float(0x58)/256.0f, 0.00f }), },
            { EColor::EmptyBorder,    ImGui::ColorConvertFloat4ToU32({ float(0xD3)/256.0f, float(0xD6)/256.0f, float(0xDA)/256.0f, 1.00f }), },
            { EColor::EmptyFill,      ImGui::ColorConvertFloat4ToU32({ float(0x00)/256.0f, float(0x00)/256.0f, float(0x00)/256.0f, 0.00f }), },
            { EColor::AbsentBorder,   ImGui::ColorConvertFloat4ToU32({ float(0x78)/256.0f, float(0x7C)/256.0f, float(0x7E)/256.0f, 1.00f }), },
            { EColor::AbsentFill,     ImGui::ColorConvertFloat4ToU32({ float(0x78)/256.0f, float(0x7C)/256.0f, float(0x7E)/256.0f, 1.00f }), },
            { EColor::PresentBorder,  ImGui::ColorConvertFloat4ToU32({ float(0xC9)/256.0f, float(0xB4)/256.0f, float(0x58)/256.0f, 1.00f }), },
            { EColor::PresentFill,    ImGui::ColorConvertFloat4ToU32({ float(0xC9)/256.0f, float(0xB4)/256.0f, float(0x58)/256.0f, 1.00f }), },
            { EColor::CorrectBorder,  ImGui::ColorConvertFloat4ToU32({ float(0x6A)/256.0f, float(0xAA)/256.0f, float(0x64)/256.0f, 1.00f }), },
            { EColor::CorrectFill,    ImGui::ColorConvertFloat4ToU32({ float(0x6A)/256.0f, float(0xAA)/256.0f, float(0x64)/256.0f, 1.00f }), },
            { EColor::KeyboardUnused, ImGui::ColorConvertFloat4ToU32({ float(0xD3)/256.0f, float(0xD6)/256.0f, float(0xDA)/256.0f, 1.00f }), },
        },
    },
    {
        EColorTheme::Dark, {
            { EColor::Title,          ImGui::ColorConvertFloat4ToU32({ float(0xD7)/256.0f, float(0xDA)/256.0f, float(0xDC)/256.0f, 1.00f }), },
            { EColor::Text,           ImGui::ColorConvertFloat4ToU32({ float(0xD7)/256.0f, float(0xDA)/256.0f, float(0xDC)/256.0f, 1.00f }), },
            { EColor::TextSubmitted,  ImGui::ColorConvertFloat4ToU32({ float(0xD7)/256.0f, float(0xDA)/256.0f, float(0xDC)/256.0f, 1.00f }), },
            { EColor::Background,     ImGui::ColorConvertFloat4ToU32({ float(0x12)/256.0f, float(0x12)/256.0f, float(0x13)/256.0f, 1.00f }), },
            { EColor::PendingBorder,  ImGui::ColorConvertFloat4ToU32({ float(0x56)/256.0f, float(0x57)/256.0f, float(0x58)/256.0f, 1.00f }), },
            { EColor::PendingFill,    ImGui::ColorConvertFloat4ToU32({ float(0x56)/256.0f, float(0x57)/256.0f, float(0x58)/256.0f, 0.00f }), },
            { EColor::EmptyBorder,    ImGui::ColorConvertFloat4ToU32({ float(0x3A)/256.0f, float(0x3A)/256.0f, float(0x3C)/256.0f, 1.00f }), },
            { EColor::EmptyFill,      ImGui::ColorConvertFloat4ToU32({ float(0x00)/256.0f, float(0x00)/256.0f, float(0x00)/256.0f, 0.00f }), },
            { EColor::AbsentBorder,   ImGui::ColorConvertFloat4ToU32({ float(0x3A)/256.0f, float(0x3A)/256.0f, float(0x3A)/256.0f, 1.00f }), },
            { EColor::AbsentFill,     ImGui::ColorConvertFloat4ToU32({ float(0x3A)/256.0f, float(0x3A)/256.0f, float(0x3A)/256.0f, 1.00f }), },
            { EColor::PresentBorder,  ImGui::ColorConvertFloat4ToU32({ float(0xB5)/256.0f, float(0x9F)/256.0f, float(0x3B)/256.0f, 1.00f }), },
            { EColor::PresentFill,    ImGui::ColorConvertFloat4ToU32({ float(0xB5)/256.0f, float(0x9F)/256.0f, float(0x3B)/256.0f, 1.00f }), },
            { EColor::CorrectBorder,  ImGui::ColorConvertFloat4ToU32({ float(0x53)/256.0f, float(0x8D)/256.0f, float(0x4E)/256.0f, 1.00f }), },
            { EColor::CorrectFill,    ImGui::ColorConvertFloat4ToU32({ float(0x53)/256.0f, float(0x8D)/256.0f, float(0x4E)/256.0f, 1.00f }), },
            { EColor::KeyboardUnused, ImGui::ColorConvertFloat4ToU32({ float(0x81)/256.0f, float(0x83)/256.0f, float(0x84)/256.0f, 1.00f }), },
        },
    },
};

// used for the fade in/out effects
const ImVec4 kColorFade = { float(0x00)/256.0f, float(0x00)/256.0f, float(0x00)/256.0f, 0.50f };

// special keys
const auto kInputEnter     = ICON_FA_CHECK;
const auto kInputBackspace = ICON_FA_BACKSPACE;

const std::vector<std::string> kAlphabet = {
    "А", "Б", "В", "Г", "Д", "Е", "Ж", "З", "И", "Й", "К", "Л", "М", "Н", "О", "П", "Р", "С", "Т", "У", "Ф", "Х", "Ц", "Ч", "Ш", "Щ", "Ъ", "Ь", "Ю", "Я",
};

// the keyboard layouts on the screen
enum class EKeyboardType {
    Phonetic,
    BDS,
};

using TKeyboard = std::vector<std::vector<std::string>>;

const TKeyboard kKeyboardBDS = {
    { "У", "Е", "И", "Ш", "Щ", "К", "С", "Д", "З", "Ц", "Б", },
    { "Ь", "Я", "А", "О", "Ж", "Г", "Т", "Н", "В", "М", "Ч", },
    { kInputEnter, "Ю", "Й", "Ъ", "Ф", "Х", "П", "Р", "Л", kInputBackspace, },
};

const TKeyboard kKeyboardPhonetic = {
    { "Я", "В", "Е", "Р", "Т", "Ъ", "У", "И", "О", "П", "Ю", },
    { "А", "С", "Д", "Ф", "Г", "Х", "Й", "К", "Л", "Ш", "Щ", },
    { kInputEnter, "З", "Ь", "Ц", "Ж", "Б", "Н", "М", "Ч", kInputBackspace, },
};

const std::map<EKeyboardType, TKeyboard> kKeyboards = {
    { EKeyboardType::Phonetic, kKeyboardPhonetic, },
    { EKeyboardType::BDS,      kKeyboardBDS,      },
};

// emojis for sharing results
const std::map<TColor, std::string> kGridEmojis = {
    { kColorThemes.at(EColorTheme::Light).at(EColor::AbsentFill),  "⬜" },
    { kColorThemes.at(EColorTheme::Light).at(EColor::PresentFill), "🟨" },
    { kColorThemes.at(EColorTheme::Light).at(EColor::CorrectFill), "🟩" },
    { kColorThemes.at(EColorTheme::Dark).at(EColor::AbsentFill),  "⬛" },
    { kColorThemes.at(EColorTheme::Dark).at(EColor::PresentFill), "🟨" },
    { kColorThemes.at(EColorTheme::Dark).at(EColor::CorrectFill), "🟩" },
};

namespace {

// poor-man's handling of cyrillic strings:

// get i'th character from utf-8 string
std::string utf8_ch(const std::string & str, int i) {
    return { str[2*i + 0], str[2*i + 1] };
}

// compare i'th character from str0 with j'th character in str1
bool utf8_cmp(const std::string & str0, int i, const std::string & str1, int j) {
    return str0[2*i + 0] == str1[2*j + 0] && str0[2*i + 1] == str1[2*j + 1];
}

// erase last utf-8 char
void utf8_erase_back(std::string & str) {
    str.pop_back();
    str.pop_back();
}

// number of utf-8 letters
std::size_t utf8_size(const std::string & str) {
    return str.size()/2;
}

// map a time point t with period T to [0, 1]
float I(float t, float T) {
    return std::max(0.0f, std::min(1.0f, t/T));
}

// is t within [t0, t0 + T]
bool within(float t, float t0, float T) {
    return (t0 <= t) && (t <= t0 + T);
}

//
// JS interface
//

// initialize initial puzzle
std::function<bool()> g_doPuzzleInit;

// initialize the game state
std::function<bool()> g_doGameInit;

// set new window size
std::function<void(int, int)> g_setWindowSize;

// main game loop
std::function<bool()> g_mainUpdate;

// provide pressed keys
std::function<void(const std::string & )> g_input;

// called from JS to get the ID of the current puzzle
std::function<int()> g_getPuzzleId;

// set attempted words so far for a puzzle
// called at the start of the game to initialize data from the localStorage
std::function<void(int, const std::string & )> g_setAttempts;

// called from JS to query for any new recorder attempts
// returns empty string if there are no new attempts
std::function<std::string()> g_getAttempts;

// set the accumulated statistics for the current player
// called at the start of the game to initialize data from the localStorage
std::function<void(const std::string & )> g_setStatistics;

// called from JS to query for any new player statistics
// returns empty string if there are no changes to the player's stats
std::function<std::string()> g_getStatistics;

// called at the start of the game to initialize settings from the localStorage
std::function<void(const std::string & )> g_setSettings;

// called from JS to get any changes to the settings
// returns empty string if no changes to the settings have ocurred
std::function<std::string()> g_getSettings;

// called from JS to check if the "Share" button has been pressed
// returns a string with emojies representing the player's attempts to guess the word
std::function<std::string()> g_getClipboard;

// called from JS to show/hide the "Results copied to clipboard" text
std::function<void(bool)> g_setClipboardTextVisible;

// called from JS to check if an URL has been clicked
// returns a string with the URL address
std::function<std::string()> g_getURL;

// set the initial timestamp at which the game was started
std::function<void(int64_t)> g_setTimestamp;

#ifdef __EMSCRIPTEN__
// need this wrapper of the main loop for the emscripten_set_main_loop_arg() call
void mainUpdate(void *) {
    g_mainUpdate();
}

// These functions are used to pass data back and forth between the JS and the C++ code

EMSCRIPTEN_BINDINGS(wordle) {
    emscripten::function("do_puzzle_init",             emscripten::optional_override([]() -> int                                 { return g_doPuzzleInit(); }));
    emscripten::function("do_game_init",               emscripten::optional_override([]() -> int                                 { return g_doGameInit(); }));
    emscripten::function("set_window_size",            emscripten::optional_override([](int sizeX, int sizeY)                    { g_setWindowSize(sizeX, sizeY); }));
    emscripten::function("input",                      emscripten::optional_override([](const std::string & input)               { g_input(input); }));
    emscripten::function("get_puzzle_id",              emscripten::optional_override([]() -> int                                 { return g_getPuzzleId(); }));
    emscripten::function("set_attempts",               emscripten::optional_override([](int puzzleId, const std::string & input) { g_setAttempts(puzzleId, input); }));
    emscripten::function("get_attempts",               emscripten::optional_override([]() -> std::string                         { return g_getAttempts(); }));
    emscripten::function("set_statistics",             emscripten::optional_override([](const std::string & input)               { g_setStatistics(input); }));
    emscripten::function("get_statistics",             emscripten::optional_override([]() -> std::string                         { return g_getStatistics(); }));
    emscripten::function("set_settings",               emscripten::optional_override([](const std::string & input)               { g_setSettings(input); }));
    emscripten::function("get_settings",               emscripten::optional_override([]() -> std::string                         { return g_getSettings(); }));
    emscripten::function("get_clipboard",              emscripten::optional_override([]() -> std::string                         { return g_getClipboard(); }));
    emscripten::function("set_clipboard_text_visible", emscripten::optional_override([](bool visible)                            { g_setClipboardTextVisible(visible); }));
    emscripten::function("get_url",                    emscripten::optional_override([]() -> std::string                         { return g_getURL(); }));
    emscripten::function("set_timestamp",              emscripten::optional_override([](double input)                            { g_setTimestamp(input); }));
}
#endif

}

//
// Core
//

// common variables used for rendering stuff on the screen
struct Rendering {
    // elapsed time since the program start - used for rendering animations
    float T;

    // total window size
    ImVec2 wSize;
};

// a grid cell containing a single letter
struct Cell {
    enum Type {
        Empty,
        Pending,
        Absent,
        Present,
        Correct,
    };

    // the time at which the contents of the cell were submitted
    float tSubmit = -100.0f;

    Type type = Empty;

    // the actual contents of the cell - a single utf-8 character
    std::string data;

    bool submitted() const { return tSubmit >= 0.0f && type != Pending; }
    bool pending()   const { return type == Pending; }

    // return <fill, border> colors
    std::pair<TColor, TColor> col(float iFlip, const TColorTheme & colors) const {
        auto colFill   = colors.at(EColor::EmptyFill);
        auto colBorder = colors.at(EColor::EmptyBorder);

        if (iFlip > 0.5f || submitted() == false) {
            switch (type) {
                case Cell::Empty:
                    {
                        colFill   = colors.at(EColor::EmptyFill);
                        colBorder = colors.at(EColor::EmptyBorder);
                    } break;
                case Cell::Pending:
                    {
                        colFill   = colors.at(EColor::PendingFill);
                        colBorder = colors.at(EColor::PendingBorder);
                    } break;
                case Cell::Absent:
                    {
                        colFill   = colors.at(EColor::AbsentFill);
                        colBorder = colors.at(EColor::AbsentBorder);
                    } break;
                case Cell::Present:
                    {
                        colFill   = colors.at(EColor::PresentFill);
                        colBorder = colors.at(EColor::PresentBorder);
                    } break;
                case Cell::Correct:
                    {
                        colFill   = colors.at(EColor::CorrectFill);
                        colBorder = colors.at(EColor::CorrectBorder);
                    } break;
            };
        }

        return { colFill, colBorder, };
    }
};

// general window vars
struct Window {
    bool showWindow = false; // show the window on the screen

    // used for fade animations
    float tShow = -100.0f;
    float tHide = -100.0f;

    // is the window currently visible?
    bool visible(float T) const {
        return showWindow && T > tShow;
    }
};

// puzzles window vars
struct Puzzles : public Window {
    int puzzleId = -1; // selected puzzle ID

    // holding arrow buttons
    bool isLeftHeld = false; // is the left arrow being held?
    bool isRightHeld = false; // is the right arrow being held?
    float nextChangeTime = 0.f; // timestamp of when the ID should next change
};

// statistics for the games that the player has played so far
struct Statistics : public Window {
    int nPlayed = 0;   // number of rounds played
    int streakCur = 0; // current winning streak
    int streakMax = 0; // longest winning streak

    std::vector<int> guesses; // distribution of the number of attempts to guess a word

    // percentage of games the player has won
    float winPercentage() const {
        if (nPlayed == 0) return 0.0f;

        int nGuessed = 0;
        for (const auto & n : guesses) nGuessed += n;

        return float(100.0f*nGuessed)/nPlayed;
    }

    // the number of attempts after which the player has guessed most words
    int maxGuesses() const {
        int result = 0;

        for (const auto & cur : guesses) {
            result = std::max(result, cur);
        }

        return std::max(1, result);
    }
};

// settings window vars
struct Settings : public Window {
    float tKeyboardSwitched = -100.0f;

    EKeyboardType keyboardType = EKeyboardType::Phonetic;
    EKeyboardType keyboardTypeNew = keyboardType;
    TKeyboard keyboard = kKeyboards.at(keyboardType);

    EColorTheme colorTheme = EColorTheme::Light;
    EColorTheme colorThemeNew = colorTheme;
    TColorTheme colors = kColorThemes.at(colorTheme);

    bool rectRounding = true;
    bool rectRoundingNew = rectRounding;

    bool addHashtag = true;
    bool addHashtagNew = addHashtag;

    bool addURL = true;
    bool addURLNew = addURL;
};

// global variable containing the entire game state
struct State {
    // rendering
    int nUpdates = 60;
    bool newInput = true;
    bool isAnimating = false;
    Rendering rendering;

    // rules
    static const int nLettersPerWord = 5;
    static const int nAttemptsTotal = 6;

    // words
    std::vector<std::string> words;
    std::vector<std::string> wordsDailyPool;

    // logic + animations
    int64_t timestamp = 0; // timestamp of when the current game started

    float tShared = -100.0f; // timestamp of when player clicked on Share button

    bool textClipboardVisible = true; // should the "Results copied to clipboard" text be shown?

    // popup windows
    Window help;
    Puzzles puzzlesWnd;
    Window advert;
    Statistics statistics;
    Settings settings;

    // layout
    float heightTitle = 50.0f;
    float heightKeyboard = 200.0f;

    // keyboard
    float keyboardMinX = 0.0f;
    float keyboardMaxX = 0.0f;
    bool keyboardPressHandled = false;

    // JS interface
    std::string dataStatistics;
    std::string dataClipboard;
    std::string dataSettings;
    std::string dataURL;

    // Stores the data of a puzzle.
    // Individual for each puzzle ID.
    struct Puzzle {
        int id = -1; // the ID of the puzzle

        std::string answer;     // puzzle answer
        std::string attemptCur; // current attempt
        std::vector<std::string> attempts; // past, submitted attempts

        bool countTowardsStats = false; // should this puzzle, on finish, be counted towards statistics?

        // logic
        bool isInitialized = false; // has the puzzle been updated in State::update() before?
        bool isGuessed  = false; // has the player guessed the correct word?
        bool isFinished = false; // has the current round finished (guessed word or ran out of attempts) ?

        float tFinished  = -100.0f; // timestamp of when the current round finished
        float tIncorrect = -100.0f; // timestamp of last incorrect input

        // type of incorrect input
        enum class TypeIncorrect {
            NotAWord,
            NotEnoughLetters,
        } eIncorrect;

        // grid
        std::vector<std::vector<Cell>> grid;

        // keyboard
        std::map<std::string, Cell::Type> keys;

        // JS interface
        std::string dataAttempts;
    };
    std::vector<std::unique_ptr<Puzzle>> puzzles;
    Puzzle* currentPuzzle;

    //
    // helper methods
    //

    // create a puzzle with a certain ID.
    Puzzle* createPuzzle(int puzzleId) {
        auto puzzle = std::make_unique<Puzzle>();

        // Initialize answer
        if (wordsDailyPool.empty()) {
            // select a random word, regardless of puzzleId
            srand(std::time(nullptr));
            puzzle->answer = words[rand() % words.size()];
        } else {
            // select a word, based on puzzId
            puzzle->id = std::max(0, puzzleId);
            printf("Puzzle ID: %d\n", puzzle->id);

            // the daily pool list is already randomized:
            puzzle->answer = wordsDailyPool[puzzle->id % wordsDailyPool.size()];
        }

        // Initialize grid
        puzzle->grid.resize(nAttemptsTotal);
        for (auto& row : puzzle->grid) {
            row.resize(nLettersPerWord);
        }

        Puzzle* puzzlePtr = puzzle.get();
        puzzles.push_back(std::move(puzzle));
        return puzzlePtr;
    }

    // searches for a saved puzzle with a certain ID and returns a pointer to it.
    // if a saved puzzle with a certain ID does not exist, it's created.
    Puzzle* getPuzzle(int puzzleId) {
        auto it = std::find_if(puzzles.begin(), puzzles.end(), [puzzleId](const auto& puzzle) { return puzzle->id == puzzleId; });
        if (it == puzzles.end()) {
            return createPuzzle(puzzleId);
        }
        return it->get();
    }

    // switches the current puzzle
    void switchPuzzle(int puzzId) {
        const int latestPuzzleId = puzzleId();
        currentPuzzle = getPuzzle(std::min(puzzId, latestPuzzleId));

        // currently unneeded, as the latest puzzle can't change, because the used timestamp is taken once at the start of the game
        //currentPuzzle->countTowardsStats = currentPuzzle->id == latestPuzzleId; // if the latest puzzle has changed, count the new latest puzzle towards statistics as well

        // play quick cell flip animation
        for (auto& row : currentPuzzle->grid) {
            for (int x = 0; x < nLettersPerWord; ++x) {
                if (row[x].submitted()) {
                    row[x].tSubmit = ImGui::GetTime() + 0.2f*x*kTimeFlip;
                }
            }
        }

        // perform an update on the new puzzle
        newInput = true;
    }

    // is any of the popup windows enabled?
    bool hasPopup() const {
        return help.showWindow ||
               puzzlesWnd.showWindow ||
               advert.showWindow ||
               statistics.showWindow ||
               settings.showWindow;
    }

    // call this at the start of each frame to initialize helper variables
    void initRendering() {
        isAnimating = false;
        rendering.T = ImGui::GetTime();
        rendering.wSize = ImGui::GetContentRegionAvail();
    }

    // when there is an active animation, call this method to disable any framerate throttling that may occur
    // the argument i is an interpolation factor of the animation
    //  - if it is within (0, 1) then the animation is in progress
    //  - if it is >= 1 then the animation has finished
    //  - if it is  < 0 then the animation will start soon
    //  - if it is == 0 then the animation is disabled
    //
    void animation(float i) {
        isAnimating |= (i != 0.0f && i < 1.0f);
    }

    // add any logic that should happen upon window resize
    void onWindowResize() {
    }

    // compute the current puzzle Id based on the timestamp of loading the game
    //  - each puzzle lasts 24 hours
    //  - the first puzzle started on kTimestamp0
    //
    int puzzleId() const {
        return std::max(0, (int)((timestamp - kTimestamp0)/(24*3600)));
    }

    // compute the timestamp of the next puzzle
    int64_t nextPuzzleTimestamp() const {
        return kTimestamp0 + 24*3600*(puzzleId() + 1);
    }

    // compute how much time has left for the current puzzle
    // returns a string formatted as hh:mm:ss
    std::string timeLeft(const double T) const {
        const int64_t t = std::max(0.0, nextPuzzleTimestamp() - (timestamp + T));
        const int h = t/3600;
        const int m = (t - h*3600)/60;
        const int s = (t - h*3600 - m*60);

        const std::string sh = h >= 10 ? std::to_string(h) : "0" + std::to_string(h);
        const std::string sm = m >= 10 ? std::to_string(m) : "0" + std::to_string(m);
        const std::string ss = s >= 10 ? std::to_string(s) : "0" + std::to_string(s);

        return sh + ":" + sm + ":" + ss;
    }

    // has the game finished ?
    bool finished(float T) const {
        return currentPuzzle->isFinished && T > currentPuzzle->tFinished &&
               (currentPuzzle->isGuessed == false || currentPuzzle->tFinished + kTimeGuessed > T);
    }

    // helper method to determine the color of the key on the on-screen keyboard
    // <Foreground, Background>
    std::pair<TColor, TColor> colKey(const std::string & ch, const TColorTheme & colors) {
        if (currentPuzzle->keys.find(ch) == currentPuzzle->keys.end()) return { colors.at(EColor::Text), colors.at(EColor::KeyboardUnused), };

        switch (currentPuzzle->keys.at(ch)) {
            case Cell::Absent:  return { colors.at(EColor::TextSubmitted), colors.at(EColor::AbsentFill), };
            case Cell::Present: return { colors.at(EColor::TextSubmitted), colors.at(EColor::PresentFill), };
            case Cell::Correct: return { colors.at(EColor::TextSubmitted), colors.at(EColor::CorrectFill), };
            default:            return { colors.at(EColor::TextSubmitted), colors.at(EColor::KeyboardUnused), };
        }

        return { colors.at(EColor::Text), colors.at(EColor::KeyboardUnused), };
    }

    // do the attempts so far satisfy the Hard Mode rules?
    bool isHardMode() {
        struct Limit {
            int lower; // known minimum number of occurances of the letter
            int upper; // known maximum number of occurances of the letter

            // the letter cannot be in the following positions:
            std::vector<bool> np;
        };

        // initialize the known limits for each letter
        std::map<std::string, Limit> limits;
        for (auto ch : kAlphabet) {
            limits[ch] = { 0, nLettersPerWord, std::vector<bool>(nLettersPerWord, false) };
        }

        const int nAttempts = currentPuzzle->attempts.size();
        for (int y = 0; y < nAttempts; ++y) {
            if (y > 0) {
                for (int x = 0; x < nLettersPerWord; ++x) {
                    // once correctly guess, the letter should remain correct for the rest of the attempts
                    if (currentPuzzle->grid[y-1][x].type == Cell::Correct && currentPuzzle->grid[y][x].type != Cell::Correct) {
                        return false;
                    }
                }
            }

            for (int x = 0; x < nLettersPerWord; ++x) {
                // check if we known that the letter ch cannot be at position x
                if (limits[currentPuzzle->grid[y][x].data].np[x]) {
                    return false;
                }

                if (currentPuzzle->grid[y][x].type != Cell::Correct) {
                    limits[currentPuzzle->grid[y][x].data].np[x] = true;
                }
            }

            std::map<std::string, std::pair<int, int>> cnt;

            // count how many times the letter occurs in current attempt
            // also, count the number of times the letter was marked as Present or Correct (i.e. non-Absent)
            for (int x = 0; x < nLettersPerWord; ++x) {
                const auto & ch = currentPuzzle->grid[y][x].data;

                auto & nInput = cnt[ch].first;
                auto & nNonAbsent = cnt[ch].second;

                nInput++;
                if (currentPuzzle->grid[y][x].type != Cell::Absent) nNonAbsent++;
            }

            // limits check - each letter in the new attempt must be within the currently known limits
            for (const auto & [ch, c] : cnt) {
                const auto & nInput = c.first;
                if (nInput < limits[ch].lower || nInput > limits[ch].upper) {
                    return false;
                }
            }

            // if we know a letter is present in the answer, it must be played in the new attempt
            for (const auto & [ch, limit] : limits) {
                if (limit.lower > 0 && cnt.find(ch) == cnt.end()) {
                    return false;
                }
            }

            // update the limits based on the current attempt results
            for (const auto & [ch, c] : cnt) {
                const auto & nInput = c.first;
                const auto & nNonAbsent = c.second;

                // update the lower limit for the occurances of ch
                limits[ch].lower = nNonAbsent;

                // we know an upper limit for the occurances of ch
                // for example: input contains ch 2 times and only one is Correct or Present => there is only one ch in the answer
                if (nInput > nNonAbsent) {
                    limits[ch].upper = nNonAbsent;
                }
            }
        }

        return true;
    }

    // update the state of the game:
    //   - grid cell colors
    //   - keyboard colors
    //   - has the game finished?
    //
    // must be called on every frame
    //
    void update(const float T) {
        if (newInput == false) return;

        //currentPuzzle->isGuessed = false;

        const bool wasFinished = currentPuzzle->isFinished;
        const int nAttempts = currentPuzzle->attempts.size();

        for (int y = 0; y < nAttemptsTotal; ++y) {
            if (y < nAttempts) {
                const auto & curAttempt = currentPuzzle->attempts[y];

                std::vector<bool> used(nLettersPerWord, false);
                std::vector<Cell::Type> guesses(nLettersPerWord, Cell::Absent);

                int nCorrect = 0;

                for (int x = 0; x < nLettersPerWord; ++x) {
                    // initialize used keys as Absent
                    if (currentPuzzle->keys.find(::utf8_ch(curAttempt, x)) == currentPuzzle->keys.end()) {
                        currentPuzzle->keys[::utf8_ch(curAttempt, x)] = Cell::Absent;
                    }

                    // first detect Correct letters/keys
                    if (::utf8_cmp(curAttempt, x, currentPuzzle->answer, x)) {
                        currentPuzzle->keys[::utf8_ch(curAttempt, x)] = Cell::Correct;
                        guesses[x] = Cell::Correct;
                        used[x] = true;
                        ++nCorrect;
                    }
                }

                // we have a guessed word -> end the game and update stats
                if (currentPuzzle->isFinished == false && nCorrect == nLettersPerWord) {
                    if (currentPuzzle->isInitialized && currentPuzzle->countTowardsStats) {
                        statistics.guesses[y]++;
                        statistics.nPlayed++;
                        statistics.streakCur++;
                        if (statistics.streakMax < statistics.streakCur) {
                            statistics.streakMax = statistics.streakCur;
                        }
                    }
                    currentPuzzle->isGuessed = true;
                    currentPuzzle->isFinished = true;
                }

                // next detect Present letters/keys
                for (int x = 0; x < nLettersPerWord; ++x) {
                    if (guesses[x] != Cell::Absent) continue;
                    for (int i = 0; i < nLettersPerWord; ++i) {
                        if (x == i) continue;
                        if (used[i]) continue;
                        if (::utf8_cmp(curAttempt, x, currentPuzzle->answer, i)) {
                            if (currentPuzzle->keys[::utf8_ch(curAttempt, x)] < Cell::Correct) {
                                currentPuzzle->keys[::utf8_ch(curAttempt, x)] = Cell::Present;
                            }
                            guesses[x] = Cell::Present;
                            used[i] = true;
                            break;
                        }
                    }
                }

                // fill in the cells on the current row with the corresponding states and trigger animations
                for (int x = 0; x < nLettersPerWord; ++x) {
                    auto & curCell = currentPuzzle->grid[y][x];

                    if (curCell.submitted() == false) {
                        curCell.data = ::utf8_ch(curAttempt, x);
                        curCell.type = guesses[x];
                        if (currentPuzzle->isInitialized) {
                            curCell.tSubmit = T + 1.0f*x*kTimeFlip;
                            if (x == 0) updateDataAttempts();
                        } else {
                            curCell.tSubmit = T + 0.2f*x*kTimeFlip;
                        }
                    }
                }
            }

            if (y == nAttempts) {
                const auto & curAttempt = currentPuzzle->attemptCur;

                // number of letters provided so far
                const int n = ::utf8_size(curAttempt);

                // mark the provided cells as Pending
                for (int x = 0; x < n; ++x) {
                    auto & curCell = currentPuzzle->grid[y][x];

                    if (curCell.type == Cell::Empty) {
                        curCell.tSubmit = T;
                    }

                    curCell.data = ::utf8_ch(curAttempt, x);
                    curCell.type = Cell::Pending;
                }

                if (n == nLettersPerWord) {
                    // if the pending word exists - color the Enter key to give a hint
                    bool found = false;
                    for (const auto & word : words) {
                        if (word == currentPuzzle->attemptCur) {
                            found = true;
                            break;
                        }
                    }

                    if (found) {
                        currentPuzzle->keys[kInputEnter] = Cell::Correct;
                    } else {
                        currentPuzzle->keys[kInputEnter] = Cell::Empty;
                    }
                } else {
                    // mark the cells without input as Empty
                    for (int x = n; x < nLettersPerWord; ++x) {
                        auto & curCell = currentPuzzle->grid[y][x];

                        curCell.data = "";
                        curCell.type = Cell::Empty;
                    }

                    currentPuzzle->keys[kInputEnter] = Cell::Empty;
                }
            }
        }

        // failed to guess the word -> end the game + update stats
        if (currentPuzzle->isFinished == false) {
            currentPuzzle->isFinished = nAttemptsTotal == nAttempts;
            if (currentPuzzle->isFinished) {
                if (currentPuzzle->isInitialized && currentPuzzle->countTowardsStats) {
                    statistics.nPlayed++;
                    statistics.streakCur = 0;
                }
            }
        }

        // the game ended during the current update call -> queue Statistics window to be shown automatically
        if (currentPuzzle->isFinished && wasFinished == false && currentPuzzle->countTowardsStats) {
            if (currentPuzzle->isInitialized) {
                statistics.showWindow = true;
                statistics.tShow = T + (1.0f*nLettersPerWord)*kTimeFlip + 1.0f*kTimeGuessed;
            } else {
                statistics.showWindow = true;
                statistics.tShow = T + (0.2f*nLettersPerWord)*kTimeFlip + 2.0f*kTimeFlip;
            }
        }

        // the game has ended -> send new Statistics data to the JS layer
        // it will be stored in the browser's localStorage in order to be persisted for the next round
        if (currentPuzzle->isInitialized && currentPuzzle->isFinished && !wasFinished) {
            currentPuzzle->tFinished = T + 1.0f*nLettersPerWord*kTimeFlip;
            updateDataStatistics();
        }

        currentPuzzle->isInitialized = true;
        newInput = false;
    }

    // error string upon incorrect input
    const char * textIncorrect() const {
        switch (currentPuzzle->eIncorrect) {
            case Puzzle::TypeIncorrect::NotAWord:          return "Непозната дума";
            case Puzzle::TypeIncorrect::NotEnoughLetters:  return "Недостатъчно букви";
        };

        return "";
    }

    // strings upon completion of the game
    const char * textFinished() const {
        // success strings
        if (currentPuzzle->isGuessed) {
            if (currentPuzzle->attempts.size() == 1) return "Гений";
            if (currentPuzzle->attempts.size() == 2) return "Невероятно";
            if (currentPuzzle->attempts.size() == 3) return "Отлично";
            if (currentPuzzle->attempts.size() == 4) return "Браво";
            if (currentPuzzle->attempts.size() == 5) return "Не е зле";
            if (currentPuzzle->attempts.size() == 6) return "За малко";
            return "Браво"; // fallback - should never happen
        }

        // upon failure -> show the answer
        return currentPuzzle->answer.c_str();
    }

    // update the dataAttempts member - to be consumed by the JS layer
    void updateDataAttempts() {
        for (const auto & cur : currentPuzzle->attempts) {
            currentPuzzle->dataAttempts += cur;
            currentPuzzle->dataAttempts += " ";
        }

        currentPuzzle->dataAttempts.pop_back();
    }

    // update the dataStatistics member - to be consumed by the JS layer
    void updateDataStatistics() {
        dataStatistics  = std::to_string(statistics.nPlayed);
        dataStatistics += " ";
        dataStatistics += std::to_string(statistics.streakCur);
        dataStatistics += " ";
        dataStatistics += std::to_string(statistics.streakMax);
        dataStatistics += " ";
        dataStatistics += std::to_string(nAttemptsTotal);
        dataStatistics += " ";

        for (int i = 0; i < nAttemptsTotal; ++i) {
            dataStatistics += std::to_string(statistics.guesses[i]);
            dataStatistics += " ";
        }

        dataStatistics.pop_back();
    }

    // update the dataClipboard member - to be consumed by the JS layer
    void updateDataClipboard(const TColorTheme & colors) {
        const int n = currentPuzzle->attempts.size();
        const std::string special = isHardMode() ? "*" : "";
        const std::string tries = currentPuzzle->isGuessed ? std::to_string(n) : "X";
        dataClipboard = std::string(kTitleClipboard) + " " + (currentPuzzle->id < 0 ? "\"" + currentPuzzle->answer + "\"" : std::to_string(currentPuzzle->id))
            + " " + tries + "/" + std::to_string(nAttemptsTotal) + special + "\n\n";
        for (int y = 0; y < n; ++y) {
            for (int x = 0; x < nLettersPerWord; ++x) {
                switch (currentPuzzle->grid[y][x].type) {
                    case Cell::Absent:  dataClipboard += kGridEmojis.at(colors.at(EColor::AbsentFill));  break;
                    case Cell::Present: dataClipboard += kGridEmojis.at(colors.at(EColor::PresentFill)); break;
                    case Cell::Correct: dataClipboard += kGridEmojis.at(colors.at(EColor::CorrectFill)); break;
                    default: dataClipboard += kGridEmojis.at(colors.at(EColor::AbsentFill)); break;
                };
            }
            dataClipboard += "\n";
        }
        dataClipboard += "\n";

        if (settings.addHashtag) {
            dataClipboard += kHashtag;
            if (settings.addURL) {
                dataClipboard += " ";
            }
        }
        if (settings.addURL) {
            dataClipboard += kURL;
        }
    }

    // update the dataSettings member - to be consumed by the JS layer
    void updateDataSettings() {
        dataSettings  = std::to_string((int) settings.colorTheme);
        dataSettings += " ";
        dataSettings += std::to_string((int) settings.rectRounding);
        dataSettings += " ";
        dataSettings += std::to_string((int) settings.keyboardType);
        dataSettings += " ";
        dataSettings += std::to_string((int) settings.addHashtag);
        dataSettings += " ";
        dataSettings += std::to_string((int) settings.addURL);
    }
} g_state;

// initialize initial puzzle
void initPuzzle() {
#ifndef __EMSCRIPTEN__
    g_state.timestamp = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
#endif

    // load word list
    {
        std::ifstream fin;
        fin.open("words.txt");
        if (!fin.is_open()) {
            fprintf(stderr, "Failed to load dictionary from '%s'\n", "words.txt");
            return;
        }

        std::string word;
        while (fin >> word) {
            g_state.words.push_back(std::move(word));
        }
    }

    // load daily pool set - puzzle answers are selected only from this set
    {
        std::ifstream fin;
        fin.open("words-daily-pool.txt");
        if (!fin.is_open()) {
            fprintf(stderr, "Failed to load dictionary from '%s'\n", "words-daily-pool.txt. Will select a random word..");
        } else {
            std::string word;
            while (fin >> word) {
                g_state.wordsDailyPool.push_back(std::move(word));
            }
        }
    }

    g_state.currentPuzzle = g_state.createPuzzle(g_state.puzzleId());
    g_state.currentPuzzle->countTowardsStats = true; // only count the initial (latest) puzzle towards statistics
}

// initialize game state
void initGame() {
    const float T = ImGui::GetTime();

    g_state.statistics.guesses.resize(g_state.nAttemptsTotal);

    // automatically show the help window to new players
    if (g_state.statistics.nPlayed == 0) {
        g_state.help.showWindow = true;
        g_state.help.tShow = T + 0.2f;
    }

    // shortcuts for settings some initial data for debugging purposes
    //g_state.currentPuzzle->answer = "БРОНЯ";
    //g_state.currentPuzzle->attempts.resize(2);
    //g_state.currentPuzzle->attempts[0] = "ПРОБА";
    //g_state.currentPuzzle->attempts[1] = "ДЕСЕТ";

    //g_state.statistics.guesses[1] = 3;
    //g_state.statistics.guesses[4] = 2;
    //g_state.statistics.guesses[5] = 8;

    g_state.update(T);
}

int ImRotateStart() {
	return ImGui::GetWindowDrawList()->VtxBuffer.Size;
}

ImVec2 ImRotationCenter(int idx) {
	ImVec2 l(FLT_MAX, FLT_MAX), u(-FLT_MAX, -FLT_MAX); // bounds

	const auto& buf = ImGui::GetWindowDrawList()->VtxBuffer;
	for (int i = idx; i < buf.Size; i++) {
		l = ImMin(l, buf[i].pos), u = ImMax(u, buf[i].pos);
    }

	return ImVec2((l.x+u.x)/2, (l.y+u.y)/2); // or use _ClipRectStack?
}

void ImRotateEnd(float rad, int idx, ImVec2 center) {
    struct Ops {
        static ImVec2 sub(const ImVec2& l, const ImVec2& r) { return{ l.x - r.x, l.y - r.y }; };
    };

    float s=sin(rad), c=cos(rad);
    center = Ops::sub(ImRotate(center, s, c), center);

    auto& buf = ImGui::GetWindowDrawList()->VtxBuffer;
    for (int i = idx; i < buf.Size; i++) {
        buf[i].pos = Ops::sub(ImRotate(buf[i].pos, s, c), center);
    }
}

// return true if the box has been clicked
bool renderBox(ImDrawList * drawList, const std::string & text, const ImVec2 & pos, TColor col, float scale, bool center, const ImVec2 & offset = { 0.0f, 0.0f }, float rounding = -1.0f) {
    ImGui::SetWindowFontScale(scale/kFontScale);

    const ImVec2 textSize = ImGui::CalcTextSize(text.c_str());

    const float kMarginX = 20.0f;
    const float kMarginY = 12.0f;

    const ImVec2 pp0 = {
        pos.x - kMarginX + (offset.x - (center ? 0.5f : 0.0f))*textSize.x,
        pos.y - kMarginY + (offset.y - (center ? 0.5f : 0.0f))*textSize.y,
    };

    const ImVec2 pp1 = {
        pos.x + 1.0f*textSize.x + kMarginX + (offset.x - (center ? 0.5f : 0.0f))*textSize.x,
        pos.y + 1.0f*textSize.y + kMarginY + (offset.y - (center ? 0.5f : 0.0f))*textSize.y,
    };

    drawList->AddRectFilled(pp0, pp1, col, rounding >= 0.0 ? rounding : g_state.settings.rectRounding ? 2.0f : 0.0f);

    return ImGui::IsMouseHoveringRect(pp0, pp1, true) && ImGui::IsMouseReleased(0);
}

ImU32 fade(const ImU32 & c32, float f) {
    const auto c4 = ImGui::ColorConvertU32ToFloat4(c32);
    return ImGui::ColorConvertFloat4ToU32({ c4.x, c4.y, c4.z, f*c4.w, });
}

// return true if the text has been clicked
bool renderText(const std::string & text, const ImVec2 & pos, TColor col, float scale, bool center, const ImVec2 & offset = { 0.0f, 0.0f }) {
    ImGui::SetWindowFontScale(scale/kFontScale);

    const ImVec2 textSize = ImGui::CalcTextSize(text.c_str());

    const ImVec2 p0 = {
        pos.x + (offset.x - (center ? 0.5f : 0.0f))*textSize.x,
        pos.y + (offset.y - (center ? 0.5f : 0.0f))*textSize.y,
    };

    ImGui::SetCursorScreenPos(p0);
    ImGui::TextColored(ImGui::ColorConvertU32ToFloat4(col), "%s", text.c_str());

    return ImGui::IsItemHovered() && ImGui::IsMouseReleased(0);
}

// return true if clicked
bool renderTextWithBackground(ImDrawList * drawList, const std::string & text, const ImVec2 & pos, TColor colFG, TColor colBG, float scale, bool center, const ImVec2 & offset = { 0.0f, 0.0f }) {
    bool result = false;

    result |= renderBox (drawList, text.c_str(), pos, colBG, scale, center, offset);
    result |= renderText(          text.c_str(), pos, colFG, scale, center, offset);

    return result;
}

void renderWord(ImDrawList * drawList, const std::vector<Cell> & word, ImVec2 ul, float cellSize, float T) {
    const auto & colors = g_state.settings.colors;

    const float kCellSize   = cellSize;
    const float kCellMargin = 0.10f*kCellSize;

    for (int x = 0; x < (int) word.size(); ++x) {
        const auto & curCell = word[x];

        // upper-left corner of cell (x, y)
        const ImVec2 p0 = {
            ul.x + x*kCellSize,
            ul.y + 0*kCellSize,
        };

        // lower-right corner of cell (x, y)
        const ImVec2 p1 = {
            p0.x + kCellSize - kCellMargin,
            p0.y + kCellSize - kCellMargin,
        };

        const float iFlip = curCell.submitted() ? ::I(T - curCell.tSubmit, kTimeFlip) : 0.0f;
        const float iFill = curCell.submitted() ? ::I(T - curCell.tSubmit, kTimeFill) : 0.0f;

        g_state.animation(iFlip);
        g_state.animation(iFill);

        const float tFlip = std::max(0.0f, std::min(1.0f, 1.0f - std::fabs(2.0f*(iFlip - 0.5f))));
        const float tFill = std::max(0.0f, std::min(1.0f, 1.0f - std::fabs(2.0f*(iFill - 0.5f))));

        const float hFlip = 0.5f*tFlip*(p1.y - p0.y);

        const ImVec2 pp0 = { p0.x, p0.y + hFlip, };
        const ImVec2 pp1 = { p1.x, p1.y - hFlip, };

        const auto [colFill, colBorder] = curCell.col(iFlip, colors);

        drawList->AddRectFilled(pp0, pp1, fade(colFill,   (1.0f - tFill)));
        drawList->AddRect      (pp0, pp1, fade(colBorder, (1.0f - tFill)), 0.0f, 0, 2.0f);

        ImGui::PushClipRect( pp0, pp1, true);

        const auto colText = curCell.submitted() && iFlip > 0.5f ? colors.at(EColor::TextSubmitted) : colors.at(EColor::Text);
        renderText(curCell.data, { 0.5f*(p0.x + p1.x), 0.5f*(p0.y + p1.y), }, colText, 1.0f*(kCellSize/18.0f), true);

        ImGui::PopClipRect();
    }
}

// main render function
void renderMain() {
    ImGui::NewFrame();

    static bool isFirstFrame = true;
    if (isFirstFrame) {
        ImGui_SetStyle();

        isFirstFrame = false;
    }

    // select Bold font
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);

    auto & style = ImGui::GetStyle();

    const auto saveWindowPadding = style.WindowPadding;
    const auto saveWindowBorderSize = style.WindowBorderSize;

    style.WindowPadding.x = 0.0f;
    style.WindowPadding.y = 0.0f;
    style.WindowBorderSize = 0.0f;

    ImGui::SetNextWindowPos({ 0.0f, 0.0f });
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
    ImGui::Begin("main", NULL,
                 ImGuiWindowFlags_NoNav |
                 ImGuiWindowFlags_NoDecoration |
                 ImGuiWindowFlags_NoBackground);

    style.WindowPadding = saveWindowPadding;
    style.WindowBorderSize = saveWindowBorderSize;

    auto drawList = ImGui::GetWindowDrawList();

    g_state.initRendering();

    const auto & T = g_state.rendering.T;
    const auto & wSize = g_state.rendering.wSize;
    const auto & colors = g_state.settings.colors;

    const int nAttempts = g_state.currentPuzzle->attempts.size();

    // background
    drawList->AddRectFilled({ 0.0f, 0.0f }, wSize, colors.at(EColor::Background));

    ImGui::SetWindowFontScale(1.0f/kFontScale);

    // is any of the popup windows enabled?
    const bool hasPopup = g_state.hasPopup();

    // draw title area
    {
        // grid center
        const ImVec2 c0 = {
            0.5f*g_state.rendering.wSize.x,
            0.5f*g_state.heightTitle,
        };

        // draw title text
        renderText(kTitle, c0, colors.at(EColor::Title), 3.0f, true);

        // draw help button
        if (renderText(ICON_FA_QUESTION_CIRCLE, { g_state.keyboardMinX, c0.y, }, colors.at(EColor::PendingBorder), 1.75f, true, { 0.85f, 0.0f }) && !hasPopup) {
            if (g_state.help.showWindow == false) {
                g_state.help.showWindow = true;
                g_state.help.tShow = T;
            }
        }

        // draw puzzles button
        if (!g_state.wordsDailyPool.empty() && renderText(ICON_FA_HISTORY, { g_state.keyboardMinX, c0.y, }, colors.at(EColor::PendingBorder), 1.75f, true, { 2.55f, 0.0f }) && !hasPopup) {
            if (g_state.puzzlesWnd.showWindow == false) {
                g_state.puzzlesWnd.showWindow = true;
                g_state.puzzlesWnd.tShow = T;
                g_state.puzzlesWnd.puzzleId = g_state.currentPuzzle->id;
            }
        }

        // draw advert button
        //if (renderText(ICON_FA_SCROLL, { g_state.keyboardMinX, c0.y, }, colors.at(EColor::PendingBorder), 1.75f, true, { 2.20f, 0.0f }) && !hasPopup) {
        //    if (g_state.advert.showWindow == false) {
        //        g_state.advert.showWindow = true;
        //        g_state.advert.tShow = T;
        //    }
        //}

        if (g_state.currentPuzzle->countTowardsStats) {
            // draw statistics button
            if (renderText(ICON_FA_CHART_BAR, { g_state.keyboardMaxX, c0.y, }, colors.at(EColor::PendingBorder), 1.75f, true, { -2.55f, 0.0f }) && !hasPopup) {
                if (g_state.statistics.showWindow == false) {
                    g_state.statistics.showWindow = true;
                    g_state.statistics.tShow = T;
                }
            }
        }
        else if (g_state.currentPuzzle->isFinished) {
            // draw share button
            if (renderText(ICON_FA_SHARE_ALT, { g_state.keyboardMaxX, c0.y, }, colors.at(EColor::PendingBorder), 1.75f, true, { -2.55f, 0.0f }) && !hasPopup) {
                g_state.updateDataClipboard(colors);
                g_state.tShared = T;
                SDL_SetClipboardText(g_state.dataClipboard.c_str());
            }
        }

        // draw settings button
        {
            const auto idx = ImRotateStart();

            if (renderText(ICON_FA_COG, { g_state.keyboardMaxX, c0.y, }, colors.at(EColor::PendingBorder), 1.75f, true, { -0.85f, 0.0f }) && !hasPopup) {
                if (g_state.settings.showWindow == false) {
                    g_state.settings.showWindow = true;
                    g_state.settings.tShow = T;
                }
            }

            const float iR = ::I(T - 1.0f, kTimeInitialize);
            ImRotateEnd(50.0f*std::pow((1.0f - iR)*iR, 2.0f), idx, ImRotationCenter(idx));
            g_state.animation(iR);
        }

        // draw title separator
        drawList->AddLine({ g_state.keyboardMinX, g_state.heightTitle, }, { g_state.keyboardMaxX, g_state.heightTitle }, colors.at(EColor::PendingBorder));
    }

    // draw grid area
    {
        // constraints
        const float kBaseMargin    = 25.0f;
        const float kGridHeightMax = g_state.rendering.wSize.y - g_state.heightTitle - g_state.heightKeyboard - 2.0f*kBaseMargin;
        const float kGridHeight    = std::min(400.0f, kGridHeightMax);

        // grid center
        const ImVec2 c0 = {
            0.5f*g_state.rendering.wSize.x,
            g_state.heightTitle + 0.5f*kGridHeightMax + kBaseMargin,
        };

        const float kCellSize = kGridHeight/g_state.nAttemptsTotal;
        const float kCellMargin = 0.10f*kCellSize;

        // grid upper-left corner
        const ImVec2 ul = {
            c0.x - 0.5f*float(g_state.nLettersPerWord)*kCellSize + 0.5f*kCellMargin,
            c0.y - 0.5f*float(g_state.nAttemptsTotal )*kCellSize + 0.5f*kCellMargin,
        };

        // position of info box
        const ImVec2 pInfo = {
            0.5f*g_state.rendering.wSize.x,
            g_state.heightTitle + 0.1f*kGridHeightMax + kBaseMargin,
        };

        for (int y = 0; y < g_state.nAttemptsTotal; ++y) {
            for (int x = 0; x < g_state.nLettersPerWord; ++x) {
                const auto & curCell = g_state.currentPuzzle->grid[y][x];

                // interpolation factors for the row animations
                const float iI = y     == nAttempts                                     ? ::I(T - g_state.currentPuzzle->tIncorrect, kTimeShake) : 0.0f;
                const float iG = y + 1 == nAttempts && g_state.currentPuzzle->isGuessed ? ::I(T - g_state.currentPuzzle->tFinished - 0.2f*x*kTimeShake, kTimeShake) : 0.0f;

                g_state.animation(iI);
                g_state.animation(iG);

                const float dxShake =  0.5f*kCellMargin*std::sin(8.0f*M_PI*iI);
                const float dyShake = -2.0f*kCellMargin*std::sin(2.0f*M_PI*iG);

                // upper-left corner of cell (x, y)
                const ImVec2 p0 = {
                    ul.x + x*kCellSize + dxShake,
                    ul.y + y*kCellSize + dyShake,
                };

                // lower-right corner of cell (x, y)
                const ImVec2 p1 = {
                    ul.x + (x + 1)*kCellSize - kCellMargin + dxShake,
                    ul.y + (y + 1)*kCellSize - kCellMargin + dyShake,
                };

                const float iFlip = curCell.submitted() ? ::I(T - curCell.tSubmit, kTimeFlip) : 0.0f;
                const float iFill = curCell.submitted() ? ::I(T - curCell.tSubmit, kTimeFill) : 0.0f;
                const float iBump = curCell.pending()   ? ::I(T - curCell.tSubmit, kTimeBump) : 0.0f;

                g_state.animation(iFlip);
                g_state.animation(iFill);
                g_state.animation(iBump);

                const float tFlip = std::max(0.0f, std::min(1.0f, 1.0f - std::fabs(2.0f*(iFlip - 0.5f))));
                const float tFill = std::max(0.0f, std::min(1.0f, 1.0f - std::fabs(2.0f*(iFill - 0.5f))));
                const float tBump = std::max(0.0f, std::min(1.0f, 1.0f - std::fabs(2.0f*(iBump - 0.5f))));

                const float hFlip = 0.5f*tFlip*(p1.y - p0.y);
                const float hBump = 0.5f*tBump*kCellMargin;

                const ImVec2 pp0 = { p0.x - hBump, p0.y + hFlip - hBump, };
                const ImVec2 pp1 = { p1.x + hBump, p1.y - hFlip + hBump, };

                const auto [colFill, colBorder] = curCell.col(iFlip, colors);

                drawList->AddRectFilled(pp0, pp1, fade(colFill,   (1.0f - tFill)));
                drawList->AddRect      (pp0, pp1, fade(colBorder, (1.0f - tFill)), 0.0f, 0, 2.0f);

                ImGui::PushClipRect( pp0, pp1, true);

                const auto colText = curCell.submitted() && iFlip > 0.5f ? colors.at(EColor::TextSubmitted) : colors.at(EColor::Text);
                renderText(curCell.data, { 0.5f*(p0.x + p1.x), 0.5f*(p0.y + p1.y), }, colText, 1.0f*(kCellSize/27.0f), true);

                ImGui::PopClipRect();
            }
        }

        // incorrect input
        if (::within(T, g_state.currentPuzzle->tIncorrect, kTimeIncorrect)) {
            renderTextWithBackground(drawList, g_state.textIncorrect(), pInfo, colors.at(EColor::Background), colors.at(EColor::Title), 1.25f, true);
        }

        // game finished
        if (g_state.finished(T)) {
            renderTextWithBackground(drawList, g_state.textFinished(), pInfo, colors.at(EColor::Background), colors.at(EColor::Title), 1.25f, true);
        }
    }

    // draw keyboard
    {
        const auto & kKeyboard = g_state.settings.keyboard;

        const float kMargin = std::min(0.005f*wSize.x, 0.02f*g_state.heightKeyboard);

        const float kKeyXMax = wSize.x/kKeyboard[0].size();
        const float kKeyYMax = g_state.heightKeyboard/kKeyboard.size();

        const float kKeyX = std::min(43.0f, kKeyXMax);
        const float kKeyY = std::min(58.0f, kKeyYMax);

        // keyboard center
        const ImVec2 c0 = {
            0.5f*g_state.rendering.wSize.x,
            wSize.y - 0.5f*g_state.heightKeyboard,
        };

        // number of rows
        const int ny = kKeyboard.size();

        for (int y = 0; y < ny; ++y) {
            // number of keys on the current row
            const int nx = kKeyboard[y].size();

            // row upper-left corner
            const ImVec2 ul = {
                c0.x - 0.5f*float(nx)*kKeyX,
                c0.y - 0.5f*float(ny)*kKeyY,
            };

            // the keyboard is the widest component so it's width determines the width of the entire app
            // here we store it in order to use it when rendering other components
            if (y == 0) {
                g_state.keyboardMinX = ul.x;
                g_state.keyboardMaxX = ul.x + nx*kKeyX;
            }

            for (int x = 0; x < nx; ++x) {
                // upper-left corner of the key
                const ImVec2 p0 = {
                    ul.x + 0.5f*kMargin + x*kKeyX - (kKeyboard[y][x] == kInputEnter ? 0.5f*kKeyX : 0.0f),
                    ul.y + 0.5f*kMargin + y*kKeyY,
                };

                // lower-right corner of the key
                const ImVec2 p1 = {
                    ul.x + (x + 1)*kKeyX - kMargin + (kKeyboard[y][x] == kInputBackspace ? 0.5f*kKeyX : 0.0f),
                    ul.y + (y + 1)*kKeyY - kMargin,
                };

                const auto & ch = kKeyboard[y][x];
                const auto [colFG, colBG] = g_state.colKey(ch, colors);

                drawList->AddRectFilled(p0, p1, colBG, g_state.settings.rectRounding ? 4.0f : 0.0f);

                renderText(ch, { 0.5f*(p0.x + p1.x), 0.5f*(p0.y + p1.y), }, colFG, 1.0f*(kKeyX/35.0f), true);

                // fade-in animation when switching the keyboard layout
                {
                    const auto tHighlight = ::I(T - g_state.settings.tKeyboardSwitched, kTimeShow);
                    g_state.animation(tHighlight);

                    if (tHighlight < 1.0f) {
                        const auto col = ImGui::ColorConvertU32ToFloat4(colors.at(EColor::Background));
                        drawList->AddRectFilled(p0, p1, ImGui::ColorConvertFloat4ToU32({ col.x, col.y, col.z, (1.0f - tHighlight)*kColorFade.w }));
                    }
                }

                if (!hasPopup && ImGui::IsMouseHoveringRect(p0, p1, true) && ImGui::IsMouseReleased(0)) {
                    g_input(ch);
                }
            }
        }
    }

    // help window
    if (g_state.help.visible(T)) {
        const auto tShown = ::I(T - g_state.help.tShow, kTimeShow);

        g_state.animation(tShown);

        // fade-out main window
        drawList->AddRectFilled({ 0.0f, 0.0f }, wSize, ImGui::ColorConvertFloat4ToU32({ 0.0f, 0.0f, 0.0f, tShown*kColorFade.w }));

        const float kCurScale = std::min(1.0f, (g_state.keyboardMaxX - g_state.keyboardMinX)/473.0f);
        const float kFontSize = 1.25f*kCurScale;
        const float kWindowYMax = 440.0f*kCurScale;

        {
            // upper-left corner
            const ImVec2 ul = {
                g_state.keyboardMinX,
                0.5f*wSize.y - 0.5f*kWindowYMax,
            };

            // lower-right corner
            const ImVec2 lr = {
                g_state.keyboardMaxX,
                0.5f*wSize.y + 0.5f*kWindowYMax,
            };

            // leave some empty space near the window border
            const float kMarginX = 20.0f;
            const float kMarginY = 10.0f;

            // window floor
            drawList->AddRectFilled(ul, lr, colors.at(EColor::Background), g_state.settings.rectRounding ? 8.0f : 0.0f);
            drawList->AddRect      (ul, lr, colors.at(EColor::AbsentFill), g_state.settings.rectRounding ? 8.0f : 0.0f, 0, 1.0f);

            {
                ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[2]);
                ImGui::PushTextWrapPos(lr.x - kMarginX);

                ImGui::SetWindowFontScale(kFontSize/kFontScale);
                const float kRowHeight = ImGui::CalcTextSize("A").y;

                renderText("Познайте думата от 6 опита.", { ul.x + kMarginX, ul.y + kMarginY + 1.0f*kRowHeight, }, colors.at(EColor::Text), kFontSize, false);
                renderText("Всеки опит трябва да е валидна 5-буквена дума.", { ul.x + kMarginX, ul.y + kMarginY + 3.0f*kRowHeight, }, colors.at(EColor::Text), kFontSize, false);
                renderText("След всеки опит цветовете на клетките ще се променят за да покажат колко сте близо до правилната дума.", { ul.x + kMarginX, ul.y + kMarginY + 5.0f*kRowHeight, }, colors.at(EColor::Text), kFontSize, false);

                drawList->AddLine({ ul.x + kMarginX, ul.y + kMarginY + 7.5f*kRowHeight, }, { lr.x - kMarginX, ul.y + kMarginY + 7.5f*kRowHeight }, colors.at(EColor::PendingBorder));

                ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
                renderText("Примери:", { ul.x + kMarginX, ul.y + kMarginY + 8.0f*kRowHeight, }, colors.at(EColor::Text), kFontSize, false);
                ImGui::PopFont();

                {
                    std::vector<Cell> curWord = {
                        { g_state.help.tShow + 0.5f, Cell::Correct, "П" },
                        { -100.0f,                   Cell::Empty,   "Е" },
                        { -100.0f,                   Cell::Empty,   "С" },
                        { -100.0f,                   Cell::Empty,   "Е" },
                        { -100.0f,                   Cell::Empty,   "Н" },
                    };

                    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
                    renderWord(drawList, curWord, { ul.x + kMarginX, ul.y + kMarginY + 9.5f*kRowHeight, }, 2.0f*kRowHeight, T);
                    ImGui::PopFont();

                    renderText("Буквата П присъства и е на правилното място.", { ul.x + kMarginX, ul.y + kMarginY + 12.0f*kRowHeight, }, colors.at(EColor::Text), kFontSize, false);
                }

                {
                    std::vector<Cell> curWord = {
                        { -100.0f,                   Cell::Empty,   "Б" },
                        { g_state.help.tShow + 0.5f, Cell::Present, "У" },
                        { -100.0f,                   Cell::Empty,   "Х" },
                        { -100.0f,                   Cell::Empty,   "А" },
                        { -100.0f,                   Cell::Empty,   "Л" },
                    };

                    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
                    renderWord(drawList, curWord, { ul.x + kMarginX, ul.y + kMarginY + 13.5f*kRowHeight, }, 2.0f*kRowHeight, T);
                    ImGui::PopFont();

                    renderText("Буквата У присъства но е на грешно място.", { ul.x + kMarginX, ul.y + kMarginY + 16.0f*kRowHeight, }, colors.at(EColor::Text), kFontSize, false);
                }

                {
                    std::vector<Cell> curWord = {
                        { -100.0f,                   Cell::Empty,   "Д" },
                        { -100.0f,                   Cell::Empty,   "И" },
                        { -100.0f,                   Cell::Empty,   "В" },
                        { g_state.help.tShow + 0.5f, Cell::Absent,  "А" },
                        { -100.0f,                   Cell::Empty,   "Н" },
                    };

                    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
                    renderWord(drawList, curWord, { ul.x + kMarginX, ul.y + kMarginY + 17.5f*kRowHeight, }, 2.0f*kRowHeight, T);
                    ImGui::PopFont();

                    renderText("Буквата А не присъства в отговора.", { ul.x + kMarginX, ul.y + kMarginY + 20.0f*kRowHeight, }, colors.at(EColor::Text), kFontSize, false);
                }

                drawList->AddLine({ ul.x + kMarginX, ul.y + kMarginY + 21.5f*kRowHeight, }, { lr.x - kMarginX, ul.y + kMarginY + 21.5f*kRowHeight }, colors.at(EColor::PendingBorder));

                ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
                renderText("Всеки ден има нова дума за познаване!", { ul.x + kMarginX, ul.y + kMarginY + 22.0f*kRowHeight, }, colors.at(EColor::Text), kFontSize, false);
                ImGui::PopFont();

                ImGui::PopTextWrapPos();
                ImGui::PopFont();
            }
        }

        // close help window
        if (tShown >= 1.0f) {
            if (ImGui::IsMouseReleased(0) || ImGui::IsKeyPressed(SDL_SCANCODE_ESCAPE)) {
                g_state.help.showWindow = false;
                g_state.help.tHide = T;
            }
        }
    } else {
        const auto tHidden = ::I(T - g_state.help.tHide, kTimeShow);

        g_state.animation(tHidden);

        if (tHidden < 1.0f) {
            // fade-in main window
            drawList->AddRectFilled({ 0.0f, 0.0f }, wSize, ImGui::ColorConvertFloat4ToU32({ 0.0f, 0.0f, 0.0f, (1.0f - tHidden)*kColorFade.w }));
        }
    }

    // puzzles window
    if (g_state.puzzlesWnd.visible(T)) {
        const auto tShown = ::I(T - g_state.puzzlesWnd.tShow, kTimeShow);

        g_state.animation(tShown);

        // fade-out main window
        drawList->AddRectFilled({ 0.0f, 0.0f }, wSize, ImGui::ColorConvertFloat4ToU32({ 0.0f, 0.0f, 0.0f, tShown*kColorFade.w }));

        bool ignoreClose = false;
        bool forceClose = false;

        const float kCurScale = std::min(1.0f, (g_state.keyboardMaxX - g_state.keyboardMinX)/473.0f);
        const float kFontSize = 1.25f*kCurScale;
        const float kWindowYMax = 120.0f*kCurScale;

        {
            // upper-left corner
            const ImVec2 ul = {
                g_state.keyboardMinX,
                0.5f*wSize.y - 0.5f*kWindowYMax,
            };

            // lower-right corner
            const ImVec2 lr = {
                g_state.keyboardMaxX,
                0.5f*wSize.y + 0.5f*kWindowYMax,
            };

            // leave some empty space near the window border
            const float kMarginX = 20.0f;
            const float kMarginY = 10.0f;

            // window floor
            drawList->AddRectFilled(ul, lr, colors.at(EColor::Background), g_state.settings.rectRounding ? 8.0f : 0.0f);
            drawList->AddRect      (ul, lr, colors.at(EColor::AbsentFill), g_state.settings.rectRounding ? 8.0f : 0.0f, 0, 1.0f);

            {
                ImGui::PushTextWrapPos(lr.x - kMarginX);

                ImGui::SetWindowFontScale(kFontSize/kFontScale);
                const float kRowHeight = ImGui::CalcTextSize("A").y;

                ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[2]);

                renderText("Играй предишни издания на Уърдъл:", { ul.x + (g_state.keyboardMaxX - g_state.keyboardMinX) / 2.f, ul.y + kMarginY + 1.0f*kRowHeight, },
                           colors.at(EColor::Text), kFontSize, true);

                renderText("#" + std::to_string(g_state.puzzlesWnd.puzzleId), { ul.x + (g_state.keyboardMaxX - g_state.keyboardMinX) * 0.4f, ul.y + kMarginY + 3.8f*kRowHeight, },
                            colors.at(EColor::Text), 3.f*kCurScale, true);

                ImGui::PopFont();

                ImGui::PopTextWrapPos();

                bool leftArrowPressed = false;
                if (renderText(ICON_FA_ANGLE_LEFT, { ul.x + (g_state.keyboardMaxX - g_state.keyboardMinX) * 0.15f, ul.y + kMarginY + 3.8f*kRowHeight, },
                                colors.at(EColor::Text), 3.f*kCurScale, true)) {
                    ignoreClose = true;
                }
                else {
                    leftArrowPressed = (ImGui::IsItemHovered() && ImGui::IsMouseDown(0)) || ImGui::IsKeyPressed(SDL_SCANCODE_LEFT);
                }

                bool rightArrowPressed = false;
                if (renderText(ICON_FA_ANGLE_RIGHT, { ul.x + (g_state.keyboardMaxX - g_state.keyboardMinX) * 0.7f, ul.y + kMarginY + 3.8f*kRowHeight, },
                                colors.at(EColor::Text), 3.f*kCurScale, true)) {
                    ignoreClose = true;
                }
                else {
                    rightArrowPressed = (ImGui::IsItemHovered() && ImGui::IsMouseDown(0)) || ImGui::IsKeyPressed(SDL_SCANCODE_RIGHT);
                }

                if ((g_state.puzzlesWnd.isLeftHeld || g_state.puzzlesWnd.isRightHeld) &&
                      (ImGui::IsMouseReleased(0) || ImGui::IsKeyReleased(SDL_SCANCODE_LEFT) || ImGui::IsKeyReleased(SDL_SCANCODE_RIGHT))) { // is an arrow no longer being held?
                    ignoreClose = true;
                    g_state.puzzlesWnd.isLeftHeld = false;
                    g_state.puzzlesWnd.isRightHeld = false;
                }
                else if (g_state.puzzlesWnd.isLeftHeld || leftArrowPressed) { // is left arrow being, or about to be held?
                    if (!g_state.puzzlesWnd.isLeftHeld) {
                        g_state.puzzlesWnd.isLeftHeld = true;
                        g_state.puzzlesWnd.nextChangeTime = T + 0.5f;
                        g_state.puzzlesWnd.puzzleId = g_state.puzzlesWnd.puzzleId == 0 ? g_state.puzzleId() : g_state.puzzlesWnd.puzzleId - 1;
                    }
                    else if (T >= g_state.puzzlesWnd.nextChangeTime) {
                        g_state.puzzlesWnd.nextChangeTime = T + 0.05f;
                        g_state.puzzlesWnd.puzzleId = g_state.puzzlesWnd.puzzleId == 0 ? g_state.puzzleId() : g_state.puzzlesWnd.puzzleId - 1;
                    }
                }
                else if (g_state.puzzlesWnd.isRightHeld || rightArrowPressed) { // is right arrow being, or about to be held?
                    if (!g_state.puzzlesWnd.isRightHeld) {
                        g_state.puzzlesWnd.isRightHeld = true;
                        g_state.puzzlesWnd.nextChangeTime = T + 0.5f;
                        g_state.puzzlesWnd.puzzleId = g_state.puzzlesWnd.puzzleId == g_state.puzzleId() ? 0 : g_state.puzzlesWnd.puzzleId + 1;
                    }
                    else if (T >= g_state.puzzlesWnd.nextChangeTime) {
                        g_state.puzzlesWnd.nextChangeTime = T + 0.05f;
                        g_state.puzzlesWnd.puzzleId = g_state.puzzlesWnd.puzzleId == g_state.puzzleId() ? 0 : g_state.puzzlesWnd.puzzleId + 1;
                    }
                }

                if (g_state.puzzlesWnd.puzzleId != g_state.currentPuzzle->id &&
                      (renderText(ICON_FA_PLAY, { ul.x + (g_state.keyboardMaxX - g_state.keyboardMinX) * 0.85f, ul.y + kMarginY + 3.8f*kRowHeight, }, colors.at(EColor::CorrectFill), 2.f*kCurScale, true) ||
                       ImGui::IsKeyPressed(SDL_SCANCODE_RETURN))) {
                    forceClose = true;
                    g_state.keyboardPressHandled = true;
                    g_state.switchPuzzle(g_state.puzzlesWnd.puzzleId);
                }
            }
        }

        // close puzzles window
        if (tShown >= 1.0f) {
            if (forceClose || (!ignoreClose && ImGui::IsMouseReleased(0))) {
                g_state.puzzlesWnd.showWindow = false;
                g_state.puzzlesWnd.tHide = T;
            }
        }
    } else {
        const auto tHidden = ::I(T - g_state.puzzlesWnd.tHide, kTimeShow);

        g_state.animation(tHidden);

        if (tHidden < 1.0f) {
            // fade-in main window
            drawList->AddRectFilled({ 0.0f, 0.0f }, wSize, ImGui::ColorConvertFloat4ToU32({ 0.0f, 0.0f, 0.0f, (1.0f - tHidden)*kColorFade.w }));
        }
    }

    // advert window
    if (g_state.advert.visible(T)) {
        const auto tShown = ::I(T - g_state.advert.tShow, kTimeShow);

        g_state.animation(tShown);

        // fade-out main window
        drawList->AddRectFilled({ 0.0f, 0.0f }, wSize, ImGui::ColorConvertFloat4ToU32({ 0.0f, 0.0f, 0.0f, tShown*kColorFade.w }));

        const float kWindowYMax = 425.0f;

        {
            // upper-left corner
            const ImVec2 ul = {
                g_state.keyboardMinX,
                0.5f*wSize.y - 0.25f*kWindowYMax,
            };

            // lower-right corner
            const ImVec2 lr = {
                g_state.keyboardMaxX,
                0.5f*wSize.y + 0.25f*kWindowYMax,
            };

            // center
            const ImVec2 c0 = {
                0.5f*(ul.x + lr.x),
                0.5f*(ul.y + lr.y),
            };

            // window floor
            drawList->AddRectFilled(ul, lr, colors.at(EColor::Background), g_state.settings.rectRounding ? 8.0f : 0.0f);
            drawList->AddRect      (ul, lr, colors.at(EColor::AbsentFill), g_state.settings.rectRounding ? 8.0f : 0.0f, 0, 1.0f);

            {
                ImGui::SetWindowFontScale(1.25f/kFontScale);
                const float kRowHeight = ImGui::CalcTextSize("A").y;

                renderText("Отгатни скритите думи в новините от вчера", { c0.x, ul.y + 3.0f*kRowHeight, }, colors.at(EColor::Text), 1.25f, true);

                // Advert button
                {
                    const ImVec2 p0 = {
                        ul.x + 0.50f*(lr.x - ul.x),
                        ul.y + 7.0f*kRowHeight,
                    };

                    if (renderTextWithBackground(drawList, "Играй ОТГАТНОВИНИ   " ICON_FA_PLAY, p0, colors.at(EColor::TextSubmitted), colors.at(EColor::CorrectFill), 1.25f, true)) {
                        g_state.dataURL = "https://otgatnovini.ggerganov.com";
                    }
                }
            }
        }

        // close advert window
        if (tShown >= 1.0f) {
            if (ImGui::IsMouseReleased(0) || ImGui::IsKeyPressed(SDL_SCANCODE_ESCAPE)) {
                g_state.advert.showWindow = false;
                g_state.advert.tHide = T;
            }
        }
    } else {
        const auto tHidden = ::I(T - g_state.advert.tHide, kTimeShow);

        g_state.animation(tHidden);

        if (tHidden < 1.0f) {
            // fade-in main window
            drawList->AddRectFilled({ 0.0f, 0.0f }, wSize, ImGui::ColorConvertFloat4ToU32({ 0.0f, 0.0f, 0.0f, (1.0f - tHidden)*kColorFade.w }));
        }
    }

    // statistics window
    if (g_state.statistics.visible(T)) {
        const auto tShown = ::I(T - g_state.statistics.tShow, kTimeShow);

        g_state.animation(tShown);

        // fade-out main window
        drawList->AddRectFilled({ 0.0f, 0.0f }, wSize, ImGui::ColorConvertFloat4ToU32({ 0.0f, 0.0f, 0.0f, tShown*kColorFade.w }));

        bool ignoreClose = false;

        const float kWindowYMax = 425.0f;

        {
            // upper-left corner
            const ImVec2 ul = {
                g_state.keyboardMinX,
                0.5f*wSize.y - 0.5f*kWindowYMax,
            };

            // lower-right corner
            const ImVec2 lr = {
                g_state.keyboardMaxX,
                0.5f*wSize.y + 0.5f*kWindowYMax,
            };

            // center
            const ImVec2 c0 = {
                0.5f*(ul.x + lr.x),
                0.5f*(ul.y + lr.y),
            };

            // leave some empty space near the window border
            const float kMarginX = 60.0f;
            const float kMarginY = 30.0f;

            // window floor
            drawList->AddRectFilled(ul, lr, colors.at(EColor::Background), g_state.settings.rectRounding ? 8.0f : 0.0f);
            drawList->AddRect      (ul, lr, colors.at(EColor::AbsentFill), g_state.settings.rectRounding ? 8.0f : 0.0f, 0, 1.0f);

            {
                ImGui::SetWindowFontScale(1.25f/kFontScale);
                const float kRowHeight = ImGui::CalcTextSize("A").y;

                renderText("СТАТИСТИКА", { c0.x, ul.y + 3.0f*kRowHeight, }, colors.at(EColor::Text), 1.25f, true);

                {
                    const auto num = std::to_string(g_state.statistics.nPlayed);
                    renderText(num,      { c0.x - 0.25f*(lr.x - ul.x), ul.y + 5.0f*kRowHeight, }, colors.at(EColor::Text), 2.00f, true);
                    renderText("Играни", { c0.x - 0.25f*(lr.x - ul.x), ul.y + 6.5f*kRowHeight, }, colors.at(EColor::Text), 1.00f, true);
                }

                {
                    const auto num = std::to_string((int) std::round(g_state.statistics.winPercentage()));
                    renderText(num,         { c0.x - 0.08f*(lr.x - ul.x), ul.y + 5.0f*kRowHeight, }, colors.at(EColor::Text), 2.00f, true);
                    renderText("Познати %", { c0.x - 0.08f*(lr.x - ul.x), ul.y + 6.5f*kRowHeight, }, colors.at(EColor::Text), 1.00f, true);
                }

                {
                    const auto num = std::to_string((int) std::round(g_state.statistics.streakCur));
                    renderText(num,      { c0.x + 0.10f*(lr.x - ul.x), ul.y + 5.0f*kRowHeight, }, colors.at(EColor::Text), 2.00f, true);
                    renderText("Подред", { c0.x + 0.10f*(lr.x - ul.x), ul.y + 6.5f*kRowHeight, }, colors.at(EColor::Text), 1.00f, true);
                }

                {
                    const auto num = std::to_string((int) std::round(g_state.statistics.streakMax));
                    renderText(num,      { c0.x + 0.25f*(lr.x - ul.x), ul.y + 5.0f*kRowHeight, }, colors.at(EColor::Text), 2.00f, true);
                    renderText("Макс.",  { c0.x + 0.25f*(lr.x - ul.x), ul.y + 6.5f*kRowHeight, }, colors.at(EColor::Text), 1.00f, true);
                    renderText("Подред", { c0.x + 0.25f*(lr.x - ul.x), ul.y + 7.5f*kRowHeight, }, colors.at(EColor::Text), 1.00f, true);
                }

                renderText("РАЗПРЕДЕЛЕНИЕ НА ПОЗНАВАНИЯТА", { c0.x, ul.y + 9.0f*kRowHeight, }, colors.at(EColor::Text), 1.25f, true);

                // histogram of guesses
                {
                    const auto maxGuesses = g_state.statistics.maxGuesses();

                    // left edge of the histogram bars
                    const float barX0 = ul.x + kMarginX + 20.f;

                    // min and max length of the histogram bars
                    const float barWidthMin = 30.0f;
                    const float barWidthMax = (lr.x - kMarginX) - barX0 - barWidthMin;

                    for (int i = 0; i < g_state.nAttemptsTotal; ++i) {
                        const ImVec2 p0 = {
                            ul.x + kMarginX,
                            ul.y + 9.5f*kRowHeight + 1.2f*(1.0f + i)*kRowHeight,
                        };

                        renderText(std::to_string(i + 1), p0, colors.at(EColor::Text), 1.00f, true, { 0.5f, 0.0f });

                        const auto curGuesses = g_state.statistics.guesses[i];

                        drawList->AddRectFilled({ barX0, p0.y - 0.5f*kRowHeight}, { barX0 + barWidthMin + (float(curGuesses)/maxGuesses)*barWidthMax, p0.y + 0.5f*kRowHeight }, colors.at(EColor::AbsentFill));

                        renderText(std::to_string(curGuesses), { barX0 + 0.5f*barWidthMin + (float(curGuesses)/maxGuesses)*barWidthMax, p0.y, }, colors.at(EColor::TextSubmitted), 1.00f, true);
                    }
                }

                if (g_state.currentPuzzle->isFinished) {
                    // time left
                    {
                        const ImVec2 p0 = {
                            ul.x + 0.25f*(lr.x - ul.x),
                            ul.y + 10.5f*kRowHeight + 1.2f*(1.0f + g_state.nAttemptsTotal)*kRowHeight,
                        };

                        renderText("СЛЕДВАЩ",           { p0.x, p0.y + 0.5f*kRowHeight, }, colors.at(EColor::Text), 1.25f, true);
                        renderText(g_state.timeLeft(T), { p0.x, p0.y + 2.5f*kRowHeight, }, colors.at(EColor::Text), 3.00f, true);

                        // vertical separator
                        drawList->AddLine({ c0.x, p0.y - 0.5f*kRowHeight, }, { c0.x, lr.y - kMarginY }, colors.at(EColor::Text));
                    }

                    // share button
                    {
                        const ImVec2 p0 = {
                            ul.x + 0.75f*(lr.x - ul.x),
                            ul.y + 12.0f*kRowHeight + 1.2f*(1.0f + g_state.nAttemptsTotal)*kRowHeight,
                        };

                        if (renderTextWithBackground(drawList, "СПОДЕЛИ " ICON_FA_SHARE_ALT, p0, colors.at(EColor::TextSubmitted), colors.at(EColor::CorrectFill), 1.65f, true)) {
                            ignoreClose = true;
                            g_state.updateDataClipboard(colors);
                            g_state.tShared = T;
                            SDL_SetClipboardText(g_state.dataClipboard.c_str());
                        }
                    }
                }
            }
        }

        // close statistics window
        if (tShown >= 1.0f) {
            if (ImGui::IsMouseReleased(0) && ignoreClose == false) {
                g_state.statistics.showWindow = false;
                g_state.statistics.tHide = T;
            }
        }
    } else {
        const auto tHidden = ::I(T - g_state.statistics.tHide, kTimeShow);

        g_state.animation(tHidden);

        if (tHidden < 1.0f) {
            // fade-in main window
            drawList->AddRectFilled({ 0.0f, 0.0f }, wSize, ImGui::ColorConvertFloat4ToU32({ 0.0f, 0.0f, 0.0f, (1.0f - tHidden)*kColorFade.w }));
        }
    }

    // settings window
    if (g_state.settings.visible(T)) {
        const auto tShown = ::I(T - g_state.settings.tShow, kTimeShow);

        g_state.animation(tShown);

        // fade-out main window
        drawList->AddRectFilled({ 0.0f, 0.0f }, wSize, ImGui::ColorConvertFloat4ToU32({ 0.0f, 0.0f, 0.0f, tShown*kColorFade.w }));

        bool ignoreClose = false;

        const float kCurScale = std::min(1.0f, (g_state.keyboardMaxX - g_state.keyboardMinX)/473.0f);
        const float kFontSize = 1.00f*kCurScale;
        const float kWindowYMax = 440.0f*kCurScale;

        {
            // upper-left corner
            const ImVec2 ul = {
                g_state.keyboardMinX,
                0.5f*wSize.y - 0.5f*kWindowYMax,
            };

            // lower-right corner
            const ImVec2 lr = {
                g_state.keyboardMaxX,
                0.5f*wSize.y + 0.5f*kWindowYMax,
            };

            // center
            const ImVec2 c0 = {
                0.5f*(ul.x + lr.x),
                0.5f*(ul.y + lr.y),
            };

            // leave some empty space near the window border
            //const float kMarginX = 20.0f;
            const float kMarginY = 10.0f;

            // window floor
            drawList->AddRectFilled(ul, lr, colors.at(EColor::Background), g_state.settings.rectRounding ? 8.0f : 0.0f);
            drawList->AddRect      (ul, lr, colors.at(EColor::AbsentFill), g_state.settings.rectRounding ? 8.0f : 0.0f, 0, 1.0f);

            {
                ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[2]);

                ImGui::SetWindowFontScale(kFontSize/kFontScale);
                const float kRowHeight = ImGui::CalcTextSize("A").y;

                ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);

                {
                    const float kOffsetY = 4.0f*kRowHeight;
                    const float kIconSize = 3.0f*kFontSize;

                    renderText("НАСТРОЙКИ", { c0.x, ul.y + kMarginY + kOffsetY, }, colors.at(EColor::Text), 1.5f*kFontSize, true);

                    if (renderText(ICON_FA_KEYBOARD, { 0.5f*(ul.x + c0.x), ul.y + kMarginY + kOffsetY + 5.0f*kRowHeight, }, colors.at(EColor::Text), kIconSize, true)) {
                        ignoreClose = true;
                        g_state.settings.tKeyboardSwitched = T;
                        if (g_state.settings.keyboardType == EKeyboardType::Phonetic) {
                            g_state.settings.keyboardTypeNew = EKeyboardType::BDS;
                        } else if (g_state.settings.keyboardType == EKeyboardType::BDS) {
                            g_state.settings.keyboardTypeNew = EKeyboardType::Phonetic;
                        }
                    }

                    if (renderText(ICON_FA_LIGHTBULB, { c0.x, ul.y + kMarginY + kOffsetY + 5.0f*kRowHeight, }, colors.at(EColor::Text), kIconSize, true)) {
                        ignoreClose = true;
                        if (g_state.settings.colorTheme == EColorTheme::Light) {
                            g_state.settings.colorThemeNew = EColorTheme::Dark;
                        } else if (g_state.settings.colorTheme == EColorTheme::Dark) {
                            g_state.settings.colorThemeNew = EColorTheme::Light;
                        }
                    }

                    if (renderBox(drawList, " ", { 0.5f*(c0.x + lr.x), ul.y + kMarginY + kOffsetY + 5.0f*kRowHeight, }, colors.at(EColor::Text), 0.10f, true, { 0.0f, 0.0f, }, g_state.settings.rectRounding ? 0.0f : 8.0f)) {
                        ignoreClose = true;
                        if (g_state.settings.rectRounding == false) {
                            g_state.settings.rectRoundingNew = true;
                        } else if (g_state.settings.rectRounding == true) {
                            g_state.settings.rectRoundingNew = false;
                        }
                    }

                    //const float kOffsetY = 13.0f*kRowHeight;
                    //const float kIconSize = 2.0f*kFontSize;

                    //renderText("СПОДЕЛЯНЕ", { c0.x, ul.y + kMarginY + kOffsetY, }, colors.at(EColor::Text), 1.5f*kFontSize, true);

                    {
                        const auto col = ImGui::ColorConvertU32ToFloat4(colors.at(EColor::Text));
                        const auto colCur = ImGui::ColorConvertFloat4ToU32({ col.x, col.y, col.z, g_state.settings.addHashtag ? 1.0f : 0.5f });

                        if (renderText(ICON_FA_HASHTAG, { ul.x + 0.75f*(c0.x - ul.x), ul.y + kMarginY + kOffsetY + 10.0f*kRowHeight, }, colCur, kIconSize, true)) {
                            ignoreClose = true;
                            if (g_state.settings.addHashtag == false) {
                                g_state.settings.addHashtagNew = true;
                            } else if (g_state.settings.addHashtag == true) {
                                g_state.settings.addHashtagNew = false;
                            }
                        }
                    }

                    {
                        const auto col = ImGui::ColorConvertU32ToFloat4(colors.at(EColor::Text));
                        const auto colCur = ImGui::ColorConvertFloat4ToU32({ col.x, col.y, col.z, g_state.settings.addURL ? 1.00f : 0.25f });

                        if (renderText(ICON_FA_LINK, { lr.x - 0.75f*(lr.x - c0.x), ul.y + kMarginY + kOffsetY + 10.0f*kRowHeight, }, colCur, kIconSize, true)) {
                            ignoreClose = true;
                            if (g_state.settings.addURL == false) {
                                g_state.settings.addURLNew = true;
                            } else if (g_state.settings.addURL == true) {
                                g_state.settings.addURLNew = false;
                            }
                        }
                    }
                }

                {
                    const float kOffsetY = 19.0f*kRowHeight;
                    const float kIconSize = 3.0f*kFontSize;

                    renderText("КОНТАКТИ", { c0.x, ul.y + kMarginY + kOffsetY, }, colors.at(EColor::Text), 1.5f*kFontSize, true);

                    if (renderText(ICON_FA_ENVELOPE, { 0.5f*(ul.x + c0.x), ul.y + kMarginY + kOffsetY + 4.0f*kRowHeight, }, colors.at(EColor::Text), kIconSize, true)) {
                        ignoreClose = true;
                        g_state.dataURL = "mailto:ggerganov@gmail.com?subject=Feedback (wordle-bg)";
                    }

                    if (renderText(ICON_FA_TWITTER, { c0.x, ul.y + kMarginY + kOffsetY + 4.0f*kRowHeight, }, colors.at(EColor::Text), kIconSize, true)) {
                        ignoreClose = true;
                        g_state.dataURL = "https://twitter.com/ggerganov";
                    }

                    if (renderText(ICON_FA_GITHUB, { 0.5f*(c0.x + lr.x), ul.y + kMarginY + kOffsetY + 4.0f*kRowHeight, }, colors.at(EColor::Text), kIconSize, true)) {
                        ignoreClose = true;
                        g_state.dataURL = "https://github.com/ggerganov/wordle-bg";
                    }

                    {
                        const std::string puzzleId = std::string("#") + std::to_string(g_state.currentPuzzle->id);
                        renderText(puzzleId, { lr.x, lr.y, }, colors.at(EColor::PendingBorder), 1.0f, true, { -1.20f, -1.10f, });
                    }
                }

                ImGui::PopFont();

                ImGui::PopFont();
            }
        }

        // close settings window
        if (tShown >= 1.0f) {
            if (ImGui::IsMouseReleased(0) && ignoreClose == false) {
                g_state.settings.showWindow = false;
                g_state.settings.tHide = T;
            }
        }
    } else {
        const auto tHidden = ::I(T - g_state.settings.tHide, kTimeShow);

        g_state.animation(tHidden);

        if (tHidden < 1.0f) {
            // fade-in main window
            drawList->AddRectFilled({ 0.0f, 0.0f }, wSize, ImGui::ColorConvertFloat4ToU32({ 0.0f, 0.0f, 0.0f, (1.0f - tHidden)*kColorFade.w }));
        }
    }

    // copy results to clipboard
    if (g_state.textClipboardVisible && ::within(T, g_state.tShared, kTimeClipboard)) {
        const float kBaseMargin = 25.0f;
        const float kGridHeightMax = g_state.rendering.wSize.y - g_state.heightTitle - g_state.heightKeyboard - 2.0f*kBaseMargin;

        const ImVec2 p0 = {
            0.5f*g_state.rendering.wSize.x,
            g_state.heightTitle + 0.1f*kGridHeightMax + kBaseMargin,
        };

        renderTextWithBackground(drawList, "Резултатите са копирани в клипборда", p0, colors.at(EColor::Background), colors.at(EColor::Title), 1.25f, true);
    }

    // animation indicator in the lower-left corner of the screen
    if (g_state.isAnimating) {
        drawList->AddRectFilled({ 0.0f, wSize.y - 6.0f, }, { 6.0f, wSize.y, }, ImGui::ColorConvertFloat4ToU32({ 1.0f, 1.0f, 0.0f, 0.5f, }));
    }

    ImGui::End();

    ImGui::PopFont();

    ImGui::EndFrame();
}

// called before rendering the new frame
void updatePre() {
    const float T = ImGui::GetTime();

    g_state.update(T);

    if (g_state.settings.keyboardType != g_state.settings.keyboardTypeNew) {
        g_state.settings.keyboard = kKeyboards.at(g_state.settings.keyboardTypeNew);
        g_state.settings.keyboardType = g_state.settings.keyboardTypeNew;
        g_state.updateDataSettings();
    }

    if (g_state.settings.colorTheme != g_state.settings.colorThemeNew) {
        g_state.settings.colors = kColorThemes.at(g_state.settings.colorThemeNew);
        g_state.settings.colorTheme = g_state.settings.colorThemeNew;
        g_state.updateDataSettings();
    }

    if (g_state.settings.rectRounding != g_state.settings.rectRoundingNew) {
        g_state.settings.rectRounding = g_state.settings.rectRoundingNew;
        g_state.updateDataSettings();
    }

    if (g_state.settings.addHashtag != g_state.settings.addHashtagNew) {
        g_state.settings.addHashtag = g_state.settings.addHashtagNew;
        g_state.updateDataSettings();
    }

    if (g_state.settings.addURL != g_state.settings.addURLNew) {
        g_state.settings.addURL = g_state.settings.addURLNew;
        g_state.updateDataSettings();
    }
}

// called after rendering each frame
void updatePost() {
    // handle keyboard presses
    if (!g_state.hasPopup() && !g_state.keyboardPressHandled) {
        switch (g_state.settings.keyboardType) {
            case EKeyboardType::Phonetic:
                {
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_A))            g_input("А");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_B))            g_input("Б");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_C))            g_input("Ц");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_D))            g_input("Д");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_E))            g_input("Е");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_F))            g_input("Ф");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_G))            g_input("Г");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_H))            g_input("Х");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_I))            g_input("И");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_J))            g_input("Й");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_K))            g_input("К");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_L))            g_input("Л");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_M))            g_input("М");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_N))            g_input("Н");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_O))            g_input("О");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_P))            g_input("П");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_Q))            g_input("Я");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_R))            g_input("Р");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_S))            g_input("С");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_T))            g_input("Т");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_U))            g_input("У");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_V))            g_input("Ж");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_W))            g_input("В");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_X))            g_input("Ь");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_Y))            g_input("Ъ");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_Z))            g_input("З");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_GRAVE))        g_input("Ч");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_BACKSLASH))    g_input("Ю");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_LEFTBRACKET))  g_input("Ш");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_RIGHTBRACKET)) g_input("Щ");
                } break;
            case EKeyboardType::BDS:
                {
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_A))            g_input("Ь");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_B))            g_input("Ф");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_C))            g_input("Ъ");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_D))            g_input("А");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_E))            g_input("Е");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_F))            g_input("О");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_G))            g_input("Ж");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_H))            g_input("Г");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_I))            g_input("С");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_J))            g_input("Т");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_K))            g_input("Н");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_L))            g_input("В");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_M))            g_input("П");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_N))            g_input("Х");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_O))            g_input("Д");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_P))            g_input("З");
                    //if (ImGui::IsKeyPressed(SDL_SCANCODE_Q))            g_input("ы");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_R))            g_input("И");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_S))            g_input("Я");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_T))            g_input("Ш");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_U))            g_input("К");
                    //if (ImGui::IsKeyPressed(SDL_SCANCODE_V))            g_input("Э");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_W))            g_input("У");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_X))            g_input("Й");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_Y))            g_input("Щ");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_Z))            g_input("Ю");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_SEMICOLON))    g_input("М");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_APOSTROPHE))   g_input("Ч");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_LEFTBRACKET))  g_input("Ц");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_COMMA))        g_input("Р");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_PERIOD))       g_input("Л");
                    if (ImGui::IsKeyPressed(SDL_SCANCODE_SLASH))        g_input("Б");
                } break;
        }
        if (ImGui::IsKeyPressed(SDL_SCANCODE_RETURN))       g_input(kInputEnter);
        if (ImGui::IsKeyPressed(SDL_SCANCODE_BACKSPACE))    g_input(kInputBackspace);
    }
    g_state.keyboardPressHandled = false;
}

void deinitMain() {
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    printf("Build time: %s\n", BUILD_TIMESTAMP);

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Error: %s\n", SDL_GetError());
        return -1;
    }

    ImGui_PreInit();

    int windowX = 1200;
    int windowY = 800;

#ifdef __EMSCRIPTEN__
    SDL_Renderer * renderer;
    SDL_Window * window;
    SDL_CreateWindowAndRenderer(windowX, windowY, SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI | SDL_RENDERER_PRESENTVSYNC, &window, &renderer);
#else
    const char * windowTitle = kTitle;
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window * window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowX, windowY, window_flags);
#endif

    void * gl_context = SDL_GL_CreateContext(window);

    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    ImGui_Init(window, gl_context);
    ImGui::GetIO().IniFilename = nullptr;

    // this font is not used, but adding it anyway
    {
        ImFontConfig cfg;
        cfg.SizePixels = 13.0f*kFontScale;
        ImGui::GetIO().Fonts->AddFontDefault(&cfg);
    }

    {
        static const ImWchar rangesFAR[] = { ICON_MIN_FA,  ICON_MAX_FA,  0, };
        static const ImWchar rangesFAS[] = { ICON_MIN_FA,  ICON_MAX_FA,  0, };
        static const ImWchar rangesFAB[] = { ICON_MIN_FAB, ICON_MAX_FAB, 0, };
        static const ImWchar * rangesCyr = ImGui::GetIO().Fonts->GetGlyphRangesCyrillic();

        static ImFontConfig configBase;
        configBase.PixelSnapH = true;
        configBase.OversampleH = 1;
        configBase.OversampleV = 1;

        static ImFontConfig configMerge;
        configMerge.MergeMode = true;
        configMerge.GlyphOffset = { 0.0f, 0.0f };
        configMerge.PixelSnapH = true;
        configMerge.OversampleH = 1;
        configMerge.OversampleV = 1;

        ImGui_tryLoadFont("Arimo-Bold.ttf",          14.0f*kFontScale, &configBase,  rangesCyr);
        ImGui_tryLoadFont(FONT_ICON_FILE_NAME_FAR,   14.0f*kFontScale, &configMerge, rangesFAR);
        ImGui_tryLoadFont(FONT_ICON_FILE_NAME_FAS,   14.0f*kFontScale, &configMerge, rangesFAS);
        ImGui_tryLoadFont(FONT_ICON_FILE_NAME_FAB,   14.0f*kFontScale, &configMerge, rangesFAB);
        ImGui_tryLoadFont("Arimo-Regular.ttf",       14.0f*kFontScale, &configBase,  rangesCyr);
    }

    ImGui_BeginFrame(window);
    ImGui::NewFrame();
    ImGui::EndFrame();
    ImGui_EndFrame(window);

    bool isInitialized = false;

    g_doPuzzleInit = [&]() {
        initPuzzle();

        return true;
    };

    g_doGameInit = [&]() {
        initGame();

        isInitialized = true;

        return true;
    };

    g_setWindowSize = [&](int sizeX, int sizeY) {
        static int lastX = -1;
        static int lastY = -1;

        if (lastX == sizeX && lastY == sizeY) {
            return;
        }

        lastX = sizeX;
        lastY = sizeY;

        SDL_SetWindowSize(window, sizeX, sizeY);

        g_state.onWindowResize();
        g_state.isAnimating = true;
    };

    g_mainUpdate = [&]() {
        // framerate throtling when idle
        --g_state.nUpdates;
        if (g_state.nUpdates < -30) g_state.nUpdates = 0;
        if (g_state.isAnimating) g_state.nUpdates = std::max(g_state.nUpdates, 2);

        if (isInitialized == false) {
            return true;
        }

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            g_state.nUpdates = std::max(g_state.nUpdates, 5);
            ImGui_ProcessEvent(&event);
            if (event.type == SDL_QUIT) return false;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window)) return false;
        }

        updatePre();

        if (g_state.nUpdates >= 0) {
            if (ImGui_BeginFrame(window) == false) {
                return false;
            }

            renderMain();
            ImGui_EndFrame(window);
        }

        updatePost();

        return true;
    };

    g_input = [&](const std::string & input) {
        if ((g_state.isAnimating && input == kInputEnter) || g_state.currentPuzzle->isFinished) return;

        auto & cur = g_state.currentPuzzle->attemptCur;

        if (input == kInputBackspace) {
            if (cur.size() > 0) {
                utf8_erase_back(cur);
            }
        } else if (input == kInputEnter) {
            if ((int) utf8_size(cur) == g_state.nLettersPerWord) {
                bool found = false;
                for (const auto & word : g_state.words) {
                    if (word == cur) {
                        found = true;
                        break;
                    }
                }

                if (found) {
                    g_state.currentPuzzle->attempts.emplace_back(std::move(cur));
                    cur.clear();
                } else {
                    g_state.currentPuzzle->tIncorrect = ImGui::GetTime();
                    g_state.currentPuzzle->eIncorrect = State::Puzzle::TypeIncorrect::NotAWord;
                }
            } else {
                g_state.currentPuzzle->tIncorrect = ImGui::GetTime();
                g_state.currentPuzzle->eIncorrect = State::Puzzle::TypeIncorrect::NotEnoughLetters;
            }
        } else {
            if ((int) utf8_size(cur) < g_state.nLettersPerWord) {
                cur += input;
            }
        }

        g_state.newInput = true;
    };

    g_getPuzzleId = [&]() {
        return g_state.currentPuzzle->id;
    };

    g_setAttempts = [&](int puzzleId, const std::string & data) {
        State::Puzzle* puzzle = g_state.getPuzzle(puzzleId);
        puzzle->isInitialized = false;
        puzzle->attempts.clear();

        std::stringstream ss(data);
        std::string word;
        while (getline(ss, word, ' ')) {
            puzzle->attempts.push_back(std::move(word));
        }

        g_state.newInput = true;
    };

    g_getAttempts = [&]() {
        auto res = g_state.currentPuzzle->dataAttempts;
        g_state.currentPuzzle->dataAttempts.clear();
        return res;
    };

    g_setStatistics = [&](const std::string & data) {
        std::stringstream ss(data);

        ss >> g_state.statistics.nPlayed;
        ss >> g_state.statistics.streakCur;
        ss >> g_state.statistics.streakMax;

        int n;
        ss >> n;
        g_state.statistics.guesses.resize(n);
        for (int i = 0; i < n; ++i) {
            ss >> g_state.statistics.guesses[i];
        }
    };

    g_getStatistics = [&]() {
        auto res = g_state.dataStatistics;
        g_state.dataStatistics.clear();
        return res;
    };

    g_setSettings = [&](const std::string & data) {
        std::stringstream ss(data);

        {
            int tmp = -1;
            ss >> tmp;
            if (tmp != -1) {
                g_state.settings.colorThemeNew = (EColorTheme) tmp;
            }
        }

        {
            int tmp = -1;
            ss >> tmp;
            if (tmp != -1) {
                g_state.settings.rectRoundingNew = tmp;
            }
        }

        {
            int tmp = -1;
            ss >> tmp;
            if (tmp != -1) {
                g_state.settings.keyboardTypeNew = (EKeyboardType) tmp;
            }
        }

        {
            int tmp = -1;
            ss >> tmp;
            if (tmp != -1) {
                g_state.settings.addHashtagNew = tmp;
            }
        }

        {
            int tmp = -1;
            ss >> tmp;
            if (tmp != -1) {
                g_state.settings.addURLNew = tmp;
            }
        }
    };

    g_getSettings = [&]() {
        auto res = g_state.dataSettings;
        g_state.dataSettings.clear();
        return res;
    };

    g_getClipboard = [&]() {
        auto res = g_state.dataClipboard;
        g_state.dataClipboard.clear();
        return res;
    };

    g_setClipboardTextVisible = [&](bool visible) {
        g_state.textClipboardVisible = visible;
    };

    g_getURL = [&]() {
        auto res = g_state.dataURL;
        g_state.dataURL.clear();
        return res;
    };

    g_setTimestamp = [&](int64_t timestamp) {
        g_state.timestamp = timestamp;
    };

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(mainUpdate, NULL, 0, true);
#else
    g_setWindowSize(windowX, windowY);

    if (!g_doPuzzleInit() || !g_doGameInit()) {
        printf("Error: failed to initialize\n");
        return -2;
    }

    while (true) {
        if (g_mainUpdate() == false) break;

        {
            int sizeX = -1;
            int sizeY = -1;

            SDL_GetWindowSize(window, &sizeX, &sizeY);
            g_setWindowSize(sizeX, sizeY);
        }
    }

    deinitMain();

    // Cleanup
    ImGui_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
#endif

    return 0;
}
