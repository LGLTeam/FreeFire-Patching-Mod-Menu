/*
 * Credit:
 *
 * Octowolve - Mod menu: https://github.com/z3r0Sec/Substrate-Template-With-Mod-Menu
 * And hooking: https://github.com/z3r0Sec/Substrate-Hooking-Example
 * VanHoevenTR A.K.A Nixi: https://github.com/LGLTeam/VanHoevenTR_Android_Mod_Menu
 * MrIkso - Mod menu: https://github.com/MrIkso/FloatingModMenu
 * AndnixSH - GTA V Sound effects: https://github.com/AndnixSH/Substrate-Template-With-Mod-Menu
 * MJx0 A.K.A Ruit - KittyMemory: https://github.com/MJx0/KittyMemory
 * */

#include <pthread.h>
#include <jni.h>
#include <src/Includes/Utils.h>
#include <src/Substrate/SubstrateHook.h>
#include "KittyMemory/MemoryPatch.h"
#include "Includes/Logger.h"

#include <android/log.h>
#include "Substrate/CydiaSubstrate.h"
#include <dlfcn.h>
#include "Unity/Quaternion.hpp" // C++ equivalent of Unity C# Quaternion. <- Credits unknown
#include "Unity/Vector3.hpp" // C++ equivalent of Unity C# Vector3. <- Credits unknown
#include "Unity/Vector2.hpp" // C++ equivalent of Unity C# Vector2. <- Credits unknown
#include "Unity/Unity.h" // C++ equivalent of Unity List/Dictionary/Array <- Credits to Shmoo for this (Small version of https://github.com/shmoo419/UnityStuff/blob/master/Unity.h)

#include <memory.h>
#include <cstdio>
#include <cstdlib>
#import "Includes/Utils.h"



// fancy struct for patches
struct My_Patches {
    // let's assume we have patches for these functions for whatever game
    // like show in miniMap boolean function
    MemoryPatch bypas;
    MemoryPatch ghost;
    MemoryPatch wallkarakter;
    MemoryPatch wallstone1;
    MemoryPatch wallstone2;
    MemoryPatch white1;
    MemoryPatch white2;
    MemoryPatch antena;
    MemoryPatch aimlock1;
    MemoryPatch aimlock2;
    MemoryPatch aimlock3;
    MemoryPatch aimlock4;
    MemoryPatch norecoil;
    MemoryPatch night;
    MemoryPatch rainbullets;
    MemoryPatch medkit1;
    MemoryPatch medkit2;
    MemoryPatch nofog1;
    MemoryPatch nofog2;
    MemoryPatch cameraview0;
    MemoryPatch cameraview1;
    MemoryPatch cameraview2;
    MemoryPatch cameraview3;
    MemoryPatch cameraview4;
    MemoryPatch cameraview5;
    MemoryPatch cameraview6;
    MemoryPatch cameraview7;
    MemoryPatch cameraview8;
    MemoryPatch cameraview9;
    MemoryPatch cameraview10;
    MemoryPatch speedrun1;
    MemoryPatch speedrun2;
    MemoryPatch speedrun3;
    MemoryPatch speedrun4;
    MemoryPatch speedrun5;
    MemoryPatch noparasut;
    MemoryPatch speedcar1;
    MemoryPatch speedcar2;
    MemoryPatch speedcar3;
    MemoryPatch speedcar4;
    MemoryPatch speedcar5;
    MemoryPatch giant1;
    MemoryPatch giant2;
    MemoryPatch giant3;
    MemoryPatch giant4;
    MemoryPatch giant5;
}

my_cool_Patches;

bool bypass;
bool wallkarakterr;
bool ghostt;
bool whitee;
bool wallstonee;
bool rainbulletss;
bool antenaa;
bool credittt;
bool aimlockk;
bool norecoill;
bool nightt;
bool medkitt;
bool nofogg;
bool noparasutt;





