#include "AnimComp.h"
#include "SDL_image.h"
#include "ImageLoader.h"

#include "Pawn.h"

AnimComp::AnimComp(const char* spriteSheetName, double frameRate, int frameW, int frameH, int frameCount)
	:m_pHitbox(nullptr)
	, m_pDamagebox(nullptr)
	, m_kFrameRate(frameRate)
	, m_currentFrameNum(-1)
	, m_pause(false)
	, m_currentSequenceName(" ")
	, m_nextFrameTime(0)
	, m_queuedSequenceName("\n")
	, m_currentSequenceOver(false)
{

	Initialize(spriteSheetName, frameW, frameH, frameCount);
	/*
	m_animState.SetTexture(ImageLoader::GetInst()->GetImage(spriteSheetName));

	//calc colum count
	int w, h;
	SDL_QueryTexture(m_animState.GetTexture(), NULL, NULL, &w, &h);

	m_spriteSheetColumns = w / frameW;
	//make sure sprite sheet is big enough to hold all frames  pImageSurface->
	int rows = h / frameH;
	if (rows * m_spriteSheetColumns < frameCount)
	{
		return;
	}

	//make transform match frame dimension
	m_animState.SetTransformSize(frameW, frameH);

	//source rect
	m_animState.SetTextureTransform(m_animState.GetTransform());*/
}

AnimComp::AnimComp(const char* spriteSheetName, double frameRate, int frameW, int frameH, int frameCount, ColComp* hitbox)
	:AnimComp(spriteSheetName, frameRate, frameW, frameH, frameCount)
{
	m_pHitbox = hitbox;
}


AnimComp::~AnimComp()
{
	m_pDamagebox = nullptr;
	m_pHitbox = nullptr;
}

AnimComp& AnimComp::operator=(const AnimComp& copy)
{
	if (this == &copy)
		return *this;

	m_kFrameRate = copy.m_kFrameRate;
	m_spriteSheetColumns = copy.m_spriteSheetColumns;
	m_animState = copy.m_animState;
	m_currentFrameNum = copy.m_currentFrameNum;
	m_nextFrameTime = copy.m_nextFrameTime;
	m_currentSequenceName = copy.m_currentSequenceName;
	m_allAnimations = copy.m_allAnimations;
	m_pause = copy.m_pause;
	m_queuedSequenceName = copy.m_queuedSequenceName;
	m_pDamagebox = copy.m_pDamagebox;
	m_pHitbox = copy.m_pHitbox;
	
	return *this;
}


void AnimComp::Initialize(const char* spriteSheetName, int frameW, int frameH, int frameCount)
{
	m_animState.SetTexture(ImageLoader::GetInst()->GetImage(spriteSheetName));

	//calc colum count
	int w, h;
	SDL_QueryTexture(m_animState.GetTexture(), NULL, NULL, &w, &h);

	m_spriteSheetColumns = w / frameW;
	//make sure sprite sheet is big enough to hold all frames  pImageSurface->
	int rows = h / frameH;
	if (rows * m_spriteSheetColumns < frameCount)
	{
		return;
	}

	//make transform match frame dimension
	m_animState.SetTransformSize(frameW, frameH);

	//source rect
	m_animState.SetTextureTransform(m_animState.GetTransform());
}

void AnimComp::AddAnimSequence(const char* sequenceName, int firstFrame, int lastFrame)
{
	m_allAnimations[sequenceName] = AnimSequence{ sequenceName, firstFrame, lastFrame, firstFrame };
}

void AnimComp::AddAnimSequence(const char* sequenceName, int firstFrame, int lastFrame, int startingFrame)
{
	if (startingFrame > lastFrame || startingFrame < firstFrame)
		startingFrame = firstFrame;

	m_allAnimations[sequenceName] = AnimSequence{ sequenceName, firstFrame, lastFrame, startingFrame };
}

void AnimComp::AddAnimSequence(AnimSequence animInfo)
{
	m_allAnimations[animInfo.m_name] = animInfo;
}

void AnimComp::PlayAnim(const char* sequenceName)
{
	if (sequenceName == m_currentSequenceName || m_allAnimations.find(sequenceName) == m_allAnimations.end())
	{
		//error
		return;
	}

	AnimSequence& newSequence = m_allAnimations[sequenceName];
	m_currentFrameNum = newSequence.m_startFrame;

	m_currentSequenceName = sequenceName;
	ResetFrameTime();
	UpdateSourceTransform();
}

void AnimComp::QueueAnim(const char* sequenceName)
{
	if (sequenceName == m_currentSequenceName || m_allAnimations.find(sequenceName) == m_allAnimations.end())
	{
		//error
		m_queuedSequenceName = "\n";
		return;
	}

	m_queuedSequenceName = sequenceName;
}

void AnimComp::ResetFrameTime()
{
	m_nextFrameTime = 1 / m_kFrameRate;
}

void AnimComp::UpdateSourceTransform()
{
	if (m_pHitbox)///update hitbox///
	{
		AnimSequence& currentSequence = m_allAnimations[m_currentSequenceName];
		SDL_Rect temp = currentSequence.m_hitboxTransforms[currentSequence.m_lastFrame - currentSequence.m_firstFrame + m_currentFrameNum + 1];//get index of frame transform
		m_pHitbox->SetSize(temp.w, temp.h);
	}///

	if (m_pDamagebox)///update hitbox///
	{
		AnimSequence& currentSequence = m_allAnimations[m_currentSequenceName];
		SDL_Rect temp = currentSequence.m_damageboxTransforms[currentSequence.m_lastFrame - currentSequence.m_firstFrame + m_currentFrameNum + 1];
		m_pDamagebox->SetSize(temp.w, temp.h);
	}///


	int frameX = m_currentFrameNum % m_spriteSheetColumns;
	int frameY = m_currentFrameNum / m_spriteSheetColumns;

	m_animState.SetTextureTransformPos((frameX * m_animState.GetTextureTransform().w), (frameY * m_animState.GetTextureTransform().h));
}

void AnimComp::Update(double delta)
{
	if (m_currentFrameNum == -1 || m_pause)
		return;

	if (DidCurrentSequenceEnd())
		PlayAnim(m_queuedSequenceName);

	AnimSequence& currentSequence = m_allAnimations[m_currentSequenceName];

	bool isFrameDirty = false;

	while (delta > m_nextFrameTime)
	{
		delta -= m_nextFrameTime;
		ResetFrameTime();

		isFrameDirty = true;

		if (currentSequence.m_lastFrame == m_currentFrameNum)
		{
			m_currentFrameNum = currentSequence.m_firstFrame;
			m_currentSequenceOver = true;
		}
		else
		{
			++m_currentFrameNum;
			m_currentSequenceOver = false;
		}
	}

	m_nextFrameTime -= delta;

	if (isFrameDirty)
		UpdateSourceTransform();
}

std::vector<const char*> AnimComp::GetSequences()
{
	std::vector<const char*> sequences;
	for (std::map<const char*, AnimSequence>::iterator it = m_allAnimations.begin(); it != m_allAnimations.end(); ++it)
	{
		sequences.push_back(it->first);
	}

	return sequences;
}