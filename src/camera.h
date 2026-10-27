#ifndef CAMERA_H
#define CAMERA_H

#include "vector_util.h"
#include <SFML/System.hpp>


// 
// pWindow = mWindowSize/2 + (pWorld - mViewCenterWorld)
class Camera {
public:
    Camera(const sf::Vector2f& windowSize, const sf::Vector2f& viewCenterWorld,
           float worldUnitsPerPixel = 1.f)
        : mWindowSize{windowSize},
          mViewCenterWorld{viewCenterWorld},
          mWorldUnitsPerPixel{worldUnitsPerPixel} {}

    // TODO: all of these:

    sf::Vector2f windowToWorld(const sf::Vector2f& pWindow) {   
        sf::Vector2f division = {2.f,2.f};
        // std::cout <<"Window: "<< pWindow <<"\n";
        // std::cout <<"mWindowSize: "<< mWindowSize <<"\n";
        // std::cout <<"mViewCenterWorld: "<< mViewCenterWorld <<"\n";
        sf::Vector2f pWorld =  mViewCenterWorld + (pWindow - mWindowSize/division)*mWorldUnitsPerPixel;
        //pWorld = pWorld * mWorldUnitsPerPixel;
        std::cout<<"world"<< pWorld <<"\n\n";
        return pWorld;
    };

    sf::Vector2f worldToWindow(const sf::Vector2f& pWorld) { 
        sf::Vector2f division = {2.f,2.f};
        // std::cout <<"world: "<< pWorld <<"\n";
        // std::cout <<"mWindowSize: "<< mWindowSize <<"\n";
        // std::cout <<"mViewCenterWorld: "<< mViewCenterWorld <<"\n";
        sf::Vector2f pWindow = (pWorld - mViewCenterWorld)/mWorldUnitsPerPixel + mWindowSize/division;
        //pWindow = pWindow / mWorldUnitsPerPixel;
        //std::cout <<"world to window: "<< pWindow <<"\n\n";
        return pWindow;
    };

    sf::Vector2f windowPercentToWorld(const sf::Vector2f& pWindowPercent) { 
        sf::Vector2f division = {2.f,2.f};
        // std::cout <<"Window Percent: "<< pWindowPercent <<"\n";
        // std::cout <<"mWindowSize: "<< mWindowSize <<"\n";
        // std::cout <<"mViewCenterWorld: "<< mViewCenterWorld <<"\n";
        sf::Vector2f normalizedWindowCoord = mWindowSize*pWindowPercent;
        // std::cout <<"normalizedWindowCoord: "<< normalizedWindowCoord <<"\n";
        sf::Vector2f pWorld =  mViewCenterWorld + (normalizedWindowCoord - mWindowSize/division)*mWorldUnitsPerPixel;
        //pWorld = pWorld * mWorldUnitsPerPixel;
        std::cout<<"world"<< pWorld <<"\n\n";
        return pWorld;
     };

    sf::Vector2f worldToWindowPercent(const sf::Vector2f& pWorld) {
        sf::Vector2f division = {2.f,2.f};
        // std::cout <<"world: "<< pWorld <<"\n";
        // std::cout <<"mWindowSize: "<< mWindowSize <<"\n";
        // std::cout <<"mViewCenterWorld: "<< mViewCenterWorld <<"\n";
        sf::Vector2f pWindow = (pWorld - mViewCenterWorld)/mWorldUnitsPerPixel + mWindowSize/division;
        sf::Vector2f normalizedWindowCoord = pWindow/mWindowSize;
        // std::cout <<"world to window: "<< pWindow <<"\n";
        // std::cout <<"normalizedWindowCoord: "<< normalizedWindowCoord <<"\n\n";
        return normalizedWindowCoord;
    };

    void translateWorld(const sf::Vector2f& deltaWorld) {
        // std::cout <<"Deltaworld: "<< deltaWorld <<"\n";
        // std::cout <<"mViewCenterWorld Before: "<< mViewCenterWorld <<"\n";
        mViewCenterWorld = mViewCenterWorld + deltaWorld;
        // std::cout <<"mViewCenterWorld After:: "<< mViewCenterWorld <<"\n\n";
    };

    void translateWindow(const sf::Vector2f& deltaScreen) {
        std::cout <<"Deltawindow: "<< deltaScreen <<"\n";
        std::cout <<"mViewCenterWorld Before: "<< mViewCenterWorld <<"\n";
        mViewCenterWorld = mViewCenterWorld + deltaScreen/mWorldUnitsPerPixel;
        std::cout <<"mViewCenterWorld After:: "<< mViewCenterWorld <<"\n\n";
    };

    void translateWindowPercent(const sf::Vector2f& deltaScreenPercent) {
        
        std::cout <<"Deltawindow Percent: "<< deltaScreenPercent <<"\n";
        std::cout <<"mViewCenterWorld Before: "<< mViewCenterWorld <<"\n";
        mViewCenterWorld = mViewCenterWorld + (deltaScreenPercent*mWindowSize)/mWorldUnitsPerPixel;
        std::cout <<"mViewCenterWorld After:: "<< mViewCenterWorld <<"\n\n";
    };

    void setCamera(const sf::Vector2f& pWorld, const sf::Vector2f& pWindow) {
        sf::Vector2f division = {2.f,2.f};
        // std::cout <<"Camera set pworld: "<< pWorld <<"\n";
        // std::cout <<"Camera set pWindow: "<< pWindow <<"\n";
        // std::cout <<"mViewCenterWorld Before: "<< mViewCenterWorld <<"\n";
        mViewCenterWorld = pWorld - (pWindow - mWindowSize/division)*mWorldUnitsPerPixel;
        // std::cout <<"mViewCenterWorld After:: "<< mViewCenterWorld <<"\n\n";
    };

    void setCameraPercent(const sf::Vector2f& pWorld, const sf::Vector2f& pWindowPercent) {
        sf::Vector2f division = {2.f,2.f};
        // std::cout <<"Camera set pworld: "<< pWorld <<"\n";
        // std::cout <<"Camera set pWindowPercent: "<< pWindowPercent <<"\n";
        // std::cout <<"mViewCenterWorld Before: "<< mViewCenterWorld <<"\n";
        sf::Vector2f normalizedWindowCoord = mWindowSize*pWindowPercent;
        mViewCenterWorld = pWorld -(normalizedWindowCoord - mWindowSize/division)*mWorldUnitsPerPixel;
        // std::cout <<"mViewCenterWorld After:: "<< mViewCenterWorld <<"\n\n";

    };

    void setCameraCenter(const sf::Vector2f& pWorld) {
        // std::cout <<"Camera set Center pworld: "<< pWorld <<"\n";
        mViewCenterWorld = pWorld;
        // std::cout <<"mViewCenterWorld After:: "<< mViewCenterWorld <<"\n\n";
    };

    sf::Vector2f getCameraCenter() const { return mViewCenterWorld; };

private:
    sf::Vector2f mWindowSize;       // size of the window in screen pixels (i.e. window coords)
    sf::Vector2f mViewCenterWorld;  // world coords point corresponding to the center of our window.
    float mWorldUnitsPerPixel;      // distance in world coords covered by one pixel
};

#endif  // CAMERA_H