extern "C" {
JNIEXPORT jstring JNICALL
Java_mpg_team_ff_FloatingModMenuService_Title(
        JNIEnv *env,
        jobject activityObject) {
    jstring str = env->NewStringUTF("*  MASTERPIECE GAMING  *");
    return str;
}

JNIEXPORT jstring JNICALL
Java_mpg_team_ff_FloatingModMenuService_Heading(
        JNIEnv *env,
        jobject activityObject) {
    std::string toast_text = "Free Fire 1.47.5 -    by : Masterpiece GaminG - v3";
    return env->NewStringUTF(toast_text.c_str());
}

JNIEXPORT jstring JNICALL
Java_mpg_team_ff_FloatingModMenuService_Icon(
        JNIEnv *env,
        jobject activityObject) {

    //Use https://www.base64encode.org/ to encode your image to base64

    std::string str = "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";
    return env->NewStringUTF(str.c_str());
}
JNIEXPORT jint JNICALL
Java_mpg_team_ff_FloatingModMenuService_IconSize(
        JNIEnv *env,
        jobject activityObject) {
    return 40;
}


JNIEXPORT jobjectArray  JNICALL
Java_mpg_team_ff_FloatingModMenuService_getFeatureList(
        JNIEnv *env,
        jobject activityObject) {
    jobjectArray ret;
    const char *features[] = {
            "Category_YouTube Masterterpiece GaminG",//0

            "Toggle_ Bypass Anti Eliminasi (Loby)",//1

            "Category_YouTube Masterterpiece GaminG",//2

            "Button_Ghost Mode ",//3
            "Button_Wall Hack Karakter ",//4
            "Button_Wall Hack Stone ",//5
            "Button_Aim Lock ",//6
            "Button_No Recoil ",//7
            "Button_Rain Of Bullets ",//8
            "Button_Medkit Run ",//9
            "Button_Night Mode ",//10
            "Button_No Fog ",//11
            "Button_White Body ",//12
            "Button_Antena Burik ",//13
            "Button_No Parasut ",//14

            "Category_YouTube Masterterpiece GaminG",//15

            "SeekBar_ Camera View _0_10",//16
            "SeekBar_ Speed Run _0_5",//17
            "SeekBar_ Speed Car _0_5",//18
            "SeekBar_ Giant Body _0_5",//19

            "Category_Aimbot",//20
            "Toggle_Aimbot",//21
            "Toggle_Fire Aimbot",//22
            "Toggle_Scope Aimbot",//23
            "Toggle_Fov Aim",//24
            "Toggle_Headshot Aimbot",//25
            "Toggle_Espshit",//26




            "Category_@Copyright 2020 | All Rights Reserved",

            "Spinner_ _ Credit  _Creator : Masterpiece GaminG_Team : MPG TEAM_Base : LGL TEAM_Build : Android studio_Code : gameguardian.net",

    };
    int Total_Feature = (sizeof features /sizeof features[0]);
    ret = (jobjectArray) env->NewObjectArray(Total_Feature, env->FindClass("java/lang/String"),env->NewStringUTF(""));
    int i;
    for (i = 0; i < Total_Feature; i++)env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));
    return (ret);
}


bool aimbot = false, fireaimbot = false, scopeaimbot = false, fovaim = false, headshoot = false, espshit = false;

JNIEXPORT void JNICALL
Java_mpg_team_ff_FloatingModMenuService_changeToggle(
        JNIEnv *env,
        jobject activityObject,
        jint feature) {

    switch (feature) {
        case 1:
            bypass = !bypass;
            if (bypass) {
                my_cool_Patches.bypas.Modify();
            } else {
                my_cool_Patches.bypas.Restore();
            }
            break;
        case 21:
            aimbot = !aimbot;
            break;
       case 22:
           fireaimbot = !fireaimbot;
            break;
       case 23:
           scopeaimbot = !scopeaimbot;
            break;
       case 24:
           fovaim = !fovaim;
            break;
        case 25:
            headshoot = !headshoot;
            break;
        case 26:
            espshit = !espshit;
            break;
    }
}



