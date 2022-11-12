#include "TileLoader.h"

#include "ImageObj.h"
#include "ImageCollidable.h"
#include "ImageLoader.h"
#include "Rigidbody.h"
#include "Trigger.h"
#include "ColManager.h"

#include "RNG.h"


TileLoader::TileLoader()
{}

TileLoader::~TileLoader()
{
}


void TileLoader::IndexFix(int& index)
{
	bool invalid = true;

	if (index < 8)
		invalid = false;

	while (invalid)
	{
		if (index > 51)
		{
			index = 51;	
			invalid = false;
		}


		if (index >= 8 || index >= 9)
			index += 2;

		if (index >= 19)
			++index;

		if (index >= 25 || index >= 26)
			index += 2;;

		if (index >= 36)
			++index;

		if (index >= 46)
			++index;

		if (index != 8 && index != 9 && index != 19 && index != 25 && index != 26 && index != 36 && index != 46)
			invalid = false;

	}
}

Display TileLoader::GetTileDisplay(int index)
{
	//10 w, 6 h
	IndexFix(index);

	SDL_Rect result;
	result.w = 16;
	result.h = 16;
	result.x = (index % 10) * 16;
	result.y = (index / 10) * 16;

	Display tile(ImageLoader::GetInst()->GetImage("Tileset"), true);
	tile.SetTextureTransform(result);
	tile.SetTransformSize(tile.GetTextureTransform().w, tile.GetTextureTransform().h);

	return tile;
}

Object* TileLoader::LoadTile(int tileIndex)
{
	return new ImageObj(GetTileDisplay(tileIndex));
}

Object* TileLoader::LoadTile(int tileIndex, ColManager* colManager)
{
	ImageCollidable* tile = new ImageCollidable(GetTileDisplay(tileIndex));

	Rigidbody* tileCol = new Rigidbody(tile, tile->GetDisplay().GetTransform(), colManager, "tile");
	tileCol->SetChannels(Collision::Channels::kAll);
	tile->SetCollisionType(tileCol);

	return tile;
}

Object* TileLoader::LoadTile(int tileIndex, ColManager* colManager, std::function<void(ColComp*)> callback)
{
	ImageCollidable* tile = new ImageCollidable(GetTileDisplay(tileIndex));

	Trigger* tileCol = new Trigger(tile, tile->GetDisplay().GetTransform(), colManager, "tileTrigger", callback);
	tileCol->SetChannels(Collision::Channels::kAll);
	tile->SetCollisionType(tileCol);

	return tile;
}

Object* TileLoader::LoadRandomTile(ColManager* colManager)
{
	RNG rng(0, 59);

	if (colManager)
		return LoadTile(rng.Generate(), colManager);

	return LoadTile(rng.Generate());
}