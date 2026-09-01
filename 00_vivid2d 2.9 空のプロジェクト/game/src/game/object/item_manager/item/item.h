#pragma once
#pragma once
#include"vivid.h"
#include"../item_id.h"

class Iitem
{
public:
	Iitem();
	~Iitem()=default;

	virtual void Initialize();
	virtual void Update();
	virtual void Draw();
	virtual void Finalize();
};