JNIEXPORT void JNICALL
Java_mpg_team_ff_FloatingModMenuService_changeButton(
        JNIEnv *env,
        jobject activityObject,
        jint feature) {
    __android_log_print(ANDROID_LOG_VERBOSE, "Mod Menu", "Button = %d", feature);
    switch (feature) {
        case 3:
            ghostt = !ghostt;
            if (ghostt){
                my_cool_Patches.ghost.Modify();
            }else{
                my_cool_Patches.ghost.Restore();
            }
            break;

        case 4:
            wallkarakterr = !wallkarakterr;
            if (wallkarakterr) {
                my_cool_Patches.wallkarakter.Modify();
            } else {
                my_cool_Patches.wallkarakter.Restore();
            }
            break;

        case 5:
            wallstonee = !wallstonee;
            if (wallstonee) {
                my_cool_Patches.wallstone1.Modify();
                my_cool_Patches.wallstone2.Modify();
            } else {
                my_cool_Patches.wallstone1.Restore();
                my_cool_Patches.wallstone2.Restore();
            }
            break;

        case 6:
            aimlockk = !aimlockk;
            if (aimlockk) {
                my_cool_Patches.aimlock1.Modify();
                my_cool_Patches.aimlock2.Modify();
                my_cool_Patches.aimlock3.Modify();
                my_cool_Patches.aimlock4.Modify();
            } else {
                my_cool_Patches.aimlock1.Restore();
                my_cool_Patches.aimlock2.Restore();
                my_cool_Patches.aimlock3.Restore();
                my_cool_Patches.aimlock4.Restore();
            }
            break;

        case 7:
            norecoill = !norecoill;
            if (norecoill) {
                my_cool_Patches.norecoil.Modify();
            } else {
                my_cool_Patches.norecoil.Restore();
            }
            break;

        case 8:
            rainbulletss = !rainbulletss;
            if (rainbulletss) {
                my_cool_Patches.rainbullets.Modify();
            } else {
                my_cool_Patches.rainbullets.Restore();
            }
            break;

        case 9:
            medkitt = !medkitt;
            if (medkitt) {
                my_cool_Patches.medkit1.Modify();
                my_cool_Patches.medkit2.Modify();
            } else {
                my_cool_Patches.medkit1.Restore();
                my_cool_Patches.medkit2.Restore();
            }
            break;

        case 10:
            nightt = !nightt;
            if (nightt) {
                my_cool_Patches.night.Modify();
            } else {
                my_cool_Patches.night.Restore();
            }
            break;

        case 11:
            nofogg = !nofogg;
            if (nofogg) {
                my_cool_Patches.nofog1.Modify();
            } else {
                my_cool_Patches.nofog2.Modify();
            }
            break;

        case 12:
            whitee = !whitee;
            if (whitee) {
                my_cool_Patches.white1.Modify();
                my_cool_Patches.white2.Modify();
            } else {
                my_cool_Patches.white1.Restore();
                my_cool_Patches.white2.Restore();
            }
            break;

        case 13:
            antenaa = !antenaa;
            if (antenaa) {
                my_cool_Patches.antena.Modify();
            } else {
                my_cool_Patches.antena.Restore();
            }
            break;

        case 14:
            noparasutt = !noparasutt;
            if (noparasutt) {
                my_cool_Patches.noparasut.Modify();
            } else {
                my_cool_Patches.noparasut.Restore();
            }
            break;
        case 20:
            aimbot = !aimbot;
            break;
    }
}



