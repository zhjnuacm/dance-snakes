LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := hellocpp/main.cpp \
../../Classes/snakes/Food.cpp \
../../Classes/snakes/FoodFactory.cpp \
../../Classes/snakes/Map.cpp \
../../Classes/snakes/SnakeNode.cpp \
../../Classes/snakes/SnakeBase.cpp \
../../Classes/snakes/Snake.cpp \
../../Classes/snakes/MarsSnake.cpp \
../../Classes/snakes/Point.cpp \
../../Classes/snakes/ScoreAndTimePanel.cpp \
                   ../../Classes/AllPassScene.cpp \
                   ../../Classes/AppDelegate.cpp \
../../Classes/ControlButton.cpp \
../../Classes/Mediator.cpp \
../../Classes/PlayScene.cpp \
../../Classes/Tools.cpp \
../../Classes/StartMenu.cpp 

                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes                   

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)
