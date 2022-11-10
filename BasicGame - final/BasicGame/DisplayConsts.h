#pragma once

//globals for all used symbols
//tiles
const char g_kEmptyTile = ' ';
const char g_kFloor = '.';
const char g_kWall = '=';
const char g_kEnd = 'E';
const char g_kSpikes = '*';
const char g_kSpikeTrap = '%';
const char g_kDoor = '(';
//user
const char g_kPlayer = '@';
//ai
const char g_kMonSpawn = 'M';
const char g_kWonderAi = '?';
const char g_kCircleAi = 'o';
const char g_kChaseAi = '!';
//pickup
const char g_kWeapon = '^';
const char g_kHealth = '+';
const char g_kArmor = '#';
const char g_kKey = 'k';

//currently if somthing new is added:
//
//change needed in levelMaker and Level
//posibly factory for object type