JNIEXPORT void JNICALL
Java_mpg_team_ff_FloatingModMenuService_changeSeekBar(
        JNIEnv *env,
        jobject activityObject,
        jint feature, jint sliderValue) {
    __android_log_print(ANDROID_LOG_VERBOSE, "Mod Menu", "Feature = %d", feature);
    __android_log_print(ANDROID_LOG_VERBOSE, "Mod Menu", "sliderValue = %d", sliderValue);

    switch (feature) {


        case 16:
            if (sliderValue == 0){my_cool_Patches.cameraview0.Modify();}
            else if (sliderValue == 1){my_cool_Patches.cameraview1.Modify();}
            else if (sliderValue == 2){my_cool_Patches.cameraview2.Modify();}
            else if (sliderValue == 3){my_cool_Patches.cameraview3.Modify();}
            else if (sliderValue == 4){my_cool_Patches.cameraview4.Modify();}
            else if (sliderValue == 5){my_cool_Patches.cameraview5.Modify();}
            else if (sliderValue == 6){my_cool_Patches.cameraview6.Modify();}
            else if (sliderValue == 7){my_cool_Patches.cameraview7.Modify();}
            else if (sliderValue == 8){my_cool_Patches.cameraview8.Modify();}
            else if (sliderValue == 9){my_cool_Patches.cameraview9.Modify();}
            else if (sliderValue == 10){my_cool_Patches.cameraview10.Modify();}
            break;

        case 17:
            if (sliderValue == 0){
                my_cool_Patches.speedrun1.Restore();
                my_cool_Patches.speedrun2.Restore();
                my_cool_Patches.speedrun3.Restore();
                my_cool_Patches.speedrun4.Restore();
                my_cool_Patches.speedrun5.Restore();}
            else if (sliderValue == 1){my_cool_Patches.speedrun1.Modify();}
            else if (sliderValue == 2){my_cool_Patches.speedrun2.Modify();}
            else if (sliderValue == 3){my_cool_Patches.speedrun3.Modify();}
            else if (sliderValue == 4){my_cool_Patches.speedrun4.Modify();}
            else if (sliderValue == 5){my_cool_Patches.speedrun5.Modify();}
            break;

        case 18:
            if (sliderValue == 0){
                my_cool_Patches.speedcar1.Restore();
                my_cool_Patches.speedcar2.Restore();
                my_cool_Patches.speedcar3.Restore();
                my_cool_Patches.speedcar4.Restore();
                my_cool_Patches.speedcar5.Restore();}
            else if (sliderValue == 1){my_cool_Patches.speedcar1.Modify();}
            else if (sliderValue == 2){my_cool_Patches.speedcar2.Modify();}
            else if (sliderValue == 3){my_cool_Patches.speedcar3.Modify();}
            else if (sliderValue == 4){my_cool_Patches.speedcar4.Modify();}
            else if (sliderValue == 5){my_cool_Patches.speedcar5.Modify();}
            break;

        case 19:
            if (sliderValue == 0) {
                my_cool_Patches.giant1.Restore();
                my_cool_Patches.giant2.Restore();
                my_cool_Patches.giant3.Restore();
                my_cool_Patches.giant4.Restore();
                my_cool_Patches.giant5.Restore();}
            else if (sliderValue == 1){my_cool_Patches.giant1.Modify();}
            else if (sliderValue == 2){my_cool_Patches.giant2.Modify();}
            else if (sliderValue == 3){my_cool_Patches.giant3.Modify();}
            else if (sliderValue == 4){my_cool_Patches.giant4.Modify();}
            else if (sliderValue == 5){my_cool_Patches.giant5.Modify();}
            break;
    }
}

JNIEXPORT void JNICALL
Java_mpg_team_ff_FloatingModMenuService_changeSpinner(
        JNIEnv *env,
        jobject activityObject,
        jint feature,jint sliderValue) {
    __android_log_print(ANDROID_LOG_VERBOSE, "Mod Menu", "Feature = %d", feature);
    switch (feature) {
        case 1:
            credittt = !credittt;
    }
}


}

const char* il2cppName = "libil2cpp.so";
const char* unityName = "libunity.so";


/**********************************

HOOK IL2CPP

***********************************/

void* (*GetHeadTF)(void* player) = (void*(*)(void*))getAbsoluteAddress(il2cppName,0xAE5868);

void* (*GetHipTF)(void* player) = (void*(*)(void*))getAbsoluteAddress(il2cppName,0xAE5994);

void* (*CurrentMatch)() = (void*(*)())getAbsoluteAddress(il2cppName,0x25C277C); //static QG CurrentMatch()

void* (*GetLocalPlayer)(void* match) = (void*(*)(void *))getAbsoluteAddress(il2cppName,0x12B1178); //public Player ^djkVy()

void* (*getPlayerByIndex)(void* match, uint8_t index) = (void*(*)(void *, uint8_t))getAbsoluteAddress(il2cppName,0x12B1600); //public Player |`pUJY(byte cA^OZCl)

int (*get_CurHP)(void* player) = (int(*)(void *))getAbsoluteAddress(il2cppName,0xAA1A74);

void* (*get_PlayerID)(void* player) = (void*(*)(void *))getAbsoluteAddress(il2cppName,0xAAC610);

void* (*get_NickName)(void* player) = (void*(*)(void *))getAbsoluteAddress(il2cppName,0xAAC720);

bool (*IsVisible)(void* player) = (bool(*)(void *))getAbsoluteAddress(il2cppName,0xAAEB6C);

bool (*IsFiring)(void* player) = (bool(*)(void *))getAbsoluteAddress(il2cppName,0xAC77A8);

bool (*get_IsSighting)(void* player) = (bool(*)(void *))getAbsoluteAddress(il2cppName,0xAF8410);

bool (*IsLocalPlayer)(void* player) = (bool(*)(void *))getAbsoluteAddress(il2cppName,0xAAF4E8);

bool (*IsLocalTeammate)(void* player) = (bool(*)(void *))getAbsoluteAddress(il2cppName,0xAB4ABC);

