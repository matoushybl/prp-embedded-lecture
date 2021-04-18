//
// Created by matous on 18.04.21.
//

#ifndef PRP_LECTURE_EMBEDDED_ROBOT_H
#define PRP_LECTURE_EMBEDDED_ROBOT_H


#include <memory>
#include "Socket.h"

class Robot {
public:
    explicit Robot(std::unique_ptr<Socket> socket);
    bool moveForward();
private:
    std::unique_ptr<Socket> socket;
};


#endif //PRP_LECTURE_EMBEDDED_ROBOT_H
