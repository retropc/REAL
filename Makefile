ARCH=x86_64-w64-mingw32
CXX=$(ARCH)-g++
WINDRES=$(ARCH)-windres
CXXFLAGS=-Ideps/expected/include -std=c++17 -municode -DWINVER=0x0A00 -D_WIN32_WINNT=0x0A00
LDFLAGS=-lole32 -s -municode

SOURCES=src/main.cpp src/MinimumLatencyAudioClient.cpp src/WindowsError.cpp res/real-app.res
.PHONY: clean default

default: real.exe real-console.exe

res/real-app.res: res/real-app.rc
	$(WINDRES) $^ -O coff -o $@

real.exe: $(SOURCES)
	$(CXX) -o $@ $(CXXFLAGS) $^ $(LDFLAGS) -mwindows

real-console.exe: $(SOURCES)
	$(CXX) -o $@ -DCONSOLE $(CXXFLAGS) $^ $(LDFLAGS) -mconsole

clean:
	rm -f src/*.o res/*.res real.exe real-console.exe
