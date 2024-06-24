![REAL](img/logo.png)

---

## Features

* Audio latency reduction on the default playback device
* Automatic updates

## Requirements

* mingw 64-bit

## Setup

1. Install Windows' in-box HDAudio driver (optional, might improve latency):
    1. Start **Device Manager**.
    2. Under **Sound, video and game controllers**, double click on the device that corresponds to your speakers.
    3. In the next window, go to the **Driver** tab.
    4. Select **Update driver** -> **Browse my computer for driver software** -> **Let me pick from a list of available drivers on my computer**.
    5. Select **High Definition Audio Device** and click **Next**.
    6. If a window titled "Update Driver warning" appears, click **Yes**.
    7. Select **Close**.
    8. If asked to reboot the system, select **Yes** to reboot.
    > **Be careful**: the new driver might reset your volume to uncomfortably high levels. 
2. Download the [latest version](https://github.com/miniant-git/REAL/releases/latest) of **REAL**.
3. Launch `REAL.exe`. The latency reduction is in effect as long as the application is kept running.

## Command-Line Options
* `--tray` Launches the application minimised to the system tray

## Building

1. run make

## FAQ

### How does this work?

As described in Mirosoft's [Low Latency Audio FAQ section](https://docs.microsoft.com/en-us/windows-hardware/drivers/audio/low-latency-audio#span-idfaqspanspan-idfaqspanfaq), by default, all applications in Windows 10 use 10ms buffers to render audio. However, if one application requests the usage of small buffers, then the Audio Engine will start transferring audio using that particular buffer size. In that case, all applications that use the same endpoint (device) and mode (either exclusive or shared) will automatically switch to that small buffer size. We make use of this Audio Engine property by starting a rendering stream which requests the minimal buffer size that is supported by the audio driver.

### What are the downsides?

Since the application reduces audio sample buffer size, the buffer runs out faster and needs to be refilled more frequently. This increases the odds of audible audio cracks appearing when the CPU is busy and unable to keep up. 

### Changes from upstream

- auto-updating removed
- now runs either foreground or as a background application
- switch from msvc to mingw
- github builds now executable for us
