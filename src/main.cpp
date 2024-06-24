#include "MinimumLatencyAudioClient.h"
#include "../res/resource.h"

#include <windows.h>
#include <conio.h>

#include <locale>
#include <iostream>
#include <sstream>
#include <memory>

#define APP_VERSION (GITHUB_REF_NAME " (" GITHUB_SHA ")")

using namespace miniant::Windows;
using namespace miniant::Windows::WasapiLatency;

void WaitForAnyKey(const std::string& message) {
    while (_kbhit()) {
        _getch();
    }

    std::cout << message << "\n";
    _getch();
}

void DisplayExitMessage(bool success) {
    if (success) {
        WaitForAnyKey("\nPress any key to disable and exit . . .");
    } else {
        WaitForAnyKey("\nPress any key to exit . . .");
    }
}

std::string ToLower(const std::string& string) {
    std::string result;
    for (const auto& c : string) {
        result.append(1, std::tolower(c, std::locale()));
    }

    return result;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    bool success = true;

    std::cout << "REAL - REduce Audio Latency " << APP_VERSION << " mini)(ant (2018-2019), retropc (2024)\n";
    std::cout << "Project: https://github.com/retropc/REAL\n";

    auto audioClient = MinimumLatencyAudioClient::Start();
    if (!audioClient) {
        success = false;
        std::cout << "ERROR: Could not enable low-latency mode.\n";
    } else {
        std::cout << "Minimum audio latency enabled on the DEFAULT playback device!\n";
        auto properties = audioClient->GetProperties();
        if (properties) {
            std::printf(
                "Device properties:\n    Sample rate %5d Hz\n    Buffer size (min) %5d samples (%3f ms) [current]\n    Buffer size (max) %5d samples (%3f ms)\n    Buffer size (default) %5d samples (%3f ms)\n",
                properties->sampleRate,
                properties->minimumBufferSize, 1000.0f * properties->minimumBufferSize / properties->sampleRate,
                properties->maximumBufferSize, 1000.0f * properties->maximumBufferSize / properties->sampleRate,
                properties->defaultBufferSize, 1000.0f * properties->defaultBufferSize / properties->sampleRate);
        }
    }

#ifdef CONSOLE
    DisplayExitMessage(success);
#else
    if (success) {
        for (;;) {
            Sleep(86400);
        }
    }
#endif
    return 0;
}
