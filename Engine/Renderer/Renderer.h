#pragma once

/**
 * \brief ������ ��� ť, ���� ����, ����Ʈ, ������ ����/��
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

