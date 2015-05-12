/******************************************************************************\
* Copyright (C) 2012-2014 Leap Motion, Inc. All rights reserved.               *
* Leap Motion proprietary and confidential. Not for distribution.              *
* Use subject to the terms of the Leap Motion SDK Agreement available at       *
* https://developer.leapmotion.com/sdk_agreement, or another agreement         *
* between Leap Motion and you, your company or other organization.             *
\******************************************************************************/

#include <iostream>
#include <string.h>
#include <Windows.h>
#include <vector>
#include "Leap.h"
#define WINVER 0x0500




using namespace Leap;

class SampleListener : public Listener {
  public:
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onExit(const Controller&);
    virtual void onFrame(const Controller&);
    virtual void onFocusGained(const Controller&);
    virtual void onFocusLost(const Controller&);
    virtual void onDeviceChange(const Controller&);
    virtual void onServiceConnect(const Controller&);
    virtual void onServiceDisconnect(const Controller&);

  private:
};

const std::string fingerNames[] = {"Thumb", "Index", "Middle", "Ring", "Pinky"};
const std::string boneNames[] = {"Metacarpal", "Proximal", "Middle", "Distal"};
const std::string stateNames[] = {"STATE_INVALID", "STATE_START", "STATE_UPDATE", "STATE_END"};


void Key (int press){
	   // This structure will be used to create the keyboard
    // input event.
    INPUT ip;
 
    // Set up a generic keyboard event.
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0; // hardware scan code for key
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
 
    // Press the "A" key
    ip.ki.wVk = press; // virtual-key code for the "a" key
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));
	Sleep(500);
    // Release the "A" key
    ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
    SendInput(1, &ip, sizeof(INPUT));
}

void KeyH (int press){
	   // This structure will be used to create the keyboard
    // input event.
    INPUT ip;
 
    // Set up a generic keyboard event.
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0; // hardware scan code for key
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
    Sleep(500);
    // Press the "A" key
    ip.ki.wVk = press; // virtual-key code for the "a" key
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));
	Sleep(100);
    // Release the "A" key
    ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
    SendInput(1, &ip, sizeof(INPUT));
}

void DoubleKey (int pressA, int pressB){

    // Create a generic keyboard event structure.
    INPUT ip;
	// Set up a generic keyboard event.
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
 
    // Press the first key
	ip.ki.wVk = pressA;
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));
    // Press the second key
    ip.ki.wVk = pressB;
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));
 	Sleep(500);
	// Release the first key
    ip.ki.wVk = pressA;
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));

    // Release the second key
    ip.ki.wVk = pressB;
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));
}

void DoubleKeyDel (int pressA, int pressB){

    // Create a generic keyboard event structure.
    INPUT ip;
	// Set up a generic keyboard event.
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;


    // Press the first key
	ip.ki.wVk = pressA;
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));
	Sleep(500);
    // Press the second key
    ip.ki.wVk = pressB;
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));
 	Sleep(500);
	// Release the first key
    ip.ki.wVk = pressA;
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));
    // Release the second key
    ip.ki.wVk = pressB;
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));
	
    

}

void SampleListener::onInit(const Controller& controller) {
  std::cout << "Initialized" << std::endl;
}

void SampleListener::onConnect(const Controller& controller) {
  std::cout << "Connected" << std::endl;
  controller.enableGesture(Gesture::TYPE_CIRCLE);
  controller.enableGesture(Gesture::TYPE_KEY_TAP);
  controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
  controller.enableGesture(Gesture::TYPE_SWIPE);
}

void SampleListener::onDisconnect(const Controller& controller) {
  // Note: not dispatched when running in a debugger.
  std::cout << "Disconnected" << std::endl;
}

void SampleListener::onExit(const Controller& controller) {
  std::cout << "Exited" << std::endl;
}

