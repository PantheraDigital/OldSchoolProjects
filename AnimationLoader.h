#pragma once
#include <vector>
#include <optional>
#include <string>

class AnimComp;
class ColComp;

class AnimationLoader
{
	struct AnimData
	{
		const char* m_spriteSheetName;
		double m_frameRate;
		int m_frameW;
		int m_frameH;
		int m_frameCount;

		AnimData(const char* spriteSheetName, double frameRate, int frameW, int frameH, int frameCount)
			:m_spriteSheetName(spriteSheetName)
			, m_frameRate(frameRate)
			, m_frameW(frameW)
			, m_frameH(frameH)
			, m_frameCount(frameCount)
		{}

	};

	std::vector<AnimData> m_anims;


//	bool LoadAnimData(int index);
//	void SaveAnimData(std::vector<AnimData> animData);

	void AnimSetup(AnimComp& animRef, int dataIndex);

public:
	AnimationLoader();

	std::optional<AnimComp> Load(const char* animName);
	std::optional<AnimComp> Load(const char* animName, ColComp* hitbox);///
};