bool (*get_IsDieing)(void* player) = (bool(*)(void *))getAbsoluteAddress(il2cppName,0xAACEC8);

bool (*IsCrouching)(void* player) = (bool(*)(void *))getAbsoluteAddress(il2cppName,0xAB60C4);

bool (*get_IsSkyDiving)(void* player) = (bool(*)(void *))getAbsoluteAddress(il2cppName,0xAAE66C);

bool (*get_IsSkyDashing)(void* player) = (bool(*)(void *))getAbsoluteAddress(il2cppName,0xAAEA48);

bool (*get_IsParachuting)(void* player) = (bool(*)(void *))getAbsoluteAddress(il2cppName,0xAAE264);

bool (*IsSameTeam)(void* p1, void* p2) = (bool(*)(void*, void*))getAbsoluteAddress(il2cppName,0x25C39F8);

void (*SetAimRotation)(void* player, Quaternion rotation) = (void(*)(void *, Quaternion))getAbsoluteAddress(il2cppName,0xAAD320);

void* (*Component_get_transform)(void* comp) = (void*(*)(void *))getAbsoluteAddress(il2cppName,0x233546C);

Vector3 (*Transform_get_position)(void* trans) = (Vector3(*)(void *))getAbsoluteAddress(il2cppName,0x2908DF8);

Vector3 (*Transform_get_forward)(void* trans) = (Vector3(*)(void *))getAbsoluteAddress(il2cppName,0x2909524);

void* (*get_main)() = (void*(*)())getAbsoluteAddress(il2cppName,0x2330740); // UnityEngine.Camera

void (*ShowPopupMessage)(void* gamescene, void* message, float duration) = (void(*)(void *, void*, float))getAbsoluteAddress(il2cppName,0x1090B8C);

void* UIInGameScene = NULL;

void* (*il2cpp_string_new)(const char* string) = (void*(*)(const char*))getAbsoluteAddress(il2cppName,0x296B4A4);

void* (*String_Concat)(void* string1, void* string2, void* string3) = (void*(*)(void*,void*, void*))getAbsoluteAddress(il2cppName,0x1DE15F4);

int (*Screen_get_width)() = (int(*)())getAbsoluteAddress(il2cppName,0x2696BB0);

int (*Screen_get_height)() = (int(*)())getAbsoluteAddress(il2cppName,0x2696C40);

Vector3 (*WorldToScreenPoint)(void* camera, Vector3 position) = (Vector3 (*)(void*, Vector3)) getAbsoluteAddress(il2cppName,0x2330150);

class Rect {
public:
    float x;
    float y;
    float width;
    float height;

    Rect(float x, float y, float width, float height){
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }
};

class Color {
public:
    float r;
    float g;
    float b;
    float a;

