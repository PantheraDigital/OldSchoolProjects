#pragma once
#include <functional>
#include <SDL.h>


class Object;
class ColComp;
class ColManager;
class Display;


class TileLoader
{

	void IndexFix(int& index);
	Display GetTileDisplay(int index);

public:
	TileLoader();
	~TileLoader();


	Object* LoadTile(int tileIndex);
	Object* LoadTile(int tileIndex, ColManager* colManager);
	Object* LoadTile(int tileIndex, ColManager* colManager, std::function<void(ColComp*)> callback);

	Object* LoadRandomTile(ColManager* colManager);

};
