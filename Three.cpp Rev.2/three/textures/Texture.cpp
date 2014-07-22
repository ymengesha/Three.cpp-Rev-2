//
//  Texture.cpp
//  Three.cpp Rev.2
//
//  Created by Saburo Okita on 16/07/14.
//  Copyright (c) 2014 Saburo Okita. All rights reserved.
//

#include "Texture.h"
#include "three.h"

using namespace std;

namespace three {
    
    ptr<Texture> Texture::create() {
        return make_shared<Texture>();
    }

    Texture::Texture() :
        HasID    ( textureIDCount++ ),
        textureID( 0 ),
        width    ( 0 ),
        height   ( 0 ),
        wrapS    ( GL_REPEAT ),
        wrapT    ( GL_REPEAT ),
        wrapR    ( GL_REPEAT ),
        magFilter( GL_LINEAR ),
        minFilter( GL_LINEAR )
    {}
    
    
    Texture::Texture(GLuint wrap_s, GLuint wrap_t, GLuint wrap_r, GLuint mag_filter, GLuint min_filter) :
        HasID    ( textureIDCount++ ),
        textureID( 0 ),
        width    ( 0 ),
        height   ( 0 ),
        wrapS    ( wrap_s ),
        wrapT    ( wrap_t ),
        wrapR    ( wrap_r ),
        magFilter( mag_filter ),
        minFilter( min_filter )
    {}
    
    Texture::~Texture(){
        if( this->textureID != 0 )
            glDeleteTextures(1, &this->textureID );
    }
    
    void Texture::setUniforms(ptr<Shader> shader, bool gamma) {
        glActiveTexture( GL_TEXTURE0 );
        glBindTexture( GL_TEXTURE_2D, this->textureID );
        shader->setUniform("map", 0);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter );
    }
}