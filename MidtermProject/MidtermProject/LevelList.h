#pragma once

typedef char LevelLayout[20][40];//y,x
constexpr int g_kLevelX = 40;
constexpr int g_kLevelY = 20;
//templates for levels 



//overall layout
// L1, L2
// L3, L4

struct LevelLayout1 
{
	LevelLayout m_board =
	{ 
		 {"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"}
		,{"W   W          W            W          "}
		,{"W   W  X   X   W         K  W    K X   "}
		,{"W   W          D            W          "}
		,{"W   W    X     W            W      WWWW"}
		,{"W K W          WWWW WWWWWWWWW      W   "}
		,{"W   W          W    W   K X W      W   "}
		,{"WWDWWWW    X   W    W       WWWWWWWW   "}
		,{"W   K W        W    W  X    W      W   "}
		,{"W X X W   WWWWWW    W    XX W X  X W   "}
		,{"W     W   W    W    W     X D      W   "}
		,{"W XXX W   W    W    WWWWWDWWW   X  W   "}
		,{"W     W   W         W  X    W X    W   "}
		,{"W XX  D   WWW WWWWWWW       W   X  W   "}
		,{"WWWWWWW   W    W    W X XXXXWWWWDWWW   "}
		,{"W         W    W    W       W      W   "}
		,{"W         W    D    W XXXXX W      W   "}
		,{"W         W    W    W  X    W      W   "}
		,{"W         W    W    W    X  W      W   "}
		,{"W         WWWWWW    W       W      W   "}
	};
};

struct LevelLayout2
{
	LevelLayout m_board =
	{
		 {"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"}
		,{"    W             W    W          W   W"}
		,{"    W       W     W    W     W    W   W"}
		,{"    W       W     W    W     WWW WW   W"}
		,{"WWW WWWW WWWW     W    W     W        W"}
		,{"  W    W    W  WWWW    W WWWWWWWWWWWW W"}
		,{"  W    W    W    W     W W       W    W"}
		,{"WWW    W    W    W     W W       W    W"}
		,{"       W    W          W W       W    W"}
		,{"   X   W    WWW WWWWWWWWDW       W    W"}
		,{"      WWWWWDW     W      W     WWW    W"}
		,{"            W     W      W     W      W"}
		,{"      WWWWW W            WWWW WWDW    W"}
		,{"   X      W W     W      W     W WWW WW"}
		,{"WWWWW     W WWWWWWWWW WWWW     WKW    W"}
		,{"    W       W     W         X  W W    W"}
		,{"          W W   K W     X      W W    W"}
		,{"    W     W W     W  X     X   W W    W"}
		,{"    W     W       W            W W    W"}
		,{"WWWWWWWWWWWWWWWWWWWWWWWWWWWWW WW WW WWW"}
	};
};

struct LevelLayout3
{
	LevelLayout m_board =
	{
		 {"W         WWWWWW    W        W      WWW"}
		,{"W    K    W         W        W      W W"}
		,{"W         W         W        W      W W"}
		,{"WWWWWWWWWWWWWWW  WWWWWWWWW   WWWW WWW  "}
		,{"W         W           W         W W   W"}
		,{"WWWWWWWWW W  X    X   W         W W   W"}
		,{"W       W W           WWWWWWWW  W WWWWW"}
		,{"W WW WW W WWWWW WWWWWWW    W    W      "}
		,{"W W   W W       W          W W  W   W  "}
		,{"W W W W         W    WWWW WW W  W   W  "}
		,{"W W W WWWWWWW WWW    W    W  WWWW   W  "}
		,{"W W W W   W   W      W  WWW W     WWWWW"}
		,{"W W W W W W W W WWWWWW      W         W"}
		,{"W   W W W   WWW W    W      W    WWWW W"}
		,{"WWWWW WWWWWWW   W WW W  WWWWWWWWWW    W"}
		,{"W     W W       W W  W  WWW     W   WWW"}
		,{"W       W WWWWW W W  W          W   W  "}
		,{"W  K  W W W     W W  WWWWWWW    W WWW W"}
		,{"W     W   W       W             W     W"}
		,{"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"}
	};
};

struct LevelLayout4
{
	LevelLayout m_board =
	{
		 {"WWWWWWWWWWWWWWWWWWWWWWWWWWWWW WW WW WWW"}
		,{"WW    W     W WWW   W   W   D  W  W   W"}
		,{"W   W W WWW W W   W   W W   W KW  W   W"}
		,{"    W W W   W W WWWWWWW WWW W  W  W   W"}
		,{"W  WW   WW WW      W    W W WWWW  W   W"}
		,{"W   W WWWW WWWWWW  WWWW W W    W  WWW W"}
		,{"WWWWW  W   W    W W   W   W    W   W  W"}
		,{"    W  W WWWWWW W WWW  WWWW   WWWW W  W"}
		,{"    W  W     W   K   W WW W  W W   W  W"}
		,{"    WW WWWWW W WW  W W    W  W    WWW W"}
		,{"           W W W   W W   WW       W   W"}
		,{"WWWWWW WWW W   W WWW     WW WW WWWW   W"}
		,{"W          W WWW W   WW  W  W  W    WWW"}
		,{"W  WWW WWWWW     W   WW  WWWW WWWWW  WW"}
		,{"W  W W WW      WWW WW W   W W W       W"}
		,{"W  W    W WWWW W   W  WWWWW W WWW     W"}
		,{"   W  W   W    W   W            W     W"}
		,{"W  WW W WWWWWWWWWW    W   WWW W WW  EEW"}
		,{"W     W W         WWWWW       W     EEW"}
		,{"WWWWWWWWW             WWWWWWWWWWWWWWWWW"}
	};
};


