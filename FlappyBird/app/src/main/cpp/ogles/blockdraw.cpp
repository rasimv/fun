#include "../game/block.h"
#include <cassert>
#include "blockdd.h"
#include "dcimpl.h"
#include "../game/defs.h"
#include "oglaux.h"

namespace Game
{
	DrawData *Block::createDD()
	{
		return new BlockDD();;
	}

	void Block::postEvol()
	{}

	void Block::initDraw(DrawContext *a)
	{
		assert(dynamic_cast<BlockDD *>(m_dd) != nullptr);
		BlockDD *const l_dd = static_cast<BlockDD *>(m_dd);
		l_dd->genBuf();
		l_dd->loadBuf();
		l_dd->setInited(true);
	}

	void Block::draw(DrawContext *a)
	{
		assert(dynamic_cast<DCImpl *>(a) != nullptr);
		assert(dynamic_cast<BlockDD *>(m_dd) != nullptr);
		BlockDD *const l_dd = static_cast<BlockDD *>(m_dd);
		if (!l_dd->inited()) initDraw(a);
		DCImpl *l_dc = static_cast<DCImpl *>(a);

        const auto l_c(center());
		const GLfloat l_transf[] = { w() / 2, 0, 0, 0,
									 0, h() / 2, 0, 0,
									 0, 0, 1, 0,
                                     l_c.first, l_c.second, 0, 1 };

		::glUniformMatrix4fv(l_dc->transf(), 1, GL_FALSE, l_transf);
		::drawBuffer(l_dd->buf(), 0, 2 * 3);    //2 * 3 - два треугольника
	}
}
