#pragma once
#pragma once
class CFall_Manager
{
	void Initialize();
	void Update();
	void Draw();
	void Finalize();

	static CFall_Manager& GetInstance();
private:
	CFall_Manager();
	~CFall_Manager() = default;
	CFall_Manager(const CFall_Manager& rhs);


};