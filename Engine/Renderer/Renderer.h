#pragma once

/**
 * \brief 렌더링 명령 큐, 상태 설정, 뷰포트, 프레임 시작/끝
 */
class Renderer
{
public:
	Renderer(uint32_t width, uint32_t height);

	void OnUpdate();

	void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
	//void SetClearColor(const glm::vec4& color) ;
	void Clear();

private:

};

