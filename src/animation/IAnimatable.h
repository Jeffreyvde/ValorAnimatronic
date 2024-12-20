#ifndef IANIMATABLE_H
#define IANIMATABLE_H

#pragma once

#include <string>

/**
 * @brief An interface for an object that is a part of an animation
 * 
 */
class IAnimatable
{
public:
    ~IAnimatable() = default;
    
    /**
     * @brief Instruct an animatable to start a specific instruction
     * 
     * @param instruction The instruction for what the animatable object should do 
     */
    virtual void Start(const std::string& instruction) = 0;

    /**
     * @brief Check if the animatable object has fulfilled the task
     * 
     * @return true if it is finished
     * @return false if it has not
     */
    virtual bool IsFinished() = 0;

    /**
     * @brief Cancel the animation
     * 
     */
    virtual void Stop() = 0;

private:

};

#endif