    Color(float r, float g, float b, float a){
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
};

Vector3 GetHeadPosition(void* player){
    return Transform_get_position(*(void**) ((uint64_t) player + 0x18C));
}

Vector3 GetHipPosition(void* player){
    return Transform_get_position(*(void**) ((uint64_t) player + 0x190));
}


void* GetClosestEnemy(void* match, bool byFOV) {
    if(!match) {
        return NULL;
    }

    float shortestDistance = 99999;
    float maxAngle = 30.0;
    void* closestEnemy = NULL;
    void* LocalPlayer = GetLocalPlayer(match);

    if(LocalPlayer && !get_IsSkyDashing(LocalPlayer) && !get_IsParachuting(LocalPlayer) && !get_IsSkyDiving(LocalPlayer) && !get_IsDieing(LocalPlayer)) {
        for(int u = 0; u <= 50; u++) {
            void* Player = getPlayerByIndex(match, (uint8_t)u);
            if(Player && !IsLocalPlayer(Player) && !IsLocalTeammate(Player) && !get_IsDieing(Player) && !get_IsSkyDashing(Player) && !get_IsParachuting(Player) &&
               !get_IsSkyDiving(Player) && IsVisible(Player) && get_CurHP(Player) > 0)
            {
                Vector3 PlayerPos = GetHipPosition(Player);
                Vector3 LocalPlayerPos = GetHipPosition(LocalPlayer);//Transform_get_position(Component_get_transform(get_main()));
                float distanceToMe = Vector3::Distance(LocalPlayerPos, PlayerPos);

                if(byFOV) {
                    Vector3 targetDir = PlayerPos - LocalPlayerPos;
                    float angle = Vector3::Angle(targetDir, Transform_get_forward(Component_get_transform(get_main()))) * 100.0;
                    if(angle <= maxAngle) {
                        if(distanceToMe < shortestDistance) {
                            shortestDistance = distanceToMe;
                            closestEnemy = Player;
                        }
                    }
                } else {
                    if(distanceToMe < shortestDistance) {
                        shortestDistance = distanceToMe;
                        closestEnemy = Player;
                    }
                }
            }
        }
    }
    return closestEnemy;
}


void (*Update)(void* gamestartup); //GameStartup
void _Update(void* gamestartup) {
    Update(gamestartup);
    if(gamestartup) {
        void* Match = CurrentMatch();
        if((aimbot || fireaimbot || scopeaimbot || espshit) && Match) {
            void* LocalPlayer = GetLocalPlayer(Match);

            if(LocalPlayer){
                //ESP
                /*if(espshit && UIInGameScene){
                    for(int u = 0; u < 100; u++) {
                        void* Player = getPlayerByIndex(Match, (uint8_t)u);
                        if(Player && !IsLocalPlayer(Player) && !get_IsDieing(Player) && IsVisible(Player) && get_CurHP(Player) > 0) {
                            Vector3 PlayerPos = GetHipPosition(Player);
                            Vector3 LocalPos = Transform_get_position(Component_get_transform(get_main()));

                            char dist[10];
                            float n = Vector3::Distance(LocalPos, PlayerPos);
                            sprintf(dist, " %dM", (int)n);
                            ShowPopupMessage(UIInGameScene, String_Concat(*(void**) ((uint64_t) Player + 0xA8), il2cpp_string_new_0(dist)), 2.0);

                            int i = 0;
                            void* headtf = *(void**) ((uint64_t) Player + 0x154);
                            if(headtf){
                                Vector3 headpos = WorldToScreenPoint(get_main(), Transform_get_position(headtf));

                                int screenWidth = Screen_get_width();
                                int screenHeight = Screen_get_height();

                                Vector2 from = Vector2((screenWidth / 2), screenHeight);
                                Vector2 to = Vector2(headpos.X, screenHeight - headpos.Y);


                            }
                        }
                    }
                }*/

                //Aimbot
                void* closestEnemy = GetClosestEnemy(Match, fovaim);
                if(closestEnemy) {
                    Vector3 PlayerPos = GetHipPosition(closestEnemy);
                    Vector3 LocalPos = Transform_get_position(Component_get_transform(get_main()));
                    Vector3 up = Vector3::Up();
                    Vector3 b = Vector3::Zero();

                    if(IsCrouching(closestEnemy)) {
                        b = Vector3::Down() * 0.4;
                    }

                    Vector3 Forward = PlayerPos - LocalPos + (up * 0.3) + b;
                    if(headshoot) {
                        Forward = GetHeadPosition(closestEnemy) - LocalPos + b;
                    }

                    if(espshit && UIInGameScene) {
                        char dist[10];
                        float n = Vector3::Distance(GetHipPosition(LocalPlayer), PlayerPos);
                        sprintf(dist, " %dM", (int)n);
                        ShowPopupMessage(UIInGameScene, String_Concat(NULL, get_NickName(closestEnemy), il2cpp_string_new(dist)), 2.0);
                    }

                    Quaternion lookRotation = Quaternion::LookRotation(Forward, up);
                    if((scopeaimbot && get_IsSighting(LocalPlayer))) {
                        SetAimRotation(LocalPlayer, lookRotation);
                    } else if(fireaimbot && IsFiring(LocalPlayer)) {
                        SetAimRotation(LocalPlayer, lookRotation);
                    } else if(aimbot) {
                        SetAimRotation(LocalPlayer, lookRotation);
                    }
                }
            }
        }
    }
}

void (*OnInit)(void* gamescene); // COW.UIInGameScene
void _OnInit(void* gamescene) {
    OnInit(gamescene);
    if(gamescene) {
        UIInGameScene = gamescene;
    }
}

void *hack_thread(void *) {
    ProcMap il2cppMap;
    do {il2cppMap = KittyMemory::getLibraryMap(il2cppName);
        sleep(1);
    } while (!il2cppMap.isValid());

    my_cool_Patches.bypas = MemoryPatch(il2cppName, 0x1710bcc,"\x00\x00\xa0\xE3\x1E\xFF\x2F\xE1", 8);
    my_cool_Patches.ghost = MemoryPatch(il2cppName, 0x17097f4,"\x00\x00\xa0\xE3\x1E\xFF\x2F\xE1", 8);
    my_cool_Patches.wallkarakter = MemoryPatch(unityName, 0xee679c,"\xbd\x37\x86\xb5\x00\x00\xa0\xE3", 8);

    my_cool_Patches.wallstone1 = MemoryPatch(unityName, 0xef2890,"\xbd\x37\x86\xb5\xbd\x37\x86\xb5", 8);
    my_cool_Patches.wallstone2 = MemoryPatch(unityName, 0xef2898,"\xbd\x37\x86\xb5\xbd\x37\x86\xb5", 8);

    my_cool_Patches.white1 = MemoryPatch(il2cppName, 0xab5908,"\x01\x00\xa0\xE3\x1E\xFF\x2F\xE1", 8);
    my_cool_Patches.white2 = MemoryPatch(il2cppName, 0x1783a38,"\x00\x00\xa0\xE3\x1E\xFF\x2F\xE1", 8);

    my_cool_Patches.aimlock1 = MemoryPatch(il2cppName, 0xad5228,"\x00\x00\xa0\xE3\x1E\xFF\x2F\xE1", 8);
    my_cool_Patches.aimlock2 = MemoryPatch(il2cppName, 0x1350298,"\x01\x00\xa0\xE3\x1E\xFF\x2F\xE1", 8);
    my_cool_Patches.aimlock3 = MemoryPatch(il2cppName, 0x13505c4,"\xf0\x00\xa0\xE3\x1E\xFF\x2F\xE1", 8);
    my_cool_Patches.aimlock4 = MemoryPatch(il2cppName, 0x1341ad4,"\x79\x04\x44\xe3\x1e\xFf\x2F\xE1", 8);

    my_cool_Patches.norecoil = MemoryPatch(il2cppName, 0xb1f8d4,"\x03\x00\xa0\xE3\x1E\xFF\x2F\xE1", 8);

    my_cool_Patches.medkit1 = MemoryPatch(il2cppName, 0xad1b78,"\x00\x00\xa0\xE3\x1E\xFF\x2F\xE1", 8);
    my_cool_Patches.medkit2 = MemoryPatch(il2cppName, 0x21445a4,"\x00\x00\xa0\xE3\x1E\xFF\x2F\xE1", 8);

    my_cool_Patches.night = MemoryPatch(unityName, 0x1a2280,"\x00\x00\x80\xbf", 4);

    my_cool_Patches.nofog1 = MemoryPatch(il2cppName, 0x26925bc,"\x00\x00\xa0\xE3\x1E\xFF\x2F\xE1", 8);
    my_cool_Patches.nofog2 = MemoryPatch(il2cppName, 0x26925bc,"\x01\x00\xa0\xE3\x1E\xFF\x2F\xE1", 8);

    my_cool_Patches.rainbullets = MemoryPatch(il2cppName, 0x134210c,"\x06\x00\xa0\xE3\x1E\xFF\x2F\xE1", 8);
    my_cool_Patches.antena = MemoryPatch(unityName, 0x2a3454, "\x10\x40\x1c\x46", 4);

    my_cool_Patches.noparasut = MemoryPatch(il2cppName, 0x28223a8,"\x00\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);

    my_cool_Patches.cameraview0 = MemoryPatch(il2cppName, 0x133ca58,"\x1F\x00\x44\xE3\x1E\xFF\x2F\xE1", 8);
    my_cool_Patches.cameraview1 = MemoryPatch(il2cppName, 0x133ca58,"\x21\x00\x44\xE3\x1E\xFF\x2F\xE1", 8);
    my_cool_Patches.cameraview2 = MemoryPatch(il2cppName, 0x133ca58,"\x23\x00\x44\xE3\x1E\xFF\x2F\xE1", 8);
    my_cool_Patches.cameraview3 = MemoryPatch(il2cppName, 0x133ca58,"\x2d\x00\x44\xE3\x1E\xFF\x2F\xE1", 8);
    my_cool_Patches.cameraview4 = MemoryPatch(il2cppName, 0x133ca58,"\x37\x00\x44\xE3\x1E\xFF\x2F\xE1", 8);
    my_cool_Patches.cameraview5 = MemoryPatch(il2cppName, 0x133ca58,"\x4b\x00\x44\xE3\x1E\xFF\x2F\xE1", 8);
    my_cool_Patches.cameraview6 = MemoryPatch(il2cppName, 0x133ca58,"\x55\x00\x44\xE3\x1E\xFF\x2F\xE1", 8);
    my_cool_Patches.cameraview7 = MemoryPatch(il2cppName, 0x133ca58,"\x5f\x00\x44\xE3\x1E\xFF\x2F\xE1", 8);
    my_cool_Patches.cameraview8 = MemoryPatch(il2cppName, 0x133ca58,"\x69\x00\x44\xE3\x1E\xFF\x2F\xE1", 8);
    my_cool_Patches.cameraview9 = MemoryPatch(il2cppName, 0x133ca58,"\x73\x00\x44\xE3\x1E\xFF\x2F\xE1", 8);
    my_cool_Patches.cameraview10 = MemoryPatch(il2cppName, 0x133ca58,"\x7d\x00\x44\xE3\x1E\xFF\x2F\xE1", 8);

    my_cool_Patches.speedrun1 = MemoryPatch(il2cppName, 0xad6900,"\x81\x0f\x43\xE3\x1E\xFF\x2F\xE1", 8);
    my_cool_Patches.speedrun2 = MemoryPatch(il2cppName, 0xad6900,"\x82\x0f\x43\xE3\x1E\xFF\x2F\xE1", 8);
    my_cool_Patches.speedrun3 = MemoryPatch(il2cppName, 0xad6900,"\x83\x0f\x43\xE3\x1E\xFF\x2F\xE1", 8);
    my_cool_Patches.speedrun4 = MemoryPatch(il2cppName, 0xad6900,"\x84\x0f\x43\xE3\x1E\xFF\x2F\xE1", 8);
    my_cool_Patches.speedrun5 = MemoryPatch(il2cppName, 0xad6900,"\x85\x0f\x43\xE3\x1E\xFF\x2F\xE1", 8);

    my_cool_Patches.speedcar1 = MemoryPatch(il2cppName, 0xb1f7dc,"\x6e\x0f\x43\xE3\x1E\xFF\x2F\xE1", 8);
    my_cool_Patches.speedcar2 = MemoryPatch(il2cppName, 0xb1f7dc,"\x78\x0f\x43\xE3\x1E\xFF\x2F\xE1", 8);
    my_cool_Patches.speedcar3 = MemoryPatch(il2cppName, 0xb1f7dc,"\x82\x0f\x43\xE3\x1E\xFF\x2F\xE1", 8);
    my_cool_Patches.speedcar4 = MemoryPatch(il2cppName, 0xb1f7dc,"\x8c\x0f\x43\xE3\x1E\xFF\x2F\xE1", 8);
    my_cool_Patches.speedcar5 = MemoryPatch(il2cppName, 0xb1f7dc,"\x96\x0f\x43\xE3\x1E\xFF\x2F\xE1", 8);

    my_cool_Patches.giant1 = MemoryPatch(unityName, 0x29bc28, "\x00\x00\x20\x41", 4);
    my_cool_Patches.giant2 = MemoryPatch(unityName, 0x29bc28, "\x00\x00\xA0\x41", 4);
    my_cool_Patches.giant3 = MemoryPatch(unityName, 0x29bc28, "\x00\x00\xF0\x41", 4);
    my_cool_Patches.giant4 = MemoryPatch(unityName, 0x29bc28, "\x00\x00\x20\x42", 4);
    my_cool_Patches.giant5 = MemoryPatch(unityName, 0x29bc28, "\x00\x00\x48\x42", 4);

    MSHookFunction((void *) getAbsoluteAddress(il2cppName, 0x108D8A8), (void *)_OnInit, (void **) &OnInit);
    MSHookFunction((void *) getAbsoluteAddress(il2cppName, 0x2262188), (void *)_Update, (void **) &Update);

    return NULL;
}

JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *globalEnv;
    vm->GetEnv((void **) &globalEnv, JNI_VERSION_1_6);
    pthread_t ptid;
    pthread_create(&ptid, NULL, hack_thread, NULL);
    return JNI_VERSION_1_6;
}
JNIEXPORT void JNICALL
JNI_OnUnload(JavaVM *vm, void *reserved) {}



