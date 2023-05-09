#pragma once

#include "DataTexture2DArray.h"
#include "Image.h"
#include <stdexcept>
#include <vector>
#include "Zip.h"


class ImageTexture2DArray : public DataTexture2DArray {
public:
    ImageTexture2DArray(std::string fname) : ImageTexture2DArray(std::vector<std::string>({fname}))
    {}
    
    ImageTexture2DArray(std::vector<std::string> files){
        std::vector<char> membuf;
        this->slices=0;
        int w=0;
        int h=0;
        int slices=0;
        for(auto fname : files ){
            if( endswith( fname, ".png") || endswith(fname,".jpg") ){
                Image img(fname);
                img.flipVertically();
                if( slices == 0 ){
                    w=(int)img.width();
                    h=(int)img.height();
                } else {
                    if(w!=(int)img.width() || h!=(int)img.height())
                        throw std::runtime_error("Size mismatch: "+
                            std::to_string(w)+"x"+std::to_string(h)+" "+
                            std::to_string(img.width())+"x"+std::to_string(img.height()));
                }
                slices += 1;
                membuf.insert( membuf.end(), img.pixels(), img.pixels()+img.width()*img.height()*img.bytesPerPixel());
            } else if( endswith(fname,".ora") || endswith(fname,".zip")){
                Zip z(fname);
                auto namelist = z.namelist();
                sort(namelist.begin(),namelist.end());
                for( auto n : namelist ){
                    if( endswith(fname,".ora") ){
                        if( n.find("thumbnail") != std::string::npos )
                            continue;
                        if( n.find("data") == std::string::npos )
                            continue;
                    }
                            
                    if( endswith(n,".png") || endswith(n,".jpg") ){
                        Image img(z.extract(n));
                        if( slices == 0 ){
                            w = (int)img.width();
                            h = (int)img.height();
                        } else {
                            if( w != (int)img.width() || h != (int)img.height() )
                                throw std::runtime_error("Size mismatch");
                        }
                        slices+=1;
                        membuf.insert( membuf.end(), img.pixels(), img.pixels()+img.width()*img.height()*img.bytesPerPixel());
                    }
                }
            } else {
                throw std::runtime_error("Cannot read file "+fname);
            }
        }
        
        setData( w,h,slices,membuf.data() );
    }
};
