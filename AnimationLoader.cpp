#include "AnimationLoader.h"

#include <iostream>
#include <fstream>
#include <limits>  
#include <string>

#include "AnimComp.h"
#include "ColComp.h"

#define NOMINMAX   
#include <windows.h>


AnimationLoader::AnimationLoader()
{
	//const char* spriteSheetName, double frameRate, int frameW, int frameH, int frameCount

	m_anims.push_back(AnimData("charTest    ", 10, 16, 20, 16));
	m_anims.push_back(AnimData("adventurer  ", 10, 50, 37, 112));

//	SaveAnimData(m_anims);
//	LoadAnimData(0);
}

/*
bool AnimationLoader::LoadAnimData(int index)
{
	std::fstream fileStream;
	fileStream.open("AnimationData/List.txt", std::ios_base::in);

	if (!fileStream.is_open())
	{
		std::cout << "Loading Error" << std::endl;
		return false;
	}

	std::string loaded;
	std::string tempLine;


	std::string spriteSheetName;//12
	double frameRate = 0;//3
	int frameW = 0;//3
	int frameH = 0;//3
	int frameCount = 0;//3

	while (!fileStream.eof())
	{
		std::getline(fileStream, spriteSheetName, ',');
		std::cout << spriteSheetName << std::endl;

		fileStream >> frameRate;
		std::cout << frameRate << std::endl;
		fileStream.ignore(std::numeric_limits<std::streamsize>::max(), ',');

		fileStream >> frameW;
		std::cout << frameW << std::endl;
		fileStream.ignore(std::numeric_limits<std::streamsize>::max(), ',');

		fileStream >> frameH;
		std::cout << frameH << std::endl;
		fileStream.ignore(std::numeric_limits<std::streamsize>::max(), ',');

		fileStream >> frameCount;
		std::cout << frameCount << std::endl;
		fileStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		/*
			m_anims.push_back(AnimData(spriteSheetName.c_str(), frameRate, frameW, frameH, frameCount));//not adding to vector?
		
	}

	/*
		std::cout << m_anims[1].m_spriteSheetName << "|";
	
	//close the file
	fileStream.close();

	return true;
}

void AnimationLoader::SaveAnimData(std::vector<AnimData> animData)
{
	// 1. open the file
	std::fstream fileStream;
	fileStream.open("AnimationData/List.txt", std::ios_base::out | std::ios_base::trunc);//write over any already existing file here

	// 2. make sure the file opened
	if (!fileStream.is_open())
	{
		std::cout << "Error opening file." << std::endl;
		return;
	}

	// 3. process the file

	for (unsigned int i = 0; i < animData.size(); ++i)
	{
		for (unsigned int j = 0; j < 12; ++j)
		{
			fileStream.write(&(animData[i].m_spriteSheetName[j]), sizeof(char));//contents
		}
		fileStream << ", ";
		fileStream << animData[i].m_frameRate;//space out based on num of digits/////
		fileStream << ", ";
		fileStream << animData[i].m_frameW;
		fileStream << ", ";
		fileStream << animData[i].m_frameH;
		fileStream << ", ";
		fileStream << animData[i].m_frameCount;

		fileStream.write("\n", sizeof(char));//line break
	}

	// 4. close the file
	fileStream.close();
}
*/

std::optional<AnimComp> AnimationLoader::Load(const char* animName)
{
	bool valid = false;
	int index = -1;

	for (int i = 0; i < m_anims.size(); ++i)
	{
		if (m_anims[i].m_spriteSheetName == animName)
		{
			index = i;
			break;
		}
	}

	if (index == -1)
	{
		std::cout << "Could not find anim: " << animName << std::endl;
		return {};
	}


	AnimData animData = m_anims[index];

	AnimComp anim(animData.m_spriteSheetName, animData.m_frameRate, animData.m_frameW, animData.m_frameH, animData.m_frameCount);
	AnimSetup(anim, index);

	return anim;
}