void SampleListener::onFrame(const Controller& controller) {
  // Get the most recent frame and report some basic information
  const Frame frame = controller.frame();
  std::cout << "Frame id: " << frame.id()
            << ", timestamp: " << frame.timestamp()
            << ", hands: " << frame.hands().count()
            << ", extended fingers: " << frame.fingers().extended().count()
            << ", tools: " << frame.tools().count()
            << ", gestures: " << frame.gestures().count() << std::endl;

  HandList hands = frame.hands();
  for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {
    // Get the first hand
    const Hand hand = *hl;
    std::string handType = hand.isLeft() ? "Left hand" : "Right hand";
    std::cout << std::string(2, ' ') << handType << ", id: " << hand.id()
              << ", palm position: " << hand.palmPosition() << std::endl;
    // Get the hand's normal vector and direction
    const Vector normal = hand.palmNormal();
    const Vector direction = hand.direction();
	Vector pp = hand.palmPosition();
	if(hand.isLeft() && pp.y <= 100){
		Key(83);
	}
	if(hand.isLeft() && pp.y >= 400){
		Key(87);
	}
	

    // Calculate the hand's pitch, roll, and yaw angles
    std::cout << std::string(2, ' ') <<  "pitch: " << direction.pitch() * RAD_TO_DEG << " degrees, "
              << "roll: " << normal.roll() * RAD_TO_DEG << " degrees, "
              << "yaw: " << direction.yaw() * RAD_TO_DEG << " degrees" << std::endl;

    // Get the Arm bone
    Arm arm = hand.arm();
    std::cout << std::string(2, ' ') <<  "Arm direction: " << arm.direction()
              << " wrist position: " << arm.wristPosition()
              << " elbow position: " << arm.elbowPosition() << std::endl;

    // Get fingers
    const FingerList fingers = hand.fingers();
    for (FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); ++fl) {
	const Finger finger = *fl;
      std::cout << std::string(4, ' ') <<  fingerNames[finger.type()]
                << " finger, id: " << finger.id()
                << ", length: " << finger.length()
                << "mm, width: " << finger.width() << std::endl;
				
      // Get finger bones
      for (int b = 0; b < 4; ++b) {
        Bone::Type boneType = static_cast<Bone::Type>(b);
        Bone bone = finger.bone(boneType);
        std::cout << std::string(6, ' ') <<  boneNames[boneType]
                  << " bone, start: " << bone.prevJoint()
                  << ", end: " << bone.nextJoint()
                  << ", direction: " << bone.direction() << std::endl;
      }
    }


	/******************************************************************************\
	*                                 ValdeWare                                    *
	\******************************************************************************/
	//Creating Finger objects
	Leap::Finger thumb = hand.fingers()[0];
	Leap::Finger index = hand.fingers()[1];
	Leap::Finger heart = hand.fingers()[2];
	Leap::Finger ring = hand.fingers()[3];
	Leap::Finger pinky = hand.fingers()[4]; 
	controller.enableGesture(Leap::Gesture::TYPE_SWIPE);

	//Gesture declaration functions
	const GestureList gestures = frame.gestures();
	for (int g = 0; g < gestures.count(); ++g) {
		Gesture gesture = gestures[g];
			if(gesture.type() == Gesture::TYPE_SWIPE){
					SwipeGesture swipe = gesture;
					//SMASH ATTACKS
						//Smash attack up (W+K)
						if(hand.isRight() && !thumb.isExtended() && index.isExtended() && !heart.isExtended() && !ring.isExtended() && !pinky.isExtended()  && swipe.direction().y > 0 && swipe.direction().x > -0.3 && swipe.direction().x < 0.3) {
							DoubleKey(87,75);
						}
						//Smash attack left (A+K)
						if(hand.isRight() && !thumb.isExtended() && index.isExtended() && !heart.isExtended() && !ring.isExtended() && !pinky.isExtended()  && swipe.direction().x < 0 && swipe.direction().y > -0.3 && swipe.direction().y < 0.3) {
							DoubleKey(65,75);
						}
						//Smash attack right (D+K)
						if(hand.isRight() && !thumb.isExtended() && index.isExtended() && !heart.isExtended() && !ring.isExtended() && !pinky.isExtended()  && swipe.direction().x > 0 && swipe.direction().y > -0.3 && swipe.direction().y < 0.3) {
							DoubleKey(68,75);
						}
						//Smash attack down (S+K)
						if(hand.isRight() && !thumb.isExtended() && index.isExtended() && heart.isExtended() && !ring.isExtended() && !pinky.isExtended()  && swipe.direction().y < 0 && swipe.direction().x > -0.5 && swipe.direction().x < 0.5) {
							DoubleKey(83,75);
						}
					//SPECIAL ATTACKS
						//Special attack up (W+J)
						if(hand.isRight() && !thumb.isExtended() && index.isExtended() && heart.isExtended() && !ring.isExtended() && !pinky.isExtended()  && swipe.direction().y > 0 && swipe.direction().x > -0.3 && swipe.direction().x < 0.3) {
							DoubleKey(87,74);
						}
						//Special attack left (A+J)
						if(hand.isRight() && !thumb.isExtended() && index.isExtended() && heart.isExtended() && !ring.isExtended() && !pinky.isExtended()  && swipe.direction().x < 0 && swipe.direction().y > -0.3 && swipe.direction().y < 0.3) {
							DoubleKey(65,74);
						}
						//Special attack right (D+J)
						if(hand.isRight() && !thumb.isExtended() && index.isExtended() && heart.isExtended() && !ring.isExtended() && !pinky.isExtended()  && swipe.direction().x > 0 && swipe.direction().y > -0.3 && swipe.direction().y < 0.3) {
							DoubleKey(68,74);
						}
						//Special attack down (S+J)
						if(hand.isRight() && !thumb.isExtended() && index.isExtended() && heart.isExtended() && !ring.isExtended() && !pinky.isExtended()  && swipe.direction().y < 0 && swipe.direction().x > -0.5 && swipe.direction().x < 0.5) {
							DoubleKey(83,74);
						}
					//Normal attacks while moving
						//Attack up (W+J)
						if(hand.isRight() && thumb.isExtended() && index.isExtended() && heart.isExtended() && !ring.isExtended() && !pinky.isExtended()  && swipe.direction().y > 0 && swipe.direction().x > -0.3 && swipe.direction().x < 0.3) {
							DoubleKeyDel(87,75);
						}
						//Attack left (A+J)
						if(hand.isRight() && thumb.isExtended() && index.isExtended() && heart.isExtended() && !ring.isExtended() && !pinky.isExtended()  && swipe.direction().x < 0 && swipe.direction().y > -0.3 && swipe.direction().y < 0.3) {
							DoubleKeyDel(65,75);
						}
						//Attack right (D+J)
						if(hand.isRight() && thumb.isExtended() && index.isExtended() && heart.isExtended() && !ring.isExtended() && !pinky.isExtended()  && swipe.direction().x > 0 && swipe.direction().y > -0.3 && swipe.direction().y < 0.3) {
							DoubleKeyDel(68,75);
						}
						//Attack down (S+J)
						if(hand.isRight() && thumb.isExtended() && index.isExtended() && heart.isExtended() && !ring.isExtended() && !pinky.isExtended()  && swipe.direction().y < 0 && swipe.direction().x > -0.5 && swipe.direction().x < 0.5) {
							DoubleKeyDel(83,75);
						}
				}
			
	}
		//Movement Right
		if(hand.isLeft() && thumb.isExtended() && !index.isExtended() && !heart.isExtended() && !ring.isExtended() && !pinky.isExtended() && thumb.direction().x > 0 && thumb.direction().y > 0  && thumb.direction().y < 0.4) {
			Key(68);
		}

		//Movement Left
		if(hand.isLeft() && thumb.isExtended() && !index.isExtended() && !heart.isExtended() && !ring.isExtended() && !pinky.isExtended() && thumb.direction().x < 0 && thumb.direction().y > 0  && thumb.direction().y < 0.4) {
			Key(65);
		} 

		//Grab
		if(hand.isRight() && thumb.isExtended() && index.isExtended() && !heart.isExtended() && !ring.isExtended() && pinky.isExtended()) {
			KeyH(72);
		}
		
	
  }


  // Get tools
  const ToolList tools = frame.tools();
  for (ToolList::const_iterator tl = tools.begin(); tl != tools.end(); ++tl) {
    const Tool tool = *tl;
    std::cout << std::string(2, ' ') <<  "Tool, id: " << tool.id()
              << ", position: " << tool.tipPosition()
              << ", direction: " << tool.direction() << std::endl;
  }

  // Get gestures
  const GestureList gestures = frame.gestures();
  for (int g = 0; g < gestures.count(); ++g) {
    Gesture gesture = gestures[g];

    switch (gesture.type()) {
      case Gesture::TYPE_CIRCLE:
      {
        CircleGesture circle = gesture;
        std::string clockwiseness;

        if (circle.pointable().direction().angleTo(circle.normal()) <= PI/2) {
          clockwiseness = "clockwise";
		  Key(70);
        } else {
          clockwiseness = "counterclockwise";
		  Key(70);
        }

        // Calculate angle swept since last frame
        float sweptAngle = 0;
        if (circle.state() != Gesture::STATE_START) {
          CircleGesture previousUpdate = CircleGesture(controller.frame(1).gesture(circle.id()));
          sweptAngle = (circle.progress() - previousUpdate.progress()) * 2 * PI;
        }
        std::cout << std::string(2, ' ')
                  << "Circle id: " << gesture.id()
                  << ", state: " << stateNames[gesture.state()]
                  << ", progress: " << circle.progress()
                  << ", radius: " << circle.radius()
                  << ", angle " << sweptAngle * RAD_TO_DEG
                  <<  ", " << clockwiseness << std::endl;
        break;
      }
      case Gesture::TYPE_SWIPE:
      {
        SwipeGesture swipe = gesture;
        std::cout << std::string(2, ' ')
          << "Swipe id: " << gesture.id()
          << ", state: " << stateNames[gesture.state()]
          << ", direction: " << swipe.direction()
          << ", speed: " << swipe.speed() << std::endl;
        break;
      }
      case Gesture::TYPE_KEY_TAP:
      {
        KeyTapGesture tap = gesture;
        std::cout << std::string(2, ' ')
          << "Key Tap id: " << gesture.id()
          << ", state: " << stateNames[gesture.state()]
          << ", position: " << tap.position()
          << ", direction: " << tap.direction()<< std::endl;
		  Key(67);
        break;
      }
      case Gesture::TYPE_SCREEN_TAP:
      {
        ScreenTapGesture screentap = gesture;
        std::cout << std::string(2, ' ')
          << "Screen Tap id: " << gesture.id()
          << ", state: " << stateNames[gesture.state()]
          << ", position: " << screentap.position()
          << ", direction: " << screentap.direction()<< std::endl;
        break;
      }
      default:
        std::cout << std::string(2, ' ')  << "Unknown gesture type." << std::endl;
        break;
    }
  }
  

  if (!frame.hands().isEmpty() || !gestures.isEmpty()) {
    std::cout << std::endl;
  }
}

