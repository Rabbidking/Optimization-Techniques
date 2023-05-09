#include "Camera.h"
#include "ImageTexture2DArray.h"
#include "Mesh.h"
#include "Program.h"
#include "Sampler.h"
#include "ImageTextureCube.h"
#include "Text.h"
#include "utils.h"
#include <iostream>
#include <cassert>
#include <iomanip>
#include "Globals.h"
#include "winsetup.h"

std::unique_ptr<Globals> globs;


#include "setup.h"
#include "draw.h"
#include "update.h"

  
int main(int argc, char* argv[]){
    
    auto win = winsetup();
    
    int cw,ch;
    SDL_GL_GetDrawableSize(win, &cw, &ch);
    setup(cw,ch);
    
    Program::setUniform("screenSize", vec4(cw,ch,1.0f/(cw),1.0f/(ch)));
    
    int DESIRED_FRAMES_PER_SEC = 100000;
    float DESIRED_SEC_PER_FRAME = 1.0f/DESIRED_FRAMES_PER_SEC;
    int DESIRED_MSEC_PER_FRAME = int(DESIRED_SEC_PER_FRAME * 1000);
    auto TICKS_PER_SECOND = SDL_GetPerformanceFrequency();
    int UPDATE_QUANTUM_MSEC = 5;
    int UPDATE_QUANTUM_USEC = UPDATE_QUANTUM_MSEC*1000;
    
    
    int64_t numFrames=0;
    auto lastTicks = SDL_GetPerformanceCounter();
    auto lastFPSReportTime = lastTicks;
    auto nextFPSReportTime = lastFPSReportTime + TICKS_PER_SECOND;
    
    int accumElapsedUsec = 0;
    while(true){
        auto nowTicks = SDL_GetPerformanceCounter();
        uint64_t elapsedTicks = nowTicks - lastTicks;
        lastTicks = nowTicks;
        auto elapsedUsec = int(1000000 * elapsedTicks / TICKS_PER_SECOND);
        accumElapsedUsec += elapsedUsec;
        while(accumElapsedUsec >= UPDATE_QUANTUM_USEC){
            update(UPDATE_QUANTUM_MSEC);
            accumElapsedUsec -= UPDATE_QUANTUM_USEC;
        }
        draw();
        globs->text1.draw();
        globs->text2.draw();
        ++numFrames;
        SDL_GL_SwapWindow(win);
        auto endTicks = SDL_GetPerformanceCounter();
        if( endTicks >= nextFPSReportTime ){
            nextFPSReportTime = endTicks + 1 * TICKS_PER_SECOND;
            {
                int fps = (int)(10 * numFrames * TICKS_PER_SECOND / (endTicks - lastFPSReportTime));
                int ipart = fps/10;
                int fpart = fps%10;
                std::ostringstream oss;
                oss << "FPS: " << ipart << "." << fpart;
                globs->text1.setText(oss.str());
            }
            
            {
                double spf = (endTicks - lastFPSReportTime) * 1.0/(numFrames * TICKS_PER_SECOND );
                int ipart = int(spf);
                int fpart = int( (spf-ipart) * 1000 );
                std::ostringstream oss;
                oss << "Sec per frame: " << ipart << "." << std::setfill('0') << std::setw(3) << fpart;
                globs->text2.setText(oss.str());
            }

            numFrames=0;
            lastFPSReportTime = endTicks;
        }
        auto frameTicks = endTicks - nowTicks;
        auto frameMsec = int(1000*frameTicks / TICKS_PER_SECOND);
        auto leftoverMsec = DESIRED_MSEC_PER_FRAME - frameMsec;
        
        if(leftoverMsec > 0)
            SDL_Delay(leftoverMsec);
    }
    
    return 0;
}
    
