
// Background info on FS dithering:
//  http://www.tannerhelland.com/4660/dithering-eleven-algorithms-source-code/
//  https://www.cyotek.com/blog/an-introduction-to-dithering-images

#include <chrono>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <tuple>
#include <set>
#include "math3d.h"
#include "Image.h"

Image computeDitheredNbitColor(Image img, int shiftCount)
{
    std::vector<vec3> error1(img.width());
    std::vector<vec3> error2(img.width());
    
    int divisor = 1<<shiftCount;
    
    for(unsigned y=0;y<img.height();++y){
        error1=error2;
        for(unsigned i=0;i<error2.size();++i)
            error2[i]=vec3(0,0,0);
        for(unsigned x=0;x<img.width();++x){
            uint8_t r,g,b,a;
            img.getPixel(x,y,r,g,b,a);
            ivec3 want = ivec3(r,g,b);
            ivec3 error;
            ivec3 out;
            for(int i=0;i<3;++i){
                want[i] += error1[x][i];
                
                out[i] = (want[i]/divisor) * divisor;
                error[i] = want[i]-out[i];
                
                if( x < img.width()-1 ){
                    error1[x+1][i] = 7*error[i]/16;
                    error2[x+1][i] = 1*error[i]/16;
                }
                if( x > 0 )
                    error2[x-1][i] = 3*error[i]/16;
                error2[x][i] = 5*error[i]/16;
            }
            img.setPixel(x,y,out[0],out[1],out[2]);
        }
    }
    return img;
}
Image computeDithered1BitColor(Image img){
    std::vector<vec3> error1(img.width());
    std::vector<vec3> error2(img.width());
    
    for(unsigned y=0;y<img.height();++y){
        error1=error2;
        for(unsigned i=0;i<error2.size();++i)
            error2[i]=vec3(0,0,0);
        for(unsigned x=0;x<img.width();++x){
            uint8_t r,g,b,a;
            img.getPixel(x,y,r,g,b,a);
            vec3 want = vec3(r,g,b);
            vec3 error;
            vec3 out;
            for(int i=0;i<3;++i){
                want[i] += error1[x][i];
                if( want[i] < 128 ){
                    out[i] = 0;
                    error[i] = want[i];
                } else {
                    out[i] = 255;
                    error[i] = -(255-want[i]);
                }
                if( x < img.width()-1 ){
                    error1[x+1][i] = 7*error[i]/16;
                    error2[x+1][i] = 1*error[i]/16;
                }
                if( x > 0 )
                    error2[x-1][i] = 3*error[i]/16;
                error2[x][i] = 5*error[i]/16;
            }
            img.setPixel(x,y,out[0],out[1],out[2]);
        }
    }
    return img;
}


Image computeGreyscale(Image img){
    //convert to greyscale
    for(unsigned y=0;y<img.height();++y){
        for(unsigned x=0;x<img.width();++x){
            uint8_t r,g,b,a;
            img.getPixel(x,y,r,g,b,a);
            int total = (int)(0.299*r + 0.587*g + 0.114*b);
            if( total > 255 )
                total = 255;
            r = (uint8_t) total;
            img.setPixel(x,y,r,r,r,255);
        }
    }
    return img;
}
Image computeDitheredBilevel(Image img){
    //floyd steinberg error diffusion
    std::vector<int> error1(img.width());
    std::vector<int> error2(img.width());
    
    for(unsigned y=0;y<img.height();++y){
        error1=error2;
        for(unsigned i=0;i<error2.size();++i)
            error2[i]=0;
        for(unsigned x=0;x<img.width();++x){
            uint8_t r,g,b,a;
            img.getPixel(x,y,r,g,b,a);
            int want = r+g+b;
            want /= 3;
            want += error1[x];
            int error;
            if( want < 128 ){
                //closer to black than white, so set output to black
                img.setPixel(x,y,0,0,0,255);
                error = want;
            } else {
                img.setPixel(x,y,255,255,255,255);
                error = -(255-want);
            }
            if( x < img.width()-1 ){
                error1[x+1] = 7*error/16;
                error2[x+1] = 1*error/16;
            }
            if( x > 0 )
                error2[x-1] = 3*error/16;
            error2[x] = 5*error/16;
        }
    }
    return img;
}    

int countColors(std::string filename){
    std::vector<std::tuple<uint8_t>> M;
    int unique=0;
    Image img(filename);
    for(unsigned y=0;y<img.height();++y){
        for(unsigned x=0;x<img.width();++x){
            uint8_t r,g,b,a;
            img.getPixel(x,y,r,g,b,a);
			std::tuple<uint8_t> v = (r,g,b);
            //ivec3 v(r,g,b);	//CHANGE THIS TO A TUPLE
            if( find(M.begin(),M.end(),v) == M.end() ){
                M.push_back(v);
                unique++;
            }
        }
    }
    return unique;
}

int main(int argc, char* argv[])
{
    auto start = std::chrono::high_resolution_clock::now();

    //std::vector<std::string> outputs; //CHANGE THIS TO SET
	std::set<std::string> outputs;
    
    Image img1(argv[1]);
    std::string fname;
    
    auto img = computeDitheredNbitColor(img1,4);
    fname = "out-dithered-color-16.png";
    img.writePng(fname);
    //outputs.push_back(fname);
	outputs.insert(fname);

    img = computeDitheredNbitColor(img1,3);
    fname = "out-dithered-color-32.png";
    img.writePng(fname);
	//outputs.push_back(fname);
	outputs.insert(fname);
    
    img = computeDithered1BitColor(img1);
    fname = "out-dithered-color-1.png";
    img.writePng(fname);
	//outputs.push_back(fname);
	outputs.insert(fname);
     
    img = computeGreyscale(img1);
    fname = "out-greyscale.png";
    img.writePng(fname);
	//outputs.push_back(fname);
	outputs.insert(fname);
    
    img = computeDitheredBilevel(img1);
    fname = "out-dithered-bilevel.png";
    img.writePng(fname);
	//outputs.push_back(fname);
	outputs.insert(fname);

    std::ofstream countfile("out-colorcount.txt");
    for(unsigned i=0;i<outputs.size();++i){
		auto o = *std::next(outputs.begin(), i);
        //int numColors = countColors(outputs[i]);
        //countfile << outputs[i] << ": " << numColors << " unique colors\n";
		int numColors = countColors(o);
		countfile << o << ": " << numColors << " unique colors\n";
    }
    countfile.close();
    
    auto end = std::chrono::high_resolution_clock::now();
    auto delta = std::chrono::duration<double>(end-start).count();
    std::cout << delta << " seconds\n";

    return 0;
}

