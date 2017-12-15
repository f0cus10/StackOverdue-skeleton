//
//  Time.hpp
//  StackOverdue
//
//  Created by Iftikhar Khan on 12/14/17.
//  Copyright © 2017 Iftikhar Khan. All rights reserved.
//

#ifndef Time_hpp
#define Time_hpp

#include <iostream>
class Time{
public:
  unsigned int getTime() const {return time; }
  void updateTime(unsigned int);
private:
  unsigned int time = 1;
};

#endif /* Time_hpp */