std::optional<AnimComp> AnimationLoader::Load(const char* animName, ColComp* hitbox)
{
	bool valid = false;
	int index = -1;

	for (int i = 0; i < m_anims.size(); ++i)
	{
		if (m_anims[i].m_spriteSheetName == animName)
		{
			index = i;
			break;
		}
	}

	if (index == -1)
	{
		std::cout << "Could not find anim: " << animName << std::endl;
		return {};
	}


	AnimData animData = m_anims[index];

	AnimComp anim(animData.m_spriteSheetName, animData.m_frameRate, animData.m_frameW, animData.m_frameH, animData.m_frameCount, hitbox);
	AnimSetup(anim, index);

	return anim;
}

void AnimationLoader::AnimSetup(AnimComp& animRef, int dataIndex)
{
	switch (dataIndex)
	{
	case 0:
	{
		animRef.AddAnimSequence("idelDown", 0, 0);
		animRef.AddAnimSequence("idelUp", 4, 4);
		animRef.AddAnimSequence("idelLeft", 8, 8);
		animRef.AddAnimSequence("idelRight", 13, 13);
		animRef.AddAnimSequence("walkDown", 0, 3, 1);
		animRef.AddAnimSequence("walkUp", 4, 7);
		animRef.AddAnimSequence("walkLeft", 8, 11);
		animRef.AddAnimSequence("walkRight", 12, 15);
		break;
	}

	case 1:
	{
		//set of frames and col info for frames
	//	animRef.AddAnimSequence("idle", 0, 3);
		AnimComp::AnimSequence temp;///
		temp.m_name = "idle";
		temp.m_firstFrame = 0;
		temp.m_lastFrame = 3;
		temp.m_interuptable = true;
		temp.m_startFrame = 0;
		temp.m_hitboxTransforms.push_back(SDL_Rect{ 5,5,0,0 });
		temp.m_hitboxTransforms.push_back(SDL_Rect{ 6,6,0,0 });
		temp.m_hitboxTransforms.push_back(SDL_Rect{ 7,7,0,0 });
		temp.m_hitboxTransforms.push_back(SDL_Rect{ 8,8,0,0 });///

		animRef.AddAnimSequence(temp);

		animRef.AddAnimSequence("swordOutIdle", 38, 41);
		animRef.AddAnimSequence("crouchIdle", 4, 7);

		animRef.AddAnimSequence("walk", 8, 13);

		animRef.AddAnimSequence("jump", 14, 17);
		animRef.AddAnimSequence("flip", 18, 21);
		animRef.AddAnimSequence("fall", 22, 23);

		animRef.AddAnimSequence("slide", 24, 28);

		animRef.AddAnimSequence("wallSlide", 79, 80);
		animRef.AddAnimSequence("climb", 81, 84);

		animRef.AddAnimSequence("ledgeHold", 29, 32);
		animRef.AddAnimSequence("ledgeClimb", 33, 37);

		animRef.AddAnimSequence("unshieth", 69, 72);
		animRef.AddAnimSequence("shieth", 73, 76);

		animRef.AddAnimSequence("slashUp", 42, 48);
		animRef.AddAnimSequence("slashDown", 49, 52);
		animRef.AddAnimSequence("spinSlash", 53, 58);
		animRef.AddAnimSequence("dashSlash", 96, 99);
		animRef.AddAnimSequence("slashUpAir", 99, 102);
		animRef.AddAnimSequence("swordSlam", 102, 105);
		animRef.AddAnimSequence("stillSlash", 106, 108);

		animRef.AddAnimSequence("crouch", 63, 68);

		animRef.AddAnimSequence("punch", 85, 92);
		animRef.AddAnimSequence("punchUp", 93, 95);
		animRef.AddAnimSequence("dash?", 77, 78);
		animRef.AddAnimSequence("unknown", 59, 62);
		break;
	}

	default:
		break;
	}
}