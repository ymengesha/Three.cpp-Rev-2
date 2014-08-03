//
//  NormalMap.cpp
//  Three.cpp Rev.2
//
//  Created by Saburo Okita on 18/07/14.
//  Copyright (c) 2014 Saburo Okita. All rights reserved.
//

#include "NormalMap.h"
#include "three.h"

using namespace std;

namespace three {
    
    ptr<NormalMap> NormalMap::create() {
        return make_shared<NormalMap>();
    }
    
    NormalMap::NormalMap():
        Texture     (TEXTURE_TYPE::TEXTURE_2D),
        normalScale (glm::vec2(1.0, 1.0))
    {}
    
    NormalMap::~NormalMap(){
        if( this->textureID != 0 )
            glDeleteTextures(1, &this->textureID );
    }
    
    
    void NormalMap::setUniforms(ptr<ShaderLib> shader_lib, bool gamma) {
        auto shader = shader_lib->getShader();
        
        /* NORMAL MAP related */
        shader->setUniform( "normal_scale", this->normalScale );
        
        int offset = shader_lib->config[0];
        
        glActiveTexture( GL_TEXTURE0 + offset );
        bind();
        shader->setUniform("normal_map", offset );
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter );
    }
}