void SampleListener::onFocusGained(const Controller& controller) {
  std::cout << "Focus Gained" << std::endl;
}

void SampleListener::onFocusLost(const Controller& controller) {
  std::cout << "Focus Lost" << std::endl;
}

void SampleListener::onDeviceChange(const Controller& controller) {
  std::cout << "Device Changed" << std::endl;
  const DeviceList devices = controller.devices();

  for (int i = 0; i < devices.count(); ++i) {
    std::cout << "id: " << devices[i].toString() << std::endl;
    std::cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
  }
}

void SampleListener::onServiceConnect(const Controller& controller) {
  std::cout << "Service Connected" << std::endl;
}

void SampleListener::onServiceDisconnect(const Controller& controller) {
  std::cout << "Service Disconnected" << std::endl;
}



int main(int argc, char** argv) {
  // Create a sample listener and controller
  SampleListener listener;
  Controller controller;

  controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);
  HWND window;
  AllocConsole();
  window = FindWindowA("ConsoleWindowClass", NULL);
  ShowWindow(window , 0);
  
  // Have the sample listener receive events from the controller
  controller.addListener(listener);

   //if (argc > 1 && strcmp(argv[1], "--bg") == 0)
   // controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);
  while(1);
  // Keep this process running until Enter is pressed
  std::cout << "Press Enter to quit..." << std::endl;
  std::cin.get();

  // Remove the sample listener when done
  controller.removeListener(listener);

  return 0;
}
