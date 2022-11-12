#pragma once
#include <SDL.h>
#include <map>
#include <vector>

#include "Display.h"
#include "ColComp.h"

/////////////////////////
//holds a single sheet with animations on it
////////////////////////////
class AnimComp
{
public:

	//set of frames and col info for frames
	struct AnimSequence
	{
		const char* m_name;
		int m_firstFrame;
		int m_lastFrame;
		int m_startFrame;//frame anim starts on at begining of loop
		bool m_interuptable;//does animation play till end?

		std::vector<SDL_Rect> m_hitboxTransforms;//transforms per-frame for anim hitbox///
		std::vector<SDL_Rect> m_damageboxTransforms;//transforms per-frame for damageing hitbox///
	};


private:
	double m_kFrameRate;
	
	//this is very sensitive/ if w / frameW is a float this will loose accuracy/ frame W and H must be accurat or sprite will fill screen
	int m_spriteSheetColumns;
	Display m_animState;//transform and image

	//collisions animation will controll
	//split anim comp into subclasses that are like the 3 constructors
	ColComp* m_pHitbox;///
	ColComp* m_pDamagebox;///

	int m_currentFrameNum;
	double m_nextFrameTime;//when anim switches to next frame
	const char* m_currentSequenceName;
	const char* m_queuedSequenceName;
	bool m_currentSequenceOver;
	std::map<const char*, AnimSequence> m_allAnimations;//can add events by adding pair of events with animsequences
														//events hold their active frames and a func for what to do
														//add their funcs to an event sys when anim is played/ update for event sys will take delta and current frame

	bool m_pause;


	void Initialize(const char* spriteSheetName, int frameW, int frameH, int frameCount);

	void ResetFrameTime();
	void UpdateSourceTransform();


public:
	AnimComp(const char* spriteSheetName, double frameRate, int frameW, int frameH, int frameCount);//no collision/ ex: background animated obj
	AnimComp(const char* spriteSheetName, double frameRate, int frameW, int frameH, int frameCount, ColComp* hitbox);//only hitbox/ ex: animated solid
	AnimComp(const char* spriteSheetName, double frameRate, int frameW, int frameH, int frameCount, ColComp* hitbox, ColComp* damagebox);// hitbox and damage box/ ex: animated enemy that attacks

	~AnimComp();

	AnimComp& operator=(const AnimComp& copy);


	void AddAnimSequence(const char* sequenceName, int firstFrame, int lastFrame);
	void AddAnimSequence(const char* sequenceName, int firstFrame, int lastFrame, int startingFrame);
	void AddAnimSequence(AnimSequence animInfo);

	void PlayAnim(const char* sequenceName);

	void QueueAnim(const char* sequenceName);

	void Pause(bool pause = true) { m_pause = pause; }

	void Update(double delta);
	
	bool DidCurrentSequenceEnd() const { return m_currentSequenceOver; }

	Display GetDisp() const { return m_animState; }

	void SetPos(int x, int y) { m_animState.SetTransformPos(x, y); }

	void SetAnimFlip(SDL_RendererFlip animFlip) { m_animState.SetFlip(animFlip); }

	std::vector<const char*> GetSequences();
};

