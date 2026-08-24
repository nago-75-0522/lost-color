#pragma once
#include"vivid.h"

#if 0

struct CAMERA
{
	vivid::Vector2 position;
};

#else
class CCamera
{
public:

	void Initialize();

	void Finalzie();

	void SetCameraPos(vivid::Vector2& pos);

	vivid::Vector2 GetCameraPos() { return m_Camera_Pos;}

	static CCamera& GetInstance();

private:
	CCamera();
	~CCamera() = default;
	
	CCamera(const CCamera& rhs);
	CCamera& operator =(const CCamera& rhs);
	vivid::Vector2 m_Camera_Pos;
};
#endif
