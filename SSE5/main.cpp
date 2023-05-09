#include "ymm.h"
#include "Image.h"
#include "Stopwatch.h"
#include <iostream>


int main(int argc, char* argv[])
{
    if( argc != 2 ){
        std::cout << "Usage: " << argv[0] << " imageFile\n";
        return 1;
    }
    
    Image img(argv[1]);
    if( img.format() != "RGBA8" ){
        std::cout << "Unsupported image format\n";
        return 1;
    }
    
    Stopwatch swatch;
    swatch.start();
    
    unsigned w=img.width();
    unsigned h=img.height();
    unsigned numBytes = w*h*4;

	//ymm_u8 variables
	ymm_u8 zero(0);
	ymm_u8 sixty_three(63);
	ymm_u8 sixty_four(64);
	ymm_u8 ninety_six(96);
	ymm_u8 one_twenty_seven(127);
	ymm_u8 one_twenty_eight(128);
	ymm_u8 one_seventy_two(172);
	ymm_u8 one_ninety_one(191);
	ymm_u8 one_ninety_two(192);
	ymm_u8 two_fifty_five(255);

    uint8_t* p = img.pixels();

    /*for(unsigned i=0;i<numBytes;++i,++p){
        if( *p < 64 )
            *p = 0;
        else if( *p < 128 )
            *p = 96;
        else if( *p < 192 )
            *p = 172;
        else
            *p = 255;
    }*/

	for (unsigned i = 0; i < numBytes; ++i, ++p)
	{
		ymm_u8 pic((__m256i*)p);

		//0-63 range
		ymm_u8 hi = pic <= sixty_three;		//high bounds for the first check
		ymm_u8 lo = pic >= zero;			//low bounds for the first check
		ymm_u8 bounds = hi & lo;			//and'ing the bounds together
		ymm_u8 tmp = andnot(bounds, pic);	//and-not'ing the full range.	tmp is what you want to replace
		ymm_u8 tmp2 = bounds & zero;		//tmp2 is where you're replacing and what you're replacing with
		ymm_u8 merged = tmp2 | tmp;			//merging the two tmp's together

		//64-127 range
		hi = pic <= one_twenty_seven;
		lo = pic >= sixty_four;
		bounds = hi & lo;
		tmp = andnot(bounds, merged);
		tmp2 = bounds & ninety_six;
		ymm_u8 merged2 = tmp2 | tmp;

		//128-191 range
		hi = pic <= one_ninety_one;
		lo = pic >= one_twenty_eight;
		bounds = hi & lo;
		tmp = andnot(bounds, merged2);
		tmp2 = bounds & one_seventy_two;
		ymm_u8 merged3 = tmp2 | tmp;

		//192-255 range
		hi = pic <= two_fifty_five;
		lo = pic >= one_ninety_two;
		bounds = hi & lo;
		tmp = andnot(bounds, merged3);
		tmp2 = bounds & two_fifty_five;
		ymm_u8 merged4 = tmp2 | tmp;

		//store output
		//std::cout << merged;
		merged4.store(p);
	}
    swatch.stop();
    std::cout << "Elapsed time: " << swatch.elapsed_ms() << " millisec\n";
    img.writePng("posterized.png");
    return 0;
}