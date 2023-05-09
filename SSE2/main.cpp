#include "Image.h"
#include <intrin.h>
#include <stdlib.h>
#include <string>
#include <cstdint>
#include "Stopwatch.h"

using namespace std;

int main(int argc, char* argv[])
{
    string fname = argv[1];
    int deltaI = atoi(argv[2]);
    Image img(fname);

	Stopwatch swatch;
	swatch.start();
    
    //number of bytes to process. bytesPerPixel might be 
    //3 (RGB) or 4 (RGBA)
    unsigned num = img.width()*img.height()*img.bytesPerPixel();
    
    uint8_t* p = img.pixels();

	alignas(8) uint8_t delta[16];
	for (int i = 0; i < sizeof(delta); i++)
	{
		if ((i + 1) % 4 == 0)
			delta[i] = 0;
		else
			delta[i] = fabs(deltaI);
	}
    
    /*for(unsigned i=0;i<num;i+=img.bytesPerPixel()){
        //make sure we don't change alpha channel, if there is one...
        for(int j=0;j<3;++j){
            //do 3 times: R,G,B. Skip A.
            int tmp = p[i+j];
            tmp += deltaI;
            if( tmp > 255 )
                tmp = 255;
            if( tmp < 0 )
                tmp = 0;
            p[i+j] = uint8_t(tmp);
        }
    }*/

	for (unsigned i = 0; i < num; i += img.bytesPerPixel() * 4)
	{
		//2 loads si128, then do adds, store them back into original array
		__m128i pic = _mm_loadu_si128((__m128i*)&p[i]);
		__m128i tmp = _mm_loadu_si128((__m128i*)delta);

		if (deltaI > 0)
			pic = _mm_adds_epu8(pic, tmp);
		else if (deltaI < 0)
			pic = _mm_subs_epu8(pic, tmp);

		_mm_storeu_si128((__m128i*)&p[i], pic);
	}

	swatch.stop();
	cout << swatch.elapsed_us() << "usec\n";

    img.writePng("out.png");
    return 0;
}
