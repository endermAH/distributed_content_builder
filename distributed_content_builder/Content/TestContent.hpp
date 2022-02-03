//
//  TestContent.hpp
//  distributed_content_builder
//
//  Created by Евгений Курятов on 03.02.2022.
//

#ifndef TestContent_hpp
#define TestContent_hpp

#include <stdio.h>
#include "IContent.h"

class TestContent : public IContent {
public:
    int size_;
public:
    TestContent(int size) {
        size_ = size;
    }
    
    int GetSize() {
        return size_;
    }
};

#endif /* TestContent_hpp */
