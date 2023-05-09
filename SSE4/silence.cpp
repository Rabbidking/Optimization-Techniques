#include "ymm.h"
#include "Wave.h"
#include "Stopwatch.h"
#include <iostream>

using namespace std;

ymm_u8 zero(0);
ymm_u8 two_fifty_five(255);
 

template<typename T>
void silenceThem_u8( T* ptr, unsigned numFrames, int min, int max, int theSoundOfSilence ){

	for (unsigned j = 0; j < numFrames; j++) 
	{
		ymm_u8 wav((__m256i*)ptr);
		ymm_u8 hi = wav <= max;
		ymm_u8 lo = wav >= min;
		ymm_u8 bounds = hi & lo;
		ymm_u8 tmp = andnot(bounds, wav);
		ymm_u8 tmp2 = bounds & two_fifty_five;
		ymm_u8 merge = tmp2 | tmp;

		merge.store((__m256i*)theSoundOfSilence);
	}

}

template<typename T>
void silenceThem_s16(T* ptr, unsigned numFrames, int min, int max, int theSoundOfSilence) 
{
	for(unsigned j=0;j<numFrames;j++){
		if( ptr[j] >= min && ptr[j] <= max )
			ptr[j] = (T) theSoundOfSilence;
	}
}

int main(int argc, char* argv[])
{
    if( argc != 3 ){
        cout << argv[0] << " filename thresh\n";
        return 1;
    }
    
    string filename = argv[1];
    int thresh = atoi(argv[2]);
    
    Wave w(filename);
    if( w.format.format != Wave::FormatCode::PCM || (w.format.bitsPerSample != 8 && w.format.bitsPerSample != 16 ) ){
        cout << "Not a supported format\n";
        return 1;
    }
    
    Stopwatch swatch;
    swatch.start();
    
    if( w.format.bitsPerSample == 8 ){
        silenceThem_u8( (uint8_t*) w.data(), w.numFrames, 127-thresh, 127+thresh, 127 );
    } else if( w.format.bitsPerSample == 16 ){
        silenceThem_s16( (int16_t*) w.data(), w.numFrames, -thresh, thresh, 0 );
    } else{
        throw runtime_error("Wrong!");
    }
     
    swatch.stop();
    cout << swatch.elapsed_us() << "usec\n";
    w.write("silenced.wav");
    
    return 